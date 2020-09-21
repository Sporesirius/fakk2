//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_servercmds.c                    $
// $Revision:: 8                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 7/24/00 6:46p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_servercmds.c                         $
// 
// 8     7/24/00 6:46p Steven
// Changed sv_cinematic from a cvar to a player stat.
// 
// 7     7/14/00 9:52p Markd
// added global volume dampener on ambient sound effects for cinematics
// 
// 6     2/29/00 5:51p Jimdose
// added alternate spawnpoint support
// 
// 5     12/11/99 5:51p Markd
// First wave of bug fixes after q3a gold merge
// 
// 4     12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 3     10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION: 
// cg_servercmds.c -- text commands sent by the server

#include "cg_local.h"


/*
================
CG_ParseServerinfo

This is called explicitly when the gamestate is first received,
and whenever the server updates any serverinfo flagged cvars
================
*/
void CG_ParseServerinfo( void ) {
	const char	*info;
	const char	*mapname;
   char        map[ MAX_QPATH ];
   char        *spawnpos;

	info = CG_ConfigString( CS_SERVERINFO );
	cgs.gametype = atoi( Info_ValueForKey( info, "g_gametype" ) );
	cgs.dmflags = atoi( Info_ValueForKey( info, "dmflags" ) );
	cgs.teamflags = atoi( Info_ValueForKey( info, "teamflags" ) );
	cgs.fraglimit = atoi( Info_ValueForKey( info, "fraglimit" ) );
	cgs.timelimit = atoi( Info_ValueForKey( info, "timelimit" ) );
	cgs.maxclients = atoi( Info_ValueForKey( info, "sv_maxclients" ) );

	mapname = Info_ValueForKey( info, "mapname" );

   spawnpos = strchr( mapname, '$' );
   if ( spawnpos )
      {
      Q_strncpyz( map, mapname, spawnpos - mapname + 1 );
      }
   else
      {
      strcpy( map, mapname );
      }

	Com_sprintf( cgs.mapname, sizeof( cgs.mapname ), "maps/%s.bsp", map );
}


/*
================
CG_ConfigStringModified

================
*/
static void CG_ConfigStringModified( void )
   {	
	int		num;

	num = atoi( cgi.Argv( 1 ) );

	// get the gamestate from the client system, which will have the
	// new configstring already integrated
	cgi.GetGameState( &cgs.gameState );

   CG_ProcessConfigString( num );
   }

/*
===============
CG_MapRestart
===============
*/
static void CG_MapRestart( void ) {
	if ( cg_showmiss->integer ) {
		cgi.Printf( "CG_MapRestart\n" );
	}
   CG_Shutdown();
   CG_Init( &cgi, cgs.processedSnapshotNum, cgs.serverCommandSequence );
}

/*
=================
CG_ServerCommand

The string has been tokenized and can be retrieved with
Cmd_Argc() / Cmd_Argv()
=================
*/
static void CG_ServerCommand( void )
   {
	const char	*cmd;

	cmd = cgi.Argv(0);

	if ( !cmd[0] ) 
      {
		// server claimed the command
		return;
	   }

	if ( !strcmp( cmd, "cs" ) )
      {
		CG_ConfigStringModified();
		return;
	   }

	if ( !strcmp( cmd, "print" ) )
      {
		cgi.Printf( "%s", cgi.Argv(1) );
		return;
	   }

	if ( !strcmp( cmd, "map_restart" ) ) 
      {
		CG_MapRestart();
		return;
	   }

	cgi.Printf( "Unknown client game command: %s\n", cmd );
   }


/*
====================
CG_ExecuteNewServerCommands

Execute all of the server commands that were received along
with this this snapshot.
====================
*/
void CG_ExecuteNewServerCommands( int latestSequence ) {
	while ( cgs.serverCommandSequence < latestSequence ) {
		if ( cgi.GetServerCommand( ++cgs.serverCommandSequence ) ) {
			CG_ServerCommand();
		}
	}
}
