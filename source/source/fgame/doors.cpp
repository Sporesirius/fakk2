//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/doors.cpp                          $
// $Revision:: 27                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/27/00 5:39p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/doors.cpp                               $
// 
// 27    7/27/00 5:39p Markd
// put in doorcompletelyclosed
// 
// 25    7/18/00 3:29p Markd
// added better caching for sounds in general
// 
// 24    7/18/00 3:03p Markd
// fixed error message
// 
// 23    7/17/00 4:43p Steven
// Made doors play locked sound when player uses them if they are locked and
// automatic.
// 
// 22    7/15/00 3:00p Steven
// fixed door locked sound playing constantly when it is an auto open door
// 
// 21    7/11/00 7:07p Steven
// Made it so actors don't cause door locked sounds and removed a center print.
// 
// 20    7/03/00 6:59p Steven
// Setup default locked door sound.
// 
// 19    7/01/00 1:25p Markd
// fixed door bug with area portals
// 
// 18    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 17    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 16    6/05/00 11:16a Markd
// fixed doors getting blocked by entities and crashing the game
// 
// 15    6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 14    3/27/00 4:15p Markd
// updated script_door documentation
// 
// 13    1/25/00 10:02a Steven
// Made doors automatically open for actors.
// 
// 12    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 11    1/14/00 5:06p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 10    1/12/00 6:16p Jimdose
// made EV_SlidingDoor_Setup use EV_HIDE
// 
// 9     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 8     12/11/99 6:44p Markd
// second run-through of q3a merge, got the entire project to build without
// errors or warnings
// 
// 7     10/14/99 5:08p Markd
// removed a lot of G_GetMoveDir calls from the initialization code
// 
// 6     10/13/99 5:03p Markd
// Fixed door bug where multiple linked doors where all adjusting the portal
// state
// 
// 5     10/07/99 2:59p Steven
// Event formatting.
// 
// 4     9/29/99 5:18p Steven
// Event formatting.
// 
// 3     9/22/99 4:47p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 2     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 22    8/28/99 11:42a Steven
// Removed global from sound function calls.
// 
// 21    8/25/99 12:42p Markd
// Fixed some minor and major scripting bugs
// 
// 20    7/08/99 4:28p Markd
// Removed obsolete QUAKED functions
// 
// 19    6/11/99 2:20p Phook
// Renamed a few entities
// 
// 18    6/11/99 1:23p Phook
// 
// 17    6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
// 
// 16    6/11/99 12:46p Phook
// EClass color changes
//
// DESCRIPTION:
// Doors are environment objects that rotate open when activated by triggers
// or when used by the player.
//

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "mover.h"
#include "doors.h"
#include "sentient.h"
#include "scriptmaster.h"
#include "item.h"
#include "actor.h"
#include "player.h"
#include "g_utils.h"

Event EV_Door_StopSound
	( 
	"sound_stop",
	EV_DEFAULT,
   "s",
   "sound_stop",
   "Sets the sound to use when the door stops."
	);
Event EV_Door_MoveSound
	( 
	"sound_move",
	EV_DEFAULT,
   "s",
   "sound_move",
   "Sets the sound to use when the door moves."
	);
Event EV_Door_MessageSound
	( 
	"sound_message",
	EV_DEFAULT,
   "s",
   "sound_message",
   "Sets the sound to use when the door displays a message."
	);
Event EV_Door_LockedSound
	( 
	"sound_locked",
	EV_DEFAULT,
   "s",
   "sound_locked",
   "Sets the sound to use when the door is locked."
	);
Event EV_Door_SetWait
	( 
	"wait",
	EV_DEFAULT,
   "f",
   "wait",
   "Sets the amount of time to wait before automatically shutting."
	);
Event EV_Door_SetDmg
	( 
	"dmg",
	EV_DEFAULT,
   "i",
   "damage",
   "Sets the amount of damage the door will do to entities that get stuck in it."
	);
Event EV_Door_TriggerFieldTouched
	( 
	"door_triggerfield",
	EV_DEFAULT,
   "e",
   "other",
   "Is called when a doors trigger field is touched."
	);
Event EV_Door_TryOpen
	( 
	"tryToOpen",
	EV_DEFAULT,
   "e",
   "other",
   "Tries to open the door."
	);
Event EV_Door_Close
	( 
	"close",
	EV_DEFAULT,
   NULL,
   NULL,
   "Closes the door."
	);
Event EV_Door_Open
	( 
	"open",
	EV_DEFAULT,
   "e",
   "other",
   "Opens the door."
	);
Event EV_Door_DoClose
	( 
	"doclose",
	EV_DEFAULT,
   NULL,
   NULL,
   "Closes the door (special doors)."
	);
Event EV_Door_DoOpen
	( 
	"doopen",
	EV_DEFAULT,
   "e",
   "other",
   "Opens the door (special doors)."
	);
Event EV_Door_CloseEnd
	( 
	"doorclosed",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called when the door finishes closing."
	);
Event EV_Door_OpenEnd
	( 
	"dooropened",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called when the door finishes opening."
	);
Event EV_Door_Fire
	( 
	"toggledoor",
	EV_DEFAULT,
   "e",
   "other",
   "Toggles the state of the door (open/close)."
	);
Event EV_Door_Link
	( 
	"linkdoor",
	EV_DEFAULT,
   NULL,
   NULL,
   "Link doors together."
	);
Event EV_Door_SetTime
	( 
	"time",
	EV_DEFAULT,
   "f",
   "traveltime",
   "Sets the time it takes for the door to open an close."
	);
Event EV_Door_Lock
	( 
	"lock",
	EV_DEFAULT,
   NULL,
   NULL,
   "Lock the door."
	);
Event EV_Door_Unlock
	( 
	"unlock",
	EV_DEFAULT,
   NULL,
   NULL,
   "Unlock the door."
	);

#define DOOR_START_OPEN			1
#define DOOR_OPEN_DIRECTION	2
#define DOOR_DONT_LINK			4
#define DOOR_TOGGLE				32
#define DOOR_AUTO_OPEN			64
#define DOOR_TARGETED 			128

#define STATE_OPEN		1
#define STATE_OPENING	2
#define STATE_CLOSING   3
#define STATE_CLOSED		4

/*

Doors are similar to buttons, but can spawn a fat trigger field around them
to open without a touch, and they link together to form simultanious
double/quad doors.

Door.master is the master door.  If there is only one door, it points to itself.
If multiple doors, all will point to a single one.

Door.enemy chains from the master door through all doors linked in the chain.

*/

CLASS_DECLARATION( ScriptSlave, Door, "NormalDoor" )
	{
      { &EV_Door_StopSound,            SetStopSound },
      { &EV_Door_MoveSound,            SetMoveSound },
      { &EV_Door_MessageSound,         SetMessageSound },
      { &EV_Door_LockedSound,          SetLockedSound },
      { &EV_Door_SetWait,              SetWait },
      { &EV_Door_SetDmg,               SetDmg },
		{ &EV_Door_TriggerFieldTouched,  FieldTouched },
	   { &EV_Trigger_Effect,			   TryOpen },
	   { &EV_Activate,			         TryOpen },
	   { &EV_Door_TryOpen,	            TryOpen },
	   { &EV_Door_Close,		            Close },
	   { &EV_Door_Open,		            Open },
	   { &EV_Door_CloseEnd,	            CloseEnd },
		{ &EV_Door_OpenEnd,	            OpenEnd },
	   { &EV_Door_Fire,		            DoorFire },
	   { &EV_Door_Link,		            LinkDoors },
	   { &EV_Door_SetTime,	            SetTime },
	   { &EV_Use,							   DoorUse },
	   { &EV_Killed,						   DoorFire },
	   { &EV_Blocked,						   DoorBlocked },
	   { &EV_Door_Lock,		            LockDoor },
	   { &EV_Door_Unlock,		         UnlockDoor },
      { &EV_SetAngle,                  SetDir },
	   { &EV_Touch,						   NULL },
		{ NULL, NULL }
	};

Door::Door()
	{
	float t;
   const char *text;

   if ( LoadingSavegame )
      {
      return;
      }

	nextdoor = 0;
	trigger = 0;
   locked = false;
   master = this;
   lastblocktime = 0;
   diropened = 0;

   dir = G_GetMovedir( 0 );
	t = dir[ 0 ];
	dir[ 0 ] = -dir[ 1 ];
	dir[ 1 ] = t;

	showModel();

	text = gi.GlobalAlias_FindRandom( "door_stop" );
   if ( text )
      {
      SetStopSound( text );
      }

	text = gi.GlobalAlias_FindRandom( "door_moving" );
   if ( text )
      {
      SetMoveSound( text );
      }

	text = gi.GlobalAlias_FindRandom( "snd_locked" );
   if ( text )
      {
      SetLockedSound( text );
      }

	traveltime = 0.3;
	speed = 1.0f / traveltime;

   wait = ( spawnflags & DOOR_TOGGLE ) ? 0 : 3;
	dmg = 0;

	setSize( mins, maxs );

	setOrigin( localorigin );

	// DOOR_START_OPEN is to allow an entity to be lighted in the closed position
	// but spawn in the open position
	if ( spawnflags & DOOR_START_OPEN )
		{
		state = STATE_OPEN;
   	PostEvent( EV_Door_Open, EV_POSTSPAWN );
		}
	else
		{
		state = STATE_CLOSED;
		}
   previous_state = state;

	if ( health )
		{
		takedamage = DAMAGE_YES;
		}

	// LinkDoors can't be done until all of the doors have been spawned, so
	// the sizes can be detected properly.
	nextdoor = 0;
	PostEvent( EV_Door_Link, EV_LINKDOORS );

	// Default to work with monsters and players
	respondto = TRIGGER_PLAYERS | TRIGGER_MONSTERS;
	if ( spawnflags & 8 )
		{
		respondto &= ~TRIGGER_PLAYERS;
		}
	if ( spawnflags & 16 )
		{
		respondto &= ~TRIGGER_MONSTERS;
		}

	next_locked_time = 0;
	}

void Door::SetDir
   (
   Event *ev
   )

   {
   float t;
   float angle;

   angle = ev->GetFloat( 1 );
   dir = G_GetMovedir( angle );
	t = dir[ 0 ];
	dir[ 0 ] = -dir[ 1 ];
	dir[ 1 ] = t;
   }

void Door::SetStopSound
   (
   str sound
   )

   {
   sound_stop = sound;
   if ( sound_stop.length() > 1 )
      {
      CacheResource( sound_stop.c_str(), this );
      }
   }

void Door::SetMoveSound
   (
   str sound
   )

   {
	sound_move = sound;
   if ( sound_move.length() > 1 )
      {
      CacheResource( sound_move.c_str(), this );
      }
   }

void Door::SetMessageSound
   (
   str sound
   )

   {
	sound_message = sound;
   if ( sound_message.length() > 1 )
      {
      CacheResource( sound_message.c_str(), this );
      }
   }

void Door::SetLockedSound
   (
   str sound
   )

   {
	sound_locked = sound;
   if ( sound_locked.length() > 1 )
      {
      CacheResource( sound_locked.c_str(), this );
      }
   }

void Door::SetStopSound
   (
   Event *ev
   )

   {
   SetStopSound( ev->GetString( 1 ) );
   }

void Door::SetMoveSound
   (
   Event *ev
   )

   {
   SetMoveSound( ev->GetString( 1 ) );
   }

void Door::SetMessageSound
   (
   Event *ev
   )

   {
   SetMessageSound( ev->GetString( 1 ) );
   }

void Door::SetLockedSound
   (
   Event *ev
   )

   {
   SetLockedSound( ev->GetString( 1 ) );
   }

void Door::SetWait
   (
   Event *ev
   )

   {
	wait = ev->GetFloat( 1 );
   }

void Door::SetDmg
   (
   Event *ev
   )

   {
	dmg = ev->GetInteger( 1 );
   }

qboolean Door::isOpen
	(
	void
	)

	{
	return ( state == STATE_OPEN );
	}

qboolean Door::isCompletelyClosed
	(
	void
	)

	{
	return ( state == STATE_CLOSED );
	}

void Door::OpenEnd
	(
	Event *ev
	)

	{
	if ( sound_stop.length() > 1 )
		{
		BroadcastSound();
		Sound( sound_stop, CHAN_VOICE );
		}
   else
      {
		StopSound( CHAN_VOICE );
      }

   previous_state = state;
	state = STATE_OPEN;
	if ( spawnflags & DOOR_TOGGLE )
		{
		// don't close automatically
		return;
		}

	if ( ( wait > 0 ) && ( master == this ) )
		{
		PostEvent( EV_Door_Close, wait );
		}
	}

void Door::CloseEnd
	(
	Event *ev
	)

	{
	if ( sound_stop.length() > 1 )
		{
		BroadcastSound();
		Sound( sound_stop, CHAN_VOICE );
		}
   else
      {
		StopSound( CHAN_VOICE );
      }

   if ( master == this )
      {
      gi.AdjustAreaPortalState( this->edict, false );
      }

   previous_state = state;
	state = STATE_CLOSED;
	}

void Door::Close
	(
	Event *ev
	)

	{
	Door *door;

   CancelEventsOfType( EV_Door_Close );

   previous_state = state;
	state = STATE_CLOSING;

	ProcessEvent( EV_Door_DoClose );

	if ( sound_move.length() > 1 )
		{
		BroadcastSound();
		Sound( sound_move, CHAN_VOICE );
		}
	if ( master == this )
		{
		if ( max_health )
			{
			takedamage	= DAMAGE_YES;
			health		= max_health;
			}

		// trigger all paired doors
		door = ( Door * )G_GetEntity( nextdoor );
		assert( door->isSubclassOf( Door ) );
		while( door && ( door != this ) )
			{
			door->ProcessEvent( EV_Door_Close );
			door = ( Door * )G_GetEntity( door->nextdoor );
			assert( door->isSubclassOf( Door ) );
			}
		}
	}

void Door::Open
	(
	Event *ev
	)

	{
	Door *door;
	Event *e;
	Entity *other;

	if ( ev->NumArgs() < 1 )
		{
		ev->Error( "No entity specified to open door.  Door may open the wrong way." );
		other = world;
		}
	else
		{
		other = ev->GetEntity( 1 );
		}

	if ( state == STATE_OPENING )
		{
		// already going up
		return;
		}

	if ( state == STATE_OPEN )
		{
		// reset top wait time
		if ( wait > 0 )
			{
         CancelEventsOfType( EV_Door_Close );
         PostEvent( EV_Door_Close, wait );
			}
		return;
		}

   previous_state = state;
	state = STATE_OPENING;

	e = new Event( EV_Door_DoOpen );
	e->AddEntity( other );
	ProcessEvent( e );

	if ( sound_move.length() > 1 )
		{
		BroadcastSound();
		Sound( sound_move, CHAN_VOICE );
		}
	if ( master == this )
		{
		// trigger all paired doors
		door = ( Door * )G_GetEntity( nextdoor );
		assert( door->isSubclassOf( Door ) );
		while( door && ( door != this ) )
			{
			e = new Event( EV_Door_Open );
			e->AddEntity( other );
			door->ProcessEvent( e );
			door = ( Door * )G_GetEntity( door->nextdoor );
			assert( door->isSubclassOf( Door ) );
			}

      if ( previous_state == STATE_CLOSED )
         {
         gi.AdjustAreaPortalState( this->edict, true );
         }
		}
	}

void Door::DoorUse
	(
	Event *ev
	)

	{
	Entity *other;
   qboolean respond;
	Event *e;

	other = ev->GetEntity( 1 );

	respond = ( ( ( respondto & TRIGGER_PLAYERS ) && other->isClient() ) ||
		( ( respondto & TRIGGER_MONSTERS ) && other->isSubclassOf( Actor ) ) );

   if ( !respond )
      {
      return;
      }

	// only allow use when not triggerd by other events
	if ( health || ( spawnflags & ( DOOR_AUTO_OPEN | DOOR_TARGETED ) ) )
		{
      if ( other->isSubclassOf( Sentient ) && ( state == STATE_CLOSED ) )
         {
         if ( health )
            {
            gi.SendServerCommand( NULL, "print \"This door is jammed.\"" );
            }
         else if ( spawnflags & DOOR_TARGETED )
            {
				Sound( "door_triggered", CHAN_VOICE );
            }
         }

		if ( spawnflags & DOOR_AUTO_OPEN && locked && other->isSubclassOf( Player ) && sound_locked.length() )
			{
			other->Sound( sound_locked, CHAN_VOICE );
			}

		return;
		}

   assert( master );
   if ( !master )
      {
      // bulletproofing
      master = this;
      }

	if ( master->state == STATE_CLOSED )
		{
		e = new Event( EV_Door_TryOpen );
		e->AddEntity( other );
		master->ProcessEvent( e );
		}
	else if ( master->state == STATE_OPEN )
		{
		e = new Event( EV_Door_Close );
		e->AddEntity( other );
		master->ProcessEvent( e );
		}
	}

void Door::DoorFire
	(
	Event *ev
	)

	{
	Event *e;
	Entity *other;

	other = ev->GetEntity( 1 );

	assert( master == this );
	if ( master != this )
		{
		gi.Error( ERR_DROP, "DoorFire: master != self" );
		}

	// no more messages
	SetMessage( NULL );

	// reset health in case we were damage triggered
	health = max_health;

	// will be reset upon return
	takedamage = DAMAGE_NO;

	if ( ( spawnflags & ( DOOR_TOGGLE | DOOR_START_OPEN ) ) && ( state == STATE_OPENING || state == STATE_OPEN ) )
		{
		spawnflags &= ~DOOR_START_OPEN;
		ProcessEvent( EV_Door_Close );
		}
	else
		{
		e = new Event( EV_Door_Open );
		e->AddEntity( other );
		ProcessEvent( e );
		}
	}

void Door::DoorBlocked
	(
	Event *ev
	)

	{
	Event *e;
	Entity *other;

   assert( master );
	if ( ( master ) && ( master != this ) )
		{
		master->ProcessEvent( new Event( ev ) );
		return;
		}

   if ( lastblocktime > level.time )
      {
      return;
      }

   lastblocktime = level.time + 0.3;

	other = ev->GetEntity( 1 );

	if ( dmg )
		{
      other->Damage( this, this, (int)dmg, origin, vec_zero, vec_zero, 0, 0, MOD_CRUSH );
		}

   //
   // if we killed him, lets keep on going
   //
   if ( other->deadflag )
		{
      return;
		}

	if ( state == STATE_OPENING || state == STATE_OPEN )
		{
		spawnflags &= ~DOOR_START_OPEN;
		ProcessEvent( EV_Door_Close );
		}
	else
		{
		e = new Event( EV_Door_Open );
		e->AddEntity( other );
		ProcessEvent( e );
		}
	}

void Door::FieldTouched
	(
	Event *ev
	)

	{
	Entity *other;

	other = ev->GetEntity( 1 );

	if ( !other )
		return;

	if ( ( state != STATE_OPEN ) && !( spawnflags & DOOR_AUTO_OPEN ) && !other->isSubclassOf( Actor ) )
		return;

	TryOpen( ev );
	}

qboolean	Door::CanBeOpenedBy
	(
	Entity *ent
	)

	{
   assert( master );
	if ( ( master ) && ( master != this ) )
		{
		return master->CanBeOpenedBy( ent );
		}

	if ( !locked && !key.length() )
		{
		return true;
		}

	if ( ent && ent->isSubclassOf( Sentient ) && ( ( Sentient * )ent )->HasItem( key.c_str() ) )
		{
		return true;
		}

	return false;
	}

void Door::TryOpen
	(
	Event *ev
	)

	{
	Entity *other;
	Event *event;

	//FIXME
	// hack so that doors aren't triggered by guys when game starts.
	// have to fix delay that guys go through before setting up their threads
	if ( level.time < 0.4 )
		{
		return;
		}

	other = ev->GetEntity( 1 );

   assert( master );
	if ( master && ( this != master ) )
		{
		event = new Event( EV_Door_TryOpen );
		event->AddEntity( other );
		master->ProcessEvent( event );
		return;
		}

	if ( !other || other->deadflag )
		{
		return;
		}

   if ( locked )
      {
		if ( next_locked_time <= level.time )
			{
			if ( sound_locked.length() > 1 && !other->isSubclassOf( Actor ) )
				{
				other->Sound( sound_locked, CHAN_VOICE );
				}
			else if ( other->isSubclassOf( Player ) )
				{
				other->Sound( "snd_locked", CHAN_VOICE );
	//         gi.centerprintf ( other->edict, "This door is locked." );
				}
			}

		// Always increment next locked time
		
		next_locked_time = level.time + 0.5;

		// locked doors don't open for anyone
      return;
      }

   if ( !CanBeOpenedBy( other ) )
		{
      Item        *item;
      ClassDef		*cls;

		if ( other->isClient() )
			{
			cls = getClass( key.c_str() );
			if ( !cls )
				{
            gi.DPrintf( "No item named '%s'\n", key.c_str() );
				return;
				}
			item = ( Item * )cls->newInstance();
			item->CancelEventsOfType( EV_Item_DropToFloor );
			item->CancelEventsOfType( EV_Remove );
			item->ProcessPendingEvents();
         gi.centerprintf ( other->edict, "You need the %s", item->getName() );
			delete item;
			}
      return;
      }

	// once we're opened by an item, we no longer need that item to open the door
	key = "";

	if ( Message().length() )
		{
      gi.centerprintf( other->edict, Message().c_str() );
		Sound( sound_message, CHAN_VOICE );
		}

	event = new Event( EV_Door_Fire );
	event->AddEntity( other );
	ProcessEvent( event );
	}

void Door::SpawnTriggerField
	(
	Vector fmins,
	Vector fmaxs
	)

	{
	TouchField *trig;
	Vector min;
	Vector max;

	min = fmins - "60 60 8";
	max = fmaxs + "60 60 8";

	trig = new TouchField;
	trig->Setup( this, EV_Door_TriggerFieldTouched, min, max, respondto );

	trigger = trig->entnum;
	}

qboolean Door::DoorTouches
	(
	Door *e1
	)

	{
	if ( e1->absmin.x > absmax.x )
		{
		return false;
		}
	if ( e1->absmin.y > absmax.y )
		{
		return false;
		}
	if ( e1->absmin.z > absmax.z )
		{
		return false;
		}
	if ( e1->absmax.x < absmin.x )
		{
		return false;
		}
	if ( e1->absmax.y < absmin.y )
		{
		return false;
		}
	if ( e1->absmax.z < absmin.z )
		{
		return false;
		}

	return true;
	}

void Door::LinkDoors
	(
	Event *ev
	)

	{
	Entity *entptr;
	Door	*ent;
	Door	*next;
	Vector			cmins;
	Vector			cmaxs;
	int				i;

   setSolidType( SOLID_BSP );
	setMoveType( MOVETYPE_PUSH );

	if ( nextdoor )
		{
		// already linked by another door
		return;
		}

	// master doors own themselves
	master = this;

	if ( spawnflags & DOOR_DONT_LINK )
		{
		// don't want to link this door
		nextdoor = entnum;
		return;
		}

	cmins = absmin;
	cmaxs = absmax;

	ent = this;
	for( entptr = this; entptr; entptr = G_FindClass( entptr, getClassID() ) )
		{
		next = ( Door * )entptr;
		if ( !ent->DoorTouches( next ) )
			{
			continue;
			}

		if ( next->nextdoor )
			{
			error( "cross connected doors.  Targetname = %s entity %d\n", TargetName(), entnum );
			}

		ent->nextdoor = next->entnum;
		ent = next;

		for( i = 0; i < 3; i++ )
			{
			if ( ent->absmin[ i ] < cmins[ i ] )
				{
				cmins[ i ] = ent->absmin[ i ];
				}
			if ( ent->absmax[ i ] > cmaxs[ i ] )
				{
				cmaxs[ i ] = ent->absmax[ i ];
				}
			}

		// set master door
		ent->master = this;

		if ( ent->health )
			{
			health = ent->health;
			}

		if ( ent->Targeted() )
			{
			if ( !Targeted() )
				{
				SetTargetName( ent->TargetName() );
				}
			else if ( strcmp( TargetName(), ent->TargetName() ) )
				{
				// not a critical error, but let them know about it.
            gi.DPrintf( "cross connected doors\n" );

				ent->SetTargetName( TargetName() );
				}
			}

		if ( ent->Message().length() )
			{
			if ( Message().length() && !strcmp( Message().c_str(), ent->Message().c_str() ) )
				{
				// not a critical error, but let them know about it.
            gi.DPrintf( "Different messages on linked doors.  Targetname = %s", TargetName() );
				}

			// only master should have a message
			SetMessage( ent->Message().c_str() );
			ent->SetMessage( NULL );
			}
		}

	// make the chain a loop
	ent->nextdoor = entnum;

	// open up any portals we control
   if ( spawnflags & DOOR_START_OPEN )
      {
      gi.AdjustAreaPortalState( this->edict, true );
      }

	// shootable or targeted doors don't need a trigger
	if ( health || ( spawnflags & DOOR_TARGETED ) )
		{
		// Don't let the player trigger the door
		return;
		}

   // Don't spawn trigger field when set to toggle
   if ( !( spawnflags & DOOR_TOGGLE ) )
      {
	   SpawnTriggerField( cmins, cmaxs );
      }
	}

void Door::SetTime
	(
	Event *ev
	)

	{
	traveltime = ev->GetFloat( 1 );
	if ( traveltime < FRAMETIME )
		{
		traveltime = FRAMETIME;
		}

	speed = 1.0f / traveltime;
	}

void Door::LockDoor
	(
	Event *ev
	)

	{
   locked = true;
	}

void Door::UnlockDoor
	(
	Event *ev
	)

	{
   locked = false;
	}

/*****************************************************************************/
/*QUAKED func_rotatingdoor (0 0.25 0.5) ? START_OPEN OPEN_DIRECTION DOOR_DONT_LINK NOT_PLAYERS NOT_MONSTERS TOGGLE AUTO_OPEN TARGETED
if two doors touch, they are assumed to be connected and operate as a unit.

TOGGLE causes the door to wait in both the start and end states for a trigger event.
DOOR_DONT_LINK is for when you have two doors that are touching but you want to operate independently.

START_OPEN causes the door to move to its destination when spawned, and operate in reverse.  It is used to temporarily or permanently close off an area when triggered (not usefull for touch or takedamage doors).
OPEN_DIRECTION indicates which direction to open when START_OPEN is set.
AUTO_OPEN causes the door to open when a player is near instead of waiting for the player to use the door.
TARGETED door is only operational from triggers or script

"message"		is printed when the door is touched if it is a trigger door and it hasn't been fired yet
"openangle"    how wide to open the door
"angle"			determines the opening direction.  point toward the middle of the door (away from the hinge)
"targetname"	if set, no touch field will be spawned and a remote button or trigger field activates the door.
"health"			if set, door must be shot open
"time"			move time (0.3 default)
"wait"			wait before returning (3 default, -1 = never return)
"dmg"				damage to inflict when blocked (0 default)
"key"          The item needed to open this door (default nothing)

"sound_stop"		Specify the sound that plays when the door stops moving (default global door_stop)
"sound_move"		Specify the sound that plays when the door opens or closes (default global door_moving)
"sound_message"	Specify the sound that plays when the door displays a message
"sound_locked"	   Specify the sound that plays when the door is locked

******************************************************************************/

Event EV_RotatingDoor_OpenAngle
	( 
	"openangle",
	EV_DEFAULT,
   "f",
   "open_angle",
   "Sets the open angle of the door."
	);

CLASS_DECLARATION( Door, RotatingDoor, "func_rotatingdoor" )
	{
	   { &EV_Door_DoClose,		            DoClose },
	   { &EV_Door_DoOpen,		            DoOpen },
      { &EV_RotatingDoor_OpenAngle,       OpenAngle },
		{ NULL, NULL }
	};

void RotatingDoor::DoOpen
   (
 	Event *ev
   )

	{
	Vector ang;

	if ( previous_state == STATE_CLOSED )
      {
      if ( ev->NumArgs() > 0 )
         {
   	   Entity *other;
	      Vector p;

	      other = ev->GetEntity( 1 );
         p = other->origin - origin;
         p.z = 0;
         diropened = dir * p;
         }
      else
         {
         diropened = 0 - init_door_direction;
         }
      }

	if ( diropened < 0 )
		{
		ang = startangle + Vector( 0, angle, 0 );
		}
	else
		{
		ang = startangle - Vector( 0, angle, 0 );
		}

   MoveTo( origin, ang, fabs( speed*angle ), EV_Door_OpenEnd );
   }

void RotatingDoor::DoClose
   (
 	Event *ev
   )

	{
   MoveTo( origin, startangle, fabs( speed*angle ), EV_Door_CloseEnd );
   }

void RotatingDoor::OpenAngle
   (
   Event *ev
   )

   {
   angle = ev->GetFloat( 1 );
   }

RotatingDoor::RotatingDoor()
	{
   if ( LoadingSavegame )
      {
      return;
      }
	startangle = angles;

	angle = 90;

   init_door_direction = (spawnflags & DOOR_OPEN_DIRECTION);
	}

/*****************************************************************************/
/*QUAKED func_door (0 0.25 0.5) ? START_OPEN x DOOR_DONT_LINK NOT_PLAYERS NOT_MONSTERS TOGGLE AUTO_OPEN TARGETED
if two doors touch, they are assumed to be connected and operate as a unit.

TOGGLE causes the door to wait in both the start and end states for a trigger event.
DOOR_DONT_LINK is for when you have two doors that are touching but you want to operate independently.

START_OPEN causes the door to move to its destination when spawned, and operate in reverse.  It is used to temporarily or permanently close off an area when triggered (not usefull for touch or takedamage doors).
OPEN_DIRECTION indicates which direction to open when START_OPEN is set.
AUTO_OPEN causes the door to open when a player is near instead of waiting for the player to use the door.
TARGETED door is only operational from triggers or script

"message"		is printed when the door is touched if it is a trigger door and it hasn't been fired yet
"angle"			determines the opening direction.  point toward the middle of the door (away from the hinge)
"targetname"	if set, no touch field will be spawned and a remote button or trigger field activates the door.
"health"			if set, door must be shot open
"speed"			move speed (100 default)
"time"			move time (1/speed default, overides speed)
"wait"			wait before returning (3 default, -1 = never return)
"lip"				lip remaining at end of move (8 default)
"dmg"				damage to inflict when blocked (0 default)
"key"          The item needed to open this door (default nothing)

"sound_stop"		Specify the sound that plays when the door stops moving (default global door_stop)
"sound_move"		Specify the sound that plays when the door opens or closes (default global door_moving)
"sound_message"	Specify the sound that plays when the door displays a message
"sound_locked"	   Specify the sound that plays when the door is locked

******************************************************************************/

Event EV_SlidingDoor_Setup
	( 
	"setup",
	EV_HIDE,
   NULL,
   NULL,
   "Sets up the sliding door."
	);
Event EV_SlidingDoor_SetLip
	( 
	"lip",
	EV_DEFAULT,
   "f",
   "lip",
   "Sets the lip of the sliding door."
	);
Event EV_SlidingDoor_SetSpeed
	( 
	"speed",
	EV_DEFAULT,
   "f",
   "speed",
   "Sets the speed of the sliding door."
	);

CLASS_DECLARATION( Door, SlidingDoor, "func_door" )
	{
	   { &EV_Door_DoClose,		            DoClose },
	   { &EV_Door_DoOpen,		            DoOpen },
      { &EV_SlidingDoor_Setup,            Setup },
      { &EV_SlidingDoor_SetLip,           SetLip },
      { &EV_SlidingDoor_SetSpeed,         SetSpeed },
      { &EV_SetAngle,                     SetMoveDir },
		{ NULL, NULL }
	};

void SlidingDoor::SetMoveDir
   (
   Event *ev
   )

   {
   float t;
   float angle;

   angle = ev->GetFloat( 1 );
	movedir = G_GetMovedir( angle );
   dir = movedir;
	t = dir[ 0 ];
	dir[ 0 ] = -dir[ 1 ];
	dir[ 1 ] = t;
   }

void SlidingDoor::DoOpen
   (
 	Event *ev
   )

	{
	MoveTo( pos2, angles, speed*totalmove, EV_Door_OpenEnd );
   }

void SlidingDoor::DoClose
   (
 	Event *ev
   )

	{
	MoveTo( pos1, angles, speed*totalmove, EV_Door_CloseEnd );
   }

void SlidingDoor::SetLip
   (
   Event *ev
   )

   {
   lip = ev->GetFloat( 1 );
   CancelEventsOfType( EV_SlidingDoor_Setup );
   PostEvent( EV_SlidingDoor_Setup, EV_POSTSPAWN );
   }

void SlidingDoor::SetSpeed
   (
   Event *ev
   )

   {
   basespeed = ev->GetFloat( 1 );
   CancelEventsOfType( EV_SlidingDoor_Setup );
   PostEvent( EV_SlidingDoor_Setup, EV_POSTSPAWN );
   }

void SlidingDoor::Setup
   (
   Event *ev
   )

   {
	totalmove = fabs( movedir * size ) - lip;
   pos1 = origin;
	pos2 = pos1 + movedir * totalmove;

	if ( basespeed )
      {
      speed = basespeed / totalmove;
      }
   }

SlidingDoor::SlidingDoor()
	{
   if ( LoadingSavegame )
      {
      return;
      }
	lip = 8;
	basespeed = 0;
	movedir = G_GetMovedir( 0 );

   PostEvent( EV_SlidingDoor_Setup, EV_POSTSPAWN );
	}

/*****************************************************************************/
/*QUAKED script_door (0 0.5 1) ? START_OPEN x DOOR_DONT_LINK NOT_PLAYERS NOT_MONSTERS TOGGLE AUTO_OPEN TARGETED
if two doors touch, they are assumed to be connected and operate as a unit.

TOGGLE causes the door to wait in both the start and end states for a trigger event.
DOOR_DONT_LINK is for when you have two doors that are touching but you want to operate independently.

START_OPEN causes the door to move to its destination when spawned, and operate in reverse.  It is used to temporarily or permanently close off an area when triggered (not usefull for touch or takedamage doors).
OPEN_DIRECTION indicates which direction to open when START_OPEN is set.
AUTO_OPEN causes the door to open when a player is near instead of waiting for the player to use the door.
TARGETED door is only operational from triggers or script

"message"		is printed when the door is touched if it is a trigger door and it hasn't been fired yet
"angle"			determines the opening direction.  point toward the middle of the door (away from the hinge)
"targetname"	if set, no touch field will be spawned and a remote button or trigger field activates the door.
"health"			if set, door must be shot open
"speed"			move speed (100 default)
"time"			move time (1/speed default, overides speed)
"wait"			wait before returning (3 default, -1 = never return)
"dmg"				damage to inflict when blocked (0 default)
"key"          The item needed to open this door (default nothing)
"initthread"   code to execute to setup the door (optional)
"openthread"   code to execute when opening the door (required)
               The openthread should send the "dooropened" event to the door, when it is completely open
"closethread"  code to execute when closing the door (required)
               The closethread should send the "doorclosed" event to the door, when it is completely closed

"sound_stop"		Specify the sound that plays when the door stops moving (default global door_stop)
"sound_move"		Specify the sound that plays when the door opens or closes (default global door_moving)
"sound_message"	Specify the sound that plays when the door displays a message
"sound_locked"	   Specify the sound that plays when the door is locked

******************************************************************************/

Event EV_ScriptDoor_DoInit
	( 
	"doinit",
	EV_DEFAULT,
   NULL,
   NULL,
   "Sets up the script door."
	);
Event EV_ScriptDoor_SetOpenThread
	( 
	"openthread",
	EV_DEFAULT,
   "s",
   "openthread",
   "Set the thread to run when the door is opened (required)."
	);
Event EV_ScriptDoor_SetCloseThread
	( 
	"closethread",
	EV_DEFAULT,
   "s",
   "closethread",
   "Set the thread to run when the door is closed (required)."
	);
Event EV_ScriptDoor_SetInitThread
	( 
	"initthread",
	EV_DEFAULT,
   "s",
   "initthread",
   "Set the thread to run when the door is initialized (optional)."
	);

CLASS_DECLARATION( Door, ScriptDoor, "script_door" )
	{
	   { &EV_ScriptDoor_DoInit,		      DoInit },
	   { &EV_Door_DoClose,		            DoClose },
	   { &EV_Door_DoOpen,		            DoOpen },
	   { &EV_ScriptDoor_SetInitThread,     SetInitThread },
	   { &EV_ScriptDoor_SetOpenThread,     SetOpenThread },
	   { &EV_ScriptDoor_SetCloseThread,    SetCloseThread },
      { &EV_SetAngle,                     SetMoveDir },
		{ NULL, NULL }
	};

void ScriptDoor::SetMoveDir
   (
   Event *ev
   )

   {
   float t;
   float angle;

   angle = ev->GetFloat( 1 );
	movedir = G_GetMovedir( angle );
   dir = movedir;
	t = dir[ 0 ];
	dir[ 0 ] = -dir[ 1 ];
	dir[ 1 ] = t;
   }

void ScriptDoor::SetOpenThread
   (
 	Event *ev
   )
	{
   openthreadname = ev->GetString( 1 );
   }

void ScriptDoor::SetCloseThread
   (
 	Event *ev
   )
	{
   closethreadname = ev->GetString( 1 );
   }

void ScriptDoor::DoInit
   (
 	Event *ev
   )
	{
   const char * label = NULL;
   GameScript * s;
   const char * tname;

   startorigin = origin;
	doorsize = fabs( movedir * size );

   //
   // see if we have an openthread
   //
   if ( !openthreadname.length() )
      {
      warning( "ScriptDoor", "No openthread defined for door at %.2f %.2f %.2f", origin[0], origin[1], origin[2] );
      }

   //
   // see if we have an closethread
   //
   if ( !closethreadname.length() )
      {
      warning( "ScriptDoor", "No closethread defined for door at %.2f %.2f %.2f", origin[0], origin[1], origin[2] );
      }

   s = ScriptLib.GetScript( ScriptLib.GetGameScript() );
   if ( !s )
      {
      warning( "DoInit", "Null game script" );
      return;
      }

   if ( initthreadname.length() )
      label = initthreadname.c_str();

	doorthread = Director.CreateThread( s, label, MODEL_SCRIPT );
   if ( !doorthread )
      {
      warning( "DoInit", "Could not allocate thread." );
      return;
      }
	doorthread->Vars()->SetVariable( "self", this );
   tname = TargetName();
   if ( tname && tname[ 0 ] )
      {
      str name;
      name = "$" + str( tname );
	   doorthread->Vars()->SetVariable( "targetname", name.c_str() );
      }
	doorthread->Vars()->SetVariable( "startorigin", startorigin );
	doorthread->Vars()->SetVariable( "startangles", startangle );
	doorthread->Vars()->SetVariable( "movedir", movedir );
	doorthread->Vars()->SetVariable( "doorsize", doorsize );
   if ( initthreadname.length() )
      {
      // start right away
      doorthread->StartImmediately();
      }
   }

void ScriptDoor::DoOpen
   (
 	Event *ev
   )

	{
   if ( !doorthread )
      {
      warning( "DoOpen", "No Thread allocated." );
      return;
      }
   else
      {
      if ( !doorthread->Goto( openthreadname.c_str() ) )
         {
         warning( "DoOpen", "Could not goto %s", openthreadname.c_str() );
         return;
         }
      }

   if ( previous_state == STATE_CLOSED )
      {
      diropened = 0;
      if ( ev->NumArgs() > 0 )
         {
   	   Entity *other;
	      Vector p;

	      other = ev->GetEntity( 1 );
         p = other->origin - origin;
         p.z = 0;
         diropened = dir * p;
         }
      }
   doorthread->Vars()->SetVariable( "origin", origin );
	doorthread->Vars()->SetVariable( "opendot", diropened );
   doorthread->Start( 0 );
   }

void ScriptDoor::DoClose
   (
 	Event *ev
   )
	{
   if ( !doorthread )
      {
      warning( "DoClose", "No Thread allocated." );
      return;
      }
   else
      {
      if ( !doorthread->Goto( closethreadname.c_str() ) )
         {
         warning( "DoOpen", "Could not goto %s", closethreadname.c_str() );
         }
      }
   doorthread->Vars()->SetVariable( "origin", origin );
   doorthread->Start( 0 );
   }

void ScriptDoor::SetInitThread
   (
   Event *ev
   )

   {
   initthreadname = ev->GetString( 1 );
   }

ScriptDoor::ScriptDoor()
	{
   if ( LoadingSavegame )
      {
      return;
      }
	startangle = angles;

   //
   // clear out the sounds if necessary
   // scripted doors typically have their own sounds
   //
   sound_stop = "";
   sound_move = "";

	movedir = G_GetMovedir( 0 );

   PostEvent( EV_ScriptDoor_DoInit, EV_POSTSPAWN );
	}
