//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/game.cpp                           $
// $Revision:: 5                                                              $
//     $Date:: 5/25/00 7:52p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/game.cpp                                $
// 
// 5     5/25/00 7:52p Markd
// 2nd pass save game stuff
// 
// 4     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 3     1/10/00 5:29p Markd
// fixed bug in unarchiving game and archiving game where logic was inverted
// 
// 2     1/06/00 11:08p Jimdose
// cleaning up unused code
//
// DESCRIPTION:
// 

#include "game.h"

Game game;

CLASS_DECLARATION( Class, Game, NULL )
	{
		{ NULL, NULL }
	};

void Game::Init
   (
   void
   )

   {
   clients = NULL;

   autosaved = false;

   maxentities = 0;
   maxclients = 0;
   }

void Game::Archive
	(
	Archiver &arc
	)

   {
   int i;

   Class::Archive( arc );

   arc.ArchiveBoolean( &autosaved );

   arc.ArchiveInteger( &maxentities );
   arc.ArchiveInteger( &maxclients );

   if ( arc.Loading() )
      {
      G_AllocGameData();
      }

   for( i = 0; i < maxclients; i++ )
      {
      arc.ArchiveRaw( &clients[ i ], sizeof( gclient_t ) );
      }
   }

