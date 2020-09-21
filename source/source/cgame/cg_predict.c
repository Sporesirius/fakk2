//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_predict.c                       $
// $Revision:: 33                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/10/00 11:54p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_predict.c                            $
// 
// 33    7/10/00 11:54p Markd
// added exit level code
// 
// 32    6/25/00 11:21a Markd
// fixed slime code for player
// 
// 31    6/14/00 12:14p Markd
// more intel compiler bug fixes
// 
// 30    6/08/00 9:14p Markd
// improved player prediction model
// 
// 29    6/03/00 10:55a Markd
// Sped up tracing and debug print messages
// 
// 28    5/16/00 6:24p Markd
// added cg_traceinfo support
// 
// 27    5/16/00 4:25p Steven
// Made entities use CONTENTS_BODY instead of CONTENTS_BODY and CONTENTS_SOLID.
// 
// 26    5/11/00 11:08a Steven
// Made sure trypush is NULL on client side.
// 
// 25    4/28/00 3:30p Steven
// If a trace started in a solid made sure the world is set as the entitynum
// 
// 24    4/21/00 9:30a Markd
// fixed camera fov problems
// 
// 23    4/20/00 5:38p Markd
// fixed fov lerping bug, I introduced yesterday
// 
// 22    4/19/00 2:38p Markd
// fixed lerping bug
// 
// 21    3/31/00 11:49a Markd
// Added contents support to TempBbox models
// 
// 20    2/15/00 8:47p Jimdose
// fixed animation frames and delta sync problem
// 
// 19    2/01/00 11:25a Markd
// Fixed up camera cutting so that there are no more false origin issues
// 
// 18    1/27/00 11:35a Markd
// Fixed solid/notsolid client side entities
// 
// 17    1/12/00 8:01p Markd
// Added nextFrameCameraCut variable for cameras
// 
// 16    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 15    11/29/99 6:32p Aldie
// Lots of changes for ammo system
// 
// 14    11/05/99 11:18a Aldie
// Fixed fov bug with Mark
// 
// 13    11/04/99 3:18p Markd
// fixed fov lerping
// 
// 12    11/04/99 10:03a Markd
// complete overhaul of the camera system
// 
// 11    10/27/99 4:31p Markd
// Fixed all camera prediction and smmoth lerping issues
// 
// 10    10/12/99 6:56p Markd
// Fixed some player interpolation bugs and also interpolated camera
// 
// 9     10/12/99 2:23p Markd
// Rewrote camera and player movetype system
// 
// 8     10/08/99 2:10p Markd
// Added PM_LOCKVIEW for when playerstate should just be predicted
// 
// 7     10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION:
// this file generates cg.predicted_player_state by either
// interpolating between snapshots from the server or locally predicting
// ahead the client's movement. It also handles local physics interaction,
// like fragments bouncing off walls

#include "cg_local.h"

static	pmove_t		cg_pmove;

static	int			cg_numSolidEntities;
static	centity_t	*cg_solidEntities[MAX_ENTITIES_IN_SNAPSHOT];
static	int			cg_numTriggerEntities;
//static	centity_t	*cg_triggerEntities[MAX_ENTITIES_IN_SNAPSHOT];

/*
====================
CG_BuildSolidList

When a new cg.snap has been set, this function builds a sublist
of the entities that are actually solid, to make for more
efficient collision detection
====================
*/
void CG_BuildSolidList( void )
   {
	int			i;
	centity_t	*cent;
	snapshot_t	*snap;
	entityState_t	*ent;

	cg_numSolidEntities = 0;
	cg_numTriggerEntities = 0;

	if ( cg.nextSnap && !cg.nextFrameTeleport && !cg.thisFrameTeleport )
      {
		snap = cg.nextSnap;
	   } 
   else
      {
		snap = cg.snap;
	   }

	for ( i = 0 ; i < snap->numEntities ; i++ )
      {
		cent = &cg_entities[ snap->entities[ i ].number ];
		ent = &cent->currentState;

		if ( ent->eType == ET_ITEM || ent->eType == ET_PUSH_TRIGGER || ent->eType == ET_TELEPORT_TRIGGER )
         {
         /*
			cg_triggerEntities[cg_numTriggerEntities] = cent;
			cg_numTriggerEntities++;
         */
			continue;
	   	}

		if ( cent->nextState.solid )
         {
			cg_solidEntities[cg_numSolidEntities] = cent;
			cg_numSolidEntities++;
			continue;
		   }
	   }
   }

/*
====================
CG_ClipMoveToEntities

====================
*/
static void CG_ClipMoveToEntities
   ( 
   const vec3_t   start,
   const vec3_t   mins,
   const vec3_t   maxs,
   const vec3_t   end,
   int            skipNumber,
   int            mask,
   trace_t        *tr,
   qboolean       cylinder
   )
   
   {
	int			   i;
	trace_t		   trace;
	entityState_t	*ent;
	clipHandle_t   cmodel;
	vec3_t		   bmins, bmaxs;
	vec3_t		   origin, angles;
	centity_t	   *cent;

	for ( i = 0 ; i < cg_numSolidEntities ; i++)
      {
		cent = cg_solidEntities[ i ];
		ent = &cent->currentState;

		if ( ent->number == skipNumber )
			continue;
	
		if ( ent->solid == SOLID_BMODEL ) 
         {
			// special value for bmodel
			cmodel = cgi.CM_InlineModel( ent->modelindex );
			if ( !cmodel ) 
         	continue;
			VectorCopy( cent->lerpAngles, angles );
			VectorCopy( cent->lerpOrigin, origin );
         }
      else 
         {
         IntegerToBoundingBox( ent->solid, bmins, bmaxs );
			cmodel = cgi.CM_TempBoxModel( bmins, bmaxs, CONTENTS_BODY ); //CONTENTS_SOLID | CONTENTS_BODY );
			VectorCopy( vec3_origin, angles );
			VectorCopy( cent->lerpOrigin, origin );
		   }

		cgi.CM_TransformedBoxTrace( &trace, start, end, mins, maxs, cmodel, mask, origin, angles, cylinder );

		if (trace.allsolid || trace.fraction < tr->fraction) 
         {
			trace.entityNum = ent->number;
			*tr = trace;
		   }
      else if (trace.startsolid)
         {
			tr->startsolid = qtrue;
		   }
	   }
   }

void CG_ShowTrace
	(
	trace_t *trace,
   int passent,
	const char *reason
	)

	{
   char text[ 1024 ];

	assert( reason );
	assert( trace );

	sprintf( text, "%0.2f : Pass (%d) Frac %f Hit (%d): '%s'\n", 
		( float )cg.time / 1000.0f, passent, trace->fraction, trace->entityNum, reason ? reason : "" );

   if ( cg_traceinfo->integer == 3 )
		{
		cgi.DebugPrintf( text );
		}
	else
		{
      cgi.DPrintf( text );
		}
	}

/*
================
CG_Trace
================
*/
void CG_Trace
   ( 
   trace_t *result,
   const vec3_t start,
   const vec3_t mins,
   const vec3_t maxs,
   const vec3_t end, 
   int skipNumber,
   int mask,
   qboolean cylinder,
   qboolean cliptoentities,
   const char * description
   )
   
   {
   trace_t	t;

	cgi.CM_BoxTrace ( &t, start, end, mins, maxs, 0, mask, cylinder );
	t.entityNum = t.fraction != 1.0 ? ENTITYNUM_WORLD : ENTITYNUM_NONE;

	// If starting in a solid make sure the world is set as the entitynum

	if ( t.startsolid )
		t.entityNum = ENTITYNUM_WORLD;

   if ( cliptoentities )
      {
	   // check all other solid models
	   CG_ClipMoveToEntities(start, mins, maxs, end, skipNumber, mask, &t, cylinder );
      }

	*result = t;

   if ( cg_traceinfo->integer )
      {
      CG_ShowTrace( result, skipNumber, description );
      }
   }

/*
================
CG_PlayerTrace
================
*/
void CG_PlayerTrace
   ( 
   trace_t *result,
   const vec3_t start,
   const vec3_t mins,
   const vec3_t maxs,
   const vec3_t end, 
   int skipNumber,
   int mask,
   qboolean cylinder
   )
   
   {
   CG_Trace( result, start, mins, maxs, end, skipNumber, mask, cylinder, qtrue, "PlayerTrace" );
   }

/*
================
CG_PointContents
================
*/
int		CG_PointContents( const vec3_t point, int passEntityNum ) {
	int			i;
	entityState_t	*ent;
	centity_t	*cent;
	clipHandle_t cmodel;
	int			contents;

	contents = cgi.CM_PointContents (point, 0);

	for ( i = 0 ; i < cg_numSolidEntities ; i++ ) {
		cent = cg_solidEntities[ i ];

		ent = &cent->currentState;

		if ( ent->number == passEntityNum ) {
			continue;
		}

		if (ent->solid != SOLID_BMODEL) { // special value for bmodel
			continue;
		}

		cmodel = cgi.CM_InlineModel( ent->modelindex );
		if ( !cmodel ) {
			continue;
		}

		contents |= cgi.CM_TransformedPointContents( point, cmodel, ent->origin, ent->angles );
	}

	return contents;
}


/*
========================
CG_InterpolatePlayerStateCamera

Generates cg.predicted_player_state by interpolating between
cg.snap->player_state and cg.nextFrame->player_state
========================
*/
static void CG_InterpolatePlayerStateCamera( void ) 
   {
	float			f;
	int				i;
	snapshot_t		*prev, *next;

	prev = cg.snap;
	next = cg.nextSnap;

   //
   // copy in the current ones if nothing else
   //
   VectorCopy( cg.predicted_player_state.camera_angles, cg.camera_angles );
   VectorCopy( cg.predicted_player_state.camera_origin, cg.camera_origin );
  	cg.camera_fov = cg.predicted_player_state.fov;

	// if the next frame is a teleport, we can't lerp to it
	if ( cg.nextFrameCameraCut ) 
      {
		return;
	   }

	if ( 
         !next || 
         next->serverTime <= prev->serverTime 
      ) 
      {
		return;
	   }

	f = (float)( cg.time - prev->serverTime ) / ( next->serverTime - prev->serverTime );

   // interpolate fov
	cg.camera_fov = prev->ps.fov + f * ( next->ps.fov - prev->ps.fov );

   if ( !( cg.snap->ps.pm_flags & PMF_CAMERA_VIEW ) )
      {
      return;
      }

	for ( i = 0 ; i < 3 ; i++ ) 
      {
		cg.camera_origin[i] = prev->ps.camera_origin[i] + f * (next->ps.camera_origin[i] - prev->ps.camera_origin[i] );
		cg.camera_angles[i] = LerpAngle( prev->ps.camera_angles[i], next->ps.camera_angles[i], f );
		}
	}

/*
========================
CG_InterpolatePlayerState

Generates cg.predicted_player_state by interpolating between
cg.snap->player_state and cg.nextFrame->player_state
========================
*/
static void CG_InterpolatePlayerState( qboolean grabAngles ) {
	float			f;
	int				i;
	playerState_t	*out;
	snapshot_t		*prev, *next;

	out = &cg.predicted_player_state;
	prev = cg.snap;
	next = cg.nextSnap;

	*out = cg.snap->ps;

   // interpolate the camera if necessary
   CG_InterpolatePlayerStateCamera();

	// if we are still allowing local input, short circuit the view angles
	if ( grabAngles ) {
		usercmd_t	cmd;
		int			cmdNum;

		cmdNum = cgi.GetCurrentCmdNumber();
		cgi.GetUserCmd( cmdNum, &cmd );

		PM_UpdateViewAngles( out, &cmd );
	}

	// if the next frame is a teleport, we can't lerp to it
	if ( cg.nextFrameTeleport ) {
		return;
	}

	if ( !next || next->serverTime <= prev->serverTime ) {
		return;
	}

   f = cg.frameInterpolation;

	i = next->ps.bobCycle;
	if ( i < prev->ps.bobCycle ) {
		i += 256;		// handle wraparound
	}
	out->bobCycle = prev->ps.bobCycle + f * ( i - prev->ps.bobCycle );

	for ( i = 0 ; i < 3 ; i++ ) {
		out->origin[i] = prev->ps.origin[i] + f * (next->ps.origin[i] - prev->ps.origin[i] );
		if ( !grabAngles ) {
			out->viewangles[i] = LerpAngle( 
				prev->ps.viewangles[i], next->ps.viewangles[i], f );
		}
		out->velocity[i] = prev->ps.velocity[i] + 
			f * (next->ps.velocity[i] - prev->ps.velocity[i] );
	}

}

/*
=================
CG_PredictPlayerState

Generates cg.predicted_player_state for the current cg.time
cg.predicted_player_state is guaranteed to be valid after exiting.

For demo playback, this will be an interpolation between two valid
playerState_t.

For normal gameplay, it will be the result of predicted usercmd_t on
top of the most recent playerState_t received from the server.

Each new snapshot will usually have one or more new usercmd over the last,
but we simulate all unacknowledged commands each time, not just the new ones.
This means that on an internet connection, quite a few pmoves may be issued
each frame.

OPTIMIZE: don't re-simulate unless the newly arrived snapshot playerState_t
differs from the predicted one.  Would require saving all intermediate
playerState_t during prediction.

We detect prediction errors and allow them to be decayed off over several frames
to ease the jerk.
=================
*/
void CG_PredictPlayerState( void ) {
	int			   cmdNum, current;
	playerState_t	oldPlayerState;
	qboolean	      moved;
	usercmd_t	   oldestCmd;
	usercmd_t	   latestCmd;

	cg.hyperspace = qfalse;	// will be set if touching a trigger_teleport

	// if this is the first frame we must guarantee
	// predicted_player_state is valid even if there is some
	// other error condition
	if ( !cg.validPPS ) {
		cg.validPPS = qtrue;
		cg.predicted_player_state = cg.snap->ps;
	}

	// demo playback just copies the moves
	if ( 
         cg.demoPlayback || 
         ( cg.snap->ps.pm_flags & PMF_NO_PREDICTION ) || 
         ( cg.snap->ps.pm_flags & PMF_FROZEN ) 
      ) 
      {
		CG_InterpolatePlayerState( qfalse );
		return;
	   }

	// non-predicting local movement will grab the latest angles
   //FIXME
   // Noclip is jittery for some reason, so I'm disabling prediction while noclipping
	if ( cg_nopredict->integer || cg_syncronousClients->integer || (cg.snap->ps.pm_type == PM_NOCLIP) ) {
		CG_InterpolatePlayerState( qtrue );
		return;
	}

	// prepare for pmove
	cg_pmove.ps             = &cg.predicted_player_state;
	cg_pmove.trace          = CG_PlayerTrace;
	cg_pmove.pointcontents  = CG_PointContents;
	cg_pmove.trypush			= NULL;

	if ( cg_pmove.ps->pm_type == PM_DEAD )
      {
		cg_pmove.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;
	   }
	else 
      {
		cg_pmove.tracemask = MASK_PLAYERSOLID;
	   }

   /* FIXME
	if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR )
      {
		cg_pmove.tracemask &= ~CONTENTS_BODY;	// spectators can fly through bodies
	   }
   */

	cg_pmove.noFootsteps = ( cgs.dmflags & DF_NO_FOOTSTEPS ) > 0;

	// save the state before the pmove so we can detect transitions
	oldPlayerState = cg.predicted_player_state;

	current = cgi.GetCurrentCmdNumber();

	// if we don't have the commands right after the snapshot, we
	// can't accurately predict a current position, so just freeze at
	// the last good position we had
	cmdNum = current - CMD_BACKUP + 1;
	cgi.GetUserCmd( cmdNum, &oldestCmd );
	if ( oldestCmd.serverTime > cg.snap->ps.commandTime 
		&& oldestCmd.serverTime < cg.time ) {	// special check for map_restart
		if ( cg_showmiss->integer ) {
			cgi.Printf ("exceeded PACKET_BACKUP on commands\n");
		}

		return;
	}

	// get the latest command so we can know which commands are from previous map_restarts
	cgi.GetUserCmd( current, &latestCmd );

	// get the most recent information we have, even if
	// the server time is beyond our current cg.time,
	// because predicted player positions are going to 
	// be ahead of everything else anyway
	if ( cg.nextSnap && !cg.nextFrameTeleport && !cg.thisFrameTeleport ) {
		cg.predicted_player_state = cg.nextSnap->ps;
		cg.physicsTime = cg.nextSnap->serverTime;
	} else {
		cg.predicted_player_state = cg.snap->ps;
		cg.physicsTime = cg.snap->serverTime;
	}

	// run cmds
	moved = qfalse;
	for ( cmdNum = current - CMD_BACKUP + 1 ; cmdNum <= current ; cmdNum++ ) {
		// get the command
		cgi.GetUserCmd( cmdNum, &cg_pmove.cmd );

		// don't do anything if the time is before the snapshot player time
		if ( cg_pmove.cmd.serverTime <= cg.predicted_player_state.commandTime ) {
			continue;
		}

		// don't do anything if the command was from a previous map_restart
		if ( cg_pmove.cmd.serverTime > latestCmd.serverTime ) {
			continue;
		}

		// check for a prediction error from last frame
		// on a lan, this will often be the exact value
		// from the snapshot, but on a wan we will have
		// to predict several commands to get to the point
		// we want to compare
		if ( cg.predicted_player_state.commandTime == oldPlayerState.commandTime ) {
			vec3_t	delta;
			float	len;

			if ( cg.thisFrameTeleport ) {
				// a teleport will not cause an error decay
				VectorClear( cg.predictedError );
				cg.thisFrameTeleport = qfalse;
				if ( cg_showmiss->integer ) {
					cgi.Printf( "PredictionTeleport\n" );
				}
			} else {
				vec3_t	adjusted;

				CG_AdjustPositionForMover( cg.predicted_player_state.origin, 
					cg.predicted_player_state.groundEntityNum, cg.physicsTime, cg.oldTime, adjusted );
				VectorSubtract( oldPlayerState.origin, adjusted, delta );
				len = VectorLength( delta );
				if ( len > 0.1 ) {
					if ( cg_showmiss->integer ) {
						cgi.Printf("Prediction miss: %f\n", len);
					}
					if ( cg_errorDecay->integer ) {
						int		t;
						float	f;

						t = cg.time - cg.predictedErrorTime;
						f = ( cg_errorDecay->value - t ) / cg_errorDecay->value;
						if ( f < 0 ) {
							f = 0;
						}
						if ( f > 0 && cg_showmiss->integer ) {
							cgi.Printf("Double prediction decay: %f\n", f);
						}
						VectorScale( cg.predictedError, f, cg.predictedError );
					} else {
						VectorClear( cg.predictedError );
					}
					VectorAdd( delta, cg.predictedError, cg.predictedError );
					cg.predictedErrorTime = cg.oldTime;
				}
			}
		}

      // if our feet are falling, don't try to move
      if ( cg_pmove.ps->feetfalling && ( cg_pmove.waterlevel < 2 ) )
         {
         cg_pmove.cmd.forwardmove = 0;
         cg_pmove.cmd.rightmove = 0;
         }

		Pmove (&cg_pmove);
      
		moved = qtrue;

		// add push trigger movement effects
		//CG_TouchTriggerPrediction();
	}

	if ( cg_showmiss->integer > 1 ) {
		cgi.Printf( "[%i : %i] ", cg_pmove.cmd.serverTime, cg.time );
	}

   // interpolate the camera if necessary
   CG_InterpolatePlayerStateCamera();

	// adjust for the movement of the groundentity
	CG_AdjustPositionForMover( cg.predicted_player_state.origin, 
		cg.predicted_player_state.groundEntityNum, 
		cg.snap->serverTime, cg.time, cg.predicted_player_state.origin );

	if ( !moved ) {
		if ( cg_showmiss->integer ) {
			cgi.Printf( "not moved\n" );
		}
		return;
	}

	// fire events and other transition triggered things
	CG_TransitionPlayerState( &cg.predicted_player_state, &oldPlayerState );


}


