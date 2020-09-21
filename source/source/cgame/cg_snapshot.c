//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_snapshot.c                      $
// $Revision:: 37                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/19/00 9:52p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_snapshot.c                           $
// 
// 37    7/19/00 9:52p Aldie
// Put ET_EVENTS back in.  They will get sent over once, and should get
// processed once on the client.
// 
// 36    6/17/00 1:54p Markd
// Added server restarted code
// 
// 35    6/15/00 8:21p Markd
// Added CleanupCommandManager support
// 
// 34    6/15/00 7:58p Markd
// added same map restarting support
// 
// 33    6/01/00 7:45p Aldie
// Made it so that swipes are removed when client entities are reset.
// 
// 32    6/01/00 12:21p Steven
// Improvement to splashes.
// 
// 31    5/20/00 5:14p Markd
// Added ITEM special effects
// 
// 30    5/04/00 9:45a Markd
// added check for different modelindex's
// 
// 29    4/20/00 3:35p Steven
// Reset the teleport flag back to false in CG_ResetEntity.
// 
// 28    4/03/00 4:43p Markd
// fixed a teleportation issue
// 
// 27    3/24/00 1:05p Aldie
// Added flag clearing to CG_ResetEntity
// 
// 26    3/02/00 10:35a Steven
// Changed reverb interface.
// 
// 25    2/07/00 10:10a Markd
// fixed bug with interpolating attached and non-attached entites
// 
// 24    1/24/00 6:43p Steven
// Added reverb stuff.
// 
// 23    1/15/00 2:39p Aldie
// Changed definition of RemoveClientEntity
// 
// 22    1/12/00 8:02p Markd
// nextFrameCameraCut gets set based on whether or not there is a camera cut in
// the following frame
// 
// 21    12/13/99 3:31p Aldie
// Commented out some Carmack code to make fakk work
// 
// 20    12/13/99 10:46a Markd
// incremental merge fix
// 
// 19    12/11/99 5:51p Markd
// First wave of bug fixes after q3a gold merge
// 
// 18    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 17    11/11/99 11:35a Jimdose
// first pass at torso animation blending in
// 
// 16    11/10/99 2:18p Jimdose
// removed some unused variables from centity_t
// working on torso animation
// 
// 15    11/03/99 4:59p Steven
// Included music stuff in initial snapshot.
// 
// 14    10/29/99 7:24p Steven
// Moved sound stuff into snapshot.
// 
// 13    10/21/99 6:19p Markd
// removed torso and head members from entity_state
// 
// 12    10/19/99 7:52p Markd
// Removed three part model system
// 
// 11    10/12/99 2:23p Markd
// Rewrote camera and player movetype system
// 
// 10    10/08/99 7:36p Markd
// Added ET_PLAYER check for ET_MODELANIM
// 
// 9     10/06/99 7:25p Markd
// removed TIMESTAMP, time and fixed make_static bug
// 
// 8     10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION:
// things that happen on snapshot transition, not necessarily every 
// single frame

#include "cg_local.h"

/*
==================
CG_ResetEntity
==================
*/
static void CG_ResetEntity( centity_t *cent ) {

	VectorCopy (cent->currentState.origin, cent->lerpOrigin);

	VectorCopy (cent->currentState.angles, cent->lerpAngles);

   // if we just teleported, all we care about is the position and orientation information
   if ( cent->teleported )
      {
		cent->teleported = qfalse;
      return;
      }

   // reset local color
   cent->client_color[ 0 ] = 1;
   cent->client_color[ 1 ] = 1;
   cent->client_color[ 2 ] = 1;
   cent->client_color[ 3 ] = 1;

	// Make sure entity starts with no loop sound
	cent->tikiLoopSound = 0;
   
   // Reset client flags
   cent->clientFlags = 0;

	// Reset splash info
	cent->splash_last_spawn_time = 0;
	cent->splash_still_count     = -1;

   // reset client command 
   CG_RemoveClientEntity( cent->currentState.number, cgs.model_tiki[ cent->currentState.modelindex ], cent );

   // reset the animation for the entities
	if ( cent->currentState.eType < ET_GENERAL )
      {
      CG_ClearModelAnimation( cgs.model_tiki[ cent->currentState.modelindex ], 
                              &cent->am, cent->currentState.anim,
                              cg.snap->serverTime,
                              cent->lerpOrigin,
                              cent->currentState.number
                            );
      CG_ClearModelAnimation( cgs.model_tiki[ cent->currentState.modelindex ],
                              &cent->torso_am, cent->currentState.torso_anim,
                              cg.snap->serverTime,
                              cent->lerpOrigin,
                              cent->currentState.number
                            );
      }

	if ( cent->currentState.eType == ET_PLAYER ) {
		CG_ResetPlayerEntity( cent );
	}
}

/*
===============
CG_TransitionEntity

cent->nextState is moved to cent->currentState and events are fired
===============
*/
static void CG_TransitionEntity( centity_t *cent )
   {
	cent->currentState = cent->nextState;
	cent->currentValid = qtrue;

	// reset if the entity wasn't in the last frame or was teleported
	if ( !cent->interpolate ) {
		CG_ResetEntity( cent );
	}

	// clear the next state.  if will be set by the next CG_SetNextSnap
	cent->interpolate = qfalse;
   // reset the teleported state
   cent->teleported = qfalse;

   if ( cent->currentState.eType == ET_EVENTS )
      {
      CG_Event( cent );
      }
   }


/*
==================
CG_SetInitialSnapshot

This will only happen on the very first snapshot, or
on tourney restarts.  All other times will use 
CG_TransitionSnapshot instead.
==================
*/
void CG_SetInitialSnapshot( snapshot_t *snap ) {
	int				i;
	centity_t		*cent;
	entityState_t	*state;

	cg.snap = snap;

	// sort out solid entities
	CG_BuildSolidList();

	CG_ExecuteNewServerCommands( snap->serverCommandSequence );

	for ( i = 0 ; i < cg.snap->numEntities ; i++ ) {
		state = &cg.snap->entities[ i ];
		cent = &cg_entities[ state->number ];

		cent->currentState = *state;
		cent->interpolate = qfalse;
		cent->currentValid = qtrue;

		CG_ResetEntity( cent );
	}

	cgi.MUSIC_UpdateMood( snap->ps.current_music_mood, snap->ps.fallback_music_mood );
	cgi.MUSIC_UpdateVolume( snap->ps.music_volume, snap->ps.music_volume_fade_time );
	cgi.S_SetReverb( snap->ps.reverb_type, snap->ps.reverb_level );
}


/*
===================
CG_TransitionSnapshot

The transition point from snap to nextSnap has passed
===================
*/
static void CG_TransitionSnapshot( void ) {
	centity_t			*cent;
	snapshot_t			*oldFrame;
   qboolean          differentServer;
	int					i;


	if ( !cg.snap ) {
		cgi.Error( ERR_DROP, "CG_TransitionSnapshot: NULL cg.snap" );
	}
	if ( !cg.nextSnap ) {
		cgi.Error( ERR_DROP, "CG_TransitionSnapshot: NULL cg.nextSnap" );
	}

	// execute any server string commands before transitioning entities
	CG_ExecuteNewServerCommands( cg.nextSnap->serverCommandSequence );

	// clear the currentValid flag for all entities in the existing snapshot
	for ( i = 0 ; i < cg.snap->numEntities ; i++ ) {
		cent = &cg_entities[ cg.snap->entities[ i ].number ];
   	cent->currentValid = qfalse;
      }	

	// move nextSnap to snap and do the transitions
	oldFrame = cg.snap;
	cg.snap = cg.nextSnap;

   // if restarted, teleport and no camera lerp
   if ( ( oldFrame->snapFlags ^ cg.snap->snapFlags ) & SNAPFLAG_SERVERCOUNT )
      {
      CG_ServerRestarted();
      differentServer = qtrue;
      }
   else
      {
      differentServer = qfalse;
      }

	//FAKK: Commented out to make our stuff work 
   //cg_entities[ cg.snap->ps.clientNum ].interpolate = qfalse;

	for ( i = 0 ; i < cg.snap->numEntities ; i++ ) {
		cent = &cg_entities[ cg.snap->entities[ i ].number ];
      if ( differentServer ) 
         {
         cent->interpolate = qfalse;
         cent->teleported = qfalse;
         }
		CG_TransitionEntity( cent );
	}

	for ( i = 0 ; i < cg.snap->number_of_sounds ; i++ ) 
		{
		CG_ProcessSound( &cg.snap->sounds[ i ] );	
		}

	cg.nextSnap = NULL;

	// check for playerstate transition events

	if ( oldFrame ) 
      {
		playerState_t	*ops, *ps;

		ops = &oldFrame->ps;
		ps = &cg.snap->ps;

		// teleporting checks are irrespective of prediction
		if ( ps->pm_flags & PMF_TIME_TELEPORT ) {
			cg.thisFrameTeleport = qtrue;
		}

		if ( ( ops->current_music_mood != ps->current_music_mood ) || ( ops->fallback_music_mood != ps->fallback_music_mood ) )
			cgi.MUSIC_UpdateMood( ps->current_music_mood, ps->fallback_music_mood );

		if ( ( ops->music_volume != ps->music_volume ) || ( ops->music_volume_fade_time != ps->music_volume_fade_time ) )
			cgi.MUSIC_UpdateVolume( ps->music_volume, ps->music_volume_fade_time );

		if ( ( ops->reverb_type != ps->reverb_type ) || ( ops->reverb_level != ps->reverb_level ) )
			cgi.S_SetReverb( ps->reverb_type, ps->reverb_level );

		// if we are not doing client side movement prediction for any
		// reason, then the client events and view changes will be issued now
		if 
         ( 
         cg.demoPlayback || 
         ( cg.snap->ps.pm_flags & PMF_NO_PREDICTION ) || 
         cg_nopredict->integer || 
         cg_syncronousClients->integer 
         ) 
         {
			CG_TransitionPlayerState( ps, ops );
		   }
	   }
}


/*
===================
CG_SetNextSnap

A new snapshot has just been read in from the client system.
===================
*/
static void CG_SetNextSnap( snapshot_t *snap ) {
	int					num;
	entityState_t		*es;
	centity_t			*cent;

	cg.nextSnap = snap;

	cg_entities[ cg.snap->ps.clientNum ].interpolate = qtrue;

	// check for extrapolation errors
	for ( num = 0 ; num < snap->numEntities ; num++ ) {
		es = &snap->entities[num];
		cent = &cg_entities[ es->number ];

		cent->nextState = *es;

		// if this frame is a teleport, or the entity wasn't in the
		// previous frame, don't interpolate
		if ( 
            !cent->currentValid || 
            ( ( cent->currentState.eFlags ^ es->eFlags ) & EF_TELEPORT_BIT )  ||
            ( cent->currentState.parent != es->parent ) ||
            ( cent->currentState.modelindex != es->modelindex )
         ) {
			cent->interpolate = qfalse;
         // if this isn't the first frame and we have valid data, set the teleport flag
         if ( cent->currentValid )
            {
            cent->teleported = qtrue;
            }
		} else {
			cent->interpolate = qtrue;
		}
	}

	// if the next frame is a teleport for the playerstate, we
	// can't interpolate during demos
	if ( cg.snap && ( snap->ps.pm_flags & PMF_TIME_TELEPORT ) ) {
		cg.nextFrameTeleport = qtrue;
	} else {
		cg.nextFrameTeleport = qfalse;
	}

	// if changing follow mode, don't interpolate
	if ( cg.nextSnap->ps.clientNum != cg.snap->ps.clientNum ) {
		cg.nextFrameTeleport = qtrue;
	}

	// if the camera cut bit changed, than the next frame is a camera cut
	if ( 
         ( cg.nextSnap->ps.camera_flags & CF_CAMERA_CUT_BIT ) != 
         ( cg.snap->ps.camera_flags & CF_CAMERA_CUT_BIT ) 
      ) {
		cg.nextFrameCameraCut = qtrue;
	} else {
      cg.nextFrameCameraCut = qfalse;
   }

	// if changing server restarts, don't interpolate
	if ( ( cg.nextSnap->snapFlags ^ cg.snap->snapFlags ) & SNAPFLAG_SERVERCOUNT ) {
      // reset the camera
      cg.lastCameraTime = -1;
		cg.nextFrameTeleport = qtrue;
	}



	// sort out solid entities
	CG_BuildSolidList();
}


/*
========================
CG_ReadNextSnapshot

This is the only place new snapshots are requested
This may increment cgs.processedSnapshotNum multiple
times if the client system fails to return a
valid snapshot.
========================
*/
static snapshot_t *CG_ReadNextSnapshot( void ) {
	qboolean	r;
	snapshot_t	*dest;

	if ( cg.latestSnapshotNum > cgs.processedSnapshotNum + 1000 ) {
		cgi.Error( ERR_DROP, "CG_ReadNextSnapshot: way out of range, %i > %i", 
			cg.latestSnapshotNum, cgs.processedSnapshotNum );
	}

	while ( cgs.processedSnapshotNum < cg.latestSnapshotNum ) {
		// decide which of the two slots to load it into
		if ( cg.snap == &cg.activeSnapshots[0] ) {
			dest = &cg.activeSnapshots[1];
		} else {
			dest = &cg.activeSnapshots[0];
		}

		// try to read the snapshot from the client system
		cgs.processedSnapshotNum++;
		r = cgi.GetSnapshot( cgs.processedSnapshotNum, dest );

		// if it succeeded, return
		if ( r ) {
			CG_AddLagometerSnapshotInfo( dest );
			return dest;
		}

		// a GetSnapshot will return failure if the snapshot
		// never arrived, or  is so old that its entities
		// have been shoved off the end of the circular
		// buffer in the client system.

		// record as a dropped packet
		CG_AddLagometerSnapshotInfo( NULL );

		// If there are additional snapshots, continue trying to
		// read them.
	}

	// nothing left to read
	return NULL;
}

/*
============
CG_ProcessSnapshots

We are trying to set up a renderable view, so determine
what the simulated time is, and try to get snapshots
both before and after that time if available.

If we don't have a valid cg.snap after exiting this function,
then a 3D game view cannot be rendered.  This should only happen
right after the initial connection.  After cg.snap has been valid
once, it will never turn invalid.

Even if cg.snap is valid, cg.nextSnap may not be, if the snapshot
hasn't arrived yet (it becomes an extrapolating situation instead
of an interpolating one)

============
*/
void CG_ProcessSnapshots( void ) {
	snapshot_t		*snap;
	int				n;

	// see what the latest snapshot the client system has is
	cgi.GetCurrentSnapshotNumber( &n, &cg.latestSnapshotTime );
	if ( n != cg.latestSnapshotNum ) {
		if ( n < cg.latestSnapshotNum ) {
			// this should never happen
			cgi.Error( ERR_DROP, "CG_ProcessSnapshots: n < cg.latestSnapshotNum" );
		}
		cg.latestSnapshotNum = n;
	}

	// If we have yet to receive a snapshot, check for it.
	// Once we have gotten the first snapshot, cg.snap will
	// always have valid data for the rest of the game
	while ( !cg.snap ) {
		snap = CG_ReadNextSnapshot();
		if ( !snap ) {
			// we can't continue until we get a snapshot
			return;
		}

		// set our weapon selection to what
		// the playerstate is currently using
		if ( !( snap->snapFlags & SNAPFLAG_NOT_ACTIVE ) ) {
			CG_SetInitialSnapshot( snap );
		}
	}

	// loop until we either have a valid nextSnap with a serverTime
	// greater than cg.time to interpolate towards, or we run
	// out of available snapshots
	do {
		// if we don't have a nextframe, try and read a new one in
		if ( !cg.nextSnap ) {
			snap = CG_ReadNextSnapshot();

			// if we still don't have a nextframe, we will just have to
			// extrapolate
			if ( !snap ) {
				break;
			}

			CG_SetNextSnap( snap );

			// if time went backwards, we have a level restart
			if ( cg.nextSnap->serverTime < cg.snap->serverTime ) {
            // only drop if this is not a restart or loadgame
   	      if ( !( ( cg.nextSnap->snapFlags ^ cg.snap->snapFlags ) & SNAPFLAG_SERVERCOUNT ) ) {
   				cgi.Error( ERR_DROP, "CG_ProcessSnapshots: Server time went backwards" );
            }
			}
		}

		// if our time is < nextFrame's, we have a nice interpolating state
		if ( cg.time >= cg.snap->serverTime && cg.time < cg.nextSnap->serverTime ) {
			break;
		}

		// we have passed the transition from nextFrame to frame
		CG_TransitionSnapshot();
	} while ( 1 );

	// assert our valid conditions upon exiting
	if ( cg.snap == NULL ) {
	   cgi.Error( ERR_DROP, "CG_ProcessSnapshots: cg.snap == NULL" );
	}
	if ( cg.time < cg.snap->serverTime ) {
		// this can happen right after a vid_restart
		cg.time = cg.snap->serverTime;
	}
	if ( cg.nextSnap != NULL && cg.nextSnap->serverTime <= cg.time ) {
		cgi.Error( ERR_DROP, "CG_ProcessSnapshots: cg.nextSnap->serverTime <= cg.time" );
	}
}

