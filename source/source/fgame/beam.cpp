//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/beam.cpp                           $
// $Revision:: 39                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/23/00 8:41p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/beam.cpp                                $
// 
// 39    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 38    6/23/00 11:49a Markd
// fixed various imagindexes and saved games
// 
// 37    5/30/00 2:47p Aldie
// Fix for beam parent
// 
// 36    5/30/00 10:59a Aldie
// Added Circle of Protection Powerup
// 
// 35    5/24/00 6:05p Markd
// Fixed bug where MAX_MAP_BOUNDS was being used instead of MAP_SIZE
// 
// 34    5/01/00 4:19p Steven
// Added some caching stuff to beams.
// 
// 33    3/30/00 6:23p Steven
// Fixed life not getting set properly.
// 
// 32    3/28/00 5:00p Aldie
// Fix beam parameter
// 
// 31    3/28/00 4:25p Aldie
// Some more beam changes for Pat
// 
// 30    3/28/00 3:16p Aldie
// Fixed some beam problems for Pat
// 
// 29    3/14/00 3:38p Aldie
// Added persist command
// 
// 28    2/14/00 7:34p Aldie
// Fixed some beam rendering issues
// 
// 27    2/03/00 7:01p Jimdose
// made all hardcoded map bounds use MAX_MAP_BOUNDS
// 
// 26    1/31/00 4:35p Steven
// Fixed a bug in CreateBeam.
// 
// 25    1/26/00 5:07p Aldie
// Fixed beamdamage
// 
// 24    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 23    1/21/00 8:01p Aldie
// Fixed a warning
// 
// 22    1/21/00 5:38p Aldie
// Fix more beam bugs
// 
// 21    1/21/00 2:10p Aldie
// Fixed beam endpoint tracking
// 
// 20    1/20/00 5:26p Aldie
// Clarified some of the spawnargs
// 
// 19    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 18    1/14/00 5:06p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 17    1/11/00 6:41p Markd
// Removed fulltrace code from the game
// 
// 16    1/07/00 8:12p Jimdose
// cleaning up unused code
// 
// 15    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 14    11/19/99 11:29a Steven
// Added ability to specify the end point of a beam.
// 
// 13    10/25/99 6:45p Aldie
// Add noise spawnflag
// 
// 12    10/25/99 3:46p Aldie
// Fixed beam spawnflag
// 
// 11    10/25/99 3:21p Aldie
// Fixed activate and deactivate
// 
// 10    10/22/99 4:28p Aldie
// added some defaults
// 
// 9     10/22/99 12:17p Aldie
// fixed defaults
// 
// 8     10/21/99 6:19p Markd
// removed torso and head members from entity_state
// 
// 7     10/21/99 2:51p Aldie
// Added some more beam functions
// 
// 6     10/19/99 4:30p Aldie
// Added wave effect
// 
// 5     10/19/99 11:57a Aldie
// Added some more beam features
// 
// 4     10/18/99 4:00p Aldie
// Fix for beam endpoints
// 
// 3     10/18/99 3:58p Aldie
// Fix for beam endpoints
// 
// 2     10/18/99 1:59p Aldie
// Lots of fixes for beams and stuff
//
// DESCRIPTION:
// 

#include "beam.h"
#include "../qcommon/qfiles.h"

/*****************************************************************************/
/*QUAKED func_beam (0 0.25 .5) (-8 -8 -8) (8 8 8) START_ON PERSIST WAVE NOISE

This creates a beam effect from the origin to the target's origin. If no
target is specified, uses angles and projects beam out from there.

"model" Specifies the model to use as the beam
"overlap" Specifies the amount of overlap each beam link should have. Use this to fill
in the cracks when using electric on beams. (Default is 0)
"minoffset" Minimum amount of electrical variation (Default is 0)
"maxoffset" Maximum amount of electrical variation (Default is 5)
"color" Vector specifiying the red,green, and blue components. (Default is "1 1 1")
"alpha" Alpha of the beam (Default is 1.0)
"damage" Amount of damage the beam inflicts if beam hits someone (Default is 0)
"angles" Sets the angle of the beam if no target is specified.
"life" Sets the life of the beam for use with the persist spawnflag.  This is how long a beam will
be displayed.
"numsegments" Number of segments in a beam (Default is 4)
"delay" Delay between beam updates.  (i.e. slows the effect of the beam down)
"shader" Set the shader of the beam
"scale" Set the width of the beam

START_ON  - Starts the beam on
PERSIST   - Keeps the last few beams around and fades them out over the life of the beam
WAVE      - Make the beam follow a sin wave pattern
NOISE     - Use a more computationally expensive random effect, but the results are smoother

If the model field is not set, then a renderer generated beam will be created
using the color, minoffset, maxoffset, scale, and subdivisions fields

If the targetname is set, it will use the target specified as the endpoint of the beam

/*****************************************************************************/

Event EV_FuncBeam_Activate
   ( 
   "activate",
   EV_DEFAULT,
   NULL,
   NULL,
   "Activate the beam"
   );
Event EV_FuncBeam_Deactivate
   (
   "deactivate",
   EV_DEFAULT,
   NULL,
   NULL,
   "Deactivate the beam"
   );
Event EV_FuncBeam_Diameter
   (
   "diameter",
   EV_DEFAULT,
   "f",
   "diameter",
   "Set the diameter of the beam"
   );
Event EV_FuncBeam_Maxoffset
   (
   "maxoffset",
   EV_DEFAULT,
   "f",
   "max_offset",
   "Set the maximum offset the beam can travel above, below, forward or back of it's endpoints"
   );
Event EV_FuncBeam_Minoffset
   (
   "minoffset",
   EV_DEFAULT,
   "f",
   "min_offset",
   "Set the minimun offset the beam can travel above, below, forward or back of it's endpoints"
   );
Event EV_FuncBeam_Overlap
   (
   "overlap",
   EV_DEFAULT,
   "f",
   "beam_overlap",
   "Set the amount of overlap the beams have when they are being strung together"
   );
Event EV_FuncBeam_Color
   (
   "color",
   EV_DEFAULT,
   "v[0,1][0,1][0,1]",
   "beam_color",
   "Set the color of the beam"
   );
Event EV_FuncBeam_SetTarget
   (
   "target",
   EV_DEFAULT,
   "s",
   "beam_target",
   "Set the target of the beam. The beam will be drawn from the origin\n"
	"to the origin of the target entity"
   );
Event EV_FuncBeam_SetEndPoint
   (
   "endpoint",
   EV_DEFAULT,
   "v",
   "beam_end_point",
   "Set the end point of the beam. The beam will be draw from the origin to\n"
	"the end point."
   );
Event EV_FuncBeam_SetLife
   (
   "life",
   EV_DEFAULT,
   "f",
   "beam_life",
   "Set the amount of time the beam stays on when activated"
   );
Event EV_FuncBeam_Shader
   (
   "shader",
   EV_DEFAULT,
   "s",
   "beam_shader",
   "Set the shader that the beam will use"
   );
Event EV_FuncBeam_TileShader
   (
   "tileshader",
   EV_DEFAULT,
   "s",
   "beam_shader",
   "Set the shader that the beam will use.  This shader will be tiled."
   );
Event EV_FuncBeam_Segments
   (
   "numsegments",
   EV_DEFAULT,
   "i",
   "numsegments",
   "Set the number of segments for the beam"
   );
Event EV_FuncBeam_Delay
   (
   "delay",
   EV_DEFAULT,
   "f",
   "delay",
   "Set the amount of delay on the beam updater"
   );
Event EV_FuncBeam_NumSphereBeams
   (
   "numspherebeams",
   EV_DEFAULT,
   "i",
   "num",
   "Set the number of beams that will be shot out in a sphere like formation"
   );
Event EV_FuncBeam_SphereRadius
   (
   "radius",
   EV_DEFAULT,
   "f",
   "radius",
   "Set the starting radius of the beams if this is a beamsphere"
   );
Event EV_FuncBeam_ToggleDelay
   (
   "toggledelay",
   EV_DEFAULT,
   "SF",
   "[random] time",
   "Causes a beam toggling effect.  Sets the time between toggling.  If random is specified, The time will be between 0 and time"
   );
Event EV_FuncBeam_FindEndpoint
   (
   "findendpoint",
   EV_DEFAULT,
   NULL,
   NULL,
   "Find the endpoint of a beam"
   );
Event EV_FuncBeam_UpdateEndpoint
   (
   "updateendpoint",
   EV_DEFAULT,
   NULL,
   NULL,
   "Update the endpoint of a beam"
   );
Event EV_FuncBeam_UpdateOrigin
   (
   "updateorigin",
   EV_DEFAULT,
   NULL,
   NULL,
   "Update the origin of a beam"
   );
Event EV_FuncBeam_EndAlpha
   (
   "endalpha",
   EV_DEFAULT,
   "f",
   "alpha",
   "Set the endpoint alpha value of the beam"
   );
Event EV_FuncBeam_Shoot
   (
   "shoot",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the beam cause damage to entities that get in the way"
   );
Event EV_FuncBeam_ShootRadius
   (
   "shootradius",
   EV_DEFAULT,
   "f",
   "radius",
   "Set the radius of the damage area between beam endpoints"
   );
Event EV_FuncBeam_Persist
   (
   "persist",
   EV_DEFAULT,
   "b",
   "bool",
   "Set the persist property of the beam"
   );

CLASS_DECLARATION( ScriptSlave, FuncBeam, "func_beam" )
	{
      { &EV_Activate,                  Activate },
      { &EV_FuncBeam_Activate,         Activate },
      { &EV_FuncBeam_Deactivate,       Deactivate },
      { &EV_FuncBeam_Maxoffset,        SetMaxoffset },
      { &EV_FuncBeam_Minoffset,        SetMinoffset },
      { &EV_FuncBeam_Overlap,          SetOverlap },
      { &EV_FuncBeam_Color,            SetColor },
      { &EV_FuncBeam_SetTarget,        SetTarget },
      { &EV_SetAngle,                  SetAngle },
      { &EV_FuncBeam_Segments,         SetSegments },
      { &EV_SetAngles,                 SetAngles },
		{ &EV_FuncBeam_SetEndPoint,      SetEndPoint },
      { &EV_Model,                     SetModel },
      { &EV_Damage,                    SetDamage },
      { &EV_FuncBeam_SetLife,          SetLife },
      { &EV_FuncBeam_Shader,           SetBeamShader },
      { &EV_FuncBeam_TileShader,       SetBeamTileShader },
      { &EV_FuncBeam_Delay,            SetDelay },
      { &EV_FuncBeam_NumSphereBeams,   SetNumSphereBeams },
      { &EV_FuncBeam_SphereRadius,     SetSphereRadius },
      { &EV_FuncBeam_ToggleDelay,      SetToggleDelay },
      { &EV_FuncBeam_ShootRadius,      SetShootRadius },
      { &EV_FuncBeam_EndAlpha,         SetEndAlpha },
      { &EV_FuncBeam_Persist,          SetPersist },
      { &EV_FuncBeam_FindEndpoint,     FindEndpoint },
      { &EV_FuncBeam_UpdateEndpoint,   UpdateEndpoint },
      { &EV_FuncBeam_UpdateOrigin,     UpdateOrigin },
      { &EV_FuncBeam_Shoot,            Shoot },
		{ NULL, NULL }
	};

FuncBeam::FuncBeam()
	{
   setSolidType( SOLID_NOT );
 	setOrigin();

   damage         = 0;
   life           = 0;
   shootradius    = 0;
	use_angles     = false;
   
   edict->s.renderfx    |= RF_BEAM;
   edict->s.eType       = ET_BEAM;  // Entity type beam
   edict->s.modelindex  = 1;	      // must be non-zero
   SetBeamShader( "beamshader" );

   if ( !LoadingSavegame )
      {
      edict->s.alpha       = 1;        // alpha  
      edict->s.surfaces[4] = 4;        // num segments

      BEAM_PARM_TO_PKT( 1, edict->s.surfaces[0] );   // life
      edict->s.bone_angles[0][1] = 5; // Max offset
      edict->s.torso_anim = ENTITYNUM_NONE;
      BEAM_PARM_TO_PKT( 1, edict->s.surfaces[9] );   // endalpha

      if ( spawnflags & 0x0001 ) // Start On
         PostEvent( EV_Activate, EV_POSTSPAWN );
      else
         hideModel();
      edict->s.skinNum = 0;
      if ( spawnflags & 0x0002 ) 
         edict->s.skinNum |= BEAM_PERSIST_EFFECT;
      if ( spawnflags & 0x0004 ) 
         edict->s.skinNum |= BEAM_WAVE_EFFECT;
      if ( spawnflags & 0x0008 ) 
         edict->s.skinNum |= BEAM_USE_NOISE;

      // Try to find the endpoint of this beam after everything has been spawned
      PostEvent( EV_FuncBeam_FindEndpoint, EV_LINKBEAMS );
      }
   }

void FuncBeam::SetEndAlpha
   (
   Event *ev
   )

   {
   BEAM_PARM_TO_PKT( ev->GetFloat( 1 ), edict->s.surfaces[9] );
   }

void FuncBeam::SetToggleDelay
   (
   Event *ev
   )

   {
   edict->s.skinNum |= BEAM_TOGGLE;
   
   if ( ev->NumArgs() > 2 )
      {
      str arg = ev->GetString( 1 );
      if ( !arg.icmp( "random" ) )
         {
         edict->s.skinNum |= BEAM_RANDOM_TOGGLEDELAY;
         }
      BEAM_PARM_TO_PKT( ev->GetFloat( 2 ), edict->s.surfaces[8] );
      }
   else
      {
      BEAM_PARM_TO_PKT( ev->GetFloat( 1 ), edict->s.surfaces[8] );
      }   
   }

void FuncBeam::SetSphereRadius
   (
   Event *ev
   )

   {
   edict->s.skinNum |= BEAM_SPHERE_EFFECT;
   BEAM_PARM_TO_PKT( ev->GetFloat( 1 ), edict->s.surfaces[7] );
   }

void FuncBeam::SetNumSphereBeams
   (
   Event *ev
   )

   {
   edict->s.skinNum |= BEAM_SPHERE_EFFECT;
   edict->s.surfaces[6] = ev->GetInteger( 1 );
   }

void FuncBeam::SetAngle
   (
   Event *ev
   )

   {
   Vector   movedir;

   movedir = G_GetMovedir( ev->GetFloat( 1 ) );
	setAngles( movedir.toAngles() );
   }

void FuncBeam::SetAngles
   (
   Event *ev
   )

   {
   setAngles( ev->GetVector( 1 ) );
   }

// Override setAngles to update the endpoint of the beam if it's rotated
void FuncBeam::setAngles
   (
   Vector angles
   )

   {
   trace_t  trace;
   Vector   endpoint;

   ScriptSlave::setAngles( angles );
  
   // If there is no target, then use the angles to determine where to put the 
   // endpoint
   if ( !end )
      {
      endpoint = origin + Vector( orientation[0] ) * MAP_SIZE;

      trace = G_Trace( origin, vec_zero, vec_zero, endpoint, this, MASK_SOLID, false, "FuncBeam" );

      VectorCopy( trace.endpos, edict->s.origin2 );

	   use_angles = true;
      }
   }

void FuncBeam::SetEndPoint
   (
   Event *ev
   )

   {
   trace_t  trace;

   end_point = ev->GetVector( 1 );

   trace = G_Trace( origin, vec_zero, vec_zero, end_point, this, MASK_SOLID, false, "FuncBeam" );
   VectorCopy( trace.endpos, edict->s.origin2 );

	use_angles = false;
   }

void FuncBeam::SetModel
   (
   Event *ev
   )

   {
   setModel( ev->GetString( 1 ) );
   edict->s.renderfx &= ~RF_BEAM;
   edict->s.eType    = ET_BEAM;
   edict->s.skinNum |= BEAM_USEMODEL;
   }

void FuncBeam::SetDamage
   (
   Event *ev
   )

   {
   damage = ev->GetFloat( 1 );
   }

void FuncBeam::SetLife
   (
   Event *ev
   )

   {
   BEAM_PARM_TO_PKT( ev->GetFloat( 1 ), edict->s.surfaces[0] );
   }

void FuncBeam::SetColor
   (
   Event *ev
   )

   {
   Vector color = ev->GetVector( 1 );
   G_SetConstantLight( &edict->s.constantLight, &color[ 0 ], &color[ 1 ], &color[ 2 ], NULL );
   }

void FuncBeam::SetSegments
   (
   Event *ev
   )

   {
   edict->s.surfaces[4] = ev->GetInteger( 1 );
   }

void FuncBeam::SetBeamShader
   (
   str beam_shader
   )

   {
   str temp_shader;

   shader = beam_shader;
   edict->s.tag_num     = gi.imageindex( shader );

	temp_shader = shader + ".spr";
	CacheResource( temp_shader, this );
   }

void FuncBeam::SetBeamShader
   (
   Event *ev
   )

   {
   SetBeamShader( ev->GetString( 1 ) );
   }

void FuncBeam::SetBeamTileShader
   (
   Event *ev
   )

   {
   SetBeamShader( ev->GetString( 1 ) );
   edict->s.skinNum |= BEAM_TILESHADER;
   }

void FuncBeam::SetMaxoffset
   (
   Event *ev
   )

   {
   edict->s.bone_angles[0][1] = ev->GetFloat( 1 );
   }

void FuncBeam::SetMinoffset
   (
   Event *ev
   )

   {
   edict->s.bone_angles[0][0] = ev->GetFloat( 1 );
   }

void FuncBeam::SetOverlap
   (
   Event *ev
   )

   {
   BEAM_PARM_TO_PKT( ev->GetFloat( 1 ), edict->s.surfaces[3] );
   }

void FuncBeam::SetDelay
   (
   Event *ev
   )

   { 
   if ( ev->NumArgs() > 2 )
      {
      str arg = ev->GetString( 1 );
      if ( !arg.icmp( "random" ) )
         {
         edict->s.skinNum |= BEAM_RANDOM_DELAY;
         }
      BEAM_PARM_TO_PKT( ev->GetFloat( 2 ), edict->s.surfaces[5] );
      }
   else
      {
      BEAM_PARM_TO_PKT( ev->GetFloat( 1 ), edict->s.surfaces[5] );
      }   
   }

void FuncBeam::Deactivate
   (
   Event *ev
   )

   {
   hideModel();

   // Cancel all of the events to activate
   CancelEventsOfType( EV_FuncBeam_Activate );
   CancelEventsOfType( EV_Activate );
   CancelEventsOfType( EV_FuncBeam_UpdateEndpoint );
   CancelEventsOfType( EV_FuncBeam_UpdateOrigin );
   }

void FuncBeam::SetShootRadius
   (
   Event *ev
   )

   {
   shootradius = ev->GetFloat( 1 );
   }

void FuncBeam::SetPersist
   (
   Event *ev
   )

   {
   qboolean persist = ev->GetBoolean( 1 );

   if ( persist )
      edict->s.skinNum |= BEAM_PERSIST_EFFECT;
   else 
      edict->s.skinNum &= ~BEAM_PERSIST_EFFECT;
   }

void FuncBeam::Shoot
   (
   Event *ev
   )

   {
   trace_t  trace;
   Vector   start, end;

   start = edict->s.origin;
   end   = edict->s.origin2;

   Vector   dir( end - start );
   Vector   b1( -shootradius, -shootradius, -shootradius );
   Vector   b2( shootradius, shootradius, shootradius );

   trace = G_Trace( start, b1, b2, end, this, MASK_SHOT, false, "FuncBeam::Activate" );

   if ( trace.ent && trace.ent->entity && trace.ent->entity->takedamage )
      {
      // damage the ent
   	trace.ent->entity->Damage( this,
                                 this,
                                 damage,
                                 trace.endpos,
                                 dir,
                                 trace.plane.normal,
                                 0,
                                 0,
                                 MOD_BEAM
                                 );
      }

   PostEvent( EV_FuncBeam_Shoot, 0.1f );
   }

void FuncBeam::Activate
   (
   Event *ev
   )

   {
   Vector      forward;
   trace_t     trace;

   showModel();

   // An entity is targeted
   if ( end )
      {
      VectorCopy( end->origin, edict->s.origin2 );
      // Post an event so that the beam will update itself every frame
      PostEvent( EV_FuncBeam_UpdateEndpoint, FRAMETIME );
      }
   else if ( use_angles )
      {
      angles.AngleVectors( &forward, NULL, NULL );

      Vector endpoint( orientation[ 0 ] );
      endpoint *= MAP_SIZE;

      trace = G_Trace( origin, vec_zero, vec_zero, endpoint, this, MASK_SOLID, false, "FuncBeam::Activate" );
      VectorCopy( trace.endpos, edict->s.origin2 );
      }
	else
		{
		trace = G_Trace( origin, vec_zero, vec_zero, end_point, this, MASK_SOLID, false, "FuncBeam::Activate" );
      VectorCopy( trace.endpos, edict->s.origin2 );
		}

   if ( origin_target )
      {
      PostEvent( EV_FuncBeam_UpdateOrigin, FRAMETIME );
      }

   if ( damage )
      {
      // Shoot beam and cause damage every frame
      ProcessEvent( EV_FuncBeam_Shoot );
      }

   // If life is set, then post a deactivate message
   if ( life > 0 && !EventPending( EV_FuncBeam_Deactivate ) )
      {
      PostEvent( EV_FuncBeam_Deactivate, life );
      return;
      }
   }

void FuncBeam::UpdateEndpoint
   (
   Event *ev
   )

   {
   if ( end )
      {
      Event *ev1 = new Event( ev );

      VectorCopy( end->origin, edict->s.origin2 );
      PostEvent( ev1, FRAMETIME );
      }
   }

void FuncBeam::UpdateOrigin
   (
   Event *ev
   )

   {
   if ( origin_target )
      {
      Event *ev1 = new Event( ev );

      setOrigin(  origin_target->centroid );
      PostEvent( ev1, FRAMETIME );
      }
   }

void FuncBeam::FindEndpoint
   (
   Event *ev
   )

   {
   if ( target && strlen( target ) )
      {
      end = G_FindTarget( NULL, target );
      if ( end )
         {
         VectorCopy( end->origin, edict->s.origin2 );
         }
      }
   }

FuncBeam *CreateBeam
   (
   const char *model,
   const char *shader,
   Vector start,
   Vector end,
   int numsegments,
   float scale,
   float life,
   float damage,
   Entity *origin_target
   )

   {
   FuncBeam *beam;
   trace_t  trace;

   // set start point
   beam = new FuncBeam;
   beam->setOrigin( start );

   if ( origin_target )
      beam->origin_target = origin_target;

   // set endpoint
	beam->end_point = end;
   trace = G_Trace( start, vec_zero, vec_zero, end, beam, MASK_SOLID, false, "CreateBeam" );
   VectorCopy( trace.endpos, beam->edict->s.origin2 );
	beam->use_angles = false;

   if ( model )
      {
      // set the model if we have one
      beam->setModel( model );
      beam->edict->s.renderfx &= ~RF_BEAM;
      beam->edict->s.eType    = ET_BEAM;
      beam->edict->s.skinNum |= BEAM_USEMODEL;
      }

   if ( shader )
      {
      // Set the shader as an image configstring   
      beam->SetBeamShader( shader );
      }

   // set num segments
   beam->edict->s.surfaces[4] = numsegments;

   // set scale
   beam->setScale( scale );

   // set life
   BEAM_PARM_TO_PKT( life, beam->edict->s.surfaces[0] );
	beam->life = life;

   // set damage
   beam->damage = damage;

   // activate it
   beam->ProcessEvent( EV_Activate );
   beam->PostEvent( EV_Remove, life );
   return beam;
   }
