//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_modelanim.c                     $
// $Revision:: 83                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/30/00 2:58p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_modelanim.c                          $
// 
// 83    7/30/00 2:58p Markd
// don't use ground targeting reticle when they are standing in water
// 
// 82    7/28/00 2:39a Aldie
// Added notimecheck anim flag, and handle it in cg_modelanim to help with
// jittering on crossblending
// 
// 81    7/23/00 1:28p Aldie
// Trying out some fixes for crossblending hitches
// 
// 80    7/23/00 10:47a Aldie
// Fixed a syntax error
// 
// 79    7/23/00 12:28a Aldie
// Slight fix for frame lerping problems in the player anims
// 
// 78    7/03/00 9:11p Markd
// fixed lerping issue when entities are reset
// 
// 77    6/26/00 5:50p Markd
// re-did some renderfx commands, fixed anti-sb juice stuff
// 
// 76    6/06/00 1:59p Aldie
// Added fadein to marks
// 
// 75    6/05/00 3:10p Markd
// Added has_commands check to client side command processing
// 
// 74    6/04/00 6:03p Markd
// Added precise shadow support
// 
// 73    6/03/00 5:25p Aldie
// Take out shadow on hidden RF_DONTDRAW objects
// 
// 72    6/03/00 10:55a Markd
// Sped up tracing and debug print messages
// 
// 71    5/25/00 9:57a Steven
// Made it so the player's shadow is not drawn if in first person mode.
// 
// 70    5/22/00 8:00p Markd
// fixed crossblend problem
// 
// 69    5/22/00 4:49p Markd
// added fix for blend bit not being masked off on crossblend anim
// 
// 68    5/09/00 1:29p Aldie
// Added lightstyles to impact marks
// 
// 67    5/03/00 5:27p Markd
// when resetting the animation, we set the old anim and old frame to the new
// anim and new frame so that we don't get unwanted crossfading
// 
// 66    5/02/00 3:46p Markd
// fixed targeting reticles spinning the right direction
// 
// 65    4/29/00 11:45a Markd
// made targeting reticles turn in the same direction
// 
// 64    4/21/00 4:36p Steven
// Bulletproofed CG_RunModelAnimation a little more.
// 
// 63    4/21/00 3:02p Markd
// removed RF_LIGHTINGORIGIN usage from models
// 
// 62    4/05/00 7:09p Markd
// fixed exit command problem
// 
// 61    4/03/00 10:55a Markd
// fixed targeting reticles on flying creatures
// 
// 60    3/22/00 11:19a Markd
// fixed lighting bug on attached models
// 
// 59    3/20/00 9:39a Markd
// fixed driven animations when switching animations and net resetting the
// frame of the animation
// 
// 58    3/18/00 10:25a Markd
// fixed some bit masking issues with anims in ValidateSkelFrame and the model
// code
// 
// 57    3/03/00 4:36p Markd
// Fixed air targeting on creatures
// 
// 56    2/24/00 3:18p Jimdose
// when changing from no legs or no torso anim, crossblend from the opposite
// part's animation
// 
// 55    2/23/00 1:46p Jimdose
// removed warning about uselegs and usetorso not being set
// 
// 54    2/23/00 12:15p Jimdose
// added checks to prevent an animation without legs or torso
// 
// 53    2/22/00 5:55p Markd
// Fixed 2 frame animations with low framerate
// 
// 52    2/21/00 2:51p Markd
// Added GlobalRadius support to tikis
// 
// 51    2/16/00 6:58p Markd
// cleaned up version of new animation system
// 
// 50    2/16/00 6:56p Markd
// added new animation system
// 
// 49    2/15/00 8:55p Jimdose
// fixed animation frames and delta sync problem
// 
// 48    2/14/00 5:48p Jimdose
// legs animation now only plays when ANIM_BLEND is set on anim or if uselegs
// is set
// 
// 47    2/14/00 10:09a Markd
// Tweaked targeting reticles
// 
// 46    2/12/00 4:32p Markd
// fixed some bugs with the targeting
// 
// 45    2/12/00 3:44p Markd
// Added targeted entity support
// 
// 44    2/12/00 3:24p Jimdose
// renamed ANIM_BLEND_TORSO to ANIM_BLEND
// 
// 43    1/27/00 1:16p Steven
// Fixed some looping sound origin issues.
// 
// 42    1/26/00 10:49p Jimdose
// crossblending was taking the crossblend time from the source anim and not
// the destination anim
// 
// 41    1/26/00 5:56p Jimdose
// CG_ClearModelAnimation now sets crossblend_frametime to cg.time.  This way,
// the game doesn't try to crossblend just because a model entered the view
// 
// 40    1/26/00 3:34p Markd
// Added Renderfx mask for inherited entities
// 
// 39    1/25/00 8:08p Jimdose
// added crossblend time to tikis
// 
// 38    1/19/00 6:42p Markd
// Added UpdateEntity to CG_General and ModelAnim specifically
// 
// 37    1/19/00 12:32p Jimdose
// trying some code to fix pause in looking anims
// 
// 36    1/11/00 7:16p Markd
// fixed com_speeds bug where rendering time was not being properly subtracted
// from client time
// 
// 35    12/17/99 7:03p Markd
// changed shadow code a little bit
// 
// 34    12/14/18 2:42p Jimdose
// fixed problem with FRAME_EXPLICIT models not showing proper animation frame.
// 
// 33    12/13/99 3:30p Aldie
// Updated printout
// 
// 32    12/09/99 7:42p Jimdose
// got rid of ignore_angles
// 
// 31    12/09/99 10:52a Jimdose
// got tags working with torso and crossblended animations
// 
// 30    11/17/99 3:07p Markd
// Fixed lerping problem in animation system
// 
// 29    11/17/99 12:17p Markd
// Took out RF_NOSHADOW flag
// 
// 28    11/17/99 10:08a Markd
// Lightened character shadows slightly
// 
// 27    11/17/99 10:07a Markd
// fixed bug with first person models
// 
// 26    11/16/99 7:03p Markd
// Put in variable shadows based off of bounding box sizes
// 
// 25    11/11/99 3:53p Jimdose
// fixed crossblending into and out of torso animations
// 
// 24    11/11/99 11:34a Jimdose
// first pass at torso animation blending in
// 
// 23    11/10/99 2:18p Jimdose
// working on torso animation
// 
// 22    11/04/99 11:34a Jimdose
// fixed problem where CG_ClearModelAnimation set the animation crossfading
// into a state that wouldn't animate until the animation changed
// 
// 21    11/01/99 4:11p Jimdose
// made tags work with bone controllers
// 
// 20    11/01/99 10:35a Markd
// if there is no tikihandle, still setup frame and anim as a general entity
// 
// 19    10/29/99 6:52p Jimdose
// added bone controllers
// 
// 18    10/28/99 6:05p Steven
// Added a use_angles flag and an offset to the entity attach stuff.
// 
// 17    10/26/99 6:30p Jimdose
// added animation blending
// 
// 16    10/25/99 12:20p Jimdose
// made head and torso angles local to each entity
// 
// 15    10/22/99 10:43a Markd
// Rewrote command processor
// 
// 14    10/19/99 7:52p Markd
// Removed three part model system
// 
// 13    10/08/99 7:36p Markd
// put in -1 frame check in ModelAnim
// 
// 12    10/06/99 7:25p Markd
// removed TIMESTAMP, time and fixed make_static bug
// 
// 11    10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION:
// Functions for doing model animation and attachments

#include "cg_local.h"

/*
===============
CG_EntityTargeted
===============
*/
#define  TARGET_GROUND_DISTANCE 32
void CG_EntityTargeted( int tikihandle, centity_t *cent, refEntity_t *model ) {
   vec3_t      end, sprite_org;
   trace_t     trace;
   qboolean    ground;
   float       radius;

   // send a trace down from the player to the ground
   VectorCopy( model->origin, end );
   end[2] -= TARGET_GROUND_DISTANCE;

   cgi.CM_BoxTrace( &trace, model->origin, end, NULL, NULL, 0, MASK_PLAYERSOLID, qfalse );

   // no shadow if too high
   if ( trace.fraction == 1.0 ) 
      {
      ground = qfalse;
      }
   else
      {
      if ( trace.contents & MASK_WATER )
         {
         ground = qfalse;
         }
      else
         {
         ground = qtrue;
         }
      }

   //
   // get the bounds of the current frame
   //
   if ( ground )
      {
      radius = cgi.R_ModelRadius( model->hModel ) * model->scale * 1.25f;
      }
   else
      {
      vec3_t mins, maxs;
      //vec3_t delta;

      if ( tikihandle >= 0 )
         {
         radius = cgi.R_ModelRadius( model->hModel ) * model->scale * 2.0f;
         VectorCopy( model->origin, sprite_org );
         sprite_org[ 2 ] += 0.5f * radius;
         }
      else
         {
         cgi.R_ModelBounds( model->hModel, mins, maxs );
         radius = ( maxs[ 2 ] - mins[ 2 ] ) * 0.5f;
         VectorAdd( mins, maxs, sprite_org );
         VectorMA( model->origin, 0.5f, sprite_org, sprite_org );
         }
      }


   if ( radius < 1 )
      {
      return;
      }

   if ( ground )
      {
      if ( cent->currentState.eFlags & EF_LEFT_TARGETED )
         {
         CG_ImpactMark( cgs.media.leftTargetShader, trace.endpos, trace.plane.normal, 
            ( cg.time * 120 / 1000 ) % 360, 1, 1, 1, 1, qfalse, radius, qtrue, -1, qfalse );
         }
      if ( cent->currentState.eFlags & EF_RIGHT_TARGETED )
         {
         CG_ImpactMark( cgs.media.rightTargetShader, trace.endpos, trace.plane.normal, 
            ( cg.time * 120 / 1000 ) % 360, 1, 1, 1, 1, qfalse, radius, qtrue, -1, qfalse );
         }
      }
   else
      {
      vec3_t angles;
      refEntity_t sprite;

      memset( &sprite, 0, sizeof( sprite ) );
      VectorCopy( sprite_org, sprite.origin);
      VectorCopy( sprite_org, sprite.oldorigin);
      VectorCopy( vec3_origin, angles );
      sprite.shaderRGBA[ 0 ] = 255;
      sprite.shaderRGBA[ 1 ] = 255;
      sprite.shaderRGBA[ 2 ] = 255;
      sprite.shaderRGBA[ 3 ] = 128;

      if ( cent->currentState.eFlags & EF_LEFT_TARGETED )
         {
         angles[ ROLL ] = ( cg.time * 120 / 1000 ) % 360;
         // convert angles to axis
         AnglesToAxis( angles, sprite.axis );

         sprite.hModel = cgs.media.leftTargetModel;
         sprite.scale = radius / cgi.R_ModelRadius( sprite.hModel );
         // add to refresh list
         cgi.R_AddRefSpriteToScene( &sprite );
         }
      if ( cent->currentState.eFlags & EF_RIGHT_TARGETED )
         {
         angles[ ROLL ] = ( cg.time * 120 / 1000 ) % 360;
         // convert angles to axis
         AnglesToAxis( angles, sprite.axis );

         sprite.hModel = cgs.media.rightTargetModel;
         sprite.scale = radius / cgi.R_ModelRadius( sprite.hModel );
         // add to refresh list
         cgi.R_AddRefSpriteToScene( &sprite );
         }
      }

   return;
}

/*
===============
CG_EntityShadow

Returns the Z component of the surface being shadowed

  should it return a full plane instead of a Z?
===============
*/
#define  SHADOW_DISTANCE      96
qboolean CG_EntityShadow( centity_t *cent, refEntity_t *model ) {
   vec3_t      end;
   trace_t     trace;
   float       alpha, radius;


   model->shadowPlane = 0;

   if ( cg_shadows->integer == 0 ) {
      return qfalse;
   }

   if ( model->renderfx & RF_SKYENTITY )
      {
      // no shadows on sky entities
      return qfalse;
      }

   // no shadows when invisible
//   if ( cent->currentState.powerups & ( 1 << PW_INVIS ) ) {
//      return qfalse;
//   }

   // send a trace down from the player to the ground
   VectorCopy( model->origin, end );
   end[2] -= SHADOW_DISTANCE;

   cgi.CM_BoxTrace( &trace, model->origin, end, NULL, NULL, 0, MASK_PLAYERSOLID, qfalse );

   // no shadow if too high
   if ( trace.fraction == 1.0 ) {
      return qfalse;
   }

   model->shadowPlane = trace.endpos[2] + 1;

   if ( ( cg_shadows->integer == 2 ) && ( model->renderfx & RF_SHADOW_PRECISE ) )
      {
      return qtrue;
      }

   //
   // get the bounds of the current frame
   //
   radius = model->scale * cgi.R_ModelRadius( model->hModel );

   if ( radius < 1 )
      {
      return qfalse;
      }

   // fade the shadow out with height
   alpha = ( 1.0 - trace.fraction ) * 0.8f;

   if ( ( cg_shadows->integer == 3 ) && ( model->renderfx & RF_SHADOW_PRECISE ) )
      {
      if ( model->shaderRGBA[ 3 ] == 255 )
         {
         model->shaderRGBA[ 3 ] = alpha * 255;
         }
      return qtrue;
      }

   // add the mark as a temporary, so it goes directly to the renderer
   // without taking a spot in the cg_marks array
   CG_ImpactMark( cgs.media.shadowMarkShader, trace.endpos, trace.plane.normal, 
      cent->lerpAngles[ YAW ], alpha,alpha,alpha,1, qfalse, radius, qtrue, -1, qfalse );

   return qtrue;
}

//
//
// NEW ANIMATION AND THREE PART MODEL SYSTEM
//
//

//=================
//CG_AnimationDebugMessage
//=================
void CG_AnimationDebugMessage
   (
   int            number,
   const char     *fmt, 
   ...
   )
   {
#ifndef NDEBUG
   if ( cg_debugAnim->integer ) 
      {
	   va_list		argptr;
	   char		msg[1024];

	   va_start (argptr,fmt);
	   vsprintf (msg,fmt,argptr);
	   va_end (argptr);

      if ( ( !cg_debugAnimWatch->integer ) || ( ( cg_debugAnimWatch->integer - 1 ) == number ) )
         {
         if ( cg_debugAnim->integer == 2 ) 
            {
 		      cgi.DebugPrintf( msg );
            }
         else
            {
 		      cgi.Printf( msg );
            }
         }
	   }
#endif
   }

/*
===============
CG_SetModelAnimation

may include ANIM_TOGGLEBIT
===============
*/
void CG_SetModelAnimation( int tikihandle, animstate_t * state, animstate_t * altstate, int newAnimation, int time, vec3_t origin, int entnum, qboolean timecheck ) 
   {
   int numframes;
   int flags;
   qboolean driven;

   numframes = cgi.Anim_NumFrames( tikihandle, newAnimation & ANIM_MASK );
   if ( !numframes )
      {
		cgi.DPrintf( "Can't find animation %i\n", newAnimation & ANIM_MASK );
      return;
      }
   flags = cgi.Anim_Flags( tikihandle, newAnimation & ANIM_MASK );
   if ( flags & MDL_ANIM_DELTA_DRIVEN )
      driven = qtrue;
   else
      driven = qfalse;

   state->time_per_frame = 1000.0f * cgi.Frame_Time( tikihandle, newAnimation & ANIM_MASK, 0 );
   if ( !state->time_per_frame )
      {
		cgi.DPrintf( "Animation %i has no time information\n", newAnimation & ANIM_MASK );
      return;
      }
   
#if 0
   // set the oldanim
   state->base.oldanim = state->base.anim;
   // set the oldframe
   state->base.oldframe = state->base.frame;
#else   
   // We are blending from the last state so set the oldanim and frame from it
   if ( state->base.anim & ANIM_BLEND )
      {
      // set the oldanim
      state->base.oldanim = state->base.anim;
      // set the oldframe
      state->base.oldframe = state->base.frame;
      }
   else // We are not blending, so get the oldanim and oldframe from the alternate state
      {
      // set the oldanim
      state->base.oldanim = altstate->base.oldanim;
      // set the oldframe
      state->base.oldframe = altstate->base.oldframe;
      }
#endif

   // if the anims are different and we aren't crossblending than crossblend from the previous animation
   if ( 
         ( ( newAnimation & ANIM_MASK ) != ( state->base.anim & ANIM_MASK ) ) &&
         ( ( ( time - state->crossblend.starttime ) >= state->crossblend_totaltime ) || !timecheck || ( flags & MDL_ANIM_NO_TIMECHECK ) )
      )
      {
      // if we didn't have an anim last state then use the alternate state for the crossblend
      if ( state->base.anim & ANIM_BLEND )
         {
         // copy the previous state over
         state->crossblend = state->base;
#if 0
         cgi.DPrintf( "Setting crossblend:%s\n", cgi.Anim_NameForNum( tikihandle, state->base.anim & ANIM_MASK ) );
#endif
         }
      else
         {
         // copy the previous state over from the alternate state
         state->crossblend = altstate->base;
#if 0
         cgi.DPrintf( "Setting crossblend (alt):%s\n", cgi.Anim_NameForNum( tikihandle, altstate->base.anim & ANIM_MASK ) );
#endif
         }
      // start crossblending from the nearest serverTime so it is synced with the other animations
      state->crossblend.starttime = time;
      // total time is determined by the animation
      state->crossblend_totaltime = cgi.Anim_CrossblendTime( tikihandle, newAnimation & ANIM_MASK );
      }

   // if we went from a non-driven to a driven or vice versa reset certain variables
   if ( driven != state->driven )
      {
      if ( driven )
         {
         // reset our position
         VectorCopy( origin, state->last_origin );
         // reset the last time we animated for driven animations
         state->last_driven_time = cg.time;
         // reset our current distance
         state->current_distance = 0;
         // reset our frame number so that we start at the beginning of the animation
         state->base.frame = 0;
         }
      else
         {
         // we don't want to process commands from the previous delta-driven animation any more, so we skip over them
         // by making it look like we are at the beginning of this animation
         state->last_cmd_frame = 0;
         }
      }
   // if we were driving last animatino, and our anim change, reset the frame number
   else if ( driven && ( newAnimation & ANIM_MASK ) != ( state->base.anim & ANIM_MASK ) )
      {
      state->base.frame = 0;
      }

   // special case for single frame animations
   // this makes sure that we replay any events on the first frame
   if ( ( state->numframes == numframes ) && ( numframes < 3 ) )
      state->last_cmd_frame = 0;

   state->driven = driven;

	state->base.anim = newAnimation;

	newAnimation &= ANIM_MASK;

   if ( state->driven )
      {
      cgi.Anim_Delta( tikihandle, newAnimation, state->frame_delta );
      VectorScale( state->frame_delta, 1.0f / ( float )numframes, state->frame_delta );
      state->frame_distance = VectorLength( state->frame_delta );
      VectorNormalize( state->frame_delta );
      if ( state->frame_distance < 0.1f )
         {
   		cgi.DPrintf( "Animation has no delta information, canceling delta.\n" );
         state->driven = qfalse;
         }
      }
   else
      {
      // reset our frame number so that we start at the beginning of the animation
      state->base.frame = 0;
      }

   state->has_commands = cgi.Anim_HasCommands( tikihandle, newAnimation );

   state->numframes = numframes;

	state->base.starttime = time;

   assert( cg.time >= time );

   state->next_evaluate_time = time + state->time_per_frame;

#ifndef NDEBUG
   if ( state->driven )
      {
      CG_AnimationDebugMessage( entnum, "cg.time: %d Entity: %3d Anim: %s(#%i) (%i) driven\n", 
         cg.time, entnum, cgi.Anim_NameForNum( tikihandle, newAnimation ), newAnimation, state->base.starttime );
      }
   else
      {
      CG_AnimationDebugMessage( entnum, "cg.time: %d Entity: %3d Anim: %s(#%i) (%i) not-driven\n", 
         cg.time, entnum, cgi.Anim_NameForNum( tikihandle, newAnimation ), newAnimation, state->base.starttime );
      }
#endif
   }

/*
===============
CG_RunModelAnimation
===============
*/
void CG_RunModelAnimation
   ( 
   int tikihandle, 
   animstate_t * state, 
   animstate_t * altstate, 
   int newAnimation, 
   int animtime, 
   vec3_t origin, 
   vec3_t or[ 3 ],
   centity_t * cent,
   qboolean timecheck
   ) 
   {
	int	f;
   int   timedelta;

   // must not be a tiki model
   if ( tikihandle < 0 )
      return;

	// debugging tool to get no animations
	if ( cg_animSpeed->value == 0 ) 
      {
      state->base.oldframe = state->base.frame = state->base.framelerp = 0;
		return;
   	}

	// see if the animation sequence is switching
	if ( newAnimation != state->base.anim ) 
      {
		CG_SetModelAnimation( tikihandle, state, altstate, newAnimation, animtime, origin, cent->currentState.number, timecheck );
	   }

	// This is here to bullet proof this proc (prevents possible divide by 0 errors farther down)

	if ( !state->time_per_frame )
		return;

   if ( state->driven )
      {
      vec3_t tmp;
      vec3_t delta;
      float dot;
      float delta_length;

      // calculate distance since last time and time elapsed
      VectorSubtract( origin, state->last_origin, tmp );
      VectorCopy( origin, state->last_origin );
      timedelta = cg.time - state->last_driven_time;
      state->last_driven_time = cg.time;

      // transform the delta into our local coordinate system
	   delta[ 0 ] = DotProduct( tmp, or[ 0 ] );
	   delta[ 1 ] = DotProduct( tmp, or[ 1 ] );
	   delta[ 2 ] = DotProduct( tmp, or[ 2 ] );

      delta_length = VectorNormalize( delta );
      dot = DotProduct( state->frame_delta, delta );
      delta_length *= dot;

      // add our distance along the direction of movement to our current distance
      state->current_distance += delta_length;
      // if we passed the distance for one frame in the forward direction, switch frames
      while ( state->current_distance > state->frame_distance )
         {
         state->base.oldanim = state->base.anim & ANIM_MASK;
         state->base.oldframe = state->base.frame;
		   state->base.frame++;
         state->current_distance -= state->frame_distance;
		   if ( state->base.frame >= state->numframes )
            state->base.frame -= state->numframes;
         }
      // if we passed the distance for one frame in the backwards direction, switch frames
      while ( state->current_distance < -state->frame_distance )
         {
         state->base.oldanim = state->base.anim & ANIM_MASK;
         state->base.oldframe = state->base.frame;
		   state->base.frame--;
         state->current_distance += state->frame_distance;
		   if ( state->base.frame < 0 )
            state->base.frame += state->numframes;
         }
      // calculate the lerp for this frame
      if ( state->current_distance >= 0 )
         {
		   state->base.framelerp = ( ( state->frame_distance - state->current_distance ) / state->frame_distance );
         }
      else
         {
		   state->base.framelerp = ( ( state->current_distance + state->frame_distance ) / state->frame_distance );
         }
      }
   else
      {
      if ( cg.time >= state->next_evaluate_time )
         {
         state->next_evaluate_time += state->time_per_frame;

         // calculate the current frame based on the starttime of the animation
         timedelta = cg.time - state->base.starttime;
         f = timedelta / state->time_per_frame;

         // make sure frame is not negative
         if ( f < 0 )
            {
            f = 0;
            }

         // don't let frame wrap around numframes
		   if ( f >= state->numframes ) 
            {
   		   f = state->numframes - 1;
   		   }

#ifndef NDEBUG
         CG_AnimationDebugMessage( cent->currentState.number, "cg.time: %d Entity: %3d anim %s frame %d\n", 
            cg.time, cent->currentState.number, cgi.Anim_NameForNum( tikihandle, state->base.anim & ANIM_MASK ), f );
#endif
		   state->base.oldframe = state->base.frame;
         state->base.oldanim = state->base.anim & ANIM_MASK;

         state->base.frame = f;
         }

      state->base.framelerp = 1.0f - ( float )( cg.time - state->base.starttime - ( state->base.frame * state->time_per_frame ) ) / ( float )state->time_per_frame;

      if ( state->base.framelerp < 0 )
         {
         state->base.framelerp = 0;
         }
      }

   if ( state->crossblend_totaltime )
      {
      state->crossblend_lerp = ( float )( cg.time - state->crossblend.starttime ) / ( float )state->crossblend_totaltime;
      if ( state->crossblend_lerp < 0 )
         {
         state->crossblend_lerp = 0;
         }
      if ( state->crossblend_lerp > 1.0f )
         {
         // < 0 means no crossfade
         state->crossblend_lerp = -1.0f;
         }
      }
   else
      {
      // < 0 means no crossfade
      state->crossblend_lerp = -1.0f;
      }
   }


/*
===============
CG_ClearModelAnimation
===============
*/
void CG_ClearModelAnimation( int tikihandle, animstate_t * state, int animationNumber, int time, vec3_t origin, int entnum ) 
   {
   memset( &state->base, 0, sizeof( state->base ) );
   if ( tikihandle >= 0 )
      {
	   CG_SetModelAnimation( tikihandle, state, state, animationNumber, time, origin, entnum, qtrue );
      //
      // we set this hear to prevent unwanted crossfading when we first start
      //
      // set the oldanim
      state->base.oldanim = state->base.anim;
      // set the oldframe
      state->base.oldframe = state->base.frame;
      }

   memset( &state->crossblend, 0, sizeof( state->crossblend ) );
   state->crossblend.starttime   = time;
   state->crossblend_totaltime   = 0;
   state->crossblend_lerp        = -1.0f;

   state->last_cmd_anim = state->last_cmd_frame = state->last_cmd_time = 0;
   }

/*
======================
CG_AttachEntity

Modifies the entities position and axis by the given
tag location
======================
*/
void CG_AttachEntity( refEntity_t *entity, refEntity_t *parent, int tikihandle, int tagnum, qboolean use_angles, vec3_t attach_offset )
   {
	int				i;
   orientation_t  or;
	vec3_t			tempAxis[3];

	// lerp the tag
   if ( r_lerpmodels->integer )
      {
      or = cgi.Tag_LerpedOrientation( tikihandle, parent, tagnum );
      }
   else
      {
      //FIXME
      // doesn't handle torso animations
      or = cgi.Tag_Orientation
         ( 
         tikihandle, 
         parent->anim, 
         parent->frame, 
         tagnum,
         parent->scale,
         parent->bone_tag,
         parent->bone_quat
         );
      }
   //cgi.Printf( "th = %d %.2f %.2f %.2f\n", tikihandle, or.origin[ 0 ], or.origin[ 1 ], or.origin[ 2 ] );

	VectorCopy( parent->origin, entity->origin );

	for ( i = 0 ; i < 3 ; i++ ) 
      {
		VectorMA( entity->origin, or.origin[i], parent->axis[i], entity->origin );
	   }

   VectorCopy( entity->origin, entity->oldorigin );

	VectorAdd( entity->origin, attach_offset, entity->origin );

	if ( use_angles )
		{
		MatrixMultiply( entity->axis, parent->axis, tempAxis );
		MatrixMultiply( or.axis, tempAxis, entity->axis );
		}

   entity->scale *= parent->scale;
   entity->renderfx |= ( parent->renderfx & ~( RF_FLAGS_NOT_INHERITED | RF_LIGHTING_ORIGIN ) );
   entity->shadowPlane = parent->shadowPlane;
   VectorCopy( parent->lightingOrigin, entity->lightingOrigin );
   }

void CG_ModelAnim
   (
   centity_t *cent
   )
   
   {
	entityState_t	*s1;
   refEntity_t    model;
   int            thandle;
   int            i;
   qboolean       dolegs;
   qboolean       dotorso;
   
 	memset( &model, 0, sizeof(model) );
	
	s1 = &cent->currentState;

	// add loop sound only if it is not attached
	if ( s1->loopSound && ( s1->parent == ENTITYNUM_NONE ) )
      {
		cgi.S_AddLoopingSound( cent->lerpOrigin, vec3_origin, cgs.sound_precache[s1->loopSound], s1->loopSoundVolume, s1->loopSoundMinDist );
	   }
	if ( cent->tikiLoopSound && ( s1->parent == ENTITYNUM_NONE ) )
		cgi.S_AddLoopingSound( cent->lerpOrigin, vec3_origin, cent->tikiLoopSound, cent->tikiLoopSoundVolume, cent->tikiLoopSoundMinDist );

	// if set to invisible, skip
	if ( !s1->modelindex )
      {
		return;
	   }

	// take the results of CL_InterpolateEntities
	VectorCopy( cent->lerpOrigin, model.origin);
	VectorCopy( cent->lerpOrigin, model.oldorigin);

	// convert angles to axis
	AnglesToAxis( cent->lerpAngles, model.axis );

   // set the entity number
   model.entityNumber = s1->number;

   // copy shader specific data
   model.shader_data[ 0 ] = s1->tag_num;
   model.shader_data[ 1 ] = s1->skinNum;

   // set and lerp the bone controllers
   model.useAngles = qfalse;
   for( i = 0; i < NUM_BONE_CONTROLLERS; i++ )
      {
      model.bone_tag[ i ] = s1->bone_tag[ i ];
      if ( model.bone_tag[ i ] >= 0 )
         {
         model.useAngles = qtrue;
         if ( ( cent->interpolate ) && ( cent->nextState.bone_tag[ i ] == cent->currentState.bone_tag[ i ] ) )
            {
            SlerpQuaternion( cent->currentState.bone_quat[ i ], cent->nextState.bone_quat[ i ], 
               cg.frameInterpolation, model.bone_quat[ i ] );
            }
         else
            {
            model.bone_quat[ i ][ 0 ] = s1->bone_quat[ i ][ 0 ];
            model.bone_quat[ i ][ 1 ] = s1->bone_quat[ i ][ 1 ];
            model.bone_quat[ i ][ 2 ] = s1->bone_quat[ i ][ 2 ];
            model.bone_quat[ i ][ 3 ] = s1->bone_quat[ i ][ 3 ];
            }
         }
      }

   // Interpolated state variables
   if ( cent->interpolate )
      {
      model.scale = s1->scale + cg.frameInterpolation * ( cent->nextState.scale - s1->scale );
      }
   else
      {
      model.scale = s1->scale;
      }

#if 0
   if ( s1->parent != ENTITYNUM_NONE )
      {
      refEntity_t *parent;
      int         tikihandle;

      parent = cgi.R_GetRenderEntity( s1->parent );

      if ( !parent )
         {
         cgi.DPrintf( "CG_ModelAnim: Could not find parent entity\n" );
         return;
         }

      tikihandle = cgi.TIKI_GetHandle( parent->hModel );
      CG_AttachEntity( &model, parent, tikihandle, s1->tag_num & TAG_MASK, s1->attach_use_angles, s1->attach_offset );

	   if ( s1->loopSound )
         {
		   cgi.S_AddLoopingSound( model.origin, vec3_origin, cgs.sound_precache[s1->loopSound], s1->loopSoundVolume, s1->loopSoundMinDist );
	      }
		if ( cent->tikiLoopSound )
			cgi.S_AddLoopingSound( cent->lerpOrigin, vec3_origin, cent->tikiLoopSound, cent->tikiLoopSoundVolume, cent->tikiLoopSoundMinDist );
      }
#endif

	//
	// add the model
	//
   thandle = cgs.model_tiki[ s1->modelindex ]; 

   dolegs   = ( s1->anim & ANIM_BLEND );
   dotorso  = ( s1->torso_anim & ANIM_BLEND );

   if ( !dolegs && !dotorso )
      {
      // always do a leg anim if we don't have a torso
      dolegs = qtrue;
      }
   
   if ( dolegs )
      {
      model.uselegs = qtrue;

      if ( ( thandle == -1 ) || ( s1->frame & FRAME_EXPLICIT ) )
         {
         // explicit frame
         model.anim = model.oldanim = s1->anim & ANIM_MASK;
         model.frame = model.oldframe = s1->frame & FRAME_MASK;
         model.backlerp = 0;

         // < 0 means no crossfade
         model.crossblend_lerp = -1.0f;

         }
      else
         {
         // run the animation
	      CG_RunModelAnimation
            ( 
            thandle,
            &cent->am, 
            &cent->torso_am,
            s1->anim, 
            cg.snap->serverTime,
            cent->lerpOrigin, 
            model.axis,
            cent,
            qtrue
            );

         model.anim = cent->am.base.anim & ANIM_MASK;
         model.frame = cent->am.base.frame;

         model.oldanim = cent->am.base.oldanim & ANIM_MASK;
         model.oldframe = cent->am.base.oldframe;
         model.backlerp = cent->am.base.framelerp;

         model.crossblend_anim      = cent->am.crossblend.anim & ANIM_MASK;
         model.crossblend_frame     = cent->am.crossblend.frame;
         model.crossblend_oldframe  = cent->am.crossblend.oldframe;
         model.crossblend_backlerp  = cent->am.crossblend.framelerp;
         model.crossblend_lerp      = cent->am.crossblend_lerp;

#if 0
         cgi.DPrintf( "Crossblending to Legs Anim: %s from %s\n", cgi.Anim_NameForNum( thandle, model.anim ),
                                                                   cgi.Anim_NameForNum( thandle, model.crossblend_anim )
                                                                 );
#endif

         }
      }

   //
	// add the torso animation
	//
   if ( dotorso )
      {     
      int flags = cgi.Anim_Flags( thandle, cent->torso_am.base.anim & ANIM_MASK );
      
      model.usetorso = qtrue;

      // if we're just switching to a torso animation and we don't have a crossblend going,
      // set the crossblend to be from the base animation
      if ( 
          !( cent->torso_am.base.anim & ANIM_BLEND ) && 
          ( ( ( cg.time - cent->torso_am.crossblend.starttime ) >= cent->torso_am.crossblend_totaltime ) || ( flags & MDL_ANIM_NO_TIMECHECK ) )
         )
         {
         cent->torso_am.crossblend             = cent->am.crossblend;
         }

      // if we have a torso anim, we explicitly set the current anim and let CG_RunModelAnimation handle crossblending
      if ( ( thandle == -1 ) || s1->torso_frame & FRAME_EXPLICIT )
         {
         // explicit frame
         model.torso_anim     = model.torso_oldanim = s1->torso_anim & ANIM_MASK;
         model.torso_frame    = model.torso_oldframe = s1->torso_frame & FRAME_MASK;
         model.torso_backlerp = 0;

         // < 0 means no crossfade
         model.torso_crossblend_lerp = -1.0f;
         }
      else
         {
         // run the animation
         CG_RunModelAnimation
            ( 
            thandle,
            &cent->torso_am,
            &cent->am,
            s1->torso_anim, 
            cg.snap->serverTime,
            cent->lerpOrigin, 
            model.axis,
            cent,
            qfalse
            );

         model.torso_anim                 = cent->torso_am.base.anim & ANIM_MASK;
         model.torso_frame                = cent->torso_am.base.frame;
         model.torso_oldanim              = cent->torso_am.base.oldanim & ANIM_MASK;
         model.torso_oldframe             = cent->torso_am.base.oldframe;
         model.torso_backlerp             = cent->torso_am.base.framelerp;

         model.torso_crossblend_anim      = cent->torso_am.crossblend.anim & ANIM_MASK;
         model.torso_crossblend_frame     = cent->torso_am.crossblend.frame;
         model.torso_crossblend_oldframe  = cent->torso_am.crossblend.oldframe;
         model.torso_crossblend_backlerp  = cent->torso_am.crossblend.framelerp;
         model.torso_crossblend_lerp      = cent->torso_am.crossblend_lerp;
         }

#if 0 
      cgi.DPrintf( "Animating Torso: %s from %s\n", cgi.Anim_NameForNum( thandle, model.torso_anim ),
                                                    cgi.Anim_NameForNum( thandle, model.torso_crossblend_anim )
                                                   );
#endif

      }
   else
      {
      // we don't have a torso anim, so crossblend from whatever the torso is currently doing
#if 1 
      if ( 
           ( cent->torso_am.base.anim & ANIM_BLEND ) // This is a hack for the torso, don't do any crossblend time checking
         )
#else
      if ( 
           ( cent->torso_am.base.anim & ANIM_BLEND ) && 
           ( ( cg.time - cent->torso_am.crossblend.starttime ) >= cent->torso_am.crossblend_totaltime ) 
         )
#endif
         {
         CG_AnimationDebugMessage( cent->currentState.number, "TORSO_AM_BASE: %s\n", cgi.Anim_NameForNum( thandle, cent->torso_am.base.anim & ANIM_MASK ) );
         
#if 0
         cgi.DPrintf( "TORSO_AM_BASE: %s\n", cgi.Anim_NameForNum( thandle, cent->torso_am.base.anim & ANIM_MASK ) );
#endif

         // only crossblend when the previous torso anim has it's flag set.
         // set the crossblend information directly from the current animation
         cent->torso_am.crossblend             = cent->torso_am.base;
         cent->torso_am.crossblend.starttime   = cg.snap->serverTime;
         cent->torso_am.crossblend_totaltime   = cgi.Anim_CrossblendTime( thandle, cent->torso_am.crossblend.anim & ANIM_MASK );

         // clear out the torso flag so that we only copy this when the torso animation goes away and there's no crossblending
         cent->torso_am.base.anim &= ~ANIM_BLEND;
         }
      
      // only set the torso information if we're crossblending from an anim
      if ( ( cg.time - cent->torso_am.crossblend.starttime ) <= cent->torso_am.crossblend_totaltime )
         {
         if ( cent->torso_am.crossblend_totaltime )
            {
            cent->torso_am.crossblend_lerp = ( float )( cg.time - cent->torso_am.crossblend.starttime ) / 
               ( float )cent->torso_am.crossblend_totaltime;
            if ( cent->torso_am.crossblend_lerp < 0 )
               {
               cent->torso_am.crossblend_lerp = 0;
               }
            if ( cent->torso_am.crossblend_lerp > 1.0f )
               {
               // < 0 means no crossfade
               cent->torso_am.crossblend_lerp = -1.0f;
               }
            }
         else
            {
            // < 0 means no crossfade
            cent->torso_am.crossblend_lerp = -1.0f;
            }

         model.usetorso = qtrue;

         model.torso_crossblend_anim      = cent->torso_am.crossblend.anim & ANIM_MASK;
         model.torso_crossblend_frame     = cent->torso_am.crossblend.frame;
         model.torso_crossblend_oldframe  = cent->torso_am.crossblend.oldframe;
         model.torso_crossblend_backlerp  = cent->torso_am.crossblend.framelerp;
         model.torso_crossblend_lerp      = cent->torso_am.crossblend_lerp;

         // this isn't set if we don't have a leg anim
         if ( s1->anim & ANIM_BLEND )
            {
            model.torso_anim     = model.anim;
            model.torso_frame    = model.frame;
            model.torso_oldanim  = model.oldanim;
            model.torso_oldframe = model.oldframe;
            model.torso_backlerp = model.backlerp;
            }
         else
            {
            // put in some valid frame info
            model.torso_anim     = model.torso_crossblend_anim;
            model.torso_frame    = model.torso_crossblend_frame;
            model.torso_oldanim  = model.torso_crossblend_anim;
            model.torso_oldframe = model.torso_crossblend_oldframe;
            model.torso_backlerp = model.torso_crossblend_backlerp;
            }
#if 0
         cgi.DPrintf( "Crossblending to Torso Anim: %s from %s\n", cgi.Anim_NameForNum( thandle, model.torso_anim ),
                                                                   cgi.Anim_NameForNum( thandle, model.torso_crossblend_anim )
                                                                 );
#endif
         }
      }

   // if we don't have a leg anim
   if ( !dolegs )
      {
      // we don't have a leg anim, so crossblend from whatever the leg is currently doing
      if ( 
           ( cent->am.base.anim & ANIM_BLEND )  && 
           ( ( cg.time - cent->am.crossblend.starttime ) >= cent->am.crossblend_totaltime ) 
         )
         {
         // only crossblend when the previous leg anim has it's flag set.
         // set the crossblend information directly from the current animation
         cent->am.crossblend             = cent->am.base;
         cent->am.crossblend.starttime   = cg.snap->serverTime;
         cent->am.crossblend_totaltime   = cgi.Anim_CrossblendTime( thandle, cent->am.crossblend.anim & ANIM_MASK );

         // clear out the leg flag so that we only copy this when the leg animation goes away and there's no crossblending
         cent->am.base.anim &= ~ANIM_BLEND;
         }

      // only set the leg information if we're crossblending from an anim
      if ( ( cg.time - cent->am.crossblend.starttime ) <= cent->am.crossblend_totaltime )
         {
         if ( cent->am.crossblend_totaltime )
            {
            cent->am.crossblend_lerp = ( float )( cg.time - cent->am.crossblend.starttime ) / 
               ( float )cent->am.crossblend_totaltime;
            if ( cent->am.crossblend_lerp < 0 )
               {
               cent->am.crossblend_lerp = 0;
               }
            if ( cent->am.crossblend_lerp > 1.0f )
               {
               // < 0 means no crossfade
               cent->am.crossblend_lerp = -1.0f;
               }
            }
         else
            {
            // < 0 means no crossfade
            cent->am.crossblend_lerp = -1.0f;
            }

         model.uselegs = qtrue;

         model.crossblend_anim      = cent->am.crossblend.anim & ANIM_MASK;
         model.crossblend_frame     = cent->am.crossblend.frame;
         model.crossblend_oldframe  = cent->am.crossblend.oldframe;
         model.crossblend_backlerp  = cent->am.crossblend.framelerp;
         model.crossblend_lerp      = cent->am.crossblend_lerp;

         model.anim     = model.torso_anim;
         model.frame    = model.torso_frame;
         model.oldanim  = model.torso_oldanim;
         model.oldframe = model.torso_oldframe;
         model.backlerp = model.torso_backlerp;
         }
      }

   if ( s1->parent != ENTITYNUM_NONE )
      {
      refEntity_t *parent;
      int         tikihandle;

      parent = cgi.R_GetRenderEntity( s1->parent );

      if ( !parent )
         {
         cgi.DPrintf( "CG_ModelAnim: Could not find parent entity\n" );
         return;
         }

      tikihandle = cgi.TIKI_GetHandle( parent->hModel );
      CG_AttachEntity( &model, parent, tikihandle, s1->tag_num & TAG_MASK, s1->attach_use_angles, s1->attach_offset );

	   if ( s1->loopSound )
         {
		   cgi.S_AddLoopingSound( model.origin, vec3_origin, cgs.sound_precache[s1->loopSound], s1->loopSoundVolume, s1->loopSoundMinDist );
	      }
		if ( cent->tikiLoopSound )
			cgi.S_AddLoopingSound( model.origin, vec3_origin, cent->tikiLoopSound, cent->tikiLoopSoundVolume, cent->tikiLoopSoundMinDist );
      }

   // set skin
	model.skinNum = s1->skinNum;
   model.renderfx |= s1->renderfx;
	model.customSkin = 0;
	model.hModel = cgs.model_draw[s1->modelindex];

   for( i=0; i<3; i++ )
      {
      model.shaderRGBA[i] = cent->color[i] * 255;
      }
   model.shaderRGBA[3] = s1->alpha * 255;

   // set surfaces
   memcpy( model.surfaces, s1->surfaces, MAX_MODEL_SURFACES );

	// get the player model information
	if ( 
      !( s1->renderfx & RF_DONTDRAW )    && 
       ( model.renderfx & RF_SHADOW )    && 
      !( model.renderfx & RF_DEPTHHACK ) && 
		!( ( s1->number == cg.snap->ps.clientNum ) && ( !cg_3rd_person->integer ) ) 
      )
	   {
      qboolean shadow;

      // add the shadow
      shadow = CG_EntityShadow( cent, &model );
      if ( 
            shadow && 
            ( cg_shadows->integer == 3 ) && 
            ( model.renderfx & RF_SHADOW_PRECISE ) 
         )
         {
         model.renderfx |= RF_SHADOW_PLANE;
         }
	   }

   if ( s1->eFlags & ( EF_LEFT_TARGETED | EF_RIGHT_TARGETED ) )
      {
      CG_EntityTargeted( thandle, cent, &model );
      }

   if ( s1->number == cg.snap->ps.clientNum )
      {
      if (!cg_3rd_person->integer)
			model.renderfx |= RF_THIRD_PERSON;			// In 1st person, only draw self in mirrors
      }

   if ( model.renderfx & RF_SKYORIGIN )
      {
      memcpy( cg.sky_axis, model.axis, sizeof( cg.sky_axis ) );
      VectorCopy( model.origin, cg.sky_origin );
      }

   if ( s1->eFlags & EF_ANTISBJUICE )
      {
   	model.customShader = cgi.R_RegisterShader( "antisuckshader" ); 
      model.renderfx |= RF_CUSTOMSHADERPASS;
      }

   if ( !( s1->renderfx & RF_DONTDRAW ) )
      {
      // add to refresh list
	   cgi.R_AddRefEntityToScene( &model );
      }

   // Run any client frame commands
   if ( thandle != -1 )
      {
      // update any emitter's...
      CG_UpdateEntity( thandle, &model, cent );

      CG_ClientCommands
         ( 
         thandle,
         model.frame, 
         model.anim, 
         &cent->am, 
         &model, 
         cent
         );

      if ( s1->torso_anim & ANIM_BLEND )
         {
         // Run any client frame commands
         CG_ClientCommands
            ( 
            thandle,
            model.torso_frame, 
            model.torso_anim,
            &cent->torso_am, 
            &model, 
            cent
            );
         }
      }
   }
