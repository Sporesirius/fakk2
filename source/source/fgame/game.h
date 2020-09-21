//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/game.h                             $
// $Revision:: 3                                                              $
//     $Date:: 5/24/00 3:14p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/game.h                                  $
// 
// 3     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 2     1/06/00 11:08p Jimdose
// cleaning up unused code
//
// DESCRIPTION:
// 

#ifndef __GAME_H__
#define __GAME_H__

#include "g_local.h"
#include "class.h"

//
// this structure is left intact through an entire game
// it should be initialized at dll load time, and read/written to
// the server.ssv file for savegames
//

class Game : public Class
	{
	public:
		CLASS_PROTOTYPE( Game );

      gclient_t	      *clients;				// [maxclients]
	   qboolean	         autosaved;

	   // store latched cvars here that we want to get at often
	   int			      maxclients;
	   int			      maxentities;

                        Game() { Init(); }

      void              Init( void );
	   virtual void      Archive( Archiver &arc );
	};

extern Game game;

#endif /* !__GAME_H__ */
