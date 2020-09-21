//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/q_shared.h                         $
// $Revision:: 118                                                            $
//   $Author:: Aldie                                                          $
//     $Date:: 8/22/00 11:26a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/q_shared.h                              $
// 
// 118   8/22/00 11:26a Aldie
// version number change
// 
// 117   8/21/00 6:13p Aldie
// Changed version to 1.02a
// 
// 116   8/08/00 11:00a Markd
// increased version to 1.01
// 
// 115   7/28/00 3:12p Markd
// increased version to 1.00
// 
// 114   7/28/00 2:37a Markd
// upped version to 0.98
// 
// 113   7/28/00 2:39a Aldie
// Added notimecheck anim flag, and handle it in cg_modelanim to help with
// jittering on crossblending
// 
// 112   7/27/00 3:52p Aldie
// Changed over letterboxing and fades to the game code.  They are sent over in
// player stats and fields now.
// 
// 111   7/27/00 2:05a Markd
// increased version to 0.95
// 
// 110   7/24/00 11:15p Markd
// increased version to 0.90
// 
// 109   7/22/00 9:06p Markd
// Added CHAN_MENU
// 
// 108   7/22/00 12:16a Markd
// increased version to 0.8
// 
// 107   7/18/00 4:28p Markd
// increased version number
// 
// 106   7/17/00 4:58p Markd
// Added CVAR_SOUND_LATCH
// 
// 105   7/14/00 10:20p Aldie
// Added short version
// 
// 104   7/14/00 9:53p Markd
// increased version to 0.60
// 
// 103   7/13/00 8:46p Markd
// Increased version to 0.55
// 
// 102   7/11/00 11:09p Markd
// increased version to 0.5
// 
// 101   7/07/00 9:24p Markd
// increased version to 0.4
// 
// 100   7/05/00 9:55p Markd
// increased version to 0.3
// 
// 99    7/02/00 6:57p Markd
// Increased version number
// 
// 98    7/02/00 11:56a Aldie
// Added some functionality for resolution changing
// 
// 97    6/30/00 9:28p Markd
// increased version to 0.2
// 
// 96    6/29/00 10:02p Markd
// increased version number
// 
// 95    6/26/00 5:50p Markd
// re-did some renderfx commands, fixed anti-sb juice stuff
// 
// 94    6/19/00 5:55p Aldie
// Added support for invisible models that are lit only by negative intensity
// lights
// 
// 93    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 92    6/12/00 9:23p Markd
// Added refeshable image support, rewrote screenshots, added loadsave
// functionality
// 
// 91    6/09/00 2:24p Steven
// Work to get bound entites to always get sent over if the entity they are
// bound to is.
// 
// 90    6/06/00 12:19p Markd
// working on player movement
// 
// 89    6/04/00 6:03p Markd
// Added precise shadow support
// 
// 88    5/27/00 8:07p Markd
// Saved games 3rd pass
// 
// 87    5/18/00 3:21p Markd
// changed to version 0.1
// 
// 86    5/08/00 1:09p Steven
// Fixed a nasty messaging bug in server sounds (1 bit too short).
// 
// 85    5/05/00 11:28a Markd
// updated RF_FLAGS_NOT_INHERITED
// 
// 84    4/10/00 6:09p Steven
// Added RF_DONT_PROCESS_COMMANDS.
// 
// 83    4/05/00 7:13p Aldie
// Lots of inventory functionality changes.
// 
// 82    4/01/00 2:02p Markd
// Added BoundsClear function
// 
// 81    3/29/00 11:51a Markd
// Increased to version 0.05
// 
// 80    3/28/00 4:25p Aldie
// Some more beam changes for Pat
// 
// 79    3/28/00 3:16p Aldie
// Fixed some beam problems for Pat
// 
// 78    3/22/00 5:21p Markd
// increased to version 0.04
// 
// 77    3/20/00 6:38p Markd
// Added damage_angles
// 
// 76    3/20/00 6:11p Steven
// Incremented NUM_BONE_CONTROLLERS so that player could have a mouth  bone
// controller.
// 
// 75    3/04/00 11:47a Markd
// Added lightstyles, RF_ADDITIVE_DLIGHT and RF_LIGHTSTYLE_DLIGHT
// 
// 74    3/02/00 10:43a Steven
// Changed reverb interface.
// 
// 73    3/02/00 9:28a Markd
// Added reverb mode conversion routines
// 
// 72    2/29/00 12:23p Aldie
// Added BEAM_OFFSET_ENDPOINTS flag
// 
// 71    2/23/00 3:19p Aldie
// Added more inventory functionality with the player
// 
// 70    2/18/00 6:41p Markd
// Added CROSSBLEND flag
// 
// 69    2/17/00 7:13p Markd
// Increased version to 0.03
// 
// 68    2/17/00 4:16p Jimdose
// added walking, groundPlane, and groundTrace to playerstate_t so that player
// could have more info on why moves failed.
// 
// 67    2/14/00 7:34p Aldie
// Fixed some beam rendering issues
// 
// 66    2/12/00 3:46p Markd
// Added LEFT_TARGETED and RIGHT_TARGETED RF flags
// 
// 65    2/11/00 10:34a Markd
// Added pm_runtime member to playerstate
// 
// 64    1/29/00 12:21p Markd
// rewrote tiki loading temp storage routines
// 
// 63    1/27/00 12:15p Markd
// added fullbright support and minlight support to all lighting functions
// 
// 62    1/26/00 3:34p Markd
// Added Renderfx mask for inherited entities
// 
// 61    1/24/00 6:52p Steven
// Added reverb stuff.
// 
// 60    1/22/00 12:00p Jimdose
// added __Q_FABS__ to indicate that Q_fabs is defined
// 
// 59    1/21/00 10:23a Markd
// Increased version from 0.01 to 0.02
// 
// 58    1/15/00 5:07p Jimdose
// added OrientCopy, OrientClear, QuatCopy, QuatSet
// 
// 57    1/15/00 4:13p Jimdose
// created ClearOrientation macro
// 
// 56    1/13/00 2:09p Jimdose
// 
// 55    1/10/00 11:06a Markd
// increased max models
// 
// 54    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 53    12/17/99 8:27p Jimdose
// got rid of unused vars and functions
// 
// 52    12/17/99 7:09p Markd
// Added developer 2 support
// 
// 51    12/11/99 6:44p Markd
// second run-through of q3a merge, got the entire project to build without
// errors or warnings
// 
// 50    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 49    12/09/99 7:38p Jimdose
// moved  Animation flags from qfiles.h
// 
// 48    12/01/99 11:26a Aldie
// Couple of fixes for emitters and more ammo stuff
// 
// 47    11/29/99 6:32p Aldie
// Lots of changes for ammo system
// 
// 46    11/17/99 12:17p Markd
// Took out RF_NOSHADOW flag
// 
// 45    11/15/99 12:46p Markd
// Added LerpAnglesFromCurrent
// 
// 44    11/15/99 12:43p Markd
// Increased precision of fov in playerstate
// 
// 43    11/10/99 2:19p Jimdose
// added torso animation control variables to entityState_t
// 
// 42    11/02/99 5:45p Steven
// Added level wide sound stuff.
// 
// 41    10/29/99 7:20p Aldie
// Added rope stuff
// 
// 40    10/29/99 6:49p Jimdose
// added bone controllers
// 
// 39    10/28/99 6:06p Steven
// Added a use_angles flag and an offset to the entity attach stuff.
// 
// 38    10/27/99 12:19p Markd
// added smooth camera lerping
// 
// 37    10/22/99 3:25p Jimdose
// removed cylinder collision detection stuff
// 
// 36    10/21/99 6:19p Markd
// removed torso and head members from entity_state
// 
// 35    10/21/99 2:51p Aldie
// Added some more beam functions
// 
// 34    10/20/99 12:20p Aldie
// More beam stuff
// 
// 33    10/19/99 7:53p Markd
// eliminated 3 part model system
// 
// 32    10/19/99 4:31p Aldie
// Added beam wave effects
// 
// 31    10/18/99 1:59p Aldie
// Lots of fixes for beams and stuff
// 
// 30    10/13/99 3:26p Aldie
// Various fixes for particles, beams and lensflares
// 
// 29    10/12/99 6:56p Markd
// Fixed some player interpolation bugs and also interpolated camera
// 
// 28    10/12/99 2:23p Markd
// Rewrote camera and player movetype system
// 
// 27    10/09/99 5:26p Markd
// Added proper portal entity support
// 
// 26    10/08/99 5:07p Aldie
// More beam stuff and fix for UI_CenterPrint
// 
// 25    10/06/99 7:25p Markd
// removed TIMESTAMP, time and fixed make_static bug
// 
// 24    10/04/99 3:47p Morbid
// Unreferenced inline warning disabled
// 
// 23    10/01/99 6:08p Aldie
// Added some new features to beam system
// 
// 22    10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 21    10/01/99 2:42p Markd
// moved all the binding code back into Entity from Mover
// 
// 20    10/01/99 2:04p Aldie
// added prototype
// 
// 19    9/30/99 12:57p Markd
// changed Q3_VERSION string to say fakk2 instead of q3t
// 
// 18    9/29/99 4:12p Aldie
// Added beams and fixed some lightmap probs
// 
// 17    9/27/99 5:45p Markd
// began documentation and cleanup phase after merge
// 
// 16    9/23/99 1:02p Markd
// fixed spelling mistake with "bigendian"
// 
// 15    9/22/99 6:43p Jimdose
// added bigendien to indicate endien-ness of the cpu
// 
// 14    9/17/99 5:32p Jimdose
// added TR_LERP
// 
// 13    9/16/99 4:46p Markd
// more merging
// 
// 12    9/16/99 3:24p Aldie
// Fix prints
// 
// 11    9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 10    9/15/99 2:03p Steven
// Merge.
// 
// 9     9/13/99 4:22p Jimdose
// merge
// 
// 8     9/13/99 3:27p Aldie
// code merge
// 
// 7     9/13/99 2:40p Jimdose
// merge
// 
// 55    9/09/99 3:55p Jimdose
// added MAX_SOUNDS_BITS
// 
// 54    9/09/99 3:28p Jimdose
// added MAX_SERVER_SOUNDS_BITS
// 
// 53    9/02/99 7:00p Markd
// put in anti_sucknblow support
// 
// 52    9/02/99 4:35p Markd
// Added Color Offset support for sentients
// 
// 51    8/30/99 2:37p Steven
// Added support for volume and minimum distance for loop sounds.
// 
// 50    8/29/99 7:24p Markd
// Fixed multiple map loading and portal skys
// 
// 49    8/27/99 4:49p Jimdose
// removed movementDir
// 
// 48    8/25/99 9:01p Markd
// working on RF_ stuff and local color for entities on client
// 
// 47    8/23/99 8:14p Aldie
// Fixed lensflare effects for entities
// 
// 46    8/20/99 7:52p Aldie
// Added some inventory to playerstate
// 
// 45    8/18/99 3:29p Jimdose
// added cylindrical collision detection
// 
// 44    8/17/99 4:49p Markd
// Fixed offset shader effect
// 
// 43    8/15/99 4:42p Markd
// Put in far clipping plane support into worldspawn
// 
// 42    8/09/99 4:27p Markd
// Upped precision on translation
// 
// 41    8/06/99 8:00p Markd
// Added shader modifiable from script
// 
// 40    8/05/99 11:21a Markd
// Added some bit packing utilities for surface manipulation
// 
// 39    8/03/99 5:40p Markd
// Removed a bunch of entity_state stuff from q_shared, added new UpdateEntity
// command
// 
// 38    7/07/99 3:35p Jimdose
// added new button flags
// 
// 37    7/07/99 11:26a Steven
// Added some stuff on the sector pathfinding approach.
//
// DESCRIPTION:
// included first by ALL program modules.  A user mod should never modify
// this file

#ifndef __Q_SHARED_H__
#define __Q_SHARED_H__

// q_shared.h -- included first by ALL program modules.
// A user mod should never modify this file

// !!!!!!!!!!!!!!!! Update both version numbers !!!!!!!!!!!!!!!!!!!!!!!!!!
#define	Q3_VERSION		      "Heavy Metal: FAKK2 1.02"
#define  FAKK_SHORT_VERSION   "1.02"

#ifdef _WIN32

#pragma warning(disable : 4018)     // signed/unsigned mismatch
#pragma warning(disable : 4032)     // formal parameter 'number' has different type when promoted
#pragma warning(disable : 4051)     // type conversion, possible loss of data
#pragma warning(disable : 4057)		// slightly different base types
#pragma warning(disable : 4100)		// unreferenced formal parameter
#pragma warning(disable : 4115)     // 'type' : named type definition in parentheses
#pragma warning(disable : 4125)		// decimal digit terminates octal escape sequence
#pragma warning(disable : 4127)		// conditional expression is constant
#pragma warning(disable : 4136)     // conversion between different floating-point types
//#pragma warning(disable : 4201)     // nonstandard extension used : nameless struct/union
#pragma warning(disable : 4214)     // nonstandard extension used : bit field types other than int
#pragma warning(disable : 4244)     // 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable : 4305)		// truncation from const double to float
#pragma warning(disable : 4310)		// cast truncates constant value
#pragma warning(disable : 4514)     // unreferenced inline/local function has been removed
#pragma warning(disable : 4711)		// selected for automatic inline expansion
#pragma warning(disable : 4220)		// varargs matches remaining parameters
#pragma warning(disable : 4710)     // did not inline this function
#pragma warning(disable : 4239)     // nonstandard extension used, conversion from class b to class & b
#pragma warning(disable : 4512)     // 'Class' : assignment operator could not be generated
#pragma warning(disable : 4611)     // interaction between '_setjmp' and C++ object destruction is non-portable
#pragma warning(disable : 4131)     // 'function' : uses old-style declarator
#pragma warning(disable : 4514)     // 'function' : unreferenced inline function has been removed

// shut up warnings with Intel Compiler
/*ARGSUSED*/
/*NOTREACHED*/
/*VARARGS*/ 
#endif

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32

//#pragma intrinsic( memset, memcpy )

#endif


// this is the define for determining if we have an asm version of a C function
#if (defined _M_IX86 || defined __i386__) && !defined C_ONLY && !defined __sun__
#define id386	1
#else
#define id386	0
#endif

//======================= WIN32 DEFINES =================================

#ifdef WIN32

#define	MAC_STATIC

// buildstring will be incorporated into the version string
#ifdef NDEBUG
#ifdef _M_IX86
#define	CPUSTRING	"win-x86"
#elif defined _M_ALPHA
#define	CPUSTRING	"win-AXP"
#endif
#else
#ifdef _M_IX86
#define	CPUSTRING	"win-x86-debug"
#elif defined _M_ALPHA
#define	CPUSTRING	"win-AXP-debug"
#endif
#endif


#define	PATH_SEP '\\' 

#endif

//======================= MAC OS X SERVER DEFINES =====================

#if defined(__MACH__) && defined(__APPLE__)

#define MAC_STATIC

#ifdef __ppc__
#define CPUSTRING	"MacOSXS-ppc"
#elif defined __i386__
#define CPUSTRING	"MacOSXS-i386"
#else
#define CPUSTRING	"MacOSXS-other"
#endif

#define	PATH_SEP	'/'

#define	GAME_HARD_LINKED
#define	CGAME_HARD_LINKED
#define	UI_HARD_LINKED
#define	BOTLIB_HARD_LINKED

#endif

//======================= MAC DEFINES =================================

#ifdef __MACOS__

#define	MAC_STATIC	static

#define	CPUSTRING	"MacOS-PPC"

#define	PATH_SEP ':'

#define	GAME_HARD_LINKED
#define	CGAME_HARD_LINKED
#define	UI_HARD_LINKED
#define	BOTLIB_HARD_LINKED

void Sys_PumpEvents( void );

#endif

//======================= LINUX DEFINES =================================

// the mac compiler can't handle >32k of locals, so we
// just waste space and make big arrays static...
#ifdef __linux__

#define	MAC_STATIC

#ifdef __i386__
#define	CPUSTRING	"linux-i386"
#elif defined __axp__
#define	CPUSTRING	"linux-alpha"
#else
#define	CPUSTRING	"linux-other"
#endif

#define	PATH_SEP '/'

#endif

//=============================================================


//======================= C++ DEFINES =================================

#ifdef __cplusplus
extern "C"
   {
#endif

#ifndef min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#define bound(a,minval,maxval)  ( ((a) > (minval)) ? ( ((a) < (maxval)) ? (a) : (maxval) ) : (minval) )

typedef unsigned char 		byte;

#ifdef __cplusplus
typedef int qboolean;
#define qfalse (0)
#define qtrue (!qfalse)
#else
typedef enum {qfalse, qtrue}	qboolean;
#endif

typedef int		qhandle_t;
typedef int		sfxHandle_t;
typedef int		fileHandle_t;
typedef int		clipHandle_t;


#ifndef NULL
#define NULL ((void *)0)
#endif

#define	MAX_QINT			0x7fffffff
#define	MIN_QINT			(-MAX_QINT-1)


// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

// the game guarantees that no string from the network will ever
// exceed MAX_STRING_CHARS
#define	MAX_STRING_CHARS	1024	// max length of a string passed to Cmd_TokenizeString
#define	MAX_STRING_TOKENS	256		// max tokens resulting from Cmd_TokenizeString
#define	MAX_TOKEN_CHARS		1024	// max length of an individual token

#define	MAX_INFO_STRING		1024
#define	MAX_INFO_KEY		1024
#define	MAX_INFO_VALUE		1024


#define	MAX_QPATH			64		// max length of a quake game pathname
#define	MAX_OSPATH			128		// max length of a filesystem pathname

#define	MAX_NAME_LENGTH		32		// max length of a client name

// paramters for command buffer stuffing
typedef enum {
	EXEC_NOW,			// don't return until completed, a VM should NEVER use this,
					   	// because some commands might cause the VM to be unloaded...
	EXEC_INSERT,		// insert at current position, but don't run yet
	EXEC_APPEND			// add to end of the command buffer (normal case)
} cbufExec_t;


//
// these aren't needed by any of the VMs.  put in another header?
//
#define	MAX_MAP_AREA_BYTES		32		// bit vector of area visibility


// print levels from renderer (FIXME: set up for game / cgame?)
typedef enum {
	PRINT_ALL,
	PRINT_DEVELOPER,		// only print when "developer 1"
	PRINT_DEVELOPER_2,		// only print when "developer 2"
	PRINT_WARNING,
	PRINT_ERROR
} printParm_t;


// parameters to the main Error routine
typedef enum {
	ERR_FATAL,					// exit the entire game with a popup window
	ERR_DROP,					// print to console and disconnect from game
	ERR_DISCONNECT,				// don't kill server
	ERR_NEED_CD					// pop up the need-cd dialog
} errorParm_t;


/*
==============================================================

MATHLIB

==============================================================
*/


typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec5_t[5];

typedef	int	fixed4_t;
typedef	int	fixed8_t;
typedef	int	fixed16_t;

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

#define NUMVERTEXNORMALS	162
extern	vec3_t	bytedirs[NUMVERTEXNORMALS];

// all drawing is done to a 640*480 virtual screen size
// and will be automatically scaled to the real resolution
#define	SCREEN_WIDTH		640
#define	SCREEN_HEIGHT		480

#define TINYCHAR_WIDTH		(SMALLCHAR_WIDTH)
#define TINYCHAR_HEIGHT		(SMALLCHAR_HEIGHT/2)

#define SMALLCHAR_WIDTH		8
#define SMALLCHAR_HEIGHT	16

#define BIGCHAR_WIDTH		16
#define BIGCHAR_HEIGHT		16

#define	GIANTCHAR_WIDTH		32
#define	GIANTCHAR_HEIGHT	48

extern	vec4_t		colorBlack;
extern	vec4_t		colorRed;
extern	vec4_t		colorGreen;
extern	vec4_t		colorBlue;
extern	vec4_t		colorYellow;
extern	vec4_t		colorMagenta;
extern	vec4_t		colorCyan;
extern	vec4_t		colorWhite;
extern	vec4_t		colorLtGrey;
extern	vec4_t		colorMdGrey;
extern	vec4_t		colorDkGrey;

#define Q_COLOR_ESCAPE	'^'
#define Q_IsColorString(p)	( p && *(p) == Q_COLOR_ESCAPE && *((p)+1) && *((p)+1) != Q_COLOR_ESCAPE )

#define COLOR_BLACK		'0'
#define COLOR_RED		'1'
#define COLOR_GREEN		'2'
#define COLOR_YELLOW	'3'
#define COLOR_BLUE		'4'
#define COLOR_CYAN		'5'
#define COLOR_MAGENTA	'6'
#define COLOR_WHITE		'7'
#define ColorIndex(c)	( ( (c) - '0' ) & 7 )

#define S_COLOR_BLACK	"^0"
#define S_COLOR_RED		"^1"
#define S_COLOR_GREEN	"^2"
#define S_COLOR_YELLOW	"^3"
#define S_COLOR_BLUE	"^4"
#define S_COLOR_CYAN	"^5"
#define S_COLOR_MAGENTA	"^6"
#define S_COLOR_WHITE	"^7"

extern vec4_t	g_color_table[8];

#define	MAKERGB( v, r, g, b ) v[0]=r;v[1]=g;v[2]=b
#define	MAKERGBA( v, r, g, b, a ) v[0]=r;v[1]=g;v[2]=b;v[3]=a

#define DEG2RAD( a ) ( ( (a) * M_PI ) / 180.0F )
#define RAD2DEG( a ) ( ( (a) * 180.0f ) / M_PI )

struct cplane_s;

extern	vec3_t	vec3_origin;
extern	vec3_t	axisDefault[3];

#define	nanmask (255<<23)

#define	IS_NAN(x) (((*(int *)&x)&nanmask)==nanmask)

#ifndef __Q_FABS__
#define __Q_FABS__
#endif

float Q_fabs( float f );
float Q_rsqrt( float f );		// reciprocal square root

#define SQRTFAST( x ) ( 1.0f / Q_rsqrt( x ) )

signed char ClampChar( int i );
signed short ClampShort( int i );

// this isn't a real cheap function to call!
int DirToByte( vec3_t dir );
void ByteToDir( int b, vec3_t dir );

#if	1

#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))

#else

#define DotProduct(x,y)			_DotProduct(x,y)
#define VectorSubtract(a,b,c)	_VectorSubtract(a,b,c)
#define VectorAdd(a,b,c)		_VectorAdd(a,b,c)
#define VectorCopy(a,b)			_VectorCopy(a,b)
#define	VectorScale(v, s, o)	_VectorScale(v,s,o)
#define	VectorMA(v, s, b, o)	_VectorMA(v,s,b,o)

#endif

#ifdef __LCC__
#ifdef VectorCopy
#undef VectorCopy
// this is a little hack to get more efficient copies
typedef struct {
	float	v[3];
} vec3struct_t;
#define VectorCopy(a,b)	*(vec3struct_t *)b=*(vec3struct_t *)a;
#endif
#endif

#define VectorClear(a)			((a)[0]=(a)[1]=(a)[2]=0)
#define VectorNegate(a,b)		((b)[0]=-(a)[0],(b)[1]=-(a)[1],(b)[2]=-(a)[2])
#define VectorSet(v, x, y, z)	((v)[0]=(x), (v)[1]=(y), (v)[2]=(z))
#define Vector4Copy(a,b)		((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2],(b)[3]=(a)[3])

#define OrientClear( or )   \
   ( VectorSet( or.origin, 0, 0, 0 ), \
   VectorSet( or.axis[ 0 ], 1, 0, 0 ), \
   VectorSet( or.axis[ 1 ], 0, 1, 0 ), \
   VectorSet( or.axis[ 2 ], 0, 0, 1 ) )
#define OrientCopy( a, b )   \
   ( VectorCopy( (a).origin, (b).origin ), \
   VectorCopy( (a).axis[ 0 ], (b).axis[ 0 ] ), \
   VectorCopy( (a).axis[ 1 ], (b).axis[ 1 ] ), \
   VectorCopy( (a).axis[ 2 ], (b).axis[ 2 ] ) )

#define QuatSet( q, x, y, z, w ) ((q)[0]=(x),(q)[1]=(y),(q)[2]=(z),(q)[3]=(w))
#define QuatCopy( a,b ) ((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2],(b)[3]=(a)[3])

#define uint_cast(X) ( *(unsigned int *) &(X) )
#define int_cast(X) ( *(int *) &(X) )
#define IsNegative(X) ( uint_cast(X) >> 31 )
#define USES_CLAMP_ZERO const unsigned s_clamp0table[2] = { 0xFFFFFFFF, 0x00000000 }
#define ClampZero(X) uint_cast(X) &= s_clamp0table[IsNegative(X)]
#define ClampNormalFloat255Byte(dst,X) { \
   float _f_ = X; \
   unsigned mask = ~ ( (int) ( uint_cast(_f_) - 1 ) >> 31 ); \
   \
   uint_cast(_f_) += (unsigned) ( 0x04000000 - 0x437F0000 ); \
   uint_cast(_f_) &= ( (int) uint_cast(_f_) ) >> 31; \
   uint_cast(_f_) += (unsigned) 0x437F0000; \
   uint_cast(_f_) &= mask; \
   dst = (unsigned char) _f_; \
}

#define SetHighest(type, dst,upperbound) { \
   type _ff_=dst-upperbound;\
   ClampZero ( _ff_ );\
   dst = dst - _ff_;\
}

#define SetLowest(type, dst,lowerbound) { \
   type _ff_= dst - lowerbound;\
   ClampZero ( _ff_ );\
   dst = lowerbound + _ff_;\
}

#define SetLowestFloat(dst,l) SetLowest ( float, dst, l )
#define SetHighestFloat(dst,l) SetHighest ( float, dst, l )
#define SetLowestInt(dst,l) SetLowest ( int, dst, l )
#define SetHighestInt(dst,l) SetHighest ( int, dst, l )

#ifdef __cplusplus
inline bool VectorFromString ( const char *ss, vec3_t v ) {
   return sscanf ( ss, "%f %f %f", &v[0], &v[1], &v[2] ) == 3;
}
#else
#define VectorFromString(ss,v)   ( sscanf ( (ss), "%f %f %f", &(v)[0], &(v)[1], &(v)[2] ) == 3 )
#endif

#define	SnapVector(v) {v[0]=(int)v[0];v[1]=(int)v[1];v[2]=(int)v[2];}

// just in case you do't want to use the macros
vec_t _DotProduct( const vec3_t v1, const vec3_t v2 );
void _VectorSubtract( const vec3_t veca, const vec3_t vecb, vec3_t out );
void _VectorAdd( const vec3_t veca, const vec3_t vecb, vec3_t out );
void _VectorCopy( const vec3_t in, vec3_t out );
void _VectorScale( const vec3_t in, float scale, vec3_t out );
void _VectorMA( const vec3_t veca, float scale, const vec3_t vecb, vec3_t vecc );

unsigned ColorBytes3 (float r, float g, float b);
unsigned ColorBytes4 (float r, float g, float b, float a);

float NormalizeColor( const vec3_t in, vec3_t out );

float RadiusFromBounds( const vec3_t mins, const vec3_t maxs );
void ClearBounds( vec3_t mins, vec3_t maxs );
qboolean BoundsClear( vec3_t mins, vec3_t maxs );
void AddPointToBounds( const vec3_t v, vec3_t mins, vec3_t maxs );
int VectorCompare( const vec3_t v1, const vec3_t v2 );
vec_t VectorLength( const vec3_t v );
vec_t Distance( const vec3_t p1, const vec3_t p2 );
vec_t DistanceSquared( const vec3_t p1, const vec3_t p2 );
void CrossProduct( const vec3_t v1, const vec3_t v2, vec3_t cross );
vec_t VectorNormalize (vec3_t v);		// returns vector length
void VectorNormalizeFast(vec3_t v);		// does NOT return vector length, uses rsqrt approximation
vec_t VectorNormalize2( const vec3_t v, vec3_t out );
void VectorInverse (vec3_t v);
void Vector4Scale( const vec4_t in, vec_t scale, vec4_t out );
void VectorRotate( vec3_t in, vec3_t matrix[3], vec3_t out );
int Q_log2(int val);
unsigned short NormalToLatLong( vec3_t normal );


int		Q_rand( int *seed );
float	Q_random( int *seed );
float	Q_crandom( int *seed );

#define random()	((rand () & 0x7fff) / ((float)0x7fff))
#define crandom()	(2.0 * (random() - 0.5))

void AccumulateTransform( vec3_t dstLocation, vec3_t dstAxes[3],
						  vec3_t childLocation, vec3_t childAxes[3],
						  vec3_t parentLocation, vec3_t parentAxes[3] );
void AccumulatePosition( vec3_t dstOrigin, vec3_t childOrigin, vec3_t parentOrigin, vec3_t parentAxes[3] );

void vectoangles( const vec3_t value1, vec3_t angles);
float vectoyaw( const vec3_t vec );

//FIXME
// get rid of all references to AnglesToMat
#define AnglesToMat AnglesToAxis

void AxisClear( vec3_t axis[3] );
void AxisCopy( vec3_t in[3], vec3_t out[3] );

void SetPlaneSignbits( struct cplane_s *out );
int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct cplane_s *plane);

float	AngleMod(float a);
float	LerpAngle (float from, float to, float frac);
float LerpAngleFromCurrent (float from, float to, float current, float frac);
float	AngleSubtract( float a1, float a2 );
void	AnglesSubtract( vec3_t v1, vec3_t v2, vec3_t v3 );

float AngleNormalize360 ( float angle );
float AngleNormalize180 ( float angle );
float AngleDelta ( float angle1, float angle2 );

qboolean PlaneFromPoints( vec4_t plane, const vec3_t a, const vec3_t b, const vec3_t c );
void ProjectPointOnPlane( vec3_t dst, const vec3_t p, const vec3_t normal );
void RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point, float degrees );
void RotateAroundDirection( vec3_t axis[3], float yaw );
void MakeNormalVectors( const vec3_t forward, vec3_t right, vec3_t up );

float noise(float vec[], int len);
float noise1(float arg);
float noise2(vec3_t arg);
float noise3(vec3_t arg);
// perpendicular vector could be replaced by this

void  R_ConcatRotations (float in1[3][3], float in2[3][3], float out[3][3]);
void  R_ConcatTransforms (float in1[3][4], float in2[3][4], float out[3][4]);
float	anglemod(float a);
float angledist( float ang );
int   BoxOnPlaneSide2 (vec3_t emins, vec3_t emaxs, struct cplane_s *p);
void  CalculateRotatedBounds( vec3_t angles, vec3_t mins, vec3_t maxs );
void  CalculateRotatedBounds2( float trans[3][3], vec3_t mins, vec3_t maxs );
int   BoundingBoxToInteger( vec3_t mins, vec3_t maxs );
void  IntegerToBoundingBox( int num, vec3_t mins, vec3_t maxs );
void  MatrixTransformVector( vec3_t in, float mat[ 3 ][ 3 ], vec3_t out );
void  Matrix4TransformVector( vec3_t in, float mat[ 4 ][ 4 ], vec3_t out );
void  MatrixToEulerAngles( float mat[ 3 ][ 3 ], vec3_t ang );
void  TransposeMatrix( float in[ 3 ][ 3 ], float out[ 3 ][ 3 ] );
void  OrthoNormalize( float mat[3][3] );
float NormalizeQuat( float q[ 4 ] );
void  MatToQuat( float srcMatrix[ 3 ][ 3 ], float destQuat[ 4 ] );
void  RotateAxis( float axis[ 3 ], float angle, float q[ 4 ] );
void  MultQuat( float q1[ 4 ], float q2[ 4 ], float out[ 4 ] );
void  QuatToMat( float q[ 4 ], float m[ 3 ][ 3 ] );
void  SlerpQuaternion( float from[ 4 ], float to[ 4 ], float t, float res[ 4 ] );
void  EulerToQuat( float ang[ 3 ], float q[ 4 ] );
int	PlaneTypeForNormal (vec3_t normal);



//=============================================

float Com_Clamp( float min, float max, float value );

const char	*COM_SkipPath( const char *pathname );
void	      COM_StripExtension( const char *in, char *out );
void	      COM_DefaultExtension( char *path, int maxSize, const char *extension );
void        Com_BackslashToSlash( char *str );

void	      COM_BeginParseSession( void );
int         COM_GetCurrentParseLine( void );
const char	*COM_Parse( const char **data_p );
char	      *COM_ParseExt( char **data_p, qboolean allowLineBreak );
const char  *COM_GetToken(const char **data_p, qboolean crossline);

// data is an in/out parm, returns a parsed out token

void	COM_MatchToken( char**buf_p, char *match );

void SkipBracedSection (char **program);
void SkipRestOfLine ( char **data );

void Parse1DMatrix (char **buf_p, int x, float *m);
void Parse2DMatrix (char **buf_p, int y, int x, float *m);
void Parse3DMatrix (char **buf_p, int z, int y, int x, float *m);

void	Com_sprintf (char *dest, int size, const char *fmt, ...);


// mode parm for FS_FOpenFile
typedef enum {
	FS_READ,
	FS_WRITE,
	FS_APPEND,
	FS_APPEND_SYNC
} fsMode_t;

typedef enum {
	FS_SEEK_CUR,
	FS_SEEK_END,
	FS_SEEK_SET
} fsOrigin_t;

//=============================================

int Q_isprint( int c );
int Q_islower( int c );
int Q_isupper( int c );
int Q_isalpha( int c );

// portable case insensitive compare
int	Q_stricmp (const char *s1, const char *s2);
int	Q_strncmp (const char *s1, const char *s2, int n);
int	Q_stricmpn (const char *s1, const char *s2, int n);
char	*Q_strlwr( char *s1 );
char	*Q_strupr( char *s1 );
char	*Q_strrchr( const char* string, int c );

// buffer size safe library replacements
void	Q_strncpyz( char *dest, const char *src, int destsize );
void	Q_strcat( char *dest, int size, const char *src );
char *Q_CleanStr( char *string );

//=============================================

extern qboolean bigendian;

short	BigShort(short l);
short	LittleShort(short l);
int	BigLong (int l);
int	LittleLong (int l);
float	BigFloat (float l);
float	LittleFloat (float l);
unsigned short	LittleUnsignedShort(unsigned short l);
unsigned short	BigUnsignedShort(unsigned short l);

void	Swap_Init (void);
const char *va(const char *format, ...);

//=============================================

int MusicMood_NameToNum( const char * name );
const char * MusicMood_NumToName( int num );
int EAXMode_NameToNum( const char * name );
const char * EAXMode_NumToName( int num );

//
// key / value info strings
//
const char *Info_ValueForKey( const char *s, const char *key );
void        Info_RemoveKey( char *s, const char *key );
void        Info_SetValueForKey( char *s, const char *key, const char *value );
qboolean    Info_Validate( const char *s );
void        Info_NextPair( const char **s, char key[MAX_INFO_KEY], char value[MAX_INFO_VALUE] );

// this is only here so the functions in q_shared.c and bg_*.c can link
void	Com_Error( int level, const char *error, ... );
void	Com_Printf( const char *msg, ... );


/*
==========================================================

CVARS (console variables)

Many variables can be used for cheating purposes, so when
cheats is zero, force all unspecified variables to their
default values.
==========================================================
*/

#define	CVAR_ARCHIVE		1	// set to cause it to be saved to vars.rc
								      // used for system variables, not for player
								      // specific configurations
#define	CVAR_USERINFO		2	// sent to server on connect or change
#define	CVAR_SERVERINFO	4	// sent in response to front end requests
#define	CVAR_SYSTEMINFO	8	// these cvars will be duplicated on all clients
#define	CVAR_INIT			16	// don't allow change from console at all,
								      // but can be set from the command line
#define	CVAR_LATCH			32	// will only change when C code next does
								      // a Cvar_Get(), so it can't be changed
								      // without proper initialization.  modified
								      // will be set, even though the value hasn't
								      // changed yet
#define	CVAR_ROM			   64	// display only, cannot be set by user at all
#define	CVAR_USER_CREATED	128	// created by a set command
#define	CVAR_TEMP			256	// can be set even when cheats are disabled, but is not archived
#define  CVAR_CHEAT			512	// can not be changed if cheats are disabled
#define  CVAR_NORESTART		1024	// do not clear when a cvar_restart is issued
#define  CVAR_RESETSTRING  2048  // force the cvar's reset string to be set
#define	CVAR_SOUND_LATCH	4096	// specifically for sound will only change 
                                 // when C code next does a Cvar_Get(), so it 
                                 // can't be changed without proper initialization.
                                 // modified will be set, even though the value hasn't
								         // changed yet

// nothing outside the Cvar_*() functions should modify these fields!
typedef struct cvar_s {
	char		*name;
	char		*string;
	char		*resetString;		// cvar_restart will reset to this value
	char		*latchedString;		// for CVAR_LATCH vars
	int			flags;
	qboolean	modified;			// set each time the cvar is changed
	int			modificationCount;	// incremented each time the cvar is changed
	float		value;				// atof( string )
	int			integer;			// atoi( string )
	struct cvar_s *next;
} cvar_t;

#define	MAX_CVAR_VALUE_STRING	256

typedef int	cvarHandle_t;

// the modules that run in the virtual machine can't access the cvar_t directly,
// so they must ask for structured updates
typedef struct {
	cvarHandle_t	handle;
	int			modificationCount;
	float		value;
	int			integer;
	char		string[MAX_CVAR_VALUE_STRING];
} vmCvar_t;

/*
==============================================================

COLLISION DETECTION

==============================================================
*/

#include "surfaceflags.h"			// shared with the q3map utility

// plane types are used to speed some tests
// 0-2 are axial planes
#define	PLANE_X			0
#define	PLANE_Y			1
#define	PLANE_Z			2
#define	PLANE_NON_AXIAL	3


// plane_t structure
// !!! if this is changed, it must be changed in asm code too !!!
typedef struct cplane_s {
	vec3_t	normal;
	float	dist;
	byte	type;			// for fast side tests: 0,1,2 = axial, 3 = nonaxial
	byte	signbits;		// signx + (signy<<1) + (signz<<2), used as lookup during collision
	byte	pad[2];
} cplane_t;

typedef struct
   {
   qboolean valid;
   int      surface;
   vec3_t   position;
   vec3_t   normal;
   float    damage_multiplier;
   } tikimdl_intersection_t;

// a trace is returned when a box is swept through the world
typedef struct {
	qboolean	         allsolid;	   // if true, plane is not valid
	qboolean	         startsolid;	   // if true, the initial point was in a solid area
	float		         fraction;	   // time completed, 1.0 = didn't hit anything
	vec3_t	         endpos;		   // final position
	cplane_t	         plane;		   // surface normal at impact, transformed to world space
	int		         surfaceFlags;	// surface hit
	int		         contents;	   // contents on other side of surface hit
	int		         entityNum;	   // entity the contacted surface is a part of
   struct gentity_s	*ent;		      // Pointer to entity hit
} trace_t;

// trace->entityNum can also be 0 to (MAX_GENTITIES-1)
// or ENTITYNUM_NONE, ENTITYNUM_WORLD


// markfragments are returned by CM_MarkFragments()
typedef struct {
	int		firstPoint;
	int		numPoints;
} markFragment_t;

typedef struct {
	vec3_t		origin;
	vec3_t		axis[3];
} orientation_t;

typedef struct {
   int      time;                   // real time of day
   int      serverTime;             // time in the game
   char	   comment[ MAX_QPATH ];   // user comment 
   char     mapName[ MAX_QPATH ];   // name of map
   char     saveName[ MAX_QPATH ];  // local name of savegame
} savegamestruct_t;

//=====================================================================

// in order from highest priority to lowest
// if none of the catchers are active, bound key strings will be executed
#define KEYCATCH_CONSOLE	1
#define	KEYCATCH_UI			2
#define	KEYCATCH_MESSAGE	4


// sound channels
// channel 0 never willingly overrides
// other channels will allways override a playing sound on that channel
typedef enum {
	CHAN_AUTO,
	CHAN_LOCAL,	
   CHAN_WEAPON,
	CHAN_VOICE,
	CHAN_ITEM,
	CHAN_BODY,
   CHAN_DIALOG,
   CHAN_DIALOG_SECONDARY,
   CHAN_WEAPONIDLE,
   CHAN_MENU
} soundChannel_t;

#define DEFAULT_MIN_DIST  -1.0
#define DEFAULT_VOL  -1.0

#define LEVEL_WIDE_MIN_DIST  10000	// full volume the entire level
#define LEVEL_WIDE_STRING "levelwide"

#define  SOUND_SYNCH             0x1
#define  SOUND_SYNCH_FADE        0x2
#define  SOUND_RANDOM_PITCH_20   0x4
#define  SOUND_RANDOM_PITCH_40   0x8
#define  SOUND_LOCAL_DIALOG      0x10

typedef enum
   {
   mood_none,
   mood_normal,
   mood_action,
   mood_suspense,
   mood_mystery,
   mood_success,
   mood_failure,
   mood_surprise,
   mood_special,
   mood_aux1,
   mood_aux2,
   mood_aux3,
   mood_aux4,
   mood_aux5,
   mood_aux6,
   mood_aux7,
   mood_totalnumber
   } music_mood_t;

typedef enum
   {
   eax_generic,
   eax_paddedcell,
   eax_room,
   eax_bathroom,
   eax_livingroom,
   eax_stoneroom,
   eax_auditorium,
   eax_concerthall,
   eax_cave,
   eax_arena,
   eax_hangar,
   eax_carpetedhallway,
   eax_hallway,
   eax_stonecorridor,
   eax_alley,
   eax_forest,
   eax_city,
   eax_mountains,
   eax_quarry,
   eax_plain,
   eax_parkinglot,
   eax_sewerpipe,
   eax_underwater,
   eax_drugged,
   eax_dizzy,
   eax_psychotic,
   eax_totalnumber
   } eax_mode_t;

/*
========================================================================

  ELEMENTS COMMUNICATED ACROSS THE NET

========================================================================
*/

#define	ANGLE2SHORT(x)	((int)((x)*65536/360) & 65535)
#define	SHORT2ANGLE(x)	((x)*(360.0/65536))

#define	SNAPFLAG_RATE_DELAYED	1
#define	SNAPFLAG_NOT_ACTIVE		2	// snapshot used during connection and for zombies
#define  SNAPFLAG_SERVERCOUNT	   4	// toggled every map_restart so transitions can be detected

//
// per-level limits
//
#define	MAX_CLIENTS			128		// absolute limit
#define MAX_LOCATIONS		64

#define	GENTITYNUM_BITS		10		// don't need to send any more
#define	MAX_GENTITIES		(1<<GENTITYNUM_BITS)

// entitynums are communicated with GENTITY_BITS, so any reserved
// values thatare going to be communcated over the net need to
// also be in this range
#define	ENTITYNUM_NONE		(MAX_GENTITIES-1)
#define	ENTITYNUM_WORLD		(MAX_GENTITIES-2)
#define	ENTITYNUM_MAX_NORMAL	(MAX_GENTITIES-2)


#define	MAX_MODELS			384		// these are sent over the net as 8 bits
#define  MAX_IMAGES        64       // so they cannot be blindly increased
#define  MAX_ACTIVE_ITEMS  32
#define  MAX_INVENTORY     32
#define  MAX_AMMO          32
#define  MAX_ITEMS         MAX_INVENTORY + MAX_AMMO 
#define  MAX_AMMOCOUNT     32
#define  MAX_SOUNDS_BITS   8
#define	MAX_SOUNDS			(1<<MAX_SOUNDS_BITS)
#define  MAX_LIGHTSTYLES   32

#define	MAX_CONFIGSTRINGS	1200

// these are the only configstrings that the system reserves, all the
// other ones are strictly for servergame to clientgame communication
#define	CS_SERVERINFO		0		// an info string with all the serverinfo cvars
#define	CS_SYSTEMINFO		1		// an info string for server system to client system configuration (timescale, etc)
#define	CS_NAME     		2		// A descriptive name of the current level

#define	MAX_GAMESTATE_CHARS	16000
typedef struct {
	int			stringOffsets[MAX_CONFIGSTRINGS];
	char		stringData[MAX_GAMESTATE_CHARS];
	int			dataCount;
} gameState_t;

//=========================================================

// bit field limits
#define	MAX_STATS				32
#define	MAX_PERSISTANT			16
#define	MAX_POWERUPS			16
#define	MAX_WEAPONS				16		

#define	MAX_PS_EVENTS			2

// playerState_t is the information needed by both the client and server
// to predict player motion and actions
// nothing outside of pmove should modify these, or some degree of prediction error
// will occur

// you can't add anything to this without modifying the code in msg.c

// playerState_t is a full superset of entityState_t as it is used by players,
// so if a playerState_t is transmitted, the entityState_t can be fully derived
// from it.
typedef struct playerState_s {
	int			commandTime;	// cmd->serverTime of last executed command
	int			pm_type;
	int			bobCycle;		// for view bobbing and footstep generation
	int			pm_flags;		// ducked, jump_held, etc
	int			pm_time;
   int         pm_runtime;    // used to keep track of how long player has been running

	vec3_t		origin;
	vec3_t		velocity;
	int			gravity;
	int			speed;
	int			delta_angles[3];	// add to command angles to get view direction
									// changed by spawns, rotating objects, and teleporters

	int			groundEntityNum;// ENTITYNUM_NONE = in air
	qboolean	   walking;
	qboolean	   groundPlane;
   int         feetfalling;
   vec3_t      falldir;
	trace_t		groundTrace;

	int			clientNum;		// ranges from 0 to MAX_CLIENTS-1

	vec3_t		viewangles;		// for fixed views
	int			viewheight;

	int			stats[MAX_STATS];
   int         activeItems[MAX_ACTIVE_ITEMS];
   int         inventory_name_index[MAX_INVENTORY];
   int         ammo_name_index[MAX_AMMO];
   int         ammo_amount[MAX_AMMOCOUNT];
   int         max_ammo_amount[MAX_AMMOCOUNT];

   // Added for FAKK
   int         current_music_mood;
   int         fallback_music_mood;
	float		   music_volume;
	float		   music_volume_fade_time;

	int			reverb_type;
	float			reverb_level;

  	float		   blend[4];		   // rgba full screen effect
   float       fov;              // fov of the player

   vec3_t      camera_origin;    // origin for camera view
   vec3_t      camera_angles;    // angles for camera view
   float       camera_time;      // time to switch between camera and normal view

   vec3_t      camera_offset;    // angular offset for camera
   vec3_t      damage_angles;    // these angles are added directly to the view, without lerping
   int         camera_flags;     // third-person camera flags

	// not communicated over the net at all
	int			ping;			// server to game info for scoreboard
} playerState_t;

#define MAX_SERVER_SOUNDS        32
#define MAX_SERVER_SOUNDS_BITS   6

typedef struct
{
	vec3_t origin;
	int entity_number; 
	int channel;
	short sound_index;
	float volume;
	float min_dist;
	qboolean stop_flag;
} server_sound_t;

//====================================================================


//
// usercmd_t->button bits, many of which are generated by the client system,
// so they aren't game-only definitions
//
#define	BUTTON_ATTACKRIGHT_BITINDEX 	0
#define	BUTTON_ATTACKLEFT_BITINDEX  	1
#define  BUTTON_SNEAK_BITINDEX         2
#define  BUTTON_RUN_BITINDEX           3
#define  BUTTON_HOLSTERWEAPON_BITINDEX 4
#define  BUTTON_USE_BITINDEX           5
#define	BUTTON_TALK_BITINDEX			   6			// displays talk balloon and disables actions
#define	BUTTON_ANY_BITINDEX			   7		   // any key whatsoever

#define	BUTTON_ATTACKRIGHT 	( 1 << BUTTON_ATTACKRIGHT_BITINDEX )
#define	BUTTON_ATTACKLEFT  	( 1 << BUTTON_ATTACKLEFT_BITINDEX )
#define  BUTTON_SNEAK         ( 1 << BUTTON_SNEAK_BITINDEX )
#define  BUTTON_RUN           ( 1 << BUTTON_RUN_BITINDEX )
#define  BUTTON_HOLSTERWEAPON ( 1 << BUTTON_HOLSTERWEAPON_BITINDEX )
#define  BUTTON_USE           ( 1 << BUTTON_USE_BITINDEX )
#define	BUTTON_TALK			   ( 1 << BUTTON_TALK_BITINDEX )			// displays talk balloon and disables actions
#define	BUTTON_ANY			   ( 1 << BUTTON_ANY_BITINDEX )		   // any key whatsoever


// usercmd_t is sent to the server each client frame
typedef struct usercmd_s {
	int	serverTime;
   byte	msec;
	byte	buttons;
	byte	weapon;
	short	angles[3];

	signed char	forwardmove, rightmove, upmove;
} usercmd_t;

//===================================================================

//
// Animation flags
//
#define  MDL_ANIM_DELTA_DRIVEN   ( 1 << 0 )
#define  MDL_ANIM_DEFAULT_ANGLES ( 1 << 3 )
#define  MDL_ANIM_NO_TIMECHECK   ( 1 << 4 )

// if entityState->solid == SOLID_BMODEL, modelindex is an inline model number
#define	SOLID_BMODEL	0xffffff

#define	RF_THIRD_PERSON	   (1<<0)   	// don't draw through eyes, only mirrors (player bodies, chat sprites)
#define	RF_FIRST_PERSON	   (1<<1)		// only draw through eyes (view weapon, damage blood blob)
#define  RF_DEPTHHACK         (1<<2)      // hack the z-depth so that view weapons do not clip into walls
#define  RF_VIEWLENSFLARE     (1<<3)      // View dependent lensflare
#define	RF_FRAMELERP		   (1<<4)      // interpolate between current and next state
#define	RF_BEAM				   (1<<5)      // draw a beam between origin and origin2
#define  RF_DONTDRAW			   (1<<7)      // don't draw this entity but send it over
#define  RF_LENSFLARE         (1<<8)      // add a lens flare to this
#define  RF_EXTRALIGHT        (1<<9)      // use good lighting on this entity
#define  RF_DETAIL            (1<<10)     // Culls a model based on the distance away from you
#define  RF_SHADOW            (1<<11)     // whether or not to draw a shadow
#define	RF_PORTALSURFACE	   (1<<12)   	// don't draw, but use to set portal views
#define	RF_SKYORIGIN   	   (1<<13)   	// don't draw, but use to set sky portal origin and coordinate system
#define	RF_SKYENTITY   	   (1<<14)   	// this entity is only visible through a skyportal
#define	RF_LIGHTOFFSET   	   (1<<15)   	// this entity has a light offset
#define	RF_CUSTOMSHADERPASS  (1<<16)     // draw the custom shader on top of the base geometry
#define	RF_MINLIGHT			   (1<<17)		// allways have some light (viewmodel, some items)
#define	RF_FULLBRIGHT		   (1<<18)		// allways have full lighting
#define  RF_LIGHTING_ORIGIN	(1<<19)		// use refEntity->lightingOrigin instead of refEntity->origin
									               // for lighting.  This allows entities to sink into the floor
									               // with their origin going solid, and allows all parts of a
									               // player to get the same lighting
#define	RF_SHADOW_PLANE      (1<<20)		// use refEntity->shadowPlane
#define	RF_WRAP_FRAMES		   (1<<21)		// mod the model frames by the maxframes to allow continuous
									               // animation without needing to know the frame count
#define  RF_PORTALENTITY      (1<<22)     // this entity should only be drawn from a portal
#define  RF_DUALENTITY        (1<<23)     // this entity is drawn both in the portal and outside it.
#define  RF_ADDITIVE_DLIGHT   (1<<24)     // this entity has an additive dynamic light
#define  RF_LIGHTSTYLE_DLIGHT (1<<25)     // this entity has a dynamic light that uses a light style
#define  RF_SHADOW_PRECISE    (1<<26)     // this entity can have a precise shadow applied to it
#define  RF_INVISIBLE         (1<<27)     // This entity is invisible, and only negative lights will light it up

//
// use this mask when propagating renderfx from one entity to another
//
#define  RF_FLAGS_NOT_INHERITED ( RF_LENSFLARE | RF_VIEWLENSFLARE | RF_BEAM | RF_EXTRALIGHT | RF_SKYORIGIN | RF_SHADOW | RF_SHADOW_PRECISE | RF_SHADOW_PLANE )

//
// the following flag is used by the server and is also defined in bg_public.h
//
#define  PMF_CAMERA_VIEW      ( 1<<8 )    // use camera view instead of ps view

#define BEAM_LIGHTNING_EFFECT   (1<<0)
#define BEAM_USEMODEL           (1<<1)
#define BEAM_PERSIST_EFFECT     (1<<2)
#define BEAM_SPHERE_EFFECT      (1<<3)
#define BEAM_RANDOM_DELAY       (1<<4)
#define BEAM_TOGGLE             (1<<5)
#define BEAM_RANDOM_TOGGLEDELAY (1<<6)
#define BEAM_WAVE_EFFECT        (1<<7)
#define BEAM_USE_NOISE          (1<<8)
#define BEAM_PARENT             (1<<9)
#define BEAM_TILESHADER         (1<<10)
#define BEAM_OFFSET_ENDPOINTS   (1<<11)

typedef enum {
	TR_STATIONARY,
	TR_INTERPOLATE,				// non-parametric, but interpolate between snapshots
	TR_LINEAR,
	TR_LINEAR_STOP,
	TR_SINE,					      // value = base + sin( time / duration ) * delta
	TR_GRAVITY,
   TR_LERP                    // Lerp between current origin and last origin
} trType_t;

typedef struct {
	trType_t	trType;
	int		trTime;
	int		trDuration;			// if non 0, trTime + trDuration = stop time
	vec3_t	trBase;
	vec3_t	trDelta;			   // velocity, etc
} trajectory_t;

#define MAX_MODEL_SURFACES   32 // this needs to be the same in qfiles.h for TIKI_MAX_SURFACES

#define  MDL_SURFACE_SKINOFFSET_BIT0  ( 1 << 0 )
#define  MDL_SURFACE_SKINOFFSET_BIT1  ( 1 << 1 )
#define  MDL_SURFACE_NODRAW           ( 1 << 2 )
#define  MDL_SURFACE_SURFACETYPE_BIT0 ( 1 << 3 )
#define  MDL_SURFACE_SURFACETYPE_BIT1 ( 1 << 4 )
#define  MDL_SURFACE_SURFACETYPE_BIT2 ( 1 << 5 )
#define  MDL_SURFACE_CROSSFADE_SKINS  ( 1 << 6 )
#define  MDL_SURFACE_SKIN_NO_DAMAGE   ( 1 << 7 )

#define CROUCH_HEIGHT		36
#define CROUCH_EYE_HEIGHT	30
#define STAND_HEIGHT			72
#define STAND_EYE_HEIGHT	66

#define NUM_BONE_CONTROLLERS 5

// entityState_t is the information conveyed from the server
// in an update message about entities that the client will
// need to render in some way
// Different eTypes may use the information in different ways
// The messages are delta compressed, so it doesn't really matter if
// the structure size is fairly large

typedef struct entityState_s {
	int		number;			// entity index
	int		eType;			// entityType_t
	int		eFlags;

	trajectory_t	pos;	// for calculating position
	trajectory_t	apos;	// for calculating angles

   vec3_t   netorigin;    // these are the ones actually sent over
	vec3_t	origin;
	vec3_t	origin2;

   vec3_t   netangles;    // these are the ones actually sent over
	vec3_t	angles;

	int		constantLight;	   // r + (g<<8) + (b<<16) + (intensity<<24)
	int      loopSound;		   // constantly loop this sound
	float		loopSoundVolume;
	float		loopSoundMinDist;

   int      parent;           // if this entity is attached, this is non-zero
   int      tag_num;          // if attached, the tag number it is attached to on the parent
	qboolean attach_use_angles;
	vec3_t	attach_offset;

	int      modelindex;
	int      skinNum;
   int      anim;
   int      frame;
   int      crossblend_time;  // in milliseconds so it can be transmitted as a short

   int      torso_anim;
   int      torso_frame;
   int      torso_crossblend_time; // in milliseconds so it can be transmitted as a short

   int      bone_tag[ NUM_BONE_CONTROLLERS ];
   vec3_t   bone_angles[ NUM_BONE_CONTROLLERS ];
   vec4_t   bone_quat[ NUM_BONE_CONTROLLERS ];        // not sent over

   byte     surfaces[MAX_MODEL_SURFACES];

	int		clientNum;		// 0 to (MAX_CLIENTS - 1), for players and corpses

   int		groundEntityNum;  // -1 = in air
	int		solid;			// for client side prediction, trap_linkentity sets this properly

   float    scale;
   float    alpha;

	int		renderfx;

	int      bindparent;    // not sent over
  	float		quat[4];       // not sent over
	float		mat[3][3];     // not sent over
} entityState_t;

typedef enum {
	CA_UNINITIALIZED,
	CA_DISCONNECTED, 	// not talking to a server
	CA_AUTHORIZING,	// not used any more, was checking cd key 
	CA_CONNECTING,		// sending request packets to the server
	CA_CHALLENGING,	// sending challenge packets to the server
	CA_CONNECTED,		// netchan_t established, getting gamestate
	CA_LOADING,			// only during cg.CG_GameStateReceived, never during main loop
	CA_PRIMED,			// got gamestate, waiting for first frame
	CA_ACTIVE,			// game views should be displayed
	CA_CINEMATIC		// playing a cinematic or a static pic, not connected to a server
} connstate_t;

/*
========================================================================

SYSTEM MATH

========================================================================
*/

void MatrixMultiply(float in1[3][3], float in2[3][3], float out[3][3]);
void AnglesToAxis( const vec3_t angles, vec3_t axis[3] );
void AngleVectors( const vec3_t angles, vec3_t forward, vec3_t left, vec3_t up);
void PerpendicularVector( vec3_t dst, const vec3_t src );
void EulerToQuat( float ang[ 3 ], float q[ 4 ] );
void MatToQuat( float srcMatrix[ 3 ][ 3 ], float destQuat[ 4 ] );
void QuatToMat( float q[ 4 ], float m[ 3 ][ 3 ]	);
void MatrixToEulerAngles( float mat[ 3 ][ 3 ], vec3_t ang );


/*
========================================================================

TIKI

========================================================================
*/

#define TIKI_CMD_MAX_CMDS 128
#define TIKI_CMD_MAX_ARGS 10

typedef struct
   {
   int num_args;
   char *args[TIKI_CMD_MAX_ARGS];
   } tiki_singlecmd_t;

typedef struct
   {
   int num_cmds;
   tiki_singlecmd_t cmds[ TIKI_CMD_MAX_CMDS ];
   } tiki_cmd_t;

typedef struct
	{
	vec3_t	start;
	vec3_t	end;
	vec3_t	color;
	float		alpha;
   float    width;
   unsigned short factor;
   unsigned short pattern;
	} debugline_t;

// Added for FAKK2
#define FLOAT_TO_INT( x, fracbits ) ( ( x ) * ( 1 << ( fracbits ) ) )

#define FLOAT_TO_PKT( x, dest, wholebits, fracbits )                            \
   {                                                                            \
   if ( ( x ) >= ( 1 << ( wholebits ) ) )                                       \
      {                                                                         \
      ( dest ) = FLOAT_TO_INT( ( 1 << ( wholebits ) ), ( fracbits ) ) - 1; \
      }                                                                         \
   else if ( ( x ) < 0 )                                                        \
      {                                                                         \
      ( dest ) = 0;                                                             \
      }                                                                         \
   else                                                                         \
      {                                                                         \
      ( dest ) = FLOAT_TO_INT( ( x ), ( fracbits ) );               \
      }                                                                         \
   }

#define SIGNED_FLOAT_TO_PKT( x, dest, wholebits, fracbits )                   \
   {                                                                          \
   float temp_x;                                                              \
   temp_x = ( x ) + ( 1 << ( wholebits ) );                                   \
   if ( temp_x >= ( 1 << ( ( wholebits ) + 1 ) ) )                            \
      ( dest ) = FLOAT_TO_INT( ( 1 << ( ( wholebits ) + 1 ) ), ( fracbits ) ) - 1;    \
   else if ( temp_x < 0 )                                                     \
      (dest) = 0;                                                             \
   else                                                                       \
      ( dest ) = FLOAT_TO_INT( temp_x, ( fracbits ) );                        \
   }

#define INT_TO_FLOAT( x, wholebits, fracbits ) ( ( float )( ( ( float )( x ) ) / ( float )( 1 << ( fracbits ) ) - ( float )( 1 << ( wholebits ) ) ) )
#define UINT_TO_FLOAT( x, fracbits ) ( ( float )( ( ( float )( x ) ) / ( float )( 1 << ( fracbits ) ) ) )

#define TRANSLATION_TO_PKT( x, dest ) FLOAT_TO_PKT( ( x ), ( dest ), 4, 11 )
#define PKT_TO_TRANSLATION( x ) UINT_TO_FLOAT( ( x ), 11 )

#define OFFSET_TO_PKT( x, dest ) FLOAT_TO_PKT( ( x ), ( dest ), 1, 14 )
#define PKT_TO_OFFSET( x ) UINT_TO_FLOAT( ( x ), 14 )

#define ROTATE_TO_PKT( x, dest ) FLOAT_TO_PKT( ( x ), ( dest ), 9, 6 )
#define PKT_TO_ROTATE( x ) UINT_TO_FLOAT( ( x ), 6 )

#define BASE_TO_PKT( x, dest ) SIGNED_FLOAT_TO_PKT( ( x ), ( dest ), 3, 4 )
#define PKT_TO_BASE( x ) INT_TO_FLOAT( ( x ), 3, 4 )

#define AMPLITUDE_TO_PKT( x, dest ) FLOAT_TO_PKT( ( x ), ( dest ), 4, 4 )
#define PKT_TO_AMPLITUDE( x ) UINT_TO_FLOAT( ( x ), 4 )

#define PHASE_TO_PKT( x, dest ) SIGNED_FLOAT_TO_PKT( ( x ), ( dest ), 3, 4 )
#define PKT_TO_PHASE( x ) INT_TO_FLOAT( ( x ), 3, 4 )

#define FREQUENCY_TO_PKT( x, dest ) FLOAT_TO_PKT( ( x ), ( dest ), 4, 4 )
#define PKT_TO_FREQUENCY( x ) UINT_TO_FLOAT( ( x ), 4 )

#define BEAM_PARM_TO_PKT( x, dest ) FLOAT_TO_PKT( ( x ), ( dest ), 4, 4 )
#define PKT_TO_BEAM_PARM( x ) UINT_TO_FLOAT( ( x ), 4 )

#ifdef __cplusplus
}
#endif

#endif	// __Q_SHARED_H__
