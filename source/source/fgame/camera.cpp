//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/camera.cpp                         $
// $Revision:: 55                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/28/00 1:34a                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/camera.cpp                              $
// 
// 55    7/28/00 1:34a Markd
// fixed auto_fov bug
// 
// 54    7/27/00 6:31p Markd
// made useAnim's work with doors, added key ability
// 
// 53    7/19/00 6:18p Markd
// fixed potential camera fov bug
// 
// 52    7/10/00 11:54p Markd
// added exit level code
// 
// 51    7/10/00 8:35p Markd
// added camera tracing to orbit
// 
// 50    7/07/00 1:45p Aldie
// Fixed a carriage return.
// 
// 49    7/04/00 2:25p Markd
// added cool cinematic for new objects
// 
// 48    6/29/00 9:27a Markd
// fixed camera with multiple automatic states
// 
// 47    6/28/00 12:26p Markd
// fixed scoring on automatic cameras
// 
// 46    6/28/00 12:23p Markd
// Added auto_active to cameras
// 
// 45    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 44    6/21/00 3:22p Markd
// Fixed camera bug
// 
// 43    6/21/00 1:49p Markd
// fixed camera bug
// 
// 42    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 41    6/09/00 7:14p Markd
// fixed additional bind bug with cameras
// 
// 40    6/09/00 6:55p Markd
// fixed camera being bound to other objects
// 
// 39    5/26/00 7:44p Markd
// 2nd phase save games
// 
// 38    5/08/00 5:53p Markd
// changed default start and stop time for auto cameras
// 
// 37    5/02/00 10:50a Markd
// fixed camera start problem 
// 
// 36    5/01/00 7:13p Markd
// fixed camera nodes being executed at the right time
// 
// 35    4/29/00 11:45a Markd
// fixed auto camera start and stop times
// 
// 34    4/19/00 2:38p Markd
// Added auto_fov support to cameras
// 
// 33    4/19/00 12:54p Markd
// put in auto_starttime and auto_stoptime support into auto cameras
// 
// 32    4/11/00 2:46p Markd
// Implemented Automatic camera support
// 
// 31    3/16/00 11:45a Markd
// fixed a camera iniatialization bug
// 
// 30    3/15/00 2:32p Markd
// made the node connects duller
// 
// 29    3/15/00 2:09p Markd
// forgot to take out debugging message
// 
// 27    3/15/00 2:04p Markd
// fixed up camera node system and added new debug oriented circle
// 
// 26    3/13/00 7:24p Jimdose
// put in error for when START_ON is set and no target specified
// 
// 25    2/03/00 3:12p Markd
// Fixed up fadetimes for watches and fov and follow
// 
// 24    2/01/00 5:40p Markd
// Fixed Camera cutting issues
// 
// 23    1/26/00 9:53a Markd
// Changed FOV command to an fov command
// 
// 22    1/06/00 4:39p Markd
// fixed tiki file name
// 
// 21    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 20    12/21/99 4:35p Markd
// separated camera angles into three parts and fixed sliders
// 
// 19    12/10/99 12:40p Markd
// fixed thread bug in camera system
// 
// 18    12/03/99 9:48a Markd
// put in immediate camera cutting so that it wouldn't look funny
// 
// 17    11/15/99 6:23p Markd
// fixed some comments
// 
// 16    11/15/99 12:46p Markd
// Added LerpAnglesFromCurrent
// 
// 15    11/10/99 1:46p Markd
// Fixed lerping code for watch State
// 
// 14    11/09/99 8:30p Markd
// fixed nodes to node and also made sure that saving paths would add that path
// to the pathList
// 
// 13    11/09/99 8:06p Markd
// Did a lot of work on the camera system
// 
// 12    11/05/99 5:55p Markd
// Added user-interface to camera system
// 
// 11    11/04/99 10:38a Markd
// Put in AngleMod on lerped angles to prevent weird interoplation issues
// 
// 10    11/04/99 10:03a Markd
// complete overhaul of the camera system
// 
// 9     10/29/99 7:04p Markd
// cleaned up some camera stuff
// 
// 8     10/27/99 12:19p Markd
// added smooth camera lerping
// 
// 7     10/07/99 2:59p Steven
// Event formatting.
// 
// 6     10/07/99 11:27a Markd
// made camera fixed size
// 
// 5     9/29/99 5:18p Steven
// Event formatting.
// 
// 4     9/22/99 4:47p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 3     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 26    9/01/99 9:41p Markd
// fixed camera speed
// 
// 25    9/01/99 9:06p Jimdose
// fixed bug in DoNodeEvent.  passed thread into ExecuteScript instead of
// node->thread
// 
// 24    9/01/99 6:15p Jimdose
// added setthread command to camera.  Threads are now started when camera
// reaches that node.
// now use triggertarget instead of target to store the name of the entity to
// trigger when camera reaches the node
// 
// 23    8/19/99 12:15p Jimdose
// made SetCamera check for NULL before calling isSubclass
// 
// 22    8/18/99 3:28p Jimdose
// added cylindrical collision detection
// 
// 21    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
// 
// 20    6/11/99 1:23p Phook
// 
// 19    6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
// 
// 18    6/11/99 12:46p Phook
// EClass color changes
//
// DESCRIPTION:
// Camera.  Duh.
//

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "camera.h"
#include "bspline.h"
#include "player.h"
#include "camera.h"

#define CAMERA_PATHFILE_VERSION 1

CameraManager CameraMan;

void CameraMoveState::Initialize( Camera * camera )
	{
   assert( camera );
   pos = camera->origin;
   angles = camera->angles;
   movedir = vec_zero;
	followEnt = NULL;
	orbitEnt = NULL;

   followingpath = false;
   cameraTime = 0;
   lastTime = 0;
   newTime = 0;
   cameraPath.Clear();
   splinePath = NULL;
   currentNode = NULL;
   loopNode = NULL;
   }

void CameraWatchState::Initialize( Camera * camera )
	{
   assert( camera );
   watchAngles = camera->angles;
	watchEnt = NULL;
   watchNodes = true;
   watchPath = false;
   }

void CameraState::Initialize( Camera * camera )
	{
   assert( camera );
   move.Initialize( camera );
   watch.Initialize( camera );
   fov = camera->Fov();
   }

void CameraMoveState::DoNodeEvents
   (
   Camera * camera
   )

   {
   SplinePath  *node;
   Entity      *ent;
   Event       *event;

   assert( camera );

   node = currentNode;
   if ( node )
      {
      float fadeTime;
      float newFov;

      fadeTime = node->GetFadeTime();
      if ( fadeTime == -1 )
         {
         fadeTime = camera->fadeTime;
         }

      if ( node->doWatch )
         {
         camera->Watch( node->GetWatch(), fadeTime );
         }

      newFov = node->GetFov();
      if ( newFov )
         {
         camera->SetFOV( newFov, fadeTime );
         }

      if ( node->thread != "" )
         {
         if ( !ExecuteThread( node->thread ) )
            {
            gi.Error( ERR_DROP, "Camera could not start thread '%s' from info_splinepath '%s'\n", 
               node->thread.c_str(), node->targetname.c_str() );
            }
         }

	   if ( node->triggertarget != "" )
		   {
         ent = NULL;
		   do
			   {
			   ent = G_FindTarget( ent, node->triggertarget.c_str() );
			   if ( !ent )
				   {
				   break;
				   }
		   	event = new Event( EV_Activate );
            event->AddEntity( camera );
			   ent->PostEvent( event, 0 );
            }
         while ( 1 );
         }
      }
   }

void CameraMoveState::Evaluate
	(
   Camera * camera
	)
   {
   Vector oldpos;
   float speed_multiplier;

   assert( camera );

   oldpos = pos;
   // 
   // check for node events
   // we explicitly skip the first node because we process that
   // when we begin the follow path command
   //
   if ( ( lastTime != newTime ) && currentNode )
      {
      if ( newTime > 1 )
         {
         DoNodeEvents( camera );
         }
      currentNode = currentNode->GetNext();
      if ( !currentNode )
         {
         currentNode = loopNode;
         }
      }
   lastTime = newTime;

   //
   // evaluate position
   //
   if ( followingpath )
      {
   	speed_multiplier = cameraPath.Eval( cameraTime, pos, angles );

	   cameraTime += level.fixedframetime * camera->camera_speed * speed_multiplier;

   	if ( orbitEnt )
	   	{
         pos += orbitEnt->origin;
         if ( camera->orbit_dotrace )
            {
            trace_t trace;
            Vector start, back;

            start = orbitEnt->origin;
	         start[ 2 ] += orbitEnt->maxs[ 2 ];

            back = start - pos;
            back.normalize();

	         trace = G_Trace( start, vec_zero, vec_zero, pos, orbitEnt, camera->follow_mask, false, "Camera::EvaluatePosition" );

            if ( trace.fraction < 1.0f )
               {
               pos = trace.endpos;
               // step in a bit towards the followEng
               pos += back * 16;
               }
            }
		   }
      }
   else
      {
	   if ( followEnt )
         {
         trace_t trace;
         Vector start, end, ang, back;

         start = followEnt->origin;
	      start[ 2 ] += followEnt->maxs[ 2 ];

	      if ( camera->follow_yaw_fixed )
		      {
		      ang = vec_zero;
		      }
	      else
		      {
		      if ( followEnt->isSubclassOf( Player ) )
			      {
               Entity * ent;
               ent = followEnt;
               ( ( Player * )ent )->GetPlayerView( NULL, &ang );
			      }
		      else
			      {
               ang = followEnt->angles;
			      }
		      }
	      ang.y += camera->follow_yaw;
	      ang.AngleVectors( &back, NULL, NULL );

	      end = start - back * camera->follow_dist;
	      end[ 2 ] += 24;

	      trace = G_Trace( start, vec_zero, vec_zero, end, followEnt, camera->follow_mask, false, "Camera::EvaluatePosition - Orbit" );

         pos = trace.endpos;
         // step in a bit towards the followEnt
         pos += back * 16;
         }
      }

   // 
   // update times for node events
   //
   newTime = cameraTime + 2.0f;

   if ( newTime < 0 )
      {
      newTime = 0;
      }
   //
   // set movedir
   //
   movedir = pos - oldpos;
   }

void CameraWatchState::Evaluate
	(
   Camera * camera,
   CameraMoveState * move
	)
   {
   assert( camera );
   assert( move );
   //
   // evaluate orientation
   //
   if ( watchEnt )
	   {
      Vector watchPos;


      watchPos.x = watchEnt->origin.x;
      watchPos.y = watchEnt->origin.y;
	   watchPos.z = watchEnt->absmax.z;
      watchPos -= camera->origin;
		watchPos.normalize();
		watchAngles = watchPos.toAngles();
	   }
   else if ( watchNodes )
      {
      watchAngles = move->angles;
      }
   else if ( watchPath )
      {
      float  length;
      Vector delta;

      delta = move->movedir;
      length = delta.length();
      if ( length > 0.05f )
         {
         delta *= 1.0f / length;
		   watchAngles = delta.toAngles();
         }
      }
   watchAngles[ 0 ] = AngleMod( watchAngles[ 0 ] );
   watchAngles[ 1 ] = AngleMod( watchAngles[ 1 ] );
   watchAngles[ 2 ] = AngleMod( watchAngles[ 2 ] );
   }

void CameraState::Evaluate
	(
   Camera * camera
	)
   {
   move.Evaluate( camera );
   watch.Evaluate( camera, &move );
   }


Event EV_Camera_CameraThink
	( 
	"camera_think",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called each frame to allow the camera to adjust its position."
	);
Event EV_Camera_StartMoving
	( 
	"start",
	EV_DEFAULT,
   NULL,
   NULL,
   "Start camera moving."
	);
Event EV_Camera_Pause
	( 
	"pause",
	EV_DEFAULT,
   NULL,
   NULL,
   "Pause the camera."
	);
Event EV_Camera_Continue
	( 
	"continue",
	EV_DEFAULT,
   NULL,
   NULL,
   "Continue the camera movement."
	);
Event EV_Camera_StopMoving
	( "stop", 
	EV_CONSOLE,
	NULL,
   NULL,
   "Stop the camera movement."
	);
Event EV_Camera_SetSpeed
	( 
	"speed",
	EV_DEFAULT,
   "f",
   "speed",
   "Sets the camera speed."
	);
Event EV_Camera_SetFOV
	( 
	"fov",
	EV_CONSOLE,
   "fF",
   "fov fadeTime",
   "Sets the camera's field of view (fov).\n"
   "if fadeTime is specified, camera will fade over that time\n"
   "if fov is less than 3, than an auto_fov will be assumed\n"
   "the value of fov will be the ratio used for keeping a watch\n"
   "entity in the view at the right scale"
	);

//
// FOLLOW EVENTS
//
Event EV_Camera_Follow
	( 
	"follow",
	EV_DEFAULT,
   "eE",
   "targetEnt targetWatchEnt",
   "Makes the camera follow an entity and optionally watch an entity."
	);
Event EV_Camera_SetFollowDistance
	( 
	"follow_distance",
	EV_DEFAULT,
   "f",
   "distance",
   "Sets the camera follow distance."
	);
Event EV_Camera_SetFollowYaw
	( 
	"follow_yaw",
	EV_DEFAULT,
   "f",
   "yaw",
   "Sets the yaw offset of the camera following an entity."
	);
Event EV_Camera_AbsoluteYaw
	( 
	"follow_yaw_absolute",
	EV_DEFAULT,
   NULL,
   NULL,
   "Makes the follow camera yaw absolute."
	);
Event EV_Camera_RelativeYaw
	( 
	"follow_yaw_relative",
	EV_DEFAULT,
   NULL,
   NULL,
   "Makes the follow camera yaw relative (not absolute)."
	);

//
// ORBIT Events
//
Event EV_Camera_Orbit
	( 
	"orbit",
	EV_DEFAULT,
   "eE",
   "targetEnt targetWatchEnt",
   "Makes the camera orbit around an entity and optionally watch an entity."
	);
Event EV_Camera_SetOrbitHeight
	( 
	"orbit_height",
	EV_DEFAULT,
   "f",
   "height",
   "Sets the orbit camera's height."
	);

//
// Watch Events
//
Event EV_Camera_Watch
	( 
	"watch", 
	EV_CONSOLE,
	"eF",
   "watchEnt fadeTime",
   "Makes the camera watch an entity.\n"
   "if fadeTime is specified, camera will fade over that time"
	);
Event EV_Camera_WatchPath
	( 
	"watchpath", 
	EV_CONSOLE,
	"F",
	"fadeTime",
   "Makes the camera look along the path of travel.\n"
   "if fadeTime is specified, camera will fade over that time"
	);
Event EV_Camera_WatchNodes
	( 
	"watchnode", 
	EV_CONSOLE,
	"F",
	"fadeTime",
   "Makes the camera watch based on what is stored\n"
   "in the camera nodes.\n"
   "if fadeTime is specified, camera will fade over that time"
	);
Event EV_Camera_NoWatch
	( 
	"nowatch", 
	EV_CONSOLE,
	"F",
   "fadeTime",
   "Stop watching an entity or looking along a path.\n"
   "Camera is now static as far as orientation.\n"
   "if fadeTime is specified, camera will fade over that time"
	);

//
// Camera positioning events
//
Event EV_Camera_LookAt
	( 
	"lookat",
	EV_DEFAULT,
   "e",
   "ent",
   "Makes the camera look at an entity."
	);
Event EV_Camera_TurnTo
	( 
	"turnto",
	EV_DEFAULT,
   "v",
   "angle",
   "Makes the camera look in the specified direction."
	);
Event EV_Camera_MoveToEntity
	( 
	"moveto",
	EV_DEFAULT,
   "e",
   "ent",
   "Move the camera's position to that of the specified entities."
	);
Event EV_Camera_MoveToPos
	( 
	"movetopos",
	EV_DEFAULT,
   "v",
   "position",
   "Move the camera's position to the specified position."
	);

//
// Camera Transitioning events
//
Event EV_Camera_FadeTime
	( 
	"fadetime",
	EV_DEFAULT,
   "f",
   "fadetime",
   "Sets the fade time for camera transitioning."
	);
Event EV_Camera_Cut
	( 
	"cut",
	EV_DEFAULT,
   NULL,
   NULL,
   "switch camera states immediately, do not transition"
	);
Event EV_Camera_SetNextCamera
	( 
	"nextcamera",
	EV_DEFAULT,
   "s",
   "nextCamera",
   "Sets the next camera to use."
	);

Event EV_Camera_SetAutoState
	( 
	"auto_state",
	EV_DEFAULT,
   "sSSSSS",
   "state1 state2 state3 state4 state5 state6",
   "Sets the states the player needs to be in for this camera to activate."
	);

Event EV_Camera_SetAutoRadius
	( 
	"auto_radius",
	EV_DEFAULT,
   "f",
   "newRadius",
   "Sets the radius of the automatic camera."
	);

Event EV_Camera_SetAutoActive
	( 
	"auto_active",
	EV_DEFAULT,
   "b",
   "newActiveState",
   "Whether or not the auto camera is active."
	);

Event EV_Camera_SetAutoStartTime
	( 
	"auto_starttime",
	EV_DEFAULT,
   "f",
   "newTime",
   "Sets how long it takes for the camera to be switched to."
	);

Event EV_Camera_SetAutoStopTime
	( 
	"auto_stoptime",
	EV_DEFAULT,
   "f",
   "newTime",
   "Sets how long it takes for the camera switch back to the player."
	);

Event EV_Camera_SetMaximumAutoFOV
	( 
	"auto_maxfov",
	EV_DEFAULT,
   "f",
   "maxFOV",
   "Sets the maximum FOV that should be used when automatically calculating FOV."
	);

// 
// general setup functions
//
Event EV_Camera_SetThread
	( 
	"setthread", 
	EV_CONSOLE,
	"s",
   "thread",
   "Sets the thread to use."
	);
Event EV_Camera_SetThread2
	( 
	"thread",
	EV_DEFAULT,
   "s",
   "thread",
   "Sets the thread to use."
	);

Event EV_Camera_SetupCamera
	( 
	"_setupcamera",
	EV_DEFAULT,
   NULL,
   NULL,
   "setup the camera, post spawn."
	);

/*****************************************************************************/
/*       func_camera (0 0.25 0.5) (-8 -8 0) (8 8 16) ORBIT START_ON AUTOMATIC NO_TRACE NO_WATCH LEVEL_EXIT

Camera used for cinematic sequences.

"target" points to the target to orbit or follow.  If it points to a path, 
the camera will follow the path.
"speed" specifies how fast to move on the path or orbit.  (default 1).
"fov" specifies fov of camera, default 90.
if fov is less than 3 than an auto-fov feature is assumed.  The fov will then
specify the ratio to be used to keep a watched entity zoomed in and on the screen
"follow_yaw" specifies yaw of the follow camera, default 0.
"follow_distance" the distance to follow or orbit if the target is not a path. (default 128).
"orbit_height" specifies height of camera from origin for orbiting, default 128.
"nextcamera" a link to the next camera in a chain of cameras
"thread" a thread label that will be fired when the camera is looked through
"auto_state" if specified, denotes the state the player must be in for the camera to engage
any number of states can be specified and only the first few letters need be specified as well
a state of 'pipe' would mean that any player state that started with 'pipe' would trigger this
camera
"auto_radius" the radius, in which the camera will automatically turn on (default 512)
"auto_starttime" how long it takes for the camera to be switched to (default 0.2)
"auto_stoptime" how long it takes for the camera to switch back to the player (default 0.2)
"auto_maxfov" Sets the maximum FOV that should be used when automatically calculating FOV. (default 90)

ORBIT tells the camera to create a circular path around the object it points to.  
It the camera points to a path, it will loop when it gets to the end of the path.
START_ON causes the camera to be moving as soon as it is spawned.
AUTOMATIC causes the camera to be switched to automatically when the player is within
a certain radius, if "thread" is specified, that thread will be triggered when the camers is activated
NO_TRACE when the camera is in automatic mode, it will try to trace to the player before
switching automatically, this turns off that feature
NO_WATCH if this is an automatic camera, the camera will automatically watch the player 
unless this is set, camera's "score" will be affected by how close to the middle of the camera
the player is.
LEVEL_EXIT if the camera is being used, the level exit state will be set

******************************************************************************/

CLASS_DECLARATION( Entity, Camera, "func_camera" )
	{
	   { &EV_Camera_CameraThink,	   CameraThink },
		{ &EV_Activate,					StartMoving },
		{ &EV_Camera_StartMoving,		StartMoving },
		{ &EV_Camera_StopMoving,		StopMoving },
		{ &EV_Camera_Pause,				Pause },
		{ &EV_Camera_Continue,			Continue },
		{ &EV_Camera_SetSpeed,			SetSpeed },
		{ &EV_Camera_SetFollowDistance,SetFollowDistance },
		{ &EV_Camera_SetFollowYaw,		SetFollowYaw },
		{ &EV_Camera_AbsoluteYaw,		AbsoluteYaw },
		{ &EV_Camera_RelativeYaw,		RelativeYaw },
		{ &EV_Camera_SetOrbitHeight,	SetOrbitHeight },
		{ &EV_Camera_SetFOV,				SetFOV },
		{ &EV_Camera_Orbit,				OrbitEvent },
		{ &EV_Camera_Follow,				FollowEvent },
		{ &EV_Camera_Watch,				WatchEvent },
		{ &EV_Camera_WatchPath,			WatchPathEvent },
		{ &EV_Camera_WatchNodes,		WatchNodesEvent },
		{ &EV_Camera_NoWatch,			NoWatchEvent },
		{ &EV_Camera_LookAt,				LookAt },
		{ &EV_Camera_TurnTo,				TurnTo },
		{ &EV_Camera_MoveToEntity,  	MoveToEntity },
		{ &EV_Camera_MoveToPos,			MoveToPos },
		{ &EV_Camera_Cut,	            Cut },
		{ &EV_Camera_FadeTime,	      FadeTime },
		{ &EV_Camera_SetNextCamera,   SetNextCamera },
		{ &EV_Camera_SetThread,       SetThread },
		{ &EV_Camera_SetThread2,      SetThread },
		{ &EV_Camera_SetupCamera,     SetupCamera },
      { &EV_SetAngles,              SetAnglesEvent },
      { &EV_Camera_SetAutoState,    SetAutoStateEvent },
      { &EV_Camera_SetAutoRadius,   SetAutoRadiusEvent },
      { &EV_Camera_SetAutoStartTime, SetAutoStartTimeEvent },
      { &EV_Camera_SetAutoStopTime, SetAutoStopTimeEvent },
      { &EV_Camera_SetMaximumAutoFOV, SetMaximumAutoFOVEvent },
      { &EV_Camera_SetAutoActive,   SetAutoActiveEvent },

		{ NULL, NULL }
	};

Camera::Camera()
	{
   Vector ang;

	camera_fov = 90;
	camera_speed = 1;
	orbit_height = 128;
   orbit_dotrace = qtrue;
   follow_yaw = 0;
   follow_yaw_fixed = false;
	follow_dist = 128;
   follow_mask = MASK_SOLID;
   auto_fov = 0;
   automatic_maxFOV = 90;

	watchTime = 0;
   followTime = 0;
   fovTime = 0;

   fadeTime = 2.0f;

	setSolidType( SOLID_NOT );
	setMoveType( MOVETYPE_NONE );

   showcamera = sv_showcameras->integer;
	if ( showcamera )
		{
		setModel( "func_camera.tik" );
		showModel();
		}
	else
		{
		hideModel();
		}

   automatic_active = qtrue;
   automatic_radius = 512;
	automatic_states.ClearObjectList();
   automatic_startTime = 0.7f;
   automatic_stopTime = 0.7f;

   if ( !LoadingSavegame )
      {
      PostEvent( EV_Camera_SetupCamera, EV_POSTSPAWN );
      }
	}

void Camera::SetupCamera
	(
	Event *ev
	)

	{
   currentstate.Initialize( this );
   newstate.Initialize( this );

	if ( spawnflags & START_ON )
		{
		PostEvent( EV_Camera_StartMoving, 0 );
		}
   if ( spawnflags & AUTOMATIC )
      {
      level.AddAutomaticCamera( this );
      }
   }

qboolean Camera::IsAutomatic
	(
   void
	)
   {
   return ( spawnflags & AUTOMATIC );
   }

qboolean Camera::IsLevelExit
	(
   void
	)
   {
   return ( spawnflags & LEVEL_EXIT );
   }

float Camera::CalculateScore
	(
   Entity * player,
   str state
	)
   {
   int i;
   float range;
   float score;
   qboolean found;

   if ( !automatic_active )
      {
      return 10;
      }

   range = Vector( player->origin - origin ).length() / automatic_radius;
   // bias the range so that we don't immediately jump out of the camera if we are out of range
   range -= 0.1f;

   score = range;

   //
   // early exit if our score exceeds 1
   //
   if ( score > 1.0f )
      return score;

   // find out if we match a state
   found = qfalse;
   for( i = 1; i <= automatic_states.NumObjects(); i++ )
      {
      str *auto_state;

      auto_state = &automatic_states.ObjectAt( i );
      if ( !state.icmpn( state, auto_state->c_str(), auto_state->length() ) )
         {
         found = qtrue;
         break;
         }
      }

   // if we are comparing states and we haven't found a valid one...
   if ( automatic_states.NumObjects() && !found )
      {
      // if we aren't in the right state, push our score out significantly
      score += 2.0f;
      return score;
      }

   // perform a trace to the player if necessary
   if ( !( spawnflags & NO_TRACE ) && !( spawnflags & NO_WATCH ) )
      {
      trace_t trace;

      trace = G_Trace( origin, vec_zero, vec_zero, player->centroid, player, follow_mask, false, "Camera::CalculateScore" );
      if ( trace.startsolid || trace.allsolid || trace.fraction < 1.0f )
         {
         // if we are blocked, push our score out, but not too much since this may be a temporary thing
         if ( trace.startsolid || trace.allsolid )
            {
            score += 2.0f;
            return score;
            }
         else
            {
            score += 1.0f - trace.fraction;
            }
         }
      }

   // perform a dot product test for no watch cameras
   if ( spawnflags & NO_WATCH )
      {
      trace_t trace;
      float  limit;
      float  threshold;
      float  dot;
      Vector dir;

      dir = player->centroid - origin;
      dir.normalize();
      dot = dir * orientation[ 0 ];

      threshold = cos( DEG2RAD( ( camera_fov * 0.25f ) ) );
      if ( dot <= threshold )
         {
         limit = cos( DEG2RAD( ( camera_fov * 0.45f ) ) );
         if ( dot <= limit )
            {
            // we are outside the viewing cone
            score += 2.0f;
            return score;
            }
         else
            {
            // our score is a scale between the two values
            score += ( threshold - dot ) / ( limit );
            }
         }

      trace = G_Trace( origin, vec_zero, vec_zero, player->origin, player, follow_mask, false, "Camera::CalculateScore" );
      if ( trace.startsolid || trace.allsolid || trace.fraction < 1.0f )
         {
         // if we are blocked, push our score out, but not too much since this may be a temporary thing
         if ( trace.startsolid || trace.allsolid )
            {
            score += 2.0f;
            return score;
            }
         else
            {
            score += 1.0f - trace.fraction;
            }
         }
      }

   return score;
   }

float Camera::AutomaticStart
	(
   Entity * player
	)
   {
   if ( !( spawnflags & NO_WATCH ) && player )
      {
      Watch( player, 0 );
      Cut( NULL );
      }

   if ( thread.length() )
      {
      ExecuteThread( thread );
      }

   return automatic_startTime;
   }

float Camera::AutomaticStop
	(
   Entity * player
	)
   {
   Stop();
   return automatic_stopTime;
   }

void Camera::UpdateStates
	(
   void
	)

	{
   if ( followTime && watchTime )
      {
      newstate.Evaluate( this );
      }
   else if ( watchTime )
      {
      newstate.watch.Evaluate( this, &currentstate.move );
      }
   else if ( followTime )
      {
      newstate.move.Evaluate( this );
      }
   currentstate.Evaluate( this );
   }


Vector Camera::CalculatePosition
	(
   void
	)

	{
   int      i;
   float    t;
   Vector   pos;

   //
   // calcualte position
   //
   if ( followTime )
      {
		t = followTime - level.time;
      //
      // are we still fading?
      //
		if ( t <= 0 )
			{
         //
         // if not zero out the fade
         //
			t = 0;
         currentstate.move = newstate.move;
         newstate.move.Initialize( this );
			followTime = 0;
         pos = currentstate.move.pos;
			}
      else
         {
         //
         // if we are lerp over followFadeTime
         //
		   t = ( followFadeTime - t ) / followFadeTime;

         for ( i = 0; i < 3; i++ )
            {
            pos[ i ] = currentstate.move.pos[ i ] + ( t * ( newstate.move.pos[ i ] - currentstate.move.pos[ i ] ) );
            }
         }
      }
   else
      {
      pos = currentstate.move.pos;
      }

   return pos;
   }


Vector Camera::CalculateOrientation
	(
   void
	)

	{
   int      i;
   float    t;
   Vector   ang;

   // 
   // calculate orientation
   //
   if ( watchTime )
      {
		t = watchTime - level.time;
      //
      // are we still fading?
      //
		if ( t <= 0 )
			{
         //
         // if not zero out the fade
         //
			t = 0;
         currentstate.watch = newstate.watch;
         newstate.watch.Initialize( this );
			watchTime = 0;
         ang = currentstate.watch.watchAngles;
			}
      else
         {
		   t = ( watchFadeTime - t ) / watchFadeTime;

         for ( i=0; i<3; i++ ) 
            {
            ang[ i ] = LerpAngleFromCurrent
               ( 
               currentstate.watch.watchAngles[ i ], 
               newstate.watch.watchAngles[ i ], 
               this->angles[ i ], 
               t 
               );
            }
         /*
         warning("", "%.2f a x%.0f y%.0f z%.0f c x%.0f y%.0f z%.0f n x%.0f y%.0f z%.0f\n",
            t,
            ang[ 0 ],
            ang[ 1 ],
            ang[ 2 ],
            currentstate.watch.watchAngles[ 0 ],
            currentstate.watch.watchAngles[ 1 ],
            currentstate.watch.watchAngles[ 2 ],
            newstate.watch.watchAngles[ 0 ],
            newstate.watch.watchAngles[ 1 ],
            newstate.watch.watchAngles[ 2 ]
            );
         */
         }
      }
   else
      {
      ang = currentstate.watch.watchAngles;
      }

   return ang;
   }

float Camera::CalculateFov
	(
   void
	)

	{
   float    fov;
   float    t;

   //
   // calculate fov
   //
   // check if we have an auto_fov
   if ( auto_fov > 0 )
      {
      if ( currentstate.watch.watchEnt )
         {
         float distance;
         float size;
         float new_fov;
         Entity * ent;

         ent = currentstate.watch.watchEnt;
         size = ent->maxs[ 2 ] - ent->mins[ 2 ];
         size = ent->edict->radius / 2;
         // cap the size
         if ( size < 16 )
            size = 16;
         distance = Vector( ent->centroid - origin ).length();
         new_fov = RAD2DEG( 2.0f * atan2( size, distance * auto_fov ) );
         if ( new_fov > automatic_maxFOV )
            new_fov = automatic_maxFOV;
         else if ( new_fov < 5 )
            new_fov = 5;
         return new_fov;
         }
      else
         {
         return 90;
         }
      }
   // if we get here, we don't have an auto_fov, or we have an invalid watch target
   if ( fovTime )
      {
		t = fovTime - level.time;
      //
      // are we still fading?
      //
		if ( t <= 0 )
			{
         //
         // if not zero out the fade
         //
			t = 0;
         currentstate.fov = newstate.fov;
			fovTime = 0;
         fov = currentstate.fov;
			}
      else
         {
         //
         // if we are lerp over fovFadeTime
         //
		   t = ( fovFadeTime - t ) / fovFadeTime;
         fov = currentstate.fov + ( t * ( newstate.fov - currentstate.fov ) );
         }
      }
   else
      {
      fov = currentstate.fov;
      }

   return fov;
   }

void Camera::CameraThink
	(
	Event *ev
	)

	{
   UpdateStates();

   setOrigin( CalculatePosition() );
   setAngles( CalculateOrientation() );
   camera_fov = CalculateFov();

   //
   // debug info
   //
   if ( sv_showcameras->integer != showcamera )
		{
      showcamera = sv_showcameras->integer;
		if ( showcamera )
			{
			setModel( "func_camera.tik" );
			showModel();
			}
		else
			{
			hideModel();
			}
		}

   if ( sv_showcameras->integer != showcamera )
	   {
      showcamera = sv_showcameras->integer;
	   if ( showcamera )
		   {
		   setModel( "func_camera.tik" );
		   showModel();
		   }
	   else
		   {
		   hideModel();
		   }
	   }
	if ( showcamera && currentstate.move.followingpath )
		{
		G_Color3f( 1, 1, 0 );
   	if ( currentstate.move.orbitEnt )
			{
         currentstate.move.cameraPath.DrawCurve( currentstate.move.orbitEnt->origin, 10 );
			}
		else
			{
			currentstate.move.cameraPath.DrawCurve( 10 );
			}
		}

	CancelEventsOfType( EV_Camera_CameraThink );
	PostEvent( EV_Camera_CameraThink, FRAMETIME );
	}

void Camera::LookAt
	(
	Event *ev
	)

	{
   Vector pos, delta;
   Entity * ent;

	ent = ev->GetEntity( 1 );

   if ( !ent )
      return;

   pos.x = ent->origin.x;
   pos.y = ent->origin.y;
	pos.z = ent->absmax.z;
   delta = pos - origin;
   delta.normalize();

   currentstate.watch.watchAngles = delta.toAngles();
   setAngles( currentstate.watch.watchAngles );
	}

void Camera::TurnTo
	(
	Event *ev
	)

	{
   currentstate.watch.watchAngles = ev->GetVector( 1 );
   setAngles( currentstate.watch.watchAngles );
	}

void Camera::MoveToEntity
	(
	Event *ev
	)

	{
   Entity * ent;

	ent = ev->GetEntity( 1 );
   if ( ent )
      currentstate.move.pos = ent->origin;
   setOrigin( currentstate.move.pos );
	}

void Camera::MoveToPos
	(
	Event *ev
	)

	{
   currentstate.move.pos = ev->GetVector( 1 );
   setOrigin( currentstate.move.pos );
	}

void Camera::Stop
	(
	void
	)

	{
   if ( followTime )
      {
      currentstate.move = newstate.move;
      newstate.move.Initialize( this );
      }
   if ( watchTime )
      {
      currentstate.watch = newstate.watch;
      newstate.watch.Initialize( this );
      }
	CancelEventsOfType( EV_Camera_CameraThink );

   watchTime = 0;
   followTime = 0;
	}

void Camera::CreateOrbit
	(
	Vector pos,
	float radius,
   Vector &forward,
   Vector &left
	)

	{
	newstate.move.cameraPath.Clear();
	newstate.move.cameraPath.SetType( SPLINE_LOOP );

	newstate.move.cameraPath.AppendControlPoint( pos + radius * forward );
	newstate.move.cameraPath.AppendControlPoint( pos + radius * left );
	newstate.move.cameraPath.AppendControlPoint( pos - radius * forward );
	newstate.move.cameraPath.AppendControlPoint( pos - radius * left );
	}

void Camera::CreatePath
	(
	SplinePath *path,
	splinetype_t type
	)

	{
	SplinePath	*node;
	SplinePath	*loop;

	newstate.move.cameraPath.Clear();
	newstate.move.cameraPath.SetType( type );

   newstate.move.splinePath = path;
   newstate.move.currentNode = path;
   newstate.move.loopNode = NULL;

	node = path;
	while( node != NULL )
		{
      newstate.move.cameraPath.AppendControlPoint( node->origin, node->angles, node->speed );
		loop = node->GetLoop();
      if ( loop && ( type == SPLINE_LOOP ) )
         {
         newstate.move.loopNode = loop;
         newstate.move.cameraPath.SetLoopPoint( loop->origin );
         }
		node = node->GetNext();

		if ( node == path )
			{
			break;
			}
		}

   if ( ( type == SPLINE_LOOP ) && ( !newstate.move.loopNode ) )
      {
      newstate.move.loopNode = path;
      }
	}

void Camera::FollowPath
	(
	SplinePath *path,
	qboolean loop,
   Entity * watch
	)

	{
   // make sure we process any setup events before continuing
   ProcessPendingEvents();

	Stop();
	if ( loop )
		{
		CreatePath( path, SPLINE_LOOP );
		}
	else
		{
		CreatePath( path, SPLINE_CLAMP );
		}

   newstate.move.cameraTime = -2;
   newstate.move.lastTime = 0;
   newstate.move.newTime = 0;
   newstate.move.currentNode = path;
   // evaluate the first node events
   newstate.move.DoNodeEvents( this );

   if ( watch )
      {
      newstate.watch.watchEnt = watch;
      }
   else
      {
      Watch( newstate.move.currentNode->GetWatch(), newstate.move.currentNode->GetFadeTime() );
      }

   followFadeTime = fadeTime;
   watchFadeTime = fadeTime;

   newstate.move.followingpath = true;
   followTime = level.time + followFadeTime;
   watchTime = level.time + watchFadeTime;

	PostEvent( EV_Camera_CameraThink, FRAMETIME );
	}

void Camera::Orbit
	(
	Entity *ent,
	float dist,
   Entity *watch,
   float yaw_offset,
   qboolean dotrace
	)

	{
   Vector ang, forward, left;

   // make sure we process any setup events before continuing
   ProcessPendingEvents();

	Stop();

   if ( watch )
      {
      ang = watch->angles;
      ang.y += yaw_offset;
      }
   else
      {
      ang = vec_zero;
      ang.y += yaw_offset;
      }
   ang.AngleVectors( &forward, &left, NULL );

   orbit_dotrace = dotrace;

	CreateOrbit( Vector( 0, 0, orbit_height ), dist, forward, left );
   newstate.move.cameraTime = -2;
   newstate.move.lastTime = 0;
   newstate.move.newTime = 0;

	newstate.move.orbitEnt = ent;

   followFadeTime = fadeTime;
   watchFadeTime = fadeTime;

   newstate.move.followingpath = true;
   followTime = level.time + followFadeTime;
   watchTime = level.time + watchFadeTime;
   newstate.move.currentNode = NULL;

   if ( watch )
      {
      newstate.watch.watchEnt = watch;
      }
   else
      {
	   newstate.watch.watchEnt = ent;
      }

	PostEvent( EV_Camera_CameraThink, FRAMETIME );
	}

void Camera::FollowEntity
	(
	Entity *ent,
	float dist,
	int mask,
   Entity *watch
	)

	{
   // make sure we process any setup events before continuing
   ProcessPendingEvents();

	assert( ent );

	Stop();

	if ( ent )
		{
	   newstate.move.followEnt = ent;
      newstate.move.followingpath = false;

      followFadeTime = fadeTime;
      watchFadeTime = fadeTime;

      newstate.move.cameraTime = -2;
      newstate.move.lastTime = 0;
      newstate.move.newTime = 0;
      newstate.move.currentNode = NULL;

      followTime = level.time + followFadeTime;
      watchTime = level.time + watchFadeTime;
      if ( watch )
         {
         newstate.watch.watchEnt = watch;
         }
      else
         {
	      newstate.watch.watchEnt = ent;
         }
		follow_dist = dist;
		follow_mask = mask;
		PostEvent( EV_Camera_CameraThink, 0 );
		}
	}

void Camera::StartMoving
	(
	Event *ev
	)

	{
   Entity *targetEnt;
   Entity *targetWatchEnt;
	Entity *ent;
	SplinePath *path;

   if ( ev->NumArgs() > 0 )
      {
      targetEnt = ev->GetEntity( 1 );
      }
   else
      {
      targetEnt = NULL;
      }

   if ( ev->NumArgs() > 1 )
      {
      targetWatchEnt = ev->GetEntity( 2 );
      }
   else
      {
      targetWatchEnt = NULL;
      }

	if ( ( spawnflags & START_ON ) && ( !Q_stricmp( Target(), "" ) ) )
      {
      gi.Error( ERR_DROP, "Camera '%s' with START_ON selected, but no target specified.", TargetName() );
      }

   if ( !targetEnt )
		{
		ent = G_FindTarget( NULL, Target() );
		if ( !ent )
			{
         //
         // we took this out just because of too many warnings, oh well
			//warning("StartMoving", "Can't find target for camera\n" );
         //
         // I put it back in as an error.  Fuck em!  Yeeeeeha!
         //
         gi.Error( ERR_DROP, "Can't find target '%s' for camera\n", Target() );
			return;
			}
		}
	else
		{
		ent = targetEnt;
		}

	if ( ent->isSubclassOf( SplinePath ) )
		{
		path = ( SplinePath * )ent;
		FollowPath( path, spawnflags & ORBIT, targetWatchEnt );
		}
	else
		{
		if ( spawnflags & ORBIT )
			{
			Orbit( ent, follow_dist, targetWatchEnt );
			}
		else
			{
			FollowEntity( ent, follow_dist, follow_mask, targetWatchEnt );
			}
		}
	}

void Camera::SetAutoStateEvent
	(
	Event *ev
	)

	{
   int i;

   for( i = 1; i <= ev->NumArgs(); i++ )
      {
      char  *buffer;
      char	com_token[ MAX_QPATH ];
      char  com_buffer[MAX_STRING_CHARS]; 

      strcpy( com_buffer, ev->GetString( i ) );
      buffer = com_buffer;
      // get the rest of the line
      while( 1 )
         {
         strcpy( com_token, COM_ParseExt( &buffer, qfalse ) );
         if (!com_token[0])
            break;

         automatic_states.AddUniqueObject( str( com_token ) );
         }
      }
	}

void Camera::SetMaximumAutoFOVEvent
	(
	Event *ev
	)

	{
   automatic_maxFOV = ev->GetFloat( 1 );
	}

void Camera::SetAutoRadiusEvent
	(
	Event *ev
	)

	{
   automatic_radius = ev->GetFloat( 1 );
	}

void Camera::SetAutoActiveEvent
	(
	Event *ev
	)

	{
   automatic_active = ev->GetBoolean( 1 );
	}

void Camera::SetAutoStartTimeEvent
	(
	Event *ev
	)

	{
   automatic_startTime = ev->GetFloat( 1 );
	}

void Camera::SetAutoStopTimeEvent
	(
	Event *ev
	)

	{
   automatic_stopTime = ev->GetFloat( 1 );
	}


void Camera::StopMoving
	(
	Event *ev
	)

	{
	Stop();
	}

void Camera::Pause
	(
	Event *ev
	)

	{
	CancelEventsOfType( EV_Camera_CameraThink );
	}

void Camera::Continue
	(
	Event *ev
	)

	{
	CancelEventsOfType( EV_Camera_CameraThink );
	PostEvent( EV_Camera_CameraThink, 0 );
	}

void Camera::SetAnglesEvent
   (
   Event *ev
   )

   {
   Vector ang;

	ang = ev->GetVector( 1 );
   setAngles( ang );
   }

void Camera::SetSpeed
	(
	Event *ev
	)

	{
   camera_speed = ev->GetFloat( 1 );
	}

void Camera::SetFollowDistance
	(
	Event *ev
	)

	{
   follow_dist = ev->GetFloat( 1 );
	}

void Camera::SetOrbitHeight
	(
   float height
	)

	{
   orbit_height = height;
	}

void Camera::SetOrbitHeight
	(
	Event *ev
	)

	{
   orbit_height = ev->GetFloat( 1 );
	}

void Camera::SetFollowYaw
	(
	Event *ev
	)

	{
	follow_yaw = ev->GetFloat( 1 );
	}

void Camera::AbsoluteYaw
	(
	Event *ev
	)

	{
	follow_yaw_fixed = true;
	}

void Camera::RelativeYaw
	(
	Event *ev
	)

	{
	follow_yaw_fixed = false;
	}

void Camera::SetNextCamera
	(
	Event *ev
	)

	{
   nextCamera = ev->GetString( 1 );
	}

void Camera::Cut
	(
	Event *ev
	)
	{
   int         j;

   if ( followTime )
      {
      currentstate.move = newstate.move;
      newstate.move.Initialize( this );
      followTime = 0;
      }
   if ( watchTime )
      {
      currentstate.watch = newstate.watch;
      newstate.watch.Initialize( this );
      watchTime = 0;
      }
   if ( fovTime )
      {
      currentstate.fov = newstate.fov;
      newstate.fov = camera_fov;
      fovTime = 0;
      }
	CancelEventsOfType( EV_Camera_CameraThink );
	ProcessEvent( EV_Camera_CameraThink );

   //
   // let any clients know that this camera has just cut
   //
	for( j = 0; j < game.maxclients; j++ )
		{
      gentity_t   *other;
      Player      *client;

      other = &g_entities[ j ];
		if ( other->inuse && other->client )
			{
         client = ( Player * )other->entity;
         client->CameraCut( this );
			}
      }
	}

void Camera::FadeTime
	(
	Event *ev
	)

	{
   fadeTime = ev->GetFloat( 1 );
	}

void Camera::OrbitEvent
	(
	Event *ev
	)

	{
	Entity *ent;

	spawnflags |= ORBIT;
	ent = ev->GetEntity( 1 );
	if ( ent )
		{
      Event * event;

      event = new Event( EV_Camera_StartMoving );
      event->AddEntity( ent );
      if ( ev->NumArgs() > 1 )
         {
         event->AddEntity( ev->GetEntity( 2 ) );
         }
		Stop();
		ProcessEvent( event );
		}
	}

void Camera::FollowEvent
	(
	Event *ev
	)

	{
	Entity *ent;

	spawnflags &= ~ORBIT;
	ent = ev->GetEntity( 1 );
	if ( ent )
		{
      Event * event;

      event = new Event( EV_Camera_StartMoving );
      event->AddEntity( ent );
      if ( ev->NumArgs() > 1 )
         {
         event->AddEntity( ev->GetEntity( 2 ) );
         }
		Stop();
		ProcessEvent( event );
		}
	}

void Camera::SetFOV
	(
	Event *ev
	)

	{
   float time;

   if ( ev->NumArgs() > 1 )
      {
      time = ev->GetFloat( 2 );
      }
   else
      {
      time = fadeTime;
      }

   SetFOV( ev->GetFloat( 1 ), time );
	}

void Camera::WatchEvent
	(
	Event *ev
	)

	{
   float time;

   if ( ev->NumArgs() > 1 )
      {
      time = ev->GetFloat( 2 );
      }
   else
      {
      time = fadeTime;
      }

   Watch( ev->GetString( 1 ), time );
	}

Entity * GetWatchEntity
	(
   str watch
	)

	{
   const char *name;
   Entity * ent;

   // 
   // if empty just return
   //
   if ( watch == "" )
      {
      return NULL;
      }

   //
   // ignore all the reserved words
   //
   if ( 
         ( watch == "path" ) ||
         ( watch == "none" ) ||
         ( watch == "node" )
      )
      {
      return NULL;
      }

   name = watch.c_str();

   if ( name[ 0 ] == '*' )
      {
		if ( !IsNumeric( &name[ 1 ] ) )
			{
			gi.DPrintf( "GetWatchEntity :: Expecting a numeric value but found '%s'.", &name[ 1 ] );
			return NULL;
			}
		else
			{
         ent = G_GetEntity( atoi( &name[ 1 ] ) );
		   if ( !ent )
			   {
			   gi.DPrintf( "GetWatchEntity :: Entity with targetname of '%s' not found", &name[ 1 ] );
			   return NULL;
			   }
			}
      }
   else if ( name[ 0 ] == '$' )
		{
		ent = G_FindTarget( NULL, &name[ 1 ] );
		if ( !ent )
			{
			gi.DPrintf( "GetWatchEntity :: Entity with targetname of '%s' not found", &name[ 1 ] );
			return NULL;
			}
		}
   else
      {
		gi.DPrintf( "GetWatchEntity :: Entity with targetname of '%s' not found", name );
		return NULL;
      }

   return ent;
	}

void Camera::Watch
	(
   str watch,
   float time
	)

	{
   // make sure we process any setup events before continuing
   ProcessPendingEvents();

   // 
   // if empty just return
   //
   if ( watch == "" )
      return;

   //
   // clear out the watch variables
   //
   watchFadeTime = time;
   newstate.watch.watchPath = false;
   newstate.watch.watchNodes = false;
   newstate.watch.watchEnt = NULL;
   watchTime = level.time + watchFadeTime;
   //
   // really a watchpath command
   //
   if ( watch == "path" )
      {
	   newstate.watch.watchPath = true;
      }
   //
   // really a watchnodes command
   //
   else if ( watch == "node" )
      {
      newstate.watch.watchNodes = true;
      }
   //
   // really a watchnodes command
   //
   else if ( watch == "none" )
      {
      // intentionally blank
      }
   //
   // just a normal watch command
   //
   else
      {
      Entity * ent = GetWatchEntity( watch );
      newstate.watch.watchEnt = ent;
      }
	}

void Camera::Watch
	(
   Entity * ent,
   float time
	)

	{
   //
   // clear out the watch variables
   //
   watchFadeTime = time;
   newstate.watch.watchPath = false;
   newstate.watch.watchNodes = false;
   watchTime = level.time + watchFadeTime;
   newstate.watch.watchEnt = ent;
	}


void Camera::SetFOV
	(
   float fov,
   float time
	)

	{
   // if it is less than 3, then we are setting an auto_fov state
   if ( fov < 3 )
      {
      auto_fov = fov;
      }
   else
      {
      // if we are explicitly setting the fov, turn the auto_fov off
      auto_fov = 0;

      fovFadeTime = time;
   	fovTime = level.time + fovFadeTime;
      currentstate.fov = newstate.fov;
      newstate.fov = fov;
      }
	}

void Camera::WatchPathEvent
	(
	Event *ev
	)

	{
   if ( ev->NumArgs() > 1 )
      {
      watchFadeTime = ev->GetFloat( 2 );
      }
   else
      {
      watchFadeTime = fadeTime;
      }

	watchTime = level.time + watchFadeTime;
   newstate.watch.watchEnt = NULL;
	newstate.watch.watchNodes = false;
	newstate.watch.watchPath = true;
	}

void Camera::WatchNodesEvent
	(
	Event *ev
	)

	{
   if ( ev->NumArgs() > 1 )
      {
      watchFadeTime = ev->GetFloat( 2 );
      }
   else
      {
      watchFadeTime = fadeTime;
      }
	watchTime = level.time + watchFadeTime;
   newstate.watch.watchEnt = NULL;
	newstate.watch.watchPath = false;
	newstate.watch.watchNodes = true;
	}

void Camera::NoWatchEvent
	(
	Event *ev
	)

	{
   if ( ev->NumArgs() > 1 )
      {
      watchFadeTime = ev->GetFloat( 2 );
      }
   else
      {
      watchFadeTime = fadeTime;
      }
	watchTime = level.time + watchFadeTime;
   newstate.watch.watchEnt = NULL;
	newstate.watch.watchPath = false;
	newstate.watch.watchNodes = false;
	}

void SetCamera
	(
	Entity   *ent,
   float    switchTime
	)

	{
   int         j;
   gentity_t   *other;
   Camera      *cam;
   Player      *client;

   if ( ent && !ent->isSubclassOf( Camera ) )
      {
      return;
      }

   cam = ( Camera * )ent;
	for( j = 0; j < game.maxclients; j++ )
		{
      other = &g_entities[ j ];
		if ( other->inuse && other->client )
			{
         client = ( Player * )other->entity;
         client->SetCamera( cam, switchTime );
			}
      }
	}

str &Camera::NextCamera
	(
   void
	)

	{
   return nextCamera;
	}

void Camera::SetThread
	(
	Event *ev
	)

	{
   thread = ev->GetString( 1 );
	}

str &Camera::Thread
	(
   void
	)

	{
   return thread;
	}

float Camera::Fov
	(
   void
	)

	{
   return camera_fov;
	}

void Camera::Reset
   (
   Vector org,
   Vector ang
   )

   {
   setOrigin( org );
   setAngles( ang );
   currentstate.Initialize( this );
   newstate.Initialize( this );
   }

void Camera::bind
	(
	Entity *master,
	qboolean use_my_angles
	)

	{
   Entity::bind( master, use_my_angles );

   currentstate.move.pos = localorigin;
   }

void Camera::unbind
	(
	void
	)

	{
   Entity::unbind();

   currentstate.move.pos = origin;
	}


/******************************************************************************

  Camera Manager

******************************************************************************/

Event EV_CameraManager_NewPath
	( 
	"new", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Starts a new path."
	);
Event EV_CameraManager_SetPath
	( 
	"setpath", 
	EV_CONSOLE,
   "e",
   "path",
   "Sets the new path."
	);
Event EV_CameraManager_SetTargetName
	( 
	"settargetname", 
	EV_CONSOLE,
   "s",
   "targetname",
   "Set the targetname."
	);
Event EV_CameraManager_SetTarget
	( 
	"settarget", 
	EV_CONSOLE,
   "s",
   "target",
   "Set the trigger target."
	);
Event EV_CameraManager_AddPoint
	(
	"add", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Add a new point to the camera path where the player is standing."
	);
Event EV_CameraManager_DeletePoint
	( 
	"delete", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Delete the current path node."
	);
Event EV_CameraManager_MovePlayer
	( 
	"moveplayer", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Move the player to the current path node position."
	);
Event EV_CameraManager_ReplacePoint
	( 
	"replace", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Replace the current path node position/angle with the player's."
	);
Event EV_CameraManager_NextPoint
	( 
	"next", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Go to the next path node."
	);
Event EV_CameraManager_PreviousPoint
	( 
	"prev", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Go to the previous path node."
	);
Event EV_CameraManager_ShowPath
	( 
	"show", 
	EV_CONSOLE,
   "E",
   "path",
   "Shows the specified path."
	);
Event EV_CameraManager_ShowingPath
	( 
	"_showing_path", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Internal event for showing the path."
	);
Event EV_CameraManager_HidePath
	( 
	"hide", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Hides the paths."
	);
Event EV_CameraManager_PlayPath
	( 
	"play", 
	EV_CONSOLE,
   "E",
   "path",
   "Play the current path or the specified one once."
	);
Event EV_CameraManager_LoopPath
	( 
	"loop", 
	EV_CONSOLE,
   "E",
   "path",
   "Loop the current path or the specified one."
	);
Event EV_CameraManager_StopPlayback
	( 
	"stop", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Stop the camera playing path."
	);
Event EV_CameraManager_Watch
	( 
	"watch", 
	EV_CONSOLE,
   "s",
   "watch",
   "Set the current path node to watch something."
	);
Event EV_CameraManager_NoWatch
	( 
	"nowatch", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Set the current path node to watch nothing."
	);
Event EV_CameraManager_Fov
	( 
	"setfov", 
	EV_CONSOLE,
   "s",
   "newFOV",
   "Set the fov at the current path node."
	);
Event EV_CameraManager_FadeTime
	( 
	"setfadetime", 
	EV_CONSOLE,
   "f",
   "newFadeTime",
   "Set the fadetime of the current path node."
	);
Event EV_CameraManager_Speed
	( 
	"setspeed", 
	EV_CONSOLE,
   "f",
   "speed",
   "Set the speed of the camera at the current path node."
	);
Event EV_CameraManager_Save
	( 
	"save", 
	EV_CONSOLE,
   "s",
   "filename",
   "Saves the camera path."
	);
Event EV_CameraManager_Load
	( 
	"load", 
	EV_CONSOLE,
   "s",
   "filename",
   "Loads a camera path."
	);
Event EV_CameraManager_SaveMap
	( 
	"savemap", 
	EV_CONSOLE,
   "s",
   "filename",
   "Saves the camera path to a map file."
	);
Event EV_CameraManager_SetThread
	( 
	"setthread", 
	EV_CONSOLE,
   "s",
   "thread",
   "Sets the thread for the current path node."
	);
Event EV_CameraManager_UpdateInput
	( 
	"updateinput", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Updates the current node with user interface values."
	);

Event EV_CameraManager_NextPath
	( 
	"nextpath", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Go to the next path."
	);
Event EV_CameraManager_PreviousPath
	( 
	"prevpath", 
	EV_CONSOLE,
   NULL,
   NULL,
   "Go to the previous path."
	);

Event EV_CameraManager_RenamePath
	( 
	"renamepath", 
	EV_CONSOLE,
   "s",
   "newName",
   "Rename the path to the new name."
	);

CLASS_DECLARATION( Listener, CameraManager, NULL )
	{
      { &EV_CameraManager_NewPath,         NewPath },
      { &EV_CameraManager_SetPath,         SetPath },
      { &EV_CameraManager_SetTargetName,   SetTargetName },
      { &EV_CameraManager_SetTarget,       SetTarget },
      { &EV_CameraManager_SetThread,       SetThread },
      { &EV_CameraManager_SetPath,         SetPath },
      { &EV_CameraManager_AddPoint,        AddPoint },
      { &EV_CameraManager_ReplacePoint,    ReplacePoint },
      { &EV_CameraManager_DeletePoint,     DeletePoint },
      { &EV_CameraManager_MovePlayer,      MovePlayer },
      { &EV_CameraManager_NextPoint,       NextPoint },
      { &EV_CameraManager_PreviousPoint,   PreviousPoint },
      { &EV_CameraManager_ShowPath,        ShowPath },
      { &EV_CameraManager_ShowingPath,     ShowingPath },
      { &EV_CameraManager_HidePath,        HidePath },
      { &EV_CameraManager_PlayPath,        PlayPath },
      { &EV_CameraManager_LoopPath,        LoopPath },
      { &EV_CameraManager_StopPlayback,    StopPlayback },
      { &EV_CameraManager_Watch,           Watch },
      { &EV_CameraManager_NoWatch,         NoWatch },
      { &EV_CameraManager_Fov,             Fov },
      { &EV_CameraManager_FadeTime,        FadeTime },
      { &EV_CameraManager_Speed,           Speed },
      { &EV_CameraManager_Save,            Save },
      { &EV_CameraManager_Load,            Load },
      { &EV_CameraManager_SaveMap,         SaveMap },
      { &EV_CameraManager_UpdateInput,     UpdateEvent },
      { &EV_CameraManager_NextPath,        NextPath },
      { &EV_CameraManager_PreviousPath,    PreviousPath },
      { &EV_CameraManager_RenamePath,      RenamePath },
		{ NULL, NULL }
	};

Player *CameraManager_GetPlayer
   (
   void
   )

   {
   assert( g_entities[ 0 ].entity && g_entities[ 0 ].entity->isSubclassOf( Player ) );
   if ( !g_entities[ 0 ].entity || !( g_entities[ 0 ].entity->isSubclassOf( Player ) ) )
      {
      gi.Printf( "No player found.\n" );
      return NULL;
      }

   return ( Player * )g_entities[ 0 ].entity;
   }

CameraManager::CameraManager()
   {
   pathList.ClearObjectList();
   path = NULL;
   current = NULL;
   cameraPath_dirty = qtrue;
   speed = 1;
   watch = 0;
   cam = NULL;
   }

void CameraManager::UpdateUI
   (
   void
   )
   {
   int   num;
   SplinePath *next;
   float temp;

   //
   // set path name
   //
   gi.cvar_set( "cam_filename", pathName );
   if ( current )
      {

      gi.cvar_set( "cam_origin", va( "%.2f %.2f %.2f", current->origin[ 0 ], current->origin[ 1 ], current->origin[ 2 ] ) );
      gi.cvar_set( "cam_angles_yaw", va( "%.1f", current->angles[ YAW ] ) );
      gi.cvar_set( "cam_angles_pitch", va( "%.1f", current->angles[ PITCH ] ) );
      gi.cvar_set( "cam_angles_roll", va( "%.1f", current->angles[ ROLL ] ) );
      gi.cvar_set( "cam_thread", current->thread.c_str() );
      gi.cvar_set( "cam_target", current->triggertarget.c_str() );
      gi.cvar_set( "cam_watch", current->watchEnt.c_str() );
      temp = current->GetFov();
      if ( temp )
         {
         gi.cvar_set( "cam_fov", va( "%.1f", temp ) );
         }
      else
         {
         gi.cvar_set( "cam_fov", "Default" );
         }
      temp = current->GetFadeTime();
      if ( temp != -1 )
         {
         gi.cvar_set( "cam_fadetime", va( "%.2f", temp ) );
         }
      else
         {
         gi.cvar_set( "cam_fadetime", "Default" );
         }
      gi.cvar_set( "cam_speed", va( "%.1f", current->speed ) );
      if ( EventPending( EV_CameraManager_ShowingPath ) )
         {
         gi.cvar_set( "cam_hiddenstate", "visible" );
         }
      else
         {
         gi.cvar_set( "cam_hiddenstate", "hidden" );
         }

      //
      // set node num
      //
      num = 0;
      next = path;
      while ( next && ( next != current ) )
         {
         next = next->GetNext();
         num++;
         }
      gi.cvar_set( "cam_nodenum", va( "%d", num ) );
      }
   }

void CameraManager::UpdateEvent
   (
   Event *ev
   )
   {
   Vector tempvec;
   cvar_t * cvar;

   if ( !current )
      {
      return;
      }

   // get origin
   cvar = gi.cvar( "cam_origin", "", 0 );
   sscanf( cvar->string, "%f %f %f", &tempvec[ 0 ], &tempvec[ 1 ], &tempvec[ 2 ] );
   current->setOrigin( tempvec );

   // get angles yaw
   cvar = gi.cvar( "cam_angles_yaw", "", 0 );
   current->angles[ YAW ] = cvar->value;

   // get angles pitch
   cvar = gi.cvar( "cam_angles_pitch", "", 0 );
   current->angles[ PITCH ] = cvar->value;

   // get angles roll
   cvar = gi.cvar( "cam_angles_roll", "", 0 );
   current->angles[ ROLL ] = cvar->value;

   current->setAngles( current->angles );

   // get thread
   cvar = gi.cvar( "cam_thread", "", 0 );
   current->SetThread( cvar->string );

   // get target
   cvar = gi.cvar( "cam_target", "", 0 );
   current->SetTriggerTarget( cvar->string );

   // get watch
   cvar = gi.cvar( "cam_watch", "", 0 );
   current->SetWatch( cvar->string );

   // get fov
   cvar = gi.cvar( "cam_fov", "", 0 );
   current->SetFov( cvar->value );

   // get fadetime
   cvar = gi.cvar( "cam_fadetime", "", 0 );
   current->SetFadeTime( cvar->value );

   // get speed
   cvar = gi.cvar( "cam_speed", "", 0 );
   current->speed = cvar->value;
   }

void CameraManager::SetPathName
   (
   str name
   )

   {
   pathName = name;
   UpdateUI();
   }

void CameraManager::NewPath
   (
   Event *ev
   )

   {
   if ( path )
      {
      cameraPath_dirty = qtrue;
      path = NULL;
      current = NULL;
      }
   SetPathName( "untitled" );
   ShowPath();
   }

void CameraManager::RenamePath
   (
   Event *ev
   )

   {
   str name;

   if ( !ev->NumArgs() )
      {
      cvar_t * cvar;

      //
      // get the path name from the cvar
      //
      cvar = gi.cvar( "cam_filename", "", 0 );
      if ( cvar->string[ 0 ] )
         {
         name = cvar->string;
         }
      else
         {
         ev->Error( "Usage: cam renamepath [pathname]" );
	   	return;
         }
      }
   else
      {
      name = ev->GetString( 1 );
      }

   if ( pathList.ObjectInList( name ) )
      {
      // remove the old name
      pathList.RemoveObject( name );
      }
   SetPathName( name );
   pathList.AddUniqueObject( name );
   }

void CameraManager::SetPath
   (
   str      pathName
   )

   {
   Entity * ent;
   SplinePath *node;

   ent = G_FindTarget( NULL, pathName );

   if ( !ent )
      {
      warning( "SetPath", "Could not find path named '%s'.", pathName.c_str() );
      return;
      }

   if ( !ent->isSubclassOf( SplinePath ) )
      {
      warning( "SetPath", "'%s' is not a camera path.", pathName.c_str() );
      return;
      }
   node = ( SplinePath * )ent;

   SetPathName( pathName );
   cameraPath_dirty = qtrue;
   path = node;
   current = node;
   UpdateUI();
   }

void CameraManager::SetPath
   (
   Event *ev
   )

   {
   if ( !ev->NumArgs() )
      {
      ev->Error( "Usage: cam setpath [pathname]" );
      return;
      }

   SetPath( ev->GetString( 1 ) );
   }

void CameraManager::SetTargetName
   (
   Event *ev
   )

   {
	if ( ev->NumArgs() != 1 )
		{
      ev->Error( "Usage: cam targetname [name]" );
		return;
		}

   if ( !path )
      {
      ev->Error( "Camera path not set." );
      return;
      }

   path->SetTargetName( ev->GetString( 1 ) );
   UpdateUI();
   }

void CameraManager::SetTarget
   (
   Event *ev
   )

   {
	if ( ev->NumArgs() != 1 )
		{
      ev->Error( "Usage: cam target [name]" );
		return;
		}

   if ( !current )
      {
      ev->Error( "Camera path not set." );
      return;
      }

   current->SetTriggerTarget( ev->GetString( 1 ) );
   UpdateUI();
   }

void CameraManager::SetThread
   (
   Event *ev
   )

   {
	if ( ev->NumArgs() != 1 )
		{
      ev->Error( "Usage: cam thread [name]" );
		return;
		}

   if ( !current )
      {
      ev->Error( "Camera path not set." );
      return;
      }

   current->SetThread( ev->GetString( 1 ) );
   UpdateUI();
   }

void CameraManager::AddPoint
   (
   Event *ev
   )

   {
   Player *player;
   SplinePath *prev;
   SplinePath *next;
   Vector ang;
   Vector pos;

   player = CameraManager_GetPlayer();
   if ( player )
      {
      prev = current;
      if ( current )
         {
         next = current->GetNext();
         }
      else
         {
         next = NULL;
         }

      player->GetPlayerView( &pos, &ang );

      current = new SplinePath;
      current->setOrigin( pos );
      current->setAngles( ang );
      current->speed = speed;
      current->SetPrev( prev );
      current->SetNext( next );

      if ( !path )
         {
         path = current;
         }

      ShowPath();
      }
   cameraPath_dirty = qtrue;
   UpdateUI();
   }

void CameraManager::ReplacePoint
   (
   Event *ev
   )

   {
   Player *player;
   Vector ang;
   Vector pos;

   player = CameraManager_GetPlayer();
   if ( current && player )
      {
      player->GetPlayerView( &pos, &ang );

      current->setOrigin( pos );
      current->setAngles( ang );
      current->speed = speed;
      }
   cameraPath_dirty = qtrue;
   UpdateUI();
   }

void CameraManager::DeletePoint
   (
   Event *ev
   )

   {
   SplinePath *node;

   if ( current )
      {
      node = current->GetNext();
      if ( !node )
         {
         node = current->GetPrev();
         }

      if ( ( SplinePath * )path == ( SplinePath * )current )
         {
         path = current->GetNext();
         }

      delete current;
      current = node;
      }
   cameraPath_dirty = qtrue;
   UpdateUI();
   }

void CameraManager::MovePlayer
   (
   Event *ev
   )

   {
   Player *player;
   Vector pos;

   player = CameraManager_GetPlayer();
   if ( current && player )
      {
      player->GetPlayerView( &pos, NULL );

      player->setOrigin( current->origin - pos + player->origin );
      player->SetViewAngles( current->angles );
      player->SetFov( current->fov );
      }
   }

void CameraManager::NextPoint
   (
   Event *ev
   )

   {
   SplinePath *next;

   if ( current )
      {
      next = current->GetNext();
      if ( next )
         {
         current = next;
         }
      }
   UpdateUI();
   }

void CameraManager::PreviousPoint
   (
   Event *ev
   )

   {
   SplinePath *prev;

   if ( current )
      {
      prev = current->GetPrev();
      if ( prev )
         {
         current = prev;
         }
      }
   UpdateUI();
   }

void CameraManager::NextPath
   (
   Event *ev
   )

   {
   int index;

   //
   // find current path in container of paths
   //
   index = pathList.IndexOfObject( pathName );
   if ( index < pathList.NumObjects() )
      index++;

   if ( index > 0 )
      {
      SetPath( pathList.ObjectAt( index ) );
      UpdateUI();
      }
   }

void CameraManager::PreviousPath
   (
   Event *ev
   )

   {
   int index;

   //
   // find current path in container of paths
   //
   index = pathList.IndexOfObject( pathName );
   if ( index > 1 )
      index--;

   if ( index > 0 )
      {
      SetPath( pathList.ObjectAt( index ) );
      UpdateUI();
      }
   }

void CameraManager::ShowingPath
   (
   Event *ev
   )

   {
   int        count;
   SplinePath *node;
   SplinePath *prev;
   Vector mins( -8, -8, -8 );
   Vector maxs( 8, 8, 8 );

   prev = NULL;
   for( node = path; node != NULL; node = node->GetNext() )
      {
      if ( prev )
         {
         G_LineStipple( 4, ( unsigned short )( 0xF0F0F0F0 >> ( 7 - ( level.framenum & 7 ) ) ) );
         G_DebugLine( prev->origin, node->origin, 0.4, 0.4, 0.4, 0.1 );
         G_LineStipple( 1, 0xffff );
         }

      if ( current == node )
         {
         G_DrawDebugNumber( node->origin + Vector( 0, 0, 20 ), node->speed, 0.5, 0, 1, 0, 1 );
         if ( current->GetFov() )
            G_DrawDebugNumber( node->origin + Vector( 0, 0, 30 ), node->GetFov(), 0.5, 0, 0, 1, 0 );
         G_DebugBBox( node->origin, mins, maxs, 1, 1, 0, 1 );
         }
      else
         {
         G_DebugBBox( node->origin, mins, maxs, 1, 0, 0, 1 );
         }

      // 
      // draw watch
      //
      if ( node->doWatch )
         {
         Entity *watchEnt;
         Vector ang;
         Vector delta;
         Vector left;
         Vector up;
         Vector endpoint;

         watchEnt = GetWatchEntity( node->GetWatch() );
         if ( watchEnt )
            {
            delta.x = watchEnt->origin.x;
            delta.y = watchEnt->origin.y;
	         delta.z = watchEnt->absmax.z;
            delta -= node->origin;
            delta.normalize();
		      ang = delta.toAngles();
            ang.AngleVectors( NULL, &left, &up );

            G_LineWidth( 1 );
            endpoint = node->origin + delta * 48;
            G_DebugLine( node->origin, endpoint, 0.5, 1, 1, 1 );
            G_DebugLine( endpoint, endpoint + (left * 8) - (delta * 8), 0.5, 1, 1, 1 );
            G_DebugLine( endpoint, endpoint - (left * 8) - (delta * 8), 0.5, 1, 1, 1 );
            G_DebugLine( endpoint, endpoint - (up * 8) - (delta * 8), 0.5, 1, 1, 1 );
            G_DebugLine( endpoint, endpoint + (up * 8) - (delta * 8), 0.5, 1, 1, 1 );
            }
         }

      G_LineWidth( 3 );
      G_DebugLine( node->origin, node->origin + Vector( node->orientation[ 0 ] ) * 16, 1, 0, 0, 1 );
      G_DebugLine( node->origin, node->origin + Vector( node->orientation[ 1 ] ) * 16, 0, 1, 0, 1 );
      G_DebugLine( node->origin, node->origin + Vector( node->orientation[ 2 ] ) * 16, 0, 0, 1, 1 );
      G_LineWidth( 1 );

      prev = node;
      }

   if ( cameraPath_dirty )
      {
      cameraPath_dirty = qfalse;
	   cameraPath.Clear();
	   cameraPath.SetType( SPLINE_CLAMP );

	   node = path;
	   while( node != NULL )
		   {
         cameraPath.AppendControlPoint( node->origin, node->angles, node->speed );
		   node = node->GetNext();

		   if ( node == path )
			   {
			   break;
			   }
		   }
	   }

   // draw the curve itself
	G_Color3f( 1, 1, 0 );
   cameraPath.DrawCurve( 10 );

   // draw all the nodes
   for( node = path, count = -1; node != NULL; node = node->GetNext(), count++ )
      {
      Vector dir, angles;

      dir = cameraPath.Eval( ( float )count - 0.9f ) - cameraPath.Eval( count - 1 );
      angles = dir.toAngles();
      if ( node->doWatch || node->GetFov() || ( node->thread != "" ) || ( node->triggertarget != "" ) )
         {
         G_DebugOrientedCircle( cameraPath.Eval( count - 1 ), 5, 0, 1, 1, 1, angles );
         }
      else
         {
         G_DebugOrientedCircle( cameraPath.Eval( count - 1 ), 2, 0, 0, 1, 0.2, angles );
         }
      // if we are the first node, we need to skip the count so that we properly go to the next node
      if ( count == -1 )
         {
         count = 0;
         }
      }


   PostEvent( EV_CameraManager_ShowingPath, FRAMETIME );
   }

void CameraManager::ShowPath
   (
   void
   )

   {
   CancelEventsOfType( EV_CameraManager_ShowingPath );
   PostEvent( EV_CameraManager_ShowingPath, FRAMETIME );
   UpdateUI();
   }

void CameraManager::ShowPath
   (
   Event *ev
   )

   {
   if ( ev->NumArgs() )
      {
      SetPath( ev->GetString( 1 ) );
      }
   ShowPath();
   }

void CameraManager::HidePath
   (
   Event *ev
   )

   {
   CancelEventsOfType( EV_CameraManager_ShowingPath );
   UpdateUI();
   }

void CameraManager::StopPlayback
   (
   Event *ev
   )

   {
   if ( cam )
      {
      cam->Stop();
      SetCamera( NULL, 0 );
      }
   }

void CameraManager::PlayPath
   (
   Event *ev
   )

   {
   if ( cam )
      {
      SetCamera( NULL, 0 );
      }

   if ( ev->NumArgs() )
      {
      SetPath( ev->GetString( 1 ) );
      }

   if ( path )
      {
      if ( !cam )
         {
         cam = new Camera;
         cam->SetTargetName( "_loadedcamera" );
         cam->ProcessPendingEvents();
         }
      
      cam->Reset( path->origin, path->angles );
      cam->FollowPath( path, false, NULL );
      cam->Cut( NULL );
      SetCamera( cam, 0 );
      }
   }

void CameraManager::LoopPath
   (
   Event *ev
   )

   {
   if ( cam )
      {
      SetCamera( NULL, 0 );
      }

   if ( ev->NumArgs() )
      {
      SetPath( ev->GetString( 1 ) );
      }

   if ( path )
      {
      if ( !cam )
         {
         cam = new Camera;
         cam->SetTargetName( "_loadedcamera" );
         cam->ProcessPendingEvents();
         }

      cam->Reset( path->origin, path->angles );
      cam->FollowPath( path, true, NULL );
      cam->Cut( NULL );
      SetCamera( cam, 0 );
      }
   }

void CameraManager::Watch
   (
   Event *ev
   )

   {
   if ( current )
      {
      current->SetWatch( ev->GetString( 1 ) );
      }
   UpdateUI();
   }

void CameraManager::NoWatch
   (
   Event *ev
   )

   {
   if ( current )
      {
      current->NoWatch();
      }
   UpdateUI();
   }

void CameraManager::Fov
   (
   Event *ev
   )

   {
   if ( current )
      {
      current->SetFov( ev->GetFloat( 1 ) );
      }
   UpdateUI();
   }

void CameraManager::FadeTime
   (
   Event *ev
   )

   {
   if ( current )
      {
      current->SetFadeTime( ev->GetFloat( 1 ) );
      }
   UpdateUI();
   }


void CameraManager::Speed
   (
   Event *ev
   )

   {
   speed = ev->GetFloat( 1 );
   if ( current )
      {
      current->speed = speed;
      }
   cameraPath_dirty = qtrue;
   UpdateUI();
   }

void CameraManager::SavePath
   (
   str pathName
   )
   {
   SplinePath  *node;
   str         buf;
	str         filename;
   int         num;
   int         index;

   num = 0;
   for( node = path; node != NULL; node = node->GetNext() )
      {
      num++;
      }

   if ( num == 0 )
      {
      warning( "CameraManager::SavePath", "Can't save.  No points in path." );
		return;
      }

	filename = "cams/";
	filename += pathName;
	filename += ".cam";

   path->SetTargetName( pathName );

   gi.Printf( "Saving camera path to '%s'...\n", filename.c_str() );

   buf = "";
   buf += va( "//\n" );
   buf += va( "// Camera Path \"%s\", %d Nodes.\n", pathName.c_str(), num );
   buf += va( "//\n" );

   index = 0;
   for( node = path; node != NULL; node = node->GetNext() )
      {
      //
      // start off the spawn command
      //
      buf += "spawn SplinePath";
      //
      // set the targetname
      //
      if ( !index )
         {
         buf += va( " targetname %s", pathName.c_str() );
         }
      else
         {
         buf += va( " targetname camnode_%s_%d", pathName.c_str(), index );
         }
      // 
      // set the target
      //
      if ( index < ( num - 1 ) )
         {
         buf += va( " target camnode_%s_%d", pathName.c_str(), index + 1 );
         }
      //
      // set the trigger target
      //
      if ( node->triggertarget != "" )
         {
         buf += va( " triggertarget %s", node->triggertarget.c_str() );
         }
      //
      // set the thread
      //
      if ( node->thread != "" )
         {
         buf += va( " thread %s", node->thread.c_str() );
         }
      //
      // set the origin
      //
      buf += va( " origin \"%.2f %.2f %.2f\"", node->origin.x, node->origin.y, node->origin.z );
      //
      // set the angles
      //
      buf += va( " angles \"%.1f %.1f %.1f\"", AngleMod( node->angles.x ), AngleMod( node->angles.y ), AngleMod( node->angles.z ) );
      //
      // set the speed
      //
      buf += va( " speed %.1f", node->speed );
      //
      // set the watch
      //
      if ( node->doWatch && node->watchEnt != "" )
         {
         buf += va( " watch %s", node->watchEnt.c_str() );
         }
      //
      // set the fov
      //
      if ( node->GetFov() )
         {
         buf += va( " fov %.1f", node->GetFov() );
         }
      //
      // set the fadetime
      //
      if ( node->GetFadeTime() )
         {
         buf += va( " fadetime %.1f", node->GetFadeTime() );
         }

      buf += "\n";
      index++;
      }
   buf += "end\n";

   gi.FS_WriteFile( filename.c_str(), buf.c_str(), buf.length() + 1 );
   gi.Printf( "done.\n" );
   }

void CameraManager::Save
   (
   Event *ev
   )

   {
	str filename;
   str name;

	if ( ev->NumArgs() != 1 )
		{
      cvar_t * cvar;

      //
      // get the path name from the cvar
      //
      cvar = gi.cvar( "cam_filename", "", 0 );
      if ( cvar->string[ 0 ] )
         {
         name = cvar->string;
         }
      else
         {
         ev->Error( "Usage: cam save [filename]" );
	   	return;
         }
		}
   else
      {
	   name = ev->GetString( 1 );
      }
   SavePath( name );
   pathList.AddUniqueObject( name );
   }

void CameraManager::Load
   (
   Event *ev
   )

   {
   ScriptThread * thread;
   qboolean show;
	str		filename;
   str      name;

	if ( ev->NumArgs() != 1 )
		{
      cvar_t * cvar;

      //
      // get the path name from the cvar
      //
      cvar = gi.cvar( "cam_filename", "", 0 );
      if ( cvar->string[ 0 ] )
         {
         show = true;
         name = cvar->string;
         }
      else
         {
         ev->Error( "Usage: cam load [filename]" );
	   	return;
         }
		}
   else
      {
      show = false;
      name = ev->GetString( 1 );
      }

   if ( pathList.ObjectInList( name ) && show )
      {
      gi.Printf( "Camera path '%s' already loaded...\n", name.c_str() );
      return;
      }

	filename = "cams/";
	filename += name;
	filename += ".cam";

   gi.Printf( "Loading camera path from '%s'...", filename.c_str() );

   thread = Director.CreateThread( filename, LEVEL_SCRIPT, NULL );
   if ( thread )
      {
      // start right away
      thread->StartImmediately();
      pathList.AddUniqueObject( name );
      if ( show )
         {
         Event * ev;

         ev = new Event( EV_CameraManager_SetPath );
         ev->AddString( name );
         PostEvent( ev, 0 );
         ShowPath();
         }
      gi.Printf( "done.\n" );
      }
   else
      {
      gi.Printf( "failed.\n" );
      }
   }


void CameraManager::SaveMap
   (
   Event *ev
   )

   {
   SplinePath  *node;
   str         buf;
	str         filename;
   int         num;
   int         index;

	if ( ev->NumArgs() != 1 )
		{
      ev->Error( "Usage: cam savemap [filename]" );
		return;
		}

   num = 0;
   for( node = path; node != NULL; node = node->GetNext() )
      {
      num++;
      }

   if ( num == 0 )
      {
      ev->Error( "Can't save.  No points in path." );
		return;
      }

	filename = "cams/";
	filename += ev->GetString( 1 );
	filename += ".map";

   if ( !path->targetname.length() )
      {
      path->SetTargetName( ev->GetString( 1 ) );
      gi.Printf( "Targetname set to '%s'\n", path->targetname.c_str() );
      }

   gi.Printf( "Saving camera path to map '%s'...\n", filename.c_str() );

   buf = "";
   index = 0;
   for( node = path; node != NULL; node = node->GetNext() )
      {
      buf += va( "// pathnode %d\n", index );
      buf += "{\n";
      buf += va( "\"classname\" \"info_splinepath\"\n" );
      if ( index < ( num - 1 ) )
         {
         buf += va( "\"target\" \"camnode_%s_%d\"\n", ev->GetString( 1 ), index + 1 );
         }
      if ( !index )
         {
         buf += va( "\"targetname\" \"%s\"\n", ev->GetString( 1 ) );
         }
      else
         {
         buf += va( "\"targetname\" \"camnode_%s_%d\"\n", ev->GetString( 1 ), index );
         }
      if ( node->triggertarget != "" )
         {
         buf += va( "\"triggertarget\" \"%s\"\n", node->triggertarget.c_str() );
         }
      if ( node->thread != "" )
         {
         buf += va( "\"thread\" \"%s\"\n", node->thread.c_str() );
         }
      buf += va( "\"origin\" \"%d %d %d\"\n", ( int )node->origin.x, ( int )node->origin.y, ( int )node->origin.z );
      buf += va( "\"angles\" \"%d %d %d\"\n", ( int )AngleMod( node->angles.x ), ( int )AngleMod( node->angles.y ), ( int )AngleMod( node->angles.z ) );
      buf += va( "\"speed\" \"%.3f\"\n", node->speed );
      buf += "}\n";
      index++;
      }

   gi.FS_WriteFile( filename.c_str(), buf.c_str(), buf.length() + 1 );
   gi.Printf( "done.\n" );
   }

