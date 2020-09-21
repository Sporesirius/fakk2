//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/g_local.h                          $
// $Revision:: 18                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 29.07.00 10:52p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/g_local.h                               $
// 
// 18    29.07.00 10:52p Jimdose
// moved radius2 out of server section of gentity_s
// 
// 17    29.07.00 10:51p Jimdose
// added radius2 to gentity_t
// 
// 16    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 15    6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 14    4/10/00 11:57a Steven
// Moved process init commands to happen before EV_POSTSPAWN.
// 
// 13    2/11/00 7:25p Aldie
// Fixed some rope setup problems and fixed some reloading issues with loop
// fire weapons
// 
// 12    1/19/00 10:22a Steven
// Increased the sound radius so monsters could hear sounds from a reasonable
// distance.
// 
// 11    1/10/00 5:30p Markd
// Removed old TAG_GAME
// 
// 10    1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 9     12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 8     12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 7     10/25/99 6:39p Markd
// removed size and other unused variables, added radius and centroid to both
// server and game code
// 
// 6     10/18/99 3:58p Aldie
// Fix for beam endpoints
// 
// 5     10/07/99 9:57a Markd
// made fov come out of playerstate not cvar, got rid of timestamp
// 
// 4     10/01/99 2:42p Markd
// moved all the binding code back into Entity from Mover
// 
// 3     9/16/99 4:50p Jimdose
// removed unused variables
// 
// 2     9/13/99 3:30p Jimdose
// merge
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 16    7/07/99 11:26a Steven
// Added some stuff on the sector pathfinding approach.
//
// DESCRIPTION:
// local definitions for game module
//

#ifndef __G_LOCAL_H__
#define __G_LOCAL_H__

#include "q_shared.h"

// define GAME_INCLUDE so that game.h does not define the
// short, server-visible gclient_t and gentity_t structures,
// because we define the full size ones in this file
#define	GAME_INCLUDE
#include "g_public.h"
#include "bg_public.h"
#include "container.h"
#include "str.h"

// the "gameversion" client command will print this plus compile date
#define	GAMEVERSION	"fakk2"

// times for posting events
// Even though negative times technically don't make sense, the effect is to 
// sort events that take place at the start of a map so that they are executed
// in the proper order.  For example, spawnargs must occur before any script
// commands take place, while unused entities must be removed before the spawnargs
// are parsed.

#define  EV_REMOVE            -11    // remove any unused entities before spawnargs are parsed
#define  EV_SPAWNARG          -10    // for spawn args passed in by the bsp file
#define  EV_LINKDOORS         -9     // for finding out which doors are linked together
#define  EV_LINKBEAMS         -9     // for finding out the endpoints of beams
#define  EV_SETUP_ROPEPIECE   -8     
#define  EV_SETUP_ROPEBASE    -7      
#define  EV_PROCESS_INIT      -6

#define  EV_POSTSPAWN         -1     // for any processing that must occur after all objects are spawned

#define SOUND_RADIUS          1500    // Sound travel distance for AI

#define	random()					((rand () & 0x7fff) / ((float)0x7fff))
#define	crandom()				(2.0 * (random() - 0.5))

// predefine Entity so that we can add it to gentity_t without any errors
class Entity;

// client data that stays across multiple level loads
typedef struct
	{
	char			userinfo[MAX_INFO_STRING];
	char			netname[16];

	// values saved and restored from edicts when changing levels
	int			health;
	int			max_health;

	} client_persistant_t;

// this structure is cleared on each PutClientInServer(),
// except for 'client->pers'
typedef struct gclient_s
	{
	// known to server
	playerState_t			ps;				// communicated by server to clients
	int						ping;

	// private to game
	client_persistant_t	pers;
   vec3_t		         cmd_angles;	   // angles sent over in the last command
   } gclient_t;

struct gentity_s
	{
	entityState_t	            s;				// communicated by server to clients
	struct         gclient_s	*client;	   // NULL if not a player
	qboolean	                  inuse;
	qboolean	                  linked;		// qfalse if not in any good cluster
	int		   	            linkcount;

	int			               svflags;		// SVF_NOCLIENT, SVF_BROADCAST, etc

	qboolean	                  bmodel;		// if false, assume an explicit mins / maxs bounding box
									               // only set by gi.SetBrushModel
	vec3_t		               mins, maxs;
	int			               contents;	// CONTENTS_TRIGGER, CONTENTS_SOLID, CONTENTS_BODY, etc
									               // a non-solid entity should set to 0

	vec3_t		               absmin, absmax;   // derived from mins/maxs and origin + rotation

   float                      radius;     // radius of object
   vec3_t                     centroid;   // centroid, to be used with radius
   int                        areanum;    // areanum needs to be seen inside the game as well

	// currentOrigin will be used for all collision detection and world linking.
	// it will not necessarily be the same as the trajectory evaluation for the current
	// time, because each entity must be moved one at a time after time is advanced
	// to avoid simultanious collision issues
	vec3_t		               currentOrigin;
	vec3_t		               currentAngles;

	int			               ownerNum;			// objects never interact with their owners, to
									                     // prevent player missiles from immediately
									                     // colliding with their owner

   solid_t			            solid;   // Added for FAKK2

	// DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
	// EXPECTS THE FIELDS IN THAT ORDER!

	//================================

   Entity			*entity;
	float				freetime;			// svs.time when the object was freed
	float				spawntime;			// svs.time when the object was spawned

	float				radius2;				// squared radius of object.  Used in findradius in g_utils.cpp

	char				entname[ 64 ];
	
   // GAMEFIX Moved some of the old fields here for the game code.   These
   // might still be needed or might not :-)
   int				clipmask;

	gentity_t		*next;
	gentity_t		*prev;
	};

#include "vector.h"
#include "linklist.h"
#include "class.h"
#include "game.h"
#include "g_main.h"
#include "listener.h"
#include "g_utils.h"
#include "g_spawn.h"
#include "g_phys.h"
#include "debuglines.h"

#endif // __G_LOCAL_H__

