//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/shield.cpp                         $
// $Revision:: 4                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 7/06/00 1:26p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/shield.cpp                              $
// 
// 4     7/06/00 1:26p Steven
// Made shield impact effect get played at max 4 times a second.
// 
// 3     2/20/00 2:56p Aldie
// Added shield impact function
// 
// 2     2/16/00 4:01p Aldie
// Added shield functionality
//
// DESCRIPTION:
// FAKK Shields

#include "shield.h"
#include "player.h"

Event EV_Shield_DamageReduction
	( 
	"damage_reduction", 
	EV_CHEAT,
   "f",
   "percent",
   "Set the percentage to reduce the amount of damage a sentient takes."
	);

CLASS_DECLARATION( Weapon, Shield, NULL )
	{
      { &EV_Shield_DamageReduction,    DamageReduction },
		{ NULL, NULL }
	};

Shield::Shield
   (
   )

   {
   damage_reduction_percentage = 0.5f;
	last_impact_time = 0;
   }

void Shield::DamageReduction
   (
   Event *ev
   )

   {
   damage_reduction_percentage = ev->GetFloat( 1 );
   }

float Shield::GetDamageReduction
   (
   void
   )

   {
   return damage_reduction_percentage;
   }

void Shield::Impact
   (
   void
   )

   {
	if ( last_impact_time + 0.25 <= level.time )
		{
		RandomAnimate( "impact", NULL );
		last_impact_time = level.time;
		}
   }
