//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/player_combat.cpp                  $
// $Revision:: 60                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/29/00 9:06p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/player_combat.cpp                       $
// 
// 60    7/29/00 9:06p Aldie
// Added water check to swipeoff
// 
// 59    7/29/00 12:55p Aldie
// Added null checks to swipes
// 
// 58    7/24/00 12:16p Steven
// Added a smaller distance to look at non-actors and fixed not finding a
// target.
// 
// 57    7/23/00 8:49p Aldie
// Added some safety nets to the weapon code in sentient and player
// 
// 56    7/18/00 4:25p Markd
// rewrote holstering code
// 
// 55    7/16/00 4:37p Steven
// Moved action level stuff to actor pain and killed.
// 
// 54    7/16/00 10:46a Steven
// Improved head target stuff.
// 
// 53    7/11/00 8:55p Aldie
// Added in an autoaim flag
// 
// 52    7/10/00 7:16p Aldie
// Fixed weapon swipes for new water required method
// 
// 51    7/10/00 6:33p Aldie
// Added SVF_SENDONCE flag and water power for swiping determination
// 
// 50    7/05/00 6:14p Steven
// Added a damage multiplier for combos.
// 
// 49    6/28/00 7:56p Aldie
// Added some pain stuff for use with death.
// 
// 48    6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 47    6/08/00 3:03p Steven
// Added a decent priority sceme to player head watch stuff.
// 
// 46    6/03/00 10:08a Steven
// Made it so player will not look at actors that are bound or attached to
// something.
// 
// 45    6/01/00 7:02p Markd
// removed activeWeapon variable
// 
// 44    6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 43    5/31/00 5:33p Steven
// Added look at me flag and changed masks used in FindClosestEntityInRadius
// from SHOT to OPAQUE.
// 
// 42    5/30/00 5:06p Aldie
// Added large shield to prevent knockdowns
// 
// 41    5/27/00 5:14p Steven
// Added player head watch stuff.
// 
// 40    5/27/00 2:31p Steven
// Added actor targetable stuff.
// 
// 39    5/26/00 2:24p Aldie
// Added waitforplayer commands so we can use it for cinematics when waiting
// for player to finish holstering
// 
// 38    5/06/00 10:40a Steven
// Made it so there is action level and means of death variables for each
// weapon mode.
// 
// 37    5/05/00 6:04p Steven
// Made melee weapons increment the player's action level.
// 
// 36    5/04/00 4:47p Markd
// Added PutawayWeapon event
// 
// 35    5/02/00 7:29p Aldie
// Fix a crash bug
// 
// 34    4/28/00 5:14p Aldie
// Fixed some warning messages
// 
// 33    4/15/00 1:43p Aldie
// Added usenoammo command for a weapon that cannot be used when it has no ammo
// 
// 32    4/07/00 10:17a Markd
// fixed shgliek pickup and weapon holstering
// 
// 31    3/22/00 2:05p Aldie
// Added holster command
// 
// 30    3/15/00 5:52p Aldie
// Added pushsound to func_pushobject and removed a printf.
// 
// 29    3/15/00 4:09p Aldie
// Fixed a bug with using weapons, and added some ability to force a state in
// the player
// 
// 28    2/24/00 4:18p Jimdose
// removed some unused variables and functions
// 
// 27    2/23/00 6:21p Aldie
// More inventory changes
// 
// 26    2/18/00 6:28p Aldie
// Removed some prints
// 
// 25    2/17/00 6:26p Aldie
// Fixed naming conventions for weapon hand and also added various attachtotag
// functionality for weapons that attach to different tags depending on which
// hand they are wielded in.
// 
// 24    2/17/00 12:00p Aldie
// Added command processing to state system with the addition of entrycommands
// and exitcommands.
// 
// 23    2/16/00 4:01p Aldie
// Added shield functionality
// 
// 22    2/10/00 8:05p Aldie
// Added trace to enemyinfov
// 
// 21    2/09/00 8:02p Aldie
// Added loopfire weapons
// 
// 20    2/09/00 5:26p Aldie
// Fix for FindClosestEnemyInRadius
// 
// 19    2/08/00 11:57a Aldie
// Added in enemy check to the FindClosestEnemyInRadius
// 
// 18    2/07/00 7:38p Aldie
// Fixed swiping, also various weapons fixes for sword and for sling
// 
// 17    2/04/00 3:11p Aldie
// Changed sword attack method for water usage
// 
// 16    2/03/00 2:56p Aldie
// Sword and water coding
// 
// 15    2/02/00 7:08p Aldie
// Added new sword code and water damage
// 
// 14    2/01/00 6:27p Aldie
// Removed debug line
// 
// 13    2/01/00 5:28p Aldie
// More updates for auto aiming
// 
// 12    1/29/00 6:17p Aldie
// Fixed some problems when state doesn't exist.
// 
// 11    1/29/00 9:33a Markd
// added logic for 2 handed weapons
// 
// 10    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 9     1/16/00 5:43p Aldie
// Made weapon tag vars
// 
// 8     1/15/00 9:29a Markd
// rename tag_weapon to tag_weapon_right
// 
// 7     1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 6     12/17/99 8:27p Jimdose
// got rid of unused vars and functions
// 
// 5     12/16/99 5:03p Aldie
// Fix for find enemyinfov
// 
// 4     12/13/99 10:14a Aldie
// Temp update for bug fixing due to merge
// 
// 3     12/09/99 2:31p Aldie
// Head tracking
// 
// 2     12/08/99 7:00p Aldie
// Busting up player a bit and wrote some head tracking code
//
// DESCRIPTION:
// Player combat system and combat utility functions
// 

#include "player.h"
#include "sword.h"
#include "weaputils.h"

static Entity *FindClosestEntityInRadius
   (
   Vector origin,
   Vector forward,
   float  fov,
   float  maxdist
   )

   {
   float    dist,dot;
   float    fovdot = cos( fov * 0.5 * M_PI / 180.0 );
   Entity   *ent;
   Entity   *bestent=NULL;
   int      bestdist = 999999;
	qboolean valid_entity;

   // Find closest enemy in radius
   ent = findradius( NULL, origin, maxdist ); 

   while( ent )
      {      
		valid_entity = false;

      if ( ent->flags & FL_AUTOAIM )
         {
         valid_entity = true;
         }
      else if ( ent->isSubclassOf( Actor ) && !ent->deadflag )
			{         
			Actor *actor = ( Actor * )ent;

			if ( actor->actortype == IS_ENEMY && actor->CanTarget() && !actor->bindmaster && actor->edict->s.parent == ENTITYNUM_NONE )
				valid_entity = true;
			}

		if ( valid_entity )
         {
         // Check to see if the enemy is closest to us
      	Vector delta = ( ent->centroid ) - origin;

      	dist = delta.length();

         if ( dist < bestdist )
            {
            delta.normalize();

            // It's close, now check to see if it's in our FOV.
	         dot = DotProduct( forward, delta );
      
            if ( dot > fovdot )
               {
               trace_t trace;
               // Do a trace to see if we can get to it
               trace = G_Trace( origin,
                                 vec_zero,
                                 vec_zero,
                                 ent->centroid,
                                 NULL,
                                 MASK_OPAQUE,
                                 false, 
                                 "FindClosestEntityInRadius" );
               
               if ( ( trace.ent && trace.entityNum == ent->entnum ) || ( trace.fraction == 1 ) )
                  {
                  // dir = delta;
                  bestent  = ent;
                  bestdist = dist;
                  }
               }
            }
         }
      ent = findradius( ent, origin, maxdist );
      }
   return bestent;
   }

static Entity *FindHeadTarget
   (
   Vector origin,
   Vector forward,
   float  fov,
   float  maxdist
   )

   {
   float    dist,dot;
   float    fovdot = cos( fov * 0.5 * M_PI / 180.0 );
   Entity   *ent;
   Entity   *bestent=NULL;
   int      bestdist = 999999;
	qboolean valid_entity;
	qboolean higher_priority;

   // Find closest enemy in radius
   ent = findradius( NULL, origin, maxdist ); 

   while( ent )
      {      
		valid_entity = false;

		if ( ent->isSubclassOf( Actor ) && !ent->deadflag )
			{         
			Actor *actor = ( Actor * )ent;

			if ( actor->actortype == IS_ENEMY && actor->CanTarget() && !actor->bindmaster && actor->edict->s.parent == ENTITYNUM_NONE )
				valid_entity = true;
			}

		if ( !valid_entity )
			{
			if ( ent->look_at_me )
				{
				if ( ent->isSubclassOf( Item ) )
					{
					Item *item = (Item *)ent;

					if ( !item->GetOwner() )
						valid_entity = true;

					if ( item->has_been_looked_at )
						valid_entity = false;
					}
				else
					valid_entity = true;
				}
			}

		if ( valid_entity )
         {
			Actor *bestact = NULL;
			Actor *act = NULL;

         // Check to see if the enemy is closest to us
      	Vector delta = ( ent->centroid ) - origin;

      	dist = delta.length();

			higher_priority = false;

			if ( bestent && bestent->isSubclassOf( Actor ) )
				bestact = (Actor *)bestent;

			if ( ent->isSubclassOf( Actor ) )
				act = (Actor *)ent;

			if ( !ent->isSubclassOf( Actor ) && ( dist > 650 ) )
				higher_priority = false;
			else if ( !bestent )
				higher_priority = true;
			else if ( ent->isSubclassOf( Actor ) && act->actortype == IS_ENEMY && 
			     bestent->isSubclassOf( Actor ) && bestact->actortype == IS_ENEMY && dist < bestdist )
				higher_priority = true;
			else if ( bestent->isSubclassOf( Actor ) && bestact->actortype == IS_ENEMY && 
			     ( bestdist < dist || bestdist < 750 ) )
				higher_priority = false;
			else if ( ent->isSubclassOf( Actor ) && act->actortype == IS_ENEMY && 
			     ( dist < bestdist || dist < 750 ) )
				higher_priority = true;
			else if ( ent->isSubclassOf( Item ) && bestent->isSubclassOf( Item ) && dist < bestdist )
				higher_priority = true;
			else if ( bestent->isSubclassOf( Item ) && ( bestdist < dist || bestdist < 250 ) )
				higher_priority = false;
			else if ( ent->isSubclassOf( Item ) && ( dist < bestdist || dist < 250 ) )
				higher_priority = true;
			else if ( dist < bestdist )
				higher_priority = true;

         if ( higher_priority )
            {
            delta.normalize();

            // It's close, now check to see if it's in our FOV.  Use the v_angle to determine it            
	         dot = DotProduct( forward, delta );
      
            if ( dot > fovdot )
               {
               trace_t trace;
               // Do a trace to see if we can get to it
               trace = G_Trace( origin,
                                 vec_zero,
                                 vec_zero,
                                 ent->centroid,
                                 NULL,
                                 MASK_OPAQUE,
                                 false, 
                                 "FindClosestEntityInRadius" );
               
               if ( ( trace.ent && trace.entityNum == ent->entnum ) || ( trace.fraction == 1 ) )
                  {
                  // dir = delta;
                  bestent  = ent;
                  bestdist = dist;
                  }
               }
            }
         }
      ent = findradius( ent, origin, maxdist );
      }
   return bestent;
   }

Entity *Player::FindEnemyInFOVFromTagWithOffset
   (
   float fov,
   float maxdist,
   str   tagname,
   Vector offset
   )

   {
   vec3_t mat[3];
   orientation_t tag_or;

   GetTagPositionAndOrientation( gi.Tag_NumForName( edict->s.modelindex, tagname ), &tag_or );
   
   AnglesToAxis( torsoAngles, mat );

   //G_DebugLine( tag_or.origin + offset, tag_or.origin + offset + Vector( mat[0] ) * 100, 1,1,1,1 );

   return FindClosestEntityInRadius( tag_or.origin + offset, mat[0], fov, maxdist );
   }

//====================
//FindEnemyInFOV
//Returns entity if an enemy is in the player's FOV
//====================
Entity *Player::FindEnemyInFOV
   (
   float fov,
   float maxdist
   )

   {
   vec3_t mat[3];

   AnglesToAxis( headAngles, mat );
   return FindClosestEntityInRadius( this->centroid, mat[0], fov, maxdist );
   }

//====================
//AdjustAnglesForAttack 
//Adjust the player angles toward an enemy if they are attacking it
//====================
void Player::AdjustAnglesForAttack
   (
   void
   )

   {
   /*
   Vector dir;
   Vector newAngles;
   Vector moveToAngles;

   if ( FindEnemyInFOV( 180, 1000 ) ) 
      {
      G_DrawCoordSystem( origin, dir,dir,dir,100 );

      if ( buttons & ( BUTTON_ATTACKRIGHT|BUTTON_ATTACKLEFT ) )
         {
         // Adjust for a percentage of the total
         float deltayaw = AngleSubtract( dir.toYaw(), v_angle[YAW] );

         if ( fabs( deltayaw ) > 5 )
            {
            v_angle[YAW] += deltayaw * 0.1f;
     		   client->ps.delta_angles[YAW] += ANGLE2SHORT( deltayaw * 0.1f );
            }
         }
      }
      */
   }

//====================
//ActivateNewWeapon
//====================
void Player::ActivateNewWeapon
   (
   Event *ev
   )

   {
   // Change the weapon to the currently active weapon as specified by useWeapon
   ChangeWeapon( newActiveWeapon.weapon, newActiveWeapon.hand );   
   
   // Check for water and ammo
   UpdateWeapons();

   // Clear out the newActiveWeapon
   ClearNewActiveWeapon();

   // Clear out the holstered weapons
   holsteredWeapons[WEAPON_LEFT]  = NULL;
   holsteredWeapons[WEAPON_RIGHT] = NULL;
   holsteredWeapons[WEAPON_DUAL]  = NULL;

   // let the player know that our weapons are not holstered
   WeaponsNotHolstered();
   }

//====================
//DeactivateWeapon
//====================
void Player::DeactivateWeapon
   (
   Event *ev
   )

   {
   // Deactivate the weapon
   weaponhand_t hand;
   str   side;

   side = ev->GetString( 1 );

   hand = WeaponHandNameToNum( side );

   if ( hand == WEAPON_ERROR )
      return;

   Sentient::DeactivateWeapon( hand );

   if ( !GetActiveWeapon( WEAPON_LEFT ) && !GetActiveWeapon( WEAPON_RIGHT ) && !GetActiveWeapon( WEAPON_DUAL ) )
      {
      // let the player know our weapons are holstered
      WeaponsHolstered();
      }
   }

//====================
//PutawayWeapon
//====================
void Player::PutawayWeapon
	(
	Event *ev
	)

	{
   Weapon * weapon;
   weaponhand_t hand;
   str   side;

   side = ev->GetString( 1 );

   hand = WeaponHandNameToNum( side );

   if ( hand == WEAPON_ERROR )
      return;

   weapon = GetActiveWeapon( hand );

   if ( weapon->isSubclassOf( Weapon ) )
      {
      weapon->RandomAnimate( "putaway" );
      }
	}


//====================
//useWeapon
//====================
void Player::useWeapon
	(
	const char     *weaponname,
   weaponhand_t   hand
	)

	{
   Weapon *weapon;

   weapon = ( Weapon * )FindItem( weaponname );

   // Check to see if player has the weapon
   if ( !weapon )
      {
      warning( "Player::useWeapon", "Player does not have weapon %s", weaponname );
      return;
      }

   useWeapon( weapon, hand );
   }

void Player::useWeapon
   (
   Weapon         *weapon,
   weaponhand_t   hand
   )

   {
   Weapon * activeWeapon;

   if ( !weapon )
      {
      warning( "Player::useWeapon", "Null weapon used.\n" );
      return;
      }

   // Check to see if we are already in the process of using a new weapon.
   if ( newActiveWeapon.weapon )
      {
      return;
      }

   // Check to see if weapon has ammo and if useNoAmmo is allowed
   if ( !weapon->HasAmmo( FIRE_PRIMARY ) && !weapon->HasAmmo( FIRE_ALTERNATE ) && !weapon->GetUseNoAmmo() )
      {
      Sound( "snd_noammo" );
      return;
      }

   // Check to see if the hand is allowed to have that weapon

   // WEAPON_ANY can be used in WEAPON_LEFT or WEAPON_RIGHT but not as a WEAPON_DUAL, so check for that first
   if ( ( hand == WEAPON_DUAL ) && ( weapon->GetHand() != hand ) )
      {
      warning( "Player::useWeapon", "Weapon %s is not allowed in %s", weapon->getName().c_str(), WeaponHandNumToName( hand ) );
      return;      
      }
   else if ( ( weapon->GetHand() != WEAPON_ANY ) && ( weapon->GetHand() != hand ) )
      {
      warning( "Player::useWeapon", "Weapon %s is not allowed in %s", weapon->getName().c_str(), WeaponHandNumToName( hand ) );
      return;
      }

   // If the weapon we are wielding is a WEAPON_DUAL, then put away the left and right ones
   if ( weapon->GetHand() == WEAPON_DUAL )
      {
      activeWeapon = GetActiveWeapon( WEAPON_LEFT );   
      if ( activeWeapon )
         activeWeapon->PutAway();
      activeWeapon = GetActiveWeapon( WEAPON_RIGHT );   
      if ( activeWeapon )
         activeWeapon->PutAway();
      }

   // Check to see if a WEAPON_DUAL is being used and put it away if needed
   activeWeapon = GetActiveWeapon( WEAPON_DUAL );
   
   if ( activeWeapon )
      {
      activeWeapon->PutAway();
      // we just want to put the dual handed weapon away
      if ( activeWeapon == weapon )
         {
         return;
         }
      }

   // Now get the active weapon in the specified hand
   activeWeapon = GetActiveWeapon( hand );

   // Check to see if this weapon is already being used in this hand and just put it away and return
   if ( activeWeapon == weapon )
      {
      // Set the putaway flag to true.  The state machine will then play the correct animation to put away the active weapon
      activeWeapon->PutAway();
      return;
      }      
      
   // If activeWeapon is set, and it's not == weapon then put away this weapon
   if ( activeWeapon )
      {
      // Set the putaway flag to true.  The state machine will then play the correct animation to put away the active weapon
      activeWeapon->PutAway();
      }

   // Check to see if this weapon is being used in a different hand and put it away as well (if it's in a different hand)
   if ( IsActiveWeapon( weapon ) )  
      {
      weapon->PutAway();
      }

   // Set the newActiveWeapon as the weapon specified, the state machine will play the appropriate animation and
   // trigger when to attach it to the player model.
	newActiveWeapon.weapon = weapon;
   newActiveWeapon.hand   = hand;
   }

//====================
//SwordAttackEvent
//====================
void Player::SwordAttackEvent
   (
   Event *ev
   )

   {
   Weapon *weapon;
   weaponhand_t hand;

   Vector pos, forward, end;

   // Project a ray from the centroid out
   end = this->centroid + Vector( orientation[0] ) * 96;     

   hand = WeaponHandNameToNum( ev->GetString( 1 ) );

   if ( hand == WEAPON_ERROR )
      return;

   weapon = GetActiveWeapon( hand );

   if ( weapon && weapon->isSubclassOf( Sword ) )
      {
      Sword *sword = ( Sword * )weapon;

      SwordAttack( this->centroid, end, sword, this, damage_multiplier );
      }
   }

//====================
//SwipeOn
//====================
void Player::SwipeOn
   (
   Event *ev
   )

   {
   Weapon         *weapon;
   weaponhand_t   hand;
   int            water_required=0;

   hand = WeaponHandNameToNum( ev->GetString( 1 ) );

   if ( hand == WEAPON_ERROR )
      return;

   weapon = GetActiveWeapon( hand );
   if ( weapon && weapon->isSubclassOf( Sword ) )
      {
      Sword *sword = ( Sword * )weapon;

      water_required = sword->GetWaterRequired();
      }

   if ( weapon && ( water_power >= water_required ) )
      {
      weapon->RandomAnimate( "swipeon", NULL );
      }
   }

//====================
//SwipeOff
//====================
void Player::SwipeOff
   (
   Event *ev
   )

   {
   Weapon         *weapon;
   weaponhand_t   hand;
   int            water_required=0;

   hand = WeaponHandNameToNum( ev->GetString( 1 ) );

   if ( hand == WEAPON_ERROR )
      return;

   weapon = GetActiveWeapon( hand );
   if ( weapon && weapon->isSubclassOf( Sword ) )
      {
      Sword *sword = ( Sword * )weapon;

      water_required = sword->GetWaterRequired();
      }

   if ( weapon && ( water_power >= water_required ) )
      {
      weapon->RandomAnimate( "swipeoff", NULL );
      }
   }

//====================
//ActivateShield
//====================
void Player::ActivateShield
   (
   Event *ev
   )

   {
   shield_active = qtrue;
   }

//====================
//DeactivateShield
//====================
void Player::DeactivateShield
   (
   Event *ev
   )

   {
   shield_active = qfalse;
   }

//====================
//ShieldActive
//====================
qboolean Player::ShieldActive
   (
   void
   )

   {
   return shield_active;
   }

//====================
//LargeShieldActive
//====================
qboolean Player::LargeShieldActive
   (
   void
   )

   {
   Weapon *weapon;
   qboolean large_shield_active=false;
   
   weapon = GetActiveWeapon( WEAPON_LEFT );
   if ( weapon && !str::icmp( weapon->item_name, "LargeShield" ) )
      large_shield_active = true;

   return shield_active && large_shield_active;
   }



void Player::AcquireHeadTarget
   (
   void
   )

   {
   vec3_t mat[3];
	Entity *new_head_target;
	Entity *ent;
	Item	 *item;

	// Find a good target

	if ( left_arm_target )
		head_target = left_arm_target;
	else if ( right_arm_target )
		head_target = right_arm_target;
	else
		{
		AnglesToAxis( headAngles, mat );

		// Make sure not to look at items too long

		if ( look_at_time <= level.time && head_target && head_target->isSubclassOf( Item ) )
			{
			item = (Item *)(Entity *)head_target;
			item->has_been_looked_at = true;
			}

		// Get the new head target
		new_head_target = FindHeadTarget( this->centroid, mat[0], 160, 1000 );

      if ( !new_head_target )
			{
			head_target = NULL;
         return;
			}

		if ( new_head_target != head_target )
			{
			// If we were looking at an item and are not now, mark it as has been looked at

			if ( head_target && head_target->isSubclassOf( Item ) )
				{
				item = (Item *)(Entity *)head_target;
				item->has_been_looked_at = true;
				}

			// Set up new head target

			head_target = new_head_target;

			look_at_time = level.time + 5;

			// Mark items near this one as looked at

			if ( head_target && head_target->isSubclassOf( Item ) )
				{
				ent = findradius( NULL, head_target->origin, 50 ); 

				while( ent )
					{
					if ( ent != head_target && ent->isSubclassOf( Item ) )
						{
						item = (Item *)ent;
						item->has_been_looked_at = true;
						}

					ent = findradius( ent, head_target->origin, 50 );
					}
				}
			}
		}
   }
