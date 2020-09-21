//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_container.h                     $
// $Revision:: 2                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 9/10/99 5:24p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_container.h                          $
// 
// 2     9/10/99 5:24p Aldie
// Merge code
// 
// 1     9/10/99 10:48a Jimdose
// 
// 2     9/09/99 3:30p Aldie
// Merge
// 
// 1     9/08/99 3:35p Aldie
//
// DESCRIPTION:
// Base class for a dynamic array.  Allows adding, removing, index of,
// and finding of entries with specified value.  Originally created for
// cataloging entities, but pointers to objects that may be removed at
// any time are bad to keep around, so only entity numbers should be
// used in the future.
//

#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <stdlib.h>

template< class Type >
class Container
	{
	private:
		Type	*objlist;
		int	numobjects;
		int	maxobjects;

	public:
					Container();
					~Container<Type>();
		void		FreeObjectList( void );
		void		ClearObjectList( void );
		int		NumObjects( void );
		void		Resize( int maxelements );
		void		SetObjectAt( int index, Type& obj );
		int		AddObject( Type& obj );
		int		AddUniqueObject( Type& obj );
		void  	AddObjectAt( int index, Type& obj );
		int		IndexOfObject( Type& obj );
		qboolean	ObjectInList( Type& obj );
		Type&		ObjectAt( int index );
		Type		*AddressOfObjectAt( int index );
		void		RemoveObjectAt( int index );
		void		RemoveObject( Type& obj );
		void		Sort( int ( __cdecl *compare )( const void *elem1, const void *elem2 ) );
	};

template< class Type >
Container<Type>::Container()
	{
	objlist = NULL;
	FreeObjectList();
	}

template< class Type >
Container<Type>::~Container<Type>()
	{
	FreeObjectList();
	}

template< class Type >
void Container<Type>::FreeObjectList
	(
	void
	)

	{
	if ( objlist )
		{
		delete[] objlist;
		}
	objlist = NULL;
	numobjects = 0;
	maxobjects = 0;
	}

template< class Type >
void Container<Type>::ClearObjectList
	(
	void
	)

	{
	// only delete the list if we have objects in it
	if ( objlist && numobjects )
		{
		delete[] objlist;
		objlist = new Type[ maxobjects ];
		numobjects = 0;
		}
	}

template< class Type >
int Container<Type>::NumObjects
	(
	void
	)

	{
	return numobjects;
	}

template< class Type >
void Container<Type>::Resize
	(
	int maxelements
	)

	{
	Type *temp;
	int i;

   assert( maxelements >= 0 );

   if ( maxelements <= 0 )
      {
      FreeObjectList();
      return;
      }

	if ( !objlist )
		{
		maxobjects = maxelements;
		objlist = new Type[ maxobjects ];
		}
	else
		{
		temp = objlist;
		maxobjects = maxelements;
		if ( maxobjects < numobjects )
			{
			maxobjects = numobjects;
			}

		objlist = new Type[ maxobjects ];
		for( i = 0; i < numobjects; i++ )
			{
			objlist[ i ] = temp[ i ];
			}
		delete[] temp;
		}
	}

template< class Type >
void Container<Type>::SetObjectAt
	(
	int index,
	Type& obj
	)

	{
	if ( ( index <= 0 ) || ( index > numobjects ) )
		{
		gi.Error( ERR_DROP, "Container::SetObjectAt : index out of range" );
		}

	objlist[ index - 1 ] = obj;
	}

template< class Type >
int Container<Type>::AddObject
	(
	Type& obj
	)

	{
	if ( !objlist )
		{
		Resize( 10 );
		}

	if ( numobjects == maxobjects )
		{
		Resize( maxobjects * 2 );
		}

	objlist[ numobjects ] = obj;
	numobjects++;

	return numobjects;
	}

template< class Type >
int Container<Type>::AddUniqueObject
	(
	Type& obj
	)

	{
   int index;

   index = IndexOfObject( obj );
   if ( !index )
      index = AddObject( obj );
   return index;
	}

template< class Type >
void Container<Type>::AddObjectAt
	(
	int index,
	Type& obj
	)

	{
   //
   // this should only be used when reconstructing a list that has to be identical to the original
   //
   if ( index > maxobjects )
      {
      Resize( index );
      }
   if ( index > numobjects )
      {
      numobjects = index;
      }
   SetObjectAt( index, obj );
	}

template< class Type >
int Container<Type>::IndexOfObject
	(
	Type& obj
	)

	{
	int i;

	for( i = 0; i < numobjects; i++ )
		{
		if ( objlist[ i ] == obj )
			{
			return i + 1;
			}
		}

	return 0;
	}

template< class Type >
qboolean Container<Type>::ObjectInList
	(
	Type& obj
	)

	{
	if ( !IndexOfObject( obj ) )
		{
		return false;
		}

	return true;
	}

template< class Type >
Type& Container<Type>::ObjectAt
	(
	int index
	)

	{
	if ( ( index <= 0 ) || ( index > numobjects ) )
		{
		cgi.Error( ERR_DROP, "Container::ObjectAt : index out of range" );
		}

	return objlist[ index - 1 ];
	}

template< class Type >
Type * Container<Type>::AddressOfObjectAt
	(
	int index
	)

	{
   //
   // this should only be used when reconstructing a list that has to be identical to the original
   //
   if ( index > maxobjects )
      {
      cgi.Error( ERR_DROP, "Container::AddressOfObjectAt : index is greater than maxobjects" );
      }
   if ( index > numobjects )
      {
      numobjects = index;
      }
	return &objlist[ index - 1 ];
	}

template< class Type >
void Container<Type>::RemoveObjectAt
	(
	int index
	)

	{
	int i;

	if ( !objlist )
		{
      cgi.Printf( "Container::RemoveObjectAt : Empty list\n" );
		return;
		}

	if ( ( index <= 0 ) || ( index > numobjects ) )
		{
		cgi.Error( ERR_DROP, "Container::RemoveObjectAt : index out of range" );
		return;
		}

	i = index - 1;
	numobjects--;
	for( i = index - 1; i < numobjects; i++ )
		{
		objlist[ i ] = objlist[ i + 1 ];
		}
	}

template< class Type >
void Container<Type>::RemoveObject
	(
	Type& obj
	)

	{
	int index;

	index = IndexOfObject( obj );
	if ( !index )
		{
      gi.DPrintf( "Container::RemoveObject : Object not in list\n" );
		return;
		}

	RemoveObjectAt( index );
	}

template< class Type >
void Container<Type>::Sort
	(
	int ( __cdecl *compare )( const void *elem1, const void *elem2 )
	)

	{
	if ( !objlist )
		{
      gi.DPrintf( "Container::RemoveObjectAt : Empty list\n" );
		return;
		}

	qsort( ( void * )objlist, ( size_t )numobjects, sizeof( Type ), compare );
	}

//
// Exported templated classes must be explicitly instantiated
//
#ifdef EXPORT_TEMPLATE
template class Container<int>;
#endif

#endif /* container.h */