//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_player.cpp                      $
// $Revision:: 13                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 6/01/00 12:21p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_player.cpp                           $
// 
// 13    6/01/00 12:21p Steven
// Improvement to splashes.
// 
// 12    5/11/00 11:08a Steven
// Added water ripple stuff.
// 
// 11    1/27/00 9:06a Markd
// Added watermark
// 
// 10    10/29/99 6:52p Jimdose
// moved torso and head angles to player.cpp
// 
// 9     10/27/99 12:18p Markd
// added smooth camera lerping
// 
// 8     10/25/99 12:20p Jimdose
// made head and torso angles local to each entity
// 
// 7     10/19/99 7:52p Markd
// Removed three part model system
// 
// 6     10/14/99 4:52p Jimdose
// added head_angles and torso_angles to refdef_t
// 
// 5     10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION:
// Player functions for the cgame 

#include "cg_local.h"
#include "cg_commands.h"

/*

player entities generate a great deal of information from implicit ques
taken from the entityState_t

*/

//=====================================================================

/*
===============
CG_ResetPlayerEntity

A player just came into view or teleported, so reset all animation info
===============
*/
void CG_ResetPlayerEntity( centity_t *cent )
   {
	cent->errorTime = -99999;		// guarantee no error decay added
	cent->extrapolated = qfalse;

	VectorCopy( cent->currentState.origin, cent->lerpOrigin );
	VectorCopy( cent->lerpOrigin, cent->rawOrigin );

	VectorCopy( cent->currentState.angles, cent->lerpAngles );
	VectorCopy( cent->lerpAngles, cent->rawAngles );

	if ( cent->currentState.number == cg.snap->ps.clientNum ) 
      {
      // initialize the camera position
      VectorCopy( cent->lerpOrigin, cg.currentViewPos );
      // initialize the camera angles
      VectorCopy( cent->lerpAngles, cg.currentViewAngles );
      // setup the lastCameraTime
      cg.lastCameraTime = -1;
      // setup the lerpCameraTime
      cg.lerpCameraTime = 0;
      // clear the cameraView flag
      cg.inCameraView = qfalse;
      }

	// Reset splash info
	cent->splash_still_count = 0;
   }

/*
===============
CG_Player
===============
*/
void CG_Player( centity_t *cent )
   {
   //CG_PlayerSplash( cent );
   }
