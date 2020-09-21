//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/armor.cpp                          $
// $Revision:: 5                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/23/00 8:41p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/armor.cpp                               $
// 
// 5     6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 4     6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 3     1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
// 
// 2     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
//
// DESCRIPTION:
// Standard armor that prevents a percentage of damage per hit.
// 

#include "g_local.h"
#include "armor.h"

CLASS_DECLARATION( Item, Armor, NULL )
	{
		{ NULL, NULL }
	};

Armor::Armor()
	{
   if ( LoadingSavegame )
      {
      // no need to proceed if loading a game
      return;
      }

	if ( DM_FLAG( DF_NO_ARMOR ) )
		{
		PostEvent( EV_Remove, EV_REMOVE );
		return;
		}

   setAmount( 0 );
	}

void Armor::Setup
	(
	const char *model,
	int amount
	)

	{
	assert( model );
	setModel( model );
   setAmount( amount );
   }

void Armor::Add
	(
	int num
	)

	{
   // Armor never adds, it only replaces
	amount = num;
   if ( amount >= MaxAmount() )
      {
      amount = MaxAmount();
      }
	}

qboolean Armor::Pickupable
   (
   Entity *other
   )

   {
	if ( !other->isSubclassOf( Sentient ) )
		{
		return false;
		}
   else
      {
      Sentient * sent;
      Item * item;

      sent = ( Sentient * )other;
      item = sent->FindItem( getName() );

      // If our armor is > than our current armor or armor has no value, then leave it alone.
      if ( item && ( ( item->getAmount() >= this->getAmount() ) || !this->getAmount() ) )
         {
         return false;
         }
      }
   return true;
   }
