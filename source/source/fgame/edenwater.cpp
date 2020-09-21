//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/edenwater.cpp                      $
// $Revision:: 12                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/14/00 11:45p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/edenwater.cpp                           $
// 
// 12    7/14/00 11:45p Markd
// Added ambient sounds to func_supllywater
// 
// 11    7/11/00 11:13a Markd
// Took space out of EdenWater item name
// 
// 10    7/01/00 4:10p Markd
// fixed edenwater pickup stuff
// 
// 9     6/27/00 5:59p Markd
// got rid of unused variable
// 
// 8     6/27/00 5:45p Steven
// Made it so water is not picked up if player already has 100.
// 
// 7     4/06/00 3:47p Markd
// added blue shift to water pickup
// 
// 6     4/06/00 11:44a Aldie
// Fix for water so it's not put into the player's inventory
// 
// 5     1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
// 
// 4     1/25/00 4:11p Aldie
// Fix the amount to use the internal variable 
// 
// 3     1/18/00 3:27p Aldie
// Changed startamount to 1
// 
// 2     1/18/00 3:11p Aldie
// First version of edenwater
//
// DESCRIPTION:
// Eden water pickupable item

#include "edenwater.h"
#include "player.h"

CLASS_DECLARATION( Item, EdenWater, "item_edenwater" )
	{
      { &EV_Item_Pickup,   PickupEdenWater },
		{ NULL, NULL }
	};

EdenWater::EdenWater
   (
   )

   {
   setName( "EdenWater" );
   setAmount( 1 );
   }

void EdenWater::PickupEdenWater
	(
	Event *ev
	)
	
	{
	Player   *player;
	Entity   *other;
	str realname;

	other = ev->GetEntity( 1 );

   if ( !other || !other->isSubclassOf( Player ) )
      {
      return;
      }

	player = ( Player * )other;

	if ( player->GetWaterPower() >= 100 )
		return;

   player->SetWaterPower( player->GetWaterPower() + this->amount );

	realname = GetRandomAlias( "snd_pickup" );
   if ( realname.length() > 1 )
		player->Sound( realname, CHAN_ITEM );

   PostEvent( EV_Remove, 0 );

   // fire off any pickup_thread's 
   if ( pickup_thread.length() )
      {
      ExecuteThread( pickup_thread );
      }
 	}
