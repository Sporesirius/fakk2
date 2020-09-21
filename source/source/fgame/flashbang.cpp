//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/flashbang.cpp                      $
// $Revision:: 9                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 7/28/00 9:27a                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/flashbang.cpp                           $
// 
// 9     7/28/00 9:27a Steven
// Made it so flashbang projectiles actually animate correctly.
// 
// 8     7/20/00 2:17p Aldie
// Fix for firing the flashbang
// 
// 7     7/17/00 3:26p Aldie
// Fix for flashbangs, changed detail variable, and added forcetorsostate
// 
// 6     4/15/00 5:18p Aldie
// Added stun events and fixed yet another bug with Ammo and AutoPutaway
// 
// 5     4/14/00 6:05p Aldie
// Added some more flashbang functions
// 
// 4     4/13/00 3:45p Aldie
// Added more flashbang support.  Added damage_type to entities used to specify
// what type of damage they take.
// 
// 3     4/07/00 6:00p Aldie
// Added flashing and fixed radius damage for explosions
// 
// 2     4/07/00 4:01p Aldie
// First version
//
// DESCRIPTION:
// Flashbang weapon

#include "flashbang.h"

Event EV_FlashbangProjectile_StunTime
   (
   "stuntime",
   EV_DEFAULT,
   "f",
   "time",
   "Amount of time to stun the target"
   );
Event EV_FlashbangProjectile_StunRadius
   (
   "stunradius",
   EV_DEFAULT,
   "f",
   "radius",
   "Radius of the stun effect"
   );

CLASS_DECLARATION( Projectile, FlashbangProjectile, NULL )
   {   
      { &EV_FlashbangProjectile_StunTime,   StunTime },
      { &EV_FlashbangProjectile_StunRadius, StunRadius },
		{ NULL, NULL }
	};

FlashbangProjectile::FlashbangProjectile
   (
   )

   {
   }

void FlashbangProjectile::StunTime
   (
   Event *ev
   )

   {
   stunTime = ev->GetFloat( 1 );
   }

void FlashbangProjectile::StunRadius
   (
   Event *ev
   )

   {
   stunRadius = ev->GetFloat( 1 );
   }

void FlashbangProjectile::Explode
   (
   Event *ev
   )

   {
   Entity *owner;

   // Get the owner of this projectile
   owner = G_GetEntity( this->owner );

   // If the owner's not here, make the world the owner
   if ( !owner )
      owner = world;

   // When a flashbang explodes, it whites the screen and does some damage
   if ( explosionmodel.length() )
      {
      ExplosionAttack( origin, owner, explosionmodel, Vector( 0,0,0 ), NULL );
      StunAttack( origin, owner, this, this->stunRadius, this->stunTime, NULL );
      }   

   PostEvent( EV_Remove, 0 );
   }


CLASS_DECLARATION( Weapon, Flashbang, NULL )
	{
		{ NULL, NULL }
	};

Flashbang::Flashbang
   (
   )

   {
   }

void Flashbang::SpecialFireProjectile
   (
   Vector pos, 
   Vector forward,
   Vector right,
   Vector up,
   Entity *owner,
   str    projectileModel,
   float  charge_fraction
   )

   {
   // Do a trace forward to see if a solid is hit
   Vector               norm,angles;
   FlashbangProjectile  *fb;
   Event                *ev;
 
   fb = new FlashbangProjectile;
   fb->setModel( projectileModel );
   fb->CancelEventsOfType( EV_ProcessInitCommands );
   fb->ProcessInitCommands( fb->edict->s.modelindex );
   fb->setMoveType( MOVETYPE_NONE );

   fb->owner             = owner->entnum;
	fb->edict->ownerNum   = owner->entnum;
   
   // Explode the flashbang after it's life expires
   ev = new Event( EV_Projectile_Explode );
	fb->PostEvent( ev, fb->life );

   // Spawn a flashbang at the player's feet.
   Vector org = owner->origin + Vector( 0,0,32 );
   Vector end = org + ( forward * 32 );
   trace_t trace = G_Trace( org, vec_zero, vec_zero, end, owner, MASK_SOLID, qfalse, "Flashbang::SpecialFireProjectile" );

   fb->setOrigin( trace.endpos );
   fb->setAngles( Vector( 0, owner->angles[1] + 180, 0 ) );
   fb->droptofloor( 64 );
	fb->RandomAnimate( "idle" );
   }


