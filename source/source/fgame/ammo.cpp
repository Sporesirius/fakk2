//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/ammo.cpp                           $
// $Revision:: 11                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/01/00 4:11p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/ammo.cpp                                $
// 
// 11    7/01/00 4:11p Markd
// added pickup_thread to ammo
// 
// 10    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 9     6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 8     5/22/00 4:41p Steven
// Fixed ammo ItemPickup (had different number of parms from item one).
// 
// 7     4/05/00 7:13p Aldie
// Lots of inventory functionality changes.
// 
// 6     3/02/00 4:43p Aldie
// Added some ammo functionality for the HUD
// 
// 5     1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
// 
// 4     12/03/99 7:02p Aldie
// More ammo joy
// 
// 3     11/29/99 6:32p Aldie
// Lots of changes for ammo system
// 
// 2     11/22/99 6:46p Aldie
// Started working on ammo changes - will finish after Thanksgiving break
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 
// DESCRIPTION:
// Base class for all ammunition for entities derived from the Weapon class.
// 
// AmmoEntity is the Class which represents ammo that the player "sees" and "
// picks up" in the game
//
// Ammo is the Class which is used to keep track of how much ammo a player has 
// in his inventory

#include "ammo.h"
#include "player.h"

CLASS_DECLARATION( Item, AmmoEntity, NULL )
	{
		{ NULL, NULL }
	};

AmmoEntity::AmmoEntity
   (
   )

	{
   if ( LoadingSavegame )
      {
      // all data will be setup by the archive function
      return;
      }
   setName( "UnknownAmmo" );
   amount       = 0;
	}

Item *AmmoEntity::ItemPickup
   (
   Entity *other, 
	qboolean add_to_inventory
   )

   {
   Sentient *player;
	str      realname;

   if ( !other->isSubclassOf( Player ) )
      return NULL;

   player = ( Sentient * )other;

	// Play pickup sound
   realname = GetRandomAlias( "snd_pickup" );
   if ( realname.length() > 1 )
		player->Sound( realname, CHAN_ITEM );

   // Cancel some events
	CancelEventsOfType( EV_Item_DropToFloor );
	CancelEventsOfType( EV_Item_Respawn );
   CancelEventsOfType( EV_FadeOut );

   // Hide the model
	setSolidType( SOLID_NOT );
	hideModel();

   // Respawn?
	if ( !Respawnable() )
		PostEvent( EV_Remove, FRAMETIME );
   else 
		PostEvent( EV_Item_Respawn, RespawnTime() );

   // fire off any pickup_thread's 
   if ( pickup_thread.length() )
      {
      ExecuteThread( pickup_thread );
      }

   // Give the ammo to the player
   player->GiveAmmo( item_name, amount );
   return NULL; // This doesn't create any items
   }


// This is the Class that is used to keep track of ammo in the player's inventory.
// It is not an entit, just a name and an amount.

CLASS_DECLARATION( Class, Ammo, NULL )
   {
      {NULL, NULL}
   };

Ammo::Ammo
   (
   )

   {
   if ( LoadingSavegame )
      {
      // all data will be setup by the archive function
      return;
      }
   setName( "UnknownAmmo" );
   setAmount( 0 );
   setMaxAmount( 100 );
   }

void Ammo::setAmount
   (
   int a
   )

   {
   amount = a;

   if ( ( maxamount > 0 ) && ( amount > maxamount ) )
      amount = maxamount;
   }

int Ammo::getAmount
   (
   void
   )

   {
   return amount;
   }

void Ammo::setMaxAmount
   (
   int a
   )

   {
   maxamount = a;
   }

int Ammo::getMaxAmount
   (
   void
   )

   {
   return maxamount;
   }

void Ammo::setName
   (
   str n
   )

   {
   name = n;
   name_index = gi.itemindex( name );
   }

str Ammo::getName
   (
   void
   )

   {
   return name;
   }

int Ammo::getIndex
   (
   void
   )

   {
   return name_index;
   }
