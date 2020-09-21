//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/mover.h                            $
// $Revision:: 6                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 2:17p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/mover.h                                 $
// 
// 6     6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 5     5/30/00 7:06p Markd
// saved games 4th pass
// 
// 4     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 3     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 2     10/01/99 2:42p Markd
// moved all the binding code back into Entity from Mover
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// DESCRIPTION:
// Base class for any object that needs to move to specific locations over a
// period of time.  This class is kept separate from most entities to keep
// class size down for objects that don't need such behavior.
// 

#ifndef __MOVER_H__
#define __MOVER_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"

class Mover : public Trigger
	{		
	private:
      Vector				finaldest;
		Vector				angledest;
		Event					*endevent;
		int					moveflags;

	public:
		CLASS_PROTOTYPE( Mover );

								Mover();
		virtual				~Mover();
		void					MoveDone( Event *ev );
		void					MoveTo( Vector tdest, Vector angdest, float tspeed, Event &event );
		void					LinearInterpolate( Vector tdest, Vector angdest, float time, Event &event );
	   virtual void      Archive( Archiver &arc );
   };

inline void Mover::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.ArchiveVector( &finaldest );
   arc.ArchiveVector( &angledest );
   arc.ArchiveEventPointer( &endevent );
   arc.ArchiveInteger( &moveflags );
   }

#endif
