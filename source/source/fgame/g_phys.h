//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/g_phys.h                           $
// $Revision:: 10                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/30/00 10:45a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/g_phys.h                                $
// 
// 10    6/30/00 10:45a Markd
// added MOVETYPE_STATIONARY and revamped some physics
// 
// 9     6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 8     3/21/00 5:06p Markd
// added vehicle support
// 
// 7     2/24/00 4:17p Jimdose
// removed duplicate definition of STEPSIZE
// 
// 6     1/29/00 12:32p Jimdose
// removed MOVETYPE_HURL
// 
// 5     1/21/00 6:47p Steven
// Added a STEPMOVE_BLOCKED_BY_DOOR for AI pathfinding.
// 
// 4     1/12/00 4:31p Steven
// Added new movetype MOVETYPE_GIB.
// 
// 3     12/17/99 8:26p Jimdose
// got rid of unused vars and functions
// 
// 2     10/28/99 10:42a Aldie
// Added rope functions
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// DESCRIPTION:
// Global header file for g_phys.cpp
// 

#ifndef __G_PHYS_H__
#define __G_PHYS_H__

#include "g_local.h"
#include "entity.h"

typedef enum
	{
	STEPMOVE_OK,
	STEPMOVE_BLOCKED_BY_ENTITY,
	STEPMOVE_BLOCKED_BY_WORLD,
	STEPMOVE_BLOCKED_BY_WATER,
	STEPMOVE_BLOCKED_BY_FALL,
	STEPMOVE_BLOCKED_BY_DOOR,
	STEPMOVE_STUCK
	} stepmoveresult_t;

// movetype values
typedef enum
	{
	MOVETYPE_NONE,			// never moves
   MOVETYPE_STATIONARY, // never moves but does collide agains push objects
	MOVETYPE_NOCLIP,		// origin and angles change with no interaction
	MOVETYPE_PUSH,			// no clip to world, push on box contact
	MOVETYPE_STOP,			// no clip to world, stops on box contact
	MOVETYPE_WALK,			// gravity
	MOVETYPE_STEP,			// gravity, special edge handling
	MOVETYPE_FLY,
	MOVETYPE_TOSS,			// gravity
	MOVETYPE_FLYMISSILE,	// extra size to monsters
	MOVETYPE_BOUNCE,
   MOVETYPE_SLIDE,
   MOVETYPE_ROPE,
	MOVETYPE_GIB,
   MOVETYPE_VEHICLE
	} movetype_t;

void		G_RunEntity( Entity *ent );
void		G_Impact( Entity *e1, trace_t *trace );
qboolean	G_PushMove( Entity *pusher, Vector move, Vector amove );
void     G_CheckWater( Entity *ent );

#endif /* g_phys.h */
