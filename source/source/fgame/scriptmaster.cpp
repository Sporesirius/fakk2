//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/scriptmaster.cpp                   $
// $Revision:: 53                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 8/04/00 3:54p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/scriptmaster.cpp                        $
// 
// 53    8/04/00 3:54p Markd
// Added StartCinematic and StopCinematic
// 
// 52    7/30/00 4:10p Markd
// clear out the cinematic skipthread on non-cinematic
// 
// 51    7/29/00 4:47p Markd
// made "null" skipthreads act as clear
// 
// 50    7/29/00 1:25p Steven
// Fixed when the object in a MoveDone no longer exists.
// 
// 49    7/28/00 9:44p Markd
// Added lightstyle repository code
// 
// 48    7/27/00 3:52p Aldie
// Changed over letterboxing and fades to the game code.  They are sent over in
// player stats and fields now.
// 
// 47    7/23/00 6:03p Markd
// added fadeout and fadesound to dieing and level change
// 
// 46    7/17/00 7:45p Markd
// changed the way that fakeplayer is executed
// 
// 45    7/14/00 9:52p Markd
// added global volume dampener on ambient sound effects for cinematics
// 
// 44    7/11/00 1:15a Markd
// bullet proofed some waitFor code
// 
// 43    7/07/00 6:35p Steven
// Added mission failed stuff.
// 
// 42    6/28/00 3:27p Steven
// Added level wide ai_on.
// 
// 41    6/22/00 7:09p Markd
// fixed some spawning issues
// 
// 40    6/16/00 5:14p Aldie
// Added locational printing (print anywhere on the screen)
// 
// 39    6/15/00 4:28p Markd
// Cleaned up GameTime variable issues
// 
// 38    5/26/00 2:24p Aldie
// Added waitforplayer commands so we can use it for cinematics when waiting
// for player to finish holstering
// 
// 37    5/01/00 7:14p Markd
// Added centerprint command to scripts
// 
// 36    4/19/00 3:36p Aldie
// Added alpha to fadein and fadeout
// 
// 35    4/05/00 3:51p Markd
// added label checking for scripts
// 
// 34    4/01/00 1:19p Markd
// fixed crash where entity was not being checked before being evaluated
// 
// 33    3/16/00 5:08p Markd
// hooked up threadname into something that actually works...woops
// 
// 32    3/16/00 4:13p Markd
// Added killthread ability
// 
// 31    3/06/00 8:17p Markd
// converted certain events from EV_CONSOLE to EV_CHEAT
// 
// 30    3/04/00 11:48a Markd
// Added light style support
// 
// 29    2/22/00 2:30p Markd
// fixed skipthread not calling the right thread
// 
// 28    1/29/00 10:29a Aldie
// Removed passtoplayer because $player is already there
// 
// 27    1/29/00 9:32a Markd
// Added setdialogscript functionality back in
// 
// 26    1/28/00 5:43p Markd
// Added script command to the game
// 
// 25    1/28/00 12:05p Steven
// Added a debug message for dialog stuff.
// 
// 24    1/27/00 12:23p Aldie
// changed player command to passtoplayer
// 
// 23    1/27/00 11:48a Aldie
// Added player command and takeweapon
// 
// 22    1/24/00 11:50a Markd
// Added delay to waitfordialog command
// 
// 21    1/20/00 6:37p Markd
// put warning message into SendCommandToSlaves
// 
// 20    1/19/00 12:12p Steven
// Added a waitForDialog command.
// 
// 19    1/14/00 5:07p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 18    1/13/00 4:53p Markd
// Fixed spawn command to properly set the spawnflags parameter
// 
// 17    1/10/00 6:17p Jimdose
// more code cleanup
// 
// 16    1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 15    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 14    12/10/99 10:59a Markd
// Removed process pending events on spawn because it was fucking up
// splinepaths
// 
// 13    12/09/99 6:51p Markd
// process pending events after spawning
// 
// 12    11/09/99 8:04p Markd
// Rewrote spawn command
// 
// 11    11/04/99 3:14p Aldie
// fixed typo
// 
// 10    11/03/99 4:32p Aldie
// Added letterboxing
// 
// 9     11/02/99 6:29p Aldie
// Added Fading
// 
// 8     10/28/99 6:33p Markd
// Added fakeplayer ability, also added CloneEntity
// 
// 7     10/27/99 12:19p Markd
// added smooth camera lerping
// 
// 6     10/07/99 3:01p Steven
// Event formatting.
// 
// 5     9/22/99 4:48p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 4     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 3     9/16/99 4:49p Jimdose
// removed unused code
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 21    9/02/99 5:41p Markd
// made CacheResource utility functions changed code every where else
// 
// 20    8/28/99 3:34p Jimdose
// added isVarGroup
// 
// 19    8/27/99 4:16p Aldie
// Fix event posting bug
// 
// 18    8/25/99 12:42p Markd
// Fixed some minor and major scripting bugs
// 
// 17    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
//
// DESCRIPTION:
// Script masters are invisible entities that are spawned at the begining of each
// map.  They simple parse the script and send commands to the specified objects
// at the apropriate time.  Using a combination of simple commands, very complex
// scripted events can occur.
//

#include "g_local.h"
#include "class.h"
#include "scriptmaster.h"
#include "container.h"
#include "scriptvariable.h"
#include "misc.h"
#include "specialfx.h"
#include "worldspawn.h"
#include "player.h"

ScriptVariableList gameVars;
ScriptVariableList levelVars;
ScriptVariableList parmVars;
static ScriptVariablePtr GameTime = NULL;

Event EV_ProcessCommands
	( 
	"processCommands",
	EV_DEFAULT,
	NULL,
	NULL,
	"Not used."
	);
Event EV_Script_NewOrders
	(	
	"newOrders",
	EV_DEFAULT,
	NULL,
	NULL,
	"Inform script that it is about to get new orders."
	);
Event EV_ScriptThread_Execute
	( 
	"execute",
	EV_DEFAULT,
	NULL,
	NULL,
	"Execute the thread."
	);
Event EV_ScriptThread_Callback
	( 
	"script_callback",
	EV_DEFAULT,
	"ese",
	"slave name other",
	"Script callback."
	);
Event EV_ScriptThread_ThreadCallback
	( 
	"thread_callback",
	EV_DEFAULT,
	NULL,
	NULL,
	"Thread callback."
	);
Event EV_ScriptThread_VariableCallback
	( 
	"variable_callback",
	EV_DEFAULT,
	NULL,
	NULL,
	"Variable callback."
	);
Event EV_ScriptThread_DeathCallback
	( 
	"death_callback",
	EV_DEFAULT,
	NULL,
	NULL,
	"Death callback."
	);
Event EV_ScriptThread_CreateThread
	( 
	"thread",
	EV_DEFAULT,
	"s",
	"label",
	"Creates a thread starting at label."
	);
Event EV_ScriptThread_TerminateThread
	( 
	"terminate",
	EV_DEFAULT,
	"i",
	"thread_number",
	"Terminates the specified thread or the current one if none specified."
	);
Event EV_ScriptThread_ControlObject
	( 
	"control",
	EV_DEFAULT,
	"e",
	"object",
	"Not used."
	);
Event EV_ScriptThread_Goto
	( 
	"goto",
	EV_DEFAULT,
	"s",
	"label",
	"Goes to the specified label."
	);
Event EV_ScriptThread_Pause
	( 
	"pause",
	EV_DEFAULT,
	NULL,
	NULL,
	"Pauses the thread."
	);
Event EV_ScriptThread_Wait
	( 
	"wait",
	EV_DEFAULT,
	"f",
	"wait_time",
	"Wait for the specified amount of time."
	);
Event EV_ScriptThread_WaitFor
	( 
	"waitFor",
	EV_DEFAULT,
	"e",
	"ent",
	"Wait for the specified entity."
	);
Event EV_ScriptThread_WaitForThread
	( 
	"waitForThread",
	EV_DEFAULT,
	"i",
	"thread_number",
	"Wait for the specified thread."
	);
Event EV_ScriptThread_WaitForVariable
	( 
	"waitForVariable",
	EV_DEFAULT,
	"s",
	"variable_name",
	"Wait for the specified variable."
	);
Event EV_ScriptThread_WaitForDeath
	( 
	"waitForDeath",
	EV_DEFAULT,
	"s",
	"name",
	"Wait for death."
	);
Event EV_ScriptThread_WaitForSound
	( 
	"waitForSound",
	EV_DEFAULT,
	"sf",
	"sound_name delay",
	"Wait for end of the named sound plus an optional delay."
	);
Event EV_ScriptThread_WaitForDialog
	( 
	"waitForDialog",
	EV_DEFAULT,
	"eF",
	"actor additional_delay",
	"Wait for end of the dialog for the specified actor.\n"
   "If additional_delay is specified, than the actor will\n"
   "wait the dialog length plus the delay."
	);
Event EV_ScriptThread_WaitForPlayer
	( 
	"waitForPlayer",
	EV_DEFAULT,
	NULL,
	NULL,
	"Wait for player to be ready."
	);
Event EV_ScriptThread_End
	( 
	"end",
	EV_DEFAULT,
	NULL,
	NULL,
	"End the thread."
	);
Event EV_ScriptThread_Print
	(
	"print",
	EV_DEFAULT,
	"s",
	"string",
	"Prints a string."
	);
Event EV_ScriptThread_PrintInt
	( 
	"printint",
	EV_DEFAULT,
	"i",
	"integer",
	"Print integer."
	);
Event EV_ScriptThread_PrintFloat
	( 
	"printfloat",
	EV_DEFAULT,
	"f",
	"float",
	"Prints a float.");
Event EV_ScriptThread_PrintVector
	( 
	"printvector",
	EV_DEFAULT,
	"v",
	"vector",
	"Prints a vector."
	);
Event EV_ScriptThread_NewLine
	( 
	"newline",
	EV_DEFAULT,
	NULL,
	NULL,
	"Prints a newline."
	);
Event EV_ScriptThread_Assert
	( 
	"assert",
	EV_DEFAULT,
	"f",
	"value",
	"Assert if value is 0."
	);
Event EV_ScriptThread_Break
	( 
	"break",
	EV_DEFAULT,
	NULL,
	NULL,
	"Asserts so that we can break back into the debugger from script."
	);
Event EV_ScriptThread_Clear
	( 
	"clear",
	EV_DEFAULT,
	"s",
	"var_group",
	"Clears the specified var group."
	);
Event EV_ScriptThread_Trigger
	( 
	"trigger",
	EV_DEFAULT,
	"s",
	"name",
	"Trigger the specified target or entity."
	);
Event EV_ScriptThread_Spawn
	( 
	"spawn", 
	EV_CHEAT,
	"sSSSSSSSS",
	"entityname keyname1 value1 keyname2 value2 keyname3 value3 keyname4 value4",
	"Spawn the specified entity."
	);
Event EV_ScriptThread_Map
	( 
	"map",
	EV_DEFAULT,
	"s",
	"map_name",
	"Starts the specified map."
	);
Event EV_ScriptThread_SetCvar
	( 
	"setcvar",
	EV_DEFAULT,
	"ss",
	"cvar_name value",
	"Sets the value of the specified cvar."
	);
Event EV_ScriptThread_CueCamera
	( 
	"cuecamera",
	EV_DEFAULT,
	"eF",
	"entity switchTime",
	"Cue the camera. If switchTime is specified, then the camera\n"
   "will switch over that length of time."
	);
Event EV_ScriptThread_CuePlayer
	( 
	"cueplayer",
	EV_DEFAULT,
   "F",
   "switchTime",
	"Go back to the normal camera. If switchTime is specified,\n"
   "then the camera will switch over that length of time."
	);
Event EV_ScriptThread_FreezePlayer
	( 
	"freezeplayer",
	EV_DEFAULT,
	NULL,
	NULL,
	"Freeze the player."
	);
Event EV_ScriptThread_ReleasePlayer
	( 
	"releaseplayer",
	EV_DEFAULT,
	NULL,
	NULL,
	"Release the player."
	);
Event EV_ScriptThread_FakePlayer
	( 
	"fakeplayer",
	EV_DEFAULT,
	NULL,
   NULL,
	"Will create a fake version of the player, hide the real one and\n"
   "call the fake one 'fakeplayer'."
	);
Event EV_ScriptThread_RemoveFakePlayer
	( 
	"removefakeplayer",
	EV_DEFAULT,
   NULL,
   NULL,
	"Will delete the fake version of the player, un-hide the real one and\n"
   "return to the normal game"
	);

Event EV_ScriptThread_KillEnt
	( 
	"killent", 
	EV_CHEAT,
	"i",
	"ent_num",
	"Kill the specified entity."
	);
Event EV_ScriptThread_KillClass
	( 
	"killclass", 
	EV_CHEAT,
	"sI",
	"class_name except",
	"Kills everything in the specified class except for the specified entity (optional)."
	);
Event EV_ScriptThread_RemoveEnt
	( 
	"removeent", 
	EV_CHEAT,
	"i",
	"ent_num",
	"Removes the specified entity."
	);
Event EV_ScriptThread_RemoveClass
	( 
	"removeclass", 
	EV_CHEAT,
	"sI",
	"class_name except",
	"Removes everything in the specified class except for the specified entity (optional)."
	);

// client/server flow control

Event EV_ScriptThread_ServerOnly
	( 
	"server",
	EV_DEFAULT,
	"SSSSSS",
	"arg1 arg2 arg3 arg4 arg5 arg6",
	"Server only command."
	);
Event EV_ScriptThread_ClientOnly
	( 
	"client",
	EV_DEFAULT,
	"SSSSSS",
	"arg1 arg2 arg3 arg4 arg5 arg6",
	"Client only command."
	);
Event EV_ScriptThread_StuffCommand
	( 
	"stuffcmd",
	EV_DEFAULT,
	"SSSSSS",
	"arg1 arg2 arg3 arg4 arg5 arg6",
	"Server only command."
	);

//
// world stuff
//
Event EV_ScriptThread_RegisterAlias
	( 
	"alias",
	EV_DEFAULT,
	"ssSSSS",
	"alias_name real_name arg1 arg2 arg3 arg4",
	"Sets up an alias."
	);
Event EV_ScriptThread_RegisterAliasAndCache
	(
	"aliascache",
	EV_DEFAULT,
	"ssSSSS",
	"alias_name real_name arg1 arg2 arg3 arg4",
	"Sets up an alias and caches the resourse."
	);
Event EV_ScriptThread_SetCinematic
	( 
	"cinematic",
	EV_DEFAULT,
	NULL,
	NULL,
	"Turns on cinematic."
	);
Event EV_ScriptThread_SetNonCinematic
	( 
	"noncinematic",
	EV_DEFAULT,
	NULL,
	NULL,
	"Turns off cinematic."
	);
Event EV_ScriptThread_SetAllAIOff
	( 
	"all_ai_off",
	EV_DEFAULT,
	NULL,
	NULL,
	"Turns all AI off."
	);
Event EV_ScriptThread_SetAllAIOn
	( 
	"all_ai_on",
	EV_DEFAULT,
	NULL,
	NULL,
	"Turns all AI back on."
	);
Event EV_ScriptThread_SetSkipThread
	( 
	"skipthread",
	EV_DEFAULT,
	"s",
	"thread_name",
	"Set the thread to skip."
	);

// Precache specific
Event EV_ScriptThread_Precache_Cache
	( 
	"cache",
	EV_DEFAULT,
	"s",
	"resource_name",
	"Cache the specified resource."
	);
// fades for movies
Event EV_ScriptThread_FadeIn
	( 
	"fadein",
	EV_DEFAULT,
	"fffffI",
	"time red green blue alpha mode",
	"Sets up fadein in values."
	);
Event EV_ScriptThread_FadeOut
	( 
	"fadeout",
	EV_DEFAULT,
	"fffffI",
	"time red green blue alpha mode",
	"Sets up fadeout values."
	);
Event EV_ScriptThread_FadeSound
	( 
	"fadesound",
	EV_DEFAULT,
	"f",
	"time",
	"fades the sound out over the given time."
	);
Event EV_ScriptThread_CameraCommand
	( 
	"cam",
	EV_DEFAULT,
	"sSSSSSS",
	"command arg1 arg2 arg3 arg4 arg5 arg6",
	"Processes a camera command."
	);

// music command
Event EV_ScriptThread_MusicEvent
	( 
	"music",
	EV_DEFAULT,
	"sS",
	"current fallback",
	"Sets the current and fallback (optional) music moods."
	);
Event EV_ScriptThread_ForceMusicEvent
	( 
	"forcemusic",
	EV_DEFAULT,
	"sS",
	"current fallback",
	"Forces the current and fallback (optional) music moods."
	);
Event EV_ScriptThread_MusicVolumeEvent
	( 
	"musicvolume",
	EV_DEFAULT,
	"ff",
	"volume fade_time",
	"Sets the volume and fade time of the music."
	);
Event EV_ScriptThread_RestoreMusicVolumeEvent
	( 
	"restoremusicvolume",
	EV_DEFAULT,
	"f",
	"fade_time",
	"Restores the music volume to its previous value."
	);
Event EV_ScriptThread_SoundtrackEvent
	( 
	"soundtrack",
	EV_DEFAULT,
	"s",
	"soundtrack_name",
	"Changes the soundtrack."
	);
Event EV_ScriptThread_RestoreSoundtrackEvent
	( 
	"restoresoundtrack",
	EV_DEFAULT,
	NULL,
	NULL,
	"Restores the soundtrack to the previous one."
	);
Event EV_ScriptThread_ClearFade
   (
   "clearfade",
   EV_DEFAULT,
   NULL,
   NULL,
   "Clear the fade from the screen"
   );
Event EV_ScriptThread_Letterbox
	( 
	"letterbox",
	EV_DEFAULT,
	"f",
	"time",
	"Puts the game in letterbox mode."
	);
Event EV_ScriptThread_ClearLetterbox
	( 
	"clearletterbox",
	EV_DEFAULT,
	"f",
   "time",
	"Clears letterbox mode."
	);
Event EV_ScriptThread_SetDialogScript
   ( 
   "setdialogscript" ,
   EV_DEFAULT,
   "s",
   "dialog_script",
   "Set the script to be used when dialog:: is used"
   );

Event EV_ScriptThread_SetLightStyle
   ( 
   "setlightstyle" ,
   EV_DEFAULT,
   "is",
   "lightstyleindex lightstyledata",
   "Set up the lightstyle with lightstyleindex to the specified data"
   );

Event EV_ScriptThread_KillThreadEvent
   ( 
   "killthread",
   EV_DEFAULT,
   "s",
   "threadName",
   "kills all threads starting with the specified name"
   );

Event EV_ScriptThread_SetThreadNameEvent
   ( 
   "threadname",
   EV_DEFAULT,
   "s",
   "threadName",
   "sets the name of the thread"
   );

Event EV_ScriptThread_CenterPrint
   ( 
   "centerprint",
   EV_DEFAULT,
   "s",
   "stuffToPrint",
   "prints the included message in the middle of all player's screens"
   );

Event EV_ScriptThread_LocationPrint
   ( 
   "locprint",
   EV_DEFAULT,
   "iis",
   "xoffset yoffset stuffToPrint",
   "prints the included message in the specified location of all player's screens"
   );

Event EV_ScriptThread_MissionFailed
   ( 
   "missionfailed",
   EV_DEFAULT,
   NULL,
   NULL,
   "Makes the player fail their mission, level restarts."
   );


CLASS_DECLARATION( Class, ThreadMarker, NULL )
	{
		{ NULL, NULL }
	};

ScriptMaster Director;

CLASS_DECLARATION( Listener, ScriptMaster, NULL )
	{
		{ NULL, NULL }
	};

ScriptMaster::ScriptMaster()
	{
	threadIndex		= 0;
	currentThread	= NULL;
   player_ready = false;
	}

ScriptMaster::~ScriptMaster()
	{
   if ( GameTime )
      {
	   gameVars.RemoveVariable( GameTime );
      GameTime = NULL;
      }
	CloseScript();
	}

void ScriptMaster::CloseScript
	(
	void
	)

	{
	KillThreads();
	ScriptLib.CloseScripts();
   if ( GameTime )
      {
	   gameVars.RemoveVariable( GameTime );
      GameTime = NULL;
      }
	}

void ScriptMaster::KillThreads
	(
   void
	)

	{
	int i;
	int num;

	num = Threads.NumObjects();

   // Clear the waitfor's from each thread before deleting
   // so they don't get triggered.
   for( i = num; i > 0; i-- )
		{
		Threads.ObjectAt( i )->ClearWaitFor();
		}

   for( i = num; i > 0; i-- )
		{
		delete Threads.ObjectAt( i );
		}

	Threads.FreeObjectList();

	threadIndex	= 0;
   currentThread = NULL;
	}

void ScriptMaster::KillThread
	(
   str name
	)
	{
	int i;
	int num;
   int len;
   const char * ptr;
	ScriptThread *thread;

   // see if the name uses a wild card
   ptr = strchr( name.c_str(), '*' );
   if ( ptr )
      {
      len = ptr - name.c_str();
      }
   else
      {
      len = name.length();
      }

   // kill only those threads whose name matches name
   num = Threads.NumObjects();

   // Clear the waitfor's from each thread before deleting
   // so they don't get triggered.
   for( i = num; i > 0; i-- )
		{
		thread = Threads.ObjectAt( i );
      if ( !strnicmp( thread->ThreadName(), name.c_str(), len ) )
         {
         thread->ClearWaitFor();
		   if ( currentThread == thread )
			   {
			   SetCurrentThread( NULL );
			   }
   		delete thread;
         }
		}
	}

qboolean ScriptMaster::NotifyOtherThreads
	(
	int num
	)

	{
	ScriptThread *thread1;
	ScriptThread *thread2;
	int i;
	int n;
	Event *ev;

	thread1 = GetThread( num );
   assert( thread1 );
	n = Threads.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		thread2 = Threads.ObjectAt( i );
      assert( thread2 );
		if ( thread2->WaitingOnThread() == thread1 )
			{
			ev = new Event( EV_ScriptThread_ThreadCallback );
			ev->SetThread( thread1 );
			thread2->ProcessEvent( ev );

			return true;
			}
		}
	return false;
	}


void ScriptMaster::DeathMessage
	(
	const char *name
	)
   {
   ScriptThread         *thread;
   Event                *ev;
	int                  i,n;

   // Look for threads that are waiting for this name
   n = Threads.NumObjects();
   for( i = 1; i <= n; i++ )
		{
      const char *waiting;
		thread = Threads.ObjectAt( i );
      assert( thread );
      if (thread)
         {
         waiting = thread->WaitingOnDeath();
         if (waiting)
            {
            if (!strcmp(waiting, name))
               {
   			   ev = new Event( EV_ScriptThread_DeathCallback );
               thread->ProcessEvent(ev);
               }
            }
         }
      }
   }

void ScriptMaster::PlayerSpawned
	(
   void
	)
   {
   ScriptThread         *thread;
	int                  i,n;

   player_ready = true;
   // Look for threads that are waiting for the player
   n = Threads.NumObjects();
   for( i = 1; i <= n; i++ )
		{
		thread = Threads.ObjectAt( i );
      assert( thread );
      if (thread)
         {
         if ( thread->WaitingOnPlayer() )
            {
	         thread->ClearWaitFor();
            thread->Start( 0 );
            }
         }
      }
   }

qboolean ScriptMaster::KillThread
	(
	int num
	)

	{
	ScriptThread *thread;

	// Must be safely reentryable so that the thread destructor can tell us that it's being deleted.
	thread = GetThread( num );
	if ( thread )
		{
      thread->ClearWaitFor();
		if ( currentThread == thread )
			{
			SetCurrentThread( NULL );
			}
		delete thread;

      return true;
		}

	return false;
	}

qboolean ScriptMaster::RemoveThread
	(
	int num
	)

	{
	ScriptThread *thread;
	int i;
	int n;

	// Must be safely reentryable so that the thread destructor can tell us that it's being deleted.
	n = Threads.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		thread = Threads.ObjectAt( i );
      assert( thread );
      if ( thread )
         {
		   if ( thread->ThreadNum() == num )
			   {
            Threads.ObjectAt( i )->ClearWaitFor();
			   Threads.RemoveObjectAt( i );
			   if ( currentThread == thread )
				   {
				   SetCurrentThread( NULL );
				   }
			   return true;
			   }
         }
		}

	return false;
	}

ScriptThread *ScriptMaster::CurrentThread
	(
	void
	)

	{
	return currentThread;
	}

void ScriptMaster::SetCurrentThread
	(
	ScriptThread *thread
	)

	{
	currentThread = thread;
	}

ScriptThread *ScriptMaster::CreateThread
	(
   scripttype_t type
	)

	{
	ScriptThread *thread;

	thread = new ScriptThread;

	thread->SetType( type );
   thread->SetThreadNum( GetUniqueThreadNumber() );
	Threads.AddObject( thread );

	return thread;
	}

ScriptThread *ScriptMaster::CreateThread
	(
	GameScript *scr,
	const char *label,
   scripttype_t type
	)

	{
	ScriptThread *thread;
	int threadnum;

	thread = new ScriptThread;

	thread->SetType( type );
   threadnum = GetUniqueThreadNumber();
	Threads.AddObject( thread );

	if ( !thread->Setup( threadnum, scr, label ) )
		{
		KillThread( threadnum );
		return NULL;
		}

	return thread;
	}

//FIXME
// Why can't these be one function?
ScriptThread *ScriptMaster::CreateThread
	(
	const char *name,
	scripttype_t type,
   const char *label
	)

	{
	GameScript *scr;
	ScriptThread *thread;

	scr = ScriptLib.GetScript( name );
	if ( scr )
		{
		thread = CreateThread( scr, label, type );
		return thread;
		}

	return NULL;
	}

ScriptThread *ScriptMaster::GetThread
	(
	int num
	)

	{
	int i;
	int n;
	ScriptThread *thread;

	n = Threads.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		thread = Threads.ObjectAt( i );
      assert( thread );
      if ( thread )
         {
		   if ( thread->ThreadNum() == num )
			   {
			   return thread;
			   }
         }
		}

	return NULL;
	}

int ScriptMaster::GetUniqueThreadNumber
	(
	void
	)

	{
   do
      {
      threadIndex++;
      if ( threadIndex == 0 )
         {
         threadIndex = 1;
         }
      }
   while( GetThread( threadIndex ) );

   return threadIndex;
	}

qboolean ScriptMaster::labelExists
	(
   GameScript * scr,
	const char *name
	)

	{
	return scr->labelExists( name );
	}

qboolean ScriptMaster::labelExists
	(
   const char *filename,
	const char *name
	)
	{
	GameScript *scr;

	scr = ScriptLib.GetScript( filename );
	if ( scr )
		{
   	return scr->labelExists( name );
		}

	return qfalse;
	}

qboolean ScriptMaster::Goto
	(
   GameScript * scr,
	const char *name
	)

	{
	return scr->Goto( name );
	}

bool ScriptMaster::isVarGroup
	(
	const char *name
	)

	{
	const char *v;
	char	vargroup[ 20 ];
	int	len;

   assert( name );
   if ( !name )
      {
      return false;
      }

	v = strchr( name, '.' );
	if ( !v )
		{
		return false;
		}

	len = v - name;
	if ( len > sizeof( vargroup ) - 1 )
		{
		len = sizeof( vargroup ) - 1;
		}
	memset( vargroup, 0, sizeof( vargroup ) );
	strncpy( vargroup, name, len );

	if ( !strcmp( vargroup, "game" ) || !strcmp( vargroup, "level" ) ||
      !strcmp( vargroup, "local" ) || !strcmp( vargroup, "parm" ) )
		{
		return true;
		}

	return false;
	}

ScriptVariableList *ScriptMaster::GetVarGroup
	(
	const char *name
	)

	{
	ScriptVariableList *vars;
	const char *v;
	char	vargroup[ 20 ];
	int	len;

	v = strchr( name, '.' );
	if ( !v )
		{
		return NULL;
		}

	len = v - name;
	if ( len > sizeof( vargroup ) - 1 )
		{
		len = sizeof( vargroup ) - 1;
		}
	memset( vargroup, 0, sizeof( vargroup ) );
	strncpy( vargroup, name, len );

	vars = NULL;
	if ( !strcmp( vargroup, "game" ) )
		{
		vars = &gameVars;
		}
	else if ( !strcmp( vargroup, "level" ) )
		{
		vars = &levelVars;
		}
	else if ( !strcmp( vargroup, "local" ) && currentThread )
		{
		vars = currentThread->Vars();
		}
	else if ( !strcmp( vargroup, "parm" ) )
		{
		vars = &parmVars;
		}

	return vars;
	}

ScriptVariable *ScriptMaster::GetExistingVariable
	(
	const char *name
	)

	{
	ScriptVariableList	*vars;
	const char				*v;

	vars = GetVarGroup( name );
	if ( !vars )
		{
		return NULL;
		}

	v = strchr( name, '.' );
	if ( !v )
		{
		return NULL;
		}

	return vars->GetVariable( v + 1 );
	}

ScriptVariable *ScriptMaster::GetVariable
	(
	const char *name
	)

	{
	ScriptVariable			*var;
	ScriptVariableList	*vars;
	const char *v;

	var = GetExistingVariable( name );
	if ( !var )
		{
		vars = GetVarGroup( name );
		if ( !vars )
			{
			return NULL;
			}

		v = strchr( name, '.' );
		assert( v );
		var = vars->CreateVariable( v + 1, "" );
		}

	return var;
	}

CLASS_DECLARATION( Listener, ScriptThread, NULL )
	{
	   { &EV_ScriptThread_Execute,			         Execute },
	   { &EV_MoveDone,							         ObjectMoveDone },
	   { &EV_ScriptThread_Callback,			         ScriptCallback },
		{ &EV_ScriptThread_ThreadCallback,           ThreadCallback },
      { &EV_ScriptThread_VariableCallback,         VariableCallback },
      { &EV_ScriptThread_DeathCallback,            DeathCallback },
	   { &EV_ScriptThread_CreateThread,		         CreateThread },
		{ &EV_ScriptThread_TerminateThread,	         TerminateThread },
	   { &EV_ScriptThread_ControlObject,	         ControlObject },
	   { &EV_ScriptThread_Goto,				         EventGoto },
	   { &EV_ScriptThread_Pause,				         EventPause },
	   { &EV_ScriptThread_Wait,				         EventWait },
	   { &EV_ScriptThread_WaitFor,			         EventWaitFor },
	   { &EV_ScriptThread_WaitForThread,	         EventWaitForThread },
      { &EV_ScriptThread_WaitForVariable,	         EventWaitForVariable },
      { &EV_ScriptThread_WaitForDeath, 	         EventWaitForDeath },
      { &EV_ScriptThread_WaitForSound, 	         EventWaitForSound },
		{ &EV_ScriptThread_WaitForDialog, 	         EventWaitForDialog },
      { &EV_ScriptThread_WaitForPlayer, 	         EventWaitForPlayer },
	   { &EV_ScriptThread_End,					         EventEnd },
	   { &EV_ScriptThread_Print,				         Print },
	   { &EV_ScriptThread_PrintInt,			         PrintInt },
	   { &EV_ScriptThread_PrintFloat,		         PrintFloat },
	   { &EV_ScriptThread_PrintVector,		         PrintVector },
	   { &EV_ScriptThread_NewLine,			         NewLine },
		{ &EV_ScriptThread_Assert,				         Assert },
		{ &EV_ScriptThread_Break,				         Break },
	   { &EV_ScriptThread_Clear,				         Clear },
		{ &EV_ScriptThread_Trigger,			         TriggerEvent },
		{ &EV_ScriptThread_ServerOnly,		         ServerEvent },
		{ &EV_ScriptThread_ClientOnly,		         ClientEvent },
		{ &EV_ScriptThread_StuffCommand,		         StuffCommand },
      { &EV_ScriptThread_Spawn,  			         Spawn },
	   { &EV_ScriptThread_Precache_Cache,	         CacheResourceEvent },
	   { &EV_ScriptThread_RegisterAlias,	         RegisterAlias },
	   { &EV_ScriptThread_RegisterAliasAndCache,	   RegisterAliasAndCache },
		{ &EV_ScriptThread_Map,					         MapEvent },
		{ &EV_ScriptThread_SetCvar,			         SetCvarEvent },
		{ &EV_ScriptThread_CueCamera,			         CueCamera },
		{ &EV_ScriptThread_CuePlayer,			         CuePlayer },
		{ &EV_ScriptThread_FreezePlayer,		         FreezePlayer },
		{ &EV_ScriptThread_ReleasePlayer,	         ReleasePlayer },
      { &EV_ScriptThread_FadeIn,       	         FadeIn },
      { &EV_ScriptThread_FadeOut,       	         FadeOut },
      { &EV_ScriptThread_FadeSound,     	         FadeSound },
      { &EV_ScriptThread_ClearFade,       	      ClearFade },
      { &EV_ScriptThread_Letterbox,       	      Letterbox },
      { &EV_ScriptThread_ClearLetterbox,   	      ClearLetterbox },
      { &EV_ScriptThread_MusicEvent,     	         MusicEvent },
      { &EV_ScriptThread_ForceMusicEvent,          ForceMusicEvent },
		{ &EV_ScriptThread_MusicVolumeEvent,     	   MusicVolumeEvent },
		{ &EV_ScriptThread_RestoreMusicVolumeEvent,  RestoreMusicVolumeEvent },
      { &EV_ScriptThread_SoundtrackEvent,          SoundtrackEvent },
		{ &EV_ScriptThread_RestoreSoundtrackEvent,   RestoreSoundtrackEvent },
      { &EV_ScriptThread_CameraCommand,            CameraCommand },
      { &EV_ScriptThread_SetCinematic,             SetCinematic },
      { &EV_ScriptThread_SetNonCinematic,          SetNonCinematic },
		{ &EV_ScriptThread_SetAllAIOff,					SetAllAIOff },
		{ &EV_ScriptThread_SetAllAIOn,					SetAllAIOn },
      { &EV_ScriptThread_SetSkipThread,            SetSkipThread },
		{ &EV_ScriptThread_KillEnt,			         KillEnt },
		{ &EV_ScriptThread_RemoveEnt,			         RemoveEnt },
		{ &EV_ScriptThread_KillClass,			         KillClass },
		{ &EV_ScriptThread_RemoveClass,		         RemoveClass },
		{ &EV_ScriptThread_FakePlayer,		         FakePlayer },
		{ &EV_ScriptThread_RemoveFakePlayer,		   RemoveFakePlayer },
		{ &EV_ScriptThread_SetDialogScript,	         SetDialogScript },
      { &EV_ScriptThread_SetLightStyle,            SetLightStyle },
      { &EV_ScriptThread_KillThreadEvent,          KillThreadEvent },
      { &EV_ScriptThread_SetThreadNameEvent,       SetThreadName },
      { &EV_ScriptThread_CenterPrint,              CenterPrint },
      { &EV_ScriptThread_LocationPrint,            LocationPrint },
		{ &EV_ScriptThread_MissionFailed,            MissionFailed },
      { &EV_AI_RecalcPaths,                        PassToPathmanager },
      { &EV_AI_CalcPath,                           PassToPathmanager },
      { &EV_AI_DisconnectPath,                     PassToPathmanager },
		{ NULL, NULL }
	};

ScriptThread::ScriptThread()
	{
	threadNum			= 0;
	ClearWaitFor();
	threadDying			= false;
	doneProcessing		= true;
	type					= LEVEL_SCRIPT;
	}

ScriptThread::~ScriptThread()
	{
	Director.NotifyOtherThreads( threadNum );
	Director.RemoveThread( threadNum );
	}

void ScriptThread::ClearWaitFor
	(
	void
	)

	{
	waitUntil = 0;
	waitingFor = "";
	waitingNumObjects = 0;
	waitingForThread = NULL;
   waitingForVariable = "";
   waitingForDeath = "";
   waitingForPlayer = false;
	}

void ScriptThread::SetType
	(
	scripttype_t newtype
	)

	{
	type = newtype;
	}

scripttype_t ScriptThread::GetType
	(
	void
	)

	{
	return type;
	}

void ScriptThread::SetThreadNum
	(
   int num
	)

	{
   threadNum = num;
	}

int ScriptThread::ThreadNum
	(
	void
	)

	{
	return threadNum;
	}

const char *ScriptThread::ThreadName
	(
	void
	)

	{
	return threadName.c_str();
	}

void ScriptThread::SetThreadName
	(
   Event *ev
	)

	{
   threadName = ev->GetString( 1 );
	}

int ScriptThread::CurrentLine
	(
	void
	)

	{
	return linenumber;
	}

const char *ScriptThread::Filename
	(
	void
	)

	{
	return script.Filename();
	}

ScriptThread *ScriptThread::WaitingOnThread
	(
	void
	)

	{
	return waitingForThread;
	}

const char *ScriptThread::WaitingOnVariable
	(
	void
	)

	{
	return waitingForVariable.c_str();
	}

const char *ScriptThread::WaitingOnDeath
	(
	void
	)

	{
	return waitingForDeath.c_str();
	}

qboolean ScriptThread::WaitingOnPlayer
	(
	void
	)

	{
   return waitingForPlayer;
	}

ScriptVariableList *ScriptThread::Vars
	(
	void
	)

	{
	return &localVars;
	}


qboolean ScriptThread::Setup
	(
	int num,
	GameScript *scr,
	const char *label
	)

	{
	threadNum = num;

	ClearWaitFor();
	script.SetSourceScript( scr );
	if ( label && !Goto( label ) )
		{
		ScriptError( "Can't create thread.  Label '%s' not found", label );
		return false;
		}

	if ( label )
		{
		threadName = label;
		}
	else
		{
		threadName = script.Filename();
		}

	return true;
	}

qboolean ScriptThread::SetScript
	(
	const char *name
	)

	{
	GameScript *scr;

	scr = ScriptLib.GetScript( name );
	if ( scr )
		{
		Setup( threadNum, scr, NULL );
		return true;
		}

	return false;
	}

qboolean ScriptThread::Goto
	(
	const char *name
	)

	{
	qboolean result;

	result = ScriptLib.Goto( &script, name );
	if ( result )
		{
		// Cancel pending execute events when waitUntil is set
		if ( waitUntil )
			{
			CancelEventsOfType( EV_ScriptThread_Execute );
			}
		ClearWaitFor();
		}
   return result;
	}

qboolean ScriptThread::labelExists
	(
	const char *name
	)

	{
   return ScriptLib.labelExists( &script, name );
	}

void	ScriptThread::Mark
	(
	ThreadMarker *mark
	)

	{
	assert( mark );

	mark->linenumber				= linenumber;
	mark->doneProcessing			= doneProcessing;
	mark->waitingFor				= waitingFor;
	mark->waitingForThread		= waitingForThread;
	mark->waitingForVariable	= waitingForVariable;
	mark->waitingForDeath		= waitingForDeath;
	mark->waitingForPlayer		= waitingForPlayer;
	mark->waitingNumObjects		= waitingNumObjects;
	if ( waitUntil )
		{
		// add one so that 0 is always reserved for no wait
		mark->waitUntil = waitUntil - level.time + 1;
		}
	else
		{
		mark->waitUntil = 0;
		}

	script.Mark( &mark->scriptmarker );
	}

void	ScriptThread::Restore
	(
	ThreadMarker *mark
	)

	{
	assert( mark );

	linenumber				= mark->linenumber;
	doneProcessing			= mark->doneProcessing;

	waitingFor				= mark->waitingFor;
	waitingForThread		= mark->waitingForThread;
	waitingForVariable	= mark->waitingForVariable;
	waitingForDeath		= mark->waitingForDeath;
	waitingForPlayer		= mark->waitingForPlayer;
	waitingNumObjects		= mark->waitingNumObjects;

	script.Restore( &mark->scriptmarker );

	if ( mark->waitUntil )
		{
		// subtract one since we added one when we stored it.
		// this way, 0 is always reserved for no wait
		// Cheezy, yeah, but since I'm commenting it, it's "ok". :)
		waitUntil = mark->waitUntil + level.time - 1;
      Start( waitUntil - level.time );
		}
	}

TargetList *ScriptThread::GetTargetList
	(
   str &targetname
	)
	{
   TargetList *tlist;
   int num;
   int i;

   num = targets.NumObjects();
   for( i = 1; i <= num; i++ )
      {
      tlist = targets.ObjectAt( i );
      if ( targetname == tlist->targetname )
			{
         return tlist;
			}
      }

   tlist = world->GetTargetList( targetname );
   targets.AddObject( tlist );

   return tlist;
	}

void ScriptThread::SendCommandToSlaves
	(
	const char *name,
	Event *ev
	)

	{
	Event		   *sendevent;
	Entity	   *ent;
   TargetList  *tlist;
   int         i;
   int         num;

   if ( name && name[ 0 ] )
      {
      tlist = GetTargetList( str(name+1) );
      num = tlist->list.NumObjects();
      for ( i = 1; i <= num; i++ )
         {
         ent = tlist->list.ObjectAt( i );

		   assert( ent );

		   sendevent = new Event( *ev );

			if ( !updateList.ObjectInList( ent->entnum ) )
			   {
			   updateList.AddObject( ent->entnum );

			   // Tell the object that we're about to send it some orders
			   ent->ProcessEvent( EV_Script_NewOrders );
			   }

		   // Send the command
		   ent->ProcessEvent( sendevent );
         }
      if ( !num )
         {
         warning( "SendCommandToSlaves", "Could not find target %s in world.\n", name );
         }
      }
   //
   // free up the event
   //
   delete ev;
	}

qboolean ScriptThread::FindEvent
	(
	const char *name
	)

	{
   if ( !Event::Exists( name ) )
		{
		ScriptError( "Unknown command '%s'\n", name );
		script.SkipToEOL();
		return false;
		}

	return true;
	}

void ScriptThread::ProcessCommand
	(
	int argc,
	const char **argv
	)

	{
	ScriptVariableList *vars;
	ScriptVariable		 *var;
	str		command;
	str		name;
	Event		*event;
	Entity	*ent;

	if ( argc < 1 )
		{
		return;
		}

	name = argv[ 0 ];
	if ( argc > 1 )
		{
		command = argv[ 1 ];
		}

	// Check for variable commands
	vars = Director.GetVarGroup( name.c_str() );
	if ( vars )
		{
		var = Director.GetVariable( name.c_str() );
		if ( var->isVariableCommand( command.c_str() ) )
			{
			event = new Event( command );
			event->SetSource( EV_FROM_SCRIPT );
			event->SetThread( this );
			event->SetLineNumber( linenumber );
			event->AddTokens( argc - 2, &argv[ 2 ] );
			var->ProcessEvent( event );
			return;
			}

		name = var->stringValue();
		if ( !name.length() )
			{
			ScriptError( "Uninitialized variable '%s' used for command '%s'", var->getName(), command.c_str() );
			return;
			}
		else if ( name[ 0 ] != '$' && name[ 0 ] != '@' && name[ 0 ] != '%' && name[ 0 ] != '*' )
			{
			ScriptError( "Invalid variable command '%s'", command.c_str() );
			return;
			}
		}

	// Check for object commands
	if ( name[ 0 ] == '$' )
		{
		if ( FindEvent( command.c_str() ) )
			{
			event = new Event( command );
			event->SetSource( EV_FROM_SCRIPT );
			event->SetThread( this );
			event->SetLineNumber( linenumber );
			event->AddTokens( argc - 2, &argv[ 2 ] );
			SendCommandToSlaves( name.c_str(), event );
			}
		return;
		}

   // Check for entnum commands
   if ( name[ 0 ] == '*' )
      {
		if ( !IsNumeric( &name[ 1 ] ) )
			{
			ScriptError( "Expecting numeric value for * command, but found '%s'\n", &name[ 1 ] );
			}
		else if ( FindEvent( command.c_str() ) )
         {
         ent = G_GetEntity( atoi( &name[ 1 ] ) );
         if ( ent )
            {
            event = new Event( command );
				event->SetSource( EV_FROM_SCRIPT );
				event->SetThread( this );
				event->SetLineNumber( linenumber );
            event->AddTokens( argc - 2, &argv[ 2 ] );
            ent->ProcessEvent( event );
            }
         else
            {
            ScriptError( "Entity not found for * command\n" );
            }
         }
      return;
      }

	// Handle global commands
	if ( FindEvent( name.c_str() ) )
		{
		event = new Event( name );
		event->SetSource( EV_FROM_SCRIPT );
		event->SetThread( this );
		event->SetLineNumber( linenumber );
		event->AddTokens( argc - 1, &argv[ 1 ] );
		if ( !ProcessEvent( event ) )
			{
			ScriptError( "Invalid global command '%s'\n", name.c_str() );
			}
		}
	}

void ScriptThread::ProcessCommandFromEvent
	(
	Event *ev,
	int startarg
	)

	{
	int			argc;
	int			numargs;
	const char	*argv[ MAX_COMMANDS ];
	str			args[ MAX_COMMANDS ];
	int			i;

	numargs = ev->NumArgs();
	if ( numargs < startarg )
		{
		ev->Error( "Expecting statement after conditional", MAX_COMMANDS );
		return;
		}

	argc = numargs - startarg + 1;

	if ( argc >= MAX_COMMANDS )
		{
		ev->Error( "Line exceeds %d command limit", MAX_COMMANDS );
		return;
		}

	for( i = 0; i < argc; i++ )
		{
		args[ i ] = ev->GetToken( startarg + i );
		argv[ i ] = args[ i ].c_str();
		}

	ProcessCommand( argc, argv );
	}

void ScriptThread::Start
	(
   float delay
	)
	{
	CancelEventsOfType( EV_ScriptThread_Execute );
   PostEvent( EV_ScriptThread_Execute, delay );
   }

void ScriptThread::StartImmediately
	(
   void
	)
	{
	CancelEventsOfType( EV_ScriptThread_Execute );
   ProcessEvent( EV_ScriptThread_Execute );
   }

void ScriptThread::Execute
	(
	Event *ev
	)

	{
	int num;
	ScriptThread *oldthread;
	int argc;
	const char *argv[ MAX_COMMANDS ];
	char args[ MAX_COMMANDS ][ MAXTOKEN ];
	ScriptVariable	*var;

	if ( threadDying )
		{
		return;
		}

	// set the current game time
	if ( !GameTime )
		{
		GameTime = gameVars.CreateVariable( "time", 0 );
		}

	GameTime->setFloatValue( level.time );

	// clear the updateList so that all objects moved this frame are notified before they receive any commands
	// we have to do this here as well as in DoMove, since DoMove may not be called
	updateList.ClearObjectList();

	oldthread = Director.CurrentThread();
	Director.SetCurrentThread( this );

	// if we're not being called from another thread, clear the parm variables
	if ( !oldthread )
		{
		parmVars.ClearList();
		}

	ClearWaitFor();

	var = Director.GetVariable( "parm.previousthread" );
	if ( oldthread )
		{
		var->setIntValue( oldthread->ThreadNum() );
		}
	else
		{
		var->setIntValue( 0 );
		}

	var = Director.GetVariable( "parm.currentthread" );

	doneProcessing = false;

	num = 0;
	while( ( num++ < 10000 ) && !doneProcessing && !threadDying )
		{
		// keep our thread number up to date
		var->setIntValue( threadNum );

		script.SkipNonToken( true );

		// save the line number for errors
		linenumber = script.GetLineNumber();

		argc = 0;
		while( script.TokenAvailable( false ) )
			{
			if ( argc >= MAX_COMMANDS )
				{
				ScriptError( "Line exceeds %d command limit", MAX_COMMANDS );
				script.SkipToEOL();
				break;
				}
			strcpy( args[ argc ], script.GetToken( false ) );
			argv[ argc ] = args[ argc ];
			argc++;
			}

		assert( argc > 0 );

		// Ignore labels
		if ( args[ 0 ][ strlen( args[ 0 ] ) - 1 ] != ':' )
			{
			ProcessCommand( argc, argv );
			}
		}

	if ( !doneProcessing )
		{
		gi.Error( ERR_DROP, "Command overflow.  Possible infinite loop in thread '%s'.\n"
			"Stopping on line %d of %s\n", threadName.c_str(), script.GetLineNumber(), script.Filename() );
		}

	Director.SetCurrentThread( oldthread );

	// Set the thread number on exit, in case we were called by someone who wants to know our thread
	var = Director.GetVariable( "parm.previousthread" );
	var->setIntValue( threadNum );
	}

void ScriptThread::ScriptError
	(
	const char *fmt,
	...
	)

	{
	va_list	argptr;
	char		text[ 1024 ];

	va_start( argptr, fmt );
	vsprintf( text, fmt, argptr );
	va_end( argptr );

   gi.DPrintf( "%s(%d):: %s\n", Filename(), linenumber, text );
	}

//****************************************************************************************
//
// global commands
//
//****************************************************************************************

qboolean ScriptThread::WaitingFor
	(
	Entity *obj
	)

	{
	assert( obj );

	if ( waitingFor.length() )
		{
		if ( ( ( waitingFor[ 0 ] == '*' ) && ( atoi( &waitingFor.c_str()[ 1 ] ) == obj->entnum ) ) ||
			( waitingFor == obj->TargetName() ) )
			{
			return true;
			}
		}

	return false;
	}

void ScriptThread::ObjectMoveDone
	(
	Event *ev
	)

	{
	Entity *obj;

	obj = ev->GetEntity( 1 );

	if ( !obj )
		{
		gi.DPrintf( "Object no longer exists, MoveDone invalid now\n" );
		return;
		}

#if 0
   gi.DPrintf( "Move done %d:'%s'\n", obj->entnum, obj->TargetName() );
#endif

	if ( WaitingFor( obj ) )
		{
      waitingNumObjects--;
      if ( waitingNumObjects <= 0 )
         {
		   ClearWaitFor();
         // start right away
         Start( 0 );
         }
		}
	}

void ScriptThread::CreateThread
	(
	Event *ev
	)

	{
   ScriptThread * pThread;

	pThread = Director.CreateThread( &script, ev->GetToken( 1 ) );
   if ( pThread )
      {
      // start right away
      pThread->StartImmediately();
      }
	}

void ScriptThread::TerminateThread
	(
	Event *ev
	)

	{
   int threadnum;
   ScriptThread *thread;

   threadnum = 0;
   // we specified the thread to kill
   if ( ev->NumArgs() > 0 )
      {
      threadnum = ev->GetInteger( 1 );
      }
   else
      {
   	thread = ev->GetThread();
	   if ( thread )
		   {
		   threadnum = thread->ThreadNum();
		   }
      }

   if ( threadnum != 0 )
      {
      thread = Director.GetThread( threadnum );
      if ( thread && ( thread->GetType() == MODEL_SCRIPT ) && ( ev->GetSource() == EV_FROM_SCRIPT ) )
         {
         ev->Error( "Can't terminate an actor's thread via script." );
         return;
         }
      Director.KillThread( threadnum );
      }
	}

void ScriptThread::ControlObject
	(
	Event *ev
	)

	{
	ev->GetEntity( 1 );
	}

void ScriptThread::EventGoto
	(
	Event *ev
	)

	{
	const char *label;

	label = ev->GetToken( 1 );
	if ( !Goto( label ) )
		{
		ev->Error( "Label '%s' not found", label );
		}
	}

void ScriptThread::EventPause
	(
	Event *ev
	)

	{
   DoMove();

	ClearWaitFor();

	doneProcessing = true;
	}

void ScriptThread::EventWait
	(
	Event *ev
	)

	{
	DoMove();

	ClearWaitFor();

	waitUntil = ev->GetFloat( 1 ) + level.time;

	Start( ev->GetFloat( 1 ) );
	doneProcessing = true;
	}

void ScriptThread::EventWaitFor
   (
   Event *ev
   )

   {
   Entity *ent;
   const char *objname;
   const char *tname;

   ClearWaitFor();
   //
   // we need to make sure we have an entity we are going to wait for
   //

   ent = ev->GetEntity( 1 );
   if ( ent )
      {
      doneProcessing = true;

      objname = ev->GetString( 1 );
      tname = ent->TargetName();
      if ( objname && objname[ 0 ] == '*' )
         {
         if ( !IsNumeric( &objname[ 1 ] ) )
            {
            ScriptError( "Expecting *-prefixed numeric value for waitFor command, but found '%s'\n", objname );
            return;
            }

         waitingFor = objname;
         }
      else if ( !tname || !tname[ 0 ] )
         {
         // Probably won't happen, but check for it anyway.
         ScriptError( "Entity doesn't have a targetname.\n" );
         return;
         }
      else
         {
         TargetList  *tlist;
         waitingFor = tname;
         //
         // set the number of objects that belong to this targetname
         //
         tlist = GetTargetList( waitingFor );
         waitingNumObjects = tlist->list.NumObjects();
         if ( waitingNumObjects <= 0 )
            {
            waitingNumObjects = 1;
            ScriptError( "no objects of targetname %s found.\n", tname );
            }
         else
            {
            Entity * tent;
            int i;
            //
            // make sure all these objects are in the update list
            //
            for ( i = 1; i <= waitingNumObjects; i++ )
               {
               tent = tlist->list.ObjectAt( i );
               // add the object to the update list to make sure we tell it to do a move
               if ( !updateList.ObjectInList( tent->entnum ) )
                  {
                  updateList.AddObject( tent->entnum );
                  }
               }
            }
         }

      // add the object to the update list to make sure we tell it to do a move
      if ( !updateList.ObjectInList( ent->entnum ) )
         {
         updateList.AddObject( ent->entnum );
         }
      }

   DoMove();
   }

void ScriptThread::EventWaitForThread
	(
	Event *ev
	)

	{
	ClearWaitFor();
	waitingForThread = Director.GetThread( ev->GetInteger( 1 ) );
	if ( !waitingForThread )
		{
		ev->Error( "EventWaitForThread", "Thread %d not running", ev->GetInteger( 1 ) );
		return;
		}
	doneProcessing = true;

	DoMove();
	}

void ScriptThread::EventWaitForDeath
	(
	Event *ev
	)

	{
	ClearWaitFor();
	waitingForDeath = ev->GetString(1);
	if ( !waitingForDeath.length() )
		{
		ev->Error( "EventWaitForDeath", "Null name" );
		return;
		}
   doneProcessing = true;

	DoMove();
	}

void ScriptThread::EventWaitForVariable
	(
	Event *ev
	)

	{
	ClearWaitFor();
	waitingForVariable = ev->GetString(1);

	if ( !waitingForVariable.length() )
		{
		ev->Error( "EventWaitForVariable", "Null variable" );
		return;
		}
   doneProcessing = true;

	DoMove();
	}

void ScriptThread::EventWaitForSound
	(
	Event *ev
	)

	{
   str sound;
   float delay;

	ClearWaitFor();

	DoMove();

   delay = 0;
	sound = ev->GetString( 1 );

   delay = gi.SoundLength( sound.c_str() );

	if ( delay < 0 )
		gi.DPrintf( "Lip file not found for dialog %s\n", sound.c_str() );

	if ( ev->NumArgs() > 1 )
      delay += ev->GetFloat( 2 );

   Start( delay );
	doneProcessing = true;
	}

void ScriptThread::EventWaitForDialog
	(
	Event *ev
	)

	{
	float delay;
   Actor *act;
	Entity *ent;

	ClearWaitFor();

	ent = ev->GetEntity( 1 );

	if ( ent && ent->isSubclassOf( Actor ) )
		{
		act = (Actor *)ent;

		delay = act->GetDialogRemainingTime( );
      if ( ev->NumArgs() > 1 )
         {
         delay += ev->GetFloat( 2 );
         }
		Start( delay );
		doneProcessing = true;
		}
	}

void ScriptThread::EventWaitForPlayer
	(
	Event *ev
	)

	{
   doneProcessing = true;

	ClearWaitFor();
	waitingForPlayer = true;

	DoMove();
	}

void ScriptThread::EventEnd
	(
	Event *ev
	)

	{
	ScriptVariable *var;
	const char *text;
	Entity *ent;

	ClearWaitFor();

	// If we're a model script, we have to tell our owning entity that we're done.
	if ( ( ev->GetSource() == EV_FROM_SCRIPT ) && ( type == MODEL_SCRIPT ) )
		{
		doneProcessing = true;
		var = Vars()->GetVariable( "self" );
		if ( !var )
			{
			ev->Error( "Model script ending without local.self set" );
			}
		else
			{
			text = var->stringValue();
			if ( ( text[ 0 ] == '*' ) && IsNumeric( &text[ 1 ] ) )
				{
				ent = G_GetEntity( atoi( &text[ 1 ] ) );

				// pass the event on to entity pointed to by self
				if ( ent )
					{
               Event * newevent;

               newevent = new Event( ev );
					ent->ProcessEvent( newevent );
					return;
					}
				}
			else
				{
				ev->Error( "Model script ending.  Invalid value in local.self '%s'", text );
				}
			}
		}

	Director.NotifyOtherThreads( threadNum );
	PostEvent( EV_Remove, 0 );
	doneProcessing = true;
	threadDying = true;
	}

void ScriptThread::Print
	(
	Event *ev
	)

	{
   gi.DPrintf( "%s", ev->GetString( 1 ) );
	}

void ScriptThread::PrintInt
	(
	Event *ev
	)

	{
   gi.DPrintf( "%d", ev->GetInteger( 1 ) );
	}

void ScriptThread::PrintFloat
	(
	Event *ev
	)

	{
   gi.DPrintf( "%.2f", ev->GetFloat( 1 ) );
	}

void ScriptThread::PrintVector
	(
	Event *ev
	)

	{
   Vector vec;

   vec = ev->GetVector( 1 );
   gi.DPrintf( "(%.2f %.2f %.2f)", vec.x, vec.y, vec.z );
	}

void ScriptThread::NewLine
	(
	Event *ev
	)

	{
   gi.DPrintf( "\n" );
	}

void ScriptThread::Assert
	(
	Event *ev
	)

	{
	assert( ev->GetFloat( 1 ) );
	}

void ScriptThread::Break
	(
	Event *ev
	)

	{
	// Break into the debugger
	assert( 0 );
	}

void ScriptThread::Clear
	(
	Event *ev
	)

	{
	ScriptVariableList *vars;

	vars = Director.GetVarGroup( ev->GetToken( 1 ) );
	if ( vars )
		{
		vars->ClearList();
		}
	}

void ScriptThread::ScriptCallback
	(
	Event *ev
	)

	{
	char		name[ MAXTOKEN ];
	Entity	*other;
	Entity	*slave;

	if ( threadDying )
		{
		return;
		}

	slave = ev->GetEntity( 1 );
	strcpy( name, ev->GetString( 2 ) );
	other = ev->GetEntity( 3 );

	if ( !Goto( name ) )
		{
		ev->Error( "Label '%s' not found", name );
		}
	else
		{
		// kill any execute events (in case our last command was "wait")
		ClearWaitFor();
      // start right away
      StartImmediately();
		}
	}

void ScriptThread::ThreadCallback
	(
	Event *ev
	)

	{
	ScriptThread *thread;

	if ( threadDying )
		{
		return;
		}

	thread = ev->GetThread();

	if ( thread && ( thread == waitingForThread ) )
		{
		ClearWaitFor();
      StartImmediately();
		}
	}

void ScriptThread::VariableCallback
	(
	Event *ev
	)

	{
	ClearWaitFor();
   // start right away
   Start( 0 );
   }

void ScriptThread::DeathCallback
	(
	Event *ev
	)

	{
	if ( threadDying )
		{
		return;
		}

	ClearWaitFor();
   // start right away
   Start( 0 );
   }

void ScriptThread::DoMove
   (
   void
   )

   {
   int      entnum;
   Entity   *ent;
   Event    *event;
   int      count;
   int      i;

   count = updateList.NumObjects();

   for( i = 1; i <= count; i++ )
      {
      entnum = ( int )updateList.ObjectAt( i );
      ent = G_GetEntity( entnum );
      if ( ent )
         {
         if ( ent->ValidEvent( EV_ProcessCommands ) )
            {
            event = new Event( EV_ProcessCommands );
            event->SetThread( this );
            ent->PostEvent( event, 0 );
            }
         else
            {
            // try to remove this from the update list
            if ( waitingNumObjects > 0 )
               {
               waitingNumObjects--;
               }
            }
         }
      }

   updateList.ClearObjectList();
   }

void ScriptThread::TriggerEvent
	(
	Event *ev
	)

	{
	const char	*name;
	Event		   *event;
	Entity	   *ent;
   TargetList  *tlist;
   int         i;
   int         num;

	name = ev->GetString( 1 );

	// Check for object commands
	if ( name && name[ 0 ] == '$' )
		{
      tlist = GetTargetList( str( name + 1 ) );
      num = tlist->list.NumObjects();
      for ( i = 1; i <= num; i++ )
         {
         ent = tlist->list.ObjectAt( i );

		   assert( ent );

         event = new Event( EV_Activate );
			event->SetSource( EV_FROM_SCRIPT );
			event->SetThread( this );
			event->SetLineNumber( linenumber );
         event->AddEntity( world );
		   ent->ProcessEvent( event );
         }
      }
	else if ( name[ 0 ] == '*' )   // Check for entnum commands
      {
		if ( !IsNumeric( &name[ 1 ] ) )
			{
			ScriptError( "Expecting numeric value for * command, but found '%s'\n", &name[ 1 ] );
			}
		else
         {
         ent = G_GetEntity( atoi( &name[ 1 ] ) );
         if ( ent )
            {
            event = new Event( EV_Activate );
				event->SetSource( EV_FROM_SCRIPT );
				event->SetThread( this );
				event->SetLineNumber( linenumber );
            event->AddEntity( world );
            ent->ProcessEvent( event );
            }
         else
            {
            ScriptError( "Entity not found for * command\n" );
            }
         }
      return;
      }
	else
		{
		ScriptError( "Invalid entity reference '%s'.\n", name );
		}
	}

void ScriptThread::ServerEvent
	(
	Event *ev
	)

	{
   int i, argc;
	const char *argv[ MAX_COMMANDS ];

	argc = 0;
   for ( i = 1; i <= ev->NumArgs(); i++ )
      {
      argv[argc++] = ev->GetString( i );
      }

   if (argc)
      {
	   ProcessCommand( argc, argv );
      }
	}

void ScriptThread::ClientEvent
	(
	Event *ev
	)

	{
   //
   // do nothing
   //
   }

void ScriptThread::CacheResourceEvent
	(
   Event * ev
	)

	{
   if ( !precache->integer )
      {
      return;
      }

   if ( world )
      {
      CacheResource( ev->GetString( 1 ), world );
      }
   else
      {
      CacheResource( ev->GetString( 1 ), NULL );
      }
	}

void ScriptThread::RegisterAlias
	(
	Event *ev
	)

	{
	char parameters[100];
	int i;

	// Get the parameters for this alias command

	parameters[0] = 0;

	for( i = 3 ; i <= ev->NumArgs() ; i++ )
	{
		strcat( parameters, ev->GetString( i ) );
		strcat( parameters, " ");
	}

   gi.GlobalAlias_Add( ev->GetString( 1 ), ev->GetString( 2 ),  parameters );
	}

void ScriptThread::RegisterAliasAndCache
	(
	Event *ev
	)

	{
	RegisterAlias(ev);

   if ( !precache->integer )
      return;

   CacheResource( ev->GetString( 2 ) );
	}

void ScriptThread::MapEvent
	(
	Event *ev
	)

	{
	if ( level.mission_failed )
		return;

	G_BeginIntermission( ev->GetString( 1 ) );
	doneProcessing = true;
	}

void ScriptThread::SetCvarEvent
	(
	Event *ev
	)

	{
	str name;

	name = ev->GetString( 1 );
	if ( name != "" )
		{
		gi.cvar_set( name.c_str(), ev->GetString( 2 ) );
		}
	}

void ScriptThread::CueCamera
	(
	Event *ev
	)

	{
   float    switchTime;
	Entity   *ent;

   if ( ev->NumArgs() > 1 )
      {
      switchTime = ev->GetFloat( 2 );
      }
   else
      {
      switchTime = 0;
      }

	ent = ev->GetEntity( 1 );
	if ( ent )
		{
		SetCamera( ent, switchTime );
		}
	else
		{
		ev->Error( "Camera named %s not found", ev->GetString( 1 ) );
		}
	}

void ScriptThread::CuePlayer
	(
	Event *ev
	)

	{
   float    switchTime;

   if ( ev->NumArgs() > 0 )
      {
      switchTime = ev->GetFloat( 1 );
      }
   else
      {
      switchTime = 0;
      }

	SetCamera( NULL, switchTime );
	}

void ScriptThread::FreezePlayer
	(
	Event *ev
	)

	{
	level.playerfrozen = true;
	}

void ScriptThread::ReleasePlayer
	(
	Event *ev
	)

	{
	level.playerfrozen = false;
	}

void ScriptThread::FakePlayer
	(
	Event *ev
	)

	{
   qboolean holster;
   Player *player;

   player = ( Player * )g_entities[ 0 ].entity;
   
   if ( ( ev->NumArgs() < 1 ) || ev->GetBoolean( 1 ) )
      {
      holster = qtrue;
      }
   else
      {
      holster = qfalse;
      }

   if ( player && player->edict->inuse && player->edict->client )
      {
      player->FakePlayer( holster );
      }
	}

void ScriptThread::RemoveFakePlayer
	(
	Event *ev
	)

	{
   Player *player;

   player = ( Player * )g_entities[ 0 ].entity;
   
   if ( player && player->edict->inuse && player->edict->client )
      {
      player->RemoveFakePlayer();
      }
	}

void ScriptThread::Spawn
	(
	Event *ev
	)

	{
	Entity		   *ent;
   Entity         *tent;
   const char	   *name;
	ClassDef		   *cls;
   int			   n;
	int			   i;
   const char     *targetname;
   ScriptVariable	*var;
	const char	   *value;

   if ( ev->NumArgs() < 1 )
		{
		ev->Error( "Usage: spawn entityname [keyname] [value]..." );
		return;
		}

   // create a new entity
   SpawnArgs args;

   name = ev->GetString( 1 );

   if ( name )
      {
      cls = getClassForID( name );
      if ( !cls )
         {
         cls = getClass( name );
         }

      if ( !cls )
         {
         str n;

         n = name;
         if ( !strstr( n.c_str(), ".tik" ) )
            {
            n += ".tik";
            }
         args.setArg( "model", n.c_str() );
         }
      else
         {
         args.setArg( "classname", name );
         }
      }

   if ( ev->NumArgs() > 2 )
		{
		n = ev->NumArgs();
		for( i = 2; i <= n; i += 2 )
			{
			args.setArg( ev->GetString( i ), ev->GetString( i + 1 ) );
			}
		}

   cls = args.getClassDef();
   if ( !cls )
      {
		ev->Error( "'%s' is not a valid entity name", name );
		return;
		}

   // If there is a spawntarget set, then use that entity's origin and angles
   targetname = args.getArg( "spawntarget" );

   if ( targetname )
      {
      tent = G_FindTarget( NULL, targetname );
      if ( tent )
         {
         args.setArg( "origin", va( "%f %f %f", tent->origin[ 0 ], tent->origin[ 1 ], tent->origin[ 2 ] ) );
         args.setArg( "angle", va( "%f", tent->angles[1] ) );
         }
      else
         {
		   ev->Error( "Can't find targetname %s", targetname );
         }
      }

   //
   // make sure to setup spawnflags properly
   //
   level.spawnflags = 0;
	value = args.getArg( "spawnflags" );
	if ( value )
      {
      level.spawnflags = atoi( value );
      }

   ent = args.Spawn();
   if ( ent )
      {
      ent->ProcessPendingEvents();
      }
   var = Director.GetVariable( "parm.lastspawn" );
   var->setIntValue( ent->entnum );
   }

//FIXME
//Move this to someplace Level class.
static float last_fraction = 1.0f/8.0f;

void ScriptThread::Letterbox
   (
   Event *ev
   )

   {
   level.m_letterbox_fraction    = 1.0f/8.0f;
   level.m_letterbox_time        = ev->GetFloat( 1 );
   level.m_letterbox_time_start  = ev->GetFloat( 1 );
   level.m_letterbox_dir         = letterbox_in;

   if ( ev->NumArgs() > 1 )
      level.m_letterbox_fraction = ev->GetFloat( 2 );
   }

void ScriptThread::ClearLetterbox
   (
   Event *ev
   )

   {
   level.m_letterbox_time = level.m_letterbox_time_start;
   level.m_letterbox_dir  = letterbox_out;
   }

void ScriptThread::SetDialogScript
	(
	Event *ev
	)
   {
   ScriptThread * pThread;

   ScriptLib.SetDialogScript( ev->GetString( 1 ) );
   //
   // precache the data in the dialog script
   //
	pThread = Director.CreateThread( &script, "dialog::precache" );
   if ( pThread )
      {
      // start right away
      pThread->Start( -1 );
      }
   }

void ScriptThread::SetLightStyle
	(
	Event *ev
	)
   {
   lightStyles.SetLightStyle( ev->GetInteger( 1 ), ev->GetString( 2 ) );
   }

void ScriptThread::FadeIn
	(
	Event *ev
	)
   {
   level.m_fade_time_start = ev->GetFloat( 1 ); 
   level.m_fade_time       = ev->GetFloat( 1 );
   level.m_fade_color[0]   = ev->GetFloat( 2 );
   level.m_fade_color[1]   = ev->GetFloat( 3 );
   level.m_fade_color[2]   = ev->GetFloat( 4 );
   level.m_fade_alpha      = ev->GetFloat( 5 );
   level.m_fade_type       = fadein;
   level.m_fade_style      = alphablend;  

   if ( ev->NumArgs() > 5 )
      {
      level.m_fade_style   = (fadestyle_t)ev->GetInteger( 6 );
      }
   }

void ScriptThread::ClearFade
   (
   Event *ev
   )

   {
   level.m_fade_time = -1;
   level.m_fade_type = fadein;
   }

void ScriptThread::FadeOut
	(
	Event *ev
	)
   {
   level.m_fade_time_start = ev->GetFloat( 1 ); 
   level.m_fade_time       = ev->GetFloat( 1 );
   level.m_fade_color[0]   = ev->GetFloat( 2 );
   level.m_fade_color[1]   = ev->GetFloat( 3 );
   level.m_fade_color[2]   = ev->GetFloat( 4 );
   level.m_fade_alpha      = ev->GetFloat( 5 );
   level.m_fade_type       = fadeout;
   level.m_fade_style      = alphablend;  

   if ( ev->NumArgs() > 5 )
      {
      level.m_fade_style   = (fadestyle_t)ev->GetInteger( 6 );
      }
   }

void ScriptThread::FadeSound
	(
	Event *ev
	)
   {
   G_FadeSound( ev->GetFloat( 1 ) );
   }

void ScriptThread::MusicEvent
	(
	Event *ev
	)
   {
   const char *current;
   const char *fallback;

   current = NULL;
   fallback = NULL;
   current = ev->GetString( 1 );

   if ( ev->NumArgs() > 1 )
      fallback = ev->GetString( 2 );

   ChangeMusic( current, fallback, false );
   }

void ScriptThread::MusicVolumeEvent
	(
	Event *ev
	)
   {
   float volume;
   float fade_time;

   volume    = ev->GetFloat( 1 );
   fade_time = ev->GetFloat( 2 );

   ChangeMusicVolume( volume, fade_time );
   }

void ScriptThread::RestoreMusicVolumeEvent
	(
	Event *ev
	)
   {
   float fade_time;

   fade_time = ev->GetFloat( 1 );

   RestoreMusicVolume( fade_time );
   }

void ScriptThread::ForceMusicEvent
	(
	Event *ev
	)
   {
   const char *current;
   const char *fallback;

   current = NULL;
   fallback = NULL;
   current = ev->GetString( 1 );

   if ( ev->NumArgs() > 1 )
      fallback = ev->GetString( 2 );

   ChangeMusic( current, fallback, true );
   }

void ScriptThread::SoundtrackEvent
	(
	Event *ev
	)
   {
   ChangeSoundtrack( ev->GetString( 1 ) );
   }

void ScriptThread::RestoreSoundtrackEvent
	(
	Event *ev
	)
   {
   RestoreSoundtrack();
   }

void ScriptThread::SetCinematic
   (
   Event *ev
   )

   {
   G_StartCinematic();
   }

void ScriptThread::SetNonCinematic
   (
   Event *ev
   )

   {
   G_StopCinematic();
   }

void ScriptThread::SetAllAIOff
   (
   Event *ev
   )

   {
   level.ai_on = false;
   }

void ScriptThread::SetAllAIOn
   (
   Event *ev
   )

   {
   level.ai_on = true;
   }

void ScriptThread::SetSkipThread
   (
   Event *ev
   )

   {
   str label;

   label = ev->GetString( 1 );
   if ( label.length() && label.icmp( "null" ) )
      {
      world->skipthread = script.Filename() + str( "::" ) + label;
      }
   else
      {
      world->skipthread = "";
      }
   }

void ScriptThread::KillThreadEvent
   (
   Event *ev
   )

   {
   Director.KillThread( ev->GetString( 1 ) );
   }

void ScriptThread::PassToPathmanager
   (
   Event *ev
   )

   {
   PathManager.ProcessEvent( ev );
   }

void ScriptThread::CenterPrint
   (
   Event *ev
   )

   {
   int         j;
   gentity_t   *other;

	for( j = 0; j < game.maxclients; j++ )
		{
      other = &g_entities[ j ];
		if ( other->inuse && other->client )
			{
         gi.centerprintf( other, ev->GetString( 1 ) );
			}
      }
   }

void ScriptThread::LocationPrint
   (
   Event *ev
   )

   {
   int         j;
   gentity_t   *other;
   int         x,y;

   x = ev->GetInteger( 1 );
   y = ev->GetInteger( 2 );

	for( j = 0; j < game.maxclients; j++ )
		{
      other = &g_entities[ j ];
		if ( other->inuse && other->client )
			{
         gi.locationprintf( other, x, y, ev->GetString( 3 ) );
			}
      }
   }

void ScriptThread::StuffCommand
   (
   Event *ev
   )

   {
   gi.SendConsoleCommand( va( "%s\n", ev->GetString( 1 ) ) );
   }

void ScriptThread::KillEnt
	(
   Event * ev
   )
   {
	int num;
	Entity *ent;

	if ( ev->NumArgs() != 1 )
		{
		ev->Error( "No args passed in" );
		return;
		}

	num = ev->GetInteger( 1 );
   if ( ( num < 0 ) || ( num >= globals.max_entities ) )
		{
      ev->Error( "Value out of range.  Possible values range from 0 to %d.\n", globals.max_entities );
		return;
		}

	ent = G_GetEntity( num );
   ent->Damage( world, world, ent->max_health + 25, vec_zero, vec_zero, vec_zero, 0, 0, 0 );
   }

void ScriptThread::RemoveEnt
	(
   Event * ev
   )
   {
	int num;
	Entity *ent;

	if ( ev->NumArgs() != 1 )
		{
		ev->Error( "No args passed in" );
		return;
		}

	num = ev->GetInteger( 1 );
   if ( ( num < 0 ) || ( num >= globals.max_entities ) )
		{
      ev->Error( "Value out of range.  Possible values range from 0 to %d.\n", globals.max_entities );
		return;
		}

	ent = G_GetEntity( num );
   ent->PostEvent( Event( EV_Remove ), 0 );
   }

void ScriptThread::KillClass
	(
   Event * ev
   )
   {
   int except;
   str classname;
   gentity_t * from;
	Entity *ent;

	if ( ev->NumArgs() < 1 )
		{
		ev->Error( "No args passed in" );
		return;
		}

   classname = ev->GetString( 1 );

   except = 0;
   if ( ev->NumArgs() == 2 )
      {
      except = ev->GetInteger( 1 );
      }

   for ( from = &g_entities[ game.maxclients ]; from < &g_entities[ globals.num_entities ]; from++ )
		{
		if ( !from->inuse )
			{
			continue;
			}

		assert( from->entity );

      ent = from->entity;

      if ( ent->entnum == except )
         {
         continue;
         }

   	if ( ent->inheritsFrom( classname.c_str() ) )
         {
         ent->Damage( world, world, ent->max_health + 25, vec_zero, vec_zero, vec_zero, 0, 0, 0 );
         }
      }
   }

void ScriptThread::RemoveClass
	(
   Event * ev
   )
   {
   int except;
   str classname;
   gentity_t * from;
	Entity *ent;

	if ( ev->NumArgs() < 1 )
		{
		ev->Error( "No args passed in" );
		return;
		}

   classname = ev->GetString( 1 );

   except = 0;
   if ( ev->NumArgs() == 2 )
      {
      except = ev->GetInteger( 1 );
      }

   for ( from = &g_entities[ game.maxclients ]; from < &g_entities[ globals.num_entities ]; from++ )
		{
		if ( !from->inuse )
			{
			continue;
			}

		assert( from->entity );

      ent = from->entity;

      if ( ent->entnum == except )
         continue;

   	if ( ent->inheritsFrom( classname.c_str() ) )
         {
         ent->PostEvent( Event( EV_Remove ), 0 );
         }
      }
   }

void ScriptThread::CameraCommand
	(
   Event * ev
   )

   {
   Event *e;
	const char *cmd;
   int   i;
   int   n;

   if ( !ev->NumArgs() )
      {
      ev->Error( "Usage: cam [command] [arg 1]...[arg n]" );
      return;
      }

	cmd = ev->GetString( 1 );
  	if ( Event::Exists( cmd ) )
		{
		e = new Event( cmd );
		e->SetSource( EV_FROM_SCRIPT );
		e->SetThread( this );
		e->SetLineNumber( linenumber );

      n = ev->NumArgs();
		for( i = 2; i <= n; i++ )
			{
			e->AddToken( ev->GetToken( i ) );
			}

      CameraMan.ProcessEvent( e );
      }
   else
      {
      ev->Error( "Unknown camera command '%s'.\n", cmd );
      }
   }

void ScriptThread::MissionFailed
   (
   Event *ev
   )

   {
	G_MissionFailed();
   }

////////////////////////
//
// LIGHTSTYLE REPOSITORY
// 
////////////////////////

LightStyleClass lightStyles;

CLASS_DECLARATION( Class, LightStyleClass, NULL )
	{
		{ NULL, NULL }
	};

void LightStyleClass::SetLightStyle( int index, str style )
   {
   if ( ( index < 0 ) || ( index >= MAX_LIGHTSTYLES ) )
      {
      assert( 0 );
      return;
      }

   styles[ index ] = style;
   gi.SetLightStyle( index, style.c_str() );
   }

void LightStyleClass::Archive( Archiver &arc )
   {
   int i;

   for( i = 0; i < MAX_LIGHTSTYLES; i++ )
      {
      arc.ArchiveString( &styles[ i ] );
      if ( arc.Loading() && styles[ i ].length() )
         {
         gi.SetLightStyle( i, styles[ i ].c_str() );
         }
      }
   }

