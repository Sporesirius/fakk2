//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/viewthing.cpp                     $
// $Revision:: 30                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 3:50p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/viewthing.cpp                          $
// 
// 30    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 29    6/04/00 6:03p Markd
// Added precise shadow support
// 
// 28    5/02/00 7:18p Markd
// Bullet proofed viewspawned stuff
// 
// 27    3/31/00 9:40a Markd
// fixed some viewthing issues
// 
// 26    3/17/00 3:45p Markd
// made viewthing slider changes for setanim
// 
// 25    2/11/00 2:23p Markd
// Added PrintTime support
// 
// 24    2/01/00 4:11p Markd
// Added Frame bounding box support
// 
// 23    1/27/00 11:35a Markd
// Fixed solid/notsolid client side entities
// 
// 22    1/25/00 7:02p Markd
// Fixed viewthing frame reporting
// 
// 21    1/24/00 12:40p Markd
// Fixed and cleaned up viewthing code
// 
// 20    1/21/00 12:28p Markd
// Added shadows to viewthings
// 
// 19    1/19/00 11:09a Markd
// Initialized viewthings ad ET_MODELANIM's
// 
// 18    1/13/00 11:45a Markd
// Fixed viewspawn bug with surfaces, now I save them off and then restore
// them on each animation
// 
// 17    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 16    12/17/99 8:27p Jimdose
// got rid of unused vars and functions
// 
// 15    12/01/99 4:56p Markd
// fixed some reference versus pointer issues with RandomAnimate and NewAnim
// 
// 14    10/22/99 5:14p Jimdose
// SetModelEvent and Passevent weren't returning after errors, causing crashes
// in the cases they were supposed to catch
// 
// 13    10/19/99 7:53p Markd
// eliminated 3 part model system
// 
// 12    10/11/99 3:10p Steven
// Event documentation cleanup.
// 
// 11    10/08/99 5:24p Jimdose
// fixed some divide by zero crashes when the animation or model is bad.
// 
// 10    10/07/99 3:00p Steven
// Event formatting.
// 
// 9     10/06/99 5:34p Jimdose
// variable names in EV_ViewThing_Attach were swapped
// 
// 8     10/05/99 10:15a Jimdose
// got rid of assignment in conditional warning
// 
// 7     10/02/99 6:51p Markd
// Put in backend work for event documentation and fixed a lot of event
// documentation bugs
// 
// 6     10/01/99 6:31p Markd
// added commands hidden inside fgame so that they would show up for command
// completion
// 
// 5     9/30/99 1:49p Aldie
// Documentation of commands
// 
// 4     9/22/99 4:48p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 3     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 7     7/15/99 4:15p Markd
// added time output to viewthing
// 
// 6     7/07/99 12:25p Markd
// 
// 5     7/06/99 5:52p Jimdose
// reversed move deltas
// 
// 4     7/01/99 6:57p Aldie
// fix crash bug
// 
// 3     6/25/99 11:50a Aldie
// made the viewthing report back to the gui by setting cvars
// 
// 2     6/23/99 3:57p Markd
// Added viewthing support
// 
// 1     6/23/99 11:00a Markd
// 
// 41    11/07/98 10:06p Jimdose
// NextAnimEvent and PrevAnimEvent now clear out the group flags
// 
// 40    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 39    10/04/98 11:12p Jimdose
// Made current_viewthing part of ViewMaster
// 
// 38    9/13/98 3:57p Markd
// Fixed bug where anim name was printed a frame behind
// 
// 37    9/09/98 5:57p Markd
// added viewautoanimate
// 
// 36    8/29/98 9:47p Jimdose
// Changed level.current_viewthing to current_viewthing
// 
// 35    8/27/98 7:34p Markd
// Put more functionality into viewthing
// 
// 34    8/26/98 10:35p Markd
// It now sets anim 0 when spawned, which sets last_frame_in_anim
// 
// 33    7/31/98 8:10p Jimdose
// Script commands now include flags to indicate cheats and console commands
// 
// 32    7/10/98 6:20a Jimdose
// Added viewpitch, viewroll, and viewangles events
// 
// 31    6/18/98 8:48p Jimdose
// Added better event error handling
// Added source info to events
// 
// 30    6/17/98 3:03p Markd
// Changed NumArgs back to previous behavior
// 
// 29    6/10/98 7:53p Markd
// Made NumArgs behave correctly like argc
// 
// 28    5/25/98 6:47p Jimdose
// Made animateframe, prethink and posthink into functions built into the base
// entity class
// 
// 27    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 26    5/21/98 7:33p Markd
// fixed str problem
// 
// 25    5/03/98 4:33p Jimdose
// Changed Vector class
// 
// 24    4/08/98 12:20a Jimdose
// Added viewdeleteall command
// 
// 23    4/07/98 8:00p Markd
// removed defhandle, changed all SINMDL calls to modelindex calls, removed
// SINMDL prefix
// 
// 22    4/05/98 11:17p Jimdose
// added check for null entity in PassEvent
// 
// 21    4/02/98 4:19p Jimdose
// Fixed bug where viewspawn was being placed at a wierd angle
// 
// 20    3/30/98 9:55p Jimdose
// Prepending of "models/" moved to setModel in entity
// 
// 19    3/30/98 10:00a Markd
// Added nextskin and prevskin events
// 
// 18    3/29/98 9:40p Jimdose
// made PrevFrameEvent properly loop the animation
// 
// 17    3/27/98 7:01p Markd
// Added new attach functions and bone manipulation stuff
// 
// 16    3/24/98 4:55p Jimdose
// Changed usage of GetToken to GetString so that script variables can be used
// 
// 15    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 14    3/12/98 9:49a Markd
// Fixed animstate >2, added YAW support
// 
// 13    3/11/98 11:33a Markd
// Changed behavior of viewthing, again, added fourth animation state
// 
// 12    3/11/98 11:30a Markd
// Re-worked viewthing a lot
// 
// 11    3/07/98 2:04p Markd
// Fixed Viewthing
// 
// 10    3/05/98 7:19p Markd
// Got rid of initial setmodel
// 
// 9     3/05/98 6:43p Markd
// Made it more functional
// 
// 8     3/05/98 11:03a Markd
// Updated for Q2
// 
// 6     10/28/97 6:54p Markd
// removed precache and changed default model to player
// 
// 5     10/27/97 3:29p Jimdose
// Removed dependency on quakedef.h
// 
// 4     10/23/97 6:34p Markd
// Added new animatino options
// 
// 3     10/01/97 6:37p Markd
// Added viewthing commands (ToggleAnimate and ChangeAnimation)
// 
// 2     10/01/97 2:47p Markd
// working on wander AI
// 
// 1     10/01/97 11:24a Markd
// New viewthing actor code
// 
// DESCRIPTION:
// Actor code for the Viewthing. 
//

#include "animate.h"
#include "viewthing.h"

Event EV_ViewThing_Think
   (
   "viewthing_think",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called every frame to process the view thing."
   );
Event EV_ViewThing_ToggleAnimate
   (
   "viewanimate",
   EV_CHEAT,
   NULL,
   NULL,
   "Cycle through the animations modes of the current viewthing\n"
   "No Animation\n"
   "Animation with no motion\n"
   "Animation with looping motion\n"
   "Animation with motion\n"
   );
Event EV_ViewThing_SetModel
   (
   "viewmodel",
   EV_CHEAT,
   "s",
   "viewthingModel",
   "Set the model of the current viewthing"
   );
Event EV_ViewThing_NextFrame
   (
   "viewnext",
   EV_CHEAT,
   NULL,
   NULL,
   "Advance to the next frame of animation of the current viewthing"
   );
Event EV_ViewThing_PrevFrame
   (
   "viewprev",
   EV_CHEAT,
   NULL,
   NULL,
   "Advance to the previous frame of animation of the current viewthing"
   );
Event EV_ViewThing_NextAnim
   (
   "viewnextanim", 
   EV_CHEAT,
   NULL,
   NULL,
   "Advance to the next animation of the current viewthing"
   );
Event EV_ViewThing_PrevAnim
   (
   "viewprevanim",
   EV_CHEAT,
   NULL,
   NULL,
   "Advance to the previous animation of the current viewthing"
   );
Event EV_ViewThing_ScaleUp
   (
   "viewscaleup",
   EV_CHEAT,
   NULL,
   NULL,
   "Increase the scale of the current viewthing"
   );
Event EV_ViewThing_ScaleDown
   (
   "viewscaledown",
   EV_CHEAT,
   NULL,
   NULL,
   "Decrease the scale of the current viewthing"
   );
Event EV_ViewThing_SetScale
   (
   "viewscale",
   EV_CHEAT,
   "f",
   "scale",
   "Set the scale of the current viewthing"
   );
Event EV_ViewThing_SetYaw
   (
   "viewyaw",
   EV_CHEAT,
   "f",
   "yaw",
   "Set the yaw of the current viewthing"
   );
Event EV_ViewThing_SetPitch
   (
   "viewpitch",
   EV_CHEAT,
   "f",
   "pitch",
   "Set the pitch of the current viewthing"
   );
Event EV_ViewThing_SetRoll
   (
   "viewroll",
   EV_CHEAT,
   "f",
   "roll",
   "Set the roll of the current viewthing"
   );
Event EV_ViewThing_SetAngles
   (
   "viewangles",
   EV_CHEAT,
   "f[0,360]f[0,360]f[0,360]",
   "pitch yaw roll",
   "Set the angles of the current viewthing"
   );
Event EV_ViewThing_Spawn
   (
   "viewspawn",
   EV_CHEAT,
   "s",
   "model",
   "Create a viewthing with the specified model"
   );
Event EV_ViewThing_Next
   (
   "viewthingnext",
   EV_CHEAT,
   NULL,
   NULL,
   "Change the active viewthing to the next viewthing"
   );
Event EV_ViewThing_Prev
   (
   "viewthingprev",
   EV_CHEAT,
   NULL,
   NULL,
   "Change the active viewthing to the previous viewthing"
   );
Event EV_ViewThing_Attach
   (
   "viewattach",
   EV_CHEAT,
   "ss",
   "tagname model",
   "Attach a model the the specified tagname"
   );
Event EV_ViewThing_Detach
   (
   "viewdetach",
   EV_CHEAT,
   NULL,
   NULL,
   "Detach the current viewthing from its parent"
   );
Event EV_ViewThing_DetachAll
   (
   "viewdetachall",
   EV_CHEAT,
   NULL,
   NULL,
   "Detach all the models attached to the current viewthing"
   );
Event EV_ViewThing_Delete
   (
   "viewdelete",
   EV_CHEAT,
   NULL,
   NULL,
   "Delete the current viewthing"
   );
Event EV_ViewThing_SetOrigin
   (
   "vieworigin",
   EV_CHEAT,
   "fff",
   "x y z",
   "Set the origin of the current viewthing"
   );
Event EV_ViewThing_DeleteAll
   (
   "viewdeleteall",
   EV_CHEAT,
   NULL,
   NULL,
   "Delete all viewthings"
   );
Event EV_ViewThing_LastFrame
   (
   "viewlastframe",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called when the view things last animation frame is displayed."
   );
Event EV_ViewThing_SaveOffSurfaces
   (
   "viewsavesurfaces",
	EV_DEFAULT,
   NULL,
   NULL,
   "Called after the model is spawned to save off the models original surfaces."
   );
Event EV_ViewThing_PrintTime
   (
   "_viewthing_printtime",
	EV_DEFAULT,
   NULL,
   NULL,
   "Prints out the current level.time."
   );
Event EV_ViewThing_SetAnim
   (
   "viewsetanim",
   EV_CHEAT,
   "f",
   "animNum",
   "Set the animation absolutely based off a floating point value"
   );

CLASS_DECLARATION( Animate, ViewMaster, NULL )
	{
	   { &EV_ViewThing_Spawn,				Spawn },
	   { &EV_ViewThing_Next,				Next },
	   { &EV_ViewThing_Prev,				Prev },
	   { &EV_ViewThing_SetModel,			SetModelEvent },
		{ &EV_ViewThing_DeleteAll,			DeleteAll },
	   { &EV_ViewThing_ToggleAnimate,	PassEvent },
	   { &EV_ViewThing_NextFrame,			PassEvent },
	   { &EV_ViewThing_PrevFrame,			PassEvent },
	   { &EV_ViewThing_NextAnim,			PassEvent },
	   { &EV_ViewThing_PrevAnim,			PassEvent },
	   { &EV_ViewThing_ScaleUp,			PassEvent },
	   { &EV_ViewThing_ScaleDown,			PassEvent },
	   { &EV_ViewThing_SetScale,			PassEvent },
	   { &EV_ViewThing_SetYaw,				PassEvent },
	   { &EV_ViewThing_SetPitch,			PassEvent },
	   { &EV_ViewThing_SetRoll,			PassEvent },
		{ &EV_ViewThing_SetAngles,			PassEvent },
	   { &EV_ViewThing_Attach,				PassEvent },
	   { &EV_ViewThing_Detach,				PassEvent },
	   { &EV_ViewThing_DetachAll,			PassEvent },
	   { &EV_ViewThing_Delete,				PassEvent },
	   { &EV_ViewThing_SetOrigin,			PassEvent },
	   { &EV_ViewThing_SetAnim,			PassEvent },
		{ NULL, NULL }
	};

ViewMaster Viewmodel;

ViewMaster::ViewMaster()
   {
   current_viewthing = NULL;
   }

void ViewMaster::Init( void )
   {
   gi.AddCommand( "viewanimate" );
   gi.AddCommand( "viewmodel" );
   gi.AddCommand( "viewnext" );
   gi.AddCommand( "viewprev" );
   gi.AddCommand( "viewnextanim" ); 
   gi.AddCommand( "viewprevanim" );
   gi.AddCommand( "viewscaleup" );
   gi.AddCommand( "viewscaledown" );
   gi.AddCommand( "viewscale" );
   gi.AddCommand( "viewyaw" );
   gi.AddCommand( "viewpitch" );
   gi.AddCommand( "viewroll" );
   gi.AddCommand( "viewangles" );
   gi.AddCommand( "viewspawn" );
   gi.AddCommand( "viewthingnext" );
   gi.AddCommand( "viewthingprev" );
   gi.AddCommand( "viewattach" );
   gi.AddCommand( "viewdetach" );
   gi.AddCommand( "viewdetachall" );
   gi.AddCommand( "viewdelete" );
   gi.AddCommand( "vieworigin" );
   gi.AddCommand( "viewdeleteall" );
   gi.AddCommand( "viewsetanim" );
   }

void ViewMaster::Next
	(
	Event *ev
	)

	{
	Viewthing *viewthing;
   Entity * ent;

   ent = G_FindClass( current_viewthing, "viewthing" );
	if ( ent )
		{
      current_viewthing = ent;

      viewthing = ( Viewthing * )( ( Entity * )current_viewthing );
      gi.Printf( "current viewthing model %s.\n", viewthing->model.c_str() );
      viewthing->UpdateCvars();
      }
   else
		{
      gi.Printf( "no more viewthings on map.\n" );
		}
	}

void ViewMaster::Prev
	(
	Event *ev
	)

	{
	Viewthing   *viewthing;
	Entity      *prev;
	Entity      *next;

	next = NULL;
	do
		{
		prev = next;
		next = G_FindClass( prev, "viewthing" );
		}
	while( next != current_viewthing );

	if ( prev )
		{
      current_viewthing = prev;

      viewthing = ( Viewthing * )( ( Entity * )current_viewthing );
      gi.Printf( "current viewthing model %s.\n", viewthing->model.c_str() );
      viewthing->UpdateCvars();
      }
   else
		{
      gi.Printf( "no more viewthings on map.\n" );
		}
	}

void ViewMaster::DeleteAll
	(
	Event *ev
	)

	{
	Entity *next;

	for( next = G_FindClass( NULL, "viewthing" ); next != NULL; next = G_FindClass( next, "viewthing" ) )
		{
	   next->PostEvent( EV_Remove, 0 );
      }

   current_viewthing = NULL;
	}

void ViewMaster::Spawn
	(
	Event *ev
	)

	{
	Viewthing	*viewthing;
   const char	*mdl;
   Vector		forward;
	Vector		up;
   Vector		delta;
	Event			*event;
	Entity		*ent;

   mdl = ev->GetString( 1 );
   if ( !mdl || !mdl[ 0 ] )
		{
		ev->Error( "Must specify a model name" );
		return;
		}

	// Check if we have a client
	ent = g_entities[ 0 ].entity;
	assert( ent );
	if ( !ent )
		{
		return;
		}

   // create a new viewthing
   viewthing = new Viewthing;

   // set the current_viewthing
   current_viewthing = viewthing;

   //FIXME FIXME
	ent->angles.AngleVectors( &forward, NULL, &up );

   viewthing->baseorigin = ent->origin;
   viewthing->baseorigin += forward * 48;
   viewthing->baseorigin += up * 48;

   viewthing->setOrigin( viewthing->baseorigin );
   viewthing->droptofloor( 256 );

   viewthing->baseorigin = viewthing->origin;

   delta = ent->origin - viewthing->origin;
	viewthing->setAngles( delta.toAngles() );

	event = new Event( EV_ViewThing_SetModel );
	event->AddString( mdl );
	viewthing->ProcessEvent( event );

   if ( !gi.IsModel( viewthing->edict->s.modelindex ) )
      {
		ev->Error( "model %s not found, viewmodel not spawned.", mdl );
      delete viewthing;
      current_viewthing = NULL;
      return;
      }
   }

void ViewMaster::SetModelEvent
	(
	Event *ev
	)

	{
   const char	*mdl;
   char			str[ 128 ];
	Event			*event;
	Viewthing	*viewthing;

   mdl = ev->GetString( 1 );
   if ( !mdl || !mdl[ 0 ] )
		{
		ev->Error( "Must specify a model name" );
      return;
		}

	if ( !current_viewthing )
		{
      // try to find one on the map
      current_viewthing = G_FindClass( NULL, "viewthing" );
	   if ( !current_viewthing )
         {
		   ev->Error( "No viewmodel" );
         return;
         }
		}

   viewthing = ( Viewthing * )( ( Entity * )current_viewthing );
	
	// Prepend 'models/' to make things easier
	str[ 0 ] = 0;
   if ( ( mdl[ 1 ] != ':' ) && strnicmp( mdl, "models", 6 ) )
      {
      strcpy( str, "models/" );
      }
	strcat( str, mdl );

	event = new Event( EV_ViewThing_SetModel );
	event->AddString( str );
	viewthing->ProcessEvent( event );
   viewthing->UpdateCvars();
	}

void ViewMaster::PassEvent
	(
	Event *ev
	)

	{
	Viewthing *viewthing;
	Event *event;

	if ( !current_viewthing )
		{
		ev->Error( "No viewmodel" );
      return;
		}

   viewthing = ( Viewthing * )( ( Entity * )current_viewthing );
	if ( viewthing )
		{
		event = new Event( ev );
		viewthing->ProcessEvent( event );
		}
	}

CLASS_DECLARATION( Animate, Viewthing, "viewthing" )
	{
	   { &EV_ViewThing_Think,				ThinkEvent },
	   { &EV_ViewThing_LastFrame,     	LastFrameEvent },
	   { &EV_ViewThing_ToggleAnimate,	ToggleAnimateEvent },
	   { &EV_ViewThing_SetModel,			SetModelEvent },
	   { &EV_ViewThing_NextFrame,			NextFrameEvent },
	   { &EV_ViewThing_PrevFrame,			PrevFrameEvent },
	   { &EV_ViewThing_NextAnim,			NextAnimEvent },
	   { &EV_ViewThing_PrevAnim,			PrevAnimEvent },
	   { &EV_ViewThing_ScaleUp,			ScaleUpEvent },
	   { &EV_ViewThing_ScaleDown,			ScaleDownEvent },
	   { &EV_ViewThing_SetScale,			SetScaleEvent },
	   { &EV_ViewThing_SetYaw,				SetYawEvent },
	   { &EV_ViewThing_SetPitch,			SetPitchEvent },
	   { &EV_ViewThing_SetRoll,			SetRollEvent },
	   { &EV_ViewThing_SetAngles,			SetAnglesEvent },
	   { &EV_ViewThing_Attach,				AttachModel },
	   { &EV_ViewThing_Detach,				Delete },
	   { &EV_ViewThing_DetachAll, 		DetachAll },
	   { &EV_ViewThing_Delete, 		   Delete },
	   { &EV_ViewThing_SetOrigin,			ChangeOrigin },
      { &EV_ViewThing_SaveOffSurfaces, SaveSurfaces },
	   { &EV_ViewThing_PrintTime,			PrintTime },
	   { &EV_ViewThing_SetAnim,			SetAnim },
		{ NULL, NULL }
	};

Viewthing::Viewthing
	(
	void
	)

	{
   frame = 0;
   animstate = 0;
	setSolidType( SOLID_NOT );
   baseorigin = origin;
   Viewmodel.current_viewthing = this;
   edict->s.eType = ET_MODELANIM;
   edict->s.renderfx |= RF_SHADOW;  
   edict->s.renderfx |= RF_SHADOW_PRECISE;  
   edict->s.renderfx |= RF_EXTRALIGHT;  

   // save off surfaces once the model is spawned
   PostEvent( EV_ViewThing_SaveOffSurfaces, FRAMETIME );

	PostEvent( EV_ViewThing_Think, FRAMETIME );
   }

void Viewthing::PrintTime
	(
	Event *ev
	)
	
	{
   gi.Printf( "ev current frame %d leveltime %.2f\n", ev->GetInteger( 1 ), level.time );
   }

void Viewthing::UpdateCvars
   (
   qboolean quiet
   )

   {
   gi.cvar_set( "viewmodelanim", AnimName() );
   gi.cvar_set( "viewmodelframe", va( "%d", CurrentFrame() ) );
   gi.cvar_set( "viewmodelname", model.c_str() );
   gi.cvar_set( "viewmodelscale", va( "%0.2f", edict->s.scale ) );
   gi.cvar_set( "currentviewthing", model.c_str() );
   gi.cvar_set( "viewthingorigin", va( "%0.2f,%0.2f,%0.2f", edict->s.origin[0],edict->s.origin[1],edict->s.origin[2] ) );
   gi.cvar_set( "viewmodelanimnum", va( "%.3f", ( float )CurrentAnim() / ( float )NumAnims() ) );
   if ( !quiet )
      {
      gi.Printf( "%s, frame %3d, scale %4.2f\n", AnimName(), CurrentFrame(), edict->s.scale );
      }
   }


void Viewthing::ThinkEvent
	(
	Event *ev
	)
	
	{
   int f;
   if (animstate >= 2)
      {
      Vector   forward;
	   Vector	left;
	   Vector	up;
      Vector   realmove;

	   angles.AngleVectors( &forward, &left, &up );
      realmove = left * total_delta[1] + up * total_delta[2] + forward * total_delta[0];
      setOrigin( baseorigin + realmove );
      gi.cvar_set( "viewthingorigin", va( "%0.2f,%0.2f,%0.2f", edict->s.origin[0],edict->s.origin[1],edict->s.origin[2] ) );
      }
	PostEvent( EV_ViewThing_Think, FRAMETIME );
   if ( ( animstate > 0 ) && ( Viewmodel.current_viewthing == this ) )
      {
      f = CurrentFrame();
      if ( f != lastframe )
         {
         float time;
         lastframe = f;
         time = f * AnimTime() / NumFrames();
         gi.Printf( "current frame %d time %.2f\n", f, time );
         gi.cvar_set( "viewmodeltime", va( "%.2f", time ) );
         gi.cvar_set( "viewmodelframe", va( "%d", f ) );
         gi.cvar_set( "viewmodelanim", AnimName() );
         }
      }
	}

void Viewthing::LastFrameEvent
	(
	Event *ev
	)

	{
	if ( animstate != 3 )
		{
		total_delta = "0 0 0";
		}
	}

void Viewthing::ToggleAnimateEvent
	(
	Event *ev
	)

	{
   animstate = ( animstate + 1 ) % 4;
   total_delta = "0 0 0";
   setOrigin( baseorigin );
   // reset to a known state
   switch( animstate )
      {
      case 0:
         SetFrame( frame );         
         gi.Printf( "Animation stopped.\n" );
         gi.cvar_set( "viewmodelanimmode", "Stopped" );
         break;
      case 1:
         NewAnim( CurrentAnim() );
         gi.Printf( "Animation no motion.\n" );
         gi.cvar_set( "viewmodelanimmode", "No Motion" );
         break;
      case 2:
         NewAnim( CurrentAnim(), EV_ViewThing_LastFrame );
         gi.Printf( "Animation with motion and looping.\n" );
         gi.cvar_set( "viewmodelanimmode", "Motion and Looping" );
         break;
      case 3:
         NewAnim( CurrentAnim(), EV_ViewThing_LastFrame );
         gi.Printf( "Animation with motion no looping.\n" );
         gi.cvar_set( "viewmodelanimmode", "Motion and No Looping" );
         break;
      }
   UpdateCvars( qtrue );
	}

void Viewthing::SetModelEvent
	(
	Event *ev
	)

	{
	str modelname;

   modelname = ev->GetString( 1 );

   setModel( modelname );

   if ( gi.IsModel( edict->s.modelindex ) )
      {
	   NewAnim( 0 );
      SetFrame( 0 );
      }
   UpdateCvars();
	}

void Viewthing::NextFrameEvent
	(
	Event *ev
	)

	{
   int numframes;

   numframes = NumFrames();
   if ( numframes )
      {
      frame = (frame+1)%numframes;
      SetFrame( frame );
      animstate = 0;
      UpdateCvars();
      }
	}

void Viewthing::PrevFrameEvent
	(
	Event *ev
	)

	{
   int numframes;

   numframes = NumFrames();
   if ( numframes )
      {
      frame = (frame-1)%numframes;
      SetFrame( frame );
      animstate = 0;
      UpdateCvars();
      }
	}

void Viewthing::SetAnim
	(
	Event *ev
	)

	{
   int numanims, anim;

   numanims = NumAnims();
   if ( numanims )
      {
      // restore original surfaces
      memcpy( edict->s.surfaces, origSurfaces, sizeof( origSurfaces ) );

      anim = ev->GetFloat( 1 ) * numanims;
      if ( anim >= numanims )
         anim = numanims - 1;
	   NewAnim( anim % numanims );
      frame = 0;
      SetFrame( frame );
      animstate = 0;
      UpdateCvars();
      }
	}


void Viewthing::NextAnimEvent
	(
	Event *ev
	)

	{
   int numanims;

   numanims = NumAnims();
   if ( numanims )
      {
      // restore original surfaces
      memcpy( edict->s.surfaces, origSurfaces, sizeof( origSurfaces ) );

	   NewAnim( ( CurrentAnim() + 1 ) % numanims );
      frame = 0;
      SetFrame( frame );
      animstate = 0;
      UpdateCvars();
      }
	}

void Viewthing::PrevAnimEvent
	(
	Event *ev
	)

	{
   int anim;
   int numanims;

   numanims = NumAnims();
   if ( numanims )
      {
      // restore original surfaces
      memcpy( edict->s.surfaces, origSurfaces, sizeof( origSurfaces ) );

	   anim = CurrentAnim() - 1;
      while( anim < 0 )
         {
         anim += numanims;
         }
	   NewAnim( anim );
      frame = 0;
      SetFrame( frame );
      animstate = 0;
      UpdateCvars();
      }
	}

void Viewthing::ScaleUpEvent
	(
	Event *ev
	)

	{
   edict->s.scale += 0.01f;
   UpdateCvars();
	}

void Viewthing::ScaleDownEvent
	(
	Event *ev
	)

	{
   edict->s.scale -= 0.01f;
   UpdateCvars();
	}

void Viewthing::SetScaleEvent
	(
	Event *ev
	)

	{
   float s;

   if ( ev->NumArgs() )
      {
      s = ev->GetFloat( 1 );
      edict->s.scale = s;
      UpdateCvars();
      }
   else
      {
      gi.Printf( "viewscale = %f\n", edict->s.scale );
      }
   }

void Viewthing::SetYawEvent
	(
	Event *ev
	)

	{
	if ( ev->NumArgs() > 0 )
		{
		angles.setYaw( ev->GetFloat( 1 ) );
		setAngles( angles );
		}
   gi.Printf( "yaw = %f\n", angles.yaw() );
	}

void Viewthing::SetPitchEvent
	(
	Event *ev
	)

	{
	if ( ev->NumArgs() > 0 )
		{
		angles.setPitch( ev->GetFloat( 1 ) );
		setAngles( angles );
		}
   gi.Printf( "pitch = %f\n", angles.pitch() );
	}

void Viewthing::SetRollEvent
	(
	Event *ev
	)

	{
	if ( ev->NumArgs() > 0 )
		{
		angles.setRoll( ev->GetFloat( 1 ) );
		setAngles( angles );
		}
   gi.Printf( "roll = %f\n", angles.roll() );
	}

void Viewthing::SetAnglesEvent
	(
	Event *ev
	)

	{
	if ( ev->NumArgs() > 2 )
		{
		angles.x = ev->GetFloat( 1 );
		angles.y = ev->GetFloat( 2 );
		angles.z = ev->GetFloat( 3 );
		setAngles( angles );
		}

   gi.Printf( "angles = %f, %f, %f\n", angles.x, angles.y, angles.z );
	}

void Viewthing::AttachModel
	(
	Event *ev
	)

	{
   Event * event;
   Viewthing * child;


   child = new Viewthing;
   child->setModel( ev->GetString( 2 ) );

   // 
   // attach the child
   //
   event = new Event( EV_Attach );
   event->AddEntity( this );
   event->AddString( ev->GetString( 1 ) );
   child->ProcessEvent( event );
	}

void Viewthing::Delete
	(
	Event *ev
	)

	{
   Viewmodel.current_viewthing = NULL;
   PostEvent( EV_Remove, 0 );
   Viewmodel.PostEvent( EV_ViewThing_Next, 0 );
	}

void Viewthing::DetachAll
	(
	Event *ev
	)

	{
   int i;
   int num;

   num = numchildren;
   for (i=0;i<MAX_MODEL_CHILDREN;i++)
      {
      Entity * ent;
      if (!children[i])
         continue;
      ent = ( Entity * )G_GetEntity( children[i] );
      ent->PostEvent( EV_Remove, 0 );
      num--;
      if (!num)
         break;
      }
	}

void Viewthing::ChangeOrigin
	(
	Event *ev
	)

	{
   if ( ev->NumArgs() )
      {
      origin.x = ev->GetFloat( 1 );
      origin.y = ev->GetFloat( 2 );
      origin.z = ev->GetFloat( 3 );
      setOrigin( origin );
      baseorigin = origin;
      UpdateCvars();
      }
   gi.Printf( "vieworigin = x%f y%f z%f\n", origin.x, origin.y, origin.z );
   }

void Viewthing::SaveSurfaces
	(
	Event *ev
	)
	
	{
   memcpy( origSurfaces, edict->s.surfaces, sizeof( origSurfaces ) );
   }

