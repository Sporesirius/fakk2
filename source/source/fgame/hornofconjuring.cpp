//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/hornofconjuring.cpp                $
// $Revision:: 4                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 2:17p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/hornofconjuring.cpp                     $
// 
// 4     6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 3     5/31/00 2:47p Aldie
// Added first vymish
// 
// 2     5/30/00 7:33p Aldie
// First version
//
// DESCRIPTION:
// Horn of Conjuring Weapon

#include "hornofconjuring.h"

CLASS_DECLARATION( Weapon, HornOfConjuring, NULL )
	{
		{ NULL, NULL }
	};

HornOfConjuring::HornOfConjuring
   (
   )

   {
   }

void HornOfConjuring::Shoot
   (
   Event *ev
   )

   {
   firemode_t  mode = FIRE_PRIMARY;
   Vector      pos,forward,right,up;
   
   if ( ev->NumArgs() > 0 )
      {
      mode = WeaponModeNameToNum( ev->GetString( 1 ) );

      if ( mode == FIRE_ERROR )
         return;
      }

   if ( !MuzzleClear() )
      {
      RandomAnimate( "clear", NULL );
      weaponstate = WEAPON_READY;
      return;
      }

   GetMuzzlePosition( &pos, &forward, &right, &up );

   ActorPtr actor;
   actor = new Actor;
   actor->setModel( "vymish_conjured.tik" );
   actor->setOrigin( pos );

   m_creatureList.AddObject( actor );

	if ( !quiet )
		{
		if ( next_noise_time <= level.time )
			{
			BroadcastSound();
			next_noise_time = level.time + 1;
			}
		}
   }

