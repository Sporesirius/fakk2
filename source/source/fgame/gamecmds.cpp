//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/gamecmds.cpp                       $
// $Revision:: 8                                                              $
//     $Date:: 7/10/00 9:27p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/gamecmds.cpp                            $
// 
// 8     7/10/00 9:27p Markd
// added ammo variables for how much ammo the player has.  Added levelvars and
// gamevars commands
// 
// 7     6/10/00 4:23p Markd
// rewrote map restarting and loading out of date save games
// 
// 6     4/26/00 7:55p Markd
// Added more documentation code into various systems
// 
// 5     2/17/00 4:18p Jimdose
// added checks in G_ClientCommand for NULL ent being passed in
// 
// 4     1/28/00 5:43p Markd
// Added script command to the game
// 
// 3     1/22/00 2:04p Markd
// Added "kill" to registered commands
// 
// 2     1/06/00 11:10p Jimdose
// cleaning up unused code
//
// DESCRIPTION:
// 

#include "gamecmds.h"
#include "g_local.h"
#include "camera.h"
#include "viewthing.h"
#include "soundman.h"
#include "navigate.h"

typedef struct
   {
   const char  *command;
   qboolean    ( *func )( gentity_t *ent );
   qboolean    allclients;
   } consolecmd_t;

consolecmd_t G_ConsoleCmds[] =
   {
   //   command name       function             available in multiplayer?
      { "say",             G_SayCmd,            qtrue },
      { "eventlist",       G_EventListCmd,      qfalse },
      { "pendingevents",   G_PendingEventsCmd,  qfalse },
      { "eventhelp",       G_EventHelpCmd,      qfalse },
      { "dumpevents",      G_DumpEventsCmd,     qfalse },
      { "classevents",     G_ClassEventsCmd,    qfalse },
      { "dumpclassevents", G_DumpClassEventsCmd,qfalse },
      { "dumpallclasses",  G_DumpAllClassesCmd, qfalse },
      { "classlist",       G_ClassListCmd,      qfalse },
      { "classtree",       G_ClassTreeCmd,      qfalse },
      { "cam",             G_CameraCmd,         qfalse },
      { "snd",             G_SoundCmd,          qfalse },
      { "showvar",         G_ShowVarCmd,        qfalse },
      { "script",          G_ScriptCmd,         qfalse },
      { "levelvars",       G_LevelVarsCmd,      qfalse },
      { "gamevars",        G_GameVarsCmd,     qfalse },
      { NULL,              NULL,                NULL }
   };

void G_InitConsoleCommands
   (
   void
   )

   {
   consolecmd_t *cmds;

   //
	// the game server will interpret these commands, which will be automatically
	// forwarded to the server after they are not recognized locally
	//
	gi.AddCommand( "give" );
	gi.AddCommand( "god" );
	gi.AddCommand( "notarget" );
	gi.AddCommand( "noclip" );
	gi.AddCommand( "kill" );
	gi.AddCommand( "script" );

   for( cmds = G_ConsoleCmds; cmds->command != NULL; cmds++ )
      {
      gi.AddCommand( cmds->command );
      }
   }

qboolean	G_ConsoleCommand
   (
   void
   )

   {
   gentity_t *ent;
   qboolean result;

   result = qfalse;
   try
      {
      ent = &g_entities[ 0 ];
      result = G_ProcessClientCommand( ent );
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }

   return result;
   }

void G_ClientCommand
	(
   gentity_t *ent
	)

	{
   try
      {
      if ( ent && !G_ProcessClientCommand( ent ) )
         {
		   // anything that doesn't match a command will be a chat
		   G_Say( ent, false, true );
		   }
      }

   catch( const char *error )
      {
      G_ExitWithError( error );
      }
   }

qboolean G_ProcessClientCommand
	(
   gentity_t *ent
	)

	{
	const char	   *cmd;
   consolecmd_t   *cmds;
	int			   i;
   int            n;
	Event			   *ev;

	if ( !ent || !ent->client || !ent->entity )
		{
		// not fully in game yet
		return qfalse;
		}

	cmd = gi.argv( 0 );
   for( cmds = G_ConsoleCmds; cmds->command != NULL; cmds++ )
      {
      // if we have multiple clients and this command isn't allowed by multiple clients, skip it
      if ( ( game.maxclients > 1 ) && ( !cmds->allclients ) )
         {
         continue;
         }

      if ( !Q_stricmp( cmd, cmds->command ) )
         {
         return cmds->func( ent );
         }
      }

  	if ( Event::Exists( cmd ) )
		{
		ev = new Event( cmd );
		ev->SetSource( EV_FROM_CONSOLE );
		ev->SetConsoleEdict( ent );

      n = gi.argc();
		for( i = 1; i < n; i++ )
			{
			ev->AddToken( gi.argv( i ) );
			}

      if ( !Q_stricmpn( cmd, "ai_", 2 ) )
			{
			return PathManager.ProcessEvent( ev );
			}
		else if ( !Q_stricmpn( cmd, "view", 4 ) )
			{
			return Viewmodel.ProcessEvent( ev );
			}
		else
			{
			return ent->entity->ProcessEvent( ev );
			}
		}

   return qfalse;
	}

/*
==================
Cmd_Say_f
==================
*/
void G_Say
	(
   gentity_t *ent,
	qboolean team,
	qboolean arg0
	)

	{
	int			j;
   gentity_t   *other;
	const char	*p;
	char			text[ 2048 ];

	if ( gi.argc() < 2 && !arg0 )
		{
		return;
		}

   if ( !ent->entity )
      {
      // just in case we're not joined yet.
      team = false;
      }

	if ( !DM_FLAG( DF_MODELTEAMS | DF_SKINTEAMS ) )
		{
		team = false;
		}

	if ( team )
		{
		Com_sprintf( text, sizeof( text ), "(%s): ", ent->client->pers.netname );
		}
	else
		{
		Com_sprintf( text, sizeof( text ), "%s: ", ent->client->pers.netname );
		}

	if ( arg0 )
		{
		strcat( text, gi.argv( 0 ) );
		strcat( text, " " );
		strcat( text, gi.args() );
		}
	else
		{
		p = gi.args();

		if ( *p == '"' )
			{
			p++;
			strcat( text, p );
			text[ strlen( text ) - 1 ] = 0;
			}
		else
			{
			strcat( text, p );
			}
		}

	// don't let text be too long for malicious reasons
	if ( strlen( text ) > 150 )
		{
		text[ 150 ] = 0;
		}

	strcat( text, "\n" );

   if ( dedicated->integer )
		{
      gi.SendServerCommand( NULL, "print \"%s\"", text );
		}

	for( j = 0; j < game.maxclients; j++ )
		{
      other = &g_entities[ j ];
		if ( !other->inuse || !other->client || !other->entity )
			{
			continue;
			}

      if ( team )
			{
			if ( !OnSameTeam( ent->entity, other->entity ) )
				{
				continue;
				}
			}

      gi.SendServerCommand( NULL, "print \"%s\"", text );
		}
	}

qboolean G_CameraCmd
   (
   gentity_t *ent
   )

   {
   Event *ev;
	const char *cmd;
   int   i;
   int   n;

   n = gi.argc();
   if ( !n )
      {
      gi.Printf( "Usage: cam [command] [arg 1]...[arg n]\n" );
      return qtrue;
      }

	cmd = gi.argv( 1 );
  	if ( Event::Exists( cmd ) )
		{
		ev = new Event( cmd );
		ev->SetSource( EV_FROM_CONSOLE );
      ev->SetConsoleEdict( NULL );

		for( i = 2; i < n; i++ )
			{
			ev->AddToken( gi.argv( i ) );
			}

      CameraMan.ProcessEvent( ev );
      }
   else
      {
      gi.Printf( "Unknown camera command '%s'.\n", cmd );
      }

   return qtrue;
   }

qboolean G_SoundCmd
   (
   gentity_t *ent
   )

   {
   Event *ev;
	const char *cmd;
   int   i;
   int   n;

   n = gi.argc();
   if ( !n )
      {
      gi.Printf( "Usage: snd [command] [arg 1]...[arg n]\n" );
      return qtrue;
      }

	cmd = gi.argv( 1 );
  	if ( Event::Exists( cmd ) )
		{
		ev = new Event( cmd );
		ev->SetSource( EV_FROM_CONSOLE );
      ev->SetConsoleEdict( NULL );

		for( i = 2; i < n; i++ )
			{
			ev->AddToken( gi.argv( i ) );
			}

      SoundMan.ProcessEvent( ev );
      }
   else
      {
      gi.Printf( "Unknown sound command '%s'.\n", cmd );
      }

   return qtrue;
   }

qboolean G_SayCmd
   (
   gentity_t *ent
   )

   {
	G_Say( ent, false, false );

   return qtrue;
   }

qboolean G_EventListCmd
   (
   gentity_t *ent
   )

   {
   const char *mask;

   mask = NULL;
   if ( gi.argc() > 1 )
      {
      mask = gi.argv( 1 );
      }

   Event::ListCommands( mask );

   return qtrue;
   }

qboolean G_PendingEventsCmd
   (
   gentity_t *ent
   )

   {
   const char *mask;

   mask = NULL;
   if ( gi.argc() > 1 )
      {
      mask = gi.argv( 1 );
      }

   Event::PendingEvents( mask );

   return qtrue;
   }

qboolean G_EventHelpCmd
   (
   gentity_t *ent
   )

   {
   const char *mask;

   mask = NULL;
   if ( gi.argc() > 1 )
      {
      mask = gi.argv( 1 );
      }

   Event::ListDocumentation( mask, false );

   return qtrue;
   }

qboolean G_DumpEventsCmd
   (
   gentity_t *ent
   )

   {
   const char *mask;

   mask = NULL;
   if ( gi.argc() > 1 )
      {
      mask = gi.argv( 1 );
      }

   Event::ListDocumentation( mask, true );

   return qtrue;
   }

qboolean G_ClassEventsCmd
   (
   gentity_t *ent
   )

   {
   const char *className;

   className = NULL;
   if ( gi.argc() < 2 )
      {
      gi.Printf( "Usage: classevents [className]\n" );
      className = gi.argv( 1 );
      }
   else
      {
      className = gi.argv( 1 );
      ClassEvents( className );
      }
   return qtrue;
   }

qboolean G_DumpClassEventsCmd
   (
   gentity_t *ent
   )

   {
   const char *className;

   className = NULL;
   if ( gi.argc() < 2 )
      {
      gi.Printf( "Usage: dumpclassevents [className]\n" );
      className = gi.argv( 1 );
      }
   else
      {
      className = gi.argv( 1 );
      ClassEvents( className, qtrue );
      }
   return qtrue;
   }

qboolean G_DumpAllClassesCmd
   (
   gentity_t *ent
   )

   {
   DumpAllClasses();
   return qtrue;
   }

qboolean G_ClassListCmd
   (
   gentity_t *ent
   )

   {
   listAllClasses();

   return qtrue;
   }

qboolean G_ClassTreeCmd
   (
   gentity_t *ent
   )

   {
   if ( gi.argc() > 1 )
      {
      listInheritanceOrder( gi.argv( 1 ) );
      }
   else
      {
      gi.SendServerCommand( ent - g_entities, "print \"Syntax: classtree [classname].\n\"" );
      }

   return qtrue;
   }

qboolean G_ShowVarCmd
   (
   gentity_t *ent
   )

   {
   ScriptVariable *var;

   var = Director.GetExistingVariable( gi.argv( 1 ) );
   if ( var )
      {
      gi.SendServerCommand( ent - g_entities, "print \"%s = '%s'\n\"", gi.argv( 1 ), var->stringValue() );
      }
   else
      {
      gi.SendServerCommand( ent - g_entities, "print \"Variable '%s' does not exist.\"", gi.argv( 1 ) );
      }

   return qtrue;
   }

qboolean G_ScriptCmd
   (
   gentity_t *ent
   )

   {
	int i, argc;
	const char *argv[ 32 ];
	char args[ 32 ][ 64 ];

	argc = 0;
	for( i = 1; i < gi.argc(); i++ )
		{
		if ( argc < 32 )
			{
		   strncpy( args[ argc ], gi.argv( i ), 64 );
		   argv[ argc ] = args[ argc ];
		   argc++;
         }
		}
   if ( argc > 0 )
      {
	   level.consoleThread->ProcessCommand( argc, argv );
      }

   return qtrue;
   }

void PrintVariableList
   (
   ScriptVariableList * list
   )
   {
   ScriptVariable *var;
	int i;

   for( i = 1; i <= list->NumVariables(); i++ )
      {
		var = list->GetVariable( i );
      gi.Printf( "%s = %s\n", var->getName(), var->stringValue() );
      }
   gi.Printf( "%d variables\n", list->NumVariables() );
   }

qboolean G_LevelVarsCmd
   (
   gentity_t *ent
   )

   {
   gi.Printf( "Level Variables\n" );
   PrintVariableList( &levelVars );

   return qtrue;
   }

qboolean G_GameVarsCmd
   (
   gentity_t *ent
   )

   {
   gi.Printf( "Game Variables\n" );
   PrintVariableList( &gameVars );

   return qtrue;
   }

