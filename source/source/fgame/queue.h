//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/queue.h                            $
// $Revision:: 3                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 7/25/00 11:32p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/queue.h                                 $
// 
// 3     7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 2     6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
//
// DESCRIPTION:
// Generic Queue object
//

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "class.h"

class QueueNode : public Class
	{
	public:
		void		 *data;
		QueueNode *next;

		QueueNode();
	};

inline QueueNode::QueueNode()
	{
	data = NULL;
	next = NULL;
	}

class Queue : public Class
	{
	private:
		QueueNode *head;
		QueueNode *tail;

	public:
					Queue();
					~Queue();
		void		Clear( void	);
		qboolean Empty( void );
		void		Enqueue( void *data );
		void		*Dequeue( void );
      void     Remove( void *data );
      qboolean Inqueue( void *data );
	};

inline qboolean Queue::Empty
	(
	void
	)

	{
	if ( head == NULL )
		{
		assert( !tail );
		return true;
		}

	assert( tail );
	return false;
	}

inline void Queue::Enqueue
	(
	void *data
	)

	{
	QueueNode *tmp;

	tmp = new QueueNode;
	if ( !tmp )
		{
		assert( NULL );
		gi.Error( ERR_DROP, "Queue::Enqueue : Out of memory" );
		}

	tmp->data = data;

	assert( !tmp->next );
	if ( !head )
		{
		assert( !tail );
		head = tmp;
		}
	else
		{
		assert( tail );
		tail->next = tmp;
		}
	tail = tmp;
	}

inline void *Queue::Dequeue
	(
	void
	)

	{
	void *ptr;
	QueueNode *node;

	if ( !head )
		{
		assert( !tail );
		return NULL;
		}

	node = head;
	ptr = node->data;

	head = node->next;
	if ( head == NULL )
		{
		assert( tail == node );
		tail = NULL;
		}

	delete node;

	return ptr;
	}

inline void Queue::Clear
	(
	void
	)

	{
	while( !Empty() )
		{
		Dequeue();
		}
	}

inline Queue::Queue()
	{
	head = NULL;
	tail = NULL;
	}

inline Queue::~Queue()
	{
	Clear();
	}

inline void Queue::Remove
   (
   void *data
   )

   {
	QueueNode *node;
	QueueNode *prev;

	if ( !head )
		{
		assert( !tail );

      gi.DPrintf( "Queue::Remove : Data not found in queue\n" );
		return;
		}

   for( prev = NULL, node = head; node != NULL; prev = node, node = node->next )
      {
      if ( node->data == data )
         {
         break;
         }
      }

   if ( !node )
      {
      gi.DPrintf( "Queue::Remove : Data not found in queue\n" );
      }
   else
      {
      if ( !prev )
         {
         // at head
         assert( node == head );
         head = node->next;
	      if ( head == NULL )
		      {
		      assert( tail == node );
		      tail = NULL;
		      }
         }
      else
         {
         prev->next = node->next;
         if ( prev->next == NULL )
            {
            // at tail
            assert( tail == node );
            tail = prev;
            }
         }

	   delete node;
      }
   }

inline qboolean Queue::Inqueue
   (
   void *data
   )

   {
	QueueNode *node;

   for( node = head; node != NULL; node = node->next )
      {
      if ( node->data == data )
         {
         return true;
         }
      }

   return false;
   }

#endif /* queue.h */
