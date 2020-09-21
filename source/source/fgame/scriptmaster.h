//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/scriptmaster.h                     $
// $Revision:: 26                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/28/00 9:44p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/scriptmaster.h                          $
// 
// 26    7/28/00 9:44p Markd
// Added lightstyle repository code
// 
// 25    7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 24    7/23/00 6:03p Markd
// added fadeout and fadesound to dieing and level change
// 
// 23    7/07/00 6:36p Steven
// Added mission failed stuff.
// 
// 22    6/28/00 3:27p Steven
// Added level wide ai_on.
// 
// 21    6/16/00 5:14p Aldie
// Added locational printing (print anywhere on the screen)
// 
// 20    6/13/00 5:04p Markd
// fixed loadsave bug
// 
// 19    5/29/00 1:16p Markd
// 3rd round of saved games
// 
// 18    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 17    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 16    5/01/00 7:14p Markd
// Added centerprint command to scripts
// 
// 15    4/05/00 3:51p Markd
// added label checking for scripts
// 
// 14    3/16/00 4:13p Markd
// Added killthread ability
// 
// 13    3/04/00 11:48a Markd
// Added light style support
// 
// 12    1/29/00 10:29a Aldie
// Removed passtoplayer because $player is already there
// 
// 11    1/29/00 9:32a Markd
// Added setdialogscript functionality back in
// 
// 10    1/28/00 5:43p Markd
// Added script command to the game
// 
// 9     1/27/00 11:48a Aldie
// Added player command and takeweapon
// 
// 8     1/19/00 12:13p Steven
// Added a waitForDialog command.
// 
// 7     1/10/00 6:17p Jimdose
// more code cleanup
// 
// 6     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 5     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 4     11/03/99 4:32p Aldie
// Added letterboxing
// 
// 3     11/02/99 6:29p Aldie
// Added Fading
// 
// 2     10/28/99 6:33p Markd
// Added fakeplayer ability, also added CloneEntity
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 10    9/02/99 5:41p Markd
// made CacheResource utility functions changed code every where else
// 
// 9     8/28/99 3:34p Jimdose
// added isVarGroup
// 
// 8     8/25/99 12:42p Markd
// Fixed some minor and major scripting bugs
// 
// 7     7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
// 
// DESCRIPTION:
// Script masters are invisible entities that are spawned at the begining of each
// map.  They simple parse the script and send commands to the specified objects
// at the apropriate time.  Using a combination of simple commands, very complex
// scripted events can occur.
// 

#ifndef __SCRIPTMASTER_H__
#define __SCRIPTMASTER_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "gamescript.h"
#include "container.h"
#include "scriptvariable.h"
#include "worldspawn.h"

#define MAX_COMMANDS 20

typedef enum
	{
	LEVEL_SCRIPT,
	MODEL_SCRIPT,
   CONSOLE_SCRIPT
	} scripttype_t;

extern ScriptVariableList gameVars;
extern ScriptVariableList levelVars;
extern ScriptVariableList parmVars;

extern Event EV_ProcessCommands;
extern Event EV_ScriptThread_Execute;
extern Event EV_ScriptThread_Callback;
extern Event EV_ScriptThread_CreateThread;
extern Event EV_ScriptThread_TerminateThread;
extern Event EV_ScriptThread_ControlObject;
extern Event EV_ScriptThread_Goto;
extern Event EV_ScriptThread_Pause;
extern Event EV_ScriptThread_Wait;
extern Event EV_ScriptThread_WaitFor;
extern Event EV_ScriptThread_WaitForThread;
extern Event EV_ScriptThread_WaitForSound;
extern Event EV_ScriptThread_End;
extern Event EV_ScriptThread_Print;
extern Event EV_ScriptThread_PrintInt;
extern Event EV_ScriptThread_PrintFloat;
extern Event EV_ScriptThread_PrintVector;
extern Event EV_ScriptThread_NewLine;
extern Event EV_ScriptThread_Clear;
extern Event EV_ScriptThread_Assert;
extern Event EV_ScriptThread_Break;
extern Event EV_ScriptThread_Clear;
extern Event EV_ScriptThread_Trigger;
extern Event EV_ScriptThread_Spawn;
extern Event EV_ScriptThread_Map;
extern Event EV_ScriptThread_SetCvar;
extern Event EV_ScriptThread_CueCamera;
extern Event EV_ScriptThread_CuePlayer;
extern Event EV_ScriptThread_FreezePlayer;
extern Event EV_ScriptThread_ReleasePlayer;
extern Event EV_ScriptThread_SetCinematic;
extern Event EV_ScriptThread_SetNonCinematic;
extern Event EV_ScriptThread_SetSkipThread;
extern Event EV_ScriptThread_MissionFailed;

class ScriptThread;

typedef SafePtr<ScriptThread> ThreadPtr;

class ThreadMarker;

class ScriptThread : public Listener
	{
	protected:
		int						threadNum;
		str						threadName;

		scripttype_t			type;
		GameScript				script;
      Container<TargetList *> targets;

		int						linenumber;
		qboolean					doneProcessing;
		qboolean					threadDying;

		Container<int>			updateList;
		float						waitUntil;
		str						waitingFor;
		ScriptThread			*waitingForThread;
      str						waitingForVariable;
      str						waitingForDeath;
      qboolean             waitingForPlayer;
		int						waitingNumObjects;
		ScriptVariableList	localVars;

		void						ObjectMoveDone( Event *ev );
		void 						CreateThread( Event *ev );
		void 						TerminateThread( Event *ev );
		void 						ControlObject( Event *ev );
		void 						EventGoto( Event *ev );
		void 						EventPause( Event *ev );
		void 						EventWait( Event *ev );
		void 						EventWaitFor( Event *ev );
		void						EventWaitForThread( Event *ev );
      void						EventWaitForVariable( Event *ev );
      void						EventWaitForDeath( Event *ev );
      void						EventWaitForSound( Event *ev );
		void						EventWaitForDialog( Event *ev );
      void						EventWaitForPlayer( Event *ev );
		void 						EventEnd( Event *ev );
		void 						Print( Event *ev );
		void 						PrintInt( Event *ev );
		void 						PrintFloat( Event *ev );
		void 						PrintVector( Event *ev );
		void 						NewLine( Event *ev );
		void 						Assert( Event *ev );
		void 						Break( Event *ev );
		void 						Clear( Event *ev );
		void 						ScriptCallback( Event *ev );
		void 						ThreadCallback( Event *ev );
      void 						VariableCallback( Event *ev );
      void 						DeathCallback( Event *ev );
		void 						DoMove( void );
		void 						Execute( Event *ev );
		void						TriggerEvent( Event *ev );
		void						ServerEvent( Event *ev );
		void						ClientEvent( Event *ev );
      void                 CacheResourceEvent( Event *ev );
      void                 RegisterAlias( Event *ev );
      void                 RegisterAliasAndCache( Event *ev );
		void						MapEvent( Event *ev );
		void						SetCvarEvent( Event *ev );
      void                 SetThreadName( Event *ev );

      TargetList           *GetTargetList( str &targetname );

		void						CueCamera( Event *ev );
		void						CuePlayer( Event *ev );
		void						FreezePlayer( Event *ev );
		void						ReleasePlayer( Event *ev );
      void                 Spawn( Event *ev );
      void                 FadeIn( Event *ev	);
      void                 FadeOut( Event *ev );
      void                 FadeSound( Event *ev );
      void                 ClearFade( Event *ev );
      void                 Letterbox( Event *ev );
      void                 ClearLetterbox( Event *ev );
      void                 MusicEvent( Event *ev	);
      void                 ForceMusicEvent( Event *ev	);
		void						MusicVolumeEvent( Event *ev );
		void						RestoreMusicVolumeEvent( Event *ev );
      void                 SoundtrackEvent( Event *ev );
		void                 RestoreSoundtrackEvent( Event *ev );
		void						ScriptError( const char *fmt, ... );
		void						SetCinematic( Event *ev );
		void						SetNonCinematic( Event *ev );
		void						SetAllAIOff( Event *ev );
		void						SetAllAIOn( Event *ev );
		void						SetSkipThread( Event *ev );
      void                 PassToPathmanager( Event *ev );
      void                 StuffCommand( Event *ev );
		void		            KillEnt( Event *ev );
		void		            RemoveEnt( Event *ev );
		void		            KillClass( Event *ev );
		void		            RemoveClass( Event *ev );
      void                 CameraCommand( Event *ev );
      void                 FakePlayer( Event *ev );
      void                 RemoveFakePlayer( Event *ev );
      void                 SetDialogScript( Event *ev );
      void                 SetLightStyle( Event *ev );
      void                 KillThreadEvent( Event *ev );
      void                 CenterPrint( Event *ev );
      void                 LocationPrint( Event *ev );
		void                 MissionFailed( Event *ev );

	public:
      CLASS_PROTOTYPE( ScriptThread );

									ScriptThread();
									~ScriptThread();
		void						ClearWaitFor( void );
		void						SetType( scripttype_t newtype );
		scripttype_t			GetType( void );
		void						SetThreadNum( int num );
		int						ThreadNum( void );
		const char				*ThreadName( void );
		int						CurrentLine( void );
		const char				*Filename( void );
		qboolean					WaitingFor( Entity *obj );
		ScriptThread			*WaitingOnThread( void );
      const char				*WaitingOnVariable( void );
      const char				*WaitingOnDeath( void );
      qboolean             WaitingOnPlayer( void );
		ScriptVariableList	*Vars( void );
		qboolean					Setup( int num, GameScript *scr, const char *label );
		qboolean					SetScript( const char *name );
		qboolean					Goto( const char *name );
		qboolean					labelExists( const char *name );
		void                 Start( float delay );
		void                 StartImmediately( void );

		void						Mark( ThreadMarker *mark );
		void						Restore( ThreadMarker *mark );

		void						SendCommandToSlaves( const char *name, Event *ev );
		qboolean					FindEvent( const char *name );
		void						ProcessCommand( int argc, const char **argv );
		void						ProcessCommandFromEvent( Event *ev, int startarg );
      virtual void         Archive( Archiver &arc );
	};

inline void ScriptThread::Archive
	(
	Archiver &arc
	)

   {
   Listener::Archive( arc );

   arc.ArchiveInteger( &threadNum );
   arc.ArchiveString( &threadName );

   ArchiveEnum( type, scripttype_t );

   arc.ArchiveObject( &script );

   // targets
   // don't need to save out targets
   if ( arc.Loading() )
      {
      targets.ClearObjectList();
      }

   arc.ArchiveInteger( &linenumber );
   arc.ArchiveBoolean( &doneProcessing );
   arc.ArchiveBoolean( &threadDying );

   // updateList
   // don't need to save out updatelist
   if ( arc.Loading() )
      {
      updateList.ClearObjectList();
      }

   arc.ArchiveFloat( &waitUntil );
   arc.ArchiveString( &waitingFor );
   arc.ArchiveObjectPointer( ( Class ** )&waitingForThread );
   arc.ArchiveString( &waitingForVariable );
   arc.ArchiveString( &waitingForDeath );
   arc.ArchiveBoolean( &waitingForPlayer );
   arc.ArchiveInteger( &waitingNumObjects );
   arc.ArchiveObject( &localVars );
   }

class ThreadMarker : public Class
	{
	public:
      CLASS_PROTOTYPE( ThreadMarker );

		int						linenumber;
		qboolean					doneProcessing;
		float						waitUntil;
		str						waitingFor;
		ScriptThread			*waitingForThread;
      str						waitingForVariable;
      str						waitingForDeath;
      qboolean             waitingForPlayer;
		int						waitingNumObjects;
		GameScriptMarker		scriptmarker;
      virtual void         Archive( Archiver &arc );
	};

inline void ThreadMarker::Archive
	(
	Archiver &arc
	)
   {
   Class::Archive( arc );

   arc.ArchiveInteger( &linenumber );
   arc.ArchiveBoolean( &doneProcessing );
   arc.ArchiveFloat( &waitUntil );
   arc.ArchiveString( &waitingFor );
   arc.ArchiveObjectPointer( ( Class ** )&waitingForThread );
   arc.ArchiveString( &waitingForVariable );
   arc.ArchiveString( &waitingForDeath );
   arc.ArchiveBoolean( &waitingForPlayer );
   arc.ArchiveInteger( &waitingNumObjects );
   arc.ArchiveObject( &scriptmarker );
   }


class ScriptMaster : public Listener
	{
	protected:
		ScriptThread					*currentThread;
		Container<ScriptThread *>	Threads;

		int								threadIndex;
      qboolean                   player_ready;

	public:
      CLASS_PROTOTYPE( ScriptMaster );

											ScriptMaster();
											~ScriptMaster();
		void								CloseScript( void );
		qboolean							NotifyOtherThreads( int num );
		void								KillThreads( void );
		void								KillThread( str name );
		qboolean							KillThread( int num );
		qboolean							RemoveThread( int num );
		ScriptThread					*CurrentThread( void );
		void								SetCurrentThread( ScriptThread *thread );
      ScriptThread               *CreateThread( GameScript *scr, const char *label, scripttype_t type = LEVEL_SCRIPT );
		ScriptThread					*CreateThread( const char *name, scripttype_t type, const char *label = NULL );
		ScriptThread					*CreateThread( scripttype_t type );
		ScriptThread					*GetThread( int num );
      bool                       isVarGroup( const char *name );
		ScriptVariableList			*GetVarGroup( const char *name );
		ScriptVariable					*GetExistingVariable( const char *name );
		ScriptVariable					*GetVariable( const char *name );
      void                       DeathMessage( const char *name );
      void                       PlayerSpawned( void );
      qboolean                   PlayerReady( void );
      void                       PlayerNotReady( void );
      qboolean                   Goto( GameScript * scr, const char *name );
      qboolean                   labelExists( GameScript * scr, const char *name );
      qboolean                   labelExists( const char *filename, const char *name );
      int                        GetUniqueThreadNumber( void );
      void                       FindLabels( void );
      virtual void               Archive( Archiver &arc );
      
	};

inline void ScriptMaster::Archive
	(
	Archiver &arc
	)
   {
   ScriptThread * ptr;
   int i, num;

   Listener::Archive( arc );

   arc.ArchiveObject( &levelVars );

   arc.ArchiveObjectPointer( ( Class ** )&currentThread );
   arc.ArchiveInteger( &threadIndex );
   arc.ArchiveBoolean( &player_ready );
   if ( arc.Saving() )
      {
      int skip;

      skip = 0;
      num = Threads.NumObjects();
      // find all the console threads
      for ( i = 1; i <= num; i++ )
         {
         ptr = Threads.ObjectAt( i );
         if ( ptr->GetType() == CONSOLE_SCRIPT )
            {
            skip++;
            }
         }
      skip = num - skip;
      arc.ArchiveInteger( &skip );
      }
   else
      {
      Threads.FreeObjectList();
      arc.ArchiveInteger( &num );
      }
   for ( i = 1; i <= num; i++ )
      {
      if ( arc.Loading() )
         {
         ptr = new ScriptThread;
         Threads.AddObject( ptr );
         }
      else
         {
         ptr = Threads.ObjectAt( i );
         // skip over console script threads
         if ( ptr->GetType() == CONSOLE_SCRIPT )
            {
            continue;
            }
         }
      arc.ArchiveObject( ptr );
      }
   }

inline qboolean ScriptMaster::PlayerReady
	(
   void
	)
   {
   return player_ready;
   }

inline void ScriptMaster::PlayerNotReady
	(
   void
	)
   {
   player_ready = false;
   }

extern ScriptMaster Director;

class LightStyleClass : public Class
	{
	private:
      CLASS_PROTOTYPE( LightStyleClass );

		str            styles[ MAX_LIGHTSTYLES ];

	public:

   void              SetLightStyle( int index, str style );
   void              Archive( Archiver &arc );
   };

extern LightStyleClass lightStyles;

#endif /* scriptmaster.h */
