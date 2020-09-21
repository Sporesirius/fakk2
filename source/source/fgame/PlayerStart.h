//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/PlayerStart.h                      $
// $Revision:: 3                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 7/02/00 6:46p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/PlayerStart.h                           $
// 
// 3     7/02/00 6:46p Markd
// added spawn thread to PlayerStart
// 
// 2     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 6     7/08/99 4:28p Markd
// Removed obsolete QUAKED functions
// 
// DESCRIPTION:
// Player start location entity declarations
// 

#ifndef __PLAYERSTART_H__
#define __PLAYERSTART_H__

#include "g_local.h"
#include "entity.h"
#include "camera.h"
#include "navigate.h"

class PlayerStart : public Entity
	{
   private:
      str            thread;
	public:
      CLASS_PROTOTYPE( PlayerStart );
		
		void           SetAngle( Event *ev );
      void           SetThread( Event *ev );
      str            getThread( void );
	   virtual void   Archive(Archiver &arc);
	};

inline void PlayerStart::Archive (Archiver &arc)
   {
	Entity::Archive( arc );

	arc.ArchiveString(&thread);
   }

class TestPlayerStart : public PlayerStart
	{
	public:
		CLASS_PROTOTYPE( TestPlayerStart );
	};

class PlayerDeathmatchStart : public PlayerStart
	{
	public:
		CLASS_PROTOTYPE( PlayerDeathmatchStart );
	};

class PlayerIntermission : public Camera
	{
	public:
		CLASS_PROTOTYPE( PlayerIntermission );
      PlayerIntermission();
	};

#endif /* PlayerStart.h */
