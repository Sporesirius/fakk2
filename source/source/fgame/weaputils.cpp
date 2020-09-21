//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/weaputils.cpp                      $
// $Revision:: 124                                                            $
//   $Author:: Aldie                                                          $
//     $Date:: 7/30/00 3:00a                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/weaputils.cpp                           $
// 
// 124   7/30/00 3:00a Aldie
// Changed projectiles to not take damage
// 
// 123   7/29/00 4:00p Aldie
// Fixed flash players to use new fading
// 
// 122   7/28/00 6:58p Steven
// Fixed another infinite loop in MeleeAttack and made sure it will never
// happen again.
// 
// 121   7/27/00 10:55p Steven
// Added always give water stuff.
// 
// 120   7/24/00 6:06p Steven
// Fixed an infinite loop in MeleeAttack.
// 
// 119   7/22/00 1:24p Steven
// Took out some lightsword stuff and made damage taken stuff in BulletAttack
// actually get calculated correctly.
// 
// 118   7/21/00 3:46p Steven
// Only post a remove event if there is a life (for explosions).
// 
// 117   7/20/00 6:22p Steven
// Fixed a melee attack problem not setting the position correctly and fixed an
// explosion issue where some explosions were getting removed immediately when
// they were needed.
// 
// 116   7/20/00 3:46p Aldie
// Lots of fixes to the goo projectile
// 
// 115   7/19/00 9:52p Aldie
// Put ET_EVENTS back in.  They will get sent over once, and should get
// processed once on the client.
// 
// 114   7/17/00 6:59p Steven
// Added RemoveWhenStopped stuff and redid ricocheting bullets a little.
// 
// 113   7/13/00 5:41p Steven
// Fixed hit spawns.
// 
// 112   7/13/00 12:32p Steven
// Made G_TraceEntities find all entities at once instead of 1 at a time.
// 
// 111   7/11/00 8:04a Steven
// Made projectiles make noise (so the AI can hear) when they bounce.
// 
// 110   7/10/00 6:33p Aldie
// Added SVF_SENDONCE flag and water power for swiping determination
// 
// 109   7/10/00 5:10p Markd
// Swords no longer use water
// 
// 108   7/10/00 4:42p Aldie
// added SVF_SENDONCE flag
// 
// 107   7/05/00 6:14p Steven
// Added a damage multiplier for combos.
// 
// 106   7/03/00 10:25a Steven
// Fixed attack_min_height not allowing a value of 0.
// 
// 105   7/02/00 1:11p Steven
// Added means of death lightsword.
// 
// 104   7/01/00 2:02p Steven
// Made bouncing projectiles hit entities that takedamage regardless if they
// still have health and added knockback stuff to explosions.
// 
// 103   7/01/00 12:02p Steven
// Added electricsword means of death.
// 
// 102   6/30/00 5:00p Steven
// Added a way for projectiles to hit their owner without getting blocked by
// them when first shot.
// 
// 101   6/30/00 11:40a Steven
// Improved radius damage.
// 
// 100   6/29/00 6:24p Steven
// Made hitspawns not happen if weapon is not powered up.
// 
// 99    6/29/00 2:32p Steven
// Fixed some warnings.
// 
// 98    6/29/00 2:03p Steven
// Fixed and improved heatseekers.
// 
// 97    6/27/00 7:17p Aldie
// Added worldhitspawn
// 
// 96    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 95    6/20/00 4:26p Aldie
// Fixed victimlist for melee attacks
// 
// 94    6/13/00 6:46p Aldie
// Added some damage debug info.  Added an ignoreEnt for explosion events
// 
// 93    6/12/00 6:19p Aldie
// fix for projectile velocity
// 
// 92    6/08/00 3:55p Aldie
// Added goo
// 
// 91    6/07/00 6:54p Aldie
// Put the prethink function in the heatseek code
// 
// 90    6/07/00 4:16p Aldie
// Added clusterbombs, heatseeking, and drunk
// 
// 89    6/07/00 3:09p Steven
// In BulletAttack only add to damage done if victim is not immune to the
// damage.
// 
// 88    6/05/00 6:07p Markd
// made all projectiles CONTENTS_SHOOTABLE_ONLY
// 
// 87    6/05/00 5:54p Markd
// added owner velocity to projectiles
// 
// 86    6/01/00 7:45p Aldie
// Heatseeking and Drunkeness added to projectiles
// 
// 85    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 84    5/26/00 6:21p Steven
// Made MeleeAttack create a reasonable direction if none in attack.
// 
// 83    5/23/00 10:20a Steven
// Fixed a bug with the projectile flags (there is 2 flags variables).
// 
// 82    5/22/00 5:13p Aldie
// First version of soulsucker
// 
// 81    5/10/00 10:35a Steven
// Added a hit_dead bool to MeleeAttack and made it so the firesword means of
// death is changed to just sword if not powered.
// 
// 80    5/08/00 5:16p Markd
// fixed sounds on impact for weapons
// 
// 79    5/08/00 2:56p Markd
// fixed impact_flesh and impact_world sounds
// 
// 78    5/07/00 5:37p Markd
// made projectiles capable of dying
// 
// 77    5/06/00 10:40a Steven
// Made it so there is action level and means of death variables for each
// weapon mode.
// 
// 76    5/05/00 2:17p Steven
// Added means of death to weapons.
// 
// 75    5/04/00 4:12p Steven
// Tweaked the find world part of MeleeAttack a little.
// 
// 74    4/26/00 11:17a Steven
// Only consider something hit in melee attacks if it is a sentient and its
// still alive and made it so sparks would not be spawned in if you hit a dead
// body.
// 
// 73    4/25/00 10:52a Steven
// Made it so explosions don't hit entities that are not solid.
// 
// 72    4/24/00 7:07p Aldie
// Added alphablend mode to flash command
// 
// 71    4/24/00 3:17p Aldie
// Fixed crash bug when projectile is not found
// 
// 70    4/21/00 5:40p Steven
// Added something to inform actors when a projectile bounces off of them.
// 
// 69    4/20/00 5:45p Steven
// Made stun attacks always hit actors even if takedamage is false (they can
// still ignore it though).
// 
// 68    4/15/00 5:18p Aldie
// Added stun events and fixed yet another bug with Ammo and AutoPutaway
// 
// 67    4/15/00 4:24p Markd
// Fixed player turning
// 
// 66    4/13/00 5:46p Steven
// Added poo_explosion means of death for Vymish Mama.
// 
// 65    4/13/00 3:45p Aldie
// Added more flashbang support.  Added damage_type to entities used to specify
// what type of damage they take.
// 
// 64    4/12/00 6:56p Steven
// Added lifedrain means of death.
// 
// 63    4/11/00 4:01p Steven
// Added attack_min_height to MeleeAttack.
// 
// 62    4/11/00 3:08p Steven
// Added a warning in ProjectileAttack if the passed in tiki is not of class
// Projectile.
// 
// 61    4/10/00 6:08p Steven
// Fixed a trace mask problem and added a check against a possible infinite
// loop.
// 
// 60    4/10/00 2:38p Markd
// eliminated the use of bg_public.h in some files
// 
// 59    4/08/00 4:39p Aldie
// Fix projectile attack spawning
// 
// 58    4/08/00 3:12p Aldie
// Added scale to flash_radius
// 
// 57    4/08/00 2:49p Aldie
// New crossbow bolt implementation
// 
// 56    4/08/00 11:58a Aldie
// Added type to FlashPlayers
// 
// 55    4/07/00 6:00p Aldie
// Added flashing and fixed radius damage for explosions
// 
// 54    4/07/00 5:15p Steven
// Made it so MeleeAttack would hit anything that can take damage not just
// Sentients.
// 
// 53    4/05/00 6:17p Steven
// Added in real support for gravity based projectiles.
//  
// 52    4/04/00 5:26p Markd
// moved static array from header into c file
// 
// 51    4/01/00 3:45p Markd
// added FL_TOUCH_TRIGGERS flag and implementation
// 
// 50    3/31/00 4:58p Steven
// Fixed it so it determines correctly if projectiles and bullets should bounce
// off an actor or not.
// 
// 49    3/30/00 6:24p Steven
// Added bullet ricocheting stuff.
// 
// 48    3/30/00 2:48p Steven
// Added knockback stuff.
// 
// 47    3/30/00 2:09p Aldie
// Added hitspawn command
// 
// 46    3/11/00 11:37a Steven
// Moved all actor booleans to 1 actor flags variable and made it so when a
// projectile bounces off an actor the owner is removed so that the owner can
// now be damaged.
// 
// 45    3/07/00 4:58p Steven
// Added projectiles bouncing off of certain actors.
// 
// 44    3/07/00 12:11p Steven
// Cleaned up means of death strings.
// 
// 43    3/04/00 5:08p Steven
// Added radius, damage_every_frame, and constant_damage to explosions.
// 
// 42    3/03/00 5:26p Steven
// Added fast_bullet stuff.
// 
// 41    2/28/00 6:33p Aldie
// Added more advanced pain state checks
// 
// 40    2/23/00 11:45a Steven
// Now pass in meansOfDeath_t type instead of the string.
// 
// 39    2/22/00 11:30a Steven
// Added means of death MOD_BULLET.
// 
// 38    2/09/00 2:59p Steven
// Fixed up some BroadcastSound issues with the weapons.
// 
// 37    2/07/00 7:38p Aldie
// Fixed swiping, also various weapons fixes for sword and for sling
// 
// 36    2/04/00 7:28p Aldie
// Combat code - blocking and combos
// 
// 35    2/04/00 3:11p Aldie
// Changed sword attack method for water usage
// 
// 34    2/01/00 5:28p Aldie
// More updates for auto aiming
// 
// 33    1/29/00 6:17p Aldie
// Fixed some problems when state doesn't exist.
// 
// 32    1/29/00 2:48p Aldie
// Added impact mark functionality and Decal class
// 
// 31    1/22/00 5:08p Steven
// Improved melee and sword attacks a lot.
// 
// 30    1/22/00 1:54p Markd
// fixed impact sparks and stopped sword from hurting script objects that could
// not be hurt
// 
// 29    1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 28    1/19/00 7:46p Aldie
// Fixed func_spawns of various types and removed some unused misc classes
// 
// 27    1/19/00 4:03p Aldie
// Added chargespeed flag
// 
// 26    1/19/00 12:10p Aldie
// Added some chargeup functionality
// 
// 25    1/19/00 10:23a Steven
// Added a sling means of death.
// 
// 24    1/14/00 5:07p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 23    1/11/00 6:41p Markd
// Removed fulltrace code from the game
// 
// 22    1/06/00 7:02p Steven
// Added knockback to the player's sword attack.
// 
// 21    1/06/00 4:39p Markd
// fixed tiki file name
// 
// 20    1/05/00 7:28p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 19    1/05/00 6:45p Steven
// Fixed the start and end point being backwards in a trace command.
// 
// 18    12/22/99 5:17p Steven
// Projectiles now notify actors that are in their path (used to allow actors
// to move out of the way of projectiles).
// 
// 17    12/07/99 6:09p Aldie
// Added weapon charging
// 
// 16    11/12/99 6:23p Steven
// Added an attack_vector to melee attacks.
// 
// 15    11/12/99 3:15p Aldie
// Added bouncesound
// 
// 14    11/11/99 6:40p Aldie
// Added some grenade type functionality
// 
// 13    11/10/99 6:12p Steven
// Added means of death to melee attacks and added new sting means of death.
// 
// 12    11/05/99 5:24p Steven
// Added attack_width to melee attacks.
// 
// 11    11/01/99 6:13p Steven
// Added flesh impact sound to sword hit.
// 
// 10    10/22/99 11:29a Steven
// Fixed another beam issue.
// 
// 9     10/22/99 11:23a Steven
// Fixed a crash bug dealing with beams on projectiles.
// 
// 8     10/21/99 2:51p Aldie
// Added some more beam functions
// 
// 7     10/14/99 5:30p Aldie
// Changed spark to Animate instead of Entity
// 
// 6     10/13/99 4:44p Steven
// Added some broadcast sounds.
// 
// 5     10/02/99 6:51p Markd
// Put in backend work for event documentation and fixed a lot of event
// documentation bugs
// 
// 4     9/30/99 1:49p Aldie
// Documentation of commands
// 
// 3     9/16/99 11:19a Markd
// Continuing merge of code, not functional yet but closer
// 
// 2     9/13/99 4:22p Jimdose
// merge
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 30    9/02/99 6:08p Steven
// Doubled the kickback from melee attacks due to all damage values being made
// smaller.
// 
// 29    9/02/99 11:05a Aldie
// removed knockback from radius damage
// 
// 28    9/01/99 9:14p Markd
// added a stopanimating event to projectiles
// 
// 27    9/01/99 9:08p Markd
// added animate once support
// 
// 26    9/01/99 5:46p Aldie
// Fixed some weapon stuff for ECTS
// 
// 25    9/01/99 5:38p Aldie
// Added MASK_ECTS_HACK for projectiles and swords
// 
// 24    9/01/99 3:55p Aldie
// Added a sparkhit
// 
// 23    9/01/99 12:45p Aldie
// Fix for crash when dumping
// 
// 22    9/01/99 11:08a Aldie
// rearranged the explosion init
// 
// 21    8/31/99 8:46p Aldie
// Fix for crossbow bolt
// 
// 20    8/31/99 8:43p Steven
// Took out sword knockback temporarily.
// 
// 19    8/31/99 7:26p Steven
// Fixed bug where 2 explosions were created instead of just 1.
// 
// 18    8/31/99 2:45p Steven
// Added sword and plasma means of death.
// 
// 17    8/28/99 11:45a Steven
// Removed global from sound function calls.
// 
// 16    8/25/99 6:54p Steven
// Added drown means of death.
// 
// 15    8/25/99 11:08a Aldie
// Added in impact sounds for projectiles
// 
// 14    8/18/99 3:29p Jimdose
// added cylindrical collision detection
// 
// 13    8/16/99 10:32a Steven
// Tweaked melee a little.
// 
// 12    8/11/99 5:57p Steven
// Added melee attacks and acid means of death.
// 
// 11    8/03/99 6:10p Steven
// Added means of death stuff to weapons.
// 
// 10    8/03/99 3:39p Aldie
// Removed some parms from ev_remove
// 
// 9     8/02/99 3:45p Steven
// Fixed some minor bugs with explosions.
// 
// 8     7/30/99 6:24p Aldie
// Updated weapons and utils to use new methods
// 
// 7     7/29/99 7:38p Aldie
// Updated weapons to new system
// 
// 6     7/23/99 3:27p Aldie
//
// DESCRIPTION:
// General Weapon Utility Functions

#include "weaputils.h"
#include "specialfx.h"
#include "sentient.h"
#include "actor.h"
#include "decals.h"
#include "weapon.h"
#include "player.h"

static void FlashPlayers
   (
   Vector   org,
   float    r,
   float    g, 
   float    b,
   float    a,
   float    rad,
   float    time,
   int      type
   );

qboolean MeleeAttack
   (
   Vector pos,
   Vector end,
   float damage,
   Entity *attacker,
	meansOfDeath_t means_of_death,
	float attack_width,
	float attack_min_height,
	float attack_max_height,
	float knockback,
	qboolean hit_dead,
   Container<Entity *>*victimlist
   )

   {
	trace_t trace;
   Entity *victim;
   Vector dir;
	float world_dist;
	Vector new_pos;
	Entity *skip_ent;
	qboolean hit_something = false;
	Vector mins;
	Vector maxs;
	Container<Entity *> potential_victimlist;
	int i;
	int num_traces;


	/* if ( attack_width == 0 )
		attack_width = 15;
	if ( attack_min_height == 0 )
		attack_min_height = -15;
	if ( attack_max_height == 0 )
		attack_max_height = 15; */

	// See how far the world is away

	dir = end - pos;
	world_dist = dir.length();

	new_pos = pos;

	skip_ent = attacker;

	num_traces = 0;

	while( new_pos != end )
		{
		trace = G_Trace( pos, vec_zero, vec_zero, end, skip_ent, MASK_SOLID, false, "MeleeAttack - World test" );

		num_traces++;

		if ( trace.fraction < 1 )
			{
			if ( ( trace.entityNum == ENTITYNUM_WORLD ) || ( trace.ent && trace.ent->entity && !trace.ent->entity->takedamage ) )
				{
				dir = trace.endpos - pos;
				world_dist = dir.length();
				break;
				}
			else
				{
				// Make sure we don't go backwards any in our trace
				if ( Vector( new_pos - pos ).length() + 0.001 >= Vector( trace.endpos - pos ).length() )
					break;

				if ( num_traces > 10 )
					{
					// We have done too many traces, stop here
					dir = trace.endpos - pos;
					world_dist = dir.length();
					break;
					}

				new_pos = trace.endpos;

				if ( trace.ent )
					skip_ent = trace.ent->entity;
				}
			}
		else
			{
			break;
			}
		}

	// Find things hit

	dir = end - pos;
	dir.normalize();
	end = pos + dir * world_dist;

	victim = NULL;

	mins = Vector( -attack_width, -attack_width, attack_min_height );
	maxs = Vector( attack_width, attack_width, attack_max_height );

	G_TraceEntities( pos, mins, maxs, end, &potential_victimlist, MASK_MELEE );

	for( i = 1 ; i <= potential_victimlist.NumObjects() ; i++ )
		{
		victim = potential_victimlist.ObjectAt( i );

		if ( victim && victim->takedamage && victim != attacker )
			{	
			dir = end - pos;
			dir.normalize();

			if ( dir == vec_zero )
				{
				dir = victim->centroid - pos;
				dir.normalize();
				}

			if ( victim->isSubclassOf( Sentient ) && victim->health > 0 )
				hit_something = true;


         if ( victim->health > 0 || hit_dead )
            {
				if ( victimlist && victim->isSubclassOf( Sentient ) && victim->health > 0 )
               victimlist->AddObject( victim );

				victim->Damage( attacker, attacker, damage, pos, dir, vec_zero, knockback, 0, means_of_death );
            }
			}
		}

	return hit_something;
   }

#define DEFAULT_SWORD_DAMAGE 10
#define DEFAULT_SWORD_KNOCKBACK 50

qboolean SwordAttack
   (
   Vector pos,
   Vector end,
   Sword  *sword,
   Entity *attacker,
	float damage_multiplier
   )

   {
   trace_t  trace;
   Entity   *victim;
   Vector   dir;
   float    damage;
   int      waterUsed=0;
   Player   *player=NULL;
	float		knockback;
	meansOfDeath_t meansofdeath;
	qboolean	water_attack;


	meansofdeath = sword->GetMeansOfDeath( FIRE_PRIMARY );

	water_attack = false;

   if ( attacker->isSubclassOf( Player ) )
      {
      player = ( Player * )attacker;

      // Use up water if required and do more powerful attack
      if ( sword->GetWaterRequired() && ( player->GetWaterPower() >= sword->GetWaterRequired() ) )
         {
         damage    = sword->GetWaterDamage();
         // swords no longer use water
         // waterUsed = sword->GetWaterRequired();
			knockback = sword->GetWaterKnockback();
			water_attack = true;
         }
      else // Not enough power, do basic damage
         {
         damage    = sword->GetBasicDamage();
			knockback = sword->GetBasicKnockback();

			if ( meansofdeath == MOD_FIRESWORD || meansofdeath == MOD_ELECTRICSWORD )
				meansofdeath = MOD_SWORD;
         }
      }
   else
      {
      damage    = DEFAULT_SWORD_DAMAGE;
		knockback = DEFAULT_SWORD_KNOCKBACK;
      }

	damage *= damage_multiplier;

   Container<Entity *>victimlist;

	if ( !MeleeAttack( pos, end, damage, attacker, meansofdeath, 15, -45, 45, knockback, true, &victimlist ) )
		{
		trace = G_Trace( pos, Vector( -8,-8,-8 ), Vector( 8,8,8 ), end, attacker, MASK_MELEE, false, "SwordAttack" );

		victim = G_GetEntity( trace.entityNum );

		if ( !victim ) 
			return false;
			
		if ( victim == world || ( victim->takedamage == DAMAGE_NO ) )
			{
         vec3_t newangles;

			vectoangles( trace.plane.normal, newangles );
         sword->WorldHitSpawn( FIRE_PRIMARY, trace.endpos, newangles, 0.1 );
      
	      str realname = sword->GetRandomAlias( "impact_world" );
         if ( realname.length() > 1 )
		      sword->Sound( realname, CHAN_VOICE );
			}
		}
	else
		{
      int i;
		str realname;

      // Use up water if we have it
      if ( player && waterUsed )
         player->SetWaterPower( player->GetWaterPower() - waterUsed );

		if ( water_attack )
			{   
			// Do a hitspawn on all the victims
			for ( i=1; i<=victimlist.NumObjects(); i++ )
				{        
				sword->HitSpawn( victimlist.ObjectAt( i )->centroid );
				}
			}

		if ( water_attack )
			realname = sword->GetRandomAlias( "impact_powered" );
		else
			realname = sword->GetRandomAlias( "impact_flesh" );

      if ( realname.length() > 1 )
		   sword->Sound( realname, CHAN_VOICE );
		return true;
		}

   return false;
   }

Event EV_Projectile_Speed
   (
   "speed",
   EV_DEFAULT,
   "f",
   "projectileSpeed",
   "set the speed of the projectile"
   );
Event EV_Projectile_MinSpeed
   (
   "minspeed",
   EV_DEFAULT,
   "f",
   "minspeed",
   "set the minimum speed of the projectile (this is for charge up weapons)"
   );
Event EV_Projectile_ChargeSpeed
   (
   "chargespeed",
   EV_DEFAULT,
   NULL,
   NULL,
   "set the projectile's speed to be determined by the charge time"
   );
Event EV_Projectile_Damage
   (
   "hitdamage",
   EV_DEFAULT,
   "f",
   "projectileHitDamage",
   "set the damage a projectile does when it hits something"
   );
Event EV_Projectile_Life
   (
   "life",
   EV_DEFAULT,
   "f",
   "projectileLife",
   "set the life of the projectile"
   );
Event EV_Projectile_MinLife
   (
   "minlife",
   EV_DEFAULT,
   "f",
   "minProjectileLife",
   "set the minimum life of the projectile (this is for charge up weapons)"
   );
Event EV_Projectile_ChargeLife
   (
   "chargelife",
   EV_DEFAULT,
   NULL,
   NULL,
   "set the projectile's life to be determined by the charge time"
   );
Event EV_Projectile_Knockback
   (
   "knockback", 
   EV_DEFAULT,
   "f",
   "projectileKnockback",
   "set the knockback of the projectile when it hits something"
   );
Event EV_Projectile_DLight
   (
   "dlight",
   EV_DEFAULT,
   "ffff",
   "red green blue intensity",
   "set the color and intensity of the dynamic light on the projectile"
   );
Event EV_Projectile_Avelocity
   (
   "avelocity",
   EV_DEFAULT,
   "SFSFSF",
   "[random|crandom] yaw [random|crandom] pitch [random|crandom] roll",
   "set the angular velocity of the projectile"
   );
Event EV_Projectile_MeansOfDeath
   (
   "meansofdeath",
   EV_DEFAULT,
   "s",
   "meansOfDeath",
   "set the meansOfDeath of the projectile"
   );
Event EV_Projectile_BeamCommand
   (
   "beam",
   EV_DEFAULT,
   "sSSSSSS",
   "command arg1 arg2 arg3 arg4 arg5 arg6",
   "send a command to the beam of this projectile"
   );
Event EV_Projectile_UpdateBeam
   (
   "updatebeam",
   EV_DEFAULT,
   NULL,
   NULL,
   "Update the attached beam"
   );
Event EV_Projectile_BounceTouch
   (
   "bouncetouch",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the projectile bounce when it hits a non-damageable solid"
   );
Event EV_Projectile_BounceSound
   (
   "bouncesound",
   EV_DEFAULT,
   NULL,
   NULL,
   "Set the name of the sound that is played when the projectile bounces"
   );
Event EV_Projectile_Explode
   (
   "explode",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the projectile explode"
   );
Event EV_Projectile_ImpactMarkShader
   (
   "impactmarkshader",
   EV_DEFAULT,
   "s",
   "shader",
   "Set the impact mark of the shader"
   );
Event EV_Projectile_ImpactMarkRadius
   (
   "impactmarkradius",
   EV_DEFAULT,
   "f",
   "radius",
   "Set the radius of the impact mark"
   );
Event EV_Projectile_ImpactMarkOrientation
   (
   "impactmarkorientation",
   EV_DEFAULT,
   "f",
   "degrees",
   "Set the orientation of the impact mark"
   );
Event EV_Projectile_SetExplosionModel
   (
   "explosionmodel",
   EV_DEFAULT,
   "s",
   "modelname",
   "Set the modelname of the explosion to be spawned"
   );
Event EV_Projectile_SetAddVelocity
   (
   "addvelocity",
   EV_DEFAULT,
   "fff",
   "velocity_x velocity_y velocity_z",
   "Set a velocity to be added to the projectile when it is created"
   );
Event EV_Projectile_AddOwnerVelocity
   (
   "addownervelocity",
   EV_DEFAULT,
   "b",
   "bool",
   "Set whether or not the owner's velocity is added to the projectile's velocity"
   );
Event EV_Projectile_HeatSeek
   (
   "heatseek",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the projectile heat seek"
   );
Event EV_Projectile_Drunk
   (
   "drunk",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the projectile drunk"
   );
Event EV_Projectile_Prethink
   (
   "prethink",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the projectile think to update it's velocity"
   );
Event EV_Projectile_SetCanHitOwner
   (
   "canhitowner",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the projectile be able to hit its owner"
   );
Event EV_Projectile_ClearOwner
   (
   "clearowner",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the projectile be able to hit its owner now"
   );
Event EV_Projectile_RemoveWhenStopped
   (
   "removewhenstopped",
   EV_DEFAULT,
   NULL,
   NULL,
   "Make the projectile get removed when it stops"
   );


CLASS_DECLARATION( Animate, Projectile, NULL )
	{
      { &EV_Touch,                              Touch },
      { &EV_Projectile_Speed,                   SetSpeed },
      { &EV_Projectile_MinSpeed,                SetMinSpeed },
      { &EV_Projectile_ChargeSpeed,             SetChargeSpeed },
      { &EV_Projectile_Damage,                  SetDamage },
      { &EV_Projectile_Life,                    SetLife },
      { &EV_Projectile_MinLife,                 SetMinLife },
      { &EV_Projectile_ChargeLife,              SetChargeLife },
      { &EV_Projectile_Knockback,               SetKnockback },
      { &EV_Projectile_DLight,                  SetDLight },
      { &EV_Projectile_Avelocity,               SetAvelocity },
		{ &EV_Projectile_MeansOfDeath,            SetMeansOfDeath },
      { &EV_Projectile_BounceTouch,             SetBounceTouch },
      { &EV_Projectile_BounceSound,             SetBounceSound },
      { &EV_Projectile_BeamCommand,             BeamCommand },
      { &EV_Projectile_UpdateBeam,              UpdateBeam },
      { &EV_Projectile_Explode,                 Explode },
      { &EV_Projectile_ImpactMarkShader,        SetImpactMarkShader },
      { &EV_Projectile_ImpactMarkRadius,        SetImpactMarkRadius },
      { &EV_Projectile_ImpactMarkOrientation,   SetImpactMarkOrientation },
      { &EV_Projectile_SetExplosionModel,       SetExplosionModel },
      { &EV_Projectile_SetAddVelocity,          SetAddVelocity },
      { &EV_Projectile_AddOwnerVelocity,        AddOwnerVelocity },
      { &EV_Projectile_HeatSeek,		      	   HeatSeek },
      { &EV_Projectile_Drunk,		          	   Drunk },
      { &EV_Projectile_Prethink,		      	   Prethink },
		{ &EV_Projectile_SetCanHitOwner,	      	SetCanHitOwner },
		{ &EV_Projectile_ClearOwner,		      	ClearOwner },
		{ &EV_Projectile_RemoveWhenStopped,     	RemoveWhenStopped },
      { &EV_Killed,		      	               Explode },
		{ &EV_Stop,			      	               Stopped },
		{ NULL, NULL }
	};

Projectile::Projectile()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

   m_beam                  = NULL;
   speed                   = 0;
   minspeed                = 0;
   damage                  = 0;
   life                    = 5;
   knockback               = 0;
   dlight_radius           = 0;
   dlight_color            = Vector( 1,1,1 );     
   avelocity               = Vector( 0,0,0 );
   mins                    = Vector( -1,-1,-1 );
   maxs                    = Vector( 1,1,1 );   
   meansofdeath            = (meansOfDeath_t )0;
   projFlags               = 0;
   gravity                 = 0;
   impactmarkradius        = 10;
   charge_fraction         = 1.0;
   target                  = NULL;
   addownervelocity        = qtrue;
   drunk                   = qfalse;
	can_hit_owner				= false;
	remove_when_stopped		= false;
   takedamage              = DAMAGE_NO;

   // make this shootable but non-solid on the client
  	setContents( CONTENTS_SHOOTABLE_ONLY );

   //
   // touch triggers by default
   //
   flags |= FL_TOUCH_TRIGGERS;
   }

float Projectile::ResolveMinimumDistance
	(
	Entity *potential_target,
	float currmin
	)

   {
   float		currdist;
	float		dot;
	Vector	angle;
	Vector	delta;
	Vector	norm;
	float		sine = 0.4f;

	delta = potential_target->centroid - this->origin;

	norm = delta;
	norm.normalize();

	// Test if the target is in front of the missile
	dot = norm * orientation[ 0 ];
	if ( dot < 0 )
		{
		return currmin;
		}

	// Test if we're within the rocket's viewcone (45 degree cone)
	dot = norm * orientation[ 1 ];
	if ( fabs( dot ) > sine )
		{
		return currmin;
		}

	dot = norm * orientation[ 2 ];
	if ( fabs( dot ) > sine )
		{
		return currmin;
		}

	currdist = delta.length();
	if ( currdist < currmin )
		{
		currmin = currdist;
		target = potential_target;
		}

	return currmin;
	}

float Projectile::AdjustAngle
	(
	float maxadjust,
	float currangle,
	float targetangle
	)

   {
   float dangle;
	float magangle;

	dangle = currangle - targetangle;

	if ( dangle )
		{
		magangle = ( float )fabs( dangle );

		while( magangle >= 360.0f )
			{
			magangle -= 360.0f;
			}

		if ( magangle < maxadjust )
			{
			currangle = targetangle;
			}
		else 
			{
			if ( magangle > 180.0f  )
				{
				maxadjust = -maxadjust;
				}
			if ( dangle > 0 )
				{
				maxadjust = -maxadjust;
				}
			currangle += maxadjust;
			}
		}

	while( currangle >= 360.0f )
		{
		currangle -= 360.0f;
		}

	while( currangle < 0.0f )
		{
		currangle += 360.0f;
		}

	return currangle;
	}

void Projectile::Drunk
   (
   Event *ev
   )

   {
   drunk = ev->GetBoolean( 1 );
   }

void Projectile::HeatSeek
	(
	Event *ev
	)

	{
	float		mindist;
	Entity	*ent;
	trace_t  trace;
	Vector	delta;
	Vector	v;
   int      n;
   int      i;

   if ( ( !target ) || ( target == world ) )
		{
		mindist = 8192.0f;

	   n = SentientList.NumObjects();
	   for( i = 1; i <= n; i++ )
		   {
		   ent = SentientList.ObjectAt( i );
			if ( ent->entnum == owner )
				{
				continue;
				}

			if ( ( ( ent->takedamage != DAMAGE_AIM ) || ( ent->health <= 0 ) ) && !( edict->svflags & SVF_MONSTER ) )
				{
				continue;
				}

			trace = G_Trace( this->origin, vec_zero, vec_zero, ent->centroid, this, MASK_SHOT, qfalse, "DrunkMissile::HeatSeek" );
			if ( ( trace.fraction != 1.0 ) && ( trace.ent != ent->edict ) )
				{
				continue;
				}
	
			mindist = ResolveMinimumDistance( ent, mindist );
			}
		}
	else 
		{
      float angspeed;

      delta = target->centroid - this->origin;
		v = delta.toAngles();

      angspeed = 5.0f;
		angles.x = AdjustAngle( angspeed, angles.x, v.x );
		angles.y = AdjustAngle( angspeed, angles.y, v.y );
		angles.z = AdjustAngle( angspeed, angles.z, v.z );
		}
   PostEvent( EV_Projectile_HeatSeek, 0.1 );
   PostEvent( EV_Projectile_Prethink, 0 );
	}

void Projectile::Prethink
	(
	Event *ev
	)

	{
	Vector end;

   if ( drunk )
   	angles += Vector( G_CRandom( 3 ), G_CRandom( 5 ), 0 );

   setAngles( angles );
   velocity = Vector( orientation[ 0 ] ) * speed;
	}

void Projectile::AddOwnerVelocity
   (
   Event *ev
   )

   {
   addownervelocity = ev->GetBoolean( 1 );
   }

void Projectile::SetAddVelocity
   (
   Event *ev
   )

   {
   addvelocity.x = ev->GetFloat( 1 );
   addvelocity.y = ev->GetFloat( 2 );
   addvelocity.z = ev->GetFloat( 3 );
   }

void Projectile::SetExplosionModel
   (
   Event *ev
   )

   {
   explosionmodel = ev->GetString( 1 );
   }

void Projectile::SetImpactMarkShader
   (
   Event *ev
   )

   {
   impactmarkshader = ev->GetString( 1 );
   }

void Projectile::SetImpactMarkRadius
   (
   Event *ev
   )

   {
   impactmarkradius = ev->GetFloat( 1 );
   }

void Projectile::SetImpactMarkOrientation
   (
   Event *ev
   )

   {
   impactmarkorientation = ev->GetString( 1 );
   }

void Projectile::Explode
   (
   Event *ev
   )

   {
   Entity *owner;
   Entity *ignoreEnt=NULL;

   if ( ev->NumArgs() == 1 )
      ignoreEnt = ev->GetEntity( 1 );
   
   // Get the owner of this projectile
   owner = G_GetEntity( this->owner );

   // If the owner's not here, make the world the owner
   if ( !owner )
      owner = world;

   takedamage = DAMAGE_NO;

   // Spawn an explosion model
   if ( explosionmodel.length() )
      {
      // Move the projectile back off the surface a bit so we can see
      // explosion effects.
      Vector dir, v;
      v = velocity;
	   v.normalize();	
      dir = v;
	   v = origin - v * 36;
      setOrigin( v );

      ExplosionAttack( v, owner, explosionmodel, dir, ignoreEnt );
      }

   CancelEventsOfType( EV_Projectile_UpdateBeam );

   // Kill the beam
   if ( m_beam )
	   {
	   m_beam->ProcessEvent( EV_Remove );
	   m_beam = NULL;
	   }

   // Remove the projectile
   PostEvent( EV_Remove, 0 );
   }

void Projectile::SetBounceTouch
   (
   Event *ev
   )

   {
   projFlags |= P_BOUNCE_TOUCH;
   setMoveType( MOVETYPE_BOUNCE );
   }

void Projectile::BeamCommand
   (
   Event *ev
   )

   {
   int i;

   if ( !m_beam )
      {
      m_beam = new FuncBeam;

      m_beam->setOrigin( this->origin );
      m_beam->Ghost( NULL );
      }
   
   Event *beamev = new Event( ev->GetToken( 1 ) );

   for( i=2; i<=ev->NumArgs(); i++ )
      {
      beamev->AddToken( ev->GetToken( i ) );
      }

   m_beam->ProcessEvent( beamev );
   PostEvent( EV_Projectile_UpdateBeam, level.frametime );
   }

void Projectile::UpdateBeam
   (
   Event *ev
   )

   {
   if ( m_beam )
      {
      m_beam->setOrigin( this->origin );
      PostEvent( EV_Projectile_UpdateBeam, level.frametime );
      }
   }

void Projectile::SetBounceSound
   (
   Event *ev
   )

   {
   bouncesound = ev->GetString( 1 );
   }

void Projectile::SetChargeLife
   (
   Event *ev
   )

   {
   projFlags   |= P_CHARGE_LIFE;
   }

void Projectile::SetMinLife
   (
   Event *ev
   )

   {
   minlife  = ev->GetFloat( 1 );
   projFlags   |= P_CHARGE_LIFE;
   }

void Projectile::SetLife
   (
   Event *ev
   )

   {
   life = ev->GetFloat( 1 );
   }

void Projectile::SetSpeed
   (
   Event *ev
   )

   {
   speed = ev->GetFloat( 1 );
   }

void Projectile::SetMinSpeed
   (
   Event *ev
   )

   {
   minspeed = ev->GetFloat( 1 );
   projFlags   |= P_CHARGE_SPEED;
   }

void Projectile::SetChargeSpeed
   (
   Event *ev
   )

   {
   projFlags   |= P_CHARGE_SPEED;
   }

void Projectile::SetAvelocity
   (
   Event *ev
   )

   {
   int i=1;
   int j=0;
   str vel;

   if ( ev->NumArgs() < 3 )
      {
      warning( "ClientGameCommandManager::SetAngularVelocity", "Expecting at least 3 args for command randvel" );
      }

   while ( j < 3 )
      {      
      vel = ev->GetString( i++ );
      if ( vel == "crandom" )
         {
         avelocity[j++] = ev->GetFloat( i++ ) * crandom();
         }
      else if ( vel == "random" )
         {
         avelocity[j++] = ev->GetFloat( i++ ) * random();
         }
      else
         {
         avelocity[j++] = atof( vel.c_str() );
         }
      }
   }

void Projectile::SetDamage
   (
   Event *ev
   )

   {
   damage = ev->GetFloat( 1 );
   }

void Projectile::SetKnockback
   (
   Event *ev
   )

   {
   knockback = ev->GetFloat( 1 );
   }

void Projectile::SetDLight
   (
   Event *ev
   )

   {
   dlight_color[0] = ev->GetFloat( 1 );
   dlight_color[1] = ev->GetFloat( 2 );
   dlight_color[2] = ev->GetFloat( 3 );
   dlight_radius   = ev->GetFloat( 4 );
   }

void Projectile::SetMeansOfDeath
   (
   Event *ev
   )

   {
	meansofdeath = (meansOfDeath_t )MOD_string_to_int( ev->GetString( 1 ) );
   }

void Projectile::DoDecal
   (
   void
   )

   {
   if ( impactmarkshader.length() )
      {
      Decal *decal = new Decal;
      decal->setShader( impactmarkshader );
      decal->setOrigin( level.impact_trace.endpos );
      decal->setDirection( level.impact_trace.plane.normal );
      decal->setOrientation( impactmarkorientation );
      decal->setRadius( impactmarkradius );
      }
   }

void Projectile::Touch
   (
   Event *ev
   )

   {
   Entity   *other;
   Entity   *owner;
   str      realname;

   // Other is what got hit
   other = ev->GetEntity( 1 );
	assert( other );

   // Don't touch teleporters
	if ( other->isSubclassOf( Teleporter ) )
		{
		return;
		}

   // Can't hit yourself with a projectile
	if ( other->entnum == this->owner )
		{
		return;
		}

   // Bouncy Projectile
   if ( ( projFlags & P_BOUNCE_TOUCH ) && !other->takedamage )
        //( !other->takedamage || other->health <= 0 ) )
      {
      // Play a bouncy sound
      if ( bouncesound.length() )
         this->Sound( bouncesound, CHAN_BODY );
		BroadcastSound();
      return;
      }

	// See if we should bounce off object
	if ( other->isSubclassOf( Actor ) )
		{
		Actor *act = (Actor *)other;

		if ( act->GetActorFlag( ACTOR_FLAG_BOUNCE_OFF ) && act->Immune( meansofdeath ) )
			{
			// Remove the owner so it can be hit after the bounce
			this->owner     = ENTITYNUM_NONE;
			edict->ownerNum = ENTITYNUM_NONE;

			if ( bouncesound.length() )
				Sound( bouncesound, CHAN_BODY );

			// Tell the actor something just bounced off of it

			Event *event = new Event( EV_Actor_BounceOff );
			event->AddVector( origin );
			act->PostEvent( event, 0 );
			return;
			}
		}

   // Make the projectile not solid
   setSolidType( SOLID_NOT );
   setMoveType( MOVETYPE_NONE );
   hideModel();
   
   // Remove it if we hit the sky
   if ( HitSky() )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

   // Do a decal
   DoDecal();

   // Get the owner of this projectile
   owner = G_GetEntity( this->owner );

   // If the owner's not here, make the world the owner
   if ( !owner )
      owner = world;

   if ( other->isSubclassOf( Sentient ) )
	   realname = this->GetRandomAlias( "impact_flesh" );
   else
	   realname = this->GetRandomAlias( "impact_world" );

   if ( realname.length() > 1 )
		this->Sound( realname, CHAN_VOICE );

   // Damage the thing that got hit
   if (other->takedamage)
      {
      other->Damage( this, 
                     owner,
                     damage,
                     origin,
                     velocity,
                     level.impact_trace.plane.normal,
                     knockback,
                     0,
                     meansofdeath
                    );
      }

	BroadcastSound();

   // Remove the projectile
   PostEvent( EV_Remove, 0 );

   // Call the explosion event
   Event *explEv;
   explEv = new Event( EV_Projectile_Explode );
   explEv->AddEntity( other );
   ProcessEvent( explEv );
   }

void Projectile::SetCanHitOwner
   (
   Event *ev
   )

   {
	can_hit_owner = true;
	}

void Projectile::ClearOwner
   (
   Event *ev
   )

   {
	this->owner     = ENTITYNUM_NONE;
	edict->ownerNum = ENTITYNUM_NONE;
	}

void Projectile::RemoveWhenStopped
   (
   Event *ev
   )

   {
	remove_when_stopped = true;
	}

void Projectile::Stopped
   (
   Event *ev
   )

   {
	if ( remove_when_stopped )
		PostEvent( EV_Remove, 0 );
	}

Event EV_Explosion_Radius
   (
   "radius",
   EV_DEFAULT,
   "f",
   "projectileRadius",
   "set the radius for the explosion"
   );
Event EV_Explosion_ConstantDamage
   (
   "constantdamage",
   EV_DEFAULT,
   NULL,
   NULL,
   "Makes the explosion do constant damage over the radius"
   );
Event EV_Explosion_DamageEveryFrame
   (
   "damageeveryframe",
   EV_DEFAULT,
   NULL,
   NULL,
   "Makes the explosion damage every frame"
   );
Event EV_Explosion_DamageAgain
   (
   "damageagain",
   EV_DEFAULT,
   NULL,
   NULL,
   "This event is generated each frame if explosion is set to damage each frame"
   );
Event EV_Explosion_Flash
   (
   "flash",
   EV_DEFAULT,
   "fffff",
   "time r g b radius",
   "Flash player screens"
   );
Event EV_Explosion_RadiusDamage
   (
   "radiusdamage",
   EV_DEFAULT,
   "f",
   "radiusDamage",
   "set the radius damage an explosion does"
   );


CLASS_DECLARATION( Projectile, Explosion, NULL )
   {
		{ &EV_Explosion_Radius,							SetRadius },
		{ &EV_Explosion_ConstantDamage,				SetConstantDamage },
		{ &EV_Explosion_DamageEveryFrame,			SetDamageEveryFrame },
		{ &EV_Explosion_DamageAgain,					DamageAgain },
      { &EV_Explosion_Flash,			 	      	SetFlash },
      { &EV_Explosion_RadiusDamage,		      	SetRadiusDamage },
      { NULL, NULL }
   };

Explosion::Explosion()
	{
   if ( LoadingSavegame )
      {
      // Archive function will setup all necessary data
      return;
      }

   radius               = 0;
	constant_damage      = false;
	damage_every_frame   = false;
   flash_time           = 0;
   flash_type           = 0;
   }

void Explosion::SetFlash
   (
   Event *ev
   )

   {
   flash_time     = ev->GetFloat( 1 );
   flash_r        = ev->GetFloat( 2 );
   flash_g        = ev->GetFloat( 3 );
   flash_b        = ev->GetFloat( 4 );
   flash_a        = ev->GetFloat( 5 );
   flash_radius   = ev->GetFloat( 6 );
   flash_type     = 0;

   if ( ev->NumArgs() > 6 ) 
      {
      str t = ev->GetString( 7 );
      
      if ( !t.icmp( "addblend" ) )
         flash_type = 1;
      else if ( !t.icmp( "alphablend" ) )
         flash_type = 0;
      }
   }

void Explosion::SetRadius
   (
   Event *ev
   )

   {
   radius = ev->GetFloat( 1 );
   }

void Explosion::SetRadiusDamage
   (
   Event *ev
   )

   {
   radius_damage = ev->GetFloat( 1 );
   }

void Explosion::SetConstantDamage
   (
   Event *ev
   )

   {
   constant_damage = true;
   }

void Explosion::SetDamageEveryFrame
   (
   Event *ev
   )

   {
   damage_every_frame = true;
   }

void Explosion::DamageAgain
   (
   Event *ev
   )
	{
	Entity *owner_ent;

	owner_ent = G_GetEntity( owner );
	RadiusDamage( this, owner_ent, radius_damage, NULL, meansofdeath, radius, knockback, constant_damage );

	PostEvent( EV_Explosion_DamageAgain, FRAMETIME );
	}

Projectile *ProjectileAttack
   (
   Vector         start,
   Vector         dir,
   Entity         *owner,
   str            projectileModel,
   float          fraction,
	float				real_speed
   )

   {
   Event          *ev;
   Projectile     *proj=NULL;
   float          newspeed,newlife;
   SpawnArgs      args;
   Entity         *obj;
   float          dot=0;

   if ( !projectileModel.length() )
      {
      gi.DPrintf( "ProjectileAttack : No model specified for ProjectileAttack" );
      return NULL;
      }

   args.setArg( "model", projectileModel );
   obj = args.Spawn();

   if ( !obj )
      {
      gi.DPrintf( "projectile model '%s' not found\n", projectileModel.c_str() );
      return NULL;
      }  

   if ( obj->isSubclassOf( Projectile ) ) 
      proj = ( Projectile * )obj;
	else
		gi.DPrintf( "%s is not of class projectile\n", projectileModel.c_str() );

   if ( !proj )
      return NULL;

   // Create a new projectile entity and set it off
   proj->setModel( projectileModel );
	proj->setMoveType( MOVETYPE_BOUNCE );   
   proj->CancelEventsOfType( EV_ProcessInitCommands );
   proj->ProcessInitCommands( proj->edict->s.modelindex );        
   proj->owner             = owner->entnum;
	proj->edict->ownerNum   = owner->entnum;
	proj->angles            = dir.toAngles();
   proj->charge_fraction   = fraction;
   
   if ( proj->projFlags & P_CHARGE_SPEED )
      {
      newspeed = proj->speed * fraction;

      if ( newspeed < proj->minspeed )
         newspeed = proj->minspeed;
      }
   else
      {
      newspeed = proj->speed;
      }

	if ( real_speed )
		newspeed = real_speed;
   
   if ( proj->addownervelocity )
      {
      dot = DotProduct( owner->velocity, dir );
      if ( dot < 0 )
         dot = 0;
      }

   proj->velocity = dir * ( newspeed + dot );   
   proj->velocity += proj->addvelocity;
   proj->setAngles( proj->angles );
	proj->setSolidType( SOLID_BBOX );

	proj->edict->clipmask = MASK_PROJECTILE;

	proj->setSize( proj->mins, proj->maxs );
   proj->setOrigin( start );
   proj->origin.copyTo( proj->edict->s.origin2 );

   if ( proj->m_beam )
      {
      proj->m_beam->setOrigin( start );
      proj->m_beam->origin.copyTo( proj->m_beam->edict->s.origin2 );
      }

   if ( proj->dlight_radius )
      {
      G_SetConstantLight( &proj->edict->s.constantLight,
                          &proj->dlight_color[0],
                          &proj->dlight_color[1],
                          &proj->dlight_color[2],
                          &proj->dlight_radius
                        );
      }

   // Calc the life of the projectile
   if ( proj->projFlags & P_CHARGE_LIFE )
      {
      newlife = proj->life * fraction;

      if ( newlife < proj->minlife )
         newlife = proj->minlife;
      }
   else
      {
      newlife = proj->life;
      }

   // Remove the projectile after it's life expires
   ev = new Event( EV_Projectile_Explode );
	proj->PostEvent( ev, newlife );

   proj->RandomAnimate( "idle", EV_StopAnimating );

	// If can hit owner clear the owner of this projectile in a second

	if ( proj->can_hit_owner )
		proj->PostEvent( EV_Projectile_ClearOwner, 1 );

	// Notify any actor that is in way of projectile
	Vector end_pos;
	trace_t trace;
	Event *event;
	Entity *victim;

	end_pos = dir * 1000 + start;
	trace = G_Trace( start, vec_zero, vec_zero, end_pos, owner, MASK_PROJECTILE, false, "ProjectileAttack" );

	if ( trace.entityNum != ENTITYNUM_NONE )
		{
		event = new Event( EV_ActorIncomingProjectile );
		event->AddEntity( proj );
		victim = G_GetEntity( trace.entityNum );
		victim->PostEvent( event, 0 );
		}

   return proj;
   }

float BulletAttack
   (
   Vector	start,
	Vector	dir,
   Vector   right,
   Vector   up,
	float    range,
   float  	damage,
   float    knockback,
   int      dflags,
   int      meansofdeath,
   Vector   spread,
   int      count,
   Entity   *owner
   )

   {
   Vector   end;
   int      i;
   trace_t  trace;
   Entity   *ent;
   float    damage_total = 0;
	float		original_value;
	float		new_value;

   for ( i=0; i<count; i++ )
      {
      end = start + dir * range +
	         right * G_CRandom() * spread.x + 
            up    * G_CRandom() * spread.y;
      
      trace = G_Trace( start, vec_zero, vec_zero, end, owner, MASK_SHOT, false, "BulletAttack" );
      
      if ( trace.ent )
         {
         ent = trace.ent->entity;

			// See if bullet should bounce off of entity

			if ( meansofdeath == MOD_BULLET && ent->isSubclassOf( Actor ) )
				{
				Actor *act = (Actor *)ent;
				Vector	real_dir;
				Vector	bounce_start;
				Vector angles;
				Vector left;
				Vector up;

				if ( act->GetActorFlag( ACTOR_FLAG_BOUNCE_OFF ) && act->Immune( meansofdeath ) )
					{
					// Play sound

					if ( owner )
						owner->Sound( "snd_ricochet", 0 );

					real_dir = trace.endpos - start;

					real_dir = real_dir * -1;

					angles = real_dir.toAngles();

					angles.AngleVectors( NULL, &left, &up );

					real_dir.normalize();
					real_dir *= range;

					real_dir += left * G_CRandom() * 100 + up * G_CRandom() * 100;

					bounce_start = trace.endpos;

					trace = G_Trace( bounce_start, vec_zero, vec_zero, bounce_start + real_dir, NULL, MASK_SHOT, false, "BulletAttack2" );

					// Add tracer

					if ( G_Random( 1 ) < .2 )
						{
						FuncBeam *beam = CreateBeam( NULL, "tracer", bounce_start, trace.endpos, 1, 1, .1, 0 );
						beam->PostEvent( EV_Remove, 1 );
						}

					if ( trace.ent )
						{
						ent = trace.ent->entity;

						if ( ent == world )
							{
							// Add bullet hole
							Decal *decal = new Decal;
							decal->setShader( "bullethole" );
							decal->setOrigin( trace.endpos );
							decal->setDirection( trace.plane.normal );
							decal->setOrientation( "random" );
							decal->setRadius( 2 );

							// Add smoke
							Animate *smoke = new Animate;

							smoke->setModel( "fx_bulletsmoke.tik" );
							smoke->setOrigin( trace.endpos );
							smoke->RandomAnimate( "idle" );
							smoke->PostEvent( EV_Remove, 2 );
							}
						}
					else
						{
						ent = NULL;
						}
					}
				}
         }
      else
         {
         ent = NULL;
         }

      if ( ent && ent->takedamage )
         {
         /* if ( !ent->deadflag )
            damage_total += damage;

			if ( ent->isSubclassOf( Sentient ) )
				{
				Sentient *sent = (Sentient *)ent;

				if ( sent->Immune( meansofdeath ) )
					damage_total = 0;
				} */

			// Get the original value of the victims health or water

			if ( meansofdeath == MOD_LIFEDRAIN )
				{
				if ( ent->isSubclassOf( Player ) )
					{
					Player *player = (Player *)ent;
					original_value = player->GetWaterPower();
					}
				else if ( ent->isSubclassOf( Actor ) )
					{
					Actor *act = (Actor *)ent;

					if ( act->GetActorFlag( ACTOR_FLAG_ALWAYS_GIVE_WATER ) )
						original_value = act->health;
					else
						original_value = act->water_level;
					}
				else
					{
					original_value = 0;
					}
				}
			else
				{
				original_value = ent->health;
				}

         ent->Damage( NULL,
                      owner,
                      damage,
                      trace.endpos,
                      dir,
                      trace.plane.normal,
                      knockback,
                      dflags,
                      meansofdeath );

			// Get the new value of the victims health or water

			if ( meansofdeath == MOD_LIFEDRAIN )
				{
				if ( ent->isSubclassOf( Player ) )
					{
					Player *player = (Player *)ent;
					new_value = player->GetWaterPower();
					}
				else if ( ent->isSubclassOf( Actor ) )
					{
					Actor *act = (Actor *)ent;

					if ( act->GetActorFlag( ACTOR_FLAG_ALWAYS_GIVE_WATER ) )
						new_value = act->health;
					else
						new_value = act->water_level;
					}
				else
					{
					new_value = 0;
					}
				}
			else
				{
				new_value = ent->health;
				}

			damage_total += original_value - new_value;
         
         }
      // Draw a debug trace line to show bullet fire  
      if ( g_showbullettrace->integer )
         G_DebugLine( start, end, 1,1,1,1 );
      }

	if ( damage_total > 0 )
		return damage_total;
	else
		return 0;
   }

void ExplosionAttack
   (
   Vector   pos,
   Entity   *owner,
   str      explosionModel,
   Vector   dir,
   Entity   *ignore,
   float    scale
   )

   {
	Explosion   *explosion;
	Event			*ev;


   if ( !owner )
      owner = world;

   if ( explosionModel.length() )
		{
   	explosion = new Explosion;

      // Create a new explosion entity and set it off
      explosion->setModel( explosionModel );

      explosion->setSolidType( SOLID_NOT );
      explosion->CancelEventsOfType( EV_ProcessInitCommands );

      // Process the INIT commands right away
      explosion->ProcessInitCommands( explosion->edict->s.modelindex );

      explosion->owner             = owner->entnum;
	   explosion->edict->ownerNum   = owner->entnum;
	   explosion->angles            = dir.toAngles();
      explosion->velocity          = dir * explosion->speed;
      explosion->edict->s.scale    = scale;
      explosion->setAngles( explosion->angles );
	   explosion->setMoveType( MOVETYPE_FLYMISSILE );
	   explosion->edict->clipmask = MASK_PROJECTILE;
	   explosion->setSize( explosion->mins, explosion->maxs );
      explosion->setOrigin( pos );
      explosion->origin.copyTo( explosion->edict->s.origin2 );

      if ( explosion->dlight_radius )
         {
         G_SetConstantLight( &explosion->edict->s.constantLight,
                             &explosion->dlight_color[0],
                             &explosion->dlight_color[1],
                             &explosion->dlight_color[2],
                             &explosion->dlight_radius
                           );
         }

      explosion->BroadcastSound();
      explosion->RandomAnimate( "idle", EV_StopAnimating );
    	
      RadiusDamage( explosion, 
                    owner,
                    explosion->radius_damage * scale,
                    ignore,
                    explosion->meansofdeath, 
                    explosion->radius * scale, 
						  explosion->knockback,
				        explosion->constant_damage
                  );

      if ( explosion->flash_radius )
         {
         FlashPlayers( explosion->origin, 
                       explosion->flash_r,
                       explosion->flash_g,
                       explosion->flash_b,
                       explosion->flash_a,
                       explosion->flash_radius * scale,
                       explosion->flash_time,
                       explosion->flash_type
                     );
         }

		if ( explosion->damage_every_frame )
			{
			explosion->PostEvent( EV_Explosion_DamageAgain, FRAMETIME );
			}

		// Remove explosion after the life has expired

		if ( explosion->life )
			{
			ev = new Event( EV_Remove );
			explosion->PostEvent( ev, explosion->life );
			}
		}
   }

void StunAttack
	(
   Vector   pos,
   Entity   *attacker,
   Entity   *inflictor,
   float    radius,
   float    time,
   Entity   *ignore
   )

	{
   Entity *ent;

   ent = findradius( NULL, inflictor->origin, radius );

	while( ent )
		{
		if ( ( ent != ignore ) && ( ( ent->takedamage ) || ent->isSubclassOf( Actor ) ) )
			{ 
         if ( inflictor->CanDamage( ent, attacker ) )
				{
            // Fixme : Add in knockback
            ent->Stun( time );
				}
			}
      ent = findradius( ent, inflictor->origin, radius );
		}
	}

void RadiusDamage
	(
	Entity   *inflictor,
	Entity   *attacker,
	float      damage,
	Entity   *ignore,
   int      mod,
	float		radius,
	float		knockback,
	qboolean	constant_damage
	)

	{
	float		points;
	Entity	*ent;
	Vector	org;
	Vector	dir;
	float		dist;
	float		rad;

	if ( radius )
		rad = radius;
	else
		rad = ( float )( damage + 60 );

   ent = findradius( NULL, inflictor->origin, rad );

	while( ent )
		{
		if ( ( ent != ignore ) && ( ent->takedamage ) && ent->edict->solid != SOLID_NOT )
			{
			if ( constant_damage )
				{
				points = damage;
				}
			else
				{
				org = ent->centroid;
				dir = org - inflictor->origin;

				dist = dir.length();

				points = damage - damage * ( dist / rad );

				knockback -= knockback * ( dist / rad );

				if ( points < 0 )
					points = 0;

				if ( knockback < 0 )
					knockback = 0;
				}

			if ( ent == attacker  )
				{
				points *= 0.5;
				}

			if ( points > 0 )
				{
            // Add this in for deathmatch maybe

            // Only players can use cover
				if ( !ent->isSubclassOf( Player ) || inflictor->CanDamage( ent, attacker ) )
					{
               ent->Damage( inflictor,
                            attacker,
                            points,
                            org,
                            dir,
                            vec_zero,
                            knockback,
                            DAMAGE_RADIUS,
                            mod
                          );
					}
				}
			}
      ent = findradius( ent, inflictor->origin, rad );
		}
	}


void FlashPlayers
   (
   Vector   org,
   float    r,
   float    g, 
   float    b,
   float    a,
   float    radius,
   float    time,
   int      type
   )

   {
   trace_t     trace;
   Vector      delta;
   float       length;
   Player      *player;
   gentity_t   *ed;
   int         i;
   Entity      *ent;
   float       newa = 1;

 	for( i = 0; i < game.maxclients; i++ )
      {
      ed = &g_entities[ i ];
		if ( !ed->inuse || !ed->entity )
			continue;

  		ent = ed->entity;
      if ( !ent->isSubclassOf( Player ) )
         continue;

      player = ( Player * )ent;

      if ( !player->WithinDistance( org, radius ) )
         continue;

      trace = G_Trace( org, vec_zero, vec_zero, player->origin, player, MASK_OPAQUE, qfalse, "FlashPlayers" );      
      if ( trace.fraction != 1.0 )
         continue;

      delta = org - trace.endpos;
      length = delta.length();

      // If alpha is specified, then modify it by the amount of distance away from the flash the player is
      if ( a != -1 )
         newa = a * ( 1 - length / radius );

      level.m_fade_alpha      = newa;
      level.m_fade_color[0]   = r;
      level.m_fade_color[1]   = g;
      level.m_fade_color[2]   = b;
      level.m_fade_time       = time;
      level.m_fade_time_start = time;

      if ( type == 1 )
         level.m_fade_style = additive;
      else
         level.m_fade_style = alphablend;

//      gi.SendServerCommand( NULL, va( "fadein %0.2f %0.2f %0.2f %0.2f %i",time*1000,r*newa,g*newa,b*newa,type ) );
      }
   }

