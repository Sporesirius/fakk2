//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_class.h                         $
// $Revision:: 1                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 9/10/99 10:48a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_class.h                              $
// 
// 1     9/10/99 10:48a Jimdose
// 
// 1     9/08/99 3:35p Aldie
// 
// 2     7/29/99 3:32p Aldie
// Updated to new class system
//
// DESCRIPTION:
// Base class that all classes that are used in conjunction with Sin should
// be based off of.  Class gives run-time type information about any class
// derived from it.  This is really handy when you have a pointer to an object 
// that you need to know if it supports certain behaviour.
// 

#ifndef __CG_CLASS_H__
#define __CG_CLASS_H__

#include "../fgame/q_shared.h"
#include "../fgame/linklist.h"
 
class Class;
class Event;

typedef void ( Class::*Response )( Event *event );

template< class Type >
struct ResponseDef
	{
	Event		      *event;
   void           ( Type::*response )( Event *event );
	};

/***********************************************************************

  ClassDef

***********************************************************************/

class ClassDef
	{
	public:
		const char	*classname;
		const char	*classID;
		const char	*superclass;
		void			*( *newInstance )( void );
		int			classSize;
		ResponseDef<Class> *responses;
		int			numEvents;
		Response		**responseLookup;
		ClassDef		*super;
		ClassDef		*next;
		ClassDef		*prev;

		ClassDef();
		~ClassDef();
		ClassDef( const char *classname, const char *classID, const char *superclass, 
			ResponseDef<Class> *responses, void *( *newInstance )( void ), int classSize );
		void	BuildResponseList( void );
	};

/***********************************************************************

  SafePtr

***********************************************************************/

class SafePtrBase;

class Class;

class SafePtrBase
	{
   private:
		void	AddReference( Class *ptr );
		void	RemoveReference( Class *ptr );

	protected:
		SafePtrBase *prevSafePtr;
		SafePtrBase *nextSafePtr;
		Class       *ptr;

	public:
                  SafePtrBase();
		virtual     ~SafePtrBase();
		void	      InitSafePtr( Class *newptr );
      void	      Clear( void );
	};

/***********************************************************************

  Class

***********************************************************************/

#define CLASS_DECLARATION( nameofsuperclass, nameofclass, classid )	\
	ClassDef nameofclass::ClassInfo												\
		(																					\
		#nameofclass, classid, #nameofsuperclass,								\
		( ResponseDef<Class> * )nameofclass::Responses,                \
      nameofclass::_newInstance,	sizeof( nameofclass )					\
		);																					\
	void *nameofclass::_newInstance( void )				               \
		{																					\
		return new nameofclass;														\
		}																					\
	ClassDef *nameofclass::classinfo( void )								   \
		{																					\
		return &( nameofclass::ClassInfo );										\
      }                                                              \
   ResponseDef<nameofclass> nameofclass::Responses[] =


#define CLASS_PROTOTYPE( nameofclass )											\
	public:																				\
	static	ClassDef			ClassInfo;											\
	static	void				*nameofclass::_newInstance( void );			\
	virtual	ClassDef			*nameofclass::classinfo( void );			   \
	static	ResponseDef<nameofclass>	nameofclass::Responses[];

class Class
	{
   private:
		SafePtrBase	 *SafePtrList;
		friend class SafePtrBase;

	public:
		CLASS_PROTOTYPE( Class );
		void * operator	new( size_t );
		void operator		delete( void * );

								Class();
		virtual				~Class();
		void					warning( const char *function, const char *fmt, ... );
		void					error( const char *function, const char *fmt, ... );
		qboolean				inheritsFrom( ClassDef *c );
		qboolean				inheritsFrom( const char *name );
		qboolean				isInheritedBy( const char *name );
		qboolean				isInheritedBy( ClassDef *c );
		const char			*getClassname( void );
		const char			*getClassID( void );
		const char			*getSuperclass( void );
		void					*newInstance( void );
	};

void		BuildEventResponses( void );
ClassDef	*getClassForID( const char *name );
ClassDef	*getClass( const char *name );
ClassDef	*getClassList( void );
void		listAllClasses( void );
void		listInheritanceOrder( const char *classname );
qboolean	checkInheritance( ClassDef *superclass, ClassDef *subclass );
qboolean	checkInheritance( ClassDef *superclass, const char *subclass );
qboolean	checkInheritance( const char *superclass, const char *subclass );
void     DisplayMemoryUsage( void );

inline qboolean Class::inheritsFrom
	( 
	ClassDef *c 
	)

	{
	return checkInheritance( c, classinfo() );
	}

inline qboolean Class::isInheritedBy
	( 
	ClassDef *c 
	)

	{
	return checkInheritance( classinfo(), c );
	}

// The lack of a space between the ")" and "inheritsFrom" is intentional.
// It allows the macro to compile like a function call.  However, this
// may cause problems in some compilers (like gcc), so we may have to
// change this to work like a normal macro with the object passed in
// as a parameter to the macro.
#define isSubclassOf( classname )inheritsFrom( &classname::ClassInfo )
#define isSuperclassOf( classname )isInheritedBy( &classname::ClassInfo )

/***********************************************************************

  SafePtr

***********************************************************************/

inline SafePtrBase::SafePtrBase()
	{
   prevSafePtr = NULL;
	nextSafePtr = NULL;
   ptr = NULL;
   }

inline SafePtrBase::~SafePtrBase()
	{
   Clear();
   }

inline void SafePtrBase::Clear
   (
   void
   )

	{
	if ( ptr )
		{
		RemoveReference( ptr );
		ptr = NULL;
		}
	}

inline void SafePtrBase::InitSafePtr
   (
   Class *newptr
   )

	{
	if ( ptr != newptr )
		{
		if ( ptr )
			{
			RemoveReference( ptr );
			}

		ptr = newptr;
	   if ( ptr == NULL )
		   {
		   return;
   	   }

      AddReference( ptr );
      }
	}

inline void SafePtrBase::AddReference
	(
	Class *ptr
	)

	{
	if ( !ptr->SafePtrList )
		{
		ptr->SafePtrList = this;
		LL_Reset( this, nextSafePtr, prevSafePtr );
		}
	else
		{
		LL_Add( ptr->SafePtrList, this, nextSafePtr, prevSafePtr );
		}
	}

inline void SafePtrBase::RemoveReference
	(
	Class *ptr
	)

	{
	if ( ptr->SafePtrList == this )
		{
		if ( ptr->SafePtrList->nextSafePtr == this )
			{
			ptr->SafePtrList = NULL;
			}
		else
			{
			ptr->SafePtrList = nextSafePtr;
			LL_Remove( this, nextSafePtr, prevSafePtr );
			}
		}
	else
		{
		LL_Remove( this, nextSafePtr, prevSafePtr );
		}
	}

template<class T>
class SafePtr : public SafePtrBase
	{
	public:
		SafePtr( T* objptr = 0 );
		SafePtr( const SafePtr& obj );

		SafePtr& operator=( const SafePtr& obj );
		SafePtr& operator=( T * const obj );

		friend int operator==( SafePtr<T> a, T *b );
		friend int operator!=( SafePtr<T> a, T *b );
		friend int operator==( T *a, SafePtr<T> b );
		friend int operator!=( T *a, SafePtr<T> b );

      operator	T*() const;
		T* operator->() const;
		T& operator*() const;
	};

template<class T>
inline SafePtr<T>::SafePtr( T* objptr )
	{
   InitSafePtr( objptr );
	}

template<class T>
inline SafePtr<T>::SafePtr( const SafePtr& obj )
	{
   InitSafePtr( obj.ptr );
	}

template<class T>
inline SafePtr<T>& SafePtr<T>::operator=( const SafePtr& obj )
	{
   InitSafePtr( obj.ptr );
	return *this;
	}

template<class T>
inline SafePtr<T>& SafePtr<T>::operator=( T * const obj )
	{
   InitSafePtr( obj );
	return *this;
	}

template<class T>
inline int operator==
	(
	SafePtr<T> a,
	T* b
	)

	{
	return a.ptr == b;
	}

template<class T>
inline int operator!=
	(
	SafePtr<T> a,
	T* b
	)

	{
	return a.ptr != b;
	}

template<class T>
inline int operator==
	(
	T* a,
	SafePtr<T> b
	)

	{
	return a == b.ptr;
	}

template<class T>
inline int operator!=
	(
	T* a,
	SafePtr<T> b
	)

	{
	return a != b.ptr;
	}

template<class T>
inline SafePtr<T>::operator T*() const
	{
	return ( T * )ptr;
	}

template<class T>
inline T* SafePtr<T>::operator->() const
	{
	return ( T * )ptr;
	}

template<class T>
inline T& SafePtr<T>::operator*() const
	{
	return *( T * )ptr;
	}

typedef SafePtr<Class> ClassPtr;

#endif /* class.h */