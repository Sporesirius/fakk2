//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/scriptslave.h                      $
// $Revision:: 9                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 6/13/00 3:45p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/scriptslave.h                           $
// 
// 9     6/13/00 3:45p Steven
// Added means of death to script objects.
// 
// 8     5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 7     5/24/00 3:14p Markd
// first phase of save/load games
// 
// 6     3/29/00 5:35p Markd
// Added gravity support to script objects
// 
// 5     2/16/00 9:17a Markd
// Added skyorigin entity
// 
// 4     1/10/00 6:17p Jimdose
// more code cleanup
// 
// 3     10/29/99 3:32p Markd
// Added OpenPortal and ClosePortal
// 
// 2     10/29/99 3:16p Markd
// made scriptslave's ET_GENERAL instead of ET_MODELANIM
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 5     9/02/99 10:48p Markd
// Added animonce command
// 
// 4     8/25/99 12:42p Markd
// Fixed some minor and major scripting bugs
//
// DESCRIPTION:
// Standard scripted objects.  Controlled by scriptmaster.  These objects
// are bmodel objects created in the editor and controlled by an external
// text based script.  Commands are interpretted on by one and executed
// upon a signal from the script master.  The base script object can
// perform several different relative and specific rotations and translations
// and can cause other parts of the script to be executed when touched, damaged,
// touched, or used.
// 

#ifndef __SCRIPTSLAVE_H__
#define __SCRIPTSLAVE_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "mover.h"
#include "script.h"
#include "scriptmaster.h"
#include "misc.h"
#include "bspline.h"

class ScriptSlave : public Mover
	{
	protected:
		ThreadPtr			touchthread;
		ThreadPtr			blockthread;
		ThreadPtr			triggerthread;
		ThreadPtr			usethread;
		ThreadPtr			damagethread;
		ThreadPtr			movethread;

		str					touchlabel;
		str					uselabel;
		str					blocklabel;
		str					triggerlabel;
		str					damagelabel;
		
		float					attack_finished;
		int					dmg;
		int					dmg_means_of_death;

	public:
		qboolean				commandswaiting;
		Vector				TotalRotation;
		Vector				NewAngles;
		Vector				NewPos;
		Vector				ForwardDir;
		float					speed;
		Waypoint				*waypoint;
		float					traveltime;
		BSpline				*splinePath;
      float             splineTime;
      qboolean          splineangles;
      qboolean          ignoreangles;
      qboolean          moving;  // is the script object currently moving?

      CLASS_PROTOTYPE( ScriptSlave );

								ScriptSlave();
								~ScriptSlave();

		void					NewOrders( Event *ev );
		void					BindEvent( Event *ev );
		void					EventUnbind( Event *ev );
		void					DoMove( Event *ev );
		void					MoveEnd( Event *ev );
		void					SetAnglesEvent( Event *ev );
		void					SetAngleEvent( Event *ev );
      void              SetModelEvent( Event *ev );
		void					TriggerEvent( Event *ev );
		void					GotoNextWaypoint( Event *ev );
		void					JumpTo( Event *ev );
		void					MoveToEvent( Event *ev );
		void					SetSpeed( Event *ev );
		void					SetTime( Event *ev );
		void					MoveUp( Event *ev );
		void					MoveDown( Event *ev );
		void					MoveNorth( Event *ev );
		void					MoveSouth( Event *ev );
		void					MoveEast( Event *ev );
		void					MoveWest( Event *ev );
		void					MoveForward( Event *ev );
		void					MoveBackward( Event *ev );
		void					MoveLeft( Event *ev );
		void					MoveRight( Event *ev );
		void					RotateXdownto( Event *ev );
		void					RotateYdownto( Event *ev );
		void					RotateZdownto( Event *ev );
		void					RotateAxisdownto( Event *ev );
		void					RotateXupto( Event *ev );
		void					RotateYupto( Event *ev );
		void					RotateZupto( Event *ev );
		void					RotateAxisupto( Event *ev );
		void					Rotateupto( Event *ev );
		void					Rotatedownto( Event *ev );
		void					Rotateto( Event *ev );
		void					RotateXdown( Event *ev );
		void					RotateYdown( Event *ev );
		void					RotateZdown( Event *ev );
		void					RotateAxisdown( Event *ev );
		void					RotateXup( Event *ev );
		void					RotateYup( Event *ev );
		void					RotateZup( Event *ev );
		void					RotateAxisup( Event *ev );
		void					RotateX( Event *ev );
		void					RotateY( Event *ev );
		void					RotateZ( Event *ev );
		void					RotateAxis( Event *ev );
		void					OnTouch( Event *ev );
		void					NoTouch( Event *ev );
		void					TouchFunc( Event *ev );
		void					OnBlock( Event *ev );
		void					NoBlock( Event *ev );
		void					BlockFunc( Event *ev );
		void					OnTrigger( Event *ev );
		void					NoTrigger( Event *ev );
		void					TriggerFunc( Event *ev );
		void					OnUse( Event *ev );
		void					NoUse( Event *ev );
		void					UseFunc( Event *ev );
		void					OnDamage( Event *ev );
		void					NoDamage( Event *ev );
      void              DamageFunc( Event *ev );
      void					SetDamage( Event *ev );
		void					SetMeansOfDeath( Event *ev );
		void					FollowPath( Event *ev );
		void					EndPath( Event *ev );
		void					FollowingPath( Event *ev );
      void              CreatePath( SplinePath *path,	splinetype_t type );
      void              Explode( Event *ev );
      void              NotShootable( Event *ev );
      void              OpenPortal( Event *ev );
      void              ClosePortal( Event *ev );
      void              PhysicsOn( Event *ev );
      void              PhysicsOff( Event *ev );
      void              PhysicsVelocity( Event *ev );
      virtual void      Archive( Archiver &arc );
	};

inline void ScriptSlave::Archive
	(
	Archiver &arc
	)
   {
   int tempInt;

   Mover::Archive( arc );

   arc.ArchiveSafePointer( &touchthread );
   arc.ArchiveSafePointer( &blockthread );
   arc.ArchiveSafePointer( &triggerthread );
   arc.ArchiveSafePointer( &usethread );
   arc.ArchiveSafePointer( &damagethread );
   arc.ArchiveSafePointer( &movethread );

   arc.ArchiveString( &touchlabel );
   arc.ArchiveString( &uselabel );
   arc.ArchiveString( &blocklabel );
   arc.ArchiveString( &triggerlabel );
   arc.ArchiveString( &damagelabel );

   arc.ArchiveFloat( &attack_finished );
   arc.ArchiveInteger( &dmg );
	arc.ArchiveInteger( &dmg_means_of_death );

   arc.ArchiveBoolean( &commandswaiting );
   arc.ArchiveVector( &TotalRotation );
   arc.ArchiveVector( &NewAngles );
   arc.ArchiveVector( &NewPos );
   arc.ArchiveVector( &ForwardDir );
   arc.ArchiveFloat( &speed );
   arc.ArchiveObjectPointer( ( Class ** )&waypoint );
   arc.ArchiveFloat( &traveltime );
   if ( arc.Saving() )
      {
      // if it exists, archive it, otherwise place a special NULL ptr tag
      if ( splinePath )
         {
         tempInt = ARCHIVE_POINTER_VALID;
         }
      else
         {
         tempInt = ARCHIVE_POINTER_NULL;
         }
      arc.ArchiveInteger( &tempInt );
      if ( tempInt == ARCHIVE_POINTER_VALID )
         {
         splinePath->Archive( arc );
         }
      }
   else
      {
      arc.ArchiveInteger( &tempInt );
      if ( tempInt == ARCHIVE_POINTER_VALID )
         {
         splinePath = new BSpline;
         splinePath->Archive( arc );
         }
      else
         {
         splinePath = NULL;
         }
      }
   arc.ArchiveFloat( &splineTime );
   arc.ArchiveBoolean( &splineangles );
   arc.ArchiveBoolean( &ignoreangles );
   arc.ArchiveBoolean( &moving );
   }

class ScriptModel : public ScriptSlave
	{
   private:
      void              GibEvent(Event *ev);

   public:
      CLASS_PROTOTYPE( ScriptModel );

								ScriptModel();
		void					SetAngleEvent( Event *ev );
		void					SetModelEvent( Event *ev );
		void					SetAnimEvent( Event *ev );
		void					AnimOnceEvent( Event *ev );
	};

class ScriptOrigin : public ScriptSlave
	{
	public:
      CLASS_PROTOTYPE( ScriptOrigin );
								ScriptOrigin();
	};

class ScriptSkyOrigin : public ScriptSlave
	{
	public:
      CLASS_PROTOTYPE( ScriptSkyOrigin );
								ScriptSkyOrigin();
	};

#endif /* scriptslave.h */
