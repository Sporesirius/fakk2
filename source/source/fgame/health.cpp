//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/health.cpp                         $
// $Revision:: 22                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 7/23/00 7:22p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/health.cpp                              $
// 
// 22    7/23/00 7:22p Steven
// Fixed a couple sounds.
// 
// 21    7/22/00 8:35p Steven
// Fixed the health and water vial use sounds.
// 
// 20    7/22/00 11:17a Steven
// Make health that falls from a healthplant give the same amount of health.
// 
// 19    7/13/00 7:28p Steven
// Fixed some targetname stuff.
// 
// 18    7/13/00 4:13p Steven
// Made fruit that is knocked off of the healthplants have a targetname =
// parent targetname + "_spawned".
// 
// 17    7/13/00 12:30p Steven
// Made it so using a health item puts out fires on your body.
// 
// 16    7/10/00 6:50p Markd
// fixed some issues with water running
// 
// 15    7/10/00 5:09p Markd
// forgot to include player
// 
// 14    7/10/00 5:07p Markd
// Added WaterInventoryItem
// 
// 13    6/27/00 5:47p Steven
// Made it so player's health will not go above 100 and health items will not
// be picked up if player already has 100 health.
// 
// 12    6/24/00 11:20a Steven
// Made health plants be able to be shot be any projectile.  Everything but a
// sling just knocks it straight down.
// 
// 11    6/05/00 11:48a Steven
// Fixed a crash in healthplant::touch.
// 
// 10    5/25/00 9:59a Steven
// Made it so when a health vial is used a special effect surrounds player and
// made it so if no fall velocity is set for a health plant the fruit falls
// towards the player.
// 
// 9     5/23/00 10:19a Steven
// Added healthplant.
// 
// 8     4/12/00 10:01a Markd
// removed unused variables
// 
// 7     4/11/00 5:31p Markd
// reworked pickup code
// 
// 6     4/05/00 8:50p Markd
// got rid of damage skin support
// 
// 5     4/04/00 3:28p Aldie
// Fix use code for health inventory item
// 
// 4     3/13/00 5:18p Aldie
// Made some changes for usable inventory item stuff
// 
// 3     1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
// 
// 2     1/06/00 11:30p Jimdose
// removed unused health items
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 6     8/28/99 2:41p Steven
// Took out some old references to def files.
// 
// DESCRIPTION:
// Health powerup 
// 

#include "g_local.h"
#include "item.h"
#include "inventoryitem.h"
#include "sentient.h"
#include "health.h"
#include "weaputils.h"
#include "player.h"

CLASS_DECLARATION( InventoryItem, HealthInventoryItem, "" )
   {
      { &EV_InventoryItem_Use,         Use },
	   { NULL, NULL }
   };


void HealthInventoryItem::Use
   (
   Event *ev
   )

   {
   Entity      *other;
   Sentient    *sen;
	Event			*event;
	str			sound_name;


	other = ev->GetEntity( 1 );
   if ( !other || !other->isSubclassOf( Sentient ) )
      {
      return;
      }

	sen = ( Sentient * )other;
   sen->health += amount;
	
   if ( sen->health > sen->max_health )
		{
		sen->health = sen->max_health;
		}

	// If we are on fire stop it

	sen->ProcessEvent( EV_Sentient_StopOnFire );

	// Spawn special effect around sentient

	sound_name = GetRandomAlias( "snd_use" );

	if ( sound_name )
		other->Sound( sound_name.c_str(), 0 );

	event = new Event( EV_AttachModel );
	event->AddString( "models/fx_tikifx2.tik" );
	event->AddString( "Bip01 Spine" );
   // set scale
   event->AddFloat( 1 );
   // set targetname
   event->AddString( "regen" );
   // set detach_at_death 
   event->AddInteger( 1 );
   // set remove_time
   event->AddFloat( 2 );
   other->ProcessEvent( event );

   PostEvent( EV_Remove, 0 );
   }

CLASS_DECLARATION( InventoryItem, WaterInventoryItem, "" )
   {
      { &EV_InventoryItem_Use,         Use },
	   { NULL, NULL }
   };


void WaterInventoryItem::Use
   (
   Event *ev
   )

   {
	Event			*event;
   Entity      *other;
	str			sound_name;

	other = ev->GetEntity( 1 );
   if ( !other || !other->isSubclassOf( Player ) )
      {
      return;
      }

	sound_name = GetRandomAlias( "snd_use" );

	if ( sound_name )
		other->Sound( sound_name.c_str(), 0 );

   ( ( Player * )other )->SetWaterPower( amount );

	event = new Event( EV_AttachModel );
	event->AddString( "models/fx_watervial.tik" );
	event->AddString( "Bip01 Spine" );
   // set scale
   event->AddFloat( 1 );
   // set targetname
   event->AddString( "regen" );
   // set detach_at_death 
   event->AddInteger( 1 );
   // set remove_time
   event->AddFloat( 2 );
   other->ProcessEvent( event );

   PostEvent( EV_Remove, 0 );
   }


CLASS_DECLARATION( Item, Health, "health_020" )
	{
      { &EV_Item_Pickup,      				PickupHealth },
		{ NULL, NULL }
	};

Health::Health()
	{
	if ( DM_FLAG( DF_NO_HEALTH ) )
		{
		PostEvent( EV_Remove, EV_REMOVE );
		return;
		}

   setAmount( 20 );
	}

void Health::PickupHealth
	(
	Event *ev
	)
	
	{
	Sentient *sen;
	Entity *other;

	other = ev->GetEntity( 1 );
   if ( !other || !other->isSubclassOf( Sentient ) )
      {
      return;
      }

	sen = ( Sentient * )other;

	if ( sen->health >= sen->max_health )
		return;

   if ( !ItemPickup( other, qfalse ) )
      {
      return;
      }

	sen->health += amount;

	if ( sen->health > sen->max_health )
		{
		sen->health = sen->max_health;
		}

	// If we are on fire stop it

	sen->ProcessEvent( EV_Sentient_StopOnFire );
	}

Event EV_HealthPlant_SetFallVelocity
	( 
	"fallvelocity",
	EV_DEFAULT,
   "v",
   "fall_velocity",
   "Sets the fall velocity for this health plant."
	);

CLASS_DECLARATION( Health, HealthPlant, NULL )
	{
		{ &EV_Trigger_Effect,						Touch },
		{ &EV_HealthPlant_SetFallVelocity,		SetFallVelocity },
		{ NULL,											NULL }
	};

HealthPlant::HealthPlant()
	{
	respondto = (TRIGGER_PLAYERS | TRIGGER_PROJECTILES);
	edict->s.eType = ET_MODELANIM;
	}

void HealthPlant::Touch
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

	if ( !other )
		return;

	if ( other->isSubclassOf( Projectile ) )
		{
		Projectile *proj = (Projectile *)other;

		if ( proj->meansofdeath == MOD_SLING )
			Hit( proj->velocity, false );
		else
			Hit( proj->velocity, true );
		}
	else
		{
		e = new Event( EV_Item_Pickup );
		e->AddEntity( other );
		ProcessEvent( e );
		}
	}

void HealthPlant::SetFallVelocity
	(
	Event *ev
	)

	{
	fall_velocity = ev->GetVector( 1 );
	}

void HealthPlant::Hit
	(
	Vector velocity,
	qboolean	fall_straight_down
	)

	{
	Health *health;
	Vector orig;

	// Spawn in a health fruit

	health = new Health;

	health->setModel( "item_healthfruit1.tik" );

	GetTag( "tag_healthfruit1", &orig );

	health->setOrigin( orig );

	health->ProcessPendingEvents();

	health->PlaceItem();
	health->setOrigin( orig );

	health->setAmount( amount );

	// Make new health fruit have the same target name of the healthplant with "_spawned" on the end

	health->targetname = targetname;
	health->targetname += "_spawned";

	health->SetTargetName( health->targetname );

	if ( fall_straight_down )
		{
		health->velocity = vec_zero;
		}
	else if ( fall_velocity != vec_zero )
		{
		health->velocity = fall_velocity;
		}
	else
		{
		health->velocity = velocity * -1;
		health->velocity.z = 0;
		health->velocity.normalize();
		health->velocity *= 150;
		health->velocity.z = 200;
		}

	setSolidType( SOLID_NOT );

	RandomAnimate( "pickup", EV_Item_PickupDone );

	if ( Respawnable() )
		PostEvent( EV_Item_Respawn, RespawnTime() );
	}

