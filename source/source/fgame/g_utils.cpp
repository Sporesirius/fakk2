//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/g_utils.cpp                        $
// $Revision:: 93                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 8/10/00 4:01p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/g_utils.cpp                             $
// 
// 93    8/10/00 4:01p Steven
// Fixed some case sensitive stuff in CacheResource.
// 
// 92    8/04/00 3:54p Markd
// Added StartCinematic and StopCinematic
// 
// 91    7/29/00 11:51p Aldie
// Added back in G_ClearFade
// 
// 90    29.07.00 11:40p Jimdose
// fixed bug in findradius
// 
// 88    29.07.00 10:51p Jimdose
// added radius2 to gentity_t
// 
// 87    7/29/00 4:00p Aldie
// Added autofadein for skipping cinematics
// 
// 86    7/28/00 6:57p Steven
// Made CloneEntity process init commands again and added some player died
// stuff.
// 
// 85    7/28/00 1:10a Markd
// canceled init commands on fakeplayered julie
// 
// 84    7/27/00 10:54p Steven
// Added means of death eat.
// 
// 83    7/27/00 9:43p Aldie
// Changed dialog for invalid save games
// 
// 82    7/24/00 5:55p Markd
// added back in centerprint on mission failed
// 
// 81    7/23/00 6:03p Markd
// added fadeout and fadesound to dieing and level change
// 
// 80    7/19/00 8:19p Steven
// Added gas blockable means of death.
// 
// 79    7/19/00 5:08p Steven
// Added electric water means of death.
// 
// 78    7/18/00 3:29p Markd
// added better caching for sounds in general
// 
// 77    7/17/00 2:55p Steven
// Fixed mission failed graphic.
// 
// 76    7/16/00 4:37p Steven
// Added new fire means of death.
// 
// 75    7/15/00 12:52p Markd
// added mission failure code
// 
// 74    7/13/00 12:30p Steven
// Added poison means of death, changed G_TraceEntities to find all entities at
// once instead of 1 at a time, and optimized broadcast sound.
// 
// 73    7/11/00 8:03a Steven
// Fixed MOD_matches to return true when damage_type == all (-1) not the
// opposite.
// 
// 72    7/11/00 12:01a Markd
// Added light sword as valid MOD_SWORD damage
// 
// 71    7/10/00 11:54p Markd
// added exit level code
// 
// 70    7/07/00 6:36p Steven
// Added mission failed stuff.
// 
// 69    7/02/00 6:46p Markd
// added spawn thread to PlayerStart
// 
// 68    7/02/00 1:11p Steven
// Changed means of death light to lightsword.
// 
// 67    7/01/00 12:01p Steven
// Added electricsword and plasmashotgun means of death.
// 
// 66    6/29/00 2:06p Steven
// Added caching of statemaps to CacheResource.
// 
// 65    6/28/00 7:55p Aldie
// Added a MOD
// 
// 64    6/17/00 11:55a Steven
// Fixed looping sounds in save games.
// 
// 63    6/14/00 5:43p Steven
// Added plasmabeam means of death.
// 
// 62    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 61    6/13/00 6:46p Aldie
// Added some damage debug info.  Added an ignoreEnt for explosion events
// 
// 60    6/13/00 3:45p Steven
// Added a gib means of death.
// 
// 59    6/08/00 1:45p Steven
// Added means of death light.
// 
// 58    6/06/00 2:37p Steven
// Added sting2 means of death.
// 
// 57    6/05/00 6:42p Steven
// Added radiation means of death.
// 
// 56    6/05/00 3:29p Aldie
// Added flickering to waterstats
// 
// 55    6/03/00 3:46p Aldie
// Added in g_debugtargets for debugging targetnames and targets
// 
// 54    5/31/00 10:19a Markd
// 4th pass saved games
// 
// 53    5/30/00 10:59a Aldie
// Added Circle of Protection Powerup
// 
// 52    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 51    5/25/00 4:28p Markd
// fixed up archive functions
// 
// 50    5/22/00 5:13p Aldie
// First version of soulsucker
// 
// 49    5/16/00 4:12p Markd
// increased level time precision on g_Showtrace
// 
// 48    5/10/00 10:31a Steven
// Added means of death firesword.
// 
// 47    5/05/00 2:15p Steven
// Added chainsword and on_fire means of death.
// 
// 46    5/04/00 12:46p Steven
// Added an axe means of death.
// 
// 45    4/27/00 12:04p Steven
// Added crush_every_frame means of death.
// 
// 44    4/18/00 12:27p Markd
// added radius support to findradius
// 
// 43    4/15/00 4:24p Markd
// Fixed player turning
// 
// 42    4/10/00 1:20p Markd
// Fixed typo
// 
// 41    4/05/00 3:51p Markd
// added label checking for scripts
// 
// 40    3/23/00 12:19p Markd
// increased range of dynamic light radius
// 
// 39    3/15/00 4:09p Aldie
// Fixed a bug with using weapons, and added some ability to force a state in
// the player
// 
// 38    3/04/00 2:02p Markd
// fixed constantLight problem
// 
// 37    3/04/00 11:48a Markd
// Added light style support
// 
// 36    3/03/00 4:42p Markd
// added in debugging messages for music and reverb
// 
// 35    2/29/00 5:51p Jimdose
// added alternate spawnpoint support
// 
// 34    2/23/00 6:21p Aldie
// More inventory changes
// 
// 33    2/17/00 6:26p Aldie
// Fixed naming conventions for weapon hand and also added various attachtotag
// functionality for weapons that attach to different tags depending on which
// hand they are wielded in.
// 
// 32    1/22/00 5:09p Steven
// Added a trace entities function.
// 
// 31    1/22/00 1:44p Markd
// Fixed attached entity bug
// 
// 30    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 29    1/14/00 5:06p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 28    1/11/00 6:41p Markd
// Removed fulltrace code from the game
// 
// 27    1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 26    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 25    12/17/99 8:26p Jimdose
// got rid of unused vars and functions
// 
// 24    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 23    12/02/99 6:58p Markd
// fixed attached entity bug with cloning entities
// 
// 22    11/12/99 11:21a Markd
// Added Debug Circles and DebugPyramids
// 
// 21    11/09/99 8:05p Markd
// Fixed ArchiveEdict function
// 
// 20    11/01/99 4:00p Jimdose
// initialized quaternion values on bone controllers
// 
// 19    10/29/99 6:46p Jimdose
// added bone controllers
// 
// 18    10/29/99 2:18p Markd
// don't copy over the eflags
// 
// 17    10/28/99 6:33p Markd
// Added fakeplayer ability, also added CloneEntity
// 
// 16    10/25/99 6:39p Markd
// removed size and other unused variables, added radius and centroid to both
// server and game code
// 
// 15    10/14/99 5:08p Markd
// removed a lot of G_GetMoveDir calls from the initialization code
// 
// 14    10/13/99 4:47p Steven
// Fixed BroadcastSound.
// 
// 13    10/12/99 2:23p Markd
// Rewrote camera and player movetype system
// 
// 12    10/05/99 2:28p Markd
// fixed all assignment within conditional warnings
// 
// 11    10/01/99 2:42p Markd
// moved all the binding code back into Entity from Mover
// 
// 10    9/28/99 5:15p Markd
// Fixed more merge bugs with sharing class, vector and listener between three
// modules
// 
// 9     9/28/99 4:26p Markd
// merged listener, class and vector between 3 projects
// 
// 8     9/23/99 12:38p Markd
// fixed a lot of renderer startup warnings, errors and bugs
// 
// 7     9/22/99 4:47p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 6     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 5     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 4     9/15/99 6:57p Aldie
// Update to get game working
// 
// 3     9/13/99 4:22p Jimdose
// merge
// 
// 2     9/13/99 3:27p Aldie
// code merge
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 28    9/02/99 5:41p Markd
// made CacheResource utility functions changed code every where else
// 
// 27    9/01/99 4:21p Jimdose
// fixed bug in findclientsinradius where passing in a NULL entity crashes
// 
// 26    8/30/99 2:36p Steven
// Added support for volume and minimum distance for loop sounds.
// 
// 25    8/28/99 3:22p Markd
// initialize r_constantlight to 1, 1, 1
// 
// 24    8/25/99 12:42p Markd
// Fixed some minor and major scripting bugs
// 
// 23    8/18/99 3:28p Jimdose
// added cylindrical collision detection
// 
// 22    8/17/99 5:08p Markd
// Changed all FS_ReadFile's to FS_ReadFileEx's in game code
// 
// 21    7/29/99 5:33p Markd
// Fixed weird compiler bug
// 
// 20    7/29/99 11:41a Markd
// Added precache and global support
//
// DESCRIPTION:
//

#include "g_local.h"
#include "g_utils.h"
#include "ctype.h"
#include "worldspawn.h"
#include "scriptmaster.h"
#include "player.h"
#include "PlayerStart.h"

char means_of_death_strings[ MOD_TOTAL_NUMBER ][ 32 ] =
   {
   "none",
   "drown",
   "suicide",
   "crush",
	"crush_every_frame",
   "telefrag",
   "lava",
   "slime",
   "falling",
   "last_self_inflicted",
   "explosion",
   "explodewall",
   "electric",
	"electricwater",
   "thrownobject",
   "beam",
   "rocket",
   "impact",
   "gas",
	"gas_blockable",
   "acid",
   "sword",
   "plasma",
	"plasmabeam",
	"plasmashotgun",
   "sting",
	"sting2",
   "sling",
   "bullet",
   "fast_bullet",
   "vehicle",
	"fire",
	"fire_blockable",
	"vortex",
	"lifedrain",
	"flashbang",
	"poo_explosion",
	"axe",
	"chainsword",
	"on_fire",
	"firesword",
	"electricsword",
   "circleofprotection",
	"radiation",
	"lightsword",
	"gib",
   "impale",
   "uppercut",
	"poison",
	"eat"
   };

int MOD_string_to_int( str immune_string )
	{
	int i;

	for ( i = 0 ; i < MOD_TOTAL_NUMBER ; i++ )
		{
		if ( !immune_string.icmp( means_of_death_strings[ i ] ) )
			return i;
		}

	gi.DPrintf( "Unknown means of death - %s\n", immune_string.c_str() );
	return -1;
	}

qboolean MOD_matches
   ( 
   int incoming_damage, 
   int damage_type 
   )
	{
   if ( damage_type == -1 )
      {
      return qtrue;
      }

   // special case the sword
   if ( damage_type == MOD_SWORD )
      {
      if (
            ( incoming_damage == MOD_SWORD ) ||
            ( incoming_damage == MOD_ELECTRICSWORD ) ||
            ( incoming_damage == MOD_LIGHTSWORD ) ||
            ( incoming_damage == MOD_FIRESWORD )
         )
         {
         return qtrue;
         }
      }
   else if ( damage_type == incoming_damage )
      {
      return qtrue;
      }

   return qfalse;
	}

/*
============
G_TouchTriggers

============
*/
void G_TouchTriggers
	(
	Entity *ent
	)

	{
	int		i;
	int		num;
   int      touch[ MAX_GENTITIES ];
   gentity_t  *hit;
	Event		*ev;

	// dead things don't activate triggers!
	if ( ( ent->client || ( ent->edict->svflags & SVF_MONSTER ) ) && ( ent->health <= 0 ) )
		{
		return;
		}

   num = gi.AreaEntities( ent->absmin, ent->absmax, touch, MAX_GENTITIES );

	// be careful, it is possible to have an entity in this
	// list removed before we get to it (killtriggered)
	for( i = 0; i < num; i++ )
		{
		hit = &g_entities[ touch[ i ] ];
		if ( !hit->inuse || ( hit->entity == ent ) || ( hit->solid != SOLID_TRIGGER ) )
         {
         continue;
         }

		assert( hit->entity );

		// FIXME
		// should we post the events on the list with zero time
		ev = new Event( EV_Touch );
		ev->AddEntity( ent );
		hit->entity->ProcessEvent( ev );
		}
	}

/*
============
G_TouchSolids

Call after linking a new trigger in during gameplay
to force all entities it covers to immediately touch it
============
*/
void G_TouchSolids
	(
	Entity *ent
	)

	{
	int		i;
	int		num;
   int      touch[ MAX_GENTITIES ];
   gentity_t  *hit;
	Event		*ev;

   num = gi.AreaEntities( ent->absmin, ent->absmax, touch, MAX_GENTITIES );

	// be careful, it is possible to have an entity in this
	// list removed before we get to it (killtriggered)
	for( i = 0; i < num; i++ )
		{
		hit = &g_entities[ touch[ i ] ];
		if ( !hit->inuse )
			{
			continue;
			}

		assert( hit->entity );

		//FIXME
		// should we post the events so that we don't have to worry about any entities going away
		ev = new Event( EV_Touch );
		ev->AddEntity( ent );
		hit->entity->ProcessEvent( ev );
		}
	}

void G_ShowTrace
	(
	trace_t *trace,
   gentity_t *passent,
	const char *reason
	)

	{
	str text;
	str pass;
	str hit;

	assert( reason );
	assert( trace );

	if ( passent )
		{
		pass = va( "'%s'(%d)", passent->entname, passent->s.number );
		}
	else
		{
		pass = "NULL";
		}

	if ( trace->ent )
		{
		hit = va( "'%s'(%d)", trace->ent->entname, trace->ent->s.number );
		}
	else
		{
		hit = "NULL";
		}

	text = va( "%0.2f : Pass %s Frac %f Hit %s : '%s'\n",
		level.time, pass.c_str(), trace->fraction, hit.c_str(), reason ? reason : "" );

   if ( sv_traceinfo->integer == 3 )
		{
		gi.DebugPrintf( text.c_str() );
		}
	else
		{
      gi.DPrintf( "%s", text.c_str() );
		}
	}

void G_CalcBoundsOfMove
   (
   Vector &start,
   Vector &end,
   Vector &mins,
   Vector &maxs,
   Vector *minbounds,
   Vector *maxbounds
   )

   {
   Vector bmin;
   Vector bmax;

   ClearBounds( bmin, bmax );
   AddPointToBounds( start, bmin, bmax );
   AddPointToBounds( end, bmin, bmax );
   bmin += mins;
   bmax += maxs;

   if ( minbounds )
      {
      *minbounds = bmin;
      }

   if ( maxbounds )
      {
      *maxbounds = bmax;
      }
   }

trace_t G_Trace
	(
	vec3_t start,
	vec3_t mins,
	vec3_t maxs,
	vec3_t end,
   gentity_t *passent,
	int contentmask,
   qboolean cylinder,
	const char *reason
	)

	{
   int entnum;
	trace_t trace;

   if ( passent )
      {
      entnum = passent->s.number;
      }
   else
      {
      entnum = ENTITYNUM_NONE;
      }

	gi.trace( &trace, start, mins, maxs, end, entnum, contentmask, cylinder );

   if ( trace.entityNum == ENTITYNUM_NONE )
      {
      trace.ent = NULL;
      }
   else
      {
      trace.ent = &g_entities[ trace.entityNum ];
      }

   if ( sv_traceinfo->integer > 1 )
		{
		G_ShowTrace( &trace, passent, reason );
		}
	sv_numtraces++;

   if ( sv_drawtrace->integer )
		{
      G_DebugLine( Vector( start ), Vector( end ), 1, 1, 0, 1 );
      }

	return trace;
	}

trace_t G_Trace
	(
	Vector &start,
	Vector &mins,
	Vector &maxs,
	Vector &end,
	Entity *passent,
	int contentmask,
   qboolean cylinder,
	const char *reason
	)

	{
   gentity_t *ent;
   int entnum;
	trace_t trace;

	assert( reason );

	if ( passent == NULL )
		{
		ent = NULL;
      entnum = ENTITYNUM_NONE;
		}
	else
		{
		ent = passent->edict;
      entnum = ent->s.number;
		}

	gi.trace( &trace, start, mins, maxs, end, entnum, contentmask, cylinder );

   if ( trace.entityNum == ENTITYNUM_NONE )
      {
      trace.ent = NULL;
      }
   else
      {
      trace.ent = &g_entities[ trace.entityNum ];
      }

   if ( sv_traceinfo->integer > 1 )
		{
		G_ShowTrace( &trace, ent, reason );
		}

   sv_numtraces++;

   if ( sv_drawtrace->integer )
		{
      G_DebugLine( start, end, 1, 1, 0, 1 );
      }

	return trace;
	}

void G_TraceEntities
	(
	Vector &start,
	Vector &mins,
	Vector &maxs,
	Vector &end,
	Container<Entity *>*victimlist,
	int contentmask
	)

	{
	trace_t trace;
	vec3_t boxmins;
	vec3_t boxmaxs;
	int num;
	int touchlist[MAX_GENTITIES];
	gentity_t *touch;
	int i;


	// Find the bounding box

	for ( i=0 ; i<3 ; i++ ) 
		{
		if ( end[i] > start[i] ) 
			{
			boxmins[i] = start[i] + mins[i] - 1;
			boxmaxs[i] = end[i] + maxs[i] + 1;
			} 
		else 
			{
			boxmins[i] = end[i] + mins[i] - 1;
			boxmaxs[i] = start[i] + maxs[i] + 1;
			}
		}

	// Find the list of entites

	num = gi.AreaEntities( boxmins, boxmaxs, touchlist, MAX_GENTITIES );

	for ( i=0 ; i<num ; i++ ) 
		{
		touch = &g_entities[ touchlist[ i ] ];
			
		// see if we should ignore this entity
		if (touch->solid == SOLID_NOT)
			continue;
      if (touch->solid == SOLID_TRIGGER)
         continue;

		gi.ClipToEntity( &trace, start, mins, maxs, end, touchlist[i], contentmask );

		if ( trace.entityNum == touchlist[i] )
			victimlist->AddObject( touch->entity );
		}
	}

/*
=======================================================================

  SelectSpawnPoint

=======================================================================
*/

/*
================
PlayersRangeFromSpot

Returns the distance to the nearest player from the given spot
================
*/
float	PlayersRangeFromSpot
	(
	Entity *spot
	)

	{
	Entity	*player;
	float		bestplayerdistance;
	Vector	v;
	int		n;
	float		playerdistance;

	bestplayerdistance = 9999999;
   for( n = 0; n < maxclients->integer; n++ )
		{
      if ( !g_entities[ n ].inuse || !g_entities[ n ].entity )
			{
			continue;
			}

      player = g_entities[ n ].entity;
		if ( player->health <= 0 )
			{
			continue;
			}

      v = spot->origin - player->origin;
		playerdistance = v.length();

		if ( playerdistance < bestplayerdistance )
			{
			bestplayerdistance = playerdistance;
			}
		}

	return bestplayerdistance;
	}

/*
================
SelectRandomDeathmatchSpawnPoint

go to a random point, but NOT the two points closest
to other players
================
*/
Entity *SelectRandomDeathmatchSpawnPoint
	(
	void
	)

	{
	Entity	*spot, *spot1, *spot2;
	int		count = 0;
	int		selection;
	float		range, range1, range2;

	spot = NULL;
	range1 = range2 = 99999;
	spot1 = spot2 = NULL;

	for( spot = G_FindClass( spot, "info_player_deathmatch" ); spot ; spot = G_FindClass( spot, "info_player_deathmatch" ) )
		{
		count++;
		range = PlayersRangeFromSpot( spot );
		if ( range < range1 )
			{
			range1 = range;
			spot1 = spot;
			}
		else if (range < range2)
			{
			range2 = range;
			spot2 = spot;
			}
		}

	if ( !count )
		{
		return NULL;
		}

	if ( count <= 2 )
		{
		spot1 = spot2 = NULL;
		}
	else
		{
		count -= 2;
		}

	selection = rand() % count;

	spot = NULL;
	do
		{
		spot = G_FindClass( spot, "info_player_deathmatch" );

      // if there are no more, break out
      if ( !spot )
         break;

		if ( spot == spot1 || spot == spot2 )
			{
			selection++;
			}
		}
	while( selection-- );

	return spot;
	}

/*
================
SelectFarthestDeathmatchSpawnPoint

================
*/
Entity *SelectFarthestDeathmatchSpawnPoint
	(
	void
	)

	{
	Entity	*bestspot;
	float		bestdistance;
	float		bestplayerdistance;
	Entity	*spot;

	spot = NULL;
	bestspot = NULL;
	bestdistance = 0;
	for( spot = G_FindClass( spot, "info_player_deathmatch" ); spot ; spot = G_FindClass( spot, "info_player_deathmatch" ) )
		{
		bestplayerdistance = PlayersRangeFromSpot( spot );
		if ( bestplayerdistance > bestdistance )
			{
			bestspot = spot;
			bestdistance = bestplayerdistance;
			}
		}

	if ( bestspot )
		{
		return bestspot;
		}

	// if there is a player just spawned on each and every start spot
	// we have no choice to turn one into a telefrag meltdown
	spot = G_FindClass( NULL, "info_player_deathmatch" );

	return spot;
	}

Entity *SelectDeathmatchSpawnPoint
	(
	void
	)

	{
	if ( DM_FLAG( DF_SPAWN_FARTHEST ) )
		{
		return SelectFarthestDeathmatchSpawnPoint();
		}
	else
		{
		return SelectRandomDeathmatchSpawnPoint();
		}
	}

/*
===========
SelectSpawnPoint

Chooses a player start, deathmatch start, etc
============
*/
void SelectSpawnPoint
	(
	Vector &org,
	Vector &ang,
   str &thread
	)

	{
	Entity *spot = NULL;

   if ( deathmatch->integer )
		{
		spot = SelectDeathmatchSpawnPoint();
		}

	// find a single player start spot
	if ( !spot )
		{
		while( ( spot = G_FindClass( spot, "info_player_start" ) ) != NULL )
			{
			if ( level.spawnpoint.icmp( spot->TargetName() ) == 0 )
				{
				break;
				}
			}

		if ( !spot && !level.spawnpoint.length() )
			{
			// there wasn't a spawnpoint without a target, so use any
			spot = G_FindClass( NULL, "info_player_start" );
			}

		if ( !spot )
         {
   		gi.Error( ERR_DROP, "No player spawn position named '%s'.  Can't spawn player.\n", level.spawnpoint.c_str() );
			}
		}

   org = spot->origin;
	ang = spot->angles;
   // 
   // see if we have a thread
   //
   if ( spot->isSubclassOf( PlayerStart ) )
      {
      thread = ( ( PlayerStart * )spot )->getThread();
      }
	}


/*
=============
M_CheckBottom

Returns false if any part of the bottom of the entity is off an edge that
is not a staircase.

=============
*/
int c_yes, c_no;

qboolean M_CheckBottom
	(
	Entity *ent
	)

	{
	Vector	mins, maxs, start, stop;
	trace_t	trace;
	int		x, y;
	float		mid, bottom;

   mins = ent->origin + ent->mins * 0.5;
   maxs = ent->origin + ent->maxs * 0.5;

	// if all of the points under the corners are solid world, don't bother
	// with the tougher checks
	// the corners must be within 16 of the midpoint
	start[ 2 ] = mins[ 2 ] - 1;

	for( x = 0; x <= 1; x++ )
		{
		for( y = 0; y <= 1; y++ )
			{
			start[ 0 ] = x ? maxs[ 0 ] : mins[ 0 ];
			start[ 1 ] = y ? maxs[ 1 ] : mins[ 1 ];
			if ( gi.pointcontents( start, 0 ) != CONTENTS_SOLID )
				{
				goto realcheck;
				}
			}
		}

	c_yes++;
	return true;		// we got out easy

realcheck:

	c_no++;

	//
	// check it for real...
	//
	start[ 2 ] = mins[ 2 ];

	// the midpoint must be within 16 of the bottom
	start[ 0 ] = stop[ 0 ] = ( mins[ 0 ] + maxs[ 0 ] ) * 0.5;
	start[ 1 ] = stop[ 1 ] = ( mins[ 1 ] + maxs[ 1 ] ) * 0.5;
	stop[ 2 ] = start[ 2 ] - 3 * STEPSIZE;//2 * STEPSIZE;

	trace = G_Trace( start, vec_zero, vec_zero, stop, ent, MASK_MONSTERSOLID, false, "M_CheckBottom 1" );

	if ( trace.fraction == 1.0 )
		{
		return false;
		}

	mid = bottom = trace.endpos[ 2 ];

	// the corners must be within 16 of the midpoint
	for( x = 0; x <= 1; x++ )
		{
		for( y = 0; y <= 1; y++ )
			{
			start[ 0 ] = stop[ 0 ] = x ? maxs[ 0 ] : mins[ 0 ];
			start[ 1 ] = stop[ 1 ] = y ? maxs[ 1 ] : mins[ 1 ];

			trace = G_Trace( start, vec_zero, vec_zero, stop, ent, MASK_MONSTERSOLID, false, "M_CheckBottom 2" );

			if ( trace.fraction != 1.0 && trace.endpos[ 2 ] > bottom )
				{
				bottom = trace.endpos[ 2 ];
				}

			if ( trace.fraction == 1.0 || mid - trace.endpos[ 2 ] > STEPSIZE )
				{
				return false;
				}
			}
		}

	c_yes++;
	return true;
	}

Entity * G_FindClass
	(
   Entity * ent,
	const char *classname
	)

	{
   int         entnum;
   gentity_t   *from;

   if ( ent )
      {
      entnum = ent->entnum;
      }
   else
      {
      entnum = -1;
      }

   for ( from = &g_entities[ entnum + 1 ]; from < &g_entities[ globals.num_entities ] ; from++ )
		{
		if ( !from->inuse )
			{
			continue;
			}
		if ( !Q_stricmp ( from->entity->getClassID(), classname ) )
			{
			return from->entity;
			}
		}

	return NULL;
	}

Entity * G_FindTarget
	(
   Entity * ent,
	const char *name
	)

	{
   Entity      *next;

   if ( name && name[ 0 ] )
      {
      next = world->GetNextEntity( str( name ), ent );
      if ( next )
			{
         return next;
			}
		}

	return NULL;
	}

Entity *G_NextEntity
	(
	Entity *ent
	)

	{
   gentity_t *from;

   if ( !g_entities )
		{
		return NULL;
		}

	if ( !ent )
		{
		from = g_entities;
		}
   else
      {
      from = ent->edict + 1;
      }

	if ( !from )
		{
		return NULL;
		}

   for ( ; from < &g_entities[ globals.num_entities ] ; from++ )
		{
		if ( !from->inuse || !from->entity )
			{
			continue;
			}

		return from->entity;
		}

	return NULL;
	}

//
// QuakeEd only writes a single float for angles (bad idea), so up and down are
// just constant angles.
//
Vector G_GetMovedir
	(
   float angle
	)

	{
	if ( angle == -1 )
		{
		return Vector( 0, 0, 1 );
		}
	else if ( angle == -2 )
		{
		return Vector( 0, 0, -1 );
		}

	angle *= ( M_PI * 2 / 360 );
	return Vector( cos( angle ), sin( angle ), 0 );
	}

/*
=================
KillBox

Kills all entities that would touch the proposed new positioning
of ent.  Ent should be unlinked before calling this!
=================
*/
qboolean KillBox
	(
	Entity *ent
	)

	{
	int		   i;
	int	   	num;
   int         touch[ MAX_GENTITIES ];
   gentity_t   *hit;
   Vector      min;
   Vector      max;
   int         fail;

   fail = 0;

   min = ent->origin + ent->mins;
   max = ent->origin + ent->maxs;

   num = gi.AreaEntities( min, max, touch, MAX_GENTITIES );

   for( i = 0; i < num; i++ )
		{
		hit = &g_entities[ touch[ i ] ];

      if ( !hit->inuse || ( hit->entity == ent ) || !hit->entity || ( hit->entity == world ) || ( !hit->entity->edict->solid ) )
			{
			continue;
			}

      hit->entity->Damage( ent, ent, hit->entity->health + 100000, ent->origin, vec_zero, vec_zero,
         0, DAMAGE_NO_PROTECTION, MOD_TELEFRAG );

		//
		// if we didn't kill it, fail
		//
		if ( hit->entity->getSolidType() != SOLID_NOT )
			{
         fail++;
			}
		}

	//
	// all clear
	//
	return !fail;
	}

qboolean IsNumeric
	(
	const char *str
	)

	{
	int len;
	int i;
	qboolean dot;

	if ( *str == '-' )
		{
		str++;
		}

	dot = false;
	len = strlen( str );
	for( i = 0; i < len; i++ )
		{
		if ( !isdigit( str[ i ] ) )
			{
			if ( ( str[ i ] == '.' ) && !dot )
				{
				dot = true;
				continue;
				}
			return false;
			}
		}

	return true;
	}

/*
=================
findradius

Returns entities that have origins within a spherical area

findradius (org, radius)
=================
*/
Entity *findradius
	(
	Entity *startent,
	Vector org,
	float rad
	)

	{
	Vector		eorg;
   gentity_t	*from;
	float			r2, distance;

	if ( !startent )
		{
		from = active_edicts.next;
      }
   else
      {
		from = startent->edict->next;
      }

	assert( from );
   if ( !from )
	   {
      return NULL;
      }

	assert( ( from == &active_edicts ) || ( from->inuse ) );

	// square the radius so that we don't have to do a square root
	r2 = rad * rad;

	for( ; from != &active_edicts; from = from->next )
	   {
		assert( from->inuse );
		assert( from->entity );

      eorg = org - from->entity->centroid;

		// dot product returns length squared
      distance = eorg * eorg;

		if ( distance <= r2 )
			{
			return from->entity;
			}
      else
         {
         // subtract the object's own radius from this distance
         distance -= from->radius2;
		   if ( distance <= r2 )
			   {
			   return from->entity;
			   }
         }
		}

	return NULL;
	}

/*
=================
findclientinradius

Returns clients that have origins within a spherical area

findclientinradius (org, radius)
=================
*/
Entity *findclientsinradius
	(
   Entity *startent,
	Vector org,
	float rad
	)

	{
	Vector	 eorg;
   gentity_t *ed;
	float		 r2;
   int       i;

   // square the radius so that we don't have to do a square root
	r2 = rad * rad;

	if ( !startent )
		{
      i = 0;
      }
   else
      {
      i = startent->entnum + 1;
      }

 	for( ; i < game.maxclients; i++ )
      {
      ed = &g_entities[ i ];

		if ( !ed->inuse || !ed->entity )
			{
			continue;
			}

      eorg = org - ed->entity->centroid;

		// dot product returns length squared
		if ( ( eorg * eorg ) <= r2 )
			{
			return ed->entity;
			}
		}

	return NULL;
	}

Vector G_CalculateImpulse
   (
   Vector start,
   Vector end,
   float speed,
   float gravity
   )

   {
   float traveltime, vertical_speed;
   Vector dir, xydir, velocity;

   dir = end - start;
   xydir = dir;
   xydir.z = 0;
   traveltime = xydir.length() / speed;
   vertical_speed = ( dir.z / traveltime ) + ( 0.5f * gravity * sv_gravity->value * traveltime );
   xydir.normalize();

   velocity = speed * xydir;
   velocity.z = vertical_speed;
   return velocity;
   }

Vector G_PredictPosition
   (
   Vector start,
   Vector target,
   Vector targetvelocity,
   float  speed
   )

   {
   Vector projected;
   float traveltime;
   Vector dir, xydir;

   dir = target - start;
   xydir = dir;
   xydir.z = 0;
   traveltime = xydir.length() / speed;
   projected = target + ( targetvelocity * traveltime );

   return projected;
   }

char *ClientTeam
   (
   gentity_t *ent
   )

   {
	static char	value[512];

	value[0] = 0;

	if (!ent->client)
		return value;

   if ( DM_FLAG( DF_MODELTEAMS ) )
      COM_StripExtension( Info_ValueForKey( ent->client->pers.userinfo, "model" ), value );
   else if ( DM_FLAG( DF_SKINTEAMS ) )
      COM_StripExtension( Info_ValueForKey( ent->client->pers.userinfo, "skin" ), value );

	return( value );
   }


qboolean OnSameTeam
   (
   Entity *ent1,
   Entity *ent2
   )

   {
	char	ent1Team [512];
	char	ent2Team [512];

	if ( !DM_FLAG( DF_MODELTEAMS | DF_SKINTEAMS ) )
		return false;

	strcpy (ent1Team, ClientTeam (ent1->edict));
	strcpy (ent2Team, ClientTeam (ent2->edict));

	if ( !strcmp( ent1Team, ent2Team ) )
		return true;

	return false;
   }

/*
==============
G_LoadAndExecScript

Like the man says...
==============
*/
qboolean G_LoadAndExecScript
   (
   const char *filename,
   const char *label,
   qboolean quiet
   )

   {
   ScriptThread *pThread;

   if ( gi.FS_ReadFile( filename, NULL, quiet ) != -1 )
		{
      if ( Director.labelExists( filename, label ) )
         {
   	   pThread = Director.CreateThread( filename, LEVEL_SCRIPT, label );
         if ( pThread )
            {
            // start right away
            pThread->StartImmediately();
            return qtrue;
            }
         else
            {
            gi.DPrintf( "G_LoadAndExecScript : %s could not create thread.\n", filename );
            return qfalse;
            }
         }
      else
         {
         if ( !quiet )
            {
            gi.DPrintf( "G_LoadAndExecScript : label %s does not exist in %s.\n", label, filename );
            }
         return qfalse;
         }
		}

   return qfalse;
   }

ScriptThread * ExecuteThread
	(
   str thread_name,
   qboolean start
	)
	{
   GameScript * s;

   if ( thread_name.length() )
      {
      ScriptThread * pThread;

   	s = ScriptLib.GetScript( ScriptLib.GetGameScript() );
      if ( !s )
         {
         gi.DPrintf( "StartThread::Null game script\n" );
         return false;
         }
	   pThread = Director.CreateThread( s, thread_name.c_str() );
      if ( pThread )
         {
         if ( start )
            {
            // start right away
            pThread->StartImmediately();
            }
         }
      else
         {
         gi.DPrintf( "StartThread::unable to go to %s\n", thread_name.c_str() );
         return NULL;
         }
      return pThread;
      }
   return NULL;
   }

/*
==============
G_ArchiveEdict
==============
*/
void G_ArchiveEdict
   (
   Archiver &arc,
   gentity_t *edict
   )

   {
   int    i;
   str    tempStr;

   assert( edict );

   //
   // this is written funny because it is used for both saving and loading
   //

   if ( edict->client )
      {
      arc.ArchiveRaw( edict->client, sizeof( *edict->client ) );
      }

   arc.ArchiveInteger( &edict->s.eType );
   arc.ArchiveInteger( &edict->s.eFlags );

   arc.ArchiveVec3( edict->s.netorigin );
   arc.ArchiveVec3( edict->s.origin );
   arc.ArchiveVec3( edict->s.origin2 );
   arc.ArchiveVec3( edict->s.netangles );
   arc.ArchiveVec3( edict->s.angles );

   arc.ArchiveInteger( &edict->s.constantLight );

	if ( arc.Saving() )
		{
		if ( edict->s.loopSound )
			tempStr = gi.getConfigstring( CS_SOUNDS + edict->s.loopSound );
		else
			tempStr = "";

		arc.ArchiveString( &tempStr );
		}
	else
		{
		arc.ArchiveString( &tempStr );

		if ( tempStr.length() )
			edict->s.loopSound = gi.soundindex( tempStr.c_str() );
		else
			edict->s.loopSound = 0;
		}

	arc.ArchiveFloat( &edict->s.loopSoundVolume );
	arc.ArchiveFloat( &edict->s.loopSoundMinDist );

   arc.ArchiveInteger( &edict->s.parent );
   arc.ArchiveInteger( &edict->s.tag_num );
   arc.ArchiveBoolean( &edict->s.attach_use_angles );
   arc.ArchiveVec3( edict->s.attach_offset );

   arc.ArchiveInteger( &edict->s.modelindex );
   arc.ArchiveInteger( &edict->s.skinNum );
   arc.ArchiveInteger( &edict->s.anim );
   arc.ArchiveInteger( &edict->s.frame );

   arc.ArchiveInteger( &edict->s.crossblend_time );

   arc.ArchiveInteger( &edict->s.torso_anim );
   arc.ArchiveInteger( &edict->s.torso_frame );
   arc.ArchiveInteger( &edict->s.torso_crossblend_time );

   for( i = 0; i < NUM_BONE_CONTROLLERS; i++ )
      {
      arc.ArchiveInteger( &edict->s.bone_tag[ i ] );
      arc.ArchiveVec3( edict->s.bone_angles[ i ] );
      arc.ArchiveVec4( edict->s.bone_quat[ i ] );
      }

   arc.ArchiveRaw( &edict->s.surfaces, sizeof( edict->s.surfaces ) );

   arc.ArchiveInteger( &edict->s.clientNum );
   arc.ArchiveInteger( &edict->s.groundEntityNum );
   arc.ArchiveInteger( &edict->s.solid );

   arc.ArchiveFloat( &edict->s.scale );
   arc.ArchiveFloat( &edict->s.alpha );
   arc.ArchiveInteger( &edict->s.renderfx );
   arc.ArchiveVec4( edict->s.quat );
   arc.ArchiveRaw( &edict->s.mat, sizeof( edict->s.mat ) );

   arc.ArchiveInteger( &edict->svflags );

   arc.ArchiveVec3( edict->mins );
   arc.ArchiveVec3( edict->maxs );
   arc.ArchiveInteger( &edict->contents );
   arc.ArchiveVec3( edict->absmin );
   arc.ArchiveVec3( edict->absmax );
   arc.ArchiveFloat( &edict->radius );
	if ( !arc.Saving() ) {
		edict->radius2 = edict->radius * edict->radius;
	}

   arc.ArchiveVec3( edict->centroid );

   arc.ArchiveVec3( edict->currentOrigin );
   arc.ArchiveVec3( edict->currentAngles );

   arc.ArchiveInteger( &edict->ownerNum );
   ArchiveEnum( edict->solid, solid_t );
   arc.ArchiveFloat( &edict->freetime );
   arc.ArchiveFloat( &edict->spawntime );

   tempStr = str( edict->entname );
   arc.ArchiveString( &tempStr );
	strncpy( edict->entname, tempStr.c_str(), sizeof( edict->entname ) - 1 );

   arc.ArchiveInteger( &edict->clipmask );

   if ( arc.Loading() )
      {
      gi.linkentity( edict );
      }
   }

/*
=========================================================================

model / sound configstring indexes

=========================================================================
*/

/*
=======================
G_FindConfigstringIndex
=======================
*/
int G_FindConfigstringIndex( char *name, int start, int max, qboolean create )
   {
	int		i;
	char	   *s;

	if ( !name || !name[0] )
      {
		return 0;
	   }

	for ( i=1 ; i<max ; i++ )
      {
		s = gi.getConfigstring( start + i );
		if ( !s || !s[0] )
         {
			break;
		   }
		if ( !strcmp( s, name ) )
         {
			return i;
		   }
	   }

	if ( !create )
      {
		return 0;
	   }

	if ( i == max )
      {
		gi.Error( ERR_DROP, "G_FindConfigstringIndex: overflow" );
	   }

	gi.setConfigstring( start + i, name );
	return i;
   }

int G_ModelIndex( char *name )
   {
	return G_FindConfigstringIndex (name, CS_MODELS, MAX_MODELS, true);
   }

int G_SoundIndex( char *name )
   {
	return G_FindConfigstringIndex (name, CS_SOUNDS, MAX_SOUNDS, true);
   }


/*
===============
G_SetTrajectory

Sets the pos trajectory for a fixed position
===============
*/
void G_SetTrajectory
   (
   gentity_t *ent,
   vec3_t org
   )

   {
	VectorCopy( org, ent->s.pos.trBase );
	ent->s.pos.trType = TR_STATIONARY;
	ent->s.pos.trTime = 0;
	ent->s.pos.trDuration = 0;
	VectorClear( ent->s.pos.trDelta );

	VectorCopy( org, ent->currentOrigin );
	VectorCopy( org, ent->s.origin );
   }

/*
===============
G_SetConstantLight

Sets the encoded constant light parameter for entities
===============
*/
void G_SetConstantLight
   (
   int * constantlight,
   float * red,
   float * green,
   float * blue,
   float * radius,
   int   * lightStyle
   )

   {
   int ir, ig, ib, iradius;

   if ( !constantlight )
      return;

	ir = (*constantlight) & 255;
	ig = ( (*constantlight) >> 8 ) & 255;
	ib = ( (*constantlight) >> 16 ) & 255;
	iradius = ( (*constantlight) >> 24 ) & 255;

   if ( red )
      {
      ir = *red * 255;
      if ( ir > 255 )
         ir = 255;
      }

   if ( green )
      {
      ig = *green * 255;
      if ( ig > 255 )
         ig = 255;
      }

   if ( blue )
      {
      ib = *blue * 255;
      if ( ib > 255 )
         ib = 255;
      }

   if ( radius )
      {
      iradius = *radius / CONSTANTLIGHT_RADIUS_SCALE;
      if ( iradius > 255 )
         iradius = 255;
      }

   if ( lightStyle )
      {
      ir = *lightStyle;
      if ( ir > 255 )
         ir = 255;
      }
   *constantlight = ( ir ) + ( ig << 8 ) + ( ib << 16 ) + ( iradius << 24 );
   }

//
// caching commands
//
int modelIndex
	(
	const char *mdl
	)
   {
   str name;

	assert( mdl );

	if ( !mdl )
		{
		return 0;
		}

	// Prepend 'models/' to make things easier
	if ( !strchr( mdl, '*' ) && !strchr( mdl, '\\' ) && !strchr( mdl, '/' ) )
		{
		name = "models/";
		}

	name += mdl;

   return gi.modelindex( name.c_str() );
   }


void CacheResource
	(
   const char * stuff,
   Entity * ent
	)

	{
	str real_stuff;

	if ( !stuff )
		return;

   if ( !strchr( stuff, '.' ) )
      {
      // must be a global alias
	   stuff = gi.GlobalAlias_FindRandom( stuff );
      if ( !stuff )
         {
         return;
         }
      }

	real_stuff = stuff;
	real_stuff.tolower();

   if ( strstr( real_stuff.c_str(), ".wav" ) )
      {
      gi.soundindex( real_stuff.c_str() );
      }
   else if ( strstr( real_stuff.c_str(), ".mp3" ) )
      {
      gi.soundindex( real_stuff.c_str() );
      }
   else if ( strstr( real_stuff.c_str(), ".tik" ) )
      {
      int index;

      index = modelIndex( real_stuff.c_str() );

      if ( index > 0 && ent )
         ent->ProcessInitCommands( index, qtrue );
      }
   else if ( strstr( real_stuff.c_str(), ".spr" ) )
      {
      gi.modelindex( real_stuff.c_str() );
      }
	else if ( strstr( real_stuff.c_str(), ".st" ) )
      {
		if ( strncmp( real_stuff.c_str(), "ai/", 3 ) == 0 )
			{
			Actor *actor = new Actor;
			CacheStatemap( stuff, ( Condition<Class> * )actor->Conditions );
			delete actor;
			}
      }
	}

void ChangeMusic
	(
   const char *current,
   const char *fallback,
   qboolean force
	)
   {
   int      j;
   gentity_t  *other;

   if ( current || fallback )
      {
	   for( j = 0; j < game.maxclients; j++ )
		   {
         other = &g_entities[ j ];
		   if ( other->inuse && other->client )
			   {
            Player *client;

            client = ( Player * )other->entity;
            client->ChangeMusic( current, fallback, force );
			   }
         }
      if ( current && fallback )
         {
         gi.DPrintf( "music set to %s with fallback %s\n", current, fallback );
         }
      }
   }

void ChangeMusicVolume
	(
   float volume,
   float fade_time
   )
   {
   int      j;
   gentity_t  *other;
   
	for( j = 0; j < game.maxclients; j++ )
		{
      other = &g_entities[ j ];
		if ( other->inuse && other->client )
			{
         Player *client;

         client = ( Player * )other->entity;
         client->ChangeMusicVolume( volume, fade_time );
			}
      }
   gi.DPrintf( "music volume set to %.2f, fade time %.2f\n", volume, fade_time );
   }

void RestoreMusicVolume
	(
   float fade_time
   )
   {
   int      j;
   gentity_t  *other;

   for( j = 0; j < game.maxclients; j++ )
		{
      other = &g_entities[ j ];
		if ( other->inuse && other->client )
			{
         Player *client;

         client = ( Player * )other->entity;
         client->RestoreMusicVolume( fade_time );
			}
      }
   }

void ChangeSoundtrack
	(
   const char * soundtrack
	)

   {   
	level.saved_soundtrack = level.current_soundtrack;
	level.current_soundtrack = soundtrack;

   gi.setConfigstring( CS_SOUNDTRACK, soundtrack );
   gi.DPrintf( "soundtrack switched to %s.\n", soundtrack );
   }

void RestoreSoundtrack
	(
	void
	)

   {
	if ( level.saved_soundtrack.length() )
		{
      level.current_soundtrack = level.saved_soundtrack;
      level.saved_soundtrack = "";
		gi.setConfigstring( CS_SOUNDTRACK, level.current_soundtrack.c_str() );
      gi.DPrintf( "soundtrack restored %s.\n", level.current_soundtrack.c_str() );
		}
   }

void G_BroadcastSound
	(
   Entity *soundent,
   Vector origin,
	float radius
	)

	{
	Sentient *ent;
	Vector	delta;
	Event		*ev;
	str		name;
   float    r2;
   float    dist2;
   int		i;
	int		n;
#if 0
	int		count;

	count = 0;
#endif

   assert( soundent );
	if ( soundent && !( soundent->flags & FL_NOTARGET ) )
		{
      r2 = radius * radius;
	   n = SentientList.NumObjects();
	   for( i = 1; i <= n; i++ )
		   {
		   ent = SentientList.ObjectAt( i );
         if ( ( ent == soundent ) || ent->deadflag )
            {
            continue;
            }

			if ( ent->isSubclassOf( Actor ) )
				{
				Actor *act = (Actor *)ent;

				if ( !act->IgnoreSounds() )
					{
					delta = origin - ent->centroid;

					// dot product returns length squared
					dist2 = delta * delta;
					if (
							( dist2 <= r2 ) &&
							(
								( soundent->edict->areanum == ent->edict->areanum ) ||
								( gi.AreasConnected( soundent->edict->areanum, ent->edict->areanum ) )
							)
						)

						{
						ev = new Event( EV_HeardSound );
						ev->AddEntity( soundent );
						ev->AddVector( origin );
						ent->PostEvent( ev, 0 );
#if 0
						count++;
#endif
						}
					}
				}
			}

#if 0
      gi.DPrintf( "Broadcast event %s to %d entities\n", ev->getName(), count );
#endif
		}
	}

void CloneEntity
   (
   Entity * dest,
   Entity * src
   )
   {
   int     i, num;

   dest->setModel( src->model );
   // don't process our init commands
   //dest->CancelEventsOfType( EV_ProcessInitCommands );
   dest->setOrigin( src->origin );
   dest->setAngles( src->angles );
   dest->setScale( src->edict->s.scale );
   dest->setAlpha( src->edict->s.alpha );
   dest->health = src->health;
   // copy the surfaces
   memcpy( dest->edict->s.surfaces, src->edict->s.surfaces, sizeof( src->edict->s.surfaces ) );
   dest->edict->s.constantLight = src->edict->s.constantLight;
   //dest->edict->s.eFlags = src->edict->s.eFlags;
   dest->edict->s.renderfx = src->edict->s.renderfx;
   dest->edict->s.anim = src->edict->s.anim;
   dest->edict->s.frame = src->edict->s.frame;

   num = src->numchildren;
   for( i = 0; ( i < MAX_MODEL_CHILDREN ) && num; i++ )
      {
      Entity * clone;
      Entity * child;

      // duplicate the children
      if ( !src->children[ i ] )
			{
         continue;
			}
      child = G_GetEntity( src->children[ i ] );
      if ( child )
         {
  			clone = new Animate;
         CloneEntity( clone, child );
         clone->attach( dest->entnum, child->edict->s.tag_num );
         }
      num--;
      }
   dest->ProcessPendingEvents();
   }

weaponhand_t WeaponHandNameToNum
   (
   str side
   )

   {
   if ( !side.length() )
      {
      gi.DPrintf( "WeaponHandNameToNum : Weapon hand not specified\n" );
      return WEAPON_ERROR;
      }

   if ( !side.icmp( "righthand" ) || !side.icmp( "right" ) ) 
      {
      return WEAPON_RIGHT;
      }
   else if ( !side.icmp( "lefthand" ) || !side.icmp( "left" ) ) 
      {
      return WEAPON_LEFT;
      }
   else if ( !side.icmp( "dualhand" ) || !side.icmp( "dual" ) ) 
      {
      return WEAPON_DUAL;
      }
   else 
      {
      return (weaponhand_t)atoi( side );
      }
   }

const char *WeaponHandNumToName
   (
   weaponhand_t hand
   )

   {
   switch( hand )
      {
      case WEAPON_RIGHT:
         return "righthand";
      case WEAPON_LEFT:
         return "lefthand";
      case WEAPON_DUAL:
         return "dualhand";
      case WEAPON_ANY:
         return "anyhand";
      default:
         return "Invalid Hand";
      }
   }

firemode_t WeaponModeNameToNum
   (
   str mode
   )

   {
   if ( !mode.length() )
      {
      gi.DPrintf( "WeaponModeNameToNum : Weapon mode not specified\n" );
      return FIRE_ERROR;
      }

   if ( !mode.icmp( "primary" ) ) 
      {
      return FIRE_PRIMARY;
      }

   if ( !mode.icmp( "alternate" ) ) 
      {
      return FIRE_ALTERNATE;
      }
   else 
      {
      return (firemode_t)atoi( mode );
      }
   }

void G_DebugTargets
   (
   Entity *e,
   str from
   )

   {
   gi.DPrintf( "DEBUGTARGETS:%s ", from.c_str() );
   
   if ( e->TargetName() && strlen( e->TargetName() ) )
      {
      gi.DPrintf( "Targetname=\"%s\"\n", e->TargetName() );
      }
   else
      {
      gi.DPrintf( "Targetname=\"None\"\n" );
      }

   if ( e->Target() && strlen( e->Target() ) )
      {
      gi.DPrintf( "Target=\"%s\"\n", e->Target() );
      }
   else
      {
      gi.DPrintf( "Target=\"None\"\n" );
      }
   }

void G_DebugDamage
   (
   float damage,
   Entity *victim,
   Entity *attacker,
   Entity *inflictor
   )

   {
   gi.DPrintf( "Victim:%s Attacker:%s Inflictor:%s Damage:%f\n", victim->getClassname(), attacker->getClassname(), inflictor->getClassname(), damage );
   }

void G_FadeOut
   (
   float delaytime
   )
   {
	// Fade the screen out
   level.m_fade_color      = Vector( 0,0,0 );
   level.m_fade_alpha      = 1.0f;
   level.m_fade_time       = delaytime;
   level.m_fade_time_start = delaytime;
   level.m_fade_type       = fadeout;
   level.m_fade_style      = alphablend;
   }

void G_AutoFadeIn
   (
   void
   )

   {
   level.m_fade_time_start = 1;
   level.m_fade_time       = 1;
   level.m_fade_color[0]   = 0;
   level.m_fade_color[1]   = 0;
   level.m_fade_color[2]   = 0;
   level.m_fade_alpha      = 1;
   level.m_fade_type       = fadein;
   level.m_fade_style      = alphablend;  
   }

void G_ClearFade
   (
   void
   )

   {
   level.m_fade_time = -1;
   level.m_fade_type = fadein;
   }

void G_FadeSound
   (
   float delaytime
   )
   {
   float time;

	// Fade the screen out
	time = delaytime * 1000;
	gi.SendServerCommand( NULL, va( "fadesound %0.2f", time ) );
   }

//
// restarts the game after delaytime
//
void G_PlayerDied
   (
   float delaytime
   )
   {
	int i;

	if ( level.died_already )
		return;

	level.died_already = true;

	// Restart the level soon

	for( i = 0; i < game.maxclients; i++ )
	   {
      if ( g_entities[ i ].inuse )
         {
         if ( g_entities[ i ].entity )
            {
            g_entities[ i ].entity->PostEvent( EV_Player_Respawn, delaytime );
            }
         }
      }

   G_FadeOut( delaytime );
   G_FadeSound( delaytime );
   }

void G_MissionFailed
   (
   void
   )

   {
	// Make the music system play the failure music for this level
   ChangeMusic( "failure", "normal", true );

   G_PlayerDied( 3 );

   // tell the player they f'd up
   gi.centerprintf( &g_entities[ 0 ], "@textures/menu/mission.tga" );

   level.mission_failed = true;
   }

void G_StartCinematic
   (
   void
   )

   {
   level.cinematic = true;
   gi.cvar_set( "sv_cinematic", "1" );
   }

void G_StopCinematic
   (
   void
   )

   {
   // clear out the skip thread
   world->skipthread = "";
   level.cinematic = false;
   gi.cvar_set( "sv_cinematic", "0" );
   }

