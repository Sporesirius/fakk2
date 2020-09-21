//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_local.h                         $
// $Revision:: 93                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 8/10/00 9:26p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_local.h                              $
// 
// 93    8/10/00 9:26p Aldie
// Fixed a lot of memory leaks on exit
// 
// 92    7/29/00 9:05p Aldie
// Added targeting to cg_general ents
// 
// 91    7/24/00 11:52a Aldie
// Added cg_effectdetail for reducing number of effects
// 
// 90    7/22/00 5:50p Markd
// added flushtikis support
// 
// 89    7/19/00 9:52p Aldie
// Put ET_EVENTS back in.  They will get sent over once, and should get
// processed once on the client.
// 
// 88    7/15/00 12:32p Aldie
// Fixed a bug for restarting tempmodels on a save game
// 
// 87    7/14/00 9:52p Markd
// added global volume dampener on ambient sound effects for cinematics
// 
// 86    7/10/00 11:54p Markd
// added exit level code
// 
// 85    7/07/00 2:58p Markd
// fixed alias bug
// 
// 84    6/28/00 4:36p Markd
// added debug footsteps code
// 
// 83    6/27/00 2:34p Markd
// clear out swipes when restarting
// 
// 82    6/17/00 1:54p Markd
// Added server restarted code
// 
// 81    6/15/00 8:21p Markd
// Added CleanupCommandManager support
// 
// 80    6/14/00 12:14p Markd
// more intel compiler bug fixes
// 
// 79    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 78    6/09/00 10:27a Markd
// got lagometer and CG_2D operations functioning
// 
// 77    6/06/00 1:59p Aldie
// Added fadein to marks
// 
// 76    6/05/00 3:10p Markd
// Added has_commands check to client side command processing
// 
// 75    6/03/00 8:19p Markd
// Added footstep code
// 
// 74    6/03/00 10:55a Markd
// Sped up tracing and debug print messages
// 
// 73    6/01/00 7:45p Aldie
// Made it so that swipes are removed when client entities are reset.
// 
// 72    6/01/00 12:21p Steven
// Improvement to splashes.
// 
// 71    5/20/00 5:14p Markd
// Added ITEM special effects
// 
// 70    5/17/00 6:55p Markd
// working on 3rd person camera
// 
// 69    5/16/00 6:24p Markd
// added cg_traceinfo support
// 
// 68    5/09/00 1:33p Markd
// added some lightstyle utilities to SetLightStyle
// 
// 67    5/09/00 1:23p Aldie
// Added lightstyle to marks
// 
// 66    5/08/00 6:12p Markd
// Added lightstyle support for the client
// 
// 65    5/04/00 8:38p Aldie
// Made beam emitters work better
// 
// 64    4/26/00 9:05p Markd
// Added client and cgame class commands
// 
// 63    4/10/00 11:16a Markd
// added rope code
// 
// 62    4/03/00 4:43p Markd
// fixed a teleportation issue
// 
// 61    3/31/00 11:49a Markd
// Added sky_portal control
// 
// 60    3/14/00 3:22p Aldie
// Changed some client side emitter functionality and added func_emitter
// 
// 59    3/06/00 8:07p Markd
// cleaned up unused cvar's
// 
// 58    3/04/00 6:03p Aldie
// Made commandManager static
// 
// 57    3/04/00 11:45a Markd
// Added light style support and malloc and free to the cgame
// 
// 56    3/01/00 1:45p Aldie
// Added some more beam functionality for beau.  Added taglist to do beam
// chains.
// 
// 55    2/21/00 7:03p Markd
// Added skyalpha support
// 
// 54    2/16/00 6:58p Markd
// cleaned up version of new animation system
// 
// 53    2/16/00 6:56p Markd
// added new animation system
// 
// 52    2/14/00 10:09a Markd
// Tweaked targeting reticles
// 
// 51    2/11/00 3:22p Aldie
// Changed swipe code a bit, and added cg_hidetempmodels cvar.
// 
// 50    2/08/00 6:24p Markd
// removed unused mediashader 
// 
// 49    1/27/00 9:06a Markd
// Added watermark
// 
// 48    1/19/00 3:18p Aldie
// Moved cg_updateentity
// 
// 47    1/15/00 2:39p Aldie
// Changed definition of RemoveClientEntity
// 
// 46    1/12/00 8:03p Markd
// Added NextFrameCameraCut and LastCameraFlags
// 
// 45    1/12/00 3:17p Aldie
// Fixed beams so that there may be multiple beams on a model
// 
// 44    12/11/99 5:51p Markd
// First wave of bug fixes after q3a gold merge
// 
// 43    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 42    12/09/99 7:42p Jimdose
// got rid of ignore_angles
// 
// 41    11/10/99 6:08p Steven
// Fixed the saving of sound origins of child entities.
// 
// 40    11/10/99 2:18p Jimdose
// removed some unused variables from centity_t
// added torso animation control variables
// 
// 39    11/04/99 3:18p Markd
// fixed fov lerping
// 
// 38    11/04/99 10:03a Markd
// complete overhaul of the camera system
// 
// 37    10/29/99 7:34p Aldie
// rope stuff
// 
// 36    10/29/99 7:29p Steven
// Moved sound stuff into snapshot.
// 
// 35    10/28/99 6:05p Steven
// Added a use_angles flag and an offset to the entity attach stuff.
// 
// 34    10/27/99 12:18p Markd
// added smooth camera lerping
// 
// 33    10/26/99 6:30p Jimdose
// added animation blending to animstate_t
// 
// 32    10/25/99 12:19p Jimdose
// made head and torso angles local to each entity
// 
// 31    10/22/99 6:29p Aldie
// Fix for beams in the sky
// 
// 30    10/21/99 2:51p Aldie
// Added some more beam functions
// 
// 29    10/19/99 7:52p Markd
// Removed three part model system
// 
// 28    10/19/99 11:57a Aldie
// Added some more beam features
// 
// 27    10/18/99 2:01p Aldie
// Fixed compile error
// 
// 26    10/13/99 3:26p Aldie
// Various fixes for particles, beams and lensflares
// 
// 25    10/08/99 5:47p Aldie
// More beam stuff
// 
// 24    10/08/99 5:07p Aldie
// More beam stuff and fix for UI_CenterPrint
// 
// 23    10/07/99 3:08p Aldie
// more beam fun
// 
// 22    10/07/99 9:56a Markd
// made fov come out of playerstate, not cvar
// 
// 21    10/06/99 3:23p Steven
// Added a dumpevents command.
// 
// 20    10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION:
// The entire cgame module is unloaded and reloaded on each level change,
// so there is NO persistant data between levels on the client side.
// If you absolutely need something stored, it can either be kept
// by the server in the server stored userinfos, or stashed in a cvar.


#include "../fgame/q_shared.h"
#include "tr_types.h"
#include "../fgame/bg_public.h"
#include "../qcommon/cm_public.h"
#include "cg_public.h"

#ifndef __CG_LOCAL_H__
#define __CG_LOCAL_H__

#ifdef __cplusplus
extern "C"
   {
#endif

typedef struct 
   {
   int      anim;
   int      frame;
   int      oldanim;
   int      oldframe;
   int      starttime;
   float    framelerp;
   } lerpstate_t;

typedef struct 
   {
   lerpstate_t base;

   // crossblend variables
   lerpstate_t crossblend;
   int         crossblend_totaltime;
   float       crossblend_lerp;

   // global variables
   int      numframes;
   int      time_per_frame;
   qboolean driven;

   // non-driven variables
   int      next_evaluate_time;

   // driven variables
   int      last_driven_time;
   vec3_t   last_origin;
   vec3_t   frame_delta;      // normalized frame delta
   float    frame_distance;   // float distance till next frame
   float    current_distance; // current distance traveled 

   // command variables
   qboolean has_commands;
   int      last_cmd_frame;
   int      last_cmd_anim;
   int      last_cmd_time;
   } animstate_t;

//=================================================

#define CF_UPDATESWIPE        0x0000001
#define CF_COMMANDS_PROCESSED 0x0000002

// centity_t have a direct corespondence with gentity_t in the game, but
// not all of the gentity_t will be communicated to the client
typedef struct centity_s {
	entityState_t	currentState;  	// from cg.frame
	entityState_t	nextState;		   // from cg.nextFrame, if available
   qboolean       teleported;       // true if the entity was just teleported
	qboolean		   interpolate;	   // true if next is valid to interpolate to
	qboolean		   currentValid;	   // true if cg.frame holds this entity

	int				miscTime;

   animstate_t    am;               // this holds the animation information for this model
   animstate_t    torso_am;         // this holds the torso animation information for this model

	int				errorTime;		   // decay the error from this time
	vec3_t			errorOrigin;
	vec3_t			errorAngles;
	
	qboolean		   extrapolated;	   // false if origin / angles is an interpolation
	vec3_t			rawOrigin;
	vec3_t			rawAngles;

	vec3_t			beamEnd;

	// exact interpolated position of entity on this frame
	vec3_t			lerpOrigin;
	vec3_t			lerpAngles;

	sfxHandle_t		tikiLoopSound;
	float				tikiLoopSoundVolume;
	float				tikiLoopSoundMinDist;

   float          color[4];
   float          client_color[4];  // the color set by client commands
   int            clientFlags;

	int				splash_last_spawn_time;
	int				splash_still_count;
} centity_t;


//======================================================================

// local entities are created as a result of events or predicted actions,
// and live independantly from all server transmitted entities

#define	MAX_VERTS_ON_POLY	10
#define	MAX_MARK_POLYS		64

typedef struct markPoly_s
   {
	struct markPoly_s	   *prevMark, *nextMark;
	int			         time;
   int                  lightstyle;
	qhandle_t	         markShader;
	qboolean	            alphaFade;		// fade alpha instead of rgb
   qboolean             fadein;
	float		            color[4];
	poly_t		         poly;
	polyVert_t	         verts[MAX_VERTS_ON_POLY];
   } markPoly_t;

#define	MAX_CUSTOM_SOUNDS	32
typedef struct {
	char			   name[MAX_QPATH];
	char			   data[MAX_QPATH];

	qhandle_t		legsModel;
	qhandle_t		legsSkin;

	qhandle_t		torsoModel;
	qhandle_t		torsoSkin;

	qhandle_t		headModel;
	qhandle_t		headSkin;

	struct sfx_s	*sounds[MAX_CUSTOM_SOUNDS];

	vec3_t			color;
	vec3_t			color2;
} clientInfo_t;


//======================================================================

// all cg.stepTime, cg.duckTime, cg.landTime, etc are set to cg.time when the action
// occurs, and they will have visible effects for #define STEP_TIME or whatever msec after
 
typedef struct {
	int			clientFrame;		   // incremented each frame
	
	qboolean	   demoPlayback;
	qboolean	   levelShot;		      // taking a level menu screenshot

	// there are only one or two snapshot_t that are relevent at a time
	int			latestSnapshotNum;	// the number of snapshots the client system has received
	int			latestSnapshotTime;	// the time from latestSnapshotNum, so we don't need to read the snapshot yet
	snapshot_t	*snap;				   // cg.snap->serverTime <= cg.time
	snapshot_t	*nextSnap;			   // cg.nextSnap->serverTime > cg.time, or NULL
	snapshot_t	activeSnapshots[2];

	float		   frameInterpolation;	// (float)( cg.time - cg.frame->serverTime ) / (cg.nextFrame->serverTime - cg.frame->serverTime)

	qboolean	   thisFrameTeleport;
	qboolean	   nextFrameTeleport;
	qboolean	   nextFrameCameraCut;

	int			frametime;		      // cg.time - cg.oldTime

	int			time;			         // this is the time value that the client
								            // is rendering at.
	int			oldTime;		         // time at last frame, used for missile trails and prediction checking

	int			physicsTime;	      // either cg.snap->time or cg.nextSnap->time

	int			timelimitWarnings;	// 5 min, 1 min, overtime

	qboolean	renderingThirdPerson;	// during deaths, chasecams, etc

	// prediction state
	qboolean	hyperspace;				   // true if prediction has hit a trigger_teleport
	playerState_t	predicted_player_state;
	qboolean	validPPS;				   // clear until the first call to CG_PredictPlayerState
	int			predictedErrorTime;
	vec3_t		predictedError;

	float		   stepChange;			   // for stair up smoothing
	int			stepTime;

	float		   duckChange;			   // for duck viewheight smoothing
	int			duckTime;

	float		   landChange;			   // for landing hard
	int			landTime;

	// input state sent to server
	int			weaponSelect;

	// auto rotating items
	vec3_t		autoAngles;
	vec3_t		autoAxis[3];
	vec3_t		autoAnglesSlow;
	vec3_t		autoAxisSlow[3];
	vec3_t		autoAnglesFast;
	vec3_t		autoAxisFast[3];

	// view rendering
	refdef_t	   refdef;
   vec3_t      playerHeadPos;       // position of the players head
	vec3_t		refdefViewAngles;		// will be converted to refdef.viewaxis
   vec3_t      currentViewPos;      // current position of the camera
   vec3_t      currentViewAngles;   // current angles of the camera

	float			SoundOrg[3];		   // position from where sound should be played
	vec3_t		SoundAxis[3];		   // axis from where sound should be played

   int         lastCameraTime;      // last time the camera moved
   float       lerpCameraTime;      // is the camera currently lerping from camera to view or vice versa
   qboolean    inCameraView;        // are we currently in a camera view
   vec3_t      camera_origin;       // lerped camera_origin
   vec3_t      camera_angles;       // lerped camera_angles
   float       camera_fov;          // lerped camera_fov
   int         lastCameraFlags;     // last Camera flags for interpolation testing

	// zoom key
	qboolean	   zoomed;
	int		   zoomTime;
	float	   	zoomSensitivity;

	// information screen text during loading
	char		infoScreenText[MAX_STRING_CHARS];
	qboolean	showInformation;

	// scoreboard
	int			scoresRequestTime;
	int			numScores;
	int			teamScores[2];
	qboolean	   showScores;
	int			scoreFadeTime;
	char		   killerName[MAX_NAME_LENGTH];

	// centerprinting
	int			centerPrintTime;
	int			centerPrintCharWidth;
	int			centerPrintY;
	char		   centerPrint[1024];
	int			centerPrintLines;

	// low ammo warning state
	qboolean	lowAmmoWarning;		// 1 = low, 2 = empty

	// kill timers for carnage reward
	int			lastKillTime;

	// crosshair client ID
	int			crosshairClientNum;
	int			crosshairClientTime;

   float			crosshair_offset;

	// powerup active flashing
	int			powerupActive;
	int			powerupTime;

	// attacking player
	int			attackerTime;

	// warmup countdown
	int			warmupCount;

	//==========================

	int			itemPickup;
	int			itemPickupTime;
	int			itemPickupBlendTime;	// the pulse around the crosshair is timed seperately

	int			weaponSelectTime;
	int			weaponAnimation;
	int			weaponAnimationTime;

	// blend blobs
	float		   damageTime;
	float		   damageX, damageY, damageValue;

	// status bar head
	float		   headYaw;
	float		   headEndPitch;
	float		   headEndYaw;
	int			headEndTime;
	float		   headStartPitch;
	float		   headStartYaw;
	int			headStartTime;

	// view movement
	float		v_dmg_time;
	float		v_dmg_pitch;
	float		v_dmg_roll;

	vec3_t		kick_angles;	// weapon kicks
	vec3_t		kick_origin;

	// temp working variables for player view
	float		bobfracsin;
	int			bobcycle;
	float		xyspeed;

	// development tool
	refEntity_t		testModelEntity;
	char			testModelName[MAX_QPATH];
	qboolean		testGun;

   // farplane parameters
   float       farplane_distance;
   vec3_t      farplane_color;
   qboolean    farplane_cull;

   // portal sky parameters
   qboolean    sky_portal;
   float       sky_alpha;
   vec3_t      sky_origin;
	vec3_t		sky_axis[3];			// rotation vectors
} cg_t;


typedef struct {
   qhandle_t   backTileShader;
   qhandle_t   lagometerShader;
   qhandle_t   shadowMarkShader;
   qhandle_t   wakeMarkShader;
   qhandle_t   leftTargetShader;
   qhandle_t   rightTargetShader;
   qhandle_t   itemRingShader;
   qhandle_t   leftTargetModel;
   qhandle_t   rightTargetModel;
   qhandle_t   pausedShader;
   qhandle_t   levelExitShader;
   } media_t;

// The client game static (cgs) structure hold everything
// loaded or calculated from the gamestate.  It will NOT
// be cleared when a tournement restart is done, allowing
// all clients to begin playing instantly
typedef struct {
	gameState_t		gameState;			// gamestate from server
	glconfig_t		glconfig;			// rendering configuration
	float			   screenXScale;		// derived from glconfig
	float			   screenYScale;
	float			   screenXBias;

	int				serverCommandSequence;	// reliable command stream counter
	int				processedSnapshotNum;// the number of snapshots cgame has requested

	qboolean		   localServer;		// detected on startup by checking sv_running
	int				levelStartTime;   // time that game was started

	// parsed from serverinfo
	gametype_t		gametype;
	int				dmflags;
	int				teamflags;
	int				fraglimit;
	int				timelimit;
	int				maxclients;
   int            cinematic;
	char			   mapname[MAX_QPATH];

	//
	// locally derived information from gamestate
	//
	qhandle_t		model_draw[MAX_MODELS];
   sfxHandle_t		sound_precache[MAX_SOUNDS];
	int				numInlineModels;
	qhandle_t		inlineDrawModel[MAX_MODELS];
	vec3_t			inlineModelMidpoints[MAX_MODELS];

   // TIKI handles for all models
   int            model_tiki[ MAX_MODELS ];

	clientInfo_t	clientinfo[MAX_CLIENTS];

   media_t        media;
   } cgs_t;

//==============================================================================

extern	cgs_t			         cgs;
extern	cg_t			         cg;
extern	clientGameImport_t	cgi;
extern	centity_t		      cg_entities[MAX_GENTITIES];
extern	markPoly_t		      cg_markPolys[MAX_MARK_POLYS];

extern cvar_t *cg_animSpeed;
extern cvar_t *cg_debugAnim;
extern cvar_t *cg_debugAnimWatch;
extern cvar_t *cg_errorDecay;
extern cvar_t *cg_nopredict;
extern cvar_t *cg_showmiss;
extern cvar_t *cg_addMarks;
extern cvar_t *cg_viewsize;
extern cvar_t *cg_3rd_person;
extern cvar_t *cg_syncronousClients;
extern cvar_t *cg_stereoSeparation;
extern cvar_t *cg_stats;
extern cvar_t *cg_lagometer;
extern cvar_t *paused;
extern cvar_t *r_lerpmodels;
extern cvar_t *cg_cameraheight;
extern cvar_t *cg_cameradist;
extern cvar_t *cg_cameraverticaldisplacement;
extern cvar_t *cg_camerascale;
extern cvar_t *cg_shadows;
extern cvar_t *cg_hidetempmodels;
extern cvar_t *cg_traceinfo;
extern cvar_t *cg_debugFootsteps;

//
// cg_main.c
//
void        CG_ProcessConfigString( int num );
const char *CG_ConfigString( int index );
void        CG_AddToTeamChat( const char *str );
void        CG_NewClientinfo( int clientNum );
sfxHandle_t	CG_CustomSound( int entityNum, const char *soundName );
int         CG_CrosshairPlayer( void );
int         CG_LastAttacker( void );
void        CG_Init( clientGameImport_t *imported, int serverMessageNum, int serverCommandSequence );
void        CG_Shutdown( void );
void        CG_ServerRestarted( void );

//
// cg_modelanim.cpp
//
void CG_ModelAnim( centity_t *cent );
void CG_EntityTargeted( int tikihandle, centity_t *cent, refEntity_t *model );
void CG_ClearModelAnimation( int tikihandle, animstate_t * state, int animationNumber, int time, vec3_t origin, int entnum );
void CG_AttachEntity( refEntity_t *entity, refEntity_t *parent, int tikihandle, int tagnum, qboolean use_angles, vec3_t attach_offset );

//
// cg_commands.cpp
//
void     CG_Event( centity_t *cent );
void     CG_UpdateEntity( int tikihandle, refEntity_t *ent, centity_t *cent );
void     CG_RemoveClientEntity( int number, int tikihandle, centity_t *cent );
void     CG_UpdateTestEmitter( void );
void     CG_AddTempModels( void );
void     CG_ResetTempModels( void );
void     CG_InitializeCommandManager( void );
void     CG_ProcessInitCommands( int tikihandle );
qboolean CG_Command_ProcessFile( const char * filename, qboolean quiet );
void     CG_RestartCommandManager( int timedelta );
void     CG_FlushCommandManager( void );
void     CG_ProcessEntityCommands( int            tikihandle,
                                   int            frame,
                                   int            anim,
                                   int            entnum,
                                   refEntity_t		*ent,
                                   centity_t      *cent
                                 );
void CG_ClientCommands
   (
   int            tikihandle,
   int            frame,
   int            anim,
   animstate_t    *state,
   refEntity_t		*ent,
   centity_t      *cent
   );

void CG_Splash( centity_t *cent );

void CG_EventList_f( void );
void CG_EventHelp_f( void ); 
void CG_DumpEventHelp_f( void ); 
void CG_PendingEvents_f( void );
void CG_ClassList_f( void );
void CG_ClassTree_f( void );
void CG_ClassEvents_f( void );
void CG_DumpClassEvents_f( void );
void CG_DumpAllClasses_f( void );

void L_InitEvents( void );
void L_ShutdownEvents( void );


//
// cg_view.c
//
void CG_TestModel_f (void);
void CG_TestGun_f (void);
void CG_TestModelNextFrame_f (void);
void CG_TestModelPrevFrame_f (void);
void CG_TestModelNextSkin_f (void);
void CG_TestModelPrevSkin_f (void);

void CG_ZoomDown_f( void );
void CG_ZoomUp_f( void );

void CG_DrawActiveFrame( int serverTime, stereoFrame_t stereoView, qboolean demoPlayback );


//
// cg_drawtools.c
//
void CG_AdjustFrom640( float *x, float *y, float *w, float *h );
void CG_TileClear( void );
void CG_Draw2D( void );

//
// cg_draw.c
//
void CG_AddLagometerFrameInfo( void );
void CG_AddLagometerSnapshotInfo( snapshot_t *snap );
void CG_CenterPrint( const char *str, int y, int charWidth );
void CG_DrawHead( float x, float y, float w, float h, int clientNum, vec3_t headAngles );
void CG_DrawActive( stereoFrame_t stereoView );
void CG_DrawFlagModel( float x, float y, float w, float h, int team );

//
// cg_predict.c
//
void     CG_BuildSolidList( void );
int      CG_PointContents( const vec3_t point, int passEntityNum );
void     CG_Trace( trace_t *result, const vec3_t start, const vec3_t mins, 
                   const vec3_t maxs, const vec3_t end, int skipNumber,
                   int mask, qboolean cylinder, qboolean cliptoentities, const char * description );
void     CG_PredictPlayerState( void );


//
// cg_ents.c
//
void CG_SetEntitySoundPosition( centity_t *cent );
void CG_AddPacketEntities( void );
void CG_Beam( centity_t *cent );
void CG_AdjustPositionForMover( const vec3_t in, int moverNum, int fromTime, int toTime, vec3_t out );

void CG_PositionEntityOnTag( refEntity_t *entity, const refEntity_t *parent, 
							qhandle_t parentModel, char *tagName );
void CG_PositionRotatedEntityOnTag( refEntity_t *entity, const refEntity_t *parent, 
							qhandle_t parentModel, char *tagName );
void CG_GetOrigin( centity_t *cent, vec3_t origin );
void CG_EntityEffects( centity_t *cent );

//
// cg_marks.c
//
void	CG_InitMarkPolys( void );
void	CG_AddMarks( void );
void	CG_ImpactMark( qhandle_t markShader, 
				    const vec3_t origin, const vec3_t dir, 
					float orientation, 
				    float r, float g, float b, float a, 
					qboolean alphaFade, 
					float radius, qboolean temporary,
               int lightstyle, qboolean fadein );

//
// cg_snapshot.c
//
void CG_ProcessSnapshots( void );

//
// cg_consolecmds.c
//
qboolean CG_ConsoleCommand( void );
void CG_InitConsoleCommands( void );
void CG_AddTestModel( void );

//
// cg_servercmds.c
//
void CG_ExecuteNewServerCommands( int latestSequence );
void CG_ParseServerinfo( void );

//
// cg_playerstate.c
//
void CG_TransitionPlayerState( playerState_t *ps, playerState_t *ops );

//
// cg_player.cpp
//
void CG_ResetPlayerEntity( centity_t *cent );
void CG_Player( centity_t *cent );

//
// cg_sound.cpp
//
void CG_ProcessSound( server_sound_t *sound );

//
// cg_beam.cpp
//
void CG_AddBeams( void );
void CG_MultiBeamBegin( void );
void CG_MultiBeamAddPoints
   (
   vec3_t   start,
   vec3_t   end,
   int      numsegments,
   int      flags,
   float    minoffset,
   float    maxoffset,
   qboolean addstartpoint
   );
void CG_MultiBeamEnd
   (
   float       scale,
   int         renderfx,
   const char  *beamshadername,
   byte        modulate[4],
   int         flags,
   int         owner,
   float       life
   );
void CG_CreateBeam
   (
   vec3_t         start,
   vec3_t         dir, 
   int            owner,
   qhandle_t      hModel,
   float          alpha, 
   float          scale, 
   int            flags, 
   float          length,
   int            life,
   qboolean       create,
   vec3_t         endpointvec,
   int            min_offset,
   int            max_offset,
   int            overlap,
   int            subdivisions,
   int            delay,
   const char     *beamshader,
   byte           modulate[4],
   int            numspherebeams,
   float          sphereradius,
   int            toggledelay,
   float          endalpha,
   int            renderfx,
   const char     *name
   );

void CG_KillBeams( int entity_number );
void CG_Rope( centity_t *cent );
void CG_RestartBeams( int timedelta );


//
// cg_nature.cpp
//
void CG_Emitter( centity_t *cent );

//
// cg_testemitter.cpp
void CG_InitTestEmitter( void );
void CG_TestEmitter_f( void );
void CG_DumpEmitter_f( void );
void CG_InitializeClientEmitters( void );

//
// cg_beam.cpp
void RemoveBeamList( int owner );
void CG_MultiBeam( centity_t *cent );

//
// cg_lightstyles.cpp
void CG_SetLightStyle( int num, const char *s );
#ifdef __cplusplus
qboolean CG_LightStyleColor( int style, int realtime, float color[4], qboolean clamp = qfalse );
#else
qboolean CG_LightStyleColor( int style, int realtime, float color[4], qboolean clamp );
#endif
void CG_ClearLightStyles( void );
int  CG_RegisterLightStyle( const char * name );

//
// cg_specialfx.cpp
void CG_Footstep( centity_t * ent, float volume );

//
// cg_swipe.cpp
void CG_ClearSwipes( void );


#ifdef __cplusplus
}
#endif

#endif // __CG_LOCAL_H__

