//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/stack.h                            $
// $Revision:: 2                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 7/25/00 11:32p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/stack.h                                 $
// 
// 2     7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
//
// DESCRIPTION:
// Generic Stack object.
// 

#ifndef __STACK_H__
#define __STACK_H__

#include "g_local.h"
#include "class.h"

template <class Type>
class StackNode : public Class
	{
	public:
		Type		 data;
		StackNode *next;

		StackNode( Type d );
	};

template <class Type>
inline StackNode<Type>::StackNode( Type d ) : data( d )
	{
	next = NULL; 
	}

template <class Type>
class Stack : public Class
	{
	private:
		StackNode<Type> *head;

	public:
					Stack();
					~Stack<Type>();
		void		Clear( void	);
		qboolean Empty( void );
		void		Push( Type data );
		Type		Pop( void );
	};

template <class Type>
inline Stack<Type>::Stack()
	{
	head = NULL;
	}

template <class Type>
inline Stack<Type>::~Stack<Type>()
	{
	Clear();
	}

template <class Type>
inline void Stack<Type>::Clear
	(
	void
	)

	{
	while( !Empty() )
		{
		Pop();
		}
	}

template <class Type>
inline qboolean Stack<Type>::Empty
	(
	void
	)

	{
	if ( head == NULL )
		{
		return true;
		}
	return false;
	}

template <class Type>
inline void Stack<Type>::Push
	(
	Type data
	)

	{
	StackNode<Type> *tmp;

	tmp = new StackNode<Type>( data );
	if ( !tmp )
		{
		assert( NULL );
		gi.Error( ERR_DROP, "Stack::Push : Out of memory" );
		}

	tmp->next = head;
	head = tmp;
	}

template <class Type>
inline Type Stack<Type>::Pop
	(
	void
	)

	{
	Type ret;
	StackNode<Type> *node;

	if ( !head )
		{
		return NULL;
		}

	node	= head;
	ret	= node->data;
	head	= node->next;

	delete node;

	return ret;
	}

#endif /* stack.h */
