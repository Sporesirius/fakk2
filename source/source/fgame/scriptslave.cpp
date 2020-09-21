//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/scriptslave.cpp                    $
// $Revision:: 27                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/23/00 6:56p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/scriptslave.cpp                         $
// 
// 27    7/23/00 6:56p Markd
// fixed potential followpath bugs
// 
// 26    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 25    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 24    6/13/00 3:45p Steven
// Added means of death to script objects.
// 
// 23    6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 22    5/10/00 10:32a Steven
// Added com_blood stuff.
// 
// 21    4/10/00 1:50p Markd
// fixed ontouch on non-solid entities
// 
// 20    4/04/00 5:45p Markd
// fixed script_object's not becoming non-solid
// 
// 19    3/29/00 5:35p Markd
// Added gravity support to script objects
// 
// 18    3/22/00 4:43p Jimdose
// fixed typo in ScriptSlave::FollowPath that made ignoreangles not work
// 
// 17    2/16/00 9:17a Markd
// Added skyorigin entity
// 
// 16    2/03/00 7:27p Aldie
// Fix traveltime bug
// 
// 15    1/27/00 11:35a Markd
// Fixed solid/notsolid client side entities
// 
// 14    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 13    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 12    1/14/00 5:07p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 11    1/12/00 6:15p Jimdose
// rewrote CreateExplosion
// 
// 10    1/10/00 6:17p Jimdose
// more code cleanup
// 
// 9     1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 8     10/29/99 3:32p Markd
// Added OpenPortal and ClosePortal
// 
// 7     10/29/99 3:16p Markd
// made scriptslave's ET_GENERAL instead of ET_MODELANIM
// 
// 6     10/19/99 11:57a Aldie
// Added some more beam features
// 
// 5     10/07/99 3:01p Steven
// Event formatting.
// 
// 4     9/27/99 5:45p Markd
// began documentation and cleanup phase after merge
// 
// 3     9/22/99 4:48p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 2     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 25    9/02/99 10:48p Markd
// Added animonce command
// 
// 24    8/28/99 3:34p Jimdose
// got rid of GetDouble
// 
// 23    8/26/99 5:18p Markd
// sprites should not be solid
// 
// 22    8/26/99 5:05p Phook
// 
// 21    8/25/99 12:42p Markd
// Fixed some minor and major scripting bugs
// 
// 20    8/24/99 2:07p Markd
// made script_model's bounding box variable sized based on model
// 
// 19    6/11/99 2:20p Phook
// Renamed a few entities
// 
// 18    6/11/99 1:23p Phook
// 
// 17    6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
// 
// 16    6/11/99 12:46p Phook
// EClass color changes
//
// DESCRIPTION:
// Standard scripted objects.  Controlled by ScriptThread.  These objects
// are bmodel objects created in the editor and controlled by an external
// text based script.  Commands are interpretted on by one and executed
// upon a signal from the script master.  The base script object can
// perform several different relative and specific rotations and translations
// and can cause other parts of the script to be executed when touched, damaged,
// touched, or used.
//

#include "g_local.h"
#include "class.h"
#include "mover.h"
#include "scriptmaster.h"
#include "scriptslave.h"
#include "sentient.h"
#include "item.h"
#include "gibs.h"
#include "explosion.h"

/*****************************************************************************/
/*QUAKED script_object (0 0.5 1) ? NOT_SOLID

******************************************************************************/

Event EV_ScriptSlave_DoMove
	( 
	"processCommands",
	EV_DEFAULT,
	NULL,
	NULL,
	"Move the script slave."
	);
Event EV_ScriptSlave_NewOrders
	( 
	"newOrders",
	EV_DEFAULT,
	NULL,
	NULL,
	"Inform script that it is about to get new orders."
	);
Event EV_ScriptSlave_Angles
	( 
	"angles",
	EV_DEFAULT,
	"v",
	"angles",
	"Sets the angles."
	);
Event EV_ScriptSlave_Trigger
	( 
	"trigger",
	EV_DEFAULT,
	"e",
	"ent",
	"Trigger entities target."
	);
Event EV_ScriptSlave_Next
	( 
	"next",
	EV_DEFAULT,
	NULL,
	NULL,
	"Goto the next waypoint."
	);
Event EV_ScriptSlave_JumpTo
	( 
	"jumpto",
	EV_DEFAULT,
	"s",
	"vector_or_entity",
	"Jump to specified vector or entity."
	);
Event EV_ScriptSlave_MoveTo
	( 
	"moveto",
	EV_DEFAULT,
	"s",
	"vector_or_entity",
	"Move to the specified vector or entity."
	);
Event EV_ScriptSlave_Speed
	( 
	"speed",
	EV_DEFAULT,
	"f",
	"speed",
	"Sets the speed."
	);
Event EV_ScriptSlave_Time
	( 
	"time",
	EV_DEFAULT,
	"f",
	"travel_time",
	"Sets the travel time."
	);
Event EV_ScriptSlave_MoveUp
	(
	"moveUp",
	EV_DEFAULT,
	"f",
	"dist",
	"Move the position up."
	);
Event EV_ScriptSlave_MoveDown
	( 
	"moveDown",
	EV_DEFAULT,
	"f",
	"dist",
	"Move the position down."
	);
Event EV_ScriptSlave_MoveNorth
	( 
	"moveNorth",
	EV_DEFAULT,
	"f",
	"dist",
	"Move the position north."
	);
Event EV_ScriptSlave_MoveSouth
	( 
	"moveSouth",
	EV_DEFAULT,
	"f",
	"dist",
	"Move the position south."
	);
Event EV_ScriptSlave_MoveEast
	( 
	"moveEast",
	EV_DEFAULT,
	"f",
	"dist",
	"Move the position east."
	);
Event EV_ScriptSlave_MoveWest
	( 
	"moveWest",
	EV_DEFAULT,
	"f",
	"dist",
	"Move the position west."
	);
Event EV_ScriptSlave_MoveForward
	( 
	"moveForward",
	EV_DEFAULT,
	"f",
	"dist",
	"Move the position forward."
	);
Event EV_ScriptSlave_MoveBackward
	( 
	"moveBackward",
	EV_DEFAULT,
	"f",
	"dist",
	"Move the position backward."
	);
Event EV_ScriptSlave_MoveLeft
	( 
	"moveLeft",
	EV_DEFAULT,
	"f",
	"dist",
	"Move the position left."
	);
Event EV_ScriptSlave_MoveRight
	( 
	"moveRight",
	EV_DEFAULT,
	"f",
	"dist",
	"Move the position right."
	);
Event EV_ScriptSlave_RotateXDownTo
	( 
	"rotateXdownto",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the x down to angle."
	);
Event EV_ScriptSlave_RotateYDownTo
	( 
	"rotateYdownto",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the y down to angle."
	);
Event EV_ScriptSlave_RotateZDownTo
	( 
	"rotateZdownto",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the z down to angle."
	);
Event EV_ScriptSlave_RotateAxisDownTo
	( 
	"rotateaxisdownto",
	EV_DEFAULT,
	"if",
	"axis angle",
	"Rotate the specified axis down to angle."
	);
Event EV_ScriptSlave_RotateXUpTo
	( 
	"rotateXupto",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the x up to angle."
	);
Event EV_ScriptSlave_RotateYUpTo
	( 
	"rotateYupto",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the y up to angle."
	);
Event EV_ScriptSlave_RotateZUpTo
	( 
	"rotateZupto",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the z up to angle."
	);
Event EV_ScriptSlave_RotateAxisUpTo
	( 
	"rotateaxisupto",
	EV_DEFAULT,
	"if",
	"axis angle",
	"Rotate the specified axis up to angle."
	);
Event EV_ScriptSlave_RotateXDown
	( 
	"rotateXdown",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the x down by the specified amount."
	);
Event EV_ScriptSlave_RotateYDown
	( 
	"rotateYdown",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the y down by the specified amount."
	);
Event EV_ScriptSlave_RotateZDown
	( 
	"rotateZdown",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the z down by the specified amount."
	);
Event EV_ScriptSlave_RotateAxisDown
	( 
	"rotateaxisdown",
	EV_DEFAULT,
	"if",
	"axis angle",
	"Rotate the specified axis down by the specified amount."
	);
Event EV_ScriptSlave_RotateXUp
	( 
	"rotateXup",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the x up by the specified amount."
	);
Event EV_ScriptSlave_RotateYUp
	( 
	"rotateYup",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the y up by the specified amount."
	);
Event EV_ScriptSlave_RotateZUp
	( 
	"rotateZup",
	EV_DEFAULT,
	"f",
	"angle",
	"Rotate the z up by the specified amount."
	);
Event EV_ScriptSlave_RotateAxisUp
	( 
	"rotateaxisup",
	EV_DEFAULT,
	"if",
	"axis angle",
	"Rotate the specified axis up by the specified amount."
	);
Event EV_ScriptSlave_RotateX
	( 
	"rotateX",
	EV_DEFAULT,
	"f",
	"avelocity",
	"Rotate about the x axis at the specified angular velocity."
	);
Event EV_ScriptSlave_RotateY
	( 
	"rotateY",
	EV_DEFAULT,
	"f",
	"avelocity",
	"Rotate about the y axis at the specified angular velocity."
	);
Event EV_ScriptSlave_RotateZ
	( 
	"rotateZ",
	EV_DEFAULT,
	"f",
	"avelocity",
	"Rotate about the z axis at the specified angular velocity."
	);
Event EV_ScriptSlave_RotateAxis
	( 
	"rotateaxis",
	EV_DEFAULT,
	"if",
	"axis avelocity",
	"Rotate about the specified axis at the specified angular velocity."
	);
Event EV_ScriptSlave_RotateDownTo
	( 
	"rotatedownto",
	EV_DEFAULT,
	"v",
	"direction",
	"Rotate down to the specified direction."
	);
Event EV_ScriptSlave_RotateUpTo
	( 
	"rotateupto",
	EV_DEFAULT,
	"v",
	"direction",
	"Rotate up to the specified direction."
	);
Event EV_ScriptSlave_RotateTo
	( 
	"rotateto",
	EV_DEFAULT,
	"v",
	"direction",
	"Rotate to the specified direction."
	);
Event EV_ScriptSlave_OnTouch
	( 
	"ontouch",
	EV_DEFAULT,
	"s",
	"label",
	"Sets what label to jump to and process script at when touched."
	);
Event EV_ScriptSlave_NoTouch
	( 
	"notouch",
	EV_DEFAULT,
	NULL,
	NULL,
	"Removes the ontouch thread."
	);
Event EV_ScriptSlave_OnUse
	( 
	"onuse",
	EV_DEFAULT,
	"s",
	"label",
	"Sets what label to jump to and process script at when used."
	);
Event EV_ScriptSlave_NoUse
	( 
	"nouse",
	EV_DEFAULT,
	NULL,
	NULL,
	"Removes the onuse thread."
	);
Event EV_ScriptSlave_OnBlock
	( 
	"onblock",
	EV_DEFAULT,
	"s",
	"label",
	"Sets what label to jump to and process script at when blocked."
	);
Event EV_ScriptSlave_NoBlock
	( 
	"noblock",
	EV_DEFAULT,
	NULL,
	NULL,
	"Removes the onblock thread."
	);
Event EV_ScriptSlave_OnTrigger
	( 
	"ontrigger",
	EV_DEFAULT,
	"s",
	"label",
	"Sets what label to jump to and process script at when triggered."
	);
Event EV_ScriptSlave_NoTrigger
	( 
	"notrigger",
	EV_DEFAULT,
	NULL,
	NULL,
	"Removes the ontrigger thread."
	);
Event EV_ScriptSlave_OnDamage
	( 
	"ondamage",
	EV_DEFAULT,
	"s",
	"label",
	"Sets what label to jump to and process script at when damaged."
	);
Event EV_ScriptSlave_NoDamage
	( 
	"nodamage",
	EV_DEFAULT,
	NULL,
	NULL,
	"Removes the ondamage thread."
	);
Event EV_ScriptSlave_SetDamage
	( 
	"setdamage",
	EV_DEFAULT,
	"i",
	"damage",
	"Set the damage."
	);
Event EV_ScriptSlave_SetMeansOfDeath
	( 
	"setmeansofdeath",
	EV_DEFAULT,
	"s",
	"means_of_death",
	"Set the damage means of death."
	);
Event EV_ScriptSlave_SetDamageSpawn
	( 
	"dmg",
	EV_DEFAULT,
	"i",
	"damage",
	"Set the damage."
	);
Event EV_ScriptSlave_FollowPath
	( 
	"followpath",
	EV_DEFAULT,
	"eSSSSSS",
	"path arg1 arg2 arg3 arg4 arg5 arg6",
	"Makes the script slave follow the specified path.  The allowable arguments are ignoreangles,\n"
	"normalangles, loop, and a number specifying the start time."
	);
Event EV_ScriptSlave_EndPath
	( 
	"endpath",
	EV_DEFAULT,
	NULL,
	NULL,
	"Stop following the path"
	);
Event EV_ScriptSlave_MoveDone
	( 
	"scriptslave_movedone",
	EV_DEFAULT,
	NULL,
	NULL,
	"Called when the script slave is doen moving"
	);
Event EV_ScriptSlave_FollowingPath
	( 
	"scriptslave_followingpath",
	EV_DEFAULT,
	NULL,
	NULL,
	"Called every frame to actually follow the path"
	);
Event EV_ScriptSlave_Explode
	( 
	"explode",
	EV_DEFAULT,
	"f",
	"damage",
	"Creates an explosion at the script slave's position"
	);
Event EV_ScriptSlave_NotShootable
	( 
	"notshootable",
	EV_DEFAULT,
	NULL,
	NULL,
	"Makes the script slave not shootable"
	);

Event EV_ScriptSlave_OpenAreaPortal
	( 
	"openportal",
	EV_DEFAULT,
	NULL,
	NULL,
	"Open the area portal enclosed in this object"
	);

Event EV_ScriptSlave_CloseAreaPortal
	( 
	"closeportal",
	EV_DEFAULT,
	NULL,
	NULL,
	"Close the area portal enclosed in this object"
	);

Event EV_ScriptSlave_PhysicsOn
	( 
	"physics_on",
	EV_DEFAULT,
	NULL,
	NULL,
	"Turn physics on this script object on"
	);

Event EV_ScriptSlave_PhysicsOff
	( 
	"physics_off",
	EV_DEFAULT,
	NULL,
	NULL,
	"Turn physics off this script object on"
	);

Event EV_ScriptSlave_PhysicsVelocity
	( 
	"physics_velocity",
	EV_DEFAULT,
	"v",
   "impulseVector",
	"Add a physical impulse to an object when it is being physically simulated"
	);

CLASS_DECLARATION( Mover, ScriptSlave, "script_object" )
	{
	   { &EV_Bind,					               BindEvent },
	   { &EV_Unbind,				               EventUnbind },
		{ &EV_ScriptSlave_DoMove,				   DoMove },
		{ &EV_ScriptSlave_NewOrders,			   NewOrders },
		{ &EV_ScriptSlave_Angles,				   SetAnglesEvent },
		{ &EV_SetAngle,			               SetAngleEvent },
      { &EV_Model,                           SetModelEvent },
      { &EV_ScriptSlave_Trigger,				   TriggerEvent },
	   { &EV_ScriptSlave_Next,					   GotoNextWaypoint },
	   { &EV_ScriptSlave_JumpTo,				   JumpTo },
	   { &EV_ScriptSlave_MoveTo,				   MoveToEvent },
	   { &EV_ScriptSlave_Speed,				   SetSpeed },
	   { &EV_ScriptSlave_Time,					   SetTime },
	   { &EV_ScriptSlave_MoveUp,				   MoveUp },
	   { &EV_ScriptSlave_MoveDown,			   MoveDown },
	   { &EV_ScriptSlave_MoveNorth,			   MoveNorth },
	   { &EV_ScriptSlave_MoveSouth,			   MoveSouth },
	   { &EV_ScriptSlave_MoveEast,			   MoveEast },
	   { &EV_ScriptSlave_MoveWest,			   MoveWest },
	   { &EV_ScriptSlave_MoveForward,		   MoveForward },
	   { &EV_ScriptSlave_MoveBackward,		   MoveBackward },
	   { &EV_ScriptSlave_MoveLeft,			   MoveLeft },
	   { &EV_ScriptSlave_MoveRight,			   MoveRight },
		{ &EV_ScriptSlave_RotateXDownTo,		   RotateXdownto },
	   { &EV_ScriptSlave_RotateYDownTo,		   RotateYdownto },
	   { &EV_ScriptSlave_RotateZDownTo,		   RotateZdownto },
	   { &EV_ScriptSlave_RotateXUpTo,		   RotateXupto },
	   { &EV_ScriptSlave_RotateYUpTo,		   RotateYupto },
	   { &EV_ScriptSlave_RotateZUpTo,		   RotateZupto },
	   { &EV_ScriptSlave_RotateXDown,		   RotateXdown },
	   { &EV_ScriptSlave_RotateYDown,		   RotateYdown },
	   { &EV_ScriptSlave_RotateZDown,		   RotateZdown },
	   { &EV_ScriptSlave_RotateXUp,			   RotateXup },
	   { &EV_ScriptSlave_RotateYUp,			   RotateYup },
	   { &EV_ScriptSlave_RotateZUp,			   RotateZup },
	   { &EV_ScriptSlave_RotateX,				   RotateX },
	   { &EV_ScriptSlave_RotateY,				   RotateY },
	   { &EV_ScriptSlave_RotateZ,				   RotateZ },
	   { &EV_ScriptSlave_RotateAxisDownTo,	   RotateAxisdownto },
	   { &EV_ScriptSlave_RotateAxisUpTo,	   RotateAxisupto },
	   { &EV_ScriptSlave_RotateAxisDown,	   RotateAxisdown },
	   { &EV_ScriptSlave_RotateAxisUp,		   RotateAxisup },
	   { &EV_ScriptSlave_RotateAxis,			   RotateZ },
		{ &EV_ScriptSlave_OnTouch,				   OnTouch },
	   { &EV_ScriptSlave_NoTouch,				   NoTouch },
	   { &EV_ScriptSlave_OnUse,				   OnUse },
	   { &EV_ScriptSlave_NoUse,				   NoUse },
	   { &EV_ScriptSlave_OnBlock,				   OnBlock },
	   { &EV_ScriptSlave_NoBlock,				   NoBlock },
	   { &EV_ScriptSlave_OnTrigger,			   OnTrigger },
	   { &EV_ScriptSlave_NoTrigger,			   NoTrigger },
	   { &EV_ScriptSlave_OnDamage,			   OnDamage },
	   { &EV_ScriptSlave_NoDamage,			   NoDamage },
	   { &EV_ScriptSlave_SetDamage,			   SetDamage },
		{ &EV_ScriptSlave_SetMeansOfDeath,	   SetMeansOfDeath },
      { &EV_ScriptSlave_SetDamageSpawn,      SetDamage },
	   { &EV_ScriptSlave_FollowPath,			   FollowPath },
	   { &EV_ScriptSlave_EndPath,			      EndPath },
	   { &EV_ScriptSlave_FollowingPath,		   FollowingPath },
	   { &EV_Touch,								   TouchFunc },
	   { &EV_Blocked,								   BlockFunc },
	   { &EV_Activate,							   TriggerFunc },
	   { &EV_Use,									   UseFunc },
	   { &EV_ScriptSlave_MoveDone,			   MoveEnd },
		{ &EV_Damage,								   DamageFunc },
	   { &EV_ScriptSlave_RotateDownTo,		   Rotatedownto },
	   { &EV_ScriptSlave_RotateUpTo,		      Rotateupto },
	   { &EV_ScriptSlave_RotateTo,		      Rotateto },
	   { &EV_ScriptSlave_Explode,		         Explode },
		{ &EV_ScriptSlave_NotShootable,		   NotShootable },
      { &EV_ScriptSlave_OpenAreaPortal,      OpenPortal },
      { &EV_ScriptSlave_CloseAreaPortal,     ClosePortal },
      { &EV_ScriptSlave_PhysicsOn,           PhysicsOn },
      { &EV_ScriptSlave_PhysicsOff,          PhysicsOff },
      { &EV_ScriptSlave_PhysicsVelocity,     PhysicsVelocity },

		{ NULL, NULL }
	};

ScriptSlave::ScriptSlave()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   // this is a normal entity
   edict->s.eType = ET_GENERAL;

   speed             = 100;
	takedamage			= DAMAGE_YES;
	waypoint				= NULL;
	NewAngles			= localangles;
	NewPos				= localorigin;
	traveltime			= 0;
	commandswaiting	= false;
	movethread			= NULL;
	touchthread			= NULL;
	blockthread			= NULL;
	damagethread		= NULL;
	triggerthread		= NULL;
	usethread			= NULL;
   splinePath        = NULL;
   splineangles      = false;
	attack_finished   = 0;

	dmg					 = 2;
	dmg_means_of_death = MOD_CRUSH;

	setMoveType( MOVETYPE_PUSH );
	setSolidType( SOLID_NOT );

   if ( spawnflags & 1 )
      {
      PostEvent( EV_BecomeNonSolid, EV_POSTSPAWN );
      }
	}

ScriptSlave::~ScriptSlave()
	{
   if ( splinePath )
      {
      delete splinePath;
      splinePath = NULL;
      }
   }

void ScriptSlave::NewOrders
	(
	Event *ev
	)

	{
	// make sure position and angles are current
	NewAngles = localangles;
	NewPos = localorigin;
	}

void ScriptSlave::BindEvent
	(
	Event *ev
	)

	{
	Entity *ent;

	ent = ev->GetEntity( 1 );
	if ( ent )
		{
		bind( ent );
		}

	// make sure position and angles are current
	NewAngles = localangles;
	NewPos = localorigin;
	}

void ScriptSlave::EventUnbind
	(
	Event *ev
	)

	{
	unbind();

   // make sure position and angles are current
	NewAngles = localangles;
	NewPos = localorigin;
	}

void ScriptSlave::DoMove
	(
	Event *ev
	)

	{
	float dist;
	ScriptThread *thread;
	Event *event;

	thread = ev->GetThread();
   assert( thread );
   if ( thread && thread->WaitingFor( this ) )
		{
		if ( movethread && ( movethread != thread ) )
			{
			// warn the user
			ev->Error( "Overriding previous move commands for '%s'\n", TargetName() );

			// Yeah, we're not REALLY done, but we tell our old thread
			// that we are so that it doesn't wait forever
			event = new Event( EV_MoveDone );
			event->AddEntity( this );
			movethread->ProcessEvent( event );
			}

		movethread = thread;
		}

	if ( commandswaiting )
		{
      if ( splinePath )
         {
         moving = true;
      	PostEvent( EV_ScriptSlave_FollowingPath, 0 );
         }
      else
         {
         float t = traveltime;
		   if ( t == 0 )
			   {
			   dist = Vector( NewPos - localorigin ).length();
			   t = dist / speed;
			   }
         moving = true;
		   LinearInterpolate( NewPos, NewAngles, t, EV_ScriptSlave_MoveDone );
         }

		commandswaiting = false;
		}
	else if ( movethread && ( movethread == thread ) && !moving )
		{
		// No commands, so tell the master that we're done
		PostEvent( EV_ScriptSlave_MoveDone, 0 );
		}
	}

void ScriptSlave::MoveEnd
	(
	Event *ev
	)

	{
	Event *event;

   moving = false;
	commandswaiting = false;
	NewAngles = localangles;
	NewPos = localorigin;

	if ( movethread )
		{
		event = new Event( EV_MoveDone );
		event->AddEntity( this );
		movethread->ProcessEvent( event );
		movethread = NULL;
		}
	}

void ScriptSlave::SetAnglesEvent
	(
	Event *ev
	)

	{
	commandswaiting = true;
   setAngles( ev->GetVector( 1 ) );
	NewAngles = localangles;
	}

void ScriptSlave::SetAngleEvent
	(
	Event *ev
	)

	{
   float angle;

	angle = ev->GetFloat( 1 );
	if ( angle == -1 )
		{
		ForwardDir = Vector( 0, 0, 90 );
		}
	else if ( angle == -2 )
		{
		ForwardDir = Vector( 0, 0, -90 );
		}
	else
		{
		ForwardDir = Vector( 0, angle, 0 );
		}
   }

void ScriptSlave::SetModelEvent
	(
	Event *ev
	)

	{
   const char *m;

   m = ev->GetString( 1 );

   setModel( m );
  	showModel();

	if ( !edict->s.modelindex )
		{
      hideModel();
		setSolidType( SOLID_NOT );
		}
	else if ( !m || strstr( m, ".tik" ) )
		{
		setSolidType( SOLID_BBOX );
		}
	else if ( strstr( m, ".spr" ) )
		{
		setSolidType( SOLID_NOT );
		}
	else
		{
   	setSolidType( SOLID_BSP );
		}
   }

void ScriptSlave::TriggerEvent
	(
	Event *ev
	)

	{
	Entity *ent;
	Event	 *e;

	ent = ev->GetEntity( 1 );
	if ( ent )
		{
		SetTarget( ent->TargetName() );

		e = new Event( EV_Trigger_ActivateTargets );
		//fixme
		//get "other"
		e->AddEntity( world );
		ProcessEvent( e );
		}
	}

void ScriptSlave::GotoNextWaypoint
	(
	Event *ev
	)

	{
	commandswaiting = true;

	if ( !waypoint )
		{
		ev->Error( "%s is currently not at a waypoint", TargetName() );
		return;
		}

	waypoint = ( Waypoint * )G_FindTarget( NULL, waypoint->Target() );
	if ( !waypoint )
		{
		ev->Error( "%s could not find waypoint %s", TargetName(), waypoint->Target() );
		return;
		}
   else
		{
      NewPos = waypoint->origin;
		}
	}

void ScriptSlave::JumpTo
	(
	Event *ev
	)

	{
	Entity *part;

   //
   // see if it is a vector
   //
   if ( ev->IsVectorAt( 1 ) )
      {
      NewPos = ev->GetVector( 1 );
		if ( bindmaster )
			{
         localorigin = bindmaster->getLocalVector( NewPos - bindmaster->origin );
			}
		else
			{
			localorigin = NewPos;
			}

		for( part = this; part; part = part->teamchain )
			{
			part->setOrigin();
         part->origin.copyTo( part->edict->s.origin2 );
			part->edict->s.renderfx |= RF_FRAMELERP;
			}
      }
   else
      {
	   waypoint = ( Waypoint * )ev->GetEntity( 1 );
	   if ( waypoint )
		   {
		   NewPos = waypoint->localorigin;
		   if ( bindmaster )
			   {
            localorigin = bindmaster->getLocalVector( NewPos - bindmaster->origin );
			   }
		   else
			   {
			   localorigin = NewPos;
			   }

		   for( part = this; part; part = part->teamchain )
			   {
			   part->setOrigin();
            part->origin.copyTo( part->edict->s.origin2 );
			   part->edict->s.renderfx |= RF_FRAMELERP;
			   }
		   }
      }
	}

void ScriptSlave::MoveToEvent
	(
	Event *ev
	)

	{
	commandswaiting = true;

   //
   // see if it is a vector
   //
   if ( ev->IsVectorAt( 1 ) )
      {
      NewPos = ev->GetVector( 1 );
      }
   else
      {
	   waypoint = ( Waypoint * )ev->GetEntity( 1 );
	   if ( waypoint )
		   {
         NewPos = waypoint->origin;
		   }
      }
	}

void ScriptSlave::SetSpeed
	(
	Event *ev
	)

	{
	speed = ev->GetFloat( 1 );
	traveltime = 0;
	}

void ScriptSlave::SetTime
	(
	Event *ev
	)

	{
	traveltime = ev->GetFloat( 1 );
	}

// Relative move commands

void ScriptSlave::MoveUp
	(
	Event *ev
	)

	{
	commandswaiting = true;
	NewPos[ 2 ] += ev->GetFloat( 1 );
	}

void ScriptSlave::MoveDown
	(
	Event *ev
	)

	{
	commandswaiting = true;
	NewPos[ 2 ] -= ev->GetFloat( 1 );
	}

void ScriptSlave::MoveNorth
	(
	Event *ev
	)

	{
	commandswaiting = true;
	NewPos[ 1 ] += ev->GetFloat( 1 );
	}

void ScriptSlave::MoveSouth
	(
	Event *ev
	)

	{
	commandswaiting = true;
	NewPos[ 1 ] -= ev->GetFloat( 1 );
	}

void ScriptSlave::MoveEast
	(
	Event *ev
	)

	{
	commandswaiting = true;
	NewPos[ 0 ] += ev->GetFloat( 1 );
	}

void ScriptSlave::MoveWest
	(
	Event *ev
	)

	{
	commandswaiting = true;
	NewPos[ 0 ] -= ev->GetFloat( 1 );
	}

void ScriptSlave::MoveForward
	(
	Event *ev
	)

	{
	Vector v;
	Vector t;

	commandswaiting = true;

	t = NewAngles + ForwardDir;
	t.AngleVectors( &v, NULL, NULL );

	NewPos += v * ev->GetFloat( 1 );
	}

void ScriptSlave::MoveBackward
	(
	Event *ev
	)

	{
	Vector v;
	Vector t;

	commandswaiting = true;

	t = NewAngles + ForwardDir;
	t.AngleVectors( &v, NULL, NULL );

	NewPos -= v * ev->GetFloat( 1 );
	}

void ScriptSlave::MoveLeft
	(
	Event *ev
	)

	{
	Vector v;
	Vector t;

	commandswaiting = true;

	t = NewAngles + ForwardDir;
	t.AngleVectors( NULL, &v, NULL );

	NewPos += v * ev->GetFloat( 1 );
	}

void ScriptSlave::MoveRight
	(
	Event *ev
	)

	{
	Vector t;
	Vector v;

	commandswaiting = true;

	t = NewAngles + ForwardDir;
	t.AngleVectors( NULL, &v, NULL );

	NewPos -= v * ev->GetFloat( 1 );
	}

// exact rotate commands

void ScriptSlave::RotateXdownto
	(
	Event *ev
	)

	{
	commandswaiting = true;

	NewAngles[ 0 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 0 ] > localangles[ 0 ] )
		{
		NewAngles[ 0 ] -= 360;
		}
	}

void ScriptSlave::RotateYdownto
	(
	Event *ev
	)

	{
	commandswaiting = true;

	NewAngles[ 1 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 1 ] > localangles[ 1 ] )
		{
		NewAngles[ 1 ] -= 360;
		}
	}

void ScriptSlave::RotateZdownto
	(
	Event *ev
	)

	{
	commandswaiting = true;

	NewAngles[ 2 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 2 ] > localangles[ 2 ] )
		{
		NewAngles[ 2 ] -= 360;
		}
	}

void ScriptSlave::RotateAxisdownto
	(
	Event *ev
	)

	{
   int axis;
	commandswaiting = true;

   axis = ev->GetInteger( 1 );
	NewAngles[ axis ] = ev->GetFloat( 2 );
	if ( NewAngles[ axis ] > localangles[ axis ] )
		{
		NewAngles[ axis ] -= 360;
		}
	}

void ScriptSlave::RotateXupto
	(
	Event *ev
	)

	{
	commandswaiting = true;

	NewAngles[ 0 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 0 ] < localangles[ 0 ] )
		{
		NewAngles[ 0 ] += 360;
		}
	}

void ScriptSlave::RotateYupto
	(
	Event *ev
	)

	{
	commandswaiting = true;

	NewAngles[ 1 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 1 ] < localangles[ 1 ] )
		{
		NewAngles[ 1 ] += 360;
		}
	}

void ScriptSlave::RotateZupto
	(
	Event *ev
	)

	{
	commandswaiting = true;

	NewAngles[ 2 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 2 ] < localangles[ 2 ] )
		{
		NewAngles[ 2 ] += 360;
		}
	}

void ScriptSlave::RotateAxisupto
	(
	Event *ev
	)

	{
   int axis;
	commandswaiting = true;

   axis = ev->GetInteger( 1 );
	NewAngles[ axis ] = ev->GetFloat( 2 );
	if ( NewAngles[ axis ] < localangles[ axis ] )
		{
		NewAngles[ axis ] += 360;
		}
	}

// full vector rotation

void ScriptSlave::Rotatedownto
	(
	Event *ev
	)

	{
   Vector ang;
	commandswaiting = true;

   ang = ev->GetVector( 1 );

	NewAngles[ 0 ] = ang[ 0 ];
	if ( NewAngles[ 0 ] > localangles[ 0 ] )
		{
		NewAngles[ 0 ] -= 360;
		}
	NewAngles[ 1 ] = ang[ 1 ];
	if ( NewAngles[ 1 ] > localangles[ 1 ] )
		{
		NewAngles[ 1 ] -= 360;
		}
	NewAngles[ 2 ] = ang[ 2 ];
	if ( NewAngles[ 2 ] > localangles[ 2 ] )
		{
		NewAngles[ 2 ] -= 360;
		}
	}

void ScriptSlave::Rotateupto
	(
	Event *ev
	)

	{
   Vector ang;
	commandswaiting = true;

   ang = ev->GetVector( 1 );

	NewAngles[ 0 ] = ang[ 0 ];
	if ( NewAngles[ 0 ] < localangles[ 0 ] )
		{
		NewAngles[ 0 ] += 360;
		}
	NewAngles[ 1 ] = ang[ 1 ];
	if ( NewAngles[ 1 ] < localangles[ 1 ] )
		{
		NewAngles[ 1 ] += 360;
		}
	NewAngles[ 2 ] = ang[ 2 ];
	if ( NewAngles[ 2 ] < localangles[ 2 ] )
		{
		NewAngles[ 2 ] += 360;
		}
	}

void ScriptSlave::Rotateto
	(
	Event *ev
	)

	{
   Vector ang;
	commandswaiting = true;

   ang = ev->GetVector( 1 );

   NewAngles = ang;
	}

// Relative rotate commands

void ScriptSlave::RotateXdown
	(
	Event *ev
	)

	{
	commandswaiting = true;
	NewAngles[ 0 ] = localangles[ 0 ] - ev->GetFloat( 1 );
	}

void ScriptSlave::RotateYdown
	(
	Event *ev
	)

	{
	commandswaiting = true;
	NewAngles[ 1 ] = localangles[ 1 ] - ev->GetFloat( 1 );
	}

void ScriptSlave::RotateZdown
	(
	Event *ev
	)

	{
	commandswaiting = true;
	NewAngles[ 2 ] = localangles[ 2 ] - ev->GetFloat( 1 );
	}

void ScriptSlave::RotateAxisdown
	(
	Event *ev
	)

	{
   int axis;
	commandswaiting = true;

   axis = ev->GetInteger( 1 );
	NewAngles[ axis ] = localangles[ axis ] - ev->GetFloat( 2 );
	}

void ScriptSlave::RotateXup
	(
	Event *ev
	)

	{
 	commandswaiting = true;
	NewAngles[ 0 ] = localangles[ 0 ] + ev->GetFloat( 1 );
	}

void ScriptSlave::RotateYup
	(
	Event *ev
	)

	{
 	commandswaiting = true;
	NewAngles[ 1 ] = localangles[ 1 ] + ev->GetFloat( 1 );
	}

void ScriptSlave::RotateZup
	(
	Event *ev
	)

	{
 	commandswaiting = true;
	NewAngles[ 2 ] = localangles[ 2 ] + ev->GetFloat( 1 );
	}

void ScriptSlave::RotateAxisup
	(
	Event *ev
	)

	{
   int axis;
	commandswaiting = true;

   axis = ev->GetInteger( 1 );
	NewAngles[ axis ] = localangles[ axis ] + ev->GetFloat( 2 );
	}

void ScriptSlave::RotateX
	(
	Event *ev
	)

	{
	avelocity[ 0 ] = ev->GetFloat( 1 );
	}

void ScriptSlave::RotateY
	(
	Event *ev
	)

	{
	avelocity[ 1 ] = ev->GetFloat( 1 );
	}

void ScriptSlave::RotateZ
	(
	Event *ev
	)

	{
	avelocity[ 2 ] = ev->GetFloat( 1 );
	}

void ScriptSlave::RotateAxis
	(
	Event *ev
	)

	{
   int axis;

   axis = ev->GetInteger( 1 );
   avelocity[ axis ] = ev->GetFloat( 2 );
	}


void ScriptSlave::OnTouch
	(
	Event *ev
	)

	{
	const char *jumpto;

	touchlabel = "";

	jumpto = ev->GetString( 1 );
	touchthread = ev->GetThread();

	assert( jumpto && touchthread );
	if ( touchthread && !touchthread->labelExists( jumpto ) )
		{
		ev->Error( "Label '%s' not found", jumpto );
		return;
		}

   // if it isn't solid than we need to change it to a trigger
   if ( getSolidType() == SOLID_NOT )
      {
   	setSolidType( SOLID_TRIGGER );
      }

	touchlabel = jumpto;
	}

void ScriptSlave::NoTouch
	(
	Event *ev
	)

	{
	touchlabel = "";
   // if it is a trigger than it wasn't solid, so restore that condition
   if ( getSolidType() == SOLID_TRIGGER )
      {
   	setSolidType( SOLID_NOT );
      }
	}

void ScriptSlave::TouchFunc
	(
	Event *ev
	)

	{
	Event *e;
	Entity *other;

	if ( touchlabel.length() )
		{
      // since we use a SafePtr, the thread pointer will be NULL if the thread has ended
      // so we should just clear our label and continue
      if ( !touchthread )
			{
         touchlabel = "";
         return;
         }

      other = ev->GetEntity( 1 );

		e = new Event( EV_ScriptThread_Callback );
		e->AddEntity( this );
		e->AddString( touchlabel );
		e->AddEntity( other );
  		touchthread->ProcessEvent( e );
		}
	}

void ScriptSlave::OnBlock
	(
	Event *ev
	)

	{
	const char *jumpto;

	blocklabel = "";

	jumpto = ev->GetString( 1 );
	blockthread = ev->GetThread();

	assert( jumpto && blockthread );
	if ( blockthread && !blockthread->labelExists( jumpto ) )
		{
		ev->Error( "Label '%s' not found", jumpto );
		return;
		}

	blocklabel = jumpto;
	}

void ScriptSlave::NoBlock
	(
	Event *ev
	)

	{
	blocklabel = "";
	}

void ScriptSlave::BlockFunc
	(
	Event *ev
	)

	{
	Event *e;
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( level.time >= attack_finished )
		{
		attack_finished = level.time + ( float )0.5;
		if ( dmg != 0 )
			{
         other->Damage( this, this, dmg, origin, vec_zero, vec_zero, 0, 0, dmg_means_of_death );
			}
		}

	if ( blocklabel.length() )
		{
      // since we use a SafePtr, the thread pointer will be NULL if the thread has ended
      // so we should just clear our label and continue
      if ( !blockthread )
			{
         blocklabel = "";
         return;
         }

		e = new Event( EV_ScriptThread_Callback );
		e->AddEntity( this );
		e->AddString( blocklabel );
		e->AddEntity( other );
  		blockthread->ProcessEvent( e );
		}
	}

void ScriptSlave::OnTrigger
	(
	Event *ev
	)

	{
	const char *jumpto;

	triggerlabel = "";

	jumpto = ev->GetString( 1 );
	triggerthread = ev->GetThread();

	assert( jumpto && triggerthread );

	if ( triggerthread && !triggerthread->labelExists( jumpto ) )
		{
		ev->Error( "Label '%s' not found", jumpto );
		return;
		}

	triggerlabel = jumpto;
	}

void ScriptSlave::NoTrigger
	(
	Event *ev
	)

	{
	triggerlabel = "";
	}

void ScriptSlave::TriggerFunc
	(
	Event *ev
	)

	{
	Event *e;
	Entity *other;

	if ( triggerlabel.length() )
		{
      // since we use a SafePtr, the thread pointer will be NULL if the thread has ended
      // so we should just clear our label and continue
      if ( !triggerthread )
			{
         triggerlabel = "";
         return;
         }

		other = ev->GetEntity( 1 );

		e = new Event( EV_ScriptThread_Callback );
		e->AddEntity( this );
		e->AddString( triggerlabel );
		e->AddEntity( other );

      triggerthread->ProcessEvent( e );
		}
	}

void ScriptSlave::OnUse
	(
	Event *ev
	)

	{
	const char *jumpto;

	uselabel = "";

	jumpto = ev->GetString( 1 );
	usethread = ev->GetThread();

	assert( jumpto && usethread );

	if ( usethread && !usethread->labelExists( jumpto ) )
		{
		ev->Error( "Label '%s' not found", jumpto );
		return;
		}

	uselabel = jumpto;
	}

void ScriptSlave::NoUse
	(
	Event *ev
	)

	{
	uselabel = "";
	}

void ScriptSlave::UseFunc
	(
	Event *ev
	)

	{
	Event *e;
	Entity *other;

	other = ev->GetEntity( 1 );

   if ( key.length() )
      {
      if ( !other->isSubclassOf( Sentient ) || !( ( (Sentient *)other )->HasItem( key.c_str() ) ) )
         {
         Item        *item;
         ClassDef		*cls;

         cls = getClass( key.c_str() );
		   if ( !cls )
			   {
            gi.DPrintf( "No item named '%s'\n", key.c_str() );
			   return;
			   }
		   item = ( Item * )cls->newInstance();
         item->CancelEventsOfType( EV_Item_DropToFloor );
	      item->CancelEventsOfType( EV_Remove );
         item->ProcessPendingEvents();
         gi.centerprintf ( other->edict, "You need the %s", item->getName() );
         delete item;
         return;
         }
      }

	if ( uselabel.length() )
		{
     	ScriptVariableList *vars;

      // since we use a SafePtr, the thread pointer will be NULL if the thread has ended
      // so we should just clear our label and continue
      if ( !usethread )
			{
         uselabel = "";
         return;
         }

		e = new Event( EV_ScriptThread_Callback );
		e->AddEntity( this );
		e->AddString( uselabel );
		e->AddEntity( other );

	   vars = usethread->Vars();
      vars->SetVariable( "other", other );
      if ( key.length() )
         {
         vars->SetVariable( "key", key.c_str() );
         }
   	usethread->ProcessEvent( e );
		}
	}

void ScriptSlave::OnDamage
	(
	Event *ev
	)

	{
	const char *jumpto;

	damagelabel = "";

	jumpto = ev->GetString( 1 );
	damagethread = ev->GetThread();

	assert( jumpto && damagethread );

	if ( damagethread && !damagethread->labelExists( jumpto ) )
		{
		ev->Error( "Label '%s' not found", jumpto );
		return;
		}

	damagelabel = jumpto;
	}

void ScriptSlave::NoDamage
	(
	Event *ev
	)

	{
	damagelabel = "";
	}

void ScriptSlave::DamageFunc
	(
	Event *ev
	)

	{
	Event			*e;
	Entity		*inflictor;
	Entity		*attacker;
	int			damage;
   Vector		position;
   Vector		direction;
  	ScriptVariableList *vars;

	if ( damagelabel.length() )
		{
      // since we use a SafePtr, the thread pointer will be NULL if the thread has ended
      // so we should just clear our label and continue
      if ( !damagethread )
			{
         damagelabel = "";
         return;
         }

		attacker	= ev->GetEntity( 3 );

		e = new Event( EV_ScriptThread_Callback );
		e->AddEntity( this );
		e->AddString( damagelabel );
		e->AddEntity( attacker );

      damage		= ev->GetInteger( 1 );
		inflictor	= ev->GetEntity( 2 );
		position		= ev->GetVector( 4 );
		direction	= ev->GetVector( 5 );

		vars = damagethread->Vars();
      vars->SetVariable( "damage", damage );
      vars->SetVariable( "inflictor", inflictor );
      vars->SetVariable( "attacker", attacker );
      vars->SetVariable( "position", position );
      vars->SetVariable( "direction", direction );
   	damagethread->ProcessEvent( e );
		}
	}

void ScriptSlave::SetDamage
	(
	Event *ev
	)

	{
	dmg = ev->GetInteger( 1 );
	}

void ScriptSlave::SetMeansOfDeath
	(
	Event *ev
	)

	{
	dmg_means_of_death = MOD_string_to_int( ev->GetString( 1 ) );
	}

void ScriptSlave::CreatePath
	(
	SplinePath *path,
	splinetype_t type
	)

	{
	SplinePath	*node;

   if ( !splinePath )
      {
      splinePath = new BSpline;
      }

	splinePath->Clear();
	splinePath->SetType( type );

	node = path;
	while( node != NULL )
		{
      splinePath->AppendControlPoint( node->origin, node->angles, node->speed );
		node = node->GetNext();

		if ( node == path )
			{
			break;
			}
		}
	}

void ScriptSlave::FollowPath
	(
	Event *ev
	)

	{
   int i, argnum;
   Entity * ent;
   const char * token;
   SplinePath *path;
   qboolean clamp;
   float starttime;


	ent = ev->GetEntity( 1 );
   argnum = 2;
   starttime = -2;
   clamp = true;
   ignoreangles = false;
   splineangles = true;
   for ( i = argnum; i <= ev->NumArgs() ; i++ )
      {
      token = ev->GetString( i );
      if (!strcmpi( token, "ignoreangles"))
         {
         ignoreangles = true;
         }
      else if (!strcmpi( token, "normalangles"))
         {
         splineangles = false;
         }
      else if (!strcmpi (token, "loop"))
         {
         clamp = false;
         }
      else if ( IsNumeric( token ) )
         {
         starttime = atof( token );
         }
      else
         {
         ev->Error( "Unknown followpath command %s.", token );
         }
      }
	if ( ent && ent->isSubclassOf( SplinePath ) )
		{
      commandswaiting = true;
		path = ( SplinePath * )ent;
      if ( clamp )
	      CreatePath( path, SPLINE_CLAMP );
      else
	      CreatePath( path, SPLINE_LOOP );
      splineTime = starttime;
		CancelEventsOfType( EV_ScriptSlave_FollowingPath );
      if ( !ignoreangles )
         {
         avelocity = vec_zero;
         }
      velocity = vec_zero;
      }
	}

void ScriptSlave::EndPath
	(
	Event *ev
	)
	{
   if ( !splinePath )
      return;

   delete splinePath;
   splinePath = NULL;
   velocity = vec_zero;
   if ( !ignoreangles )
      {
      avelocity = vec_zero;
      }
   }

void ScriptSlave::FollowingPath
	(
	Event *ev
	)
	{
	Vector	pos;
	Vector	orient;
   float    speed_multiplier;

   if ( !splinePath )
      return;

   if ( ( splinePath->GetType() == SPLINE_CLAMP ) && ( splineTime > ( splinePath->EndPoint() - 2 ) ) )
      {
      delete splinePath;
      splinePath = NULL;
      velocity = vec_zero;
      if ( !ignoreangles )
         {
         avelocity = vec_zero;
         }
      moving = false;
      ProcessEvent( EV_ScriptSlave_MoveDone );
      return;
      }

	speed_multiplier = splinePath->Eval( splineTime, pos, orient );

	splineTime += level.frametime * speed_multiplier;

   velocity = ( pos - origin ) * ( 1 / level.frametime );
   if ( !ignoreangles )
      {
      if ( splineangles )
         {
         avelocity = ( orient - angles ) * ( 1 / level.frametime );
         }
      else
         {
         float len;

         len = velocity.length();
         if ( len > 0.05 )
            {
            Vector ang;
            Vector dir;
            float  aroll;

            aroll = avelocity[ ROLL ];
			   dir = velocity * ( 1 / len );
			   ang = dir.toAngles();
            avelocity = ( ang - angles ) * ( 1 / level.frametime );
            avelocity[ ROLL ] = aroll;
            }
         else
            avelocity = vec_zero;
         }
      }
	PostEvent( EV_ScriptSlave_FollowingPath, level.frametime );
	}

void ScriptSlave::Explode
	(
	Event *ev
	)

	{
   float damage;

   if ( ev->NumArgs() )
      {
      damage = ev->GetFloat( 1 );
      }
   else
      {
      damage = 120.0f;
      }

   CreateExplosion( origin, damage, this, this, this );
   }

void ScriptSlave::NotShootable
	(
	Event *ev
	)
	{
  	setContents( 0 );
   }

void ScriptSlave::OpenPortal
	(
	Event *ev
	)
	{
   gi.AdjustAreaPortalState( this->edict, true );
   }

void ScriptSlave::ClosePortal
	(
	Event *ev
	)
	{
   gi.AdjustAreaPortalState( this->edict, false );
   }

void ScriptSlave::PhysicsOn
	(
	Event *ev
	)
	{
	commandswaiting = false;
   setMoveType( MOVETYPE_BOUNCE );
   setSolidType( SOLID_BBOX );
   velocity = "0 0 1";
   edict->clipmask = MASK_SOLID|CONTENTS_BODY;
   }

void ScriptSlave::PhysicsOff
	(
	Event *ev
	)
	{
   Event * event;

	commandswaiting = false;
   setMoveType( MOVETYPE_PUSH );
   edict->clipmask = 0;
   // become solid again
   event = new Event( EV_Model );
   event->AddString( model );
   PostEvent( event, 0 );
   }

void ScriptSlave::PhysicsVelocity
	(
	Event *ev
	)
	{
   velocity += ev->GetVector( 1 );
   }


/*****************************************************************************/
/*QUAKED script_model (0 0.5 1) (0 0 0) (0 0 0) NOT_SOLID

******************************************************************************/

Event EV_ScriptModel_SetAnim
	( 
	"anim",
	EV_DEFAULT,
	"s",
	"anim_name",
	"Sets the script model's animation"
	);
Event EV_ScriptModel_AnimOnce
	( 
	"animonce",
	EV_DEFAULT,
	"s",
	"anim_name",
	"Sets the script model's animation but only plays it once"
	);

CLASS_DECLARATION( ScriptSlave, ScriptModel, "script_model" )
	{
	   { &EV_Gib,				         GibEvent },
		{ &EV_SetAngle,	            SetAngleEvent },
      { &EV_ScriptModel_SetAnim,	   SetAnimEvent },
      { &EV_ScriptModel_AnimOnce,	AnimOnceEvent },
      { &EV_Model,	               SetModelEvent },
  		{ NULL, NULL },
	};

ScriptModel::ScriptModel()
	{
   // this is a tiki model
   edict->s.eType = ET_MODELANIM;
   }

void ScriptModel::SetModelEvent
   (
   Event *ev
   )

   {
   ScriptSlave::SetModelEvent( ev );

   if ( ( gi.IsModel( edict->s.modelindex ) ) && !mins.length() && !maxs.length() )
      {
      gi.CalculateBounds( edict->s.modelindex, edict->s.scale, mins, maxs );
      }
   }

void ScriptModel::SetAnimEvent
   (
   Event *ev
   )

   {
   const char * animname;

   animname = ev->GetString( 1 );
   if ( animname && strlen( animname ) && gi.IsModel( edict->s.modelindex ) )
      {
      int animnum;

      animnum = gi.Anim_NumForName( edict->s.modelindex, animname );
      if ( animnum >= 0 )
         {
         NewAnim( animnum );
         }
      }
   }

void ScriptModel::AnimOnceEvent
   (
   Event *ev
   )

   {
   const char * animname;

   animname = ev->GetString( 1 );
   if ( animname && strlen( animname ) && gi.IsModel( edict->s.modelindex ) )
      {
      RandomAnimate( animname, EV_StopAnimating );
      }
   }

void ScriptModel::SetAngleEvent
	(
	Event *ev
	)

	{
   float angle;

	angle = ev->GetFloat( 1 );
	if ( angle == -1 )
		{
		ForwardDir = Vector( 0, 0, 90 );
      localangles = Vector( -90, 0, 0 );
		}
	else if ( angle == -2 )
		{
		ForwardDir = Vector( 0, 0, -90 );
      localangles = Vector( 90, 0, 0 );
		}
	else
		{
		ForwardDir = Vector( 0, angle, 0 );
      localangles = Vector( 0, angle, 0 );
		}

	setAngles( localangles );
   }

void ScriptModel::GibEvent
   (
   Event *ev
   )

   {
   int      num,power;
   float    scale;

   setSolidType( SOLID_NOT );
   hideModel();

   if ( !com_blood->integer )
      {
      PostEvent( EV_Remove, 0 );
      return;
      }

   num = ev->GetInteger( 1 );
   power = ev->GetInteger( 2 );
   scale = ev->GetFloat( 3 );

   power = -power;

   if ( ev->NumArgs() > 3 )
      {
      CreateGibs( this, power, scale, num, ev->GetString( 4 ) );
      }
   else
      {
      CreateGibs( this, power, scale, num );
      }

   PostEvent( EV_Remove, 0 );
   }

/*****************************************************************************/
/*QUAKED script_origin (1.0 0 0) (-8 -8 -8) (8 8 8)

Used as an alternate origin for objects.  Bind the object to the script_origin
in order to simulate changing that object's origin.
******************************************************************************/

CLASS_DECLARATION( ScriptSlave, ScriptOrigin, "script_origin" )
	{
		{ &EV_Model,				SetModelEvent },
		{ NULL, NULL }
	};

ScriptOrigin::ScriptOrigin()
	{
  	setContents( 0 );
	setSolidType( SOLID_NOT );
	}

/*****************************************************************************/
/*QUAKED script_skyorigin (1.0 0 0) ?

Used to specify the origin of a portal sky
******************************************************************************/

CLASS_DECLARATION( ScriptSlave, ScriptSkyOrigin, "script_skyorigin" )
	{
		{ NULL, NULL }
	};

ScriptSkyOrigin::ScriptSkyOrigin()
	{
   edict->s.renderfx |= RF_SKYORIGIN;
  	setContents( 0 );
	setSolidType( SOLID_NOT );
	}
