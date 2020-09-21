//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/gamecvars.h                        $
// $Revision:: 17                                                             $
//     $Date:: 7/22/00 3:02p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/gamecvars.h                             $
// 
// 17    7/22/00 3:02p Steven
// Added boss health bar stuff.
// 
// 16    7/17/00 3:40p Steven
// Removed sv_gore stuff.
// 
// 15    7/17/00 3:26p Aldie
// Fix for flashbangs, changed detail variable, and added forcetorsostate
// 
// 14    7/14/00 10:04p Aldie
// Added g_logstats cvar
// 
// 13    7/14/00 9:52p Markd
// added global volume dampener on ambient sound effects for cinematics
// 
// 12    7/12/00 6:34p Aldie
// Added in crosshair scaling for long distances
// 
// 11    6/13/00 6:46p Aldie
// Added some damage debug info.  Added an ignoreEnt for explosion events
// 
// 10    6/03/00 3:46p Aldie
// Added in g_debugtargets for debugging targetnames and targets
// 
// 9     5/10/00 10:37a Steven
// Added com_blood.
// 
// 8     5/08/00 3:19p Aldie
// Added initial crosshair work
// 
// 7     3/15/00 2:04p Markd
// fixed up camera node system and added new debug oriented circle
// 
// 6     3/06/00 8:07p Markd
// cleaned up unused cvar's
// 
// 5     2/09/00 8:02p Aldie
// Added loopfire weapons
// 
// 4     2/01/00 8:13p Aldie
// More autoaim work
// 
// 3     1/19/00 7:46p Aldie
// Fixed func_spawns of various types and removed some unused misc classes
// 
// 2     1/06/00 11:08p Jimdose
// cleaning up unused code
//
// DESCRIPTION:
// 

#ifndef __GAMECVARS_H__
#define __GAMECVARS_H__

#include "g_local.h"

extern	cvar_t	*developer;
extern	cvar_t	*deathmatch;
extern	cvar_t	*dmflags;
extern	cvar_t	*skill;
extern	cvar_t	*fraglimit;
extern	cvar_t	*timelimit;
extern	cvar_t	*password;
extern	cvar_t	*filterban;
extern	cvar_t	*flood_msgs;
extern	cvar_t	*flood_persecond;
extern	cvar_t	*flood_waitdelay;
extern	cvar_t	*maxclients;
extern	cvar_t	*maxentities;
extern	cvar_t	*nomonsters;
extern	cvar_t	*precache;
extern	cvar_t	*dedicated;
extern	cvar_t	*detail;
extern	cvar_t	*com_blood;
extern   cvar_t   *whereami;
extern   cvar_t   *bosshealth;

extern	cvar_t	*sv_maxvelocity;
extern	cvar_t	*sv_gravity;
extern	cvar_t	*sv_rollspeed;
extern	cvar_t	*sv_rollangle;
extern	cvar_t	*sv_cheats;
extern	cvar_t	*sv_showbboxes;
extern	cvar_t	*sv_showcameras;
extern	cvar_t	*sv_showentnums;
extern	cvar_t	*sv_stopspeed;
extern	cvar_t	*sv_friction;
extern	cvar_t	*sv_waterfriction;
extern	cvar_t	*sv_waterspeed;
extern	cvar_t	*sv_traceinfo;
extern	cvar_t	*sv_drawtrace;
extern	cvar_t	*sv_fps;
extern   cvar_t   *sv_cinematic;

extern	cvar_t	*csys_posx;
extern	cvar_t	*csys_posy;
extern	cvar_t	*csys_posz;
extern	cvar_t	*csys_x;
extern	cvar_t	*csys_y;
extern	cvar_t	*csys_z;
extern	cvar_t	*csys_draw;

extern	cvar_t	*g_showmem;
extern	cvar_t	*g_timeents;
extern	cvar_t	*g_showaxis;
extern	cvar_t	*g_showgravpath;
extern	cvar_t	*g_showplayerstate;
extern	cvar_t	*g_showplayeranim;
extern   cvar_t   *g_showbullettrace;
extern	cvar_t	*g_legswingspeed;
extern	cvar_t	*g_legclampangle;
extern	cvar_t	*g_legclamptolerance;
extern	cvar_t	*g_legtolerance;
extern	cvar_t	*g_numdebuglines;
extern	cvar_t	*g_playermodel;
extern	cvar_t	*g_statefile;
extern	cvar_t	*g_showautoaim;
extern	cvar_t	*g_crosshair;
extern	cvar_t	*g_crosshair_maxscale;
extern   cvar_t   *g_debugtargets;
extern   cvar_t   *g_debugdamage;
extern	cvar_t	*s_debugmusic;
extern	cvar_t	*g_logstats;

void CVAR_Init( void );

#endif /* !__GAMECVARS_H__ */
