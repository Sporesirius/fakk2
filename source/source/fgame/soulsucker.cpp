//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/soulsucker.cpp                     $
// $Revision:: 9                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 7/22/00 1:23p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/soulsucker.cpp                          $
// 
// 9     7/22/00 1:23p Steven
// Took out the water factor thing.
// 
// 8     7/16/00 4:38p Steven
// Moved action level stuff to actor pain and killed.
// 
// 7     7/14/00 8:28p Aldie
// Added waterfactor to soulsucker
// 
// 6     6/07/00 3:09p Steven
// Only update some stuff if damage_total is above 0.
// 
// 5     6/01/00 7:45p Aldie
// Heatseeking and Drunkeness added to projectiles
// 
// 4     5/30/00 7:33p Aldie
// Removed unused code
// 
// 3     5/26/00 6:31p Aldie
// Added alternate fire to soulsucker and bug fix to AmmoAvailable()
// 
// 2     5/22/00 5:13p Aldie
// First version of soulsucker
//
// DESCRIPTION:
// Soulsucker weapon

#include "soulsucker.h"
#include "player.h"

Event EV_Soulsucker_WaterFactor
   (
   "waterfactor",
   EV_DEFAULT,
   "f",
   "factor",
   "Factor by which to scale the amount of water the player gets from shooting the gun"
   );


CLASS_DECLARATION( Weapon, Soulsucker, NULL )
	{
      { &EV_Soulsucker_WaterFactor,    WaterFactor },
		{ NULL, NULL }
	};

Soulsucker::Soulsucker
   (
   )

   {
   }

void Soulsucker::WaterFactor
   (
   Event *ev
   )

   {
   m_waterfactor = ev->GetFloat( 1 );
   }

void Soulsucker::Shoot
   (
   Event *ev
   )

   {
   firemode_t  mode = FIRE_PRIMARY;
   Vector      pos,forward,right,up;
   float       damage_total=0;

   if ( ev->NumArgs() > 0 )
      {
      mode = WeaponModeNameToNum( ev->GetString( 1 ) );

      if ( mode == FIRE_ERROR )
         return;
      }

   // If we are in loopfire, we need to keep checking ammo and using it up
   if ( loopfire[mode] )
      {
      if ( HasAmmo( mode ) && MuzzleClear() )
         {
         // Use up the appropriate amount of ammo, it's already been checked that we have enough
         UseAmmo( ammorequired[mode], mode );
         }
      else
         {
         ForceIdle();
         }
      }

   if ( !MuzzleClear() )
      {
      RandomAnimate( "clear", NULL );
      weaponstate = WEAPON_READY;
      return;
      }

   GetMuzzlePosition( &pos, &forward, &right, &up );

   if ( mode == FIRE_ALTERNATE )
      {
      ProjectileAttack( pos, forward, owner, projectileModel[mode], 1 ); 
      }
   else if ( mode == FIRE_PRIMARY )
      {
      damage_total = BulletAttack( pos,
                                   forward,
                                   right,
                                   up,
                                   bulletrange[mode],
                                   bulletdamage[mode],
                                   bulletknockback[mode],
                                   0, 
			                          GetMeansOfDeath( mode ),
                                   bulletspread[mode],
                                   bulletcount[mode],
                                   owner );
      if ( owner && owner->isSubclassOf( Player ) )
		   {
		   Player *player = (Player *)(Sentient *)owner;

			if ( damage_total > 0 )
				{
				// Add damage to player's water total
				//player->SetWaterPower( player->GetWaterPower() + ( damage_total * m_waterfactor ) );

				player->SetWaterPower( player->GetWaterPower() + damage_total );

				// Give the player soul ammo to power the alternate fire mode
				player->GiveAmmo( ammo_type[ FIRE_ALTERNATE ], damage_total );
				}
		   }
      }

	if ( !quiet )
		{
		if ( next_noise_time <= level.time )
			{
			BroadcastSound();
			next_noise_time = level.time + 1;
			}
		}
   }
