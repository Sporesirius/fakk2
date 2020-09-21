//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/crossbow.cpp                       $
// $Revision:: 3                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 4/08/00 2:49p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/crossbow.cpp                            $
// 
// 3     4/08/00 2:49p Aldie
// New crossbow bolt implementation
// 
// 2     4/08/00 11:53a Aldie
// First version
//
// DESCRIPTION:
// Crossbow projectile

#include "crossbow.h"
#include "decals.h"

CLASS_DECLARATION( Projectile, CrossbowProjectile, NULL )
	{
		{ NULL, NULL }
	};

CrossbowProjectile::CrossbowProjectile
   (
   )

   {
   }

void CrossbowProjectile::DoDecal
   (
   void
   )

   {
   float scale=1;

   if ( charge_fraction < 0.3 )
      {
      scale = .3;
      }
   else if ( charge_fraction > 0.6 )
      {
      scale = 1.5;
      }

   if ( impactmarkshader.length() )
      {
      Decal *decal = new Decal;
      decal->setShader( impactmarkshader );
      decal->setOrigin( level.impact_trace.endpos );
      decal->setDirection( level.impact_trace.plane.normal );
      decal->setOrientation( impactmarkorientation );
      decal->setRadius( impactmarkradius * scale );
      }
   }

void CrossbowProjectile::Explode
   (
   Event *ev
   )

   {
   Entity *owner;

   // Get the owner of this projectile
   owner = G_GetEntity( this->owner );

   // If the owner's not here, make the world the owner
   if ( !owner )
      owner = world;

   // When a crossbow bolt explodes, depending on the charge time it may explode   
   if ( explosionmodel.length() && charge_fraction > 0.3 )
      {
      if ( charge_fraction > 0.6 ) 
         ExplosionAttack( origin, owner, explosionmodel, Vector( 0,0,0 ), NULL, 1.5 );
      else
         ExplosionAttack( origin, owner, explosionmodel, Vector( 0,0,0 ), NULL );
      }

   PostEvent( EV_Remove, 0 );
   }
