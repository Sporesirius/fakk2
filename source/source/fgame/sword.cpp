//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/sword.cpp                          $
// $Revision:: 9                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 7/12/00 3:21p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/sword.cpp                               $
// 
// 9     7/12/00 3:21p Aldie
// Added alternate modes to sword
// 
// 8     6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 7     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 6     3/30/00 2:48p Steven
// Added knockback stuff.
// 
// 5     3/30/00 2:09p Aldie
// Added hitspawn command
// 
// 4     2/04/00 11:49a Aldie
// Fix for poweron/off
// 
// 3     2/03/00 2:56p Aldie
// Sword and water coding
// 
// 2     2/02/00 7:08p Aldie
// Added new sword code and water damage
//
// DESCRIPTION:
// FAKK Swords

#include "sword.h"
#include "player.h"

Event EV_Sword_WaterRequired
  (
  "water_required",
  EV_DEFAULT,
  "i",
  "amount",
  "Set the amount of water this sword requires to operate at full strength"
  );

Event EV_Sword_WaterDamage
  (
  "water_damage",
  EV_DEFAULT,
  "f",
  "amount",
  "Set the amount of damage the sword does when using water"
  );

Event EV_Sword_BasicDamage
  (
  "basic_damage",
  EV_DEFAULT,
  "f",
  "amount",
  "Set the amount of basic damage the sword does without water"
  );

Event EV_Sword_WaterKnockback
  (
  "water_knockback",
  EV_DEFAULT,
  "f",
  "amount",
  "Set the amount of knockback the sword does when using water"
  );

Event EV_Sword_BasicKnockback
  (
  "basic_knockback",
  EV_DEFAULT,
  "f",
  "amount",
  "Set the amount of basic knockback the sword does without water"
  );

Event EV_Sword_HitSpawn
   (
   "hitspawn",
   EV_DEFAULT,
   "s",
   "model",
   "Set a model to spawn when the sword hits an enemy"
   );

CLASS_DECLARATION( Weapon, Sword, NULL )
	{
      { &EV_Sword_WaterRequired,    SetWaterRequiredEvent },
      { &EV_Sword_BasicDamage,      SetBasicDamageEvent },
      { &EV_Sword_WaterDamage,      SetWaterDamageEvent },
		{ &EV_Sword_BasicKnockback,   SetBasicKnockbackEvent },
      { &EV_Sword_WaterKnockback,   SetWaterKnockbackEvent },
      { &EV_Sword_HitSpawn,         SetHitSpawn },
		{ NULL, NULL }
	};

Sword::Sword
   (
   )

   {
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

   INITIALIZE_WEAPONMODE_VAR( waterRequired, 0 );
   INITIALIZE_WEAPONMODE_VAR( basicDamage, 25 );
   INITIALIZE_WEAPONMODE_VAR( waterDamage, 50);
   INITIALIZE_WEAPONMODE_VAR( poweractive, qfalse );
   INITIALIZE_WEAPONMODE_VAR( basicKnockback, 50);
   INITIALIZE_WEAPONMODE_VAR( waterKnockback, 50);
   }

void Sword::HitSpawn
   (
   Vector origin,
   firemode_t mode
   )

   {
   assert( ( mode >= 0 ) && ( mode < MAX_FIREMODES ) );
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::HitSpawn", "Invalid mode %d\n", mode );
      return;
      }

   Animate *ent;

   ent = new Animate;
   ent->setModel( hitspawn[mode] );
   ent->setMoveType( MOVETYPE_NONE );
   ent->RandomAnimate( "idle" );
   ent->setOrigin( origin );
   
   ent->PostEvent( EV_Remove, 1 );
   }

void Sword::SetHitSpawn
   (
   Event *ev
   )

   {
   assert( ( firemodeindex >= 0 ) && ( firemodeindex < MAX_FIREMODES ) );
   hitspawn[firemodeindex] = ev->GetString( 1 );
   }

void Sword::SetWaterDamageEvent
   (
   Event *ev
   )

   {
   assert( ( firemodeindex >= 0 ) && ( firemodeindex < MAX_FIREMODES ) );
   waterDamage[firemodeindex] = ev->GetFloat( 1 );
   }

void Sword::SetWaterDamage
   (
   float amount,
   firemode_t mode
   )

   {
   assert( ( mode >= 0 ) && ( mode < MAX_FIREMODES ) );
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::SetWaterDamage", "Invalid mode %d\n", mode );
      return;
      }

   waterDamage[mode] = amount;
   }

float Sword::GetWaterDamage
   (
   firemode_t mode
   )

   {
   assert( ( mode >= 0 ) && ( mode < MAX_FIREMODES ) );
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::GetWaterDamage", "Invalid mode %d\n", mode );
      return 0;
      }

   return waterDamage[mode];
   }

void Sword::SetBasicDamageEvent
   (
   Event *ev
   )

   {
   assert( ( firemodeindex >= 0 ) && ( firemodeindex < MAX_FIREMODES ) );
   basicDamage[firemodeindex] = ev->GetFloat( 1 );
   }

void Sword::SetBasicDamage
   (
   float amount,
   firemode_t mode
   )

   {
   assert( ( mode >= 0 ) && ( mode < MAX_FIREMODES ) );
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::SetBasicDamage", "Invalid mode %d\n", mode );
      return;
      }

   basicDamage[mode] = amount;
   }

float Sword::GetBasicDamage
   (
   firemode_t mode
   )

   {
   assert( ( mode >= 0 ) && ( mode < MAX_FIREMODES ) );
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::GetBasicDamage", "Invalid mode %d\n", mode );
      return 0;
      }

   return basicDamage[mode];
   }

void Sword::SetWaterRequiredEvent
   (
   Event *ev
   )

   {
   assert( ( firemodeindex >= 0 ) && ( firemodeindex < MAX_FIREMODES ) );
   waterRequired[firemodeindex] = ev->GetFloat( 1 );
   }

void Sword::SetWaterRequired
   (
   int amount,
   firemode_t mode
   )

   {
   assert( ( mode >= 0 ) && ( mode < MAX_FIREMODES ) );
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::SetWaterRequired", "Invalid mode %d\n", mode );
      return;
      }

   waterRequired[mode] = amount;
   }

int Sword::GetWaterRequired
   (
   firemode_t mode
   )

   {
   assert( ( mode >= 0 ) && ( mode < MAX_FIREMODES ) );
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::GetWaterRequired", "Invalid mode %d\n", mode );
      return 0;
      }

   return waterRequired[mode];
   }

void Sword::SetBasicKnockbackEvent
   (
   Event *ev
   )

   {
   assert( ( firemodeindex >= 0 ) && ( firemodeindex < MAX_FIREMODES ) );
   basicKnockback[firemodeindex] = ev->GetFloat( 1 );
   }

float Sword::GetBasicKnockback
   (
   firemode_t mode
   )

   {
   assert( ( mode >= 0 ) && ( mode < MAX_FIREMODES ) );
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::GetBasicKnockback", "Invalid mode %d\n", mode );
      return 0;
      }

   return basicKnockback[mode];
   }

void Sword::SetWaterKnockbackEvent
   (
   Event *ev
   )

   {
   assert( ( firemodeindex >= 0 ) && ( firemodeindex < MAX_FIREMODES ) );
   waterKnockback[firemodeindex] = ev->GetFloat( 1 );
   }

float Sword::GetWaterKnockback
   (
   firemode_t mode
   )

   {
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::GetWaterKnockback", "Invalid mode %d\n", mode );
      return 0;
      }

   return waterKnockback[mode];
   }

void Sword::SetPowerOff
   (
   firemode_t mode
   )

   {
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::SetPowerOff", "Invalid mode %d\n", mode );
      return;
      }

   if ( str::icmp( AnimName(), "poweroff" ) )
      RandomAnimate( "poweroff" );
   
   poweractive[mode] = qfalse;
   }

void Sword::SetPowerOn
   (
   firemode_t mode
   )

   {
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::SetPowerOn", "Invalid mode %d\n", mode );
      return;
      }

   if ( str::icmp( AnimName(), "poweron" ) )
      RandomAnimate( "poweron" );
   poweractive[mode] = qtrue;
   }

qboolean Sword::GetPowerActive
   (
   firemode_t mode
   )

   {
   if ( ( mode < 0 ) || ( mode >= MAX_FIREMODES ) )
      {
      warning( "Sword::GetPowerActive", "Invalid mode %d\n", mode );
      return false;
      }

   return poweractive[mode];
   }
