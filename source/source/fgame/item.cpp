//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/item.cpp                           $
// $Revision:: 31                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 7/19/00 5:08p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/item.cpp                                $
// 
// 31    7/19/00 5:08p Steven
// Added some caching stuff for cool item.
// 
// 30    7/16/00 10:44a Steven
// Added has_been_looked_at stuff.
// 
// 29    7/10/00 8:09p Markd
// fixed cool item pickup problems
// 
// 28    7/04/00 6:45p Markd
// enhanced cool item features
// 
// 27    7/04/00 2:25p Markd
// added cool cinematic for new objects
// 
// 26    6/26/00 12:21p Steven
// Printing out better info on stuck warning.
// 
// 25    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 24    6/17/00 12:05p Steven
// Made it so the player would not look at items that have been picked up and
// not yet respawned.
// 
// 23    6/03/00 5:23p Markd
// fixed bug in saved games, made items have playersolid as their default
// clipmask
// 
// 22    6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 21    5/31/00 5:32p Steven
// Marked these as things for Julie to look at.
// 
// 20    5/30/00 7:06p Markd
// saved games 4th pass
// 
// 19    5/27/00 5:06p Steven
// Added a GetOwner function.
// 
// 18    5/25/00 9:59a Steven
// Fixed some item name stuff.
// 
// 17    5/20/00 5:14p Markd
// Added ITEM special effects
// 
// 16    5/07/00 5:00p Markd
// fixed weapon pickup code
// 
// 15    4/11/00 5:32p Markd
// reworked PickupItem code
// 
// 14    4/06/00 12:14p Aldie
// Added a default name to Item
// 
// 13    4/01/00 2:03p Markd
// overrode use of EV_SetAngle event from trigger
// 
// 12    3/27/00 4:47p Markd
// added pickup_thread capability to all items
// 
// 11    3/13/00 5:18p Aldie
// Made some changes for usable inventory item stuff
// 
// 10    1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
// 
// 9     1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 8     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 7     12/03/99 7:02p Aldie
// More ammo joy
// 
// 6     12/02/99 6:53p Aldie
// Changed naming conventions from "both" to "dualhanded"  Also put in the
// inventory renderer for the hud file
// 
// 5     12/01/99 4:56p Markd
// fixed some reference versus pointer issues with RandomAnimate and NewAnim
// 
// 4     9/29/99 7:43p Markd
// Made items behave better when dropping to floor
// 
// 3     9/29/99 5:17p Steven
// Event formatting.
// 
// 2     9/27/99 5:44p Markd
// began documentation and cleanup phase after merge
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 15    9/02/99 6:44p Jimdose
// removed message when owned item is triggered
// 
// 14    8/28/99 6:40p Steven
// Added more pickup animation and respawn animation stuff.
// 
// 13    8/28/99 11:44a Steven
// Removed global from sound function calls.
// 
// 12    8/27/99 5:07p Steven
// General item work.
//
// DESCRIPTION:
// Base class for respawnable, carryable objects.
//

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "item.h"
#include "inventoryitem.h"
#include "scriptmaster.h"
#include "health.h"

Event EV_Item_Pickup
	( 
	"item_pickup",
	EV_DEFAULT,
   "e",
   "item",
   "Pickup the specified item."
	);
Event EV_Item_DropToFloor
	( 
	"item_droptofloor",
	EV_DEFAULT,
   NULL,
   NULL,
   "Drops the item to the ground."
	);
Event EV_Item_Respawn
	( 
	"respawn",
	EV_DEFAULT,
   NULL,
   NULL,
   "Respawns the item."
	);
Event EV_Item_SetRespawn
	( 
	"set_respawn",
	EV_DEFAULT,
   "i",
   "respawn",
   "Turns respawn on or off."
	);
Event EV_Item_SetRespawnTime
	( 
	"set_respawn_time",
	EV_DEFAULT,
   "f",
   "respawn_time",
   "Sets the respawn time."
	);
Event EV_Item_SetAmount
	( 
	"amount",
	EV_DEFAULT,
   "i",
   "amount",
   "Sets the amount of the item."
	);
Event EV_Item_SetMaxAmount
	( 
	"maxamount",
	EV_DEFAULT,
   "i",
   "max_amount",
   "Sets the max amount of the item."
	);
Event EV_Item_SetItemName
	( 
	"name",
	EV_DEFAULT,
   "s",
   "item_name",
   "Sets the item name."
	);
Event EV_Item_RespawnSound
	( 
	"respawnsound",
	EV_DEFAULT,
   NULL,
   NULL,
   "Turns on the respawn sound for this item."
	);
Event EV_Item_DialogNeeded
	( 
	"dialogneeded",
	EV_DEFAULT,
   "s",
   "dialog_needed",
   "Sets the dialog needed string."
	);
Event EV_Item_NoRemove
	( 
	"no_remove",
	EV_DEFAULT,
   NULL,
   NULL,
   "Makes it so the item is not removed from the world when it is picked up."
	);
Event EV_Item_RespawnDone
	( 
	"respawn_done",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called when the item respawn is done."
	);
Event EV_Item_PickupDone
	( 
	"pickup_done",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called when the item pickup is done."
	);

Event EV_Item_SetPickupThread
	( 
	"pickup_thread",
	EV_DEFAULT,
   "s",
   "labelName",
   "A thread that is called when an item is picked up."
	);

Event EV_Item_CoolItem
	( 
	"coolitem",
	EV_DEFAULT,
   "SS",
   "dialog anim_to_play",
   "Specify that this is a cool item when we pick it up for the first time.\n"
   "If dialog is specified, than the dialog will be played during the pickup.\n"
   "If anim_to_play is specified, than the specified anim will be played after\n"
   "the initial cinematic."
	);

Event EV_Item_ForceCoolItem
	( 
	"forcecoolitem",
	EV_DEFAULT,
   "SS",
   "dialog anim_to_play",
   "Specify that this is a cool item when we pick it up regardless of whether or not we have it.\n"
   "If dialog is specified, than the dialog will be played during the pickup.\n"
   "If anim_to_play is specified, than the specified anim will be played after\n"
   "the initial cinematic."
	);

CLASS_DECLARATION( Trigger, Item, NULL )
	{
		{ &EV_Trigger_Effect,	      ItemTouch },
	   { &EV_Item_DropToFloor,	      DropToFloor },
	   { &EV_Item_Respawn,		      Respawn },
	   { &EV_Item_SetAmount,         SetAmountEvent },
	   { &EV_Item_SetMaxAmount,      SetMaxAmount },
      { &EV_Item_SetItemName,       SetItemName },
	   { &EV_Item_Pickup,			   Pickup },
      { &EV_Use,		               TriggerStuff },
      { &EV_Item_RespawnSound,      RespawnSound },
      { &EV_Item_DialogNeeded,      DialogNeeded },
		{ &EV_Item_NoRemove,          SetNoRemove },
		{ &EV_Item_RespawnDone,			RespawnDone },
		{ &EV_Item_PickupDone,			PickupDone },
		{ &EV_Item_SetRespawn,			setRespawn },
		{ &EV_Item_SetRespawnTime,		setRespawnTime },
      { &EV_Item_SetPickupThread,   SetPickupThread },   
      { &EV_Item_CoolItem,          CoolItemEvent },   
      { &EV_Item_ForceCoolItem,     ForceCoolItemEvent },   
		{ &EV_Stop,	               	Landed },
      { &EV_SetAngle,               SetAngleEvent },
		{ NULL, NULL }
	};

Item::Item()
	{
   str fullname;

   if ( LoadingSavegame )
      {
      return;
      }

	setSolidType( SOLID_NOT );

	// Set default respawn behavior
	// Derived classes should use setRespawn
	// if they want to override the default behavior
   setRespawn( deathmatch->integer ? true : false );
	setRespawnTime( 20 );

   //
   // we want the bounds of this model auto-rotated
   //
   flags |= FL_ROTATEDBOUNDS;

   //
   // set a minimum mins and maxs for the model
   //
   if ( size.length() < 10 )
      {
	   mins = "-10 -10 0";
      maxs = "10 10 20";
      }

   //
   // reset the mins and maxs to pickup the FL_ROTATEDBOUNDS flag
   //
   setSize( mins, maxs );

   if ( !LoadingSavegame )
      {
	   // Items can't be immediately dropped to floor, because they might
	   // be on an entity that hasn't spawned yet.
	   PostEvent( EV_Item_DropToFloor, EV_POSTSPAWN );
      }

	respondto = TRIGGER_PLAYERS;

   // items should collide with everything that the player does
	edict->clipmask	 = MASK_PLAYERSOLID;

   item_index = 0;
   maximum_amount = 1;
   playrespawn = false;

   // this is an item entity
   edict->s.eType = ET_ITEM;

   amount = 1;
	no_remove = false;
   setName( "Unknown Item" );

	look_at_me = true;
   coolitem = qfalse;
   coolitemforced = qfalse;

	has_been_looked_at = false;
	}

Item::~Item()
	{
	if ( owner )
		{
		owner->RemoveItem( this );
		owner = NULL;
		}
	}

void Item::SetNoRemove
	(
	Event *ev
	)
	{
	no_remove = true;
	}

/*
============
PlaceItem

Puts an item back in the world
============
*/
void Item::PlaceItem
	(
	void
	)

	{
	setSolidType( SOLID_TRIGGER );
	setMoveType( MOVETYPE_TOSS );
	showModel();

	groundentity = NULL;
	}

/*
============
DropToFloor

plants the object on the floor
============
*/
void Item::DropToFloor
	(
	Event *ev
	)

	{
   str fullname;
	Vector save;

	PlaceItem();

   addOrigin( "0 0 1" );

	save = origin;
	if ( !droptofloor( 8192 ) )
		{
      gi.DPrintf( "%s (%d) stuck in world at '%5.1f %5.1f %5.1f'\n",
         getClassID(), entnum, origin.x, origin.y, origin.z );
	   setOrigin( save );
   	setMoveType( MOVETYPE_NONE );
		}
   else
      {
   	setMoveType( MOVETYPE_NONE );
      }
   //
   // if the our global variable doesn't exist, lets zero it out
   //
   fullname = str( "playeritem_" ) + getName();
   if ( !gameVars.VariableExists( fullname.c_str() ) )
      {
      gameVars.SetVariable( fullname.c_str(), 0 );
      }

   if ( !levelVars.VariableExists( fullname.c_str() ) )
      {
      levelVars.SetVariable( fullname.c_str(), 0 );
      }

	}

qboolean Item::Drop
	(
	void
	)

	{
	if ( !owner )
		{
		return false;
		}

   setOrigin( owner->origin + "0 0 40" );

	// drop the item
	PlaceItem();
	velocity = owner->velocity * 0.5 + Vector( G_CRandom( 50 ), G_CRandom( 50 ), 100 );
	setAngles( owner->angles );
	avelocity = Vector( 0, G_CRandom( 360 ), 0 );

   trigger_time = level.time + 1;

	if ( owner->isClient() )
		{
		spawnflags |= DROPPED_PLAYER_ITEM;
		}
	else
		{
		spawnflags |= DROPPED_ITEM;
		}

   // Remove this from the owner's item list
   owner->RemoveItem( this );
	owner = NULL;

	return true;
	}


void Item::ItemTouch
	(
	Event *ev
	)

	{
	Entity	*other;
	Event		*e;

	if ( owner )
		{
		// Don't respond to trigger events after item is picked up.
      // we really don't need to see this.
      //gi.DPrintf( "%s with targetname of %s was triggered unexpectedly.\n", getClassID(), TargetName() );
		return;
		}

	other = ev->GetEntity( 1 );

	e = new Event( EV_Item_Pickup );
	e->AddEntity( other );
	ProcessEvent( e );
	}

void Item::SetOwner
	(
	Sentient *ent
	)

	{
	assert( ent );
	if ( !ent )
		{
		// return to avoid any buggy behaviour
		return;
		}

   owner = ent;
	setRespawn( false );

	setSolidType( SOLID_NOT );
	hideModel();
   CancelEventsOfType( EV_Touch );
	CancelEventsOfType( EV_Item_DropToFloor );
	CancelEventsOfType( EV_Remove );
//	ItemPickup( ent );
	}

Sentient *Item::GetOwner
	(
	void
	)

	{
	return owner;
	}

Item * Item::ItemPickup
	(
	Entity *other,
   qboolean add_to_inventory
	)

	{
   Sentient * sent;
   Item * item = NULL;
	str realname;

   if ( !Pickupable( other ) )
		{
		return NULL;
		}

   sent = ( Sentient * )other;

   if ( add_to_inventory )
      {
      item = sent->giveItem( model, getAmount() );

      if ( !item )
         return NULL;
      }
   else
      {
      item = this;
      }

   //
   // make sure to copy over the coolness factor :)
   //
   item->coolitem = coolitem;
   item->cool_dialog = cool_dialog;
   item->cool_anim = cool_anim;
   item->coolitemforced = coolitemforced;

   //
   // let our sent know they received it
   // we put this here so we can transfer information from the original item we picked up
   //
   sent->ReceivedItem( item );

	realname = GetRandomAlias( "snd_pickup" );
   if ( realname.length() > 1 )
		sent->Sound( realname, CHAN_ITEM );

	if ( !Removable() )
		{
		// leave the item for others to pickup
		return item;
		}

	look_at_me = false;

	CancelEventsOfType( EV_Item_DropToFloor );
	CancelEventsOfType( EV_Item_Respawn );
   CancelEventsOfType( EV_FadeOut );

	setSolidType( SOLID_NOT );

	if ( HasAnim( "pickup" ) )
		RandomAnimate( "pickup", EV_Item_PickupDone );
	else 
		{
		if ( !no_remove )
			{
			hideModel();

			if ( !Respawnable() )
				PostEvent( EV_Remove, FRAMETIME );
			}
		}

	if ( Respawnable() )
		PostEvent( EV_Item_Respawn, RespawnTime() );

   // fire off any pickup_thread's 
   if ( pickup_thread.length() )
      {
      ExecuteThread( pickup_thread );
      }


   if ( item && DM_FLAG( DF_INSTANT_ITEMS ) )
		{
      Event *ev;

      ev = new Event( EV_InventoryItem_Use );
      ev->AddEntity( other );

      item->ProcessEvent( ev );
		}

   return item;
	}

void Item::Respawn
	(
	Event *ev
	)

	{
	showModel();

	// allow it to be touched again
	setSolidType( SOLID_TRIGGER );

	// play respawn sound
   if ( playrespawn )
      {
		Sound( "snd_itemspawn" );
      }

	setOrigin();

	if ( HasAnim( "respawn" ) )
		RandomAnimate( "respawn", EV_Item_RespawnDone );

	look_at_me = true;
	has_been_looked_at = false;
	}

void Item::setRespawn
	(
	Event *ev
	)

	{
	if ( ev->NumArgs() < 1 )
		return;

	setRespawn( ev->GetInteger( 1 ) );
	}

void Item::setRespawnTime
	(
	Event *ev
	)

	{
	if ( ev->NumArgs() < 1 )
		return;

	setRespawnTime( ev->GetFloat( 1 ) );
	}

void Item::RespawnDone
	(
	Event *ev
	)

	{
	RandomAnimate( "idle" );
	}

void Item::PickupDone
	(
	Event *ev
	)

	{
	if ( !no_remove )
		{
		hideModel();

		if ( !Respawnable() )
			PostEvent( EV_Remove, FRAMETIME );
		}
	else
		{
		if ( HasAnim( "pickup_idle" ) )
			RandomAnimate( "pickup_idle" );
		else
			RandomAnimate( "pickup" );
		}
	}

void Item::setRespawn
	(
	qboolean flag
	)

	{
	respawnable = flag;
	}

qboolean Item::Respawnable
	(
	void
	)

	{
	return respawnable;
	}

void Item::setRespawnTime
	(
	float time
	)

	{
	respawntime = time;
	}

float Item::RespawnTime
	(
	void
	)

	{
	return respawntime;
	}

int Item::getAmount
   (
   void
   )

   {
   return amount;
   }

int Item::MaxAmount
   (
   void
   )

   {
   return maximum_amount;
   }

qboolean Item::Pickupable
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

      if ( item && ( item->getAmount() >= item->MaxAmount() ) )
         {
         return false;
         }

      // If deathmatch and already in a powerup, don't pickup anymore when DF_INSTANT_ITEMS is on
      if ( DM_FLAG( DF_INSTANT_ITEMS ) &&
           this->isSubclassOf( InventoryItem ) &&
           sent->PowerupActive()
         )
         {
         return false;
         }
      }
   return true;
   }

void Item::Pickup
	(
   Event * ev
	)

	{
	ItemPickup( ev->GetEntity( 1 ) );
   }

void Item::setName
   (
   const char *i
   )

   {
   item_name = i;
   item_index = gi.itemindex( i );
	strcpy( edict->entname, i );
   }

str Item::getName
   (
   void
   )

   {
   return( item_name );
   }

int Item::getIndex
   (
   void
   )

   {
   return item_index;
   }

void Item::setAmount
	(
	int startamount
	)

	{
   amount = startamount;
   if ( amount >= MaxAmount() )
      {
      SetMax( amount );
      }
   }

void Item::SetMax
	(
	int maxamount
	)

	{
   maximum_amount = maxamount;
   }

void Item::SetAmountEvent
	(
	Event *ev
	)

	{
	setAmount( ev->GetInteger( 1 ) );
   }

void Item::SetMaxAmount
	(
	Event *ev
	)

	{
	SetMax( ev->GetInteger( 1 ) );
   }

void Item::SetItemName
	(
	Event *ev
	)

	{
   setName( ev->GetString( 1 ) );
	}

void Item::Add
	(
	int num
	)

	{
	amount += num;
   if ( amount >= MaxAmount() )
      amount = MaxAmount();
	}

void Item::Remove
   (
   int num
   )
   {
   amount -= num;
   if (amount < 0)
      amount = 0;
   }


qboolean Item::Use
	(
	int num
	)

	{
	if ( num > amount )
		{
		return false;
		}

	amount -= num;
	return true;
	}

qboolean Item::Removable
	(
	void
	)

	{
   return true;
	}

void Item::RespawnSound
	(
	Event *ev
	)

	{
   playrespawn = true;
   }

void Item::DialogNeeded
	(
	Event *ev
	)

	{
   //
   // if this item is needed for a trigger, play this dialog
   //
   dialog_needed = ev->GetString( 1 );
   }

str Item::GetDialogNeeded
	(
   void
	)

	{
   return dialog_needed;
   }

//
// once item has landed on the floor, go to movetype none
//
void Item::Landed
	(
	Event *ev
	)
	{
   if ( groundentity && ( groundentity->entity != world ) )
      {
      warning( "Item::Landed", "Item %d has landed on an entity that might move\n", entnum );
      }
	setMoveType( MOVETYPE_NONE );
   }

void Item::SetPickupThread
	(
	Event *ev
	)

	{
	pickup_thread = ev->GetString( 1 );
   }

void Item::SetCoolItem
	(
   qboolean cool,
   str &dialog,
   str &anim
	)
   {
   coolitem = cool;
   cool_dialog = dialog;
   if ( cool_dialog.length() )
      {
      CacheResource( cool_dialog, this );
      }

	CacheResource( "models/fx_coolitem.tik", this );
	CacheResource( "models/fx_coolitem_reverse.tik", this );

   cool_anim = anim;
   }

void Item::CoolItemEvent
	(
	Event *ev
	)

	{
   qboolean cool;
   str dialog, anim;

   cool = qtrue;
   if ( ev->NumArgs() > 0 )
      {
      dialog = ev->GetString( 1 );
      }
   if ( ev->NumArgs() > 1 )
      {
      anim = ev->GetString( 2 );
      }
   SetCoolItem( cool, dialog, anim );
   }

void Item::ForceCoolItemEvent
	(
	Event *ev
	)

	{
   coolitemforced = qtrue;
   CoolItemEvent( ev );
   }

qboolean Item::IsItemCool
	(
   str * dialog,
   str * anim,
   qboolean * forced
	)
   {
   *dialog = cool_dialog;
   *anim = cool_anim;
   *forced = coolitemforced;
   return coolitem;
   }
