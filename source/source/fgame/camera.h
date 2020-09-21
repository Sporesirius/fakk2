//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/camera.h                           $
// $Revision:: 21                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/25/00 11:32p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/camera.h                                $
// 
// 21    7/25/00 11:32p Aldie
// Made some changes to the memory system and fixed a memory allocation bug in
// Z_TagMalloc.  Also changed a lot of classes to subclass from Class.
// 
// 20    7/10/00 11:54p Markd
// added exit level code
// 
// 19    7/10/00 8:35p Markd
// added camera tracing to orbit
// 
// 18    7/04/00 2:25p Markd
// added cool cinematic for new objects
// 
// 17    6/28/00 12:23p Markd
// Added auto_active to cameras
// 
// 16    6/09/00 6:55p Markd
// fixed camera being bound to other objects
// 
// 15    5/26/00 7:44p Markd
// 2nd phase save games
// 
// 14    5/25/00 7:52p Markd
// 2nd pass save game stuff
// 
// 13    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 12    4/19/00 2:38p Markd
// Added auto_fov support to cameras
// 
// 11    4/19/00 12:54p Markd
// put in auto_starttime and auto_stoptime support into auto cameras
// 
// 10    4/11/00 2:46p Markd
// Implemented Automatic camera support
// 
// 9     3/16/00 11:45a Markd
// fixed a camera iniatialization bug
// 
// 8     3/15/00 2:04p Markd
// fixed up camera node system and added new debug oriented circle
// 
// 7     2/03/00 3:12p Markd
// Fixed up fadetimes for watches and fov and follow
// 
// 6     11/09/99 8:07p Markd
// Did a lot of work on the camera system
// 
// 5     11/05/99 5:55p Markd
// Added user-interface to camera system
// 
// 4     11/04/99 10:03a Markd
// complete overhaul of the camera system
// 
// 3     10/29/99 7:04p Markd
// cleaned up some camera stuff
// 
// 2     10/27/99 12:19p Markd
// added smooth camera lerping
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 10    9/01/99 6:16p Jimdose
// added SetThread
// 
// 9     7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
// 
// DESCRIPTION:
// Camera.  Duh.
// 

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "g_local.h"
#include "entity.h"
#include "bspline.h"
#include "container.h"

#define CAMERA_SWITCHTIME 0.5f

#define ORBIT		( 1 << 0 )
#define START_ON	( 1 << 1 )
#define AUTOMATIC ( 1 << 2 )
#define NO_TRACE  ( 1 << 3 )
#define NO_WATCH  ( 1 << 4 )
#define LEVEL_EXIT ( 1 << 5 )


extern Event EV_Camera_CameraThink;
extern Event EV_Camera_StartMoving;
extern Event EV_Camera_Pause;
extern Event EV_Camera_Continue;
extern Event EV_Camera_StopMoving;
extern Event EV_Camera_SetSpeed;
extern Event EV_Camera_SetFollowDistance;
extern Event EV_Camera_SetOrbitHeight;
extern Event EV_Camera_SetYaw;
extern Event EV_Camera_AbsoluteYaw;
extern Event EV_Camera_RelativeYaw;
extern Event EV_Camera_SetFOV;
extern Event EV_Camera_Orbit;
extern Event EV_Camera_Follow;
extern Event EV_Camera_Watch;
extern Event EV_Camera_WatchPath;
extern Event EV_Camera_LookAt;
extern Event EV_Camera_TurnTo;
extern Event EV_Camera_MoveToEntity;
extern Event EV_Camera_MoveToPos;
extern Event EV_Camera_NoWatch;
extern Event EV_Camera_FadeTime;
extern Event EV_Camera_Cut;

class Camera;

class CameraMoveState : public Class
   {
   public:
      Vector            pos;
      Vector            movedir;    // direction of travel
      Vector            angles;     // angles from spline camera

	   BSpline				cameraPath;
      SplinePathPtr     splinePath;
      SplinePathPtr     currentNode;
      SplinePathPtr     loopNode;

	   float					cameraTime;
      int               lastTime;
      int               newTime;

      qboolean          followingpath;
	   EntityPtr			followEnt;
      EntityPtr         orbitEnt;

		void		      operator=( CameraMoveState &newstate );
      void           Evaluate( Camera * camera );
      void           Initialize( Camera * camera );
      void           DoNodeEvents( Camera * camera );
	   virtual void   Archive( Archiver &arc );
   };

inline void CameraMoveState::operator=
	(
	CameraMoveState &newstate
	)

	{
   movedir = newstate.movedir;
   pos = newstate.pos;
   angles = newstate.angles;

   cameraPath = newstate.cameraPath;
   splinePath = newstate.splinePath;
   currentNode = newstate.currentNode;
   loopNode = newstate.loopNode;

   cameraTime = newstate.cameraTime;
   lastTime = newstate.lastTime;
   newTime = newstate.newTime;

   followEnt = newstate.followEnt;
   orbitEnt = newstate.orbitEnt;

   followingpath = newstate.followingpath;
	}

inline void CameraMoveState::Archive
	(
	Archiver &arc
	)
   {
   arc.ArchiveVector( &movedir );
   arc.ArchiveVector( &pos );
   arc.ArchiveVector( &angles );

   cameraPath.Archive( arc );

   arc.ArchiveSafePointer( &splinePath );
   arc.ArchiveSafePointer( &currentNode );
   arc.ArchiveSafePointer( &loopNode );

   arc.ArchiveFloat( &cameraTime );
   arc.ArchiveInteger( &lastTime );
   arc.ArchiveInteger( &newTime );

   arc.ArchiveSafePointer( &followEnt );
   arc.ArchiveSafePointer( &orbitEnt );

   arc.ArchiveBoolean( &followingpath );
   }

class CameraWatchState : public Class 
   {
   public:
      Vector            watchAngles;

	   EntityPtr			watchEnt;
      qboolean          watchNodes;
      qboolean          watchPath;

      void              Evaluate( Camera * camera, CameraMoveState * move );
      void              Initialize( Camera * camera );
	   virtual void      Archive( Archiver &arc );
   };

inline void CameraWatchState::Archive
	(
	Archiver &arc
	)
   {
   arc.ArchiveVector( &watchAngles );
   arc.ArchiveSafePointer( &watchEnt );
   arc.ArchiveBoolean( &watchNodes );
   arc.ArchiveBoolean( &watchPath );
   }

class CameraState : public Class 
   {
   public:
      CameraMoveState   move;
      CameraWatchState  watch;
      float             fov;

      void              Evaluate( Camera * camera );
      void              Initialize( Camera * camera );
	   virtual void      Archive( Archiver &arc );
   };

inline void CameraState::Archive
	(
	Archiver &arc
	)
   {
   move.Archive( arc );
   watch.Archive( arc );
   arc.ArchiveFloat( &fov );
   }

class Camera : public Entity
	{
   private:
      friend class	      CameraState;
      friend class	      CameraWatchState;
      friend class	      CameraMoveState;
      //
      // follow parameters
      //
	   float					follow_yaw;
	   qboolean				follow_yaw_fixed;
		float					follow_dist;
		int					follow_mask;

      // camera speed
	   float					camera_speed;
      // current camera fov
	   float					camera_fov;
      // orbit height
		float					orbit_height;
      // orbit_dotrace
      qboolean          orbit_dotrace;
      // whether or not auto calculate fov, a non-zero value means yes
      float             auto_fov;

      // automatic variables
      float             automatic_startTime;
      float             automatic_stopTime;
      float             automatic_radius;
      float             automatic_maxFOV;
      qboolean          automatic_active;
      Container<str>		automatic_states;

	protected:
      CameraState       currentstate;
      CameraState       newstate;

      float             watchTime;  // if non-zero, camera view is transitioning
      float             followTime; // if non-zero, camera position is tranisitioning
      float             fovTime;    // if non-zero, fov is being lerped

      float             fadeTime; // time to transition over
      float             fovFadeTime; // time for fov transition
      float             followFadeTime; // time for fov transition
      float             watchFadeTime; // time for fov transition

      str               nextCamera;
      str               thread;

		qboolean				showcamera;

		void					SetupCamera( Event *ev );
		void					CameraThink( Event *ev );
		void					CreateOrbit( Vector pos, float radius, Vector &forward, Vector &left );
		void					CreatePath( SplinePath *path, splinetype_t type );
      void              UpdateStates( void );
      Vector            CalculatePosition( void );
      Vector            CalculateOrientation( void	);
      float             CalculateFov( void );
      virtual void      bind( Entity *master, qboolean use_my_angles = false );
      virtual void      unbind( void );

	public:
      CLASS_PROTOTYPE( Camera );

								Camera();
		void					Stop( void );
		void					FollowPath( SplinePath *path, qboolean loop, Entity *watch );
		void					Orbit( Entity *ent, float dist, Entity *watch, float yaw_offset = 0, qboolean dotrace = qtrue );
		void					FollowEntity( Entity *ent, float dist, int mask, Entity *watch = NULL );
      void              Watch( str watch, float time );
      void              Watch( Entity *ent, float time );
      void              SetFOV( float fov, float time	);

		void					StartMoving( Event *ev );
		void					StopMoving( Event *ev );
		void					Pause( Event *ev );
		void					Continue( Event *ev );
      void              SetAnglesEvent( Event *ev );
		void					SetSpeed( Event *ev );
		void					SetFollowDistance( Event *ev );
		void					SetOrbitHeight( float height );
		void					SetOrbitHeight( Event *ev );
		void					SetFollowYaw( Event *ev );
		void					AbsoluteYaw( Event *ev );
		void					RelativeYaw( Event *ev );
		void					SetFOV( Event *ev );
		void					OrbitEvent( Event *ev );
		void					FollowEvent( Event *ev );
		void					WatchEvent( Event *ev );
		void					WatchPathEvent( Event *ev );
		void					WatchNodesEvent( Event *ev );
		void					NoWatchEvent( Event *ev );
		void					LookAt( Event *ev );
		void					MoveToEntity( Event *ev );
		void					MoveToPos( Event *ev );
		void					Cut( Event *ev );
		void					FadeTime( Event *ev );
		void					TurnTo( Event *ev );
      void              SetNextCamera( Event *ev );
      void              SetThread( Event *ev );
      float             CalculateScore( Entity * player, str state );
      float             AutomaticStart( Entity * player );
      float             AutomaticStop( Entity * player );
      qboolean          IsAutomatic( void );
      qboolean          IsLevelExit( void );
      void              SetAutoStateEvent( Event * ev );
      void              SetAutoRadiusEvent( Event * ev );
      void              SetAutoStartTimeEvent( Event * ev );
      void              SetAutoStopTimeEvent( Event * ev );
      void              SetMaximumAutoFOVEvent( Event * ev );
      void              SetAutoActiveEvent( Event * ev );

      str               &NextCamera( void );
      str               &Thread( void );
      float             Fov( void );

      void              Reset( Vector org, Vector ang );

	   virtual void      Archive( Archiver &arc );
	};

inline void Camera::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.ArchiveFloat( &follow_yaw );
   arc.ArchiveBoolean( &follow_yaw_fixed );
   arc.ArchiveFloat( &follow_dist );
   arc.ArchiveInteger( &follow_mask );

   arc.ArchiveFloat( &camera_speed );
   arc.ArchiveFloat( &camera_fov );
   arc.ArchiveFloat( &orbit_height );
   arc.ArchiveBoolean( &orbit_dotrace );
   arc.ArchiveFloat( &auto_fov );

   arc.ArchiveFloat( &automatic_startTime );
   arc.ArchiveFloat( &automatic_stopTime );
   arc.ArchiveFloat( &automatic_radius );
   arc.ArchiveFloat( &automatic_maxFOV );
   arc.ArchiveBoolean( &automatic_active );

   automatic_states.Archive( arc );

   // currentstate
   currentstate.Archive( arc );
   // newstate
   newstate.Archive( arc );

   arc.ArchiveFloat( &watchTime );
   arc.ArchiveFloat( &followTime );
   arc.ArchiveFloat( &fovTime );
   arc.ArchiveFloat( &fadeTime );
   arc.ArchiveFloat( &fovFadeTime );
   arc.ArchiveFloat( &followFadeTime );
   arc.ArchiveFloat( &watchFadeTime );

   arc.ArchiveString( &nextCamera );
   arc.ArchiveString( &thread );

   arc.ArchiveBoolean( &showcamera );

   if ( arc.Loading() )
      {
      if ( spawnflags & AUTOMATIC )
         {
         level.AddAutomaticCamera( this );
         }
      }
   }

void SetCamera( Entity *ent, float switchTime );
Entity * GetWatchEntity( str watch );

typedef SafePtr<Camera> CameraPtr;

class CameraManager : public Listener
   {
   protected:
      Container<str>    pathList;
	   BSpline				cameraPath;
      SplinePathPtr     path;
      SplinePathPtr     current;
      float             speed;
      int               watch;
      str               pathName;
      CameraPtr         cam;
      qboolean          cameraPath_dirty;

      void              NewPath( Event *ev );
      void              SetPath( Event *ev );
      void              SetTargetName( Event *ev );
      void              SetTarget( Event *ev );
      void              SetThread( Event *ev );
      void              AddPoint( Event *ev );
      void              ReplacePoint( Event *ev );
      void              DeletePoint( Event *ev );
      void              MovePlayer( Event *ev );
      void              NextPoint( Event *ev );
      void              PreviousPoint( Event *ev );
      void              ShowingPath( Event *ev );
      void              ShowPath( Event *ev );
      void              HidePath( Event *ev );
      void              StopPlayback( Event *ev );
      void              PlayPath( Event *ev );
      void              LoopPath( Event *ev );
      void              Watch( Event *ev );
      void              NoWatch( Event *ev );
      void              Fov( Event *ev );
      void              FadeTime( Event *ev );
      void              Speed( Event *ev );
      void              Save( Event *ev );
      void              Load( Event *ev );
      void              SaveMap( Event *ev );
      void              UpdateEvent( Event *ev );
      void              NextPath( Event *ev );
      void              PreviousPath( Event *ev );
      void              RenamePath( Event *ev );

      void              ShowPath( void );
      void              UpdateUI( void );
      void              SetPathName( str name );
      void              SavePath( str pathName );

   public:
      CLASS_PROTOTYPE( CameraManager );

                        CameraManager();
      void              SetPath( str pathName );
	   virtual void      Archive( Archiver &arc );
   };

inline void CameraManager::Archive
	(
	Archiver &arc
	)

   {
   Listener::Archive( arc );

   pathList.Archive( arc );

   // no need to archive the cameraPath
   arc.ArchiveSafePointer( &path );
   arc.ArchiveSafePointer( &current );
   arc.ArchiveFloat( &speed );
   arc.ArchiveInteger( &watch );
   arc.ArchiveString( &pathName );
   arc.ArchiveSafePointer( &cam );

   // make sure the cameraPath gets rebuilt
   cameraPath_dirty = qtrue;
   }

extern CameraManager CameraMan;

#endif /* camera.h */
