//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/animate.cpp                        $
// $Revision:: 38                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/22/00 7:32p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/animate.cpp                             $
// 
// 38    7/22/00 7:32p Markd
// bullet proofed RandomAnimate code
// 
// 37    6/26/00 5:50p Markd
// re-did some renderfx commands, fixed anti-sb juice stuff
// 
// 36    6/23/00 9:14p Markd
// don't go into NewAnim if we are currently loading a saved game
// 
// 35    6/22/00 5:32p Steven
// Made it so server commands don't get run if RF_DONT_PROCESS_COMMANDS is set.
// 
// 34    6/21/00 6:02p Markd
// allowed lower framerate animations to still post animations properly
// 
// 33    6/05/00 3:11p Markd
// fixed HasCommands calls in server
// 
// 32    5/02/00 10:59a Aldie
// Fix for initializations
// 
// 31    4/14/00 11:31a Aldie
// Fixed cut and paste error
// 
// 30    4/13/00 7:04p Aldie
// Fixed bug for animation events where the anim was greater than 255.  Added
// animframe and animnumber to Event.
// 
// 29    4/11/00 5:30p Markd
// fixed one frame animation bug
// 
// 28    4/01/00 3:46p Markd
// Added single frame animation optimization
// 
// 27    3/27/00 6:24p Markd
// reworked NewAnim function
// 
// 26    3/21/00 2:30p Aldie
// Fixed a statck overflow with ClearTorsoAnim and ClearLegsAnim
// 
// 25    3/20/00 5:00p Aldie
// Fixes for entry and exit commands
// 
// 24    3/15/00 4:09p Aldie
// Fixed a bug with using weapons, and added some ability to force a state in
// the player
// 
// 23    2/23/00 11:44a Markd
// fixed bug with 1 frame animations
// 
// 22    2/22/00 6:20p Markd
// modified the way that the animation system works so that the animdone event
// is actually played 1 frame before the end of the animation
// 
// 21    2/16/00 6:54p Markd
// reordered deltas and time based events
// 
// 20    2/14/00 5:43p Jimdose
// legs anims are now only mixed in if ANIM_BLEND is set
// 
// 19    2/09/00 6:02p Markd
// added entry and exit support to server side
// 
// 18    1/27/00 9:05a Markd
// fixed enttiy type over writing
// 
// 17    1/26/00 12:03p Markd
// added back old lighting code for certain objects in the game
// 
// 16    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 15    1/19/00 8:50p Jimdose
// added Anim_AbsolueDelta
// 
// 14    1/12/00 11:27a Markd
// made entities which don't explicitly animate, not animate
// 
// 13    1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 12    12/10/99 12:30p Jimdose
// calling NewAnim multiple times per frame no longer toggles the togglebit
// more than once (which used to sometimes cause the animation not to change)
// 
// 11    12/09/99 7:37p Jimdose
// changed magic number to MDL_ANIM_DELTA_DRIVEN
// 
// 10    12/01/99 4:56p Markd
// fixed some reference versus pointer issues with RandomAnimate and NewAnim
// 
// 9     12/01/99 3:17p Aldie
// fix for animation bug
// 
// 8     11/11/99 5:25p Jimdose
// added separate torso animation
// 
// 7     11/11/99 3:54p Jimdose
// readded separate torso animations
// 
// 6     10/19/99 7:52p Markd
// Removed three part model system
// 
// 5     10/08/99 2:12p Markd
// Made Animate entities of type MODELANIM
// 
// 4     10/06/99 7:25p Markd
// removed TIMESTAMP, time and fixed make_static bug
// 
// 3     9/27/99 6:18p Markd
// Added event documentation
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 22    9/01/99 9:08p Markd
// added animate once support
// 
// 21    8/27/99 5:00p Markd
// cleaned up animate code so that deltas were only posted as needed
// 
// 20    8/27/99 4:35p Jimdose
// changed NewAnim to post the anim done event after the frame events instead
// of before.
// 
// 19    8/19/99 6:59p Markd
// removed the old tiki_cmd structure, now tiki_cmd_t is passed into the tiki
// functions
// 
// 18    8/19/99 6:40p Steven
// Added a stop anim event.
// 
// 17    8/09/99 5:07p Aldie
// More changes to accomodate weapons system
// 
// 16    8/05/99 9:14a Steven
// Added a stop animating at end so that it wouldn't skip to beginning of
// animation again.
// 
// 15    7/14/99 4:41p Markd
// Changed at which times events are posted
// 
// DESCRIPTION: Animate Class
// 

#include "g_local.h"
#include "animate.h"
#include "player.h"
#include "../qcommon/qfiles.h"

// Leg Animation events
Event EV_Anim
   ( 
   "anim",
   0,
   "s",
   "animName",
   "set the legs animation to animName."
   );

Event EV_SetFrame
   ( 
   "setframe",
   0,
   "iS",
   "frameNumber animName",
   "Set the frame on the legs, if anim is not specified, current is assumed."
   );
Event EV_AnimDone
   ( 
   "animdone",
   0,
   NULL,
   NULL,
   "Legs animation has finished, not for script use."
   );
Event EV_FrameDelta
   ( 
   "setmovedelta",
   0,
   "vf",
   "moveDelta moveTime",
   "movement from animation, not for script use."
   );
Event EV_StopAnimating
   ( 
   "stopanimating",
   0,
   NULL,
   NULL,
   "stop the legs from animating.  Animation will end at the end of current cycle."
   );

// Torso Animation events
Event EV_Torso_Anim
   ( 
   "torso_anim",
   0,
   "s",
   "animName",
   "set the torso animation to animName."
   );
Event EV_Torso_SetFrame
   ( 
   "torso_setframe",
   0,
   "iS",
   "frameNumber animName",
   "Set the frame on the torso, if anim is not specified, current is assumed."
   );
Event EV_Torso_AnimDone
   ( 
   "torso_animdone",
   0,
   NULL,
   NULL,
   "Torso animation has finished, not for script use."
   );
Event EV_Torso_StopAnimating
   ( 
   "torso_stopanimating",
   0,
   NULL,
   NULL,
   "stop the torso from animating.  Animation will end at the end of current cycle."
   );

Event EV_NewAnim
   ( 
   "animate_newanim",
   0,
   "ii",
   "animNum bodyPart",
   "Start a new animation, not for script use."
   );

CLASS_DECLARATION( Entity, Animate, "animate" )
	{
      { &EV_Anim,             Legs_AnimEvent },
		{ &EV_SetFrame,			Legs_SetFrameEvent },
		{ &EV_AnimDone,			Legs_AnimDoneEvent },
		{ &EV_StopAnimating,		Legs_StopAnimating },
		{ &EV_FrameDelta,			FrameDeltaEvent },
      { &EV_NewAnim,          NewAnimEvent },

      { &EV_Torso_Anim,       Torso_AnimEvent },
		{ &EV_Torso_SetFrame,	Torso_SetFrameEvent },
		{ &EV_Torso_AnimDone,	Torso_AnimDoneEvent },
		{ &EV_Torso_StopAnimating,Torso_StopAnimating },

		{ NULL, NULL }
	};

Animate::Animate()
	{
	// Animation variables
   frame_delta    = "0 0 0";
	animDoneEvent	= NULL;
	torso_animDoneEvent	= NULL;

   legs_animtime = 0;
   torso_animtime = 0;

   legs_starttime = 0;
   torso_starttime = 0;

   legs_numframes = 0;
   torso_numframes = 0;

   edict->s.anim        |= (ANIM_SERVER_EXITCOMMANDS_PROCESSED);
   edict->s.torso_anim  |= (ANIM_SERVER_EXITCOMMANDS_PROCESSED);
	}

void Animate::NewAnim
	(
	int animnum,
   bodypart_t part
	)

   {
   float totaltime;
   int   *anim;
   int   flags;
   int   i;
   float time;
   tiki_cmd_t cmds;
   Event *ev;
   float *starttime;
   float *animtime;
   float *frametime;
   int   *numframes;
   int   last_anim,last_anim_flags;
   qboolean dodelta; // should we even post movement delta stuff?
   qboolean has_commands; // does this animation have any frame commands

   //
   // this is an animating model, we set this here so that non-animating models 
   // don't have to go through the animating code path
   //
   if ( edict->s.eType == ET_GENERAL )
      {
      edict->s.eType = ET_MODELANIM;
      }

   if ( LoadingSavegame )
      {
      // if we are loading a game, we don't need to start animating, that will be automatic
      // all these events would mess everything up anyway
      return;
      }

   // initially don't post move delta stuff   
   dodelta = qfalse;

   switch( part )
      {
      case legs:
         anim = &edict->s.anim;
      	edict->s.frame &= ~FRAME_EXPLICIT;
         flags = EVENT_LEGS_ANIM;
         animtime = &legs_animtime;
         starttime = &legs_starttime;
         frametime = &legs_frametime;
         numframes = &legs_numframes;
         break;
      case torso:
         anim = &edict->s.torso_anim;
      	edict->s.torso_frame &= ~FRAME_EXPLICIT;
         flags = EVENT_TORSO_ANIM;
         animtime = &torso_animtime;
         starttime = &torso_starttime;
         frametime = &torso_frametime;
         numframes = &torso_numframes;
         break;
      default:
         warning( "NewAnim", "Unknown body part %d", part );
         return;
         break;
      }

   last_anim = *anim & ANIM_MASK;
   last_anim_flags = *anim;

   //
   // if the animations were different we need to process the entry and exit events   
   //
   if ( ( last_anim != animnum ) && !( last_anim_flags & ANIM_SERVER_EXITCOMMANDS_PROCESSED ) )
      {
      // exit the previous animation
      if ( gi.Frame_Commands( edict->s.modelindex, last_anim, TIKI_FRAME_CMD_EXIT, &cmds ) )
         {
         int ii, j;

         for( ii = 0; ii < cmds.num_cmds; ii++ )
            {
      	   ev = new Event( cmds.cmds[ ii ].args[ 0 ] );
         	
            ev->SetSource( EV_FROM_ANIMATION );
            ev->SetAnimationNumber( last_anim );
            ev->SetAnimationFrame( 0 );

            for( j = 1; j < cmds.cmds[ ii ].num_args; j++ )
               {
      		   ev->AddToken( cmds.cmds[ ii ].args[ j ] );
               }
            ProcessEvent( ev );
            }
         }
      }

   if ( ( animnum >= 0 ) && ( animnum < gi.NumAnims( edict->s.modelindex ) ) )
		{
      if ( *starttime == level.time )
         {
         // don't toggle the togglebit if we've already had an animation set this frame
         *anim = ( *anim & ANIM_TOGGLEBIT ) | animnum | ANIM_BLEND;
         }
      else
         {
         *anim = ( ( *anim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | animnum | ANIM_BLEND;
         }
		}
   else 
		{
		// bad value
      return;
		}

   // get rid of old anim events
   CancelFlaggedEvents( flags );

   // get total time of animation
   totaltime = gi.Anim_Time( edict->s.modelindex, animnum );

   // set the total time for the animation
   *animtime = totaltime;

   // set the start time of the animation
   *starttime = level.time;

   // set the number of frames for the animation
   *numframes = gi.Anim_NumFrames( edict->s.modelindex, animnum );

   // set the time for each animation frame
   *frametime = gi.Frame_Time( edict->s.modelindex, animnum, 0 );

   has_commands = gi.Anim_HasCommands( edict->s.modelindex, animnum );

	if ( edict->s.eFlags & EF_DONT_PROCESS_COMMANDS )
		has_commands = false;

   if ( ( last_anim != animnum ) && ( has_commands ) )
      {
      // enter this animation
      if ( gi.Frame_Commands( edict->s.modelindex, animnum, TIKI_FRAME_CMD_ENTRY, &cmds ) )
         {
         int ii, j;

         for( ii = 0; ii < cmds.num_cmds; ii++ )
            {
      	   ev = new Event( cmds.cmds[ ii ].args[ 0 ] );
         	
            ev->SetSource( EV_FROM_ANIMATION );
            ev->SetAnimationNumber( animnum );
            ev->SetAnimationFrame( 0 );

            for( j = 1; j < cmds.cmds[ ii ].num_args; j++ )
               {
      		   ev->AddToken( cmds.cmds[ ii ].args[ j ] );
               }
            ProcessEvent( ev );
            }
         }
      }


   // if it is the legs, find out if there is a delta and if it is a delta_driven animation
   if ( part == legs )
      {
      float  length;
      Vector totaldelta;

      gi.Anim_AbsoluteDelta( edict->s.modelindex, animnum, totaldelta );
      length = totaldelta.length();
      if ( length > MINIMUM_DELTA_MOVEMENT )
         {
         int flags;

         flags = gi.Anim_Flags( edict->s.modelindex, animnum );
         if ( !( flags & MDL_ANIM_DELTA_DRIVEN ) )
            {
            length /= *numframes;
            if ( length > MINIMUM_DELTA_MOVEMENT_PER_FRAME )
               {
               dodelta = qtrue;
               }
            }
         }
      }

   if ( has_commands || dodelta )
      {
      time = 0;

      for( i = 0; i < *numframes; i++ )
         {
         if ( has_commands )
            {
            // we want normal frame commands to occur right on the frame
            if ( gi.Frame_Commands( edict->s.modelindex, animnum, i, &cmds ) )
               {
               int ii, j;

               for( ii = 0; ii < cmds.num_cmds; ii++ )
                  {
      	         ev = new Event( cmds.cmds[ ii ].args[ 0 ] );
         	      
                  ev->SetSource( EV_FROM_ANIMATION );
                  ev->SetAnimationNumber( animnum );
                  ev->SetAnimationFrame( i );

                  for( j = 1; j < cmds.cmds[ ii ].num_args; j++ )
                     {
      		         ev->AddToken( cmds.cmds[ ii ].args[ j ] );
                     }
                  PostEvent( ev, time, flags );
                  }
               }
            }
         // add to time
         time += *frametime;

         // we want deltas to occur at the end of the frame
         // only add deltas on the legs
         if ( dodelta )
            {
            Vector delta;

            // get the current frame delta
	         gi.Frame_Delta( edict->s.modelindex, animnum, i, delta );

            if ( *frametime > FRAMETIME )
               {
               float time_offset;

               VectorScale( delta, ( FRAMETIME / *frametime ), delta );

               for ( time_offset = 0; time_offset < *frametime; time_offset += FRAMETIME )
                  {
                  ev = new Event( EV_FrameDelta );
                  ev->AddVector( delta );
                  ev->AddFloat( *frametime );
                  PostEvent( ev, time + time_offset, flags );
                  }
               }
            else
               {
               ev = new Event( EV_FrameDelta );
               ev->AddVector( delta );
               ev->AddFloat( *frametime );
               PostEvent( ev, time, flags );
               }
            }

         }
      }

   //
   // if we have a 1 frame animation, which has no commands,
   // we aren't a subclass of Sentient and our animation time is the same as frametime
   // there is no reason for us to constantly animate, since nothing will change
   // lets get the hell out of dodge!
   if ( 
         ( *numframes == 1 ) && 
         !isSubclassOf( Player ) && 
         !has_commands &&
         ( *frametime == FRAMETIME )
      )
      {
      switch( part )
         {
         case legs:
	         if ( animDoneEvent )
		         {
	            PostEvent( *animDoneEvent, 0 );
		         }
            break;
         case torso:
	         if ( torso_animDoneEvent )
		         {
	            PostEvent( *torso_animDoneEvent, 0 );
		         }
            break;
         default:
            break;
         }
      return;
      }

   switch( part )
      {
      case legs:
         if ( totaltime > *frametime )
            PostEvent( EV_AnimDone, totaltime - *frametime, flags );
         else
            PostEvent( EV_AnimDone, totaltime, flags );
         break;
      case torso:
         if ( totaltime > *frametime )
            PostEvent( EV_Torso_AnimDone, totaltime - *frametime, flags );
         else
            PostEvent( EV_Torso_AnimDone, totaltime, flags );
         break;
      default:
         warning( "NewAnim", "Unknown body part %d", part );
         return;
         break;
      }
   }

void Animate::NewAnim
	(
	int animnum,
	Event &newevent,
   bodypart_t part
	)
   {
   SetAnimDoneEvent( newevent, part );
   NewAnim( animnum, part );
   }

void Animate::NewAnim
	(
	int animnum,
	Event *newevent,
   bodypart_t part
	)
   {
   SetAnimDoneEvent( newevent, part );
   NewAnim( animnum, part );
   }

void Animate::FrameDeltaEvent
	(
	Event *ev
	)

	{
   frame_delta = ev->GetVector( 1 );
   move_time = ev->GetFloat( 2 );
   total_delta += frame_delta * edict->s.scale;
	}

void Animate::EndAnim
	(
   bodypart_t part
	)

   {
   Event * ev;

   switch( part )
      {
      case legs:
	      if ( animDoneEvent )
		      {
	         PostEvent( *animDoneEvent, 0 );
		      }
         ev = new Event( EV_NewAnim );
         ev->AddInteger( edict->s.anim );
         ev->AddInteger( part );
         if ( legs_animtime > legs_frametime )
            PostEvent( ev, legs_frametime, EVENT_LEGS_ANIM );
         else
            PostEvent( ev, 0, EVENT_LEGS_ANIM );
         break;
      case torso:
	      if ( torso_animDoneEvent )
		      {
	         PostEvent( *torso_animDoneEvent, 0 );
		      }
         ev = new Event( EV_NewAnim );
         ev->AddInteger( edict->s.torso_anim );
         ev->AddInteger( part );
         if ( torso_animtime > torso_frametime )
            PostEvent( ev, torso_frametime, EVENT_TORSO_ANIM );
         else
            PostEvent( ev, 0, EVENT_TORSO_ANIM );
         break;
      default:
         warning( "EndAnim", "Unknown body part %d", part );
         return;
         break;
      }
   }

void Animate::SetAnimDoneEvent
	(
   Event *event,
   bodypart_t part
   )
   {
   Event **doneevent;

   switch( part )
      {
      case legs:
         doneevent = &animDoneEvent;
         break;
      case torso:
         doneevent = &torso_animDoneEvent;
         break;
      default:
         warning( "SetAnimDoneEvent", "Unknown body part %d", part );
         return;
         break;
      }
   if ( *doneevent )
      {
      delete *doneevent;
      }

   *doneevent = event;
   }

void Animate::SetAnimDoneEvent
	(
   Event &event,
   bodypart_t part
   )
   {
   SetAnimDoneEvent( new Event( event ), part );
   }

void Animate::RandomAnimate
	(
   const char *animname,
	Event *endevent,
   bodypart_t part
   )

   {
   Event *event_to_post;
   int   num;
   int   flags;
   qboolean allparts;

   assert( animname );
   if ( !animname )
      {
      return;
      }

   allparts = false;
   if ( part == all )
      {
      allparts = true;
      }

   do {
      if ( allparts )
         {
         switch( part )
            {
            case all:
               part = legs;
               break;
            case legs:
               part = torso;
               break;
            case torso:
               return;
               break;
            }
         }
      switch( part )
         {
         case legs:
            flags = EVENT_LEGS_ANIM;
            break;
         case torso:
            flags = EVENT_TORSO_ANIM;
            break;
         default:
            warning( "RandomAnimate", "Unknown body part %d", part );
            return;
            break;
         }
	   num = gi.Anim_Random( edict->s.modelindex, animname );

      currentAnim = animname;

      //
      // this is here to ensure that multiple distinct events are posted for each body part
      //
      if ( allparts && ( part != legs ) )
         {
         if ( endevent )
            {
            event_to_post = new Event( endevent );
            }
         else
            {
            event_to_post = NULL;
            }
         }
      else
         {
         event_to_post = endevent;
         }

      //
      // see if we even have a valid animation at all
      //
      if ( num == -1 )
         {
         if ( event_to_post )
			   {
	         PostEvent( event_to_post, FRAMETIME, flags );
			   }
         }
      else
         {
         SetAnimDoneEvent( event_to_post, part );
         NewAnim( num, part );
         }
      } while( allparts );
   }

void Animate::SetFrame
	( 
   int framenum,
   bodypart_t part,
   int anim
	)

   {
   int   flags;
   int   numframes;
   int   *panim;
   int   *frame;

   switch( part )
      {
      case legs:
         frame = &edict->s.frame;
         flags = EVENT_LEGS_ANIM;
         numframes = legs_numframes;
         panim = &edict->s.anim;
         break;
      case torso:
         frame = &edict->s.torso_frame;
         flags = EVENT_TORSO_ANIM;
         numframes = torso_numframes;
         panim = &edict->s.torso_anim;
         break;
      default:
         warning( "SetFrame", "Unknown body part %d", part );
         return;
         break;
      }

   if ( anim >= 0 )
      {
      numframes = gi.Anim_NumFrames( edict->s.modelindex, anim );
      }

   if ( framenum < 0 || framenum >= numframes )
      {
      warning( "SetFrame","Frame is out of range" );
      return;
      }

   // get rid of old anim events so we don't animate
   CancelFlaggedEvents( flags );

   *frame = framenum | FRAME_EXPLICIT;

   // if we have a frame override, make sure to set the animation as well
   if ( anim >= 0 )
      {
      *panim = anim | ANIM_BLEND;
      }
   }

qboolean Animate::HasAnim
	(
   const char *animname
   )
   {
   int num;

	num = gi.Anim_Random( edict->s.modelindex, animname );
   return ( num >= 0 );
   }

void Animate::NewAnimEvent
	(
	Event *ev
	)

	{
   NewAnim( ev->GetInteger( 1 ) & ANIM_MASK, (bodypart_t) ev->GetInteger( 2 ) );
	}

void Animate::StopAnimating
	(
   bodypart_t part
   )
   {
   int frame;
   int anim;

   if ( part == all )
      {
      // legs
      frame = CurrentFrame( legs );
      anim = CurrentAnim( legs );
      SetFrame( frame, legs, anim );
      // torso
      frame = CurrentFrame( torso );
      anim = CurrentAnim( torso );
      SetFrame( frame, torso, anim );
      }
   else
      {
      frame = CurrentFrame( part );
      anim = CurrentAnim( part );
      SetFrame( frame, part, anim );
      }
   }

void Animate::StopAnimatingAtEnd
	(
   bodypart_t part
   )
   {
   int anim;

   if ( part == all )
      {
		StopAnimatingAtEnd( legs );
		StopAnimatingAtEnd( torso );
      }
   else if ( part == legs )
      {
      anim = CurrentAnim( part );
      SetFrame( legs_numframes - 1, part, anim );
      }
	else if ( part == torso )
      {
      anim = CurrentAnim( part );
      SetFrame( legs_numframes - 1, part, anim );
      }
   }


////////////////////////////
// 
// BODY PART SPECIFIC EVENTS
//
////////////////////////////

// Legs

void Animate::Legs_AnimDoneEvent
	(
	Event *ev
	)

	{
   EndAnim( legs );
	}


void Animate::Legs_AnimEvent
	(
	Event *ev
	)

	{
   RandomAnimate( ev->GetString( 1 ), NULL, legs );
	}

void Animate::Legs_SetFrameEvent
	( 
	Event *ev
	)

   {
	int framenum;
   int animnum;

	framenum = ev->GetInteger( 1 );
   if ( ev->NumArgs() > 1 )
      {
      animnum = gi.Anim_NumForName( edict->s.modelindex, ev->GetString( 2 ) );
      }
   else
      {
      animnum = -1;
      }

   SetFrame( framenum, legs, animnum );
   }

// HACK HACK HACK
void Animate::Legs_StopAnimating
	(
	Event *ev
	)

	{
   CancelFlaggedEvents( EVENT_LEGS_ANIM );
	}

// Torso

void Animate::Torso_AnimDoneEvent
	(
	Event *ev
	)

	{
   EndAnim( torso );
	}

void Animate::Torso_AnimEvent
	(
	Event *ev
	)

	{
   RandomAnimate( ev->GetString( 1 ), NULL, torso );
	}

void Animate::Torso_SetFrameEvent
	( 
	Event *ev
	)

   {
	int framenum;
   int animnum;

	framenum = ev->GetInteger( 1 );
   if ( ev->NumArgs() > 1 )
      {
      animnum = gi.Anim_NumForName( edict->s.modelindex, ev->GetString( 2 ) );
      }
   else
      {
      animnum = -1;
      }

   SetFrame( framenum, torso, animnum );
   }

// HACK HACK HACK
void Animate::Torso_StopAnimating
	(
	Event *ev
	)

	{
   CancelFlaggedEvents( EVENT_TORSO_ANIM );
	}

void Animate::ClearTorsoAnim
   (
   void
   )

   {
   tiki_cmd_t  cmds;
   int         last_anim;
   static qboolean clearing=qfalse;

   last_anim = edict->s.torso_anim & ANIM_MASK;   

   if ( ( edict->s.torso_anim & ANIM_BLEND ) && !( edict->s.torso_anim & ANIM_SERVER_EXITCOMMANDS_PROCESSED ) && !clearing )
      {
      if ( gi.Frame_Commands( edict->s.modelindex, last_anim, TIKI_FRAME_CMD_EXIT, &cmds ) )
         {
         int ii, j;

         clearing = qtrue;
         for( ii = 0; ii < cmds.num_cmds; ii++ )
            {
            Event *ev = new Event( cmds.cmds[ ii ].args[ 0 ] );
      
            ev->SetSource( EV_FROM_ANIMATION );
            ev->SetAnimationNumber( last_anim );
            ev->SetAnimationFrame( 0 );

            for( j = 1; j < cmds.cmds[ ii ].num_args; j++ )
               {
      	      ev->AddToken( cmds.cmds[ ii ].args[ j ] );
               }
            ProcessEvent( ev );
            }
         clearing = qfalse;
         }
      edict->s.torso_anim |= ANIM_SERVER_EXITCOMMANDS_PROCESSED;
      }

   CancelFlaggedEvents( EVENT_TORSO_ANIM );
   edict->s.torso_anim &= ~ANIM_BLEND;
   }

void Animate::ClearLegsAnim
   (
   void
   )

   {
   tiki_cmd_t        cmds;
   int               last_anim;
   static qboolean   clearing=qfalse;

   if ( edict->s.anim & ANIM_SERVER_EXITCOMMANDS_PROCESSED )
      {
      last_anim = edict->s.anim & ANIM_MASK;

      if ( gi.Frame_Commands( edict->s.modelindex, last_anim, TIKI_FRAME_CMD_EXIT, &cmds ) )
         {
         int ii, j;

         clearing = qtrue;
         for( ii = 0; ii < cmds.num_cmds; ii++ )
            {
            Event *ev = new Event( cmds.cmds[ ii ].args[ 0 ] );
      
            ev->SetSource( EV_FROM_ANIMATION );
            ev->SetAnimationNumber( last_anim );
            ev->SetAnimationFrame( 0 );

            for( j = 1; j < cmds.cmds[ ii ].num_args; j++ )
               {
      	      ev->AddToken( cmds.cmds[ ii ].args[ j ] );
               }
            ProcessEvent( ev );
            }
         clearing = qfalse;
         }
      edict->s.anim |= ANIM_SERVER_EXITCOMMANDS_PROCESSED;
      }

   CancelFlaggedEvents( EVENT_LEGS_ANIM );

   edict->s.anim &= ~ANIM_BLEND;
   }
