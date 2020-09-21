//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/object.cpp                         $
// $Revision:: 15                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/03/00 7:56p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/object.cpp                              $
// 
// 15    7/03/00 7:56p Markd
// fixed setup and anim events
// 
// 14    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 13    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 12    5/10/00 10:32a Steven
// Added com_blood stuff.
// 
// 11    1/27/00 11:35a Markd
// Fixed solid/notsolid client side entities
// 
// 10    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 9     1/14/00 5:07p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 8     1/12/00 6:12p Jimdose
// rewrote CreateExplosion
// 
// 7     1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 6     10/21/99 5:24p Aldie
// Changed Object::Setup to use Anim_Random
// 
// 5     9/29/99 5:18p Steven
// Event formatting.
// 
// 4     9/22/99 4:48p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 3     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 2     9/13/99 4:22p Jimdose
// merge
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 15    8/26/99 5:57p Markd
// Re-added fx_sprite support
// 
// 14    6/11/99 1:23p Phook
// 
// 13    6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
// 
// 12    6/11/99 12:46p Phook
// EClass color changes
//
// DESCRIPTION:
//


#include "g_local.h"
#include "object.h"
#include "sentient.h"
#include "misc.h"
#include "explosion.h"
#include "gibs.h"
#include "specialfx.h"

Event EV_Object_Setup
	( 
	"_setup",
	EV_DEFAULT,
   NULL,
   NULL,
   "Sets up an object."
	);
Event EV_Object_SetAnim
	( 
	"anim",
	EV_DEFAULT,
   "s",
   "animname",
   "Sets up the object with the specified animname."
	);

Event EV_Object_Shootable
	( 
	"shootable",
	EV_DEFAULT,
   NULL,
   NULL,
   "Make the object shootable but not necessarily solid to the player."
	);

CLASS_DECLARATION( Animate, Object, "object" )
	{
      { &EV_Killed,					      Killed },
      { &EV_Object_Setup,              Setup },
      { &EV_Object_SetAnim,            SetAnim },
      { &EV_Object_Shootable,          MakeShootable },
		{ NULL, NULL }
	};

Object::Object()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   // 
   // all objects default to not solid
   //
  	setSolidType( SOLID_NOT );

   health = 0;

   takedamage = ( spawnflags & 2 ) ? DAMAGE_NO : DAMAGE_YES;

   //
   // we want the bounds of this model auto-rotated
   //
   flags |= FL_ROTATEDBOUNDS;

   if ( !com_blood->integer )
      {
      flags &= ~FL_BLOOD;
      flags &= ~FL_DIE_GIBS;
      }

   PostEvent( EV_Object_Setup, EV_POSTSPAWN );
	}

void Object::SetAnim
   (
   Event *ev
   )

   {
   int animnum;

   if ( ( ev->NumArgs() >= 1 ) && gi.IsModel( edict->s.modelindex ) )
      {
      animnum = gi.Anim_Random( edict->s.modelindex, ev->GetString( 1 ) );
      if ( animnum >= 0 )
         {
         NewAnim( animnum );
         }
      }
   }


void Object::Setup
   (
   Event *ev
   )

   {
   if ( !health )
      {
      health = ( maxs - mins ).length();
      max_health = health;
      }
   }

void Object::MakeShootable
   (
   Event *ev
   )

   {
  	setContents( CONTENTS_SHOOTABLE_ONLY );
   link();
   }

void Object::Killed(Event *ev)
   {
   Entity * ent;
   Entity * attacker;
   Vector dir;
   Event * event;
   const char * name;

   takedamage = DAMAGE_NO;
   setSolidType( SOLID_NOT );
	hideModel();

	attacker		= ev->GetEntity( 1 );

   if (flags & FL_DIE_EXPLODE)
      {
      CreateExplosion( origin, 50, this, this, this );
      }

   if (flags & FL_DIE_GIBS)
      {
      setSolidType( SOLID_NOT );
      hideModel();

      CreateGibs( this, -150, edict->s.scale, 3 );
      }

//
// kill the killtargets
//
	name = KillTarget();
	if ( name && strcmp( name, "" ) )
		{
      ent = NULL;
		do
			{
			ent = G_FindTarget( ent, name );
			if ( !ent )
				{
				break;
				}
			ent->PostEvent( EV_Remove, 0 );
			}
		while ( 1 );
		}

//
// fire targets
//
	name = Target();
	if ( name && strcmp( name, "" ) )
		{
      ent = NULL;
		do
			{
			ent = G_FindTarget( ent, name );
			if ( !ent )
				{
				break;
				}
			event = new Event( EV_Activate );
			event->AddEntity( attacker );
			ent->ProcessEvent( event );
			}
		while ( 1 );
		}

   PostEvent( EV_Remove, 0 );
   }

/*****************************************************************************/
/*QUAKED func_throwobject (0 0.25 0.5) (-16 -16 0) (16 16 32)

This is an object you can pickup and throw at people
******************************************************************************/

Event EV_ThrowObject_Pickup
	( 
	"pickup",
	EV_DEFAULT,
   "es",
   "entity tag_name",
   "Picks up this throw object and attaches it to the entity."
	);
Event EV_ThrowObject_Throw
	( 
	"throw",
	EV_DEFAULT,
   "efeF",
   "owner speed targetent grav",
   "Throw this throw object."
	);
Event EV_ThrowObject_PickupOffset
	( 
	"pickupoffset",
	EV_DEFAULT,
   "v",
   "pickup_offset",
   "Sets the pickup_offset."
	);
Event EV_ThrowObject_ThrowSound
	( 
	"throwsound",
	EV_DEFAULT,
   "s",
   "throw_sound",
   "Sets the sound to play when object is thrown."
	);

CLASS_DECLARATION( Object, ThrowObject, "func_throwobject" )
	{
      { &EV_Touch,					      Touch },
      { &EV_ThrowObject_Pickup,	      Pickup },
      { &EV_ThrowObject_Throw,	      Throw },
      { &EV_ThrowObject_PickupOffset,	PickupOffset },
      { &EV_ThrowObject_ThrowSound,	   ThrowSound },
		{ NULL, NULL }
	};

ThrowObject::ThrowObject()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   pickup_offset = vec_zero;
	}

void ThrowObject::PickupOffset
	(
	Event *ev
	)
	{
   pickup_offset = edict->s.scale * ev->GetVector( 1 );
   }

void ThrowObject::ThrowSound
	(
	Event *ev
	)
	{
   throw_sound = ev->GetString( 1 );
   }

void ThrowObject::Touch
	(
	Event *ev
	)

	{
   Entity *other;

	if ( movetype != MOVETYPE_BOUNCE )
      {
      return;
      }

	other = ev->GetEntity( 1 );
	assert( other );

	if ( other->isSubclassOf( Teleporter ) )
		{
		return;
		}

	if ( other->entnum == owner )
		{
		return;
		}

   if ( throw_sound.length() )
      {
		StopLoopSound();
      }

   if ( other->takedamage )
      {
      other->Damage( this, G_GetEntity( owner ), size.length() * velocity.length() / 400, origin, velocity, 
         level.impact_trace.plane.normal, 32, 0, MOD_THROWNOBJECT );
      }

   Damage( this, this, max_health, origin, velocity, level.impact_trace.plane.normal, 32, 0, MOD_THROWNOBJECT );
	}

void ThrowObject::Throw
	(
	Event *ev
	)

	{
   Entity   *owner;
   Sentient *targetent;
   float    speed;
   float    traveltime;
   float    vertical_speed;
   Vector   target;
   Vector   dir;
   float    grav;
   Vector   xydir;
   Event    *e;

   owner = ev->GetEntity( 1 );
   assert( owner );

   if ( !owner )
      {
      return;
      }

   speed = ev->GetFloat( 2 );
   if ( !speed )
      {
      speed = 1;
      }

   targetent = ( Sentient * )ev->GetEntity( 3 );
   assert( targetent );
   if (!targetent)
      {
      return;
      }

   if ( ev->NumArgs() == 4 )
      {
      grav = ev->GetFloat( 4 );
      }
   else
      {
      grav = 1;
      }

   e = new Event( EV_Detach );
   ProcessEvent( e );

	this->owner = owner->entnum;
	edict->ownerNum = owner->entnum;

   gravity = grav;

   target = targetent->origin;
   target.z += targetent->viewheight;

	setMoveType( MOVETYPE_BOUNCE );
	setSolidType( SOLID_BBOX );
	edict->clipmask = MASK_PROJECTILE;

   dir = target - origin;
   xydir = dir;
   xydir.z = 0;
   traveltime = xydir.length() / speed;
   vertical_speed = ( dir.z / traveltime ) + ( 0.5f * gravity * sv_gravity->value * traveltime );
   xydir.normalize();

	// setup ambient flying sound
   if ( throw_sound.length() )
      {
		LoopSound( throw_sound.c_str() );
      }

   velocity = speed * xydir;
   velocity.z = vertical_speed;

 	angles = velocity.toAngles();
	setAngles( angles );

   avelocity.x = crandom() * 200;
   avelocity.y = crandom() * 200;
	takedamage = DAMAGE_YES;
   }

void ThrowObject::Pickup
	(
	Event *ev
	)

	{
   Entity * ent;
   Event * e;
   str bone;

   ent = ev->GetEntity( 1 );

   assert( ent );
   if ( !ent )
      {
      return;
      }
   bone = ev->GetString( 2 );

   setOrigin( pickup_offset );

   e = new Event( EV_Attach );
   e->AddEntity( ent );
   e->AddString( bone );
   ProcessEvent( e );

   edict->s.renderfx &= ~RF_FRAMELERP;
   }
