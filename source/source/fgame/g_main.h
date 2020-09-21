//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/g_main.h                           $
// $Revision:: 16                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/17/00 12:36a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/g_main.h                                $
// 
// 16    7/17/00 12:36a Markd
// Made sure to close the log file when exiting a level or shutting down a
// server
// 
// 15    7/06/00 7:48p Markd
// Added LevelArchiveValid function
// 
// 14    6/15/00 8:04p Markd
// Added CleanupGame
// 
// 13    6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 12    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 11    6/10/00 4:23p Markd
// rewrote map restarting and loading out of date save games
// 
// 10    6/02/00 4:26p Markd
// renamed ReadGame functions to ReadPersistant
// 
// 9     1/10/00 5:33p Markd
// Added DeallocGameData
// 
// 8     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 7     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 6     12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 5     12/10/99 11:52a Aldie
// Adjusted player angles a bit
// 
// 4     12/01/99 11:26a Aldie
// Couple of fixes for emitters and more ammo stuff
// 
// 3     10/05/99 5:03p Markd
// Removed un-used game function ClientPredict
// 
// 2     9/16/99 4:50p Jimdose
// removed unused variables
// changed G_ClientConnect
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 7     8/28/99 3:24p Markd
// got rid of maxbulletholes and max bloodsplats
//
// DESCRIPTION:
// Global header file for g_main.cpp
//

#ifndef __G_MAIN_H__
#define __G_MAIN_H__

#include "g_local.h"
#include "gamecvars.h"
#include "level.h"

extern	Vector			vec_origin;
extern	Vector			vec_zero;

extern   qboolean       LoadingSavegame;
extern   qboolean       LoadingServer;

extern	game_import_t	gi;
extern	game_export_t	globals;

extern   gentity_t      *g_entities;
extern	gentity_t	   active_edicts;
extern	gentity_t	   free_edicts;

extern	int		      sv_numtraces;

extern   usercmd_t      *current_ucmd;

#define DM_FLAG( flag ) ( deathmatch->integer && ( ( int )dmflags->integer & ( flag ) ) )

void		G_BeginIntermission( const char *map );
void		G_MoveClientToIntermission( Entity *client );
void     G_WriteClient( Archiver &arc, gclient_t *client );
void     G_AllocGameData( void );
void     G_DeAllocGameData( void );
void		G_ClientDrawBoundingBoxes( void );

void     G_ExitWithError( const char *error );

extern "C" {
   void	   G_SpawnEntities( const char *mapname, const char *entities, int time );
	void		G_ClientEndServerFrames( void );
   void     G_ClientThink( gentity_t *ent, usercmd_t *cmd );
   char     *G_ClientConnect( int clientNum, qboolean firstTime );      
   void     G_ClientUserinfoChanged( gentity_t *ent, const char *userinfo );
   void     G_ClientDisconnect( gentity_t *ent );
   void     G_ClientBegin( gentity_t *ent, usercmd_t *cmd );
	void		G_WritePersistant( const char *filename );
	qboolean G_ReadPersistant( const char *filename );
	void		G_WriteLevel( const char *filename, qboolean autosave );
	qboolean G_ReadLevel( const char *filename );
	qboolean G_LevelArchiveValid( const char *filename );
	void		G_InitGame( int startTime, int randomSeed );
	void		G_ShutdownGame( void );
   void     G_CleanupGame( void );
   void     G_RunFrame( int levelTime, int frametime );
   void     G_ServerCommand( void );
   void     G_ClientThink( gentity_t *ent, usercmd_t *ucmd );
	}

void     ClosePlayerLogFile( void );

qboolean    SV_FilterPacket( const char *from );
void        SVCmd_AddIP_f( void );
void        SVCmd_RemoveIP_f( void );
void        SVCmd_ListIP_f( void );
void        SVCmd_WriteIP_f( void );

#endif /* g_main.h */

