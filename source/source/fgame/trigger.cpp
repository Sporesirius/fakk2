//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/trigger.cpp                        $
// $Revision:: 56                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/27/00 9:52p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/trigger.cpp                             $
// 
// 56    7/27/00 9:52p Markd
// got keyed triggers to work correctly
// 
// 55    7/27/00 6:31p Markd
// made useAnim's work with doors, added key ability
// 
// 54    7/24/00 10:41p Markd
// fixed trigger push problems
// 
// 53    7/18/00 3:29p Markd
// added better caching for sounds in general
// 
// 52    7/14/00 11:45p Markd
// Added ambient sounds to func_supllywater
// 
// 51    7/14/00 5:39p Steven
// Added a check in Trigger::StartThread to make sure ent is not NULL before
// using it.
// 
// 50    7/14/00 4:44p Steven
// Made TriggerGivePowerup be triggerable by actors also.
// 
// 49    7/11/00 9:42p Markd
// Added activator_targetname
// 
// 48    7/10/00 11:58p Markd
// fixed level exit issues
// 
// 47    7/10/00 11:54p Markd
// added exit level code
// 
// 46    7/07/00 4:22p Markd
// fixed save game bug
// 
// 45    7/06/00 9:53p Markd
// added local.other to threads that are called from triggers
// 
// 44    7/04/00 3:06p Markd
// fixed explode object bug where models were being orientated incorrectly
// 
// 43    6/30/00 3:08p Markd
// fixed rise animation issues
// 
// 42    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 41    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 40    6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 39    5/30/00 7:06p Markd
// saved games 4th pass
// 
// 38    5/25/00 10:00a Steven
// Fixed an edgetrigger/one time trigger bug and added givepowerup trigger.
// 
// 37    4/15/00 4:49p Markd
// Added damage_type
// 
// 36    4/12/00 10:01a Markd
// fixed Trigger set damage functions
// 
// 35    3/31/00 1:14p Markd
// Added trigger cone support
// 
// 34    3/03/00 4:42p Markd
// added in debugging messages for music and reverb
// 
// 33    3/03/00 4:18p Markd
// Added up/down multi-facet support
// 
// 32    3/02/00 6:55p Markd
// Added reverb triggers
// 
// 31    2/29/00 6:56p Jimdose
// made spawnspots work
// 
// 30    2/22/00 3:11p Steven
// Fixed an event documentation typo.
// 
// 29    2/22/00 1:57p Jimdose
// added TriggerByPushObject
// 
// 28    2/04/00 3:11p Aldie
// Changed sword attack method for water usage
// 
// 27    1/22/00 2:05p Markd
// made "volume" an EV_DEFAULT command instead of a EV_CONSOLE command
// 
// 26    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 25    1/14/00 5:07p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 24    1/10/00 6:17p Jimdose
// more code cleanup
// 
// 23    12/20/99 3:00p Markd
// fixed more music system bugs
// 
// 22    12/20/99 11:41a Markd
// Fixed a music trigger issue
// 
// 21    11/15/99 10:40a Markd
// made it so that directed triggers, when not triggered in the proper
// direction, delay re-triggering for 1 second.
// 
// 20    11/12/99 6:52p Markd
// fixed up sound manager saving and loading
// 
// 19    11/12/99 11:47a Markd
// Added sound manager support and retro-fitted TriggerSpeaker and TriggerMusic
// to work with everything
// 
// 18    11/01/99 6:12p Steven
// Changed some old attenuation stuff to min dist stuff.
// 
// 17    10/27/99 12:19p Markd
// added smooth camera lerping
// 
// 16    10/22/99 4:57p Markd
// Added documentation to triggers
// 
// 15    10/21/99 2:56p Markd
// Added triggerable and nottriggerable
// 
// 14    10/14/99 7:01p Markd
// Added first run of func_fullcrum
// 
// 13    10/14/99 5:08p Markd
// removed a lot of G_GetMoveDir calls from the initialization code
// 
// 12    10/12/99 2:23p Markd
// Rewrote camera and player movetype system
// 
// 11    10/07/99 3:00p Steven
// Event formatting.
// 
// 10    10/02/99 6:51p Markd
// Put in backend work for event documentation and fixed a lot of event
// documentation bugs
// 
// 9     10/01/99 10:31a Markd
// added TriggerSetVariable
// 
// 8     9/30/99 1:49p Aldie
// Documentation of commands
// 
// 7     9/29/99 11:52a Markd
// removed some unused enums and variables form shared headers between cgame
// and fgame
// 
// 6     9/28/99 4:09p Markd
// Changed entity color of all triggers
// 
// 5     9/27/99 5:45p Markd
// began documentation and cleanup phase after merge
// 
// 4     9/22/99 4:48p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 3     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 34    9/02/99 3:06p Markd
// Fixed speakers, precaching of models and appending "models" and
// automatically caching in projectiles.
// 
// 33    9/01/99 9:35p Markd
// fixed camera triggering issues with centerprint
// 
// 32    9/01/99 5:38p Markd
// made trigger messages work when triggered from camera
// 
// 31    8/30/99 2:37p Steven
// Added support for volume and minimum distance for loop sounds.
// 
// 30    8/28/99 11:45a Steven
// Removed global from sound function calls.
// 
// 29    8/23/99 5:48p Steven
// Added a music trigger type.
// 
// 28    7/08/99 4:56p Markd
// removed areaportal.h includes
// 
// 27    7/08/99 4:28p Markd
// Removed obsolete QUAKED functions
// 
// 26    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
// 
// 25    6/11/99 2:20p Phook
// Renamed a few entities
// 
// 24    6/11/99 1:23p Phook
// 
// 23    6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
// 
// 22    6/11/99 12:46p Phook
// EClass color changes
//
// DESCRIPTION:
// Environment based triggers.
//

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "scriptmaster.h"
#include "worldspawn.h"
#include "misc.h"
#include "specialfx.h"
#include "sentient.h"
#include "item.h"
#include "player.h"
#include "camera.h"
#include "actor.h"
#include "g_utils.h"
#include "weaputils.h"

Event EV_Trigger_ActivateTargets
   (
   "activatetrigger",
	EV_DEFAULT,
   "e",
   "triggering_entity",
   "Activates all of the targets for this trigger."
   );
Event EV_Trigger_SetWait
   (
   "wait",
   EV_DEFAULT,
   "f",
   "wait_time",
   "Set the wait time (time bewteen triggerings) for this trigger"
   );
Event EV_Trigger_SetDelay
   (
   "delay",
   EV_DEFAULT,
   "f",
   "delay_time",
   "Set the delay time (time between triggering and firing) for this trigger"
   );
Event EV_Trigger_SetCount
   (
   "cnt",
   EV_DEFAULT,
   "i",
   "count",
   "Set the amount of times this trigger can be triggered"
   );
Event EV_Trigger_SetMessage
   (
   "message",
   EV_DEFAULT,
   "s",
   "message",
   "Set a message to be displayed when this trigger is activated"
   );
Event EV_Trigger_SetNoise
   (
   "noise",
   EV_DEFAULT,
   "s",
   "sound",
   "Set the sound to play when this trigger is activated"
   );
Event EV_Trigger_SetSound
   (
   "sound",
   EV_DEFAULT,
   "s",
   "sound",
   "Set the sound to play when this trigger is activated"
   );
Event EV_Trigger_SetThread
   (
   "thread",
   EV_DEFAULT,
   "s",
   "thread",
   "Set the thread to execute when this trigger is activated"
   );
Event EV_Trigger_Effect
   (
   "triggereffect",
	EV_DEFAULT,
   "e",
   "triggering_entity",
   "Send event to owner of trigger."
   );
Event EV_Trigger_Effect_Alt
   (
   "triggereffectalt",
	EV_DEFAULT,
   "e",
   "triggering_entity",
   "Send event to owner of trigger.  This event is only triggered when using a trigger\n"
   "as a multi-faceted edge trigger."
   );
Event EV_Trigger_StartThread
   (
   "triggerthread",
	EV_DEFAULT,
   NULL,
   NULL,
   "Start the trigger thread." 
   );
Event EV_Trigger_SetKey
   (
   "key",
   EV_DEFAULT,
   "s",
   "key",
   "Set the object needed by the sentient to activate this trigger"
   );

Event EV_Trigger_SetTriggerable
   (
   "triggerable",
   EV_DEFAULT,
   NULL,
   NULL,
   "Turn this trigger back on"
   );

Event EV_Trigger_SetNotTriggerable
   (
   "nottriggerable",
   EV_DEFAULT,
   NULL,
   NULL,
   "Turn this trigger off"
   );

Event EV_Trigger_SetMultiFaceted
   (
   "multifaceted",
   EV_DEFAULT,
   "i",
   "facetDirection",
   "Make this trigger multifaceted.  If facet is 1, than trigger is North/South oriented.\n"
   "If facet is 2 than trigger is East/West oriented. If facet is 3 than trigger is Up/Down oriented."
   );

Event EV_Trigger_SetEdgeTriggered
   (
   "edgetriggered",
   EV_DEFAULT,
   "b",
   "newEdgeTriggered",
   "If true, trigger will only trigger when object enters trigger, not when it is inside it."
   );

Event EV_Trigger_SetTriggerCone
   (
   "cone",
   EV_DEFAULT,
   "f",
   "newTriggerCone",
   "Sets the cone in which directed triggers will trigger."
   );


#define MULTI_ACTIVATE	1
#define INVISIBLE			2

#define VISIBLE			1

#define TRIGGER_PLAYERS			4
#define TRIGGER_MONSTERS		8
#define TRIGGER_PROJECTILES	16

/*****************************************************************************/
/*QUAKED trigger_multiple (1 0 0) ? x x NOT_PLAYERS MONSTERS PROJECTILES

Variable sized repeatable trigger.  Must be targeted at one or more entities.

If "health" is set, the trigger must be killed to activate each time.
If "delay" is set, the trigger waits some time after activating before firing.

"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

if "angle" is set, the trigger will only fire when someone is facing the
direction of the angle.
"cone" the cone in which a directed trigger can be triggered (default 60 degrees)

"wait" : Seconds between triggerings. (.2 default)
"cnt" how many times it can be triggered (infinite default)

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

set "message" to text string

******************************************************************************/

CLASS_DECLARATION( Animate, Trigger, "trigger_multiple" )
	{
	   { &EV_Trigger_SetWait,				EventSetWait },
	   { &EV_Trigger_SetDelay,				EventSetDelay },
	   { &EV_Trigger_SetCount,				EventSetCount },
	   { &EV_Trigger_SetMessage,			EventSetMessage },
	   { &EV_Trigger_SetNoise,				EventSetNoise },
	   { &EV_Trigger_SetSound,				EventSetNoise },
      { &EV_Trigger_SetThread,		   EventSetThread },
      { &EV_SetHealth,                 EventSetHealth },
	   { &EV_Touch,							TriggerStuff },
	   { &EV_Killed,							TriggerStuff },
	   { &EV_Activate,						TriggerStuff },
	   { &EV_Trigger_ActivateTargets,	ActivateTargets },
	   { &EV_Trigger_SetKey,				EventSetKey },
	   { &EV_Trigger_StartThread,			StartThread },
      { &EV_Model,                     SetModelEvent },
      { &EV_SetAngle,                  SetTriggerDir },
      { &EV_Trigger_SetTriggerable,    SetTriggerable },
      { &EV_Trigger_SetNotTriggerable, SetNotTriggerable },
      { &EV_Trigger_SetMultiFaceted,   SetMultiFaceted },
      { &EV_Trigger_SetEdgeTriggered,  SetEdgeTriggered },
      { &EV_Trigger_SetTriggerCone,    SetTriggerCone },
      { NULL, NULL }
	};

Trigger::Trigger()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
	triggerActivated	= false;
	activator			= NULL;
	trigger_time		= (float)0;

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_TRIGGER );

   setContents( 0 );
   //edict->contents = CONTENTS_TRIGGER;		// replaces the -1 from gi.SetBrushModel
	edict->svflags |= SVF_NOCLIENT;

	delay = 0;
	wait  = 0.2;
	health = 0;
	max_health = 0;
   triggerCone = cos( DEG2RAD( 60 ) );

   useTriggerDir = qfalse;
   triggerDir = G_GetMovedir( 0 );

   triggerable = qtrue;
   removable = qtrue;

	trigger_time = (float)0;
   // normal trigger to begin with
   multiFaceted = 0;
   // normally, not edge triggered
   edgeTriggered = qfalse;

	count = -1;

	//noise = "environment/switch/switch2.wav";
   noise = "";

	respondto = spawnflags ^ TRIGGER_PLAYERS;
	}

Trigger::~Trigger()
	{
	}

void Trigger::SetTriggerDir
	(
   float angle
	)

   {
   triggerDirYaw = angle;
   triggerDir = G_GetMovedir( angle );
   useTriggerDir = qtrue;
   }

Vector Trigger::GetTriggerDir
	(
   void
	)

   {
   return triggerDir;
   }

void Trigger::SetTriggerCone
	(
	Event *ev
	)

   {
   triggerCone = cos( DEG2RAD( ev->GetFloat( 1 ) ) );
   }

qboolean Trigger::UsingTriggerDir
   (
   void 
   )
   {
   return useTriggerDir;
   }

void Trigger::SetTriggerDir
	(
	Event *ev
	)

   {
   SetTriggerDir( ev->GetFloat( 1 ) );
   }

void Trigger::SetModelEvent
	(
	Event *ev
	)

   {
   Animate::SetModelEvent( ev );
   setContents( 0 );
   //edict->contents = CONTENTS_TRIGGER;		// replaces the -1 from gi.SetBrushModel
	edict->svflags |= SVF_NOCLIENT;
   link();
   }

void Trigger::StartThread
	(
	Event *ev
	)

	{
   if ( thread.length() )
      {
      ScriptThread * threadPtr;

      threadPtr = ExecuteThread( thread, qfalse );
      if ( !threadPtr )
         {
         warning( "StartThread", "Null game script" );
         }
      else
         {
         if ( ev->NumArgs() > 0 )
            {
            Entity * ent;

            ent = ev->GetEntity( 1 );

      	   threadPtr->Vars()->SetVariable( "activator", ent );

				if ( ent )
      			threadPtr->Vars()->SetVariable( "activator_targetname", ent->TargetName() );
            }
         threadPtr->StartImmediately();
         }
      }
   }

qboolean Trigger::respondTo
   (
   Entity *other
   )

   {
	return ( ( ( respondto & TRIGGER_PLAYERS ) && other->isClient() ) ||
		( ( respondto & TRIGGER_MONSTERS ) && other->isSubclassOf( Actor ) ) ||
		( ( respondto & TRIGGER_PROJECTILES ) && other->isSubclassOf( Projectile ) ) );
   }

Entity *Trigger::getActivator
   (
   Entity *other
   )

   {
   return other;
   }

void Trigger::TriggerStuff
	(
	Event *ev
	)

	{
	Entity *other;
   Entity *activator;
	Event *event;
   int    whatToTrigger;

   // if trigger is shut off return immediately
   if ( !triggerable )
      {
      return;
      }

   // Don't bother with testing anything if we can't trigger yet
   if ( ( level.time < trigger_time ) || ( trigger_time == -1 ) )
		{
      // if we are edgeTriggered, we reset our time until we leave the trigger
      if ( edgeTriggered && trigger_time != -1 )
         {
      	trigger_time = level.time + wait;
         }
		return;
		}

	health = max_health;
	if ( health && ( ( int )*ev != ( int )EV_Killed ) && ( ( int )*ev != ( int )EV_Activate ) )
		{
		// if health is set, we only respond to killed and activate messages
		return;
		}

	other = ev->GetEntity( 1 );

	assert( other != this );

	// Always respond to activate messages from the world since they're probably from
	// the "trigger" command
	if ( !respondTo( other ) && !( ( other == world ) && ( ( int )*ev == ( int )EV_Activate ) ) &&
      ( !other || !other->isSubclassOf( Camera ) ) )
		{
		return;
		}

   //
   // if we setup an angle for this trigger, only trigger if other is within ~60 degrees of the triggers origin
   // only test for this case if we were touched, activating or killed should never go through this code
   //
   if ( useTriggerDir && ( ( int )*ev == ( int )EV_Touch ) )
      {
      Vector norm;
      float dot;

      norm = origin - other->origin;
      norm.normalize();
      dot = norm * triggerDir;
      if ( dot < triggerCone )
         {
         // don't retrigger for at least a second
      	trigger_time = level.time + 1;
         return;
         }
      }

   activator = getActivator( other );

   if ( key.length() )
      {
      if ( !activator->isSubclassOf( Sentient ) )
         {
         return;
         }
      if ( !( ( (Sentient *)activator )->HasItem( key.c_str() ) ) )
         {
         qboolean    setModel;
         Item        *item;
         ClassDef		*cls;
         str         dialog;

         cls = FindClass( key.c_str(), &setModel );
		   if ( !cls || !checkInheritance( "Item", cls->classname ) )
			   {
            gi.DPrintf( "No item named '%s'\n", key.c_str() );
            return;
			   }
		   item = ( Item * )cls->newInstance();
         if ( setModel )
            {
            item->setModel( key.c_str() );
            }
         item->CancelEventsOfType( EV_Item_DropToFloor );
	      item->CancelEventsOfType( EV_Remove );
         item->ProcessPendingEvents();
         dialog = item->GetDialogNeeded();
         if ( dialog.length() > 1 )
            {
            activator->Sound( dialog );
            }
         else
            {
            gi.centerprintf ( activator->edict, "You need the %s", item->getName() );
            }
         delete item;
         return;
         }
      }

   if ( multiFaceted )
      {
      Vector delta;

      delta = other->origin - origin;
      switch( multiFaceted )
         {
         case 1:
            if ( delta[ 1 ] > 0 )
               {
               whatToTrigger = 0;
               }
            else
               {
               whatToTrigger = 1;
               }
            break;
         case 2:
            if ( delta[ 0 ] > 0 )
               {
               whatToTrigger = 0;
               }
            else
               {
               whatToTrigger = 1;
               }
            break;
         case 3:
         default:
            if ( delta[ 2 ] > 0 )
               {
               whatToTrigger = 0;
               }
            else
               {
               whatToTrigger = 1;
               }
            break;
         }
      }
   else
      {
      whatToTrigger = 0;
      }

	trigger_time = level.time + wait;

   if ( !whatToTrigger )
      {
	   event = new Event( EV_Trigger_Effect );
	   event->AddEntity( activator );
	   PostEvent( event, delay );
      }
   else
      {
	   event = new Event( EV_Trigger_Effect_Alt );
	   event->AddEntity( activator );
	   PostEvent( event, delay );
      }

	event = new Event( EV_Trigger_ActivateTargets );
	event->AddEntity( activator );
	PostEvent( event, delay );

   if ( thread.length() )
      {
      // don't trigger the thread if we were triggered by the world touching us
      if ( ( activator != world ) || ( ev->GetSource() != EV_FROM_CODE ) )
         {
	      event = new Event( EV_Trigger_StartThread );
         if ( activator )
            {
            event->AddEntity( activator );
            }
   	   PostEvent( event, delay );
         }
      }

	if ( count > -1 )
		{
		count--;
		if ( count < 1 )
			{
			//
			// Don't allow it to trigger anymore
			//
			trigger_time = -1;

			//
			// Make sure we wait until we're done triggering things before removing
			//
         if ( removable )
            {
			   PostEvent( EV_Remove, delay + FRAMETIME );
            }
			}
		}
	}

//
//==============================
// ActivateTargets
//
// "other" should be set to the entity that initiated the firing.
//
// Centerprints any message to the activator.
//
// Removes all entities with a targetname that match killtarget,
// so some events can remove other triggers.
//
// Search in targetname of all entities that match target
// and send EVENT_ACTIVATE to there event handler
//==============================
//
void Trigger::ActivateTargets
	(
	Event *ev
	)

	{
	Entity	*other;
	Entity	*ent;
	Event		*event;
	const char *name;

	other = ev->GetEntity( 1 );

   if ( !other )
      other = world;

	if ( triggerActivated )
		{
		//
		// Entity triggered itself.  Prevent an infinite loop
		//
		ev->Error( "Entity targeting itself--Targetname '%s'", TargetName() );
		return;
		}

	triggerActivated = true;
	activator = other;

//
// print the message
//
	if ( message.length() && other && ( other->isClient() || other->isSubclassOf( Camera ) ) )
		{
      // HACK HACK HACK
      // if it is a camera, pass in default player
      if ( !other->isClient() )
         {
		   gi.centerprintf( &g_entities[ 0 ], message.c_str() );
         }
      else
         {
		   gi.centerprintf( other->edict, message.c_str() );
         }
		if ( Noise().length() )
			{
			other->Sound( noise.c_str(), CHAN_VOICE );
			}
		}

//
// kill the killtargets
//
	name = KillTarget();
	if ( name && strcmp( name, "" ) )
		{
      ent = NULL;
		do
			{
			ent = G_FindTarget( ent, name );
			if ( !ent )
				{
				break;
				}
			ent->PostEvent( EV_Remove, 0 );
			}
		while ( 1 );
		}

//
// fire targets
//
	name = Target();
	if ( name && strcmp( name, "" ) )
		{
      ent = NULL;
		do
			{
			ent = G_FindTarget( ent, name );
			if ( !ent )
				{
				break;
				}

			event = new Event( EV_Activate );
			event->AddEntity( other );
			ent->ProcessEvent( event );
			}
		while ( 1 );
		}

	triggerActivated = false;
	}

void Trigger::EventSetWait
	(
	Event *ev
	)

	{
	wait = ev->GetFloat( 1 );
   }

void Trigger::EventSetDelay
	(
	Event *ev
	)

	{
	delay = ev->GetFloat( 1 );
	}

void Trigger::EventSetKey
	(
	Event *ev
	)

	{
	key = ev->GetString( 1 );
	}

void Trigger::EventSetThread
   (
   Event *ev
   )

   {
   thread = ev->GetString( 1 );
   }

void Trigger::EventSetHealth
	(
	Event *ev
	)

	{
	health = ev->GetFloat( 1 );
   max_health = health;
	if ( health )
		{
		takedamage = DAMAGE_YES;
		setSolidType( SOLID_BBOX );
		}
   else
      {
	   setMoveType( MOVETYPE_NONE );
	   setSolidType( SOLID_TRIGGER );
      }
   }

void Trigger::EventSetCount
	(
	Event *ev
	)

	{
	count = ev->GetInteger( 1 );
   }

void Trigger::EventSetMessage
	(
	Event *ev
	)

	{
  	SetMessage( ev->GetString( 1 ) );
	}

void Trigger::SetMessage
	(
	const char *text
	)

	{
   if ( text )
      {
      message = str( text );
      }
   else
      {
      message = "";
      }
	}

str &Trigger::Message
	(
	void
	)

	{
   return message;
	}

void Trigger::EventSetNoise
	(
	Event *ev
	)

	{
   SetNoise( ev->GetString( 1 ) );
	}

void Trigger::SetNoise
	(
	const char *text
	)

	{
   if ( text )
      {
      noise = str( text );
      //
      // cache in the sound
      //
      CacheResource( noise.c_str(), this );
      }
	}

str &Trigger::Noise
	(
	void
	)

	{
	return noise;
	}

void Trigger::SetMultiFaceted
	(
   int newFacet
	)
	{
   multiFaceted = newFacet;
	}

void Trigger::SetEdgeTriggered
	(
   qboolean newEdge
	)
	{
   edgeTriggered = newEdge;
	}

int Trigger::GetMultiFaceted
	(
   void
	)
	{
   return multiFaceted;
	}

qboolean Trigger::GetEdgeTriggered
	(
   void
	)
	{
   return edgeTriggered;
	}

void Trigger::SetMultiFaceted
	(
	Event *ev
	)
	{
   SetMultiFaceted( ev->GetInteger( 1 ) );
	}

void Trigger::SetEdgeTriggered
	(
	Event *ev
	)
	{
   SetEdgeTriggered( ev->GetBoolean( 1 ) );
	}

void Trigger::SetTriggerable
	(
	Event *ev
	)
	{
   triggerable = qtrue;
	}

void Trigger::SetNotTriggerable
	(
	Event *ev
	)
	{
   triggerable = qfalse;
	}


CLASS_DECLARATION( Trigger, TouchField, NULL )
	{
	   { &EV_Trigger_Effect,				SendEvent },
		{ NULL, NULL }
	};

TouchField::TouchField()
   {
   ontouch = NULL;
   }

void TouchField::Setup
	(
	Entity *ownerentity,
	Event &touchevent,
	Vector min,
	Vector max,
	int respondto
	)

	{
	assert( ownerentity );
	if ( !ownerentity )
		{
		error( "Setup", "Null owner" );
		}

	owner = ownerentity;
   if ( ontouch )
      {
      delete ontouch;
      }
	ontouch	= new Event( touchevent );
	setSize( min, max );

   setContents( 0 );
   setSolidType( SOLID_TRIGGER );
   link();

	this->respondto = respondto;
	}

void TouchField::SendEvent
	(
	Event *ev
	)

	{
	Event *event;

   // Check if our owner is still around
   if ( owner )
      {
	   event = new Event( ontouch );
	   event->AddEntity( ev->GetEntity( 1 ) );
	   owner->PostEvent( event, delay );
      }
   else
      {
      // Our owner is gone!  The bastard didn't delete us!
      // Guess we're no longer needed, so remove ourself.
      PostEvent( EV_Remove, 0 );
      }
	}

/*****************************************************************************/
/*QUAKED trigger_once (1 0 0) ? NOTOUCH x NOT_PLAYERS MONSTERS PROJECTILES

Variable sized trigger. Triggers once, then removes itself.
You must set the key "target" to the name of another object in the
level that has a matching

If "health" is set, the trigger must be killed to activate it.
If "delay" is set, the trigger waits some time after activating before firing.

"targetname".  If "health" is set, the trigger must be killed to activate.

"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

if "killtarget" is set, any objects that have a matching "target" will be
removed when the trigger is fired.

if "angle" is set, the trigger will only fire when someone is facing the
direction of the angle.
"cone" the cone in which a directed trigger can be triggered (default 60 degrees)

"key" The item needed to activate this. (default nothing)

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOTOUCH is set, trigger will not respond to touch
If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

set "message" to text string

******************************************************************************/

CLASS_DECLARATION( Trigger, TriggerOnce, "trigger_once" )
	{
		{ NULL, NULL }
	};

TriggerOnce::TriggerOnce()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
	//
	// no matter what, we only trigger once
	//
	count = 1;
	respondto = spawnflags ^ TRIGGER_PLAYERS;

   //
   // if it's not supposed to be touchable, clear the trigger
   //
   if ( spawnflags & 1 )
      {
	   setSolidType( SOLID_NOT );
      }
	}

/*****************************************************************************/
/*QUAKED trigger_relay (1 0 0) (-8 -8 -8) (8 8 8) x x NOT_PLAYERS MONSTERS PROJECTILES

This fixed size trigger cannot be touched, it can only be fired by other events.
It can contain killtargets, targets, delays, and messages.

If NOT_PLAYERS is set, the trigger does not respond to events triggered by players
If MONSTERS is set, the trigger will respond to events triggered by monsters
If PROJECTILES is set, the trigger will respond to events triggered by projectiles (rockets, grenades, etc.)

******************************************************************************/

CLASS_DECLARATION( Trigger, TriggerRelay, "trigger_relay" )
	{
		{ &EV_Touch,   NULL },
		{ NULL,        NULL }
	};

TriggerRelay::TriggerRelay()
	{
	setSolidType( SOLID_NOT );
	}


/*****************************************************************************/
/*QUAKED trigger_secret (1 0 0) ? NOTOUCH x NOT_PLAYERS MONSTERS PROJECTILES
Secret counter trigger.  Automatically sets and increments script variables \
level.total_secrets and level.found_secrets.

set "message" to text string

"key" The item needed to activate this. (default nothing)

if "angle" is set, the trigger will only fire when someone is facing the
direction of the angle.
"cone" the cone in which a directed trigger can be triggered (default 60 degrees)

"thread" name of thread to trigger.  This can be in a different script file as well \
by using the '::' notation.  (defaults to "global/universal_script.scr::secret")

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOTOUCH is set, trigger will not respond to touch
If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

******************************************************************************/

CLASS_DECLARATION( TriggerOnce, TriggerSecret, "trigger_secret" )
	{
		{ &EV_Trigger_Effect,		FoundSecret },
		{ NULL, NULL }
	};

TriggerSecret::TriggerSecret()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
	level.total_secrets++;
   levelVars.SetVariable( "total_secrets", level.total_secrets );
	respondto = spawnflags ^ TRIGGER_PLAYERS;

   // set the thread to trigger when secrets are found
   thread = "global/universal_script.scr::secret";
	}

void TriggerSecret::FoundSecret
	(
	Event *ev
	)

	{
	//
	// anything that causes the trigger to fire increments the number
   // of secrets found.  This way, if the level designer triggers the
   // secret from the script, the player still gets credit for finding
   // it.  This is to prevent a secret from becoming undiscoverable.
	//
	level.found_secrets++;
   levelVars.SetVariable( "found_secrets", level.found_secrets );
   }

/*****************************************************************************/
/*QUAKED trigger_setvariable (1 0 0) ? NOTOUCH LEVEL NOT_PLAYERS MONSTERS PROJECTILES 

Sets a variable specified by "variable" and "value".
Variable is assumed to be of the "global" variety unless LEVEL is set.
Variable sized trigger. Triggers once by default.
You must set the key "target" to the name of another object in the
level that has a matching

"variable" - variable to set
"value" - value to set in variable, value can also be one of the following reserved\
tokens.
   - "increment" - add one to the variable
   - "decrement" - subtract one from the variable
   - "toggle" - if 1, then zero.  If zero then 1.

If "health" is set, the trigger must be killed to activate it.
If "delay" is set, the trigger waits some time after activating before firing.

"targetname".  If "health" is set, the trigger must be killed to activate.

"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

if "killtarget" is set, any objects that have a matching "target" will be
removed when the trigger is fired.

if "angle" is set, the trigger will only fire when someone is facing the
direction of the angle.
"cone" the cone in which a directed trigger can be triggered (default 60 degrees)

"key" The item needed to activate this. (default nothing)

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOTOUCH is set, trigger will not respond to touch
if LEVEL is set, variable will be a level variable otherwise it will be a game variable
If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

set "message" to text string

******************************************************************************/

#define LEVEL_VARIABLE ( 1 << 1 )

Event EV_TriggerSetVariable_SetVariable
   (
   "variable",
   EV_DEFAULT,
   "s",
   "variableName",
   "Set the name of the variable to set"
   );
Event EV_TriggerSetVariable_SetVariableValue
   (
   "value",
   EV_DEFAULT,
   "s",
   "variableValue",
   "Set the value of the variable to set.\n"
   "values can also use one of the following reserved words:\n"
   "  increment - increment the variable\n"
   "  decrement - decrement the variable\n"
   "  toggle - toggle the value of the variable"
   );
CLASS_DECLARATION( Trigger, TriggerSetVariable, "trigger_setvariable" )
	{
		{ &EV_Trigger_Effect,		SetVariable },
      { &EV_TriggerSetVariable_SetVariable, SetVariableName },
      { &EV_TriggerSetVariable_SetVariableValue, SetVariableValue },
		{ NULL, NULL }
	};

TriggerSetVariable::TriggerSetVariable()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
	//
	// no matter what, we only trigger once
	//
	count = 1;
	respondto = spawnflags ^ TRIGGER_PLAYERS;

   //
   // if it's not supposed to be touchable, clear the trigger
   //
   if ( spawnflags & 1 )
      {
	   setSolidType( SOLID_NOT );
      }
   variableName = "undefined";
   variableValue = "notset";
   variableType = VAR_NORMAL;
	}

void TriggerSetVariable::SetVariableName
	(
	Event *ev
	)

	{
   variableName = ev->GetString( 1 );
   }

void TriggerSetVariable::SetVariableValue
	(
	Event *ev
	)

	{
   variableValue = ev->GetString( 1 );
   if ( variableValue == "increment" )
      {
      variableType = VAR_INCREMENT;
      }
   else if ( variableValue == "decrement" )
      {
      variableType = VAR_DECREMENT;
      }
   else if ( variableValue == "toggle" )
      {
      variableType = VAR_TOGGLE;
      }
   else
      {
      variableType = VAR_NORMAL;
      }
   }

void TriggerSetVariable::SetVariable
	(
	Event *ev
	)

	{
   ScriptVariable * var;
   int value;

   if ( spawnflags & LEVEL_VARIABLE )
      {
      var = levelVars.GetVariable( variableName );
      if ( !var )
         {
         var = levelVars.SetVariable( variableName, 0 );
         }
      }
   else
      {
      var = gameVars.GetVariable( variableName );
      if ( !var )
         {
         var = gameVars.SetVariable( variableName, 0 );
         }
      }

   assert( var );
   value = var->intValue();

   switch( variableType )
      {
      case VAR_INCREMENT:
         value++;
         break;
      case VAR_DECREMENT:
         value--;
         break;
      case VAR_TOGGLE:
         value = !value;
         break;
      }

   if ( variableType == VAR_NORMAL )
      {
      var->setStringValue( variableValue );
      }
   else
      {
      var->setIntValue( value );
      }
   }

/*****************************************************************************/
/*QUAKED trigger_push (1 0 0) ? x x NOT_PLAYERS NOT_MONSTERS NOT_PROJECTILES

Pushes entities as if they were caught in a heavy wind.

"speed" indicates the rate that entities are pushed (default 1000).

"angle" indicates the direction the wind is blowing (-1 is up, -2 is down)

"key" The item needed to activate this. (default nothing)

"target" if target is set, then a velocity will be calculated based on speed

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not push players
If NOT_MONSTERS is set, the trigger will not push monsters
If NOT_PROJECTILES is set, the trigger will not push projectiles (rockets, grenades, etc.)

******************************************************************************/

Event EV_TriggerPush_SetPushSpeed
   (
   "speed",
   EV_DEFAULT,
   "f",
   "speed",
   "Set the push speed of the TriggerPush"
   );

CLASS_DECLARATION( Trigger, TriggerPush, "trigger_push" )
	{
	   { &EV_Trigger_Effect,			   Push },
	   { &EV_SetAngle,	               SetPushDir },
	   { &EV_TriggerPush_SetPushSpeed,	SetPushSpeed },
		{ NULL, NULL }
	};

void TriggerPush::Push
	(
	Event *ev
	)

	{
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( other )
		{
      const char * targ;
	   Entity *ent;

      targ = Target ();
      if ( targ[ 0 ] )
         {
		   ent = G_FindTarget( NULL, Target() );
		   if ( ent )
            {
            other->velocity = G_CalculateImpulse
               (
               other->origin,
               ent->origin,
               speed,
               other->gravity
               );
            }
         }
      else
         {
         float dot;

         // find out how much velocity we have in this direction
         dot = triggerDir * other->velocity;
         // subtract it out and add in our velocity
         other->velocity += ( speed - dot ) * triggerDir;
         }

      other->VelocityModified();
		}
	}

void TriggerPush::SetPushDir
	(
	Event *ev
	)

	{
   float angle;

   angle = ev->GetFloat( 1 );
   // this is used, since we won't need elsewhere
   triggerDir = G_GetMovedir( angle );
   }


void TriggerPush::SetPushSpeed
	(
	Event *ev
	)

	{
   speed = ev->GetFloat( 1 );
   }

TriggerPush::TriggerPush()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   speed = 1000;
	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS | TRIGGER_PROJECTILES );
	}

/*****************************************************************************/
/*QUAKED trigger_pushany (1 0 0) ? x x NOT_PLAYERS NOT_MONSTERS NOT_PROJECTILES

Pushes entities as if they were caught in a heavy wind.

"speed" indicates the rate that entities are pushed (default 1000).
"angles" indicates the direction of the push
"key" The item needed to activate this. (default nothing)
"target" if target is set, then a velocity will be calculated based on speed

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not push players
If NOT_MONSTERS is set, the trigger will not push monsters
If NOT_PROJECTILES is set, the trigger will not push projectiles (rockets, grenades, etc.)

******************************************************************************/

Event EV_TriggerPushAny_SetSpeed
	( 
	"speed",
	EV_DEFAULT,
   "f",
   "speed",
   "Set the speed."
	);

CLASS_DECLARATION( Trigger, TriggerPushAny, "trigger_pushany" )
	{
      { &EV_TriggerPushAny_SetSpeed,   SetSpeed },
	   { &EV_Trigger_Effect,			   Push },
		{ NULL, NULL }
	};

TriggerPushAny::TriggerPushAny()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   speed = 1000;
	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS | TRIGGER_PROJECTILES );
	}

void TriggerPushAny::Push
	(
	Event *ev
	)

	{
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( other )
		{
	   Entity *ent;

      if ( target.length() )
         {
		   ent = G_FindTarget( NULL, target.c_str() );
		   if ( ent )
            {
            other->velocity = G_CalculateImpulse
               (
               other->origin,
               ent->origin,
               speed,
               other->gravity
               );
            }
         }
      else
         {
		   other->velocity = Vector( orientation[ 0 ] ) * speed;
         }
      other->VelocityModified();
		}
	}

void TriggerPushAny::SetSpeed
   (
   Event *ev
   )

   {
   speed = ev->GetFloat( 1 );
   }

//================================================================================================
//
// TriggerSound stuff
//
//================================================================================================

Event EV_TriggerPlaySound_SetVolume
	( 
	"volume",
	EV_DEFAULT,
   "f",
   "volume",
   "Sets the volume."
	);
Event EV_TriggerPlaySound_SetMinDist
	( 
	"min_dist",
	EV_DEFAULT,
   "f",
   "min_dist",
   "Sets the minimum distance."
	);
Event EV_TriggerPlaySound_SetChannel
	( 
	"channel",
	EV_DEFAULT,
   "i",
   "channel",
   "Sets the sound channel to play on."
	);

CLASS_DECLARATION( Trigger, TriggerPlaySound, "play_sound_triggered" )
	{
	   { &EV_Trigger_Effect,						   ToggleSound },
	   { &EV_TriggerPlaySound_SetVolume,		   SetVolume },
	   { &EV_TriggerPlaySound_SetMinDist,			SetMinDist },
	   { &EV_TriggerPlaySound_SetChannel,		   SetChannel },
		{ &EV_Touch,                              NULL },
		{ NULL, NULL }
	};

void TriggerPlaySound::ToggleSound
	(
	Event *ev
	)

	{
	if ( !state )
		{
		// noise should already be initialized
      if ( Noise().length() )
         {
         if ( ambient || spawnflags & TOGGLESOUND )
            {
 		      state = 1;
            }

         if ( ambient )
            {
			   LoopSound( Noise().c_str(), volume, min_dist );
            }
         else
            {
			   Sound( Noise(), channel, volume, min_dist );
            }
         }
		}
	else
		{
		state = 0;
      if ( ambient )
         {
			StopLoopSound();
         }
      else
         {
			StopSound( channel );
         }
		}
	}

void TriggerPlaySound::StartSound
	(
   void
	)

	{
   // turn the current one off
   state = 1;
   ToggleSound( NULL );

   // start it up again
   state = 0;
   ToggleSound( NULL );
	}

void TriggerPlaySound::SetVolume
	(
   float vol
	)

	{
	volume = vol;
	}


void TriggerPlaySound::SetVolume
	(
	Event *ev
	)

	{
	volume = ev->GetFloat( 1 );
	}

void TriggerPlaySound::SetMinDist
	(
   float dist
	)

	{
	min_dist = dist;
	}

void TriggerPlaySound::SetMinDist
	(
	Event *ev
	)

	{
	min_dist = ev->GetFloat( 1 );
	}

void TriggerPlaySound::SetChannel
	(
	Event *ev
	)

	{
	channel = ev->GetInteger( 1 );
	}

TriggerPlaySound::TriggerPlaySound()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   //
   // this is here so that it gets sent over at least once
   //
   PostEvent( EV_Show, EV_POSTSPAWN );

   ambient     = false;
	volume		= DEFAULT_VOL;
	channel		= CHAN_VOICE;
	state			= 0;
	respondto	= spawnflags ^ TRIGGER_PLAYERS;
   min_dist		= DEFAULT_MIN_DIST;

   if ( spawnflags & ( AMBIENT_ON | AMBIENT_OFF ) )
      {
      ambient = true;
      if ( spawnflags & AMBIENT_ON )
         {
         PostEvent( EV_Trigger_Effect, EV_POSTSPAWN );
         }
      }
	}

/*****************************************************************************/
/*QUAKED sound_speaker (0 0.75 0.75) (-8 -8 -8) (8 8 8) AMBIENT-ON AMBIENT-OFF NOT_PLAYERS MONSTERS PROJECTILES TOGGLE

play a sound when it is used

AMBIENT-ON specifies an ambient sound that starts on
AMBIENT-OFF specifies an ambient sound that starts off
TOGGLE specifies that the speaker toggles on triggering

if (AMBIENT-?) is not set, then the sound is sent over explicitly this creates more net traffic

"volume" how loud 0-4 (1 default full volume, ambients do not respond to volume)
"noise" sound to play
"channel" channel on which to play sound\
(0 auto, 1 weapon, 2 voice, 3 item, 4 body, 8 don't use PHS) (voice is default)
"key" The item needed to activate this. (default nothing)
"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

Normal sounds play each time the target is used.

Ambient Looped sounds have a volume 1, and the use function toggles it on/off.

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

******************************************************************************/

CLASS_DECLARATION( TriggerPlaySound, TriggerSpeaker, "sound_speaker" )
	{
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

TriggerSpeaker::TriggerSpeaker()
	{
	}

/*****************************************************************************/
/*QUAKED sound_randomspeaker (0 0.75 0.75) (-8 -8 -8) (8 8 8) x x NOT_PLAYERS MONSTERS PROJECTILES x x

play a sound at random times

"mindelay" minimum delay between sound triggers (default 3)
"maxdelay" maximum delay between sound triggers (default 10)
"chance" chance that sound will play when fired (default 1)
"volume" how loud 0-4 (1 default full volume)
"noise" sound to play
"channel" channel on which to play sound\
(0 auto, 1 weapon, 2 voice, 3 item, 4 body, 8 don't use PHS) (voice is default)
"key"          The item needed to activate this. (default nothing)

Normal sounds play each time the target is used.

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

******************************************************************************/

Event EV_TriggerRandomSpeaker_TriggerSound
	( 
	"triggersound",
	EV_DEFAULT,
   NULL,
   NULL,
   "Triggers the sound to play and schedules the next time to play."
	);
Event EV_Trigger_SetMinDelay
	( 
	"mindelay",
	EV_DEFAULT,
   "f",
   "min_delay",
   "Sets the minimum time between playings."
	);
Event EV_Trigger_SetMaxDelay
	( 
	"maxdelay",
	EV_DEFAULT,
   "f",
   "max_delay",
   "Sets the maximum time between playings."
	);
Event EV_Trigger_SetChance
	( 
	"chance",
	EV_DEFAULT,
   "f[0,1]",
   "newChance",
   "Sets the chance that the sound will play when triggered."
	);

CLASS_DECLARATION( TriggerSpeaker, RandomSpeaker, "sound_randomspeaker" )
	{
	   { &EV_Trigger_Effect,						TriggerSound },
      { &EV_Trigger_SetMinDelay,             SetMinDelay },
      { &EV_Trigger_SetMaxDelay,             SetMaxDelay },
      { &EV_Trigger_SetChance,               SetChance },
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

void RandomSpeaker::TriggerSound
	(
	Event *ev
	)

	{
   ScheduleSound();
   if ( G_Random( 1 ) <= chance )
      TriggerPlaySound::ToggleSound( ev );
	}

void RandomSpeaker::ScheduleSound
	(
   void
	)

	{
	CancelEventsOfType( EV_Trigger_Effect );
   PostEvent( EV_Trigger_Effect, mindelay + G_Random( maxdelay-mindelay ) );
	}

void RandomSpeaker::SetMinDelay
	(
	Event *ev
	)

	{
	mindelay = ev->GetFloat( 1 );
	}

void RandomSpeaker::SetMaxDelay
	(
	Event *ev
	)

	{
	maxdelay = ev->GetFloat( 1 );
	}

void RandomSpeaker::SetChance
	(
	Event *ev
	)

	{
	chance = ev->GetFloat( 1 );
	}

void RandomSpeaker::SetMinDelay
	(
   float newMinDelay
	)

	{
	mindelay = newMinDelay;
	}

void RandomSpeaker::SetMaxDelay
	(
   float newMaxDelay
	)

	{
	maxdelay = newMaxDelay;
	}

void RandomSpeaker::SetChance
	(
	float newChance
	)

	{
	chance = newChance;
	}

RandomSpeaker::RandomSpeaker()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   ambient = qfalse;
   chance = 1.0f;
	mindelay = 3;
	maxdelay = 10;

   ScheduleSound();
	}

/*****************************************************************************/
/*QUAKED trigger_changelevel (1 0 0) ? NO_INTERMISSION x NOT_PLAYERS MONSTERS PROJECTILES

When the player touches this, he gets sent to the map listed in the "map" variable.
Unless the NO_INTERMISSION flag is set, the view will go to the info_intermission
spot and display stats.

"spawnspot"  name of the spawn location to start at in next map.
"key"          The item needed to activate this. (default nothing)
"thread" This defaults to "LevelComplete" and should point to a thread that is called just
before the level ends.

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

******************************************************************************/

Event EV_TriggerChangeLevel_Map
	( 
	"map",
	EV_DEFAULT,
   "s",
   "map_name",
   "Sets the map to change to when triggered."
	);
Event EV_TriggerChangeLevel_SpawnSpot
	( 
	"spawnspot",
	EV_DEFAULT,
   "s",
   "spawn_spot",
   "Sets the spawn spot to use."
	);

CLASS_DECLARATION( Trigger, TriggerChangeLevel, "trigger_changelevel" )
	{
		{ &EV_Trigger_Effect,		            ChangeLevel },
      { &EV_TriggerChangeLevel_Map,          SetMap },
      { &EV_TriggerChangeLevel_SpawnSpot,    SetSpawnSpot },
      { &EV_Trigger_SetThread,		         SetThread },
		{ NULL, NULL }
	};

TriggerChangeLevel::TriggerChangeLevel()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   // default level change thread
   changethread = "LevelComplete";
	respondto = spawnflags ^ TRIGGER_PLAYERS;
	}

void TriggerChangeLevel::SetMap
	(
	Event *ev
	)

	{
   map = ev->GetString( 1 );
   }

void TriggerChangeLevel::SetSpawnSpot
	(
	Event *ev
	)

	{
	spawnspot = ev->GetString( 1 );
   }

void TriggerChangeLevel::SetThread
	(
	Event *ev
	)

	{
   // We have to handle calling the thread ourselves, so clear out Trigger's thread variable
   thread = "";
   changethread = ev->GetString( 1 );
   }

void TriggerChangeLevel::ChangeLevel
	(
	Event *ev
	)

	{
	Entity *other;

	other = ev->GetEntity( 1 );

	if ( level.intermissiontime )
		{
		// already activated
		return;
		}

	// if noexit, do a ton of damage to other
   if ( deathmatch->integer && DM_FLAG( DF_SAME_LEVEL ) && other != world )
		{
      other->Damage( this, other, 10 * other->max_health, other->origin, vec_zero, vec_zero, 1000, 0, MOD_CRUSH );
		return;
		}

   // tell the script that the player's not ready so that if we return to this map,
   // we can do something about it.
   Director.PlayerNotReady();

   //
   // make sure we execute the thread before changing
   //
   if ( changethread.length() )
      {
      ExecuteThread( changethread );
      }

   if ( spawnspot.length() )
      {
	   G_BeginIntermission( ( map + "$" + spawnspot ).c_str() );
      }
   else
      {
      G_BeginIntermission( map.c_str() );
      }
	}

const char *TriggerChangeLevel::Map
	(
	void
	)

	{
	return map.c_str();
	}

const char *TriggerChangeLevel::SpawnSpot
	(
	void
	)

	{
	return spawnspot.c_str();
	}

/*****************************************************************************/
/*QUAKED trigger_use (1 0 0) ? VISIBLE x NOT_PLAYERS MONSTERS

Activates targets when 'used' by an entity
"key"          The item needed to activate this. (default nothing)
"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters

******************************************************************************/

CLASS_DECLARATION( Trigger, TriggerUse, "trigger_use" )
	{
	   { &EV_Use,		   TriggerStuff },
		{ &EV_Touch,	   NULL },
		{ NULL, NULL }
	};

TriggerUse::TriggerUse()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
	if ( spawnflags & VISIBLE )
		{
		showModel();
		setMoveType( MOVETYPE_PUSH );
		setSolidType( SOLID_BSP );
		}

	respondto = ( spawnflags ^ TRIGGER_PLAYERS ) & ~TRIGGER_PROJECTILES;
	}

/*****************************************************************************/
/*QUAKED trigger_useonce (1 0 0) ? VISIBLE x NOT_PLAYERS MONSTERS

Activates targets when 'used' by an entity, but only once
"key"          The item needed to activate this. (default nothing)
"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters

******************************************************************************/

CLASS_DECLARATION( TriggerUse, TriggerUseOnce, "trigger_useonce" )
	{
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

TriggerUseOnce::TriggerUseOnce()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

	// Only allow 1 use.
	count = 1;

	respondto = ( spawnflags ^ TRIGGER_PLAYERS ) & ~TRIGGER_PROJECTILES;
	}

/*****************************************************************************/
/*QUAKED trigger_hurt (1 0 0) ? x x NOT_PLAYERS NOT_MONSTERS PROJECTILES

"damage" amount of damage to cause. (default 10)
"key"          The item needed to activate this. (default nothing)
"damagetype" what kind of damage should be given to the player. (default CRUSH)

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not hurt players
If NOT_MONSTERS is set, the trigger does not hurt monsters
If PROJECTILES is set, the trigger will hurt projectiles (rockets, grenades, etc.)

******************************************************************************/

Event EV_TriggerHurt_SetDamage
	( 
	"damage",
	EV_DEFAULT,
   "i",
   "damage",
   "Sets the amount of damage to do."
	);

Event EV_TriggerHurt_SetDamageType
	( 
	"damagetype",
	EV_DEFAULT,
   "s",
   "damageType",
   "Sets the type of damage a TriggerHurt delivers."
	);

CLASS_DECLARATION( TriggerUse, TriggerHurt, "trigger_hurt" )
	{
		{ &EV_Trigger_Effect,		      Hurt },
		{ &EV_TriggerHurt_SetDamage,     SetDamage },
		{ &EV_TriggerHurt_SetDamageType, DamageType },
	   { &EV_Touch,						   Trigger::TriggerStuff },
		{ NULL, NULL }
	};

TriggerHurt::TriggerHurt()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

	damage = 10;
   damage_type = MOD_CRUSH;
	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS );
	}

void TriggerHurt::SetDamage
	(
	Event *ev
	)

	{
	damage = ev->GetInteger( 1 );
	}

void TriggerHurt::Hurt
	(
	Event *ev
	)

	{
	Entity *other;

	other = ev->GetEntity( 1 );

	if ( ( damage != 0 ) && !other->deadflag && !( other->flags & FL_GODMODE ) )
		{
      other->Damage( this, other, damage, other->origin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR|DAMAGE_NO_SKILL, damage_type );
		}
	}

/*****************************************************************************/
/*QUAKED trigger_damagetargets (1 0 0) ? SOLID x NOT_PLAYERS NOT_MONSTERS PROJECTILES

"damage" amount of damage to cause. If no damage is specified, objects\
are damaged by the current health+1

"key"          The item needed to activate this. (default nothing)

if a trigger_damagetargets is shot at and the SOLID flag is set,\
the damage is passed on to the targets

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not hurt players
If NOT_MONSTERS is set, the trigger does not hurt monsters
If PROJECTILES is set, the trigger will hurt projectiles (rockets, grenades, etc.)

******************************************************************************/

Event EV_TriggerDamageTargets_SetDamage
	( 
	"damage",
	EV_DEFAULT,
   "i",
   "damage",
   "Sets the amount of damage to do."
	);

CLASS_DECLARATION( Trigger, TriggerDamageTargets, "trigger_damagetargets" )
	{
      { &EV_Trigger_ActivateTargets,	DamageTargets },
      { &EV_TriggerDamageTargets_SetDamage, SetDamage },
      { &EV_Damage,						   PassDamage },
		{ &EV_Touch,                     NULL },
		{ NULL, NULL }
	};

TriggerDamageTargets::TriggerDamageTargets()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

	damage = 0;
	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS );

   if ( spawnflags & 1 )
      {
	   health = 60;
	   max_health = health;
	   takedamage = DAMAGE_YES;
	   setSolidType( SOLID_BBOX );
      }
   else
      {
	   takedamage = DAMAGE_NO;
	   setSolidType( SOLID_NOT );
      }
	}

void TriggerDamageTargets::SetDamage
	(
	Event *ev
	)

	{
	damage = ev->GetInteger( 1 );
	}


void TriggerDamageTargets::PassDamage
	(
	Event *ev
	)

	{
	Entity		*attacker;
	int			dmg;
	Entity	   *ent;
	const char	*name;

	dmg		= ev->GetInteger( 1 );
	attacker = ev->GetEntity( 3 );

   //
   // damage the targets
   //
	name = Target();
	if ( name && strcmp( name, "" ) )
		{
      ent = NULL;
		do
			{
			ent = G_FindTarget( ent, name );
			if ( !ent )
				{
				break;
				}

	      if ( !ent->deadflag && !( ent->flags & FL_GODMODE ) )
		      {
            ent->Damage( this, attacker, dmg, ent->origin, vec_zero, vec_zero, 0, 0, MOD_CRUSH );
		      }
			}
		while ( 1 );
		}
	}
//
//==============================
// DamageTargets
//==============================
//

void TriggerDamageTargets::DamageTargets
	(
	Event *ev
	)

	{
	Entity	*other;
	Entity	*ent;
	const char		*name;

	other = ev->GetEntity( 1 );

	if ( triggerActivated )
		{
		//
		// Entity triggered itself.  Prevent an infinite loop
		//
		ev->Error( "Entity targeting itself--Targetname '%s'", TargetName() );
		return;
		}

	triggerActivated = true;
	activator = other;

   //
   // print the message
   //
	if ( message.length() && other && other->isClient() )
		{
		gi.centerprintf( other->edict, message.c_str() );
		if ( Noise().length() )
			{
			other->Sound( Noise().c_str(), CHAN_VOICE );
			}
		}

   //
   // damage the targets
   //
	name = Target();
	if ( name && strcmp( name, "" ) )
		{
      ent = NULL;
		do
			{
			ent = G_FindTarget( ent, name );
			if ( !ent )
				{
				break;
				}

	      if ( !ent->deadflag && !( ent->flags & FL_GODMODE ) )
		      {
            if (damage)
               ent->Damage( this, other, damage, ent->origin, vec_zero, vec_zero, 0, 0, MOD_CRUSH );
            else
               ent->Damage( this, other, ent->health+1, ent->origin, vec_zero, vec_zero, 0, 0, MOD_CRUSH );
		      }
			}
		while ( 1 );
		}

	triggerActivated = false;
	}

/*****************************************************************************/
/*QUAKED trigger_camerause (1 0 0) ? VISIBLE x NOT_PLAYERS MONSTERS

Activates 'targeted' camera when 'used'
If activated, toggles through cameras
"key"          The item needed to activate this. (default nothing)
"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters

******************************************************************************/

CLASS_DECLARATION( TriggerUse, TriggerCameraUse, "trigger_camerause" )
	{
	   { &EV_Use,		TriggerCamera },
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

void TriggerCameraUse::TriggerCamera
	(
	Event *ev
	)
	{
   str    camthread;
	Entity *other;

	other = ev->GetEntity( 1 );
   if ( other->isClient() )
      {
      Player * client;
      Entity * ent;
      Camera * cam;

      client = ( Player * )other;
      cam = client->CurrentCamera();
      if ( cam != NULL )
         {
         str nextcam;

         nextcam = cam->NextCamera();
         if ( nextcam.length() )
            {
            ent = G_FindTarget( NULL, nextcam.c_str() );

            if ( ent )
               {
               if ( ent->isSubclassOf( Camera ) )
                  {
                  cam = (Camera *)ent;
                  camthread = cam->Thread();
                  client->SetCamera( cam, CAMERA_SWITCHTIME );
                  }
               }
            }
         }
      else
         {
         ent = G_FindTarget( NULL, Target() );
         if ( ent )
            {
            if ( ent->isSubclassOf( Camera ) )
               {
               cam = (Camera *)ent;
               camthread = cam->Thread();
               client->SetCamera( cam, CAMERA_SWITCHTIME );
               }
            else
               {
               warning( "TriggerCamera", "%s is not a camera", Target() );
               }
            }

         }
      if ( camthread.length() > 1 )
         {
         if ( !ExecuteThread( camthread ) )
            {
            warning( "TriggerCamera", "Null game script" );
            }
         }
      }
	}

/*****************************************************************************/
/*QUAKED trigger_exit (1 0 0) ?

When the player touches this, an exit icon will be displayed in his hud.
This is to inform him that he is near an exit.

"triggerable" turn trigger on
"nottriggerable" turn trigger off

******************************************************************************/

Event EV_TriggerExit_TurnExitOff
	( 
	"_turnexitoff",
	EV_DEFAULT,
   NULL,
   NULL,
   "Internal event that turns the exit sign off."
	);

CLASS_DECLARATION( Trigger, TriggerExit, "trigger_exit" )
	{
		{ &EV_Trigger_Effect,		DisplayExitSign },
		{ &EV_TriggerExit_TurnExitOff, TurnExitSignOff },
		{ NULL, NULL }
	};

TriggerExit::TriggerExit()
	{
   wait = 1;
	respondto = TRIGGER_PLAYERS;
	}

void TriggerExit::TurnExitSignOff
	(
	Event *ev
	)

	{
   level.near_exit = false;
	}

void TriggerExit::DisplayExitSign
	(
	Event *ev
	)

	{
   level.near_exit = qtrue;

   CancelEventsOfType( EV_TriggerExit_TurnExitOff );
   PostEvent( EV_TriggerExit_TurnExitOff, 1.1f );
	}

/*****************************************************************************/
/*       trigger_box (0.5 0.5 0.5) ? x x NOT_PLAYERS MONSTERS PROJECTILES

Variable sized repeatable trigger.  Must be targeted at one or more entities.  Made to
be spawned via script.

If "health" is set, the trigger must be killed to activate each time.
If "delay" is set, the trigger waits some time after activating before firing.

"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

"wait" : Seconds between triggerings. (.2 default)
"cnt" how many times it can be triggered (infinite default)

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

set "message" to text string

******************************************************************************/

Event EV_TriggerBox_SetMins
	( 
	"mins",
	EV_DEFAULT,
   "v",
   "mins",
   "Sets the minimum bounds of the trigger box."
	);
Event EV_TriggerBox_SetMaxs
	( 
	"maxs",
	EV_DEFAULT,
   "v",
   "maxs",
   "Sets the maximum bounds of the trigger box."
	);

CLASS_DECLARATION( Trigger, TriggerBox, "trigger_box" )
	{
      { &EV_TriggerBox_SetMins,  SetMins },
      { &EV_TriggerBox_SetMaxs,  SetMaxs },
		{ NULL, NULL }
	};

void TriggerBox::SetMins
	(
	Event *ev
	)

	{
   Vector org;

	mins = ev->GetVector( 1 );
   org = ( mins + maxs ) * 0.5;

   setSize( mins - org, maxs - org );
	setOrigin( org );
	}

void TriggerBox::SetMaxs
	(
	Event *ev
	)

	{
   Vector org;

	maxs = ev->GetVector( 1 );
   org = ( mins + maxs ) * 0.5;

   setSize( mins - org, maxs - org );
	setOrigin( org );
	}

/*****************************************************************************/
/*QUAKED trigger_music (1 0 0) ? NORMAL ACTION NOT_PLAYERS MONSTERS PROJECTILES SUSPENSE MYSTERY SURPRISE

Variable sized repeatable trigger to change the music mood.  

If "delay" is set, the trigger waits some time after activating before firing.
"current" can be used to set the current mood
"fallback" can be used to set the fallback mood
"altcurrent" can be used to set the current mood of the opposite face, if multiFaceted
"altfallback" can be used to set the fallback mood of the opposite face, if multiFaceted
"edgeTriggerable" trigger only fires when entering a trigger
"multiFaceted" if 1, then trigger is North/South separate triggerable\
if 2, then trigger East/West separate triggerable

"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.
"wait" : Seconds between triggerings. (1.0 default)
"cnt" how many times it can be triggered (infinite default)
"oneshot" make this a one time trigger

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

NORMAL, ACTION, SUSPENSE, MYSTERY, and SURPRISE are the moods that can be triggered

******************************************************************************/

Event EV_TriggerMusic_CurrentMood
	( 
	"current",
	EV_DEFAULT,
   "s",
   "current_mood",
   "Sets the current mood to use when triggered."
	);

Event EV_TriggerMusic_FallbackMood
	( 
	"fallback",
	EV_DEFAULT,
   "s",
   "fallback_mood",
   "Sets the fallback mood to use when triggered."
	);

Event EV_TriggerMusic_AltCurrentMood
	( 
	"altcurrent",
	EV_DEFAULT,
   "s",
   "alternate_current_mood",
   "Sets the alternate current mood to use when triggered."
	);

Event EV_TriggerMusic_AltFallbackMood
	( 
	"altfallback",
	EV_DEFAULT,
   "s",
   "alterante_fallback_mood",
   "Sets the alternate fallback mood to use when triggered."
	);

Event EV_TriggerMusic_OneShot
	( 
	"oneshot",
	EV_DEFAULT,
   NULL,
   NULL,
   "Make this a one time trigger."
	);

CLASS_DECLARATION( Trigger, TriggerMusic, "trigger_music" )
	{
		{ &EV_TriggerMusic_CurrentMood,	SetCurrentMood },
		{ &EV_TriggerMusic_FallbackMood,	SetFallbackMood },
		{ &EV_TriggerMusic_AltCurrentMood,	SetAltCurrentMood },
		{ &EV_TriggerMusic_AltFallbackMood,	SetAltFallbackMood },
		{ &EV_TriggerMusic_OneShot,		SetOneShot },
		{ &EV_Trigger_Effect,				ChangeMood },
		{ &EV_Trigger_Effect_Alt,			AltChangeMood },
		{ NULL, NULL }
	};

TriggerMusic::TriggerMusic()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   removable         = false;
	triggerActivated	= false;
	activator			= NULL;
	trigger_time		= (float)0;
   edgeTriggered     = qtrue;

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_TRIGGER );

   setContents( 0 );
	edict->svflags |= SVF_NOCLIENT;

	delay = 0;
	wait  = 1.0f;
	health = 0;
	max_health = 0;

	trigger_time = (float)0;

   SetOneShot( false );

   noise = "";
	respondto = spawnflags ^ TRIGGER_PLAYERS;

	current  = "normal";
	fallback = "normal";

	altcurrent  = "normal";
	altfallback = "normal";

   // setup sound based on spawn flags
	if ( spawnflags & 1 )
		current = "normal";
	else if ( spawnflags & 2 )
		current = "action";
	else if ( spawnflags & 32 )
		current = "suspense";
	else if ( spawnflags & 64 )
		current = "mystery";
	else if ( spawnflags & 128 )
		current = "surprise";
	}

void TriggerMusic::SetMood
	(
   str crnt,
   str fback
	)
	{
   current = crnt;
   fallback = fback;
	}

void TriggerMusic::SetAltMood
	(
   str crnt,
   str fback
	)
	{
   altcurrent = crnt;
   altfallback = fback;
	}

void TriggerMusic::SetCurrentMood
	(
	Event *ev
	)
	{
	current = ev->GetString( 1 );
	}

void TriggerMusic::SetFallbackMood
	(
	Event *ev
	)
	{
	fallback = ev->GetString( 1 );
	}

void TriggerMusic::SetAltCurrentMood
	(
	Event *ev
	)
	{
	altcurrent = ev->GetString( 1 );
	}

void TriggerMusic::SetAltFallbackMood
	(
	Event *ev
	)
	{
	altfallback = ev->GetString( 1 );
	}

void TriggerMusic::ChangeMood
	(
	Event *ev
	)
	{
	ChangeMusic( current.c_str(), fallback.c_str(), qfalse );
	}

void TriggerMusic::AltChangeMood
	(
	Event *ev
	)
	{
	ChangeMusic( altcurrent.c_str(), altfallback.c_str(), qfalse );
	}

void TriggerMusic::SetOneShot
	(
   qboolean once
	)
	{
	trigger_time = 0.0f;
   oneshot = once;
   if ( oneshot )
      count = 1;
   else
      count = -1;
	}

void TriggerMusic::SetOneShot
	(
	Event *ev
	)
	{
   SetOneShot( true );
	}

/*****************************************************************************/
/*QUAKED trigger_reverb (1 0 0) ? x x NOT_PLAYERS MONSTERS PROJECTILES

Variable sized repeatable trigger to change the reverb level in the game

If "delay" is set, the trigger waits some time after activating before firing.
"reverbtype" what kind of reverb should be used
"reverblevel" how much of the reverb effect should be applied
"altreverbtype" what kind of reverb should be used
"altreverblevel" how much of the reverb effect should be applied
"edgeTriggerable" trigger only fires when entering a trigger
"multiFaceted" if 1, then trigger is North/South separate triggerable\
if 2, then trigger East/West separate triggerable

"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.
"wait" : Seconds between triggerings. (1.0 default)
"cnt" how many times it can be triggered (infinite default)
"oneshot" make this a one time trigger

"triggerable" turn trigger on
"nottriggerable" turn trigger off

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

******************************************************************************/

Event EV_TriggerReverb_ReverbType
	( 
	"reverbtype",
	EV_DEFAULT,
   "i",
   "reverbType",
   "Sets the reverb type."
	);

Event EV_TriggerReverb_ReverbLevel
	( 
	"reverblevel",
	EV_DEFAULT,
   "f",
   "reverbLevel",
   "Sets the reverb level to be used when triggered."
	);

Event EV_TriggerReverb_AltReverbType
	( 
	"altreverbtype",
	EV_DEFAULT,
   "i",
   "reverbType",
   "Sets the reverb type."
	);

Event EV_TriggerReverb_AltReverbLevel
	( 
	"altreverblevel",
	EV_DEFAULT,
   "f",
   "reverbLevel",
   "Sets the reverb level to be used when triggered."
	);

Event EV_TriggerReverb_OneShot
	( 
	"oneshot",
	EV_DEFAULT,
   NULL,
   NULL,
   "Make this a one time trigger."
	);

CLASS_DECLARATION( Trigger, TriggerReverb, "trigger_music" )
	{
		{ &EV_TriggerReverb_ReverbType,	   SetReverbType },
		{ &EV_TriggerReverb_ReverbLevel,	   SetReverbLevel },
		{ &EV_TriggerReverb_AltReverbType,	SetAltReverbType },
		{ &EV_TriggerReverb_AltReverbLevel,	SetAltReverbLevel },
		{ &EV_TriggerReverb_OneShot,		   SetOneShot },
		{ &EV_Trigger_Effect,				   ChangeReverb },
		{ &EV_Trigger_Effect_Alt,			   AltChangeReverb },
		{ NULL, NULL }
	};

TriggerReverb::TriggerReverb()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   removable         = false;
	triggerActivated	= false;
	activator			= NULL;
	trigger_time		= (float)0;
   edgeTriggered     = qtrue;

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_TRIGGER );

   setContents( 0 );
	edict->svflags |= SVF_NOCLIENT;

	delay = 0;
	wait  = 1.0f;
	health = 0;
	max_health = 0;

	trigger_time = (float)0;

   SetOneShot( false );

   noise = "";
	respondto = spawnflags ^ TRIGGER_PLAYERS;

   reverbtype = 0;
   altreverbtype = 0;
   reverblevel = 0.5f;
   altreverblevel = 0.5f;
	}

void TriggerReverb::SetReverb
	(
   int type,
   float level
	)
	{
   reverbtype = type;
   reverblevel = level;
	}

void TriggerReverb::SetAltReverb
	(
   int type,
   float level
	)
	{
   altreverbtype = type;
   altreverblevel = level;
	}

void TriggerReverb::SetReverbType
	(
	Event *ev
	)
	{
	reverbtype = ev->GetInteger( 1 );
	}

void TriggerReverb::SetReverbLevel
	(
	Event *ev
	)
	{
	reverblevel = ev->GetFloat( 1 );
	}

void TriggerReverb::SetAltReverbType
	(
	Event *ev
	)
	{
	altreverbtype = ev->GetInteger( 1 );
	}

void TriggerReverb::SetAltReverbLevel
	(
	Event *ev
	)
	{
	altreverblevel = ev->GetFloat( 1 );
	}

void TriggerReverb::ChangeReverb
	(
	Event *ev
	)
	{
   Entity * other;

   other = ev->GetEntity( 1 );
   if ( other->isClient() ) 
      {
      Player *client;

      client = ( Player * )other;
      client->SetReverb( reverbtype, reverblevel );
      gi.DPrintf( "reverb set to %s at level %.2f\n", EAXMode_NumToName( reverbtype ), reverblevel );
      }
	}

void TriggerReverb::AltChangeReverb
	(
	Event *ev
	)
	{
   Entity * other;

   other = ev->GetEntity( 1 );
   if ( other->isClient() ) 
      {
      Player *client;

      client = ( Player * )other;
      client->SetReverb( altreverbtype, altreverblevel );
      gi.DPrintf( "reverb set to %s at level %.2f\n", EAXMode_NumToName( altreverbtype ), altreverblevel );
      }
	}

void TriggerReverb::SetOneShot
	(
   qboolean once
	)
	{
	trigger_time = 0.0f;
   oneshot = once;
   if ( oneshot )
      count = 1;
   else
      count = -1;
	}

void TriggerReverb::SetOneShot
	(
	Event *ev
	)
	{
   SetOneShot( true );
	}

/*****************************************************************************/
/*QUAKED trigger_pushobject (1 0 0) ? 
Special trigger that can only be triggered by a push object.

"triggername" if set, trigger only responds to objects with a targetname the same as triggername.
"cnt" how many times it can be triggered (default 1, use -1 for infinite)
******************************************************************************/

Event EV_TriggerByPushObject_TriggerName
	( 
	"triggername",
	EV_DEFAULT,
   "s",
   "targetname_of_object",
   "If set, trigger will only respond to objects with specified name."
	);

CLASS_DECLARATION( TriggerOnce, TriggerByPushObject, "trigger_pushobject" )
	{
      { &EV_TriggerByPushObject_TriggerName,    setTriggerName },
		{ NULL, NULL }
	};

void TriggerByPushObject::setTriggerName
   (
   Event *event
   )

   {
   triggername = event->GetString( 1 );
   }

qboolean TriggerByPushObject::respondTo
   (
   Entity *other
   )

   {
   if ( other->isSubclassOf( PushObject ) )
      {
      if ( triggername.length() )
         {
         return ( triggername == other->TargetName() );
         }

      return qtrue;
      }

   return qfalse;
   }

Entity *TriggerByPushObject::getActivator
   (
   Entity *other
   )

   {
   Entity *owner;

   if ( other->isSubclassOf( PushObject ) )
      {
      owner = ( ( PushObject * )other )->getOwner();
      
      if ( owner )
         {
         return owner;
         }
      }

   return other;
   }

/*****************************************************************************/
/*QUAKED trigger_givepowerup (1 0 0) ? x x NOT_PLAYERS MONSTERS x

Variable sized repeatable trigger to give a powerup to the player

"oneshot" makes this triggerable only once
"powerupname" sets the name of the powerup to give to the player

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters

******************************************************************************/

Event EV_TriggerGivePowerup_OneShot
	( 
	"oneshot",
	EV_DEFAULT,
   NULL,
   NULL,
   "Make this a one time trigger."
	);
Event EV_TriggerGivePowerup_PowerupName
	( 
	"powerupname",
	EV_DEFAULT,
   "s",
   "powerup_name",
   "Specifies the powerup to give to the sentient."
	);

CLASS_DECLARATION( Trigger, TriggerGivePowerup, "trigger_givepowerup" )
	{
		{ &EV_TriggerGivePowerup_OneShot,		SetOneShot },
		{ &EV_TriggerGivePowerup_PowerupName,	SetPowerupName },
		{ &EV_Trigger_Effect,						GivePowerup },
		{ NULL, NULL }
	};

TriggerGivePowerup::TriggerGivePowerup()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

   removable         = false;
	triggerActivated	= false;
	activator			= NULL;
	trigger_time		= (float)0;
   edgeTriggered     = false;

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_TRIGGER );

   setContents( 0 );
	edict->svflags |= SVF_NOCLIENT;

	delay = 0;
	wait  = 1.0f;
	health = 0;
	max_health = 0;

	trigger_time = 0.0;
	oneshot = false;
	count = -1;

   noise = "";
	respondto = spawnflags ^ (TRIGGER_PLAYERS | TRIGGER_MONSTERS );
	}

void TriggerGivePowerup::SetOneShot
	(
	Event *ev
	)
	{
	trigger_time = 0.0f;
   oneshot = true;
   count = 1;
	}

void TriggerGivePowerup::SetPowerupName
	(
	Event *ev
	)
	{
	powerup_name = ev->GetString( 1 );
	}

void TriggerGivePowerup::GivePowerup
	(
	Event *ev
	)
	{
	Entity *other;

	other = ev->GetEntity( 1 );

   if ( other->isSubclassOf( Sentient ) ) 
      {
      Sentient *sent;

      sent = ( Sentient * )other;

		if ( powerup_name.length() && !sent->FindItem( powerup_name.c_str() ) )
			sent->giveItem( powerup_name );
      }
	}