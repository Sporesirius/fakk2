//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/spawners.cpp                       $
// $Revision:: 18                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/22/00 10:35p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/spawners.cpp                            $
// 
// 18    7/22/00 10:35p Markd
// added spawnchance and spawnitem to func_spawns
// 
// 17    7/10/00 11:54p Markd
// added exit level code
// 
// 16    7/06/00 2:22p Steven
// Fixed spawners getting their angles set correctly.
// 
// 15    6/30/00 6:28p Steven
// Fixed a crash bug in Spawn::DoSpawn.
// 
// 14    6/26/00 9:01p Markd
// fixed angle overriding angles in func_spawn
// 
// 13    6/26/00 8:39p Markd
// Added func_randomspawn
// 
// 12    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 11    6/10/00 5:51p Aldie
// Fix G_DebugTargets function call
// 
// 10    6/03/00 3:46p Aldie
// Added in g_debugtargets for debugging targetnames and targets
// 
// 9     5/20/00 2:04p Aldie
// Fixed target with all the spawners
// 
// 8     5/19/00 7:19p Aldie
// Added spawntarget command
// 
// 7     4/29/00 12:07p Markd
// fixed precaching of func_spawners
// 
// 6     4/15/00 3:38p Aldie
// Added "idle" animation to func_spawner
// 
// 5     4/06/00 3:03p Markd
// fixed func_spawn's to pass on angles and scale
// 
// 4     3/27/00 3:06p Aldie
// Fixed a warning
// 
// 3     3/27/00 3:04p Aldie
// Took out some code that sends EV_Activate events to spawned ents
// 
// 2     3/18/00 2:43p Aldie
// Changed some func_spawn functionality
//
// DESCRIPTION:
// Various spawning entities

/*****************************************************************************/
/*QUAKED func_spawn(0 0.25 0.5) (-8 -8 -8) (8 8 8)
"modelname" The name of the TIKI file you wish to spawn. (Required)
"spawntargetname" This will be the targetname of the spawned model. (default is null)
"spawntarget" This will be the target of the spawned model. (default is null)
"pickup_thread" passed on to the spawned model
"key"       The item needed to activate this. (default nothing)
"attackmode" Attacking mode of the spawned actor (default 0)
******************************************************************************/

#include "spawners.h"

Event EV_Spawn_ModelName
	( 
	"modelname",
	EV_DEFAULT,
   "s",
   "model_name",
   "Sets the model name for this spawn entity."
	);
Event EV_Spawn_SpawnTargetName
	( 
	"spawntargetname",
	EV_DEFAULT,
   "s",
   "spawntargetname",
   "Sets spawn target name for this spawn entity."
	);
Event EV_Spawn_SpawnTarget
	( 
	"spawntarget",
	EV_DEFAULT,
   "s",
   "spawntarget",
   "Sets spawn target for this spawn entity."
	);
Event EV_Spawn_AttackMode
	( 
	"attackmode",
	EV_DEFAULT,
   "i",
   "attackmode",
   "Sets the attackmode for this spawn entity."
	);

Event EV_Spawn_PickupThread
	( 
	"pickup_thread",
	EV_DEFAULT,
   "s",
   "threadName",
   "Sets the pickup thread for the spawned entity."
	);

Event EV_Spawn_AddSpawnItem
	( 
	"spawnitem",
	EV_DEFAULT,
	"s",
	"spawn_item_name",
	"Adds this named item to what will be spawned when this spawned entity is killed, if it is an actor."
	);
Event EV_Spawn_SetSpawnChance
	( 
	"spawnchance",
	EV_DEFAULT,
	"f",
	"spawn_chance",
	"Sets the chance that this spawned entity will spawn something when killed, if it is an actor."
	);


CLASS_DECLARATION( ScriptSlave, Spawn, "func_spawn" )
	{
      { &EV_Activate,               DoSpawn },
      { &EV_Spawn_ModelName,        ModelName },
      { &EV_Spawn_SpawnTargetName,  SpawnTargetName },
      { &EV_Spawn_AttackMode,       AttackMode },
      { &EV_Spawn_SpawnTarget,      SpawnTarget },
      { &EV_Spawn_PickupThread,     SetPickupThread },
		{ &EV_SetAngle,			      SetAngleEvent },
		{ &EV_Spawn_AddSpawnItem,		SetSpawnItem },
		{ &EV_Spawn_SetSpawnChance,	SetSpawnChance },
      { NULL, NULL }
	};

void Spawn::SetAngleEvent
	(
	Event *ev
	)
	{
	Entity::SetAngleEvent( ev );
   }

void Spawn::SetPickupThread
	(
	Event *ev
	)
	{
	pickup_thread = ev->GetString( 1 );
   }

void Spawn::ModelName
   (
   Event *ev
   )

   {
   modelname = ev->GetString( 1 );
   CacheResource( modelname, this );
   }

void Spawn::SpawnTargetName
   (
   Event *ev
   )

   {
   spawntargetname = ev->GetString( 1 );
   }

void Spawn::SpawnTarget
   (
   Event *ev
   )

   {
   spawntarget = ev->GetString( 1 );
   }

void Spawn::AttackMode
   (
   Event *ev
   )

   {
   attackmode = ev->GetInteger( 1 );
   }

void Spawn::SetSpawnItem
   (
   Event *ev
   )

   {
   spawnitem = ev->GetString( 1 );
   }

void Spawn::SetSpawnChance
   (
   Event *ev
   )

   {
   spawnchance = ev->GetFloat( 1 );
   }

Spawn::Spawn()
	{
	setSolidType( SOLID_NOT );
	setMoveType( MOVETYPE_NONE );
   hideModel();

   spawnchance = 0;
   attackmode = 0;
   }

void Spawn::SetArgs
   ( 
   SpawnArgs &args 
   )
   {
   args.setArg( "origin",     va( "%f %f %f", origin[ 0 ], origin[ 1 ], origin[ 2 ] ) );
   args.setArg( "angle",      va( "%f", angles[ 1 ] ) );
   args.setArg( "angles",     va( "%f %f %f", angles[ 0 ], angles[ 1 ], angles[ 2 ] ) );
   args.setArg( "model",      modelname.c_str() );
   args.setArg( "attackmode", va( "%i",attackmode ) );
   args.setArg( "scale",      va( "%f",edict->s.scale ) );
   if ( spawntargetname.length() )
      {
      args.setArg( "targetname", spawntargetname.c_str() );
      }
   if ( spawntarget.length() )
      {
      args.setArg( "target",     spawntarget.c_str() );
      }
   if ( pickup_thread.length() )
      {
      args.setArg( "pickup_thread", pickup_thread.c_str() );
      }
   if ( spawnitem.length() )
      {
      args.setArg( "spawnitem", spawnitem.c_str() );
      args.setArg( "spawnchance", va( "%f", spawnchance ) );
      }
   }

void Spawn::DoSpawn
   ( 
   Event *ev 
   )
   {
   Entity *spawn;
   SpawnArgs args;

   if ( !modelname.length() )
      {
      warning("Spawn", "modelname not set" );
      }

   SetArgs( args );

   spawn = args.Spawn();

   if ( spawn )
      {
      // make sure spawned entity starts falling if necessary
	   spawn->velocity = "0 0 -1";

		Event *e = new Event( EV_Anim );
		e->AddString( "idle" );
		spawn->PostEvent( e, EV_SPAWNARG );

		if ( g_debugtargets->integer )
			{
			G_DebugTargets( spawn, "Spawn::DoSpawn" );
			}
      }
   }

/*****************************************************************************/
/*QUAKED func_randomspawn(0 0.25 0.5) (-8 -8 -8) (8 8 8) START_OFF
Randomly spawns an entity.  The time between spawns is determined by min_time and max_time
The entity can be turned off and on by triggering it
"modelname"   The name of the TIKI file you wish to spawn. (Required)
"key"         The item needed to activate this. (default nothing)
"min_time" The minimum time between spawns (default 0.2 seconds)
"max_time" The maximum time between spawns (default 1 seconds)
START_OFF - spawn is off by default
******************************************************************************/

Event EV_RandomSpawn_MinTime
	( 
	"min_time",
	EV_DEFAULT,
   "f",
   "minTime",
   "Minimum time between random spawns."
	);

Event EV_RandomSpawn_MaxTime
	( 
	"max_time",
	EV_DEFAULT,
   "f",
   "maxTime",
   "Maximum time between random spawns."
	);

Event EV_RandomSpawn_Think
	( 
	"_randomspawn_think",
	EV_DEFAULT,
   NULL,
   NULL,
   "The function that actually spawns things in."
	);

CLASS_DECLARATION( Spawn, RandomSpawn, "func_randomspawn" )
	{
      { &EV_Activate,                   ToggleSpawn },
      { &EV_RandomSpawn_MinTime,        MinTime },
      { &EV_RandomSpawn_MaxTime,        MaxTime },
      { &EV_RandomSpawn_Think,          Think },
      { NULL, NULL }
	};

RandomSpawn::RandomSpawn()
   {
   min_time = 0.2f;
   max_time = 1.0f;
   if ( !LoadingSavegame && !( spawnflags & 1 ) )
      {
      PostEvent( EV_RandomSpawn_Think, min_time + ( G_Random( max_time - min_time ) ) );
      }
   }

void RandomSpawn::MinTime
   (
   Event *ev
   )

   {
   min_time = ev->GetFloat( 1 );
   }

void RandomSpawn::MaxTime
   (
   Event *ev
   )

   {
   max_time = ev->GetFloat( 1 );
   }

void RandomSpawn::ToggleSpawn
   (
   Event *ev
   )

   {
   if ( EventPending( EV_RandomSpawn_Think ) )
      {
      // if currently on, turn it off
      CancelEventsOfType( EV_RandomSpawn_Think );
      }
   else
      {
      Think( NULL );
      }
   }

void RandomSpawn::Think( Event *ev )
   {
   CancelEventsOfType( EV_RandomSpawn_Think );

   //
   // spawn our entity
   //
   DoSpawn( NULL );

   // 
   // post the next time
   //
   PostEvent( EV_RandomSpawn_Think, min_time + ( G_Random( max_time - min_time ) ) );
   }

/*****************************************************************************/
/*QUAKED func_respawn(0 0.25 0.5) (-8 -8 -8) (8 8 8)
When the thing that is spawned is killed, this func_respawn will get
triggered.
"modelname"   The name of the TIKI file you wish to spawn. (Required)
"key"         The item needed to activate this. (default nothing)
******************************************************************************/

CLASS_DECLARATION( Spawn, ReSpawn, "func_respawn" )
	{
      { NULL, NULL }
	};

void ReSpawn::DoSpawn( Event *ev )
   {
   Entity      *spawn;
   SpawnArgs   args;

   SetArgs( args );

   // This will trigger the func_respawn when the thing dies
   args.setArg( "targetname", TargetName() );
   args.setArg( "target", TargetName() );

   spawn = args.Spawn();
   if ( spawn )
      {
      // make sure spawned entity starts falling if necessary
	   spawn->velocity = "0 0 -1";
      }
   }

/*****************************************************************************/
/*QUAKED func_spawnoutofsight(0 0.25 0.5) (-8 -8 -8) (8 8 8)
Will only spawn something out of sight of its targets.
"modelname"   The name of the TIKI file you wish to spawn. (Required)
"spawntargetname" This will be the targetname of the spawned model. (default is null)
"spawntarget" This will be the target of the spawned model. (default is null)
"key"         The item needed to activate this. (default nothing)
******************************************************************************/

CLASS_DECLARATION( Spawn, SpawnOutOfSight, "func_spawnoutofsight" )
	{
      { NULL, NULL }
	};

void SpawnOutOfSight::DoSpawn
	(
	Event *ev
	)

   {
   int         i;
   Entity	   *ent;
   gentity_t   *ed;
   trace_t     trace;
   qboolean    seen = false;

   // Check to see if I can see any players before spawning
 	for( i = 0; i < game.maxclients; i++ )
      {
      ed = &g_entities[ i ];
		if ( !ed->inuse || !ed->entity )
			{
			continue;
			}

		ent = ed->entity;
	   if ( ( ent->health < 0 ) || ( ent->flags & FL_NOTARGET ) )
			{
			continue;
			}

      trace = G_Trace( origin, vec_zero, vec_zero, ent->centroid, this, MASK_OPAQUE, false, "SpawnOutOfSight::DoSpawn" );
      if ( trace.fraction == 1.0 )
         {
         seen = true;
         break;
         }
      }

   if ( seen )
      {
      return;
      }

   Spawn::DoSpawn( ev );
   }


/*****************************************************************************/
/*QUAKED func_spawnchain(0 0.25 0.5) (-8 -8 -8) (8 8 8)
Tries to spawn something out of the sight of players.  If it fails, it will
trigger its targets.
"modelname"   The name of the TIKI file you wish to spawn. (Required)
"spawntargetname" This will be the targetname of the spawned model. (default is null)
"spawntarget" This will be the target of the spawned model. (default is null)
"key"         The item needed to activate this. (default nothing)
******************************************************************************/

CLASS_DECLARATION( Spawn, SpawnChain, "func_spawnchain" )
	{
      { NULL, NULL }
	};

void SpawnChain::DoSpawn
	(
	Event *ev
	)

   {
   int         i;
   Entity	   *ent;
   gentity_t   *ed;
   trace_t     trace;
   qboolean    seen = false;
   const char  *name;
   Event       *event;

   // Check to see if this can see any players before spawning
 	for( i = 0; i < game.maxclients; i++ )
      {
      ed = &g_entities[ i ];
		if ( !ed->inuse || !ed->entity )
			{
			continue;
			}

		ent = ed->entity;
	   if ( ( ent->health < 0 ) || ( ent->flags & FL_NOTARGET ) )
			{
			continue;
			}

      trace = G_Trace( origin, vec_zero, vec_zero, ent->centroid, this, MASK_OPAQUE, false, "SpawnChain::DoSpawn" );
      if ( trace.fraction == 1.0 )
         {
         seen = true;
         break;
         }
      }

   // Couldn't spawn anything, so activate targets
   if ( seen )
      {
   	name = Target();
	   if ( name && strcmp( name, "" ) )
		   {
         ent = NULL;
		   do
			   {
			   ent = G_FindTarget( ent, name );
			   if ( !ent )
				   {
				   break;
				   }
		   	event = new Event( EV_Activate );
            event->AddEntity( world );
			   ent->PostEvent( event, 0 );
            } while ( 1 );
         }
      return;
      }

   Spawn::DoSpawn( ev );
   }
