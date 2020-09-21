//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/viewthing.h                       $
// $Revision:: 12                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 3:50p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/viewthing.h                            $
// 
// 12    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 11    6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 10    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 9     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 8     5/02/00 7:18p Markd
// Bullet proofed viewspawned stuff
// 
// 7     3/17/00 3:45p Markd
// made viewthing slider changes for setanim
// 
// 6     2/11/00 2:24p Markd
// Added printtime support
// 
// 5     1/13/00 11:45a Markd
// Fixed viewspawn bug with surfaces, now I save them off and then restore
// them on each animation
// 
// 4     12/17/99 8:27p Jimdose
// got rid of unused vars and functions
// 
// 3     10/02/99 6:51p Markd
// Put in backend work for event documentation and fixed a lot of event
// documentation bugs
// 
// 2     9/22/99 4:48p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 3     7/07/99 12:25p Markd
// 
// 2     6/23/99 3:57p Markd
// Added viewthing support
// 
// 1     6/23/99 11:00a Markd
// 
// 20    10/08/98 12:35a Jimdose
// Added archive functions
// 
// 19    10/04/98 11:11p Jimdose
// Made current_viewthing part of ViewMaster
// 
// 18    9/09/98 5:57p Markd
// added viewautoanimate
// 
// 17    7/10/98 6:20a Jimdose
// Added viewpitch, viewroll, and viewangles events
// 
// 16    4/08/98 12:21a Jimdose
// Added viewdeleteall command
// 
// 15    3/30/98 10:00a Markd
// Added nextskin and prevskin events
// 
// 14    3/27/98 7:00p Markd
// Added new viewthing commands
// 
// 13    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 12    3/12/98 9:49a Markd
// Added YAW event
// 
// 11    3/11/98 11:30a Markd
// Added events and variable
// 
// 10    3/07/98 2:05p Markd
// Fixed Viewthing
// 
// 9     3/05/98 6:48p Markd
// 
// 8     3/05/98 11:03a Markd
// Updated for Q2
// 
// 6     10/28/97 6:55p Markd
// made initialorigin a public variable instead of a private one.
// 
// 5     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 4     10/23/97 6:37p Markd
// Added initialorigin stuff
// 
// 3     10/01/97 6:37p Markd
// Added viewthing commands (ToggleAnimate and ChangeAnimation)
// 
// 2     10/01/97 2:47p Markd
// working on wander AI
// 
// 1     10/01/97 11:24a Markd
// new viewthing actor code
//
// DESCRIPTION:
// Actor code for the viewthing. 
//

#ifndef __VIEWTHING_H__
#define __VIEWTHING_H__

#include "animate.h"

class ViewMaster : public Listener
	{
	public:
      CLASS_PROTOTYPE( ViewMaster );

      EntityPtr current_viewthing;

           ViewMaster();
      void Init( void );
		void Next( Event *ev );
		void Prev( Event *ev );
		void DeleteAll( Event *ev );
		void Spawn( Event *ev );
		void SetModelEvent( Event *ev );
		void PassEvent( Event *ev );

      virtual void Archive( Archiver &arc );
	};

inline void ViewMaster::Archive
	(
	Archiver &arc
	)

   {
   Listener::Archive( arc );

   arc.ArchiveSafePointer( &current_viewthing );
   }

extern ViewMaster Viewmodel;

class Viewthing : public Animate
	{
	public:
      CLASS_PROTOTYPE( Viewthing );

      int      animstate;
      int      frame;
      int      lastframe;
      Vector   baseorigin;
      byte     origSurfaces[MAX_MODEL_SURFACES];

							   Viewthing();
		void					UpdateCvars( qboolean quiet = false );
		void					PrintTime( Event *ev );
		void					ThinkEvent( Event *ev );
		void					LastFrameEvent( Event *ev );
		void					ToggleAnimateEvent( Event *ev );
		void					SetModelEvent( Event *ev );
		void					NextFrameEvent( Event *ev );
		void					PrevFrameEvent( Event *ev );
		void					NextAnimEvent( Event *ev );
		void					PrevAnimEvent( Event *ev );
		void					ScaleUpEvent( Event *ev );
		void					ScaleDownEvent( Event *ev );
		void					SetScaleEvent( Event *ev );
		void					SetYawEvent( Event *ev );
		void					SetPitchEvent( Event *ev );
		void					SetRollEvent( Event *ev );
		void					SetAnglesEvent( Event *ev );
      void              AttachModel( Event *ev );
      void              Delete( Event *ev );
      void              DetachAll( Event *ev );
      void              ChangeOrigin( Event *ev );
      void              SaveSurfaces( Event *ev );
      void              SetAnim( Event *ev );

      virtual void      Archive( Archiver &arc );
	};

inline void Viewthing::Archive
	(
	Archiver &arc
	)

   {
   Animate::Archive( arc );

   arc.ArchiveInteger( &animstate );
   arc.ArchiveInteger( &frame );
   arc.ArchiveInteger( &lastframe );
   arc.ArchiveVector( &baseorigin );
   arc.ArchiveRaw( origSurfaces, sizeof( origSurfaces ) );
   }

#endif /* viewthing.h */
