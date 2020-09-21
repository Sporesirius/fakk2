//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/fists.cpp                             $
// $Revision:: 1                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 9/10/99 10:53a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/fists.cpp                                  $
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 9     8/28/99 11:44a Steven
// Removed global from sound function calls.
// 
// 8     8/18/99 3:28p Jimdose
// added cylindrical collision detection
// 
// DESCRIPTION:
// Normal Hands
// 

#include "g_local.h"
#include "fists.h"
#include "misc.h"
#include "specialfx.h"
//#include "surface.h"

CLASS_DECLARATION( Weapon, Fists, NULL )
	{
	   { &EV_Weapon_Shoot,     Shoot },
		{ NULL, NULL }
	};

Fists::Fists()
	{
	SetModels( NULL, "view_punch.def" );
	SetAmmo( NULL, 0, 0 );
	SetRank( 10, 10 );	
   strike_reach = 64;
   strike_damage = 20;
	SetMaxRange( strike_reach );
   SetType( WEAPON_MELEE );
   kick = 40;
   meansofdeath = MOD_FISTS;
	}

void Fists::Shoot( Event * ev )
	{
	trace_t	trace;
	Vector	start;
	Vector	end;
   float    damage;
	Vector   org;
	Vector   dir;
   int      surfflags;
   int      surftype;

	assert( owner );
	if ( !owner )
		{
		return;
		}

	NextAttack( 1 );

   damage = G_Random(strike_damage)+strike_damage;

	GetMuzzlePosition( &start, &dir );
	end	= start + dir * strike_reach;

   trace = G_FullTrace( start, vec_zero, vec_zero, end, 64, owner, MASK_PROJECTILE, false, "Fists::Shoot" );

	if ( !trace.surface )
		{
      surfflags = 0;
      surftype = 0;
		}
   else
      {
      surfflags = trace.surface->flags;
      surftype = SURFACETYPE_FROM_FLAGS( surfflags );
//      surfaceManager.DamageSurface( &trace, damage, owner );
      }
	dir = Vector(trace.endpos) - start;
	dir.normalize();

	org = Vector(trace.endpos) - dir;

   if ( (trace.fraction < 1.0f) )
      {
      if ( trace.ent->entity && trace.ent->entity->takedamage )
		   {
         if ( trace.ent->entity->flags & FL_BLOOD )
	         {
            if ( ( meansofdeath == MOD_MUTANTHANDS ) || ( trace.ent->entity->health < -500 ) )
               {
					owner->Sound( "impact_goryimpact" );
               }
            else
               {
					owner->Sound( "impact_bodyimpact" );
               }
	         SpawnBlood( org, trace.plane.normal, damage );
	         }
         else
            {
/* GAMEFIX
            gi.WriteByte( svc_temp_entity );
		      gi.WriteByte( TE_STRIKE );
		      gi.WritePosition( org.vec3() );
		      gi.WriteDir( trace.plane.normal );
		      gi.WriteByte( 120 );
		      gi.WriteByte( surftype );
		      gi.multicast( org.vec3(), MULTICAST_PVS );
            */
            }
         if ( trace.intersect.valid )
            {
            // take the ground out so that the kick works
            trace.ent->entity->groundentity = NULL;

   			// We hit a valid surface so send in location based damage
            trace.ent->entity->Damage( this,
                         owner,
                         damage,
                         trace.endpos,
                         dir,
                         trace.plane.normal,
                         kick,
                         0,
                         meansofdeath,
                         trace.intersect.surface,
                         -1,
                         1 );
                         //trace.intersect.damage_multiplier );
            }
         else
            {
            // We didn't hit any surfaces, so send in generic damage
   			trace.ent->entity->Damage( this,
                         owner,
                         damage,
                         trace.endpos,
                         dir,
                         trace.plane.normal,
                         kick,
                         0,
                         meansofdeath,
                         -1,
                         -1,
                         1 );
            }
		   }
      else
		   {
/* GAMEFIX
         gi.WriteByte( svc_temp_entity );
		   gi.WriteByte( TE_STRIKE );
		   gi.WritePosition( org.vec3() );
		   gi.WriteDir( trace.plane.normal );
		   gi.WriteByte( 120 );
		   gi.WriteByte( surftype );
		   gi.multicast( org.vec3(), MULTICAST_PVS );
         */
		   }
      }
	}
