//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/flamethrower.cpp                   $
// $Revision:: 6                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/23/00 8:41p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/flamethrower.cpp                        $
// 
// 6     6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 5     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 4     5/06/00 2:06p Steven
// Fixed a precendence bug.
// 
// 3     5/05/00 5:17p Aldie
// comment
// 
// 2     5/05/00 5:17p Aldie
// Flamethrower
//
// DESCRIPTION:
// Flamethrower weapon

#include "flamethrower.h"

CLASS_DECLARATION( Weapon, Flamethrower, NULL )
	{
		{ NULL, NULL }
	};

Flamethrower::Flamethrower
   (
   )

   {
   // Attach the gasoline model to the flamethrower
   Event *ev;

   if ( LoadingSavegame )
      {
      return;
      }

   ev = new Event ( EV_AttachModel );
   ev->AddString( "weapon_flamethrowergas.tik" );
	ev->AddString( "tag_gas" );

   PostEvent( ev, FRAMETIME );

   m_gas = NULL;
   }

void Flamethrower::Shoot
   (
   Event *ev
   )

   {
   firemode_t  mode = FIRE_PRIMARY;
   
   if ( ev->NumArgs() > 0 )
      {
      mode = WeaponModeNameToNum( ev->GetString( 1 ) );

      if ( mode == FIRE_ERROR )
         return;
      }

   // Find a pointer to the gas 
   if ( !m_gas )
      {
      if ( numchildren == 1 ) 
         {
         m_gas = ( Animate * )G_GetEntity( children[ 0 ] );
         m_gas->RandomAnimate( "gas" );
         m_gas->StopAnimating();
         m_gas->SetFrame( 0 );
         }
      }
   // Check the ammo level and see if we need to adjust the gas animation

   if ( owner && m_gas )
      {
      int amount        = owner->AmmoCount( ammo_type[mode] );
      int maxamount     = owner->MaxAmmoCount( ammo_type[mode] );
      float percentage  = 1.0f - ( ( float )amount / ( float )maxamount );
      int numframes     = m_gas->NumFrames();
      
      m_gas->SetFrame( percentage * ( numframes - 1 ) );

      if ( percentage >= 1 )
         m_gas->hideModel();
      else
         m_gas->showModel();
      }

   Weapon::Shoot( ev );
   }
