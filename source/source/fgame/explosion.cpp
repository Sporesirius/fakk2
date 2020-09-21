//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/explosion.cpp                      $
// $Revision:: 24                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 7/22/00 5:53p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/explosion.cpp                           $
// 
// 24    7/22/00 5:53p Steven
// Made it so a remove event is only posted if explosions have a life set.
// 
// 23    7/16/00 2:10p Markd
// fixed multi use func_explodeobjects
// 
// 22    7/16/00 12:44p Markd
// fixed multi-use func_explodeobjects
// 
// 21    7/06/00 3:26p Markd
// added rock to func_explodeobject
// 
// 20    6/27/00 5:46p Steven
// Added some CacheResource calls to make sure explosions are cached correctly.
// 
// 19    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 18    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 17    5/27/00 3:32p Markd
// 2nd pass save games 
// 
// 16    4/21/00 3:01p Markd
// fixed up explode_object explosions
// 
// 15    4/18/00 5:57p Markd
// fixed multi arg support for debris models
// 
// 14    4/18/00 4:20p Markd
// added random scale ability to func_explodeobject and func_multiexploder
// 
// 13    4/18/00 4:01p Markd
// fixed up explosions
// 
// 12    2/07/00 4:21p Markd
// Added "thread" to quaked sections for better documentation
// 
// 11    2/03/00 9:33a Markd
// added VISIBLE flag to func_multi_exploder and func_explodeobject
// 
// 10    2/02/00 7:18p Markd
// fixed some commented out code
// 
// 9     2/02/00 7:14p Markd
// Added func_explodeobject and TossObject
// 
// 8     2/01/00 5:41p Markd
// Made Multi-Exploder multi-use
// 
// 7     1/12/00 6:16p Jimdose
// rewrote CreateExplosion
// 
// 6     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 5     11/12/99 11:47a Markd
// Added sound manager support and retro-fitted TriggerSpeaker and TriggerMusic
// to work with everything
// 
// 4     11/01/99 6:11p Steven
// Changed some old attenuation stuff to min dist stuff.
// 
// 3     9/29/99 5:18p Steven
// Event formatting.
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 20    8/28/99 11:44a Steven
// Removed global from sound function calls.
// 
// 19    8/18/99 3:28p Jimdose
// added cylindrical collision detection
// 
// 18    8/03/99 3:37p Aldie
// Removed some old explosion stuff
// 
// 17    7/30/99 6:24p Aldie
// Updated weapons and utils to use new methods
// 
// 16    7/30/99 3:00p Steven
// New temporary stuff for gas explosions.
// 
// 15    6/11/99 1:23p Phook
// 
// 14    6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
// 
// 13    6/11/99 12:46p Phook
// EClass color changes
//
// DESCRIPTION:
// Standard explosion object that is spawned by other entites and not map designers.
// Explosion is used by many of the weapons for the blast effect, but is also used
// by the Exploder and MultiExploder triggers.  These triggers create one or more
// explosions each time they are activated.
//

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "explosion.h"
#include "weaputils.h"

#define MULTI_USE       (1<<0)
#define RANDOM_TIME     (1<<1)
#define VISIBLE         (1<<2)
#define RANDOM_SCALE    (1<<3)
#define NO_EXPLOSIONS   (1<<4)

Event EV_Exploder_SetDmg
	( 
	"dmg",
	EV_DEFAULT,
   "i",
   "damage",
   "Sets the damage the explosion does."
	);
Event EV_Exploder_SetDuration
	( 
	"duration",
	EV_DEFAULT,
   "f",
   "duration",
   "Sets the duration of the explosion."
	);
Event EV_Exploder_SetWait
	( 
	"wait",
	EV_DEFAULT,
   "f",
   "explodewait",
   "Sets the wait time of the explosion."
	);
Event EV_Exploder_SetRandom
	( 
	"random",
	EV_DEFAULT,
   "f",
   "randomness",
   "Sets the randomness value of the explosion."
	);

void CreateExplosion
   (
   Vector pos,
   float  damage,
   Entity *inflictor,
   Entity *attacker,
   Entity *ignore,
   const char *explosionModel,
   float  scale
   )

   {
   Explosion   *explosion;
   Event       *ev;

   assert( inflictor );

   if ( !inflictor )
      {
      return;
      }

   if ( !attacker )
      {
      attacker = world;
      }

   if ( !explosionModel )
      {
      explosionModel = "fx_explosion.tik";
      }

	explosion = new Explosion;
   	
   // Create a new explosion entity and set it off
   explosion->setModel( explosionModel );

   explosion->setSolidType( SOLID_NOT );
   explosion->CancelEventsOfType( EV_ProcessInitCommands );
   explosion->ProcessInitCommands( explosion->edict->s.modelindex );

   explosion->owner             = attacker->entnum;
	explosion->edict->ownerNum   = attacker->entnum;
	explosion->setMoveType( MOVETYPE_FLYMISSILE );
	explosion->edict->clipmask = MASK_PROJECTILE;
	explosion->setSize( explosion->mins, explosion->maxs );
   explosion->setOrigin( pos );
   explosion->origin.copyTo( explosion->edict->s.origin2 );

   if ( explosion->dlight_radius )
      {
      G_SetConstantLight( &explosion->edict->s.constantLight,
                          &explosion->dlight_color[0],
                          &explosion->dlight_color[1],
                          &explosion->dlight_color[2],
                          &explosion->dlight_radius
                        );
      }

   explosion->BroadcastSound();

   explosion->RandomAnimate( "idle", EV_StopAnimating );
   RadiusDamage( inflictor, attacker, damage, ignore, MOD_EXPLOSION );

	if ( explosion->life )
		{
		ev = new Event( EV_Remove );
		explosion->PostEvent( ev, explosion->life );
		}
   }


/*****************************************************************************/
/*QUAKED func_exploder (0 0.25 0.5) (0 0 0) (8 8 8)

  Spawns an explosion when triggered.  Triggers any targets.

  "dmg" specifies how much damage to cause. Default indicates 120.
  "key" The item needed to activate this. (default nothing)
  "thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.
******************************************************************************/

CLASS_DECLARATION( Trigger, Exploder, "func_exploder" )
	{
		{ &EV_Touch,				         NULL },
		{ &EV_Trigger_Effect,	         MakeExplosion },
      { &EV_Exploder_SetDmg,	         SetDmg },
		{ NULL, NULL }
	};

void Exploder::MakeExplosion
	(
	Event *ev
	)

	{
   CreateExplosion
      (
      origin,
      damage,
      this,
      ev->GetEntity( 1 ),
      this
      );
	}

Exploder::Exploder()
	{
	damage      = 120;
	respondto   = TRIGGER_PLAYERS | TRIGGER_MONSTERS | TRIGGER_PROJECTILES;
	}

void Exploder::SetDmg
   (
   Event *ev
   )

   {
   damage = ev->GetInteger( 1 );
	if ( damage < 0 )
		{
		damage = 0;
		}
   }

/*****************************************************************************/
/*QUAKED func_multi_exploder (0 0.25 0.5) ? MULTI_USE RANDOM_TIME VISIBLE RANDOM_SCALE

  Spawns an explosion when triggered.  Triggers any targets.
  size of brush determines where explosions will occur.

  "dmg" specifies how much damage to cause from each explosion. (Default 120)
  "delay" delay before exploding (Default 0 seconds)
  "duration" how long to explode for (Default 1 second)
  "wait" time between each explosion (default 0.25 seconds)
  "random" random factor (default 0.25)
  "key" The item needed to activate this. (default nothing)
  "thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.
  "health" makes the object damageable
  "scale" set the maximum size for spawned debris and explosions.

  MULTI_USE allows the func_multi_exploder to be used more than once
  RANDOM_TIME adjusts the wait between each explosion by the random factor
  VISIBLE allows you to make the trigger visible
  RANDOM_SCALE scale explosions randomly. size will be between 0.25 and 1 times scale

******************************************************************************/

CLASS_DECLARATION( Trigger, MultiExploder, "func_multi_exploder" )
	{
		{ &EV_Touch,				         NULL },
		{ &EV_Trigger_Effect,	         MakeExplosion },
      { &EV_Exploder_SetDmg,	         SetDmg },
      { &EV_Exploder_SetDuration,      SetDuration },
      { &EV_Exploder_SetWait,	         SetWait },
      { &EV_Exploder_SetRandom,	      SetRandom },
		{ NULL, NULL }
	};

void MultiExploder::MakeExplosion
	(
	Event *ev
	)

	{
	Vector pos;
	float t, scale;
   Entity *other;
   Event *event;

	other = ev->GetEntity( 1 );

   // make sure other is valid
   if ( !other )
      {
      other = world;
      }

	// prevent the trigger from triggering again
	trigger_time = -1;

	if ( !explode_time )
		{
      hideModel();
		explode_time = level.time + duration;
		}

	if ( spawnflags & RANDOM_TIME )
		{
		t = explodewait * ( 1 + G_CRandom( randomness ) );
		}
	else
		{
		t = explodewait;
		}

	event = new Event( EV_Trigger_Effect );
	event->AddEntity( other );
   PostEvent( event, t );

	if ( level.time > explode_time )
		{
      if ( spawnflags & MULTI_USE )
         {
         //
         // reset the trigger in a half second
         //
         trigger_time = level.time + 0.5f;
         explode_time = 0;
         CancelEventsOfType( EV_Trigger_Effect );
         //
         // reset health if necessary
         //
         health = max_health;
         return;
         }
      else
         {
		   PostEvent( EV_Remove, 0 );
		   return;
         }
		}

	pos[ 0 ] = absmin[ 0 ] + G_Random( absmax[ 0 ] - absmin[ 0 ] );
	pos[ 1 ] = absmin[ 1 ] + G_Random( absmax[ 1 ] - absmin[ 1 ] );
	pos[ 2 ] = absmin[ 2 ] + G_Random( absmax[ 2 ] - absmin[ 2 ] );

   if ( spawnflags & RANDOM_SCALE )
      {
      scale = edict->s.scale * 0.25f;
      scale += G_Random( 3 * scale );
      }
   else
      {
      scale = 1.0f;
      }

   CreateExplosion
      (
      pos,
      damage,
      this,
      other,
      this,
      NULL,
      scale
      );
	}

MultiExploder::MultiExploder()
	{
   if ( LoadingSavegame )
      {
      return;
      }

	damage         = 120;
	duration			= 1.0;
	explodewait		= 0.25;
	randomness		= 0.25;
	explode_time	= 0;

   if ( spawnflags & VISIBLE )
      {
      PostEvent( EV_Show, EV_POSTSPAWN );
      }
   else
      {
      PostEvent( EV_Hide, EV_POSTSPAWN );
      }

	// So that we don't get deleted after we're triggered
	count = -1;

	respondto = TRIGGER_PLAYERS | TRIGGER_MONSTERS | TRIGGER_PROJECTILES;
	}

void MultiExploder::SetDmg
   (
   Event *ev
   )

   {
   damage = ev->GetInteger( 1 );
	if ( damage < 0 )
		{
		damage = 0;
		}
   }

void MultiExploder::SetDuration
   (
   Event *ev
   )

   {
	duration = ev->GetFloat( 1 );
   }

void MultiExploder::SetWait
   (
   Event *ev
   )

   {
	explodewait = ev->GetFloat( 1 );
   }

void MultiExploder::SetRandom
   (
   Event *ev
   )

   {
	randomness = ev->GetFloat( 1 );
   }


#define METAL_DEBRIS (1<<5)
#define ROCK_DEBRIS  (1<<6)
#define NOTSOLID     (1<<7)

/*****************************************************************************/
/*QUAKED func_explodeobject (0 0.25 0.5) ? MULTI_USE RANDOM_TIME VISIBLE RANDOM_SCALE NO_EXPLOSIONS METAL_DEBRIS ROCK_DEBRIS NOTSOLID

  Spawns different kinds of debris when triggered.  Triggers any targets.
  size of brush determines where explosions and debris will be spawned.

  "dmg" specifies how much damage to cause from each explosion. (Default 120)
  "delay" delay before exploding (Default 0 seconds)
  "duration" how long to explode for (Default 1 second)
  "wait" time between each explosion (default 0.25 seconds)
  "random" random factor (default 0.25)
  "health" if specified, object must be damaged to trigger
  "key" The item needed to activate this. (default nothing)
  "severity" how violent the debris should be ejected from the object( default 1.0 )
  "debrismodel" What kind of debris to spawn (default nothing)
  "amount" how much debris to spawn for each explosion (default 4)
  "thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.
  "health" makes the object damageable
  "scale" set the maximum size for spawned debris and explosions

  MULTI_USE allows the func_explodeobject to be used more than once
  RANDOM_TIME adjusts the wait between each explosion by the random factor
  VISIBLE allows you to make the trigger visible
  RANDOM_SCALE scale explosions and debris randomly. size will be between 0.25 and 1 times scale
  NO_EXPLOSIONS, if checked no explosions will be created
  METAL_DEBRIS automatically spawn metal debris, no need for debrismodel to be set
  ROCK_DEBRIS automatically spawn rock debris, no need for debrismodel to be set
  NOTSOLID debris is not solid

  other valid tiki files include:

  obj_debris_glass1-4.tik
  obj_debris_wood1-4.tik

******************************************************************************/

Event EV_ExplodeObject_SetSeverity
	( 
	"severity",
	EV_DEFAULT,
   "f",
   "newSeverity",
   "How violently the debris should be ejected."
	);

Event EV_ExplodeObject_SetDebrisModel
	( 
	"debrismodel",
	EV_DEFAULT,
   "s",
   "debrisModel",
   "What kind of debris to spawn when triggered."
	);

Event EV_ExplodeObject_SetDebrisAmount
	( 
	"amount",
	EV_DEFAULT,
   "i",
   "amountOfDebris",
   "How much debris to spawn each time."
	);


CLASS_DECLARATION( MultiExploder, ExplodeObject, "func_explodeobject" )
	{
		{ &EV_Touch,				               NULL },
		{ &EV_Trigger_Effect,	               MakeExplosion },
		{ &EV_ExplodeObject_SetSeverity,       SetSeverity },
		{ &EV_ExplodeObject_SetDebrisModel,    SetDebrisModel },
		{ &EV_ExplodeObject_SetDebrisAmount,   SetDebrisAmount },
		{ NULL, NULL }
	};

void ExplodeObject::SetDebrisModel
   (
   Event *ev
   )

   {
   char   string[ 1024 ];
   const char *ptr;

   // there could be multiple space delimited models, so we need to search for the spaces.
   strcpy( string,  ev->GetString( 1 ) );
   ptr = strtok( string, " " );
   while ( ptr )
      {
      debrismodels.AddUniqueObject( str( ptr ) );
		CacheResource( ptr, this );
      ptr = strtok( NULL, " " );
      }
   }

void ExplodeObject::SetSeverity
   (
   Event *ev
   )

   {
	severity = ev->GetFloat( 1 );
   }

void ExplodeObject::SetDebrisAmount
   (
   Event *ev
   )

   {
	debrisamount = ev->GetInteger( 1 );
   }

void ExplodeObject::MakeExplosion
	(
	Event *ev
	)

	{
	Vector pos;
	float t, scale;
   Entity *other;
   Event *event;

	other = ev->GetEntity( 1 );

   // make sure other is valid
   if ( !other )
      {
      other = world;
      }

	// prevent the trigger from triggering again
	trigger_time = -1;

	if ( !explode_time )
		{
      setSolidType( SOLID_NOT );
      hideModel();
		explode_time = level.time + duration;
		}

	if ( spawnflags & RANDOM_TIME )
		{
		t = explodewait * ( 1 + G_CRandom( randomness ) );
		}
	else
		{
		t = explodewait;
		}

	event = new Event( EV_Trigger_Effect );
	event->AddEntity( other );
   PostEvent( event, t );

	if ( level.time > explode_time )
		{
      if ( spawnflags & MULTI_USE )
         {
         //
         // reset the trigger in a half second
         //
         trigger_time = level.time + 0.5f;
         explode_time = 0;
         CancelEventsOfType( EV_Trigger_Effect );
         //
         // reset health if necessary
         //
         health = max_health;
         if ( health )
            {
   		   setSolidType( SOLID_BBOX );
            }
         if ( spawnflags & VISIBLE )
            {
            PostEvent( EV_Show, 0.5f );
            }
         return;
         }
      else
         {
		   PostEvent( EV_Remove, 0 );
		   return;
         }
		}

	pos[ 0 ] = absmin[ 0 ] + G_Random( absmax[ 0 ] - absmin[ 0 ] );
	pos[ 1 ] = absmin[ 1 ] + G_Random( absmax[ 1 ] - absmin[ 1 ] );
	pos[ 2 ] = absmin[ 2 ] + G_Random( absmax[ 2 ] - absmin[ 2 ] );

   if ( spawnflags & RANDOM_SCALE )
      {
      scale = edict->s.scale * 0.25f;
      scale += G_Random( 3 * scale );
      }
   else
      {
      scale = 1.0f;
      }

   if ( !( spawnflags & NO_EXPLOSIONS ) )
      {
      CreateExplosion
         (
         pos,
         damage,
         this,
         other,
         this,
         NULL,
         scale
         );
      }
   if ( debrismodels.NumObjects() )
      {
      TossObject *to;
      int i;
      for ( i = 0; i < debrisamount; i++ )
         {
         int num;

         if ( spawnflags & RANDOM_SCALE )
            {
            scale = edict->s.scale * 0.25f;
            scale += G_Random( 3 * scale );
            }
         else
            {
            scale = 1.0f;
            }

         num = G_Random( debrismodels.NumObjects() ) + 1;
         to = new TossObject( debrismodels.ObjectAt( num ) );
         to->setScale( scale );
         to->setOrigin( pos );
         to->SetVelocity( severity );
         if ( spawnflags & NOTSOLID )
            {
            to->setSolidType( SOLID_NOT );
            }
	      pos[ 0 ] = absmin[ 0 ] + G_Random( absmax[ 0 ] - absmin[ 0 ] );
	      pos[ 1 ] = absmin[ 1 ] + G_Random( absmax[ 1 ] - absmin[ 1 ] );
	      pos[ 2 ] = absmin[ 2 ] + G_Random( absmax[ 2 ] - absmin[ 2 ] );
         }
      }

	}

ExplodeObject::ExplodeObject()
	{
   if ( !LoadingSavegame )
      {
	   duration			= 1;
	   explodewait		= 0.25f;
      severity       = 1.0f;
      debrismodels.ClearObjectList();
      debrisamount   = 2;
      if ( spawnflags & METAL_DEBRIS )
         {
         debrismodels.AddUniqueObject( str( "obj_debris_metal1.tik" ) );
         debrismodels.AddUniqueObject( str( "obj_debris_metal2.tik" ) );
         debrismodels.AddUniqueObject( str( "obj_debris_metal3.tik" ) );
			CacheResource( "obj_debris_metal1.tik", this );
			CacheResource( "obj_debris_metal2.tik", this );
			CacheResource( "obj_debris_metal3.tik", this );
         }
      else if ( spawnflags & ROCK_DEBRIS )
         {
         debrismodels.AddUniqueObject( str( "obj_debris_rock1.tik" ) );
         debrismodels.AddUniqueObject( str( "obj_debris_rock2.tik" ) );
         debrismodels.AddUniqueObject( str( "obj_debris_rock3.tik" ) );
         debrismodels.AddUniqueObject( str( "obj_debris_rock4.tik" ) );
			CacheResource( "obj_debris_rock1.tik", this );
			CacheResource( "obj_debris_rock2.tik", this );
			CacheResource( "obj_debris_rock3.tik", this );
			CacheResource( "obj_debris_rock4.tik", this );
         }
      }
	}

