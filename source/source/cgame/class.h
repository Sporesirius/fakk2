//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/client/class.h                           $
// $Revision:: 13                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 8/10/00 9:27p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/client/class.h                                $
// 
// 13    8/10/00 9:27p Aldie
// Fixing memory leaks
// 
// 12    8/10/00 6:34p Aldie
// Added a shutdown method
// 
// 11    6/14/00 12:14p Markd
// more intel compiler bug fixes
// 
// 10    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 9     5/26/00 7:44p Markd
// 2nd phase save games
// 
// 8     5/25/00 4:28p Markd
// fixed up archive functions
// 
// 7     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 6     4/26/00 7:55p Markd
// Added more documentation code into various systems
// 
// 5     3/16/00 10:50a Markd
// Fixed some bad syntax in headers that exhibited itself in non-visualc
// compilers
// 
// 4     12/15/99 11:45a Markd
// made Event's Classes and also freed up safe pointers at the appropriate
// times
// 
// 3     10/05/99 2:03p Markd
// Added warning about files being in multiple projects
// 
// 2     9/28/99 4:26p Markd
// merged listener, class and vector between 3 projects
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 6     8/27/99 3:31p Markd
// externed totalmemallocated
//
// DESCRIPTION:
// Base class that all classes that are used in conjunction with Sin should
// be based off of.  Class gives run-time type information about any class
// derived from it.  This is really handy when you have a pointer to an object 
// that you need to know if it supports certain behaviour.
//
// WARNING: This file is shared between fgame, cgame and possibly the user interface.
// It is instanced in each one of these directories because of the way that SourceSafe works.
// 

#ifndef __CLASS_H__
#define __CLASS_H__

#if defined( GAME_DLL )
//
// game dll specific defines
//
#include "g_local.h"
#include "linklist.h"

#define CLASS_DPrintf gi.DPrintf
#define CLASS_Printf gi.Printf
#define CLASS_Error gi.Error

class Archiver;

#elif defined ( CGAME_DLL )
//
// cgame dll specific defines
//
#include "../fgame/q_shared.h"
#include "linklist.h"

#define CLASS_DPrintf cgi.DPrintf
#define CLASS_Printf cgi.Printf
#define CLASS_Error cgi.Error

#else

//
// client specific defines
//
#include "../fgame/q_shared.h"
#include "linklist.h"

#define CLASS_DPrintf Com_DPrintf
#define CLASS_Printf Com_Printf
#define CLASS_Error Com_Error
#endif

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
      void  Shutdown( void );
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
      Class       *Pointer( void );
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
	static	void				*_newInstance( void );			            \
	virtual	ClassDef			*classinfo( void );			               \
	static	ResponseDef<nameofclass>	Responses[]

class Class
	{
   private:
		SafePtrBase	 *SafePtrList;
		friend class SafePtrBase;

   protected:
      void              ClearSafePointers( void );

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

#ifdef GAME_DLL
		virtual void		Archive( Archiver &arc );
#endif
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
void     ClassEvents( const char *classname, qboolean dump = qfalse );
void     DumpAllClasses( void	);

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

inline Class * SafePtrBase::Pointer
   (
   void
   )

	{
   return ptr;
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

#ifdef GAME_DLL
#include "archive.h"
#endif

// used by listener for event allocation
extern int totalmemallocated;

#ifndef GAME_DLL
extern "C" 
   {
   // interface functions
   void	        ShutdownClasses( void );
   }
#endif

#endif /* class.h */
