//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/powerups.cpp                       $
// $Revision:: 9                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 7/29/00 9:06p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/powerups.cpp                            $
// 
// 9     7/29/00 9:06p Aldie
// Increased time of COP
// 
// 8     7/15/00 12:48p Steven
// Made circle of protection not attack friends.
// 
// 7     7/13/00 3:18p Aldie
// Fix for cop
// 
// 6     7/10/00 6:50p Markd
// fixed some issues with water running
// 
// 5     6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 4     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 3     5/30/00 2:48p Aldie
// Fix for beam parent effect
// 
// 2     5/30/00 10:59a Aldie
// Added Circle of Protection Powerup
//
// DESCRIPTION:
// 
#include "powerups.h"
#include "player.h"

//====================================
// CIRCLE OF PROTECTION
//====================================

Event EV_CircleOfProtection_Deactivate
   (
   "_deactivate",
   EV_DEFAULT,
   NULL,
   NULL,
   "Deactivates the COP"
   );
Event EV_CircleOfProtection_DoDamage
   (
   "_dodamage",
   EV_DEFAULT,
   NULL,
   NULL,
   "Damages enemies in a radius"
   );
Event EV_CircleOfProtection_MinRadius
   (
   "minradius",
   EV_DEFAULT,
   "f",
   "minradius",
   "Set the minimum distance for the enemy in order for it to be damaged."
   );
Event EV_CircleOfProtection_MaxRadius
   (
   "maxradius",
   EV_DEFAULT,
   "f",
   "maxradius",
   "Set the maximum distance for the enemy in order for it to be damaged."
   );
Event EV_CircleOfProtection_Damage
   (
   "damage",
   EV_DEFAULT,
   "f",
   "damage",
   "Set the amount of damage the COP does"
   );
Event EV_CircleOfProtection_DamageDelay
   (
   "damagedelay",
   EV_DEFAULT,
   "f",
   "delay",
   "Set the delay between doing damage"
   );
Event EV_CircleOfProtection_Knockback
   (
   "knockback",
   EV_DEFAULT,
   "f",
   "knockback",
   "Set the knockback of the damage effect"
   );

CLASS_DECLARATION( InventoryItem, CircleOfProtection, "" )
   {
      { &EV_InventoryItem_Use,                     Use },
      { &EV_CircleOfProtection_Deactivate,         Deactivate },
      { &EV_CircleOfProtection_DoDamage,           DoDamage },
      { &EV_CircleOfProtection_MinRadius,          MinRadius },
      { &EV_CircleOfProtection_MaxRadius,          MaxRadius },
      { &EV_CircleOfProtection_Damage,             SetDamage },
      { &EV_CircleOfProtection_DamageDelay,        DamageDelay },
      { &EV_CircleOfProtection_Knockback,          Knockback },
	   { NULL, NULL }
   };

CircleOfProtection::CircleOfProtection
   (
   )

   {
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }
   m_minradius    = 100.0f;
   m_maxradius    = 200.0f;
   m_damage       = 10.0f;
   m_damage_delay = 1.0f;
   m_knockback    = 20;
   m_copmodel     = NULL;   
   }

void CircleOfProtection::SetDamage
   (
   Event *ev
   )

   {
   m_damage = ev->GetFloat( 1 );
   }

void CircleOfProtection::MinRadius
   (
   Event *ev
   )

   {
   m_minradius = ev->GetFloat( 1 );
   }

void CircleOfProtection::MaxRadius
   (
   Event *ev
   )

   {
   m_maxradius = ev->GetFloat( 1 );
   }

void CircleOfProtection::DamageDelay
   (
   Event *ev
   )

   {
   m_damage_delay = ev->GetFloat( 1 );
   }

void CircleOfProtection::Knockback
   (
   Event *ev
   )

   {
   m_knockback = ev->GetFloat( 1 );
   }

void CircleOfProtection::Use
   (
   Event *ev
   )

   {
   Entity   *other;
   int      tag_num;

   // Player already has circle of protection power
   if ( m_copmodel )
      return;

   // Make sure it's the player
   other = ev->GetEntity( 1 );
   if ( !other || !other->isSubclassOf( Player ) )
      {
      return;
      }

   // Attach the COP model to the player
   m_copmodel = new Animate;
   m_copmodel->setModel( "models/fx_cop.tik" );
   tag_num = gi.Tag_NumForName( other->edict->s.modelindex, "Bip01 Spine" );
   m_copmodel->attach( other->entnum, tag_num );
   m_copmodel->setSolidType( SOLID_NOT );
   m_copmodel->setMoveType( MOVETYPE_NONE );
   m_copmodel->showModel();

   // Disable the protection in 30 seconds
   PostEvent( EV_CircleOfProtection_DoDamage, m_damage_delay );
   PostEvent( EV_CircleOfProtection_Deactivate, 90 );

   // Remove this item from the player's inventory
   if ( owner )
		{
		owner->RemoveItem( this );
		}
   }

void CircleOfProtection::DoDamage
   (
   Event *ev
   )

   {
   Entity   *ent;
   qboolean playsound=qfalse;
   Sentient *owner;

   owner = this->owner;
   // Make sure we have an owner
   assert( owner );
   if ( !owner )
      return;

   // Find enemies in radius and damage them
   ent = findradius( NULL, owner->origin, m_maxradius ); 

   while( ent )
      {
      Vector delta   = ent->centroid - owner->centroid;
      float dist     = delta.length();
		qboolean	do_damage;

		do_damage = false;
      
      // Do damage if it's past the minradius

      if ( ( dist > m_minradius ) && ent->isSubclassOf( Sentient ) && !ent->deadflag && ent->takedamage )
			do_damage = true;

		// Don't damage if this is a friend

		if ( do_damage && ent->isSubclassOf( Actor ) )
			{
			Actor *act = (Actor *)ent;

			if ( act->actortype == IS_FRIEND )
				do_damage = false;
			}

		if ( do_damage )
         {
         delta.normalize();
         ent->Damage( this, owner, m_damage, ent->centroid, delta, vec_zero, m_knockback, 0, MOD_CIRCLEOFPROTECTION );
         FuncBeam *beam = CreateBeam( NULL, "emap1", owner->centroid, ent->centroid, 10, 6.0f, 0.2f );
         beam->edict->s.torso_anim = owner->entnum;
         beam->setOrigin( owner->centroid - owner->origin );
         playsound = qtrue;
         }

      ent = findradius( ent, owner->origin, m_maxradius ); 
      }

   if ( playsound )
      {
      owner->Sound( "snd_cop_impact" );
      }

   // Recheck for damage in 0.5 seconds
   PostEvent( EV_CircleOfProtection_DoDamage, m_damage_delay );   
   }

void CircleOfProtection::Deactivate
   (
   Event *ev
   )

   {
   if ( m_copmodel )
      m_copmodel->ProcessEvent( EV_Remove );

   m_copmodel = NULL;   
   CancelEventsOfType( EV_CircleOfProtection_DoDamage );
   }

