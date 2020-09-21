//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/g_main.cpp                         $
// $Revision:: 89                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 8/08/00 8:34p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/g_main.cpp                              $
// 
// 89    8/08/00 8:34p Markd
// increased error messages to handle 4k instead of 1024
// 
// 88    7/31/00 1:32a Markd
// added some debugging information
// 
// 87    7/29/00 3:13p Markd
// made sure pointers were valid in G_ClientUserinfoChanged
// 
// 86    7/28/00 10:07p Markd
// Added archive lightStyles
// 
// 85    7/27/00 11:43p Aldie
// Removed statement I accidentally added
// 
// 84    7/27/00 10:54p Steven
// Bumped up savegame version.
// 
// 83    7/27/00 9:43p Aldie
// Changed dialog for invalid save games
// 
// 82    7/27/00 3:03p Markd
// return false on LevelArchiveValid if file doesn't exist
// 
// 81    7/27/00 2:05a Markd
// increased savegame_version 
// 
// 80    7/25/00 9:25p Steven
// Bumped up savegame version.
// 
// 79    7/23/00 6:03p Markd
// added fadeout and fadesound to dieing and level change
// 
// 78    7/22/00 1:18p Steven
// Bumped up savegame version.
// 
// 77    7/19/00 9:20p Steven
// Made the proc Loaded get called for each player after everything has been
// loaded so that some things can be set up correctly.
// 
// 76    7/18/00 4:26p Steven
// Bumped up savegame version.
// 
// 75    7/17/00 12:36a Markd
// Made sure to close the log file when exiting a level or shutting down a
// server
// 
// 74    7/16/00 10:47a Steven
// Bumped up savegame version.
// 
// 73    7/15/00 12:49p Steven
// Bumped up savegame version.
// 
// 72    7/13/00 8:47p Markd
// reset savegame version and persistant version
// 
// 71    7/13/00 3:44p Steven
// Bumped up savegame version.
// 
// 70    7/12/00 11:38a Steven
// Bumped up savegame and persistant version.
// 
// 69    7/11/00 8:02a Steven
// In G_ClientDisconnect made sure to check that ent is not NULL.
// 
// 68    7/10/00 6:34p Aldie
// Added SVF_SENDONCE flag
// 
// 67    7/10/00 6:26p Steven
// Bumped up savegame version.
// 
// 66    7/09/00 1:43p Markd
// Changed center print for game saved
// 
// 65    7/07/00 6:36p Steven
// Bumped up savegame version.
// 
// 64    7/06/00 7:48p Markd
// Added LevelArchiveValid function
// 
// 63    7/06/00 1:25p Steven
// Bimped savegame version.
// 
// 62    7/05/00 9:55p Markd
// Increased savegame and persistant version
// 
// 61    7/05/00 7:35p Steven
// Bumped the PERSISTANT_VERSION up.
// 
// 60    7/05/00 6:15p Steven
// Bumped up savegame version.
// 
// 59    7/01/00 6:07p Steven
// Bumped savegame version.
// 
// 58    6/27/00 5:48p Steven
// Bumped savegame version.
// 
// 57    6/23/00 8:27p Markd
// increased save game version
// 
// 56    6/23/00 11:49a Markd
// fixed various imagindexes and saved games
// 
// 55    6/23/00 10:47a Markd
// fixed loading of out of date savegame files
// 
// 54    6/22/00 3:45p Markd
// bumped savegame version
// 
// 53    6/20/00 7:01p Steven
// Bumped savegame version.
// 
// 52    6/19/00 4:13p Markd
// fixed load/save bug with targetnames
// 
// 51    6/17/00 11:57a Steven
// Bumped up the savegame version.
// 
// 50    6/15/00 8:04p Markd
// Added CleanupGame
// 
// 49    6/13/00 3:57p Markd
// Added centerprint message when saving the game
// 
// 48    6/13/00 3:44p Steven
// Added alias saving stuff.
// 
// 47    6/10/00 4:23p Markd
// rewrote map restarting and loading out of date save games
// 
// 46    6/02/00 4:43p Markd
// changed Persistant data to use separate persistant version number instead of
// GAME_API_VERSION number
// 
// 45    6/02/00 4:24p Markd
// cleaned up archive functions
// 
// 44    6/02/00 2:01p Markd
// Fixed client persistant data issues
// 
// 43    5/31/00 3:50p Markd
// fixed precaching issue
// 
// 42    5/30/00 7:06p Markd
// saved games 4th pass
// 
// 41    5/29/00 1:16p Markd
// 3rd round of saved games
// 
// 40    5/26/00 2:24p Aldie
// Added waitforplayer commands so we can use it for cinematics when waiting
// for player to finish holstering
// 
// 39    5/25/00 4:28p Markd
// fixed up archive functions
// 
// 38    5/16/00 4:11p Markd
// fixed precision on total number of traces
// 
// 37    2/26/00 12:58p Jimdose
// added level.restart
// 
// 36    2/16/00 6:55p Markd
// increment time at the end of a frame so that player stuff will work properly
// 
// 35    2/01/00 4:11p Markd
// Added Frame bounding box support
// 
// 34    1/25/00 6:06p Markd
// Put in fix for player movement
// 
// 33    1/25/00 4:43p Markd
// cleaned up main routine so that level.settime would be used properly
// 
// 32    1/19/00 4:20p Aldie
// Fix for level.fixedframetime
// 
// 31    1/15/00 1:39p Markd
// Fixed old command in G_ExitLevel
// 
// 30    1/13/00 5:19p Jimdose
// removed clearsavegames
// 
// 29    1/10/00 5:27p Markd
// Added DeAllocGameData
// 
// 28    1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 27    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 26    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 25    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 24    12/10/99 11:52a Aldie
// Adjusted player angles a bit
// 
// 23    12/09/99 3:32p Aldie
// Removed a line where player origin was being multiplied by 0.125
// 
// 22    12/01/99 11:26a Aldie
// Couple of fixes for emitters and more ammo stuff
// 
// 21    11/12/99 11:47a Markd
// Added sound manager support and retro-fitted TriggerSpeaker and TriggerMusic
// to work with everything
// 
// 20    11/04/99 10:03a Markd
// complete overhaul of the camera system
// 
// 19    10/27/99 12:19p Markd
// added smooth camera lerping
// 
// 18    10/26/99 5:27p Aldie
// Fix for gravpaths
// 
// 17    10/25/99 6:39p Markd
// removed size and other unused variables, added radius and centroid to both
// server and game code
// 
// 16    10/12/99 2:23p Markd
// Rewrote camera and player movetype system
// 
// 15    10/06/99 3:09p Steven
// Added dumpevents command.
// 
// 14    10/05/99 5:03p Markd
// Removed un-used game function ClientPredict
// 
// 13    10/02/99 6:51p Markd
// Put in backend work for event documentation and fixed a lot of event
// documentation bugs
// 
// 12    10/01/99 6:31p Markd
// added commands hidden inside fgame so that they would show up for command
// completion
// 
// 11    9/29/99 11:52a Markd
// removed some unused enums and variables form shared headers between cgame
// and fgame
// 
// 10    9/28/99 4:26p Markd
// merged listener, class and vector between 3 projects
// 
// 9     9/22/99 4:47p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 8     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 7     9/16/99 4:48p Jimdose
// removed unused code and variables
// rewrote G_ClientConnect for merge
// 
// 6     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 5     9/15/99 6:57p Aldie
// Update to get game working
// 
// 4     9/13/99 4:22p Jimdose
// merge
// 
// 3     9/13/99 3:30p Jimdose
// merge
// 
// 2     9/10/99 5:45p Jimdose
// merge
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 29    8/28/99 3:23p Markd
// got rid of bulletholes and blood splats
// 
// 28    8/27/99 8:25p Markd
// added pengingevents and fixed some event holes
// 
// 27    8/19/99 6:18p Markd
// took out con_clearfade stuff from g_main, to be replaced later on with
// proper level restarting
// 
// 26    7/07/99 11:25a Steven
// Added some stuff on the sector pathfinding approach.
// 
// 25    6/23/99 3:57p Markd
// Added viewthing support
//
// DESCRIPTION:
//

#define SAVEGAME_VERSION 8
#define PERSISTANT_VERSION 1

#include "g_local.h"
#include "g_utils.h"
#include "gamecmds.h"
#include "Entity.h"
#include "vector.h"
#include "scriptmaster.h"
#include "navigate.h"
#include "player.h"
#include "gravpath.h"
#include "camera.h"
#include "level.h"
#include "viewthing.h"
#include "ipfilter.h"
#include "../qcommon/alias.h"

Vector         vec_origin = "0 0 0";
Vector         vec_zero = "0 0 0";

qboolean       LoadingSavegame = false;
qboolean       LoadingServer = false;
game_import_t	gi;
game_export_t	globals;

gentity_t      *g_entities = NULL;
gentity_t      active_edicts;
gentity_t      free_edicts;

int		      sv_numtraces;

usercmd_t      *current_ucmd;

void		      ( *ServerError )( int level, const char *fmt, ... );

/*
===============
G_Error

Abort the server with a game error
===============
*/
void G_Error
	(
   int level,
	const char *fmt,
	...
	)

	{
	va_list	argptr;
   char		error[ 4096 ];

	va_start( argptr, fmt );
	vsprintf( error, fmt, argptr );
	va_end( argptr );

   assert( 0 );

   throw error;
	}

/*
===============
G_ExitWithError

Calls the server's error function with the last error that occurred.
Should only be called after an exception.
===============
*/
void G_ExitWithError
	(
	const char *error
	)

	{
   static char G_ErrorMessage[ 4096 ];
	
   //ServerError( ERR_DROP, error );
   
   Q_strncpyz( G_ErrorMessage, error, sizeof( G_ErrorMessage ) );

   globals.error_message = G_ErrorMessage;
	}

/*
=================
G_CleanupGame

Frees up resources from current level
=================
*/
void G_CleanupGame
	(
	void
	)

	{
   try
      {
      gi.DPrintf ("==== CleanupGame ====\n");

      level.CleanUp();
		}

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
	}

/*
=================
G_ShutdownGame

Frees up any resources
=================
*/
void G_ShutdownGame
	(
	void
	)

	{
   try
      {
      gi.DPrintf ("==== ShutdownGame ====\n");

      // close the player log file if necessary
      ClosePlayerLogFile();

      level.CleanUp();

      L_ShutdownEvents();
   
      // destroy the game data
	   G_DeAllocGameData();
		}

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
	}

/*
============
G_InitGame

This will be called when the dll is first loaded, which
only happens when a new game is begun
============
*/
void G_InitGame
   (
   int startTime,
   int randomSeed
   )

	{
   gi.DPrintf ("==== InitGame ====\n");

	// Install our own error handler, since we can't
	// call the EXE's handler from within a C++ class
	ServerError = gi.Error;
	gi.Error    = G_Error;

	// If we get an error, call the server's error function
   try
      {
	   srand( randomSeed );

      // setup all the cvars the game needs
      CVAR_Init();

	   // initialize the game variables
	   gameVars.ClearList();

      level.fixedframetime = ( 1.0f / sv_fps->value );
	   level.startTime = startTime;

      G_InitConsoleCommands();
	   L_InitEvents();

      sv_numtraces = 0;

      // setup ViewMaster
      Viewmodel.Init();

      game.maxentities = maxentities->integer;
      if (maxclients->integer * 8 > game.maxentities)
		   {
         game.maxentities = maxclients->integer * 8;
		   }
      game.maxclients = maxclients->integer;

      G_AllocGameData();
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
   }

void G_AllocGameData
   (
   void
   )

   {
   int i;

   // de-allocate from previous level
   G_DeAllocGameData();

   // Initialize debug lines
	G_AllocDebugLines();

	// initialize all entities for this game
   game.maxentities     = maxentities->integer;
	g_entities           = ( gentity_t * )gi.Malloc (game.maxentities * sizeof(g_entities[0]) );

   // clear out the entities
   memset( g_entities, 0, sizeof( g_entities[ 0 ] ) * game.maxentities );
	globals.gentities    = g_entities;
	globals.max_entities = game.maxentities;

	// Add all the edicts to the free list
	LL_Reset( &free_edicts, next, prev );
	LL_Reset( &active_edicts, next, prev );
	for( i = 0; i < game.maxentities; i++ )
		{
      LL_Add( &free_edicts, &g_entities[ i ], next, prev );
		}

	// initialize all clients for this game
	game.clients = ( gclient_t * )gi.Malloc( game.maxclients * sizeof( game.clients[ 0 ] ) );
	memset( game.clients, 0, game.maxclients * sizeof( game.clients[ 0 ] ) );
	for( i = 0; i < game.maxclients; i++ )
		{
     	// set client fields on player ents
      g_entities[ i ].client = game.clients + i;

		G_InitClientPersistant (&game.clients[i]);
		}
   globals.num_entities = game.maxclients;

   // Tell the server about our data
   gi.LocateGameData( g_entities, globals.num_entities, sizeof( gentity_t ), &game.clients[0].ps, sizeof( game.clients[0] ) );
   }

void G_DeAllocGameData
   (
   void
   )

   {
   // Initialize debug lines
	G_DeAllocDebugLines();

	// free up the entities
   if ( g_entities )
      {
	   gi.Free( g_entities );
      g_entities = NULL;
      }

   // free up the clients
   if ( game.clients )
      {
      gi.Free( game.clients );
      game.clients = NULL;
      }
   }

void G_SpawnEntities
	(
	const char *mapname,
	const char *entities,
   int         levelTime
	)

	{
   try
      {
      level.NewMap( mapname, entities, levelTime );
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
   }

void G_ArchivePersistantData
   (
	Archiver &arc
   )
   {
   gentity_t   *ed;
   int         i;

 	for( i = 0; i < game.maxclients; i++ )
      {
      Entity   *ent;

      ed = &g_entities[ i ];
		if ( !ed->inuse || !ed->entity )
			continue;

  		ent = ed->entity;
      if ( !ent->isSubclassOf( Player ) )
         continue;
      ( ( Player * )ent )->ArchivePersistantData( arc );
      }
   }

qboolean G_ArchivePersistant
   (
   const char *name,
   qboolean loading
   )

	{
   int version;
   Archiver arc;

   if ( loading )
      {
	   if ( !arc.Read( name, qfalse ) )
         {
         return qfalse;
         }

      arc.ArchiveInteger( &version );
      if ( version < PERSISTANT_VERSION )
         {
         gi.Printf( "Persistant data from an older version (%d) of FAKK2.\n", version );
   	   arc.Close();
         return qfalse;
         }
      else if ( version > PERSISTANT_VERSION )
         {
         gi.DPrintf( "Persistnat data from newer version %d of FAKK2.\n", version );
   	   arc.Close();
         return qfalse;
         }
      }
   else
      {
      arc.Create( name );

      version = PERSISTANT_VERSION;
      arc.ArchiveInteger( &version );
      }


   arc.ArchiveObject( &gameVars );
   G_ArchivePersistantData( arc );

	arc.Close();
   return qtrue;
   }


qboolean G_ReadPersistant
   (
   const char *name
   )

	{
   try
      {
      return G_ArchivePersistant( name, qtrue );
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
   return qfalse;
   }

/*
============
G_WritePersistant

This will be called whenever the game goes to a new level,

A single player death will automatically restore from the
last save position.
============
*/

void G_WritePersistant
   (
   const char *name
   )

	{
   try
      {
      G_ArchivePersistant( name, qfalse );
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
   }


/*
=================
LevelArchiveValid
=================
*/
qboolean LevelArchiveValid
   ( 
	Archiver &arc
   )
	{
   int      version;
   int      savegame_version;

   // read the version number
   arc.ArchiveInteger( &version );
   arc.ArchiveInteger( &savegame_version );

   if ( version < GAME_API_VERSION )
      {
      gi.Printf( "Savegame from an older version (%d) of FAKK 2.\n", version );
      return qfalse;
      }
   else if ( version > GAME_API_VERSION )
      {
      gi.Printf( "Savegame from version %d of FAKK 2.\n", version );
      return qfalse;
      }

   if ( savegame_version < SAVEGAME_VERSION )
      {
      gi.Printf( "Savegame from an older version (%d) of FAKK 2.\n", version );
      return qfalse;
      }
   else if ( savegame_version > SAVEGAME_VERSION )
      {
      gi.Printf( "Savegame from version %d of Sin.\n", version );
      return qfalse;
      }
   return qtrue;
   }


void ArchiveAliases
	(
	Archiver &arc
	)

	{
	int i;
	byte another;
	AliasList_t *alias_list;
	AliasListNode_t *alias_node;
	AliasActorNode_t *actor_node;
	str alias_name;
	str model_name;
	const char *name;
	int model_index;
	int actor_number;
	int number_of_times_played;
	byte been_played_this_loop;
	int last_time_played;


	if ( arc.Saving() )
		{
		for( i = 0 ; i < MAX_MODELS ; i++ )
			{
			alias_list = (AliasList_t *)gi.Alias_GetList( i );

			if ( alias_list )
				alias_node = alias_list->data_list;
			else
				alias_node = NULL;

			if ( alias_node )
				{
				name = gi.NameForNum( i );

				if ( name )
					{
					another = true;
					arc.ArchiveByte( &another );

					model_name = name;
					arc.ArchiveString( &model_name );

					// Go through all aliases in this model

					while ( alias_node )
						{
						another = true;
						arc.ArchiveByte( &another );

						alias_name = alias_node->alias_name;

						arc.ArchiveString( &alias_name );

						arc.ArchiveInteger( &alias_node->number_of_times_played );
						arc.ArchiveByte( &alias_node->been_played_this_loop );
						arc.ArchiveInteger( &alias_node->last_time_played );

						actor_node = alias_node->actor_list;
				
						// Go through actor info

						while ( actor_node )
							{
							another = true;
							arc.ArchiveByte( &another );

							arc.ArchiveInteger( &actor_node->actor_number );
							arc.ArchiveInteger( &actor_node->number_of_times_played );
							arc.ArchiveByte( &actor_node->been_played_this_loop );
							arc.ArchiveInteger( &actor_node->last_time_played );

							actor_node = actor_node->next;
							}

						another = false;
						arc.ArchiveByte( &another );

						alias_node = alias_node->next;
						}

					another = false;
					arc.ArchiveByte( &another );
					}
				}
			}

		another = false;
		arc.ArchiveByte( &another );
		}
	else
		{
		arc.ArchiveByte( &another );

		while( another )
			{
			arc.ArchiveString( &model_name );

			model_index = gi.modelindex( model_name.c_str() );

			arc.ArchiveByte( &another );

			while( another )
				{
				// Read in aliases

				arc.ArchiveString( &alias_name );
				arc.ArchiveInteger( &number_of_times_played );
				arc.ArchiveByte( &been_played_this_loop );
				arc.ArchiveInteger( &last_time_played );

				gi.Alias_UpdateDialog( model_index, alias_name.c_str(), number_of_times_played, been_played_this_loop, last_time_played );

				arc.ArchiveByte( &another );

				while( another )
					{
					// Read in actor infos

					arc.ArchiveInteger( &actor_number );
					arc.ArchiveInteger( &number_of_times_played );
					arc.ArchiveByte( &been_played_this_loop );
					arc.ArchiveInteger( &last_time_played );

					gi.Alias_AddActorDialog( model_index, alias_name.c_str(), actor_number, number_of_times_played, been_played_this_loop, last_time_played );

					arc.ArchiveByte( &another );
					}

				arc.ArchiveByte( &another );
				}

			arc.ArchiveByte( &another );
			}
		}
	}
	

/*
=================
G_ArchiveLevel

=================
*/
qboolean G_ArchiveLevel
   (
   const char *filename,
   qboolean autosave,
   qboolean loading
   )

	{
   try
      {
	   int		i;
      int      num;
      Archiver arc;
      gentity_t  *edict;


      if ( loading )
         {
         LoadingSavegame = true;
         LoadingServer = true;

         // Get rid of anything left over from the last level
         level.CleanUp();

	      arc.Read( filename );

         if ( !LevelArchiveValid( arc ) )
            {
            arc.Close();
            return qfalse;
            }

         // Read in the pending events.  These are read in first in case
         // later objects need to post events.
         L_UnarchiveEvents( arc );
         }
      else
         {
         int temp;

         if ( autosave )
            {
	         for( i = 0; i < game.maxclients; i++ )
   	         {
               edict = &g_entities[ i ];
		         if ( !edict->inuse && !edict->entity )
                  {
			         continue;
                  }

               delete edict->entity;
	            }
            }

         arc.Create( filename );

         // write out the version number
         temp = GAME_API_VERSION;
         arc.ArchiveInteger( &temp );
         temp = SAVEGAME_VERSION;
         arc.ArchiveInteger( &temp );

         // Write out the pending events.  These are written first in case
         // later objects need to post events when reading the archive.
         L_ArchiveEvents( arc );
         }
      // archive the game object
      arc.ArchiveObject( &game );

      // archive the game variables
      arc.ArchiveObject( &gameVars );

	   // archive Level
      arc.ArchiveObject( &level );

      if ( arc.Loading() )
         {
         // Set up for a new map
	      PathManager.Init( level.mapname.c_str() );
         }

      // archive script librarian
      arc.ArchiveObject( &ScriptLib );

      // archive gravity paths
      arc.ArchiveObject( &gravPathManager );

      // archive camera paths
      arc.ArchiveObject( &CameraMan );

      // archive paths
      arc.ArchiveObject( &PathManager );

      // archive script controller
      arc.ArchiveObject( &Director );

      // archive lightstyles
      arc.ArchiveObject( &lightStyles );

      if ( arc.Saving() )
         {
	      // count the entities
         num = 0;
         for( i = 0; i < globals.num_entities; i++ )
	         {
            edict = &g_entities[ i ];
		      if ( edict->inuse && edict->entity && !( edict->entity->flags & FL_DONTSAVE ) )
               {
			      num++;
               }
            }
         }

	   // archive all the entities
      arc.ArchiveInteger( &globals.num_entities );
      arc.ArchiveInteger( &num );

      if ( arc.Saving() )
         {
         // write out the world
         arc.ArchiveObject( world );

         for( i = 0; i < globals.num_entities; i++ )
	         {
            edict = &g_entities[ i ];
		      if ( !edict->inuse || !edict->entity || ( edict->entity->flags & FL_DONTSAVE ) )
               {
			      continue;
               }

            arc.ArchiveObject( edict->entity );
	         }
         }
      else
         {
         // Tell the server about our data
         gi.LocateGameData( g_entities, globals.num_entities, sizeof( gentity_t ), &game.clients[0].ps, sizeof( game.clients[0] ) );

         // read in the world
         arc.ReadObject();

	      for( i = 0; i < num; i++ )
	         {
            arc.ReadObject();
	         }
         }

		ArchiveAliases( arc );

      arc.Close();

      if ( arc.Loading() )
         {
         LoadingSavegame = false;

         // call the precache scripts
         level.Precache();
         }
      else
         {
         gi.centerprintf( &g_entities[ 0 ], "@textures/menu/gamesaved" );
         }

		if ( arc.Loading() )
			{
			// Make sure all code that needs to setup the player after they have been loaded is run

			for( i = 0; i < game.maxclients; i++ )
   			{
				edict = &g_entities[ i ];

				if ( edict->inuse && edict->entity )
					{
					Player *player = (Player *)edict->entity;
					player->Loaded();	
					}
				}
			}

      return qtrue;
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
   return qfalse;
   }

/*
=================
G_WriteLevel

=================
*/
void G_WriteLevel
   (
   const char *filename,
   qboolean autosave
   )

	{
   game.autosaved = autosave;
   G_ArchiveLevel( filename, autosave, qfalse );
   game.autosaved = false;
   }

/*
=================
G_ReadLevel

SpawnEntities will already have been called on the
level the same way it was when the level was saved.

That is necessary to get the baselines set up identically.

The server will have cleared all of the world links before
calling ReadLevel.

No clients are connected yet.
=================
*/
qboolean G_ReadLevel
   (
   const char *filename
   )

   {
   qboolean status;

   status = G_ArchiveLevel( filename, qfalse, qtrue );
   // if the level load failed make sure that these variables are not set
   if ( !status )
      {
      LoadingSavegame = false;
      LoadingServer = false;
      }
   return status;
   }

/*
=================
G_LevelArchiveValid
=================
*/
qboolean G_LevelArchiveValid
   ( 
   const char *filename 
   )
	{
   try
      {
      qboolean ret;

      Archiver arc;

      if ( !arc.Read( filename ) )
         {
         return qfalse;
         }

      ret = LevelArchiveValid( arc );

      arc.Close();

      return ret;
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      return qfalse;
      }
   }


/*
=================
GetGameAPI

Returns a pointer to the structure with all entry points
and global variables
=================
*/
game_export_t *GetGameAPI
   (
   game_import_t *import
   )

	{
	gi = *import;

	globals.apiversion				= GAME_API_VERSION;
	globals.Init						= G_InitGame;
	globals.Shutdown					= G_ShutdownGame;
	globals.Cleanup					= G_CleanupGame;
	globals.SpawnEntities			= G_SpawnEntities;

	globals.WritePersistant			= G_WritePersistant;
	globals.ReadPersistant			= G_ReadPersistant;
	globals.WriteLevel				= G_WriteLevel;
	globals.ReadLevel					= G_ReadLevel;
	globals.LevelArchiveValid		= G_LevelArchiveValid;

	globals.ClientThink				= G_ClientThink;
	globals.ClientConnect			= G_ClientConnect;
	globals.ClientUserinfoChanged = G_ClientUserinfoChanged;
	globals.ClientDisconnect		= G_ClientDisconnect;
	globals.ClientBegin				= G_ClientBegin;
	globals.ClientCommand			= G_ClientCommand;

   globals.ConsoleCommand        = G_ConsoleCommand;
	globals.RunFrame					= G_RunFrame;

   globals.gentitySize           = sizeof(gentity_t);
   globals.error_message         = NULL;

	return &globals;
	}

/*
=================
G_ClientEndServerFrames
=================
*/
void G_ClientEndServerFrames
	(
	void
	)

	{
	int		i;
   gentity_t  *ent;

	// calc the player views now that all pushing
	// and damage has been added
   for( i = 0; i < maxclients->integer; i++ )
		{
      ent = g_entities + i;
		if ( !ent->inuse || !ent->client || !ent->entity )
			{
			continue;
			}

		ent->entity->ProcessEvent( EV_ClientEndFrame );
		}
	}

void G_MoveClientToIntermission
   (
   Entity *ent
   )

   {
   }

void G_BeginIntermission
	(
	const char *map
	)

	{
   gentity_t   *client;
   Entity      *ent;
   Entity      *path;
   int         i;
   Event       *event;

	assert( map );
   if ( !map )
      {
      gi.DPrintf( "G_BeginIntermission : Null map name\n" );
      return;
      }

	if ( level.intermissiontime )
		{
		// already activated
		return;
		}

   if ( deathmatch->integer )
      {
	   level.intermissiontime = level.time + 5.0f;
      }
   else
      {
	   level.intermissiontime = level.time + 1.0f;
      G_FadeOut( 1 );
      G_FadeSound( 1 );
      }

   level.nextmap = map;

   // find an intermission spot
   ent = G_FindClass( NULL, "info_player_intermission" );

   // Only do the camera stuff if the node exists.
   if ( ent )
      {
	   SetCamera( ent, CAMERA_SWITCHTIME );
      event = new Event( EV_Camera_Orbit );

      // Find the end node
      path = G_FindTarget( NULL, "endnode1" );
      if ( path )
         {
         event->AddEntity( path );
         ent->ProcessEvent( event );
         event = new Event( EV_Camera_Cut );
         ent->ProcessEvent( event );
         }
      }

   // Display scores for all the clients
   for( i = 0; i < maxclients->integer; i++ )
      {
      client = g_entities + i;
      if ( !client->inuse )
         {
			continue;
         }

      ent = G_GetEntity( client->s.number );
      G_MoveClientToIntermission( ent );
      }

   // tell the script that the player's not ready so that if we return to this map,
   // we can do something about it.
   Director.PlayerNotReady();
	}

/*
=============
G_ExitLevel
=============
*/
void G_ExitLevel
   (
   void
   )

	{
	char command[ 256 ];
   int j;
   gentity_t *ent;

   // close the player log file if necessary
   ClosePlayerLogFile();

   // kill the sounds
	Com_sprintf( command, sizeof( command ), "stopsound\n" );
	gi.SendConsoleCommand( command );

	Com_sprintf( command, sizeof( command ), "gamemap \"%s\"\n", level.nextmap.c_str() );
	gi.SendConsoleCommand( command );

	level.nextmap = "";

	level.exitintermission = 0;
	level.intermissiontime = 0;

   // Tell all the client that the level is done
	for( j = 0; j < game.maxclients; j++ )
		{
      ent = &g_entities[ j ];
		if ( !ent->inuse || !ent->entity )
			{
			continue;
			}

      ent->entity->ProcessEvent( EV_Player_EndLevel );
      }

	G_ClientEndServerFrames();

   // tell the script that the player's not ready so that if we return to this map,
   // we can do something about it.
   Director.PlayerNotReady();
	}

/*
================
G_RunFrame

Advances the world by 0.1 seconds
================
*/
void G_RunFrame
   (
   int levelTime,
   int frameTime
   )

   {
   gentity_t  *edict;
	Entity	*ent;
   int		num;
	qboolean showentnums;
   int      start;
   int      end;

   try
      {
      if ( level.restart )
         {
         level.Restart();
         }
#if 0
      {
      int i, num;

      num = 0;
      edict = g_entities;
      for ( i = maxclients->integer; i < globals.num_entities; i++, edict++ )
		   {
		   // the first couple seconds of server time can involve a lot of
		   // freeing and allocating, so relax the replacement policy
		   if ( 
               edict->inuse 
            )
			   {
            num++;
            }
         }

      Com_Printf( "num_entities = %d\n", num );
      }
#endif

      level.setTime( levelTime, frameTime );

      if ( g_showmem->integer )
         {
         DisplayMemoryUsage();
         }

	   // exit intermissions
	   if ( level.exitintermission )
		   {
		   G_ExitLevel();
		   return;
		   }

	   path_checksthisframe = 0;

	   // Reset debug lines
	   G_InitDebugLines();

	   // testing coordinate system
      if ( csys_draw->integer )
		   {
		   G_DrawCSystem();
		   }

	   PathManager.ShowNodes();

	   // don't show entnums during deathmatch
      showentnums = ( sv_showentnums->integer && ( !deathmatch->integer || sv_cheats->integer ) );

      // Wake up any monsters in the area
      AI_TargetPlayer();

	   // Process most of the events before the physics are run
	   // so that we can affect the physics immediately
	   L_ProcessPendingEvents();

	   //
	   // treat each object in turn
	   //
	   for( edict = active_edicts.next, num = 0; edict != &active_edicts; edict = level.next_edict, num++ )
		   {
		   assert( edict );
		   assert( edict->inuse );
		   assert( edict->entity );

		   level.next_edict = edict->next;

		   // Paranoia - It's a way of life
         assert( num <= MAX_GENTITIES );
         if ( num > MAX_GENTITIES )
            {
            gi.DPrintf( "Possible infinite loop in G_RunFrame.\n");
            break;
            }

		   ent = edict->entity;
         if ( g_timeents->integer )
            {
            start = gi.Milliseconds();
		      G_RunEntity( ent );
            end = gi.Milliseconds();

            if ( g_timeents->value <= ( end - start ) )
               {
               gi.DebugPrintf( "%d: '%s'(%d) : %d\n", level.framenum, ent->targetname.c_str(), ent->entnum, end - start );
               }
            }
         else
            {
		      G_RunEntity( ent );
            }

        if ( ( edict->svflags & SVF_SENDONCE ) && ( edict->svflags & SVF_SENT ) )
            {
            // Entity has been sent once, and is marked as such, then remove it
            ent->PostEvent( EV_Remove, 0 );
            }

		   if ( showentnums )
			   {
            G_DrawDebugNumber( ent->origin + Vector( 0, 0, ent->maxs.z + 2 ), ent->entnum, 2, 1, 1, 0 );
			   }
		   }

	   // Process any pending events that got posted during the physics code.
	   L_ProcessPendingEvents();

	   // build the playerstate_t structures for all players
	   G_ClientEndServerFrames();

      // see if we should draw the bounding boxes
      G_ClientDrawBoundingBoxes();

	   // show how many traces the game code is doing
      if ( sv_traceinfo->integer )
		   {
         if ( sv_traceinfo->integer == 3 )
			   {
			   gi.DebugPrintf( "%0.2f : Total traces %d\n", level.time, sv_numtraces );
			   }
		   else
			   {
            gi.DPrintf( "%0.2f : Total traces %d\n", level.time, sv_numtraces );
			   }
		   }

	   // reset out count of the number of game traces
	   sv_numtraces = 0;

      level.framenum++;

      // we increment time so that events that occurr before we think again are automatically on the next frame
      levelTime += frameTime;
      level.setTime( levelTime, frameTime );
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
	}

void G_ClientThink
   (
   gentity_t *ent,
   usercmd_t *ucmd
   )

	{
   try
      {
	   if ( ent->entity )
		   {
		   current_ucmd = ucmd;
		   ent->entity->ProcessEvent( EV_ClientMove );
         current_ucmd = NULL;
		   }
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
	}

/*
===========
G_ClientBegin

called when a client has finished connecting, and is ready
to be placed into the game.  This will happen every level load.
============
*/
void G_ClientBegin
	(
   gentity_t *ent,
	usercmd_t *cmd
	)

	{
   try
      {
      if ( ent->inuse && ent->entity )
		   {
		   // the client has cleared the client side viewangles upon
		   // connecting to the server, which is different than the
		   // state when the game is saved, so we need to compensate
		   // with deltaangles
         ent->entity->SetDeltaAngles();
         }
	   else
		   {
         Player *player;

		   // a spawn point will completely reinitialize the entity
	      level.spawn_entnum = ent->s.number;
         player = new Player;
		   }

	   if ( level.intermissiontime && ent->entity )
		   {
		   G_MoveClientToIntermission( ent->entity );
		   }
	   else
		   {
		   // send effect if in a multiplayer game
		   if ( game.maxclients > 1 )
			   {
			   gi.Printf ( "%s entered the game\n", ent->client->pers.netname );
			   }
		   }

	   // make sure all view stuff is valid
	   if ( ent->entity )
		   {
		   ent->entity->ProcessEvent( EV_ClientEndFrame );

         if ( !Director.PlayerReady() )
            {
            // let any threads waiting on us know they can go ahead
            Director.PlayerSpawned();
            }
		   }
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
   }

/*
===========
G_ClientUserInfoChanged

called whenever the player updates a userinfo variable.

The game can override any of the settings in place
(forcing skins or names, etc) before copying it off.
============
*/
void G_ClientUserinfoChanged
   (
   gentity_t *ent,
   const char *userinfo
   )

   {
	const char	*s;
	int			playernum;
   Player      *player;
   float       fov;
   Event       *ev;

   try
      {
      if ( !ent )
         {
         assert( 0 );
         return;
         }

      player = ( Player * )ent->entity;

      if ( !player )
         {
         assert( 0 );
         return;
         }

	   // set name
	   s = Info_ValueForKey( userinfo, "name" );
      if ( !s )
         {
         assert( 0 );
         return;
         }
	   strncpy( ent->client->pers.netname, s, sizeof( ent->client->pers.netname ) - 1 );

      // send over a subset of the userinfo keys so other clients can
      // print scoreboards, display models, and play custom sounds
      playernum = ent - g_entities;
      gi.setConfigstring( CS_PLAYERS + playernum, va( "name\\%s", ent->client->pers.netname ) );

      // Fov
      if ( player )
         {
	      fov = atof( Info_ValueForKey( userinfo, "fov" ) );
	      if ( fov < 1 )
            {
		      fov = 90;
            }
	      else if ( fov > 160 )
            {
		      fov = 160;
            }
         ev = new Event( EV_Player_Fov );
         ev->AddFloat( fov );
         player->ProcessEvent( ev );
         }

	   // save off the userinfo in case we want to check something later
	   strncpy( ent->client->pers.userinfo, userinfo, sizeof( ent->client->pers.userinfo ) - 1 );
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
   }

/*
===========
ClientConnect

Called when a player begins connecting to the server.
Called again for every map change or tournement restart.

The session information will be valid after exit.

Return NULL if the client should be allowed, otherwise return
a string with the reason for denial.

Otherwise, the client will be sent the current gamestate
and will eventually get to ClientBegin.

firstTime will be qtrue the very first time a client connects
to the server machine, but qfalse on map changes and tournement
restarts.
============
*/
char *G_ClientConnect
   (
   int clientNum,
   qboolean firstTime
   )

   {
	const char *value;
	gentity_t	*ent;
	char		   userinfo[ MAX_INFO_STRING ];
	gclient_t	*client;

   try
      {
	   ent = &g_entities[ clientNum ];
	   gi.getUserinfo( clientNum, userinfo, sizeof( userinfo ) );

	   // check to see if they are on the banned IP list
	   value = Info_ValueForKey( userinfo, "ip" );
	   if ( SV_FilterPacket( value ) )
         {
		   return "Banned IP";
         }

	   // check for a password
	   value = Info_ValueForKey( userinfo, "password" );
	   if ( strcmp( password->string, value ) != 0 )
         {
		   return "Invalid password";
         }

	   // they can connect
	   ent->client = game.clients + clientNum;
	   client = ent->client;

      // read or initialize the session data
      // if there is already a body waiting for us (a loadgame), just
      // take it, otherwise spawn one from scratch
	   if ( firstTime )
         {
   	   memset( client, 0, sizeof( *client ) );

         // clear the respawning variables
         if ( !game.autosaved )
            {
            G_InitClientPersistant( client );
            }
   	   }

	   G_ClientUserinfoChanged( ent, userinfo );

	   if ( firstTime && game.maxclients > 1 )
         {
         gi.Printf( "%s connected\n", ent->client->pers.netname );
         }

      LoadingServer = false;
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }

	return NULL;
   }

/*
===========
G_ClientDisconnect

called when a player drops from the server

============
*/
void G_ClientDisconnect
	(
   gentity_t *ent
	)

	{
   try
      {
	   if ( !ent || ( !ent->client ) || ( !ent->entity ) )
		   {
		   return;
		   }

	   delete ent->entity;
	   ent->entity = NULL;
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
	}

/*
=================
G_ClientDrawBoundingBoxes
=================
*/
void G_ClientDrawBoundingBoxes
	(
	void
	)

	{
   gentity_t  *edict;
	Entity	*ent;
	Vector	eye;

	// don't show bboxes during deathmatch
   if ( ( !g_showgravpath->integer && !sv_showbboxes->integer ) || ( deathmatch->integer && !sv_cheats->integer ) )
		{
      return;
		}

   if ( sv_showbboxes->integer )
      {
      edict = g_entities;
      ent = edict->entity;
      if ( ent )
         {
         eye = ent->origin;
	      ent = findradius( NULL, eye, 1000 );
	      while( ent )
		      {
            switch ((int)sv_showbboxes->integer)
               {
               case 1:
                  if ( ent->edict != edict && ent->edict->s.solid)
                     {
                     G_DebugBBox( ent->origin, ent->mins, ent->maxs, 1, 1, 0, 1 );
                     }
                  break;
               case 2:
                  if ( ent->edict != edict && ent->edict->s.solid)
                     {
                     G_DebugBBox( vec_zero, ent->edict->absmin, ent->edict->absmax, 1, 0, 1, 1 );
                     }
                  break;
               case 3:
                  if ( ent->edict->s.modelindex && !(ent->edict->s.renderfx & RF_DONTDRAW) )
                     G_DebugBBox( ent->origin, ent->mins, ent->maxs, 1, 1, 0, 1 );
                  break;
               case 4:
                  G_DebugBBox( ent->origin, ent->mins, ent->maxs, 1, 1, 0, 1 );
                  break;
               case 5:
               default:
                  if ( ent->isSubclassOf( Animate ) && gi.IsModel( ent->edict->s.modelindex ) )
                     {
                     Animate * anim;
                     vec3_t mins, maxs;

                     anim = ( Animate * )ent;
                     gi.Frame_Bounds( ent->edict->s.modelindex, anim->CurrentAnim(), anim->CurrentFrame(), ent->edict->s.scale, mins, maxs );
                     G_DebugBBox( ent->origin, mins, maxs, 0, 1, 0, 1 );
                     }
                  else
                     {
                     G_DebugBBox( ent->origin, ent->mins, ent->maxs, 1, 1, 0, 1 );
                     }
                  break;
               }
	         ent = findradius( ent, eye, 1000 );
		      }
         }
      }

   if ( g_showgravpath->integer )
      {
      // Draw the gravity node paths
      gravPathManager.DrawGravPaths();
      }
	}

//======================================================================

#ifndef GAME_HARD_LINKED
// this is only here so the functions in q_shared.c and q_shwin.c can link
void Com_Error ( int level, const char *error, ... ) {
	va_list	argptr;
	char		text[4096];

	va_start (argptr, error);
	vsprintf (text, error, argptr);
	va_end (argptr);

	gi.Error( level, "%s", text);
}

void Sys_Error
   (
   const char *error,
   ...
   )

	{
	va_list	argptr;
	char		text[4096];

	va_start (argptr, error);
	vsprintf (text, error, argptr);
	va_end (argptr);

	gi.Error (ERR_FATAL, "%s", text);
	}

void Com_Printf
   (
   const char *msg,
   ...
   )

	{
	va_list	argptr;
	char		text[4096];

	va_start (argptr, msg);
	vsprintf (text, msg, argptr);
	va_end (argptr);

   gi.DPrintf ("%s", text);
	}

#endif
