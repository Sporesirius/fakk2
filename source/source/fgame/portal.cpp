//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/portal.cpp                         $
// $Revision:: 7                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/23/00 8:41p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/portal.cpp                              $
// 
// 7     6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 6     1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 5     10/05/99 2:05p Markd
// Added SVF_SENDPVS which forces an entity to be checked by the PVS for
// sending and not trivially rejected because of lack of modelindex or sound
// 
// 4     9/29/99 5:19p Steven
// Event formatting.
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
// 9     8/23/99 6:54p Markd
// fixed portal quaked stuff
// 
// 8     8/03/99 5:40p Markd
// Removed a bunch of entity_state stuff from q_shared, added new UpdateEntity
// command
// 
// 7     6/11/99 2:20p Phook
// Renamed a few entities
//
// DESCRIPTION:
// Portals - surfaces that are mirrors or cameras

#include "portal.h"

/*QUAKED portal_surface (1 0 1) (-8 -8 -8) (8 8 8)
The portal surface nearest this entity will show a view from the targeted portal_camera, or a mirror view if untargeted.
*/
   
Event EV_Portal_LocateCamera
	( 
	"locatecamera",
	EV_DEFAULT,
   NULL,
   NULL,
   "Locates the camera position."
	);

CLASS_DECLARATION( Entity, PortalSurface, "portal_surface" )
	{
      { &EV_Portal_LocateCamera,     LocateCamera },
		{ NULL, NULL }
	};

void PortalSurface::LocateCamera
   (
   Event *ev 
   )

   {
	Entity   *owner;
	Entity   *target;
   Vector   dir;

	owner = G_FindTarget( NULL, Target() );

   if ( !owner )
      {
      // No target, just a mirror
      VectorCopy( edict->s.origin, edict->s.origin2 );
      return;
      }

	// frame holds the rotate speed
	if ( owner->spawnflags & 1 )
      {
		edict->s.frame = 25;
	   }
   else if ( owner->spawnflags & 2 )
      {
		edict->s.frame = 75;
	   }

	// skinNum holds the rotate offset
	edict->s.skinNum = owner->edict->s.skinNum;

	VectorCopy( owner->origin, edict->s.origin2 );

	// see if the portal_camera has a target
	target = G_FindTarget( NULL, owner->Target() );

	if ( target )
      {
		dir = target->origin - owner->origin;
		dir.normalize();
      setAngles( dir.toAngles() );
	   } 
   else
      {
      setAngles( owner->angles );
		dir = owner->orientation[ 0 ];
	   }
   }

PortalSurface::PortalSurface
   (
   )

   {
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

   VectorClear( edict->mins );
	VectorClear( edict->maxs );

	gi.linkentity( edict );

	edict->svflags = SVF_PORTAL | SVF_SENDPVS;
	edict->s.eType = ET_PORTAL;

   PostEvent( EV_Portal_LocateCamera, EV_POSTSPAWN );
   }


/*QUAKED portal_camera (1 0 1) (-8 -8 -8) (8 8 8) slowrotate fastrotate
The target for a portal_surface.  You can set either angles or target another entity to determine the direction of view.
"roll" an angle modifier to orient the camera around the target vector;
*/
   
Event EV_Portal_Roll
	( 
	"roll",
	EV_DEFAULT,
   "f",
   "roll",
   "Sets the portal camera's roll."
	);

CLASS_DECLARATION( Entity, PortalCamera, "portal_camera" )
	{
      { &EV_Portal_Roll,         Roll },
		{ NULL, NULL }
	};

void PortalCamera::Roll   
   (
   Event *ev
   )

   {
   float roll = ev->GetFloat( 1 );

   // skinNum holds the roll
   edict->s.skinNum = roll/360.0f * 256;
   }

PortalCamera::PortalCamera
   (
   )

   {
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

   VectorClear( edict->mins );
   VectorClear( edict->maxs );

   // No roll on the camera by default
   edict->s.skinNum = 0;
   
   gi.linkentity( edict );
   }
