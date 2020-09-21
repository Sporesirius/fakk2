//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/PlayerStart.cpp                    $
// $Revision:: 11                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/03/00 8:53p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/PlayerStart.cpp                         $
// 
// 11    7/03/00 8:53p Markd
// fixed player start bug
// 
// 10    7/02/00 6:46p Markd
// added spawn thread to PlayerStart
// 
// 9     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 8     1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 7     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 6     11/04/99 10:03a Markd
// complete overhaul of the camera system
// 
// 5     10/13/99 11:59a Phook
// 
// 4     10/13/99 11:52a Phook
// adjusted the bounding box of player starts
// 
// 3     9/28/99 9:51a Markd
// fixed default flags
// 
// 2     9/27/99 5:45p Markd
// began documentation and cleanup phase after merge
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 11    7/08/99 4:28p Markd
// Removed obsolete QUAKED functions
// 
// 10    6/17/99 1:20p Phook
// Made the player starts 96 units tall
// 
// 9     6/11/99 1:23p Phook
// 
// 8     6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
// 
// 7     6/11/99 12:46p Phook
// EClass color changes
//
// DESCRIPTION:
// Player start location entity declarations
//

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "PlayerStart.h"

/*****************************************************************************/
/*QUAKED info_player_start (0.75 0.75 0) (-16 -16 0) (16 16 96)

The normal starting point for a level.

"angle" - the direction the player should face
"thread" - the thread that should be called when spawned at this position

******************************************************************************/

Event EV_PlayerStart_SetThread
   (
   "thread",
   EV_DEFAULT,
   "s",
   "thread",
   "Set the thread to execute when this player start is used"
   );

CLASS_DECLARATION( Entity, PlayerStart, "info_player_start" )
	{
      { &EV_SetAngle,               SetAngle },
      { &EV_PlayerStart_SetThread,  SetThread },
		{ NULL, NULL }
	};

void PlayerStart::SetAngle
   (
   Event *ev
   )

   {
	angles = Vector( 0, ev->GetFloat( 1 ), 0 );
   }

void PlayerStart::SetThread
   (
   Event *ev
   )

   {
   thread = ev->GetString( 1 );
   }

str PlayerStart::getThread
   (
   void
   )

   {
   return thread;
   }

/*****************************************************************************/
/*  saved out by quaked in region mode

******************************************************************************/

CLASS_DECLARATION( PlayerStart, TestPlayerStart, "testplayerstart" )
	{
		{ NULL, NULL }
	};

/*****************************************************************************/
/*QUAKED info_player_deathmatch (0.75 0.75 1) (-16 -16 0) (16 16 96)

potential spawning position for deathmatch games

"angle" - the direction the player should face
"thread" - the thread that should be called when spawned at this position

******************************************************************************/

CLASS_DECLARATION( PlayerStart, PlayerDeathmatchStart, "info_player_deathmatch" )
	{
		{ NULL, NULL }
	};

/*****************************************************************************/
/*QUAKED info_player_intermission (0.75 0.75 0) (-16 -16 0) (16 16 96)

viewing point in between deathmatch levels

******************************************************************************/

CLASS_DECLARATION( Camera, PlayerIntermission, "info_player_intermission" )
	{
		{ NULL, NULL }
	};

PlayerIntermission::PlayerIntermission
   (
   )

   {
   currentstate.watch.watchPath = false;
   }

