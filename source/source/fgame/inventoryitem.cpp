//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/inventoryitem.cpp                  $
// $Revision:: 7                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 7/01/00 7:02p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/inventoryitem.cpp                       $
// 
// 7     7/01/00 7:02p Steven
// Fixed the antisucknblaugh name so it would match the classname.
// 
// 6     6/26/00 5:50p Markd
// re-did some renderfx commands, fixed anti-sb juice stuff
// 
// 5     6/24/00 11:19a Steven
// Made the anti sucknblaugh juice item set its item name.
// 
// 4     6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 3     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 2     9/29/99 5:18p Steven
// Event formatting.
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 6     9/01/99 8:17p Steven
// Fixed some typos.
// 
// 5     8/27/99 5:06p Steven
// Added anit Sucknblaugh juice powerup.
// 
// DESCRIPTION:
// Inventory items

#include "inventoryitem.h"

Event EV_InventoryItem_Use
	( 
	"useinvitem",
	EV_DEFAULT,
   NULL,
   NULL,
   "Use this inventory item."
	);

CLASS_DECLARATION( Item, InventoryItem, NULL )
	{
      { &EV_InventoryItem_Use,         UseEvent },
      { NULL, NULL }
   };

InventoryItem::InventoryItem
   (
   )

   {
   if ( LoadingSavegame )
      {
      return;
      }

   // All powerups are inventory items
   if ( DM_FLAG( DF_NO_POWERUPS ) )
	   {
	   PostEvent( EV_Remove, EV_REMOVE );
	   return;
	   }
   }

void InventoryItem::UseEvent
   (
   Event *ev
   )

   {
   }

Event EV_AntiSBJuice_Wearoff
	( 
	"antiSBjuice_wearoff",
	EV_DEFAULT,
   NULL,
   NULL,
   "Is called when the effect wears off."
	);

CLASS_DECLARATION( InventoryItem, AntiSBJuice, "AntiSBJuice" )
	{
      { &EV_AntiSBJuice_Wearoff,				Wearoff },
		{ &EV_Use, 									UseEvent },
      { NULL, NULL }
   };

AntiSBJuice::AntiSBJuice
	(
	)

	{
	PostEvent( EV_Use, 0 );
	item_name = "AntiSBJuice";
	}

void AntiSBJuice::UseEvent
	(
	Event *ev
	)
	{
	if ( !owner )
      {
      CancelPendingEvents();
      PostEvent( EV_Remove, 0 );
      return;
      }

   owner->edict->s.eFlags |= EF_ANTISBJUICE;

	PostEvent( EV_AntiSBJuice_Wearoff, 30.0 );
	}

void AntiSBJuice::Wearoff
	(
	Event *ev
	)

	{
	if ( !owner )
      {
      CancelPendingEvents();
      PostEvent( EV_Remove, 0 );
      return;
      }

   owner->edict->s.eFlags &= ~EF_ANTISBJUICE;

	CancelPendingEvents();
   PostEvent( EV_Remove, 0 );
	}
