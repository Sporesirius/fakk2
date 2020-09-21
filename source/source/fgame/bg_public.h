//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/bg_public.h                        $
// $Revision:: 109                                                            $
//   $Author:: Steven                                                         $
//     $Date:: 7/27/00 10:56p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/bg_public.h                             $
// 
// 109   7/27/00 10:56p Steven
// Added means of death eat.
// 
// 108   7/27/00 3:52p Aldie
// Changed over letterboxing and fades to the game code.  They are sent over in
// player stats and fields now.
// 
// 107   7/25/00 12:47p Markd
// Added new player sounds
// 
// 106   7/24/00 6:46p Steven
// Changed sv_cinematic from a cvar to a player stat.
// 
// 105   7/24/00 12:46p Markd
// fixed rope movment
// 
// 104   7/23/00 5:02p Markd
// Added boss health stat
// 
// 103   7/19/00 8:19p Steven
// Added gas blockable means of death.
// 
// 102   7/19/00 5:10p Steven
// Added electric water means of death.
// 
// 101   7/16/00 4:39p Steven
// Added a new fire means of death.
// 
// 100   7/13/00 12:33p Steven
// Added poison means of death.
// 
// 99    7/10/00 11:54p Markd
// added exit level code
// 
// 98    7/10/00 6:50p Markd
// fixed some issues with water running
// 
// 97    7/02/00 1:11p Steven
// Changed means of death light to lightsword.
// 
// 96    7/01/00 12:02p Steven
// Added electricsword and plasmashotgun means of death.
// 
// 95    6/28/00 7:55p Aldie
// Added some MOD
// 
// 94    6/26/00 5:50p Markd
// re-did some renderfx commands, fixed anti-sb juice stuff
// 
// 93    6/25/00 12:38p Markd
// added STUCK_JUMP code
// 
// 92    6/14/00 5:43p Steven
// Added plasmabeam means of death.
// 
// 91    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 90    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 89    6/13/00 3:42p Steven
// Added gib means of death.
// 
// 88    6/08/00 1:45p Steven
// Added means of death light.
// 
// 87    6/06/00 2:51p Steven
// Added sting2 means of death.
// 
// 86    6/05/00 6:42p Steven
// Added radiation means of death.
// 
// 85    6/05/00 2:24p Markd
// Added CONTENTS_CAMERACLIP to MASK_OPAQUE
// 
// 84    6/02/00 6:51p Markd
// added better camera look features
// 
// 83    5/30/00 10:59a Aldie
// Added Circle of Protection Powerup
// 
// 82    5/27/00 8:07p Markd
// Saved games 3rd pass
// 
// 81    5/22/00 5:13p Aldie
// First version of soulsucker
// 
// 80    5/20/00 5:14p Markd
// Added ITEM special effects
// 
// 79    5/15/00 2:19p Aldie
// Added new tempmodel system and added player accumulated pain
// 
// 78    5/11/00 11:08a Steven
// Added trypush to player move stuff.
// 
// 77    5/10/00 10:25a Steven
// Added firesword means of death.
// 
// 76    5/06/00 5:25p Markd
// fixed camera and pipe hang issues
// 
// 75    5/05/00 2:17p Steven
// Addec chainsword and on_fire means of death.
// 
// 74    5/04/00 12:46p Steven
// Added an axe means of death.
// 
// 73    4/27/00 12:05p Steven
// Added crush_every_frame means of death.
// 
// 72    4/27/00 11:58a Jimdose
// Changed OVERCLIP constant
// 
// 71    4/15/00 5:40p Markd
// fixed falling damage and getting into and out of water
// 
// 70    4/15/00 1:30p Markd
// added check_was_running code so that player does not always stop short
// 
// 69    4/13/00 5:46p Steven
// Added poo_explosion means of death for Vymish Mama.
// 
// 68    4/13/00 3:45p Aldie
// Added more flashbang support.  Added damage_type to entities used to specify
// what type of damage they take.
// 
// 67    4/12/00 6:57p Steven
// Added lifedrain means of death.
// 
// 66    4/10/00 4:10p Markd
// Added CONTENTS_WEAPONCLIP to weapon masks
// 
// 65    4/10/00 2:38p Markd
// eliminated the use of bg_public.h in some files
// 
// 64    4/10/00 11:16a Markd
// added rope code
// 
// 63    4/08/00 9:22a Markd
// Changed MASK_USE to include CONTENTS_BODY
// 
// 62    4/07/00 3:00p Markd
// Added legs dangling code for pipehanging
// 
// 61    4/06/00 10:59a Markd
// fixed player speed when player has full water
// 
// 60    4/05/00 7:13p Aldie
// Lots of inventory functionality changes.
// 
// 59    4/04/00 5:26p Markd
// moved static array from header into c file
// 
// 58    3/31/00 1:01p Steven
// Added vortex means of death.
// 
// 57    3/28/00 1:15p Steven
// Added means of death fire.
// 
// 56    3/23/00 12:19p Markd
// increased range of dynamic light radius
// 
// 55    3/21/00 5:06p Markd
// Added vehicle MOD
// 
// 54    3/20/00 5:00p Aldie
// Fixes for entry and exit commands
// 
// 53    3/14/00 3:22p Aldie
// Changed some client side emitter functionality and added func_emitter
// 
// 52    3/13/00 11:26a Markd
// increased maximum number of animations
// 
// 51    3/07/00 12:11p Steven
// Cleaned up means of death strings.
// 
// 50    3/04/00 11:45a Markd
// Added light style support and malloc and free to the cgame
// 
// 49    3/03/00 5:26p Steven
// Added MOD_FAST_BULLET means of death.
// 
// 48    3/02/00 4:43p Aldie
// Added some ammo functionality for the HUD
// 
// 47    2/26/00 12:51p Jimdose
// changed DEAD_VIEWHEIGHT
// 
// 46    2/24/00 4:17p Jimdose
// moved some defines from bg_pmove.cpp
// 
// 45    2/22/00 11:30a Steven
// Added means of death MOD_BULLET.
// 
// 44    2/21/00 7:03p Markd
// Added skyalpha support
// 
// 43    2/17/00 4:19p Jimdose
// added prototype for Pmove_GroundTrace
// 
// 42    2/15/00 8:58p Jimdose
// added moveresult
// 
// 41    2/14/00 5:37p Jimdose
// removed ANIM_BLEND_TORSO
// 
// 40    2/12/00 3:24p Jimdose
// renamed ANIM_BLEND_TORSO to ANIM_BLEND
// 
// 39    2/10/00 2:56p Markd
// changed FRAME_EXPLICIT mask from 128 to 512.
// 
// 38    2/04/00 6:35p Markd
// Made animations dynamically allocated when loaded, fixed up messaging system
// to handle up to 1024 for each animation
// 
// 37    1/29/00 2:48p Aldie
// Added impact mark functionality and Decal class
// 
// 36    1/27/00 11:35a Markd
// Fixed solid/notsolid client side entities
// 
// 35    1/19/00 7:14p Markd
// made camera's clip to all forms of water
// 
// 34    1/19/00 6:37p Steven
// Added a MOD_NONE to fix some problems when a means of death is not
// specified.
// 
// 33    1/19/00 10:44a Markd
// Cleaned up MOD messages and fixed music starting because of falling damage
// 
// 32    1/19/00 10:23a Steven
// Added a sling means of death.
// 
// 31    1/15/00 3:57p Markd
// Added MASK_USABLE
// 
// 30    1/12/00 8:03p Markd
// Added Camera Cut bit
// 
// 29    1/11/00 7:45p Aldie
// added water level
// 
// 28    1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 27    1/03/00 5:08p Markd
// put in camera offsets for player and state machine
// 
// 26    12/17/99 8:26p Jimdose
// got rid of unused vars and functions
// 
// 25    12/11/99 5:51p Markd
// First wave of bug fixes after q3a gold merge
// 
// 24    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 23    12/03/99 7:02p Aldie
// More ammo joy
// 
// 22    12/02/99 6:53p Aldie
// Changed naming conventions from "both" to "dualhanded"  Also put in the
// inventory renderer for the hud file
// 
// 21    12/01/99 11:26a Aldie
// Couple of fixes for emitters and more ammo stuff
// 
// 20    11/22/99 6:46p Aldie
// Started working on ammo changes - will finish after Thanksgiving break
// 
// 19    11/10/99 6:08p Steven
// Added the sting means of death.
// 
// 18    11/10/99 2:19p Jimdose
// added ANIM_BLEND_TORSO flag
// 
// 17    10/29/99 7:16p Aldie
// Updated rope stuff
// 
// 16    10/27/99 10:23a Steven
// Added new flag PMF_NO_MOVE and new contents type CONTENTS_SHOOTABLE_ONLY..
// 
// 15    10/19/99 7:52p Markd
// Removed three part model system
// 
// 14    10/18/99 1:59p Aldie
// Lots of fixes for beams and stuff
// 
// 13    10/12/99 6:56p Markd
// Fixed some player interpolation bugs and also interpolated camera
// 
// 12    10/12/99 2:23p Markd
// Rewrote camera and player movetype system
// 
// 11    10/08/99 2:11p Markd
// Re-ordered PM_TYPES
// 
// 10    10/07/99 3:08p Aldie
// more beam fun
// 
// 9     10/06/99 5:37p Jimdose
// updated tag bits to support the number of bones skeletal models can have
// added TAG_NUMBITS
// 
// 8     9/30/99 4:37p Aldie
// Added ET_SPRITE
// 
// 7     9/29/99 11:52a Markd
// removed some unused enums and variables form shared headers between cgame
// and fgame
// 
// 6     9/27/99 5:44p Markd
// began documentation and cleanup phase after merge
// 
// 5     9/16/99 12:27p Aldie
// code merge
// 
// 4     9/13/99 4:22p Jimdose
// merge
// 
// 3     9/10/99 6:51p Aldie
// restored trace function to new calling method
// 
// 2     9/10/99 5:24p Aldie
// Merge code
// 
// 1     9/10/99 10:53a Jimdose
// 
// 2     9/09/99 3:30p Aldie
// Merge
// 
// 1     9/08/99 3:15p Aldie
// 
// 22    9/01/99 5:46p Aldie
// Fixed some weapon stuff for ECTS
// 
// 21    8/31/99 2:45p Steven
// Added sword and plasma means of death.
// 
// 20    8/29/99 8:09p Markd
// fixed up monstersolid and camerasolid MASK's
// 
// 19    8/18/99 3:28p Jimdose
// added cylindrical collision detection
// 
// 18    8/11/99 5:57p Steven
// Added acid means of death.
// 
// 17    8/04/99 10:49a Steven
// Added gas as a new means of death.
// 
// 16    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
//
// DESCRIPTION:
// Definitions shared by both the server game and client game modules

#ifndef __BG_PUBLIC_H__
#define __BG_PUBLIC_H__

#ifdef __cplusplus
extern "C" {
#endif

// because games can change separately from the main system version, we need a
// second version that must match between game and cgame
#define	GAME_VERSION		"fakk-base-1"

#define DEFAULT_GRAVITY 800

// CS_SERVERINFO and CS_SYSTEMINFO and CS_NAME are defined in q_shared.h
#define	CS_SOUNDTRACK	      8
#define  CS_FOGINFO  		   9
#define  CS_SKYINFO  		   10
#define	CS_GAME_VERSION		11
#define	CS_LEVEL_START_TIME	12		// so the timer only shows the current level
#define	CS_MODELS			   32
#define	CS_SOUNDS			   (CS_MODELS+MAX_MODELS)
#define  CS_IMAGES            (CS_SOUNDS+MAX_SOUNDS)
#define  CS_LIGHTSTYLES	      (CS_IMAGES+MAX_IMAGES)
#define	CS_PLAYERS			   (CS_LIGHTSTYLES+MAX_LIGHTSTYLES)
#define  CS_ITEMS             (CS_PLAYERS+MAX_CLIENTS) // strings for item names
#define  CS_AMMO              (CS_ITEMS+MAX_ITEMS)     // strings for ammo names
#define  CS_LOCATIONS	      (CS_AMMO+MAX_AMMO)
#define  CS_MAX				   (CS_LOCATIONS+MAX_LOCATIONS)

#if (CS_MAX) > MAX_CONFIGSTRINGS
#error overflow: (CS_MAX) > MAX_CONFIGSTRINGS
#endif

typedef enum {
	GT_FFA,				// free for all
	GT_TOURNAMENT,		// one on one tournament
	GT_SINGLE_PLAYER,	// single player tournament

	//-- team games go after this --

	GT_TEAM,		   	// team deathmatch
	GT_CTF,				// capture the flag

	GT_MAX_GAME_TYPE
} gametype_t;


//
// scale to use when evaluating constantLight scale
//
#define CONSTANTLIGHT_RADIUS_SCALE 8

/*
===================================================================================

PMOVE MODULE

The pmove code takes a player_state_t and a usercmd_t and generates a new player_state_t
and some other output data.  Used for local prediction on the client game and true
movement on the server game.
===================================================================================
*/

#define	MAX_CLIP_PLANES	   5
#define	MIN_WALK_NORMAL	   0.7f		   // can't walk on very steep slopes

#define	STEPSIZE		         31

#define  MINS_X               -15
#define  MINS_Y               -15
#define  MAXS_X               15
#define  MAXS_Y               15

#define	MINS_Z				   0
#define  MAXS_Z               96

#define  DEAD_MINS_Z          32
#define  CROUCH_MAXS_Z        49
#define	DEFAULT_VIEWHEIGHT	90
#define  CROUCH_VIEWHEIGHT	   45
#define	DEAD_VIEWHEIGHT		90

#define  WATER_TURBO_SPEED    1.35f
#define  WATER_TURBO_TIME     1200
#define  MINIMUM_RUNNING_TIME 800
#define  MINIMUM_WATER_FOR_TURBO  90

#define	OVERCLIP		         1.001f

typedef enum {
	PM_NORMAL,		   // normal movement mode
   PM_NOCLIP,		   // noclip movement
	PM_DEAD		      // no acceleration or turning, but free falling
} pmtype_t;

// entityState_t->event values
// entity events are for effects that take place reletive
// to an existing entities origin.  Very network efficient.
typedef enum {
   EV_NONE,

   EV_FALL_SHORT,
   EV_FALL_MEDIUM,
   EV_FALL_FAR,
   EV_FALL_FATAL,
   EV_TERMINAL_VELOCITY,

   EV_WATER_TOUCH,   // foot touches
   EV_WATER_LEAVE,   // foot leaves
   EV_WATER_UNDER,   // head touches
   EV_WATER_CLEAR,   // head leaves

   EV_LAST_PREDICTED      // just a marker point

   // events generated by non-players or never predicted
} entity_event_t;

// pmove->pm_flags
#define	PMF_DUCKED			   ( 1<<0 )    // player is ducked
#define	PMF_TIME_LAND		   ( 1<<1 )		// pm_time is time before rejump
#define	PMF_TIME_KNOCKBACK	( 1<<2 )		// pm_time is an air-accelerate only time
#define	PMF_TIME_WATERJUMP	( 1<<3 )		// pm_time is waterjump
#define  PMF_TIME_TELEPORT    ( 1<<4 )    // pm_time is teleport
#define  PMF_NO_PREDICTION    ( 1<<5 )    // no prediction
#define  PMF_FROZEN           ( 1<<6 )    // player cannot move or look around
#define  PMF_INTERMISSION     ( 1<<7 )    // intermission view

//
// the following flag is required by the server and cannot be changed
//
#define  PMF_CAMERA_VIEW      ( 1<<8 )    // use camera view instead of ps view

#define  PMF_NO_MOVE          ( 1<<9 )    // player cannot move but can still look around
#define  PMF_LEGS_LIFTED      ( 1<<10 )   // player has pulled up his legs so that he occupies only the top of his bounding box
#define	PMF_TIME_STUCKJUMP	( 1<<11 )	// pm_time is stuckjump
#define  PMF_LEVELEXIT        ( 1<<12 )   // player is near an exit
#define  PMF_NO_GRAVITY       ( 1<<13 )   // do not apply gravity to the player

#define	PMF_ALL_TIMES	(PMF_TIME_WATERJUMP|PMF_TIME_LAND|PMF_TIME_KNOCKBACK|PMF_TIME_TELEPORT|PMF_TIME_STUCKJUMP)

#define	MAXTOUCH	32

#define  MOVERESULT_NONE     0            // nothing blocking
#define  MOVERESULT_TURNED   1            // move blocked, but player turned to avoid it
#define  MOVERESULT_BLOCKED  2            // move blocked by slope or wall
#define  MOVERESULT_HITWALL  3            // player ran into wall

typedef struct {
   // state (in / out)
	playerState_t	*ps;

	// command (in)
	usercmd_t	cmd;
	int			tracemask;			// collide against these types of surfaces
	int			debugLevel;			// if set, diagnostic output will be printed
	qboolean	   noFootsteps;		// if the game is setup for no footsteps by the server

	// results (out)
	int			numtouch;
	int			touchents[MAXTOUCH];

   int         moveresult;       // indicates whether 2the player's movement was blocked and how

	qboolean	   stepped;		      // made a non-smooth step that can be
									      // smoothed on the client side

	int			pmoveEvent;			// events predicted on client side
	vec3_t		mins, maxs;			// bounding box size
	int			watertype;
	int			waterlevel;

	// callbacks to test the world
	// these will be different functions during game and cgame
	void        (*trace)( trace_t *result, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask, qboolean cylinder );
	int			(*pointcontents)( const vec3_t point, int passEntityNum );
	qboolean		(*trypush)( int entnum, vec3_t move_origin, vec3_t move_end );
} pmove_t;

// if a full pmove isn't done on the client, you can just update the angles
void PM_UpdateViewAngles( playerState_t *ps, const usercmd_t *cmd );
void Pmove_GroundTrace( pmove_t *pmove );
void Pmove (pmove_t *pmove);

//===================================================================================

// content masks
#define	MASK_ALL				(-1)
#define	MASK_SOLID				(CONTENTS_SOLID)
#define	MASK_USABLE				(CONTENTS_SOLID|CONTENTS_BODY)
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_BODY)
#define	MASK_DEADSOLID			(CONTENTS_SOLID|CONTENTS_PLAYERCLIP)
#define	MASK_MONSTERSOLID		(CONTENTS_SOLID|CONTENTS_MONSTERCLIP|CONTENTS_BODY)
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_LAVA|CONTENTS_SLIME)
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA|CONTENTS_CAMERACLIP)
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_BODY|CONTENTS_CORPSE|CONTENTS_WEAPONCLIP|CONTENTS_SHOOTABLE_ONLY)
#define	MASK_PROJECTILE		(CONTENTS_SOLID|CONTENTS_BODY|CONTENTS_CORPSE|CONTENTS_WEAPONCLIP|CONTENTS_SHOOTABLE_ONLY)
#define	MASK_MELEE     		(CONTENTS_SOLID|CONTENTS_BODY|CONTENTS_CORPSE|CONTENTS_WEAPONCLIP|CONTENTS_SHOOTABLE_ONLY)
#define	MASK_PATHSOLID		   (CONTENTS_SOLID|CONTENTS_MONSTERCLIP)
#define	MASK_CAMERASOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_CAMERACLIP|CONTENTS_BODY|MASK_WATER)
#define  MASK_CURRENT		   (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// player_state->persistant[] indexes
// these fields are the only part of player_state that isn't
// cleared on respawn
typedef enum {
	PERS_SCORE,						// !!! MUST NOT CHANGE, SERVER AND GAME BOTH REFERENCE !!!
   PERS_TEAM
} persEnum_t;

// entityState_t->eFlags
#define	EF_EVENT_BIT1		0x00000001		// toggled every time an event changes
#define	EF_EVENT_BIT2		0x00000002		// toggled every time an event changes
#define	EF_EVENT_BITS	(EF_EVENT_BIT1|EF_EVENT_BIT2)
#define	EF_TELEPORT_BIT	(1<<2)   		// toggled every time the origin abruptly changes
#define  EF_EVERYFRAME  	(1<<3)    		// def commands will be run every client frame
#define  EF_ANTISBJUICE  	(1<<4)    		// anti sucknblow juice
#define  EF_LEFT_TARGETED  (1<<5)         // this entity is being targeted by the left hand
#define  EF_RIGHT_TARGETED (1<<6)         // this entity is being targeted by the right hand
#define  EF_DONT_PROCESS_COMMANDS (1<<7)  // don't process client commands for this entity

// flip the togglebit every time an animation
// changes so a restart of the same anim can be detected
#define	ANIM_TOGGLEBIT		(1<<9)
#define	ANIM_BLEND        (1<<10)
#define  ANIM_NUMBITS      11

// server side anim bits
#define  ANIM_SERVER_EXITCOMMANDS_PROCESSED (1<<12)

#define  ANIM_MASK         ( ~( ANIM_TOGGLEBIT | ANIM_BLEND | ANIM_SERVER_EXITCOMMANDS_PROCESSED ) )

// if FRAME_EXPLICIT is set, don't auto animate
#define	FRAME_EXPLICIT	   512
#define  FRAME_MASK        ( ~FRAME_EXPLICIT )

//
// Tag specific flags
//
#define TAG_NUMBITS        10                    // number of bits required to send over network
#define TAG_MASK           ( ( 1 << 10 ) - 1 )


//
// Camera Flags
//
#define CF_CAMERA_ANGLES_ABSOLUTE      ( 1 << 0 )
#define CF_CAMERA_ANGLES_IGNORE_PITCH  ( 1 << 1 )
#define CF_CAMERA_ANGLES_IGNORE_YAW    ( 1 << 2 )
#define CF_CAMERA_ANGLES_ALLOWOFFSET   ( 1 << 3 )
#define CF_CAMERA_CUT_BIT              ( 1 << 7 ) // this bit gets toggled everytime we do a hard camera cut

typedef enum {
   MOD_NONE,
   MOD_DROWN,
   MOD_SUICIDE,
   MOD_CRUSH,
	MOD_CRUSH_EVERY_FRAME,
   MOD_TELEFRAG,
   MOD_LAVA,
   MOD_SLIME,
   MOD_FALLING,
   MOD_LAST_SELF_INFLICTED,
   MOD_EXPLOSION,
   MOD_EXPLODEWALL,
   MOD_ELECTRIC,
	MOD_ELECTRICWATER,
   MOD_THROWNOBJECT,
   MOD_BEAM,
   MOD_ROCKET,
   MOD_IMPACT,
	MOD_GAS,
	MOD_GAS_BLOCKABLE,
	MOD_ACID,
	MOD_SWORD,
	MOD_PLASMA,
	MOD_PLASMABEAM,
	MOD_PLASMASHOTGUN,
	MOD_STING,
	MOD_STING2,
	MOD_SLING,
	MOD_BULLET,
	MOD_FAST_BULLET,
   MOD_VEHICLE,
	MOD_FIRE,
	MOD_FIRE_BLOCKABLE,
	MOD_VORTEX,
	MOD_LIFEDRAIN,
   MOD_FLASHBANG,
	MOD_POO_EXPLOSION,
	MOD_AXE,
	MOD_CHAINSWORD,
	MOD_ON_FIRE,
	MOD_FIRESWORD,
	MOD_ELECTRICSWORD,
   MOD_CIRCLEOFPROTECTION,
	MOD_RADIATION,
	MOD_LIGHTSWORD,
	MOD_GIB,
   MOD_IMPALE,
   MOD_UPPERCUT,
	MOD_POISON,
	MOD_EAT,

	MOD_TOTAL_NUMBER
   } meansOfDeath_t;

// If you add to the enum above go add a string to the means_of_death_strings in g_utils.cpp
extern char means_of_death_strings[ MOD_TOTAL_NUMBER ][ 32 ];

//---------------------------------------------------------


// g_dmflags->integer flags

#define DF_NO_HEALTH				(1<<0)
#define DF_NO_POWERUPS   		(1<<1)
#define DF_WEAPONS_STAY			(1<<2)
#define DF_NO_FALLING			(1<<3)
#define DF_INSTANT_ITEMS		(1<<4)
#define DF_SAME_LEVEL			(1<<5)
#define DF_SKINTEAMS				(1<<6)
#define DF_MODELTEAMS			(1<<7)
#define DF_FRIENDLY_FIRE		(1<<8)
#define DF_SPAWN_FARTHEST		(1<<9)
#define DF_FORCE_RESPAWN		(1<<10)
#define DF_NO_ARMOR				(1<<11)
#define DF_FAST_WEAPONS			(1<<12)
#define DF_NOEXIT             (1<<13)
#define DF_INFINITE_AMMO      (1<<14)
#define DF_FIXED_FOV          (1<<15)
#define DF_NO_DROP_WEAPONS    (1<<16)
#define DF_NO_FOOTSTEPS			(1<<17)

// teamflags->integer flags
#define TF_TEAMPLAY				1
#define TF_NO_FRIENDLY_FIRE	2

//
// entityState_t->eType
//
typedef enum {
   ET_MODELANIM,
	ET_PLAYER,
	ET_ITEM,
	ET_GENERAL,
	ET_MISSILE,
	ET_MOVER,
	ET_BEAM,
   ET_MULTIBEAM,
   ET_SPRITE,
	ET_PORTAL,
	ET_EVENT_ONLY,
   ET_RAIN,
   ET_LEAF,
	ET_SPEAKER,
	ET_PUSH_TRIGGER,
	ET_TELEPORT_TRIGGER,
   ET_DECAL,
   ET_EMITTER,
   ET_ROPE,
   ET_EVENTS
} entityType_t;

void	EvaluateTrajectory( const trajectory_t *tr, int atTime, vec3_t result );
void	EvaluateTrajectoryDelta( const trajectory_t *tr, int atTime, vec3_t result );

// Added for FAKK

typedef enum
   {
   STAT_HEALTH,
   STAT_DEAD_YAW,          // cleared each frame
   STAT_AMMO_LEFT,         // ammo in current weapon in left hand or primary ammo in 2 handed weapons
   STAT_AMMO_RIGHT,        // ammo in current weapon in right hand or alternate ammo in 2 handed weapons
   STAT_CLIPAMMO_LEFT,     // ammo in left weapon clip
   STAT_CLIPAMMO_RIGHT,    // ammo in right weapon clip
   STAT_WATER_LEVEL, 
   STAT_MAXAMMO_LEFT,      // maxammo for left weapon
   STAT_MAXAMMO_RIGHT,     // maxammo for right weapon
   STAT_MAXCLIPAMMO_LEFT,  // maxammo in left weapon clip
   STAT_MAXCLIPAMMO_RIGHT, // maxammo in right weapon clip
   STAT_LAST_PAIN,         // Last amount of damage the player took
   STAT_ACCUMULATED_PAIN,  // Accumulated damage
   STAT_BOSSHEALTH,        // if we are fighting a boss, how much health he currently has
	STAT_CINEMATIC,			// This is set when we go into cinematics
   STAT_ADDFADE,           // This is set when we need to do an addblend for the fade
   STAT_LETTERBOX,         // This is set to the fraction of the letterbox
   STAT_LAST_STAT
   } playerstat_t
   ;

#define MAX_LETTERBOX_SIZE        0x7fff

#define ITEM_NAME_AMMO_LEFT       0
#define ITEM_NAME_AMMO_RIGHT      1
#define ITEM_NAME_WEAPON_LEFT     2
#define ITEM_NAME_WEAPON_RIGHT    3
#define ITEM_NAME_WEAPON_DUAL     4

#ifdef __cplusplus
   }
#endif

#endif // __BG_PUBLIC_H__

