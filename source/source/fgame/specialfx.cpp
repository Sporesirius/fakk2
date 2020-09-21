//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/specialfx.cpp                      $
// $Revision:: 39                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/22/00 10:15p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/specialfx.cpp                           $
// 
// 39    7/22/00 10:15p Markd
// fixed fulcrum bug
// 
// 38    7/14/00 4:43p Steven
// Made RunThroughs cache their spawn models.
// 
// 37    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 36    6/22/00 7:09p Markd
// fixed some spawning issues
// 
// 35    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 34    6/03/00 11:59a Markd
// transposed FALLAWAY and NO_RESET for sinkobjects
// 
// 33    6/03/00 11:56a Markd
// fixed bug with sinkobjects not being solid
// 
// 32    4/29/00 12:07p Markd
// added active ability to sink objects
// 
// 31    4/24/00 7:16p Markd
// added movesounds to fulcrums
// 
// 30    2/02/00 9:26a Markd
// Added resetsound, resetdelay and sinksound to sinkobject
// 
// 29    2/01/00 6:55p Markd
// Added offset support to func_runthrough
// 
// 28    1/31/00 6:07p Markd
// tweaked func_sinkobject
// 
// 27    1/29/00 4:06p Markd
// Added func_sinkobject
// 
// 26    1/29/00 2:13p Markd
// Added Func_Runthrough entity
// 
// 25    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 24    1/12/00 8:44p Markd
// fixed fulcrum, its axises were inverted
// 
// 23    1/12/00 6:16p Jimdose
// Removed sprite class
// 
// 22    1/10/00 6:17p Jimdose
// more code cleanup
// 
// 21    1/05/00 7:28p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 20    1/03/00 11:23a Markd
// fixed func_fulcrum bug
// 
// 19    11/15/99 12:43p Markd
// added single axis rotation, angle limits and separate dampening and reset
// speed constants
// 
// 18    10/22/99 11:55a Markd
// made fulcrum have reset speed adjustment
// 
// 17    10/18/99 7:14p Markd
// Fixed fulcrum stuff
// 
// 16    10/18/99 1:59p Aldie
// Lots of fixes for beams and stuff
// 
// 15    10/14/99 7:01p Markd
// Added first run of func_fullcrum
// 
// 14    10/14/99 5:08p Markd
// removed a lot of G_GetMoveDir calls from the initialization code
// 
// 13    10/11/99 3:10p Steven
// Event documentation cleanup.
// 
// 12    10/04/99 10:53a Aldie
// fix warning
// 
// 11    10/02/99 6:51p Markd
// Put in backend work for event documentation and fixed a lot of event
// documentation bugs
// 
// 10    10/01/99 6:08p Aldie
// Added some new features to beam system
// 
// 9     9/30/99 4:37p Aldie
// Added subdivisions event
// 
// 8     9/30/99 1:49p Aldie
// Documentation of commands
// 
// 7     9/29/99 4:12p Aldie
// Added beams and fixed some lightmap probs
// 
// 6     9/22/99 4:48p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 5     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 4     9/16/99 4:49p Jimdose
// removed unused code
// 
// 3     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 2     9/13/99 3:27p Aldie
// code merge
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 29    8/28/99 7:45p Markd
// added broadcast to any entity that is a skyorigin
// 
// 28    8/26/99 5:57p Markd
// Re-added fx_sprite support
// 
// 27    8/18/99 3:29p Jimdose
// added cylindrical collision detection
// 
// 26    7/23/99 3:27p Aldie
// 
// 25    6/11/99 1:23p Phook
// 
// 24    6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
// 
// 23    6/11/99 12:46p Phook
// EClass color changes
//
// DESCRIPTION:
// Special fx
//

#include "g_local.h"
#include "specialfx.h"

/*****************************************************************************/
/*QUAKED func_fulcrum (0 0 1) ? X_AXIS_ONLY Y_AXIS_ONLY

This creates a fulcrum that when you stand on it, it will rotate due to 
the weight exerted it will start rotating, when not standing on it, it 
will return to its rest position.
"speed" - set the speed at which the fulcrum will operate (default is 48)
"resetspeed" - speed at whcih fulcrum resets, (default speed * 0.002)
"dampening" - dampen constant (default 0.95)
"limit" - limit the movement of the fulcrum (default 90 degrees)
"movesound" - sound to be played while fulcrum is moving

X_AXIS_ONLY - only adjust the X axis
Y_AXIS_ONLY - only adjust the Y axis

******************************************************************************/

#define X_AXIS_ONLY ( 1 << 0 )
#define Y_AXIS_ONLY ( 1 << 1 )

Event EV_Fulcrum_SetSpeed
   (
   "speed",
   EV_DEFAULT,
   "f",
   "speed",
   "Speed at which fulcrum operates itself."
   );

Event EV_Fulcrum_Reset
   (
   "reset",
   EV_CONSOLE,
   NULL,
   NULL,
   "Reset the fulcrum right now."
   );

Event EV_Fulcrum_AdjustFulcrum
   (
   "_adjust_fulcrum",
   EV_HIDE,
   NULL,
   NULL,
   "Called periodically to adjust the frustum every frame and update its angular velocity."
   );

Event EV_Fulcrum_SetResetSpeed
   (
   "resetspeed",
   EV_DEFAULT,
   "f",
   "newResetspeed",
   "Speed at which fulcrum resets itself, defaults to 0.002 * speed."
   );

Event EV_Fulcrum_SetDampening
   (
   "dampening",
   EV_DEFAULT,
   "f",
   "newDampening",
   "dampening of fulcrum."
   );

Event EV_Fulcrum_SetLimit
   (
   "limit",
   EV_DEFAULT,
   "f",
   "newLimit",
   "angular limit for the fulcrum."
   );

Event EV_Fulcrum_Setup
   (
   "_setup",
   EV_DEFAULT,
   NULL,
   NULL,
   "setup the fulcrum for the first time."
   );

Event EV_Fulcrum_SetMoveSound
   (
   "movesound",
   EV_DEFAULT,
   "s",
   "newSinkSound",
   "Sound played when fulcrum is moving."
   );


CLASS_DECLARATION( ScriptSlave, Fulcrum, "func_fulcrum" )
	{
      { &EV_Fulcrum_SetSpeed,       SetSpeed },
      { &EV_Fulcrum_Reset,          Reset },
      { &EV_Fulcrum_AdjustFulcrum,  Adjust },
      { &EV_Touch,                  Touched },
      { &EV_Fulcrum_SetResetSpeed,  SetResetSpeed },
      { &EV_Fulcrum_SetDampening,   SetDampening },
      { &EV_Fulcrum_SetLimit,       SetLimit },
      { &EV_Fulcrum_Setup,          Setup },
      { &EV_Fulcrum_SetMoveSound,   SetMoveSound },
		{ NULL, NULL }
	};

Fulcrum::Fulcrum()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   touched = qfalse;
   speed = 48;
   resetspeed = speed * 0.002;
   dampening = 0.95;
   limit = 90;
	setMoveType( MOVETYPE_PUSH );
	PostEvent( EV_Fulcrum_Setup, FRAMETIME );
   }

void Fulcrum::Setup
   (
   Event *ev
   )

   {
   startangles = angles;
   }

void Fulcrum::SetSpeed
   (
   Event *ev
   )

   {
   speed = ev->GetFloat( 1 );
   resetspeed = speed * 0.002;
   }

void Fulcrum::SetResetSpeed
   (
   Event *ev
   )

   {
   resetspeed = ev->GetFloat( 1 );
   }

void Fulcrum::SetDampening
   (
   Event *ev
   )

   {
   dampening = ev->GetFloat( 1 );
   }

void Fulcrum::SetLimit
   (
   Event *ev
   )

   {
   limit = ev->GetFloat( 1 );
   }

void Fulcrum::SetMoveSound
   (
   Event *ev
   )

   {
   movesound = ev->GetString( 1 );
   }


void Fulcrum::Reset
   (
   Event *ev
   )

   {
   StopLoopSound();
   touched = qfalse;
   avelocity = vec_zero;
   setAngles( startangles );
   CancelEventsOfType( EV_Fulcrum_AdjustFulcrum );
   }

void Fulcrum::Touched
   (
   Event *ev
   )

   {
   Vector   diff;
   vec3_t   dest;
   Vector   delta;
   Entity * other;

   other = ev->GetEntity( 1 );

   assert( other );
   if ( !other )
      return;

   //
   // only things resting on me will affect me
   //
   if ( other->groundentity != this->edict )
      return;

   if ( movesound.length() )
      {
      LoopSound( movesound );
      }

   delta = getLocalVector( other->origin - origin );

   //
   // clear out angular velocity
   //
   avelocity = vec_zero;

   // only look at x and y since z doesn't really concern us.
   if ( !( spawnflags & X_AXIS_ONLY ) )
      {
      avelocity[ PITCH ] += cos( DEG2RAD( startangles[ YAW ] ) ) * speed * delta[ 0 ] / maxs[ 0 ];
      avelocity[ ROLL ] += sin( DEG2RAD( startangles[ YAW ] ) ) * speed * delta[ 0 ] / maxs[ 0 ];
      }
   if ( !( spawnflags & Y_AXIS_ONLY ) )
      {
      avelocity[ ROLL ] += cos( DEG2RAD( startangles[ YAW ] ) ) * -speed * delta[ 1 ] / maxs[ 1 ];
      avelocity[ PITCH ] += sin( DEG2RAD( startangles[ YAW ] ) ) * -speed * delta[ 1 ] / maxs[ 1 ];
      }

   AnglesSubtract( startangles, angles, dest );
   diff = Vector( dest );
   if ( fabs( diff[ PITCH ] ) >= limit )
      {
      Vector newAngles;
      StopLoopSound();
      if ( diff[ PITCH ] > 0 )
         {
         if ( avelocity[ PITCH ] < 0 )
            {
            avelocity[ PITCH ] = 0;
            }
         }
      else if ( diff[ PITCH ] < 0 )
         {
         if ( avelocity[ PITCH ] > 0 )
            {
            avelocity[ PITCH ] = 0;
            }
         }
      }

   if ( fabs( diff[ ROLL ] ) >= limit )
      {
      StopLoopSound();
      if ( diff[ ROLL ] > 0 )
         {
         if ( avelocity[ ROLL ] < 0 )
            {
            avelocity[ ROLL ] = 0;
            }
         }
      else if ( diff[ ROLL ] < 0 )
         {
         if ( avelocity[ ROLL ] > 0 )
            {
            avelocity[ ROLL ] = 0;
            }
         }
      }

   touched = qtrue;
   CancelEventsOfType( EV_Fulcrum_AdjustFulcrum );
   PostEvent( EV_Fulcrum_AdjustFulcrum, 0 );
   }

void Fulcrum::Adjust
   (
   Event *ev
   )

   {
   if ( !touched )
      {
      int      i;
      float    f;
      Vector   diff;
      vec3_t   dest;
      qboolean post;

      if ( movesound.length() )
         {
         LoopSound( movesound );
         }
      AnglesSubtract( startangles, angles, dest );
      diff = Vector( dest );
      post = qfalse;

      for( i = 0; i < 3; i++ )
         {
         if ( diff[ i ] )
            {
            avelocity[ i ] += resetspeed * diff[ i ];
            }
         avelocity[ i ] *= dampening;
         f = fabs( avelocity[ i ] );
         if ( f > 0.01f )
            {
            post = qtrue;
            }
         }
      if ( !post )
         {
         Reset( NULL );
         return;
         }
      }  
   else
      {
      touched = qfalse;
      }

   PostEvent( EV_Fulcrum_AdjustFulcrum, FRAMETIME );
   }

/*****************************************************************************/
/*QUAKED func_runthrough (0 0 1) ? 

This is a trigger field that the player can run through and spawn tiki models
at that position.  Used for releasing chaff from grass or butterflys from
flower gardens
"speed" - speed at which you have to be moving to trigger ( default 100 )
"delay" - time between triggering ( default 0.1 )
"chance" - chance that the trigger will spawn something( default 0.5 )
"lip" - how far below the surface of the trigger we should spawn these things ( default 3 )
"offset" - vector offset oriented along velocity vector( default "0 0 0" )
"spawnmodel" - thing to spawn when triggered

******************************************************************************/


Event EV_RunThrough_SetSpeed
   (
   "speed",
   EV_DEFAULT,
   "f",
   "speed",
   "threshold speed at which RunThrough is activated."
   );

Event EV_RunThrough_SetDelay
   (
   "delay",
   EV_DEFAULT,
   "f",
   "delay",
   "time between RunThrough being activated."
   );

Event EV_RunThrough_SetChance
   (
   "chance",
   EV_DEFAULT,
   "f",
   "chance",
   "chance that trigger will spawn something."
   );

Event EV_RunThrough_SetLip
   (
   "lip",
   EV_DEFAULT,
   "f",
   "lip",
   "distance below trigger we should spawn things."
   );

Event EV_RunThrough_SetSpawnModel
   (
   "spawnmodel",
   EV_DEFAULT,
   "s",
   "model_to_spawn",
   "When triggered, what to spawn."
   );

Event EV_RunThrough_SetOffset
   (
   "offset",
   EV_DEFAULT,
   "v",
   "spawn_offset",
   "When triggered, what to offset the spawned object by."
   );


CLASS_DECLARATION( Entity, RunThrough, "func_runthrough" )
	{
      { &EV_RunThrough_SetSpeed,       SetSpeed },
      { &EV_RunThrough_SetDelay,       SetDelay },
      { &EV_RunThrough_SetChance,      SetChance },
      { &EV_RunThrough_SetLip,         SetLip },
      { &EV_RunThrough_SetSpawnModel,  SetSpawnModel },
      { &EV_RunThrough_SetOffset,      SetOffset },
      { &EV_Touch,                     Touched },
		{ NULL, NULL }
	};

RunThrough::RunThrough()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   offset = vec_zero;
   speed = 100.0f;
   chance = 0.5f;
   delay = 0.1f;
   lip = 3.0f;
   spawnmodel = "";
   lasttriggertime = 0;
	setMoveType( MOVETYPE_NONE );
  	setSolidType( SOLID_TRIGGER );
   }

void RunThrough::SetSpeed
   (
   Event *ev
   )

   {
   speed = ev->GetFloat( 1 );
   }

void RunThrough::SetChance
   (
   Event *ev
   )

   {
   chance = ev->GetFloat( 1 );
   }

void RunThrough::SetDelay
   (
   Event *ev
   )

   {
   delay = ev->GetFloat( 1 );
   }

void RunThrough::SetLip
   (
   Event *ev
   )

   {
   lip = ev->GetFloat( 1 );
   }

void RunThrough::SetOffset
   (
   Event *ev
   )

   {
   offset = ev->GetVector( 1 );
   }

void RunThrough::SetSpawnModel
   (
   Event *ev
   )

   {
   spawnmodel = ev->GetString( 1 );
	CacheResource( spawnmodel, this );
   }

void RunThrough::Touched
   (
   Event *ev
   )

   {
   Vector   forward, left, up;
   Vector   ang;
   Vector   org;
   Entity * other;

   other = ev->GetEntity( 1 );

   assert( other );
   if ( !other )
      return;

   // don't trigger on the world
   if ( other == world )
      return;

   // don't re-trigger too soon
   if ( level.time < lasttriggertime )
      return;

   // don't trigger if not moving fast enough
   if ( other->velocity.length() < speed )
      return;

   // don't trigger if chance says not to.
   if ( G_Random( 1 ) > chance )
      return;

   ang = other->velocity.toAngles();
   ang.AngleVectors( &forward, &left, &up );

   // get the origin from the thing that triggered me
   org = other->origin;

   // set the height of the origin based on the bounds of this trigger minus the lip
   org.z = absmax.z - lip;

   org += offset.x * forward;
   org += offset.y * left;
   org += offset.z * up;

   if ( spawnmodel.length() )
      {
      Entity * ent;
      // purposely declared here so that we don't do it every frame
      SpawnArgs args;

      args.setArg( "origin", va( "%f %f %f", org[ 0 ], org[ 1 ], org[ 2 ] ) );
      args.setArg( "angles", va( "%f %f %f", ang[ 0 ], ang[ 1 ], ang[ 2 ] ) );
      args.setArg( "model", spawnmodel.c_str() );

      ent = args.Spawn();
      if ( ent )
         {
         ent->ProcessPendingEvents();
         }
      }
   // set trigger time for next time
   lasttriggertime = level.time + delay;
   }



/*****************************************************************************/
/*QUAKED func_sinkobject (0 0 1) ? x FALLAWAY NO_RESET 

This creates an object which gradually sinks downward when stepped on.
"delay" - delay between when object starts reacting towards weight (default 0 seconds)
"speed" - set the speed at which sinkobject sinks (default is 50)
"resetspeed" - speed at which sinkobject resets its position, (default speed * 0.1)
"dampening" - dampening constant to mitigate acceleration (default 0.95)
"limit" - limit the movement of the sinkobject how far down it should go (default 1000 units)
"resetdelay" - time between player gets off platform, and platform starts resetting itself.
"sinksound" - sound to be played while platform is sinking.
"resetsound" - sound to be played while platform is resetting.
"active" - make the sink object active
"notactive" - make the sink object not active

FALLAWAY - the sink object will progressively fall down faster and faster
NO_RESET - the sink object will not reset, only move downward

******************************************************************************/

#define FALLAWAY ( 1 << 1 )
#define NO_RESET ( 1 << 2 )

Event EV_SinkObject_SetSpeed
   (
   "speed",
   EV_DEFAULT,
   "f",
   "speed",
   "Speed at which SinkObject starts falling."
   );

Event EV_SinkObject_SetDelay
   (
   "delay",
   EV_DEFAULT,
   "f",
   "delay",
   "Delay until SinkObject starts falling."
   );

Event EV_SinkObject_Reset
   (
   "reset",
   EV_CONSOLE,
   NULL,
   NULL,
   "Reset the SinkObject right now."
   );

Event EV_SinkObject_AdjustSinkObject
   (
   "_adjust_SinkObject",
   EV_HIDE,
   NULL,
   NULL,
   "Called periodically to adjust the sinkobject every frame and adjust its velocity."
   );

Event EV_SinkObject_Fall
   (
   "_fall_SinkObject",
   EV_HIDE,
   NULL,
   NULL,
   "Called periodically to make a sink object fall away."
   );

Event EV_SinkObject_SetResetSpeed
   (
   "resetspeed",
   EV_DEFAULT,
   "f",
   "newResetspeed",
   "Speed at which SinkObject resets itself, defaults to 0.002 * speed."
   );

Event EV_SinkObject_SetResetDelay
   (
   "resetdelay",
   EV_DEFAULT,
   "f",
   "newResetDelay",
   "Delay between when sinkobject starts resetting."
   );

Event EV_SinkObject_SetSinkSound
   (
   "sinksound",
   EV_DEFAULT,
   "s",
   "newSinkSound",
   "Sound played when sinkobject is sinking."
   );

Event EV_SinkObject_SetResetSound
   (
   "resetsound",
   EV_DEFAULT,
   "s",
   "newResetSound",
   "Sound played when sinkobject is resetting."
   );

Event EV_SinkObject_SetDampening
   (
   "dampening",
   EV_DEFAULT,
   "f",
   "newDampening",
   "dampening of SinkObject."
   );

Event EV_SinkObject_SetLimit
   (
   "limit",
   EV_DEFAULT,
   "f",
   "newLimit",
   "maximum displacement of the SinkObject."
   );

Event EV_SinkObject_Setup
   (
   "_setup",
   EV_DEFAULT,
   NULL,
   NULL,
   "setup the SinkObject for the first time."
   );

Event EV_SinkObject_MakeActive
   (
   "active",
   EV_DEFAULT,
   NULL,
   NULL,
   "make the SinkObject active, so that it will respond to players touching it."
   );

Event EV_SinkObject_MakeNonActive
   (
   "notactive",
   EV_DEFAULT,
   NULL,
   NULL,
   "make the SinkObject not active, so that it won't respond to players touching it."
   );


CLASS_DECLARATION( ScriptSlave, SinkObject, "func_sinkobject" )
	{
      { &EV_SinkObject_SetSpeed,          SetSpeed },
      { &EV_SinkObject_SetDelay,          SetDelay },
      { &EV_SinkObject_Reset,             Reset },
      { &EV_SinkObject_AdjustSinkObject,  Adjust },
      { &EV_SinkObject_Fall,              Fall },
      { &EV_Touch,                        Touched },
      { &EV_SinkObject_SetResetSpeed,     SetResetSpeed },
      { &EV_SinkObject_SetDampening,      SetDampening },
      { &EV_SinkObject_SetLimit,          SetLimit },
      { &EV_SinkObject_Setup,             Setup },
      { &EV_SinkObject_SetResetDelay,     SetResetDelay },
      { &EV_SinkObject_SetResetSound,     SetResetSound },
      { &EV_SinkObject_SetSinkSound,      SetSinkSound },
      { &EV_SinkObject_MakeActive,        MakeActive },
      { &EV_SinkObject_MakeNonActive,     MakeNonActive },
		{ NULL, NULL }
	};

#define RESET_SCALE 0.1f
#define SPEED_DIVISOR ( 1.0f / 250.0f )

SinkObject::SinkObject()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   active = qtrue;
   sinksound = "";
   resetsound = "";
   resetdelay = 0;
   delay = 0;
   touched = qfalse;
   speed = 50 * SPEED_DIVISOR;
   resetspeed = speed * RESET_SCALE;
   dampening = 0.95;
   limit = 1000;
   time_touched = -1;
   time_reset = -1;
	setMoveType( MOVETYPE_PUSH );
	PostEvent( EV_SinkObject_Setup, FRAMETIME );
   }

void SinkObject::Setup
   (
   Event *ev
   )

   {
   startpos = origin;
   }

void SinkObject::SetSpeed
   (
   Event *ev
   )

   {
   speed = ev->GetFloat( 1 ) * SPEED_DIVISOR;
   resetspeed = speed * RESET_SCALE;
   }

void SinkObject::SetDelay
   (
   Event *ev
   )

   {
   delay = ev->GetFloat( 1 );
   }

void SinkObject::SetResetSpeed
   (
   Event *ev
   )

   {
   resetspeed = ev->GetFloat( 1 ) * SPEED_DIVISOR;
   }

void SinkObject::SetResetDelay
   (
   Event *ev
   )

   {
   resetdelay = ev->GetFloat( 1 );
   }

void SinkObject::SetSinkSound
   (
   Event *ev
   )

   {
   sinksound = ev->GetString( 1 );
   }

void SinkObject::SetResetSound
   (
   Event *ev
   )

   {
   resetsound = ev->GetString( 1 );
   }

void SinkObject::SetDampening
   (
   Event *ev
   )

   {
   dampening = ev->GetFloat( 1 );
   }

void SinkObject::SetLimit
   (
   Event *ev
   )

   {
   limit = ev->GetFloat( 1 );
   }

void SinkObject::Reset
   (
   Event *ev
   )

   {
   time_reset = -1;
   time_touched = -1;
   touched = qfalse;
   velocity = vec_zero;
   setOrigin( startpos );
   CancelEventsOfType( EV_SinkObject_AdjustSinkObject );
   StopLoopSound();
   }

void SinkObject::Touched
   (
   Event *ev
   )

   {
   Entity * other;

   // if we aren't active, don't let anyone touch us
   if ( !active )
      return;

   other = ev->GetEntity( 1 );

   assert( other );
   if ( !other )
      return;

   //
   // only things resting on me will affect me
   //
   if ( other->groundentity != this->edict )
      return;

   if ( delay )
      {
      if ( time_touched == -1 )
         time_touched = level.time + delay;
      //
      // not time yet
      //
      if ( level.time < time_touched )
         return;
      }
   if ( sinksound.length() )
      {
      LoopSound( sinksound );
      }

   velocity.z -= speed;

   if ( origin.z < ( startpos.z - limit ) )
      {
      origin.z = startpos.z - limit;
      setOrigin( origin );
      velocity = vec_zero;
      }

   touched = qtrue;

   if ( spawnflags & FALLAWAY )
      {
      CancelEventsOfType( EV_SinkObject_Fall );
      PostEvent( EV_SinkObject_Fall, FRAMETIME );
      return;
      }

   CancelEventsOfType( EV_SinkObject_AdjustSinkObject );
   PostEvent( EV_SinkObject_AdjustSinkObject, FRAMETIME );
   }

void SinkObject::Fall
   (
   Event *ev
   )

   {
   velocity.z -= speed;

   if ( origin.z < ( startpos.z - limit ) )
      {
      origin.z = startpos.z - limit;
      setOrigin( origin );
      velocity = vec_zero;
      StopLoopSound();
      }
   else
      {
      CancelEventsOfType( EV_SinkObject_Fall );
      PostEvent( EV_SinkObject_Fall, FRAMETIME );
      }
   }


void SinkObject::Adjust
   (
   Event *ev
   )

   {
   if ( !touched )
      {
      float    diff;

      if ( spawnflags & NO_RESET )
         {
         StopLoopSound();
         time_touched = -1;
         velocity.z = 0;
         return;
         }
      else
         {
         if ( resetdelay )
            {
            // stop the object
            velocity.z = 0;
            // kill its sound
            StopLoopSound();
            if ( time_reset == -1 )
               time_reset = level.time + resetdelay;
            //
            // not time yet
            //
            if ( level.time < time_reset )
               {
               PostEvent( EV_SinkObject_AdjustSinkObject, FRAMETIME );
               return;
               }
            }
         if ( resetsound.length() )
            {
            LoopSound( resetsound );
            }
         diff = startpos.z - origin.z;

         velocity.z += resetspeed * diff;
         velocity.z *= dampening;
         if ( ( fabs( diff ) < 0.5f ) && ( fabs( velocity.z ) < 1 ) )
            {
            Reset( NULL );
            return;
            }
         }
      }  
   else
      {
      touched = qfalse;
      }

   PostEvent( EV_SinkObject_AdjustSinkObject, FRAMETIME );
   }

void SinkObject::MakeActive
   (
   Event *ev
   )

   {
   active = qtrue;
   }

void SinkObject::MakeNonActive
   (
   Event *ev
   )

   {
   active = qfalse;
   }
