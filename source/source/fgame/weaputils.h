//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/weaputils.h                        $
// $Revision:: 40                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/20/00 3:48p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/weaputils.h                             $
// 
// 40    7/20/00 3:48p Aldie
// Fixes for goo
// 
// 39    7/17/00 6:59p Steven
// Added RemoveWhenStopped stuff.
// 
// 38    7/05/00 6:15p Steven
// Added a damage multiplier for combos.
// 
// 37    7/03/00 10:25a Steven
// Fixed attack_min_height not allowing a value of 0.
// 
// 36    7/01/00 2:02p Steven
// Added knockback stuff to explosions
// 
// 35    6/30/00 5:00p Steven
// Added a way for projectiles to hit their owner without getting blocked by
// them when first shot.
// 
// 34    6/30/00 11:41a Steven
// Improved radius damage.
// 
// 33    6/20/00 6:59p Steven
// Fixed a savegame bug.
// 
// 32    6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 31    6/08/00 3:55p Aldie
// Added goo
// 
// 30    6/07/00 4:16p Aldie
// Added clusterbombs, heatseeking, and drunk
// 
// 29    6/01/00 7:45p Aldie
// Heatseeking and Drunkeness added to projectiles
// 
// 28    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 27    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 26    5/22/00 5:13p Aldie
// First version of soulsucker
// 
// 25    5/10/00 10:37a Steven
// Added hit_dead to MeleeAttack.
// 
// 24    4/15/00 5:18p Aldie
// Added stun events and fixed yet another bug with Ammo and AutoPutaway
// 
// 23    4/15/00 4:24p Markd
// Fixed player turning
// 
// 22    4/11/00 4:01p Steven
// Added attack_min_height to MeleeAttack.
// 
// 21    4/08/00 2:49p Aldie
// New crossbow bolt implementation
// 
// 20    4/07/00 6:00p Aldie
// Added flashing and fixed radius damage for explosions
// 
// 19    4/05/00 6:17p Steven
// Added in real support for gravity based projectiles.
// 
// 18    3/30/00 2:09p Aldie
// Added hitspawn command
// 
// 17    3/04/00 5:08p Steven
// Added radius, damage_every_frame, and constant_damage to explosions.
// 
// 16    2/23/00 11:45a Steven
// Now pass in meansOfDeath_t type instead of the string.
// 
// 15    2/07/00 7:38p Aldie
// Fixed swiping, also various weapons fixes for sword and for sling
// 
// 14    2/04/00 3:11p Aldie
// Changed sword attack method for water usage
// 
// 13    2/01/00 5:28p Aldie
// More updates for auto aiming
// 
// 12    1/29/00 2:48p Aldie
// Added impact mark functionality and Decal class
// 
// 11    1/22/00 5:07p Steven
// Added knockback to meleeattack.
// 
// 10    1/19/00 4:02p Aldie
// Added chargespeed flag
// 
// 9     1/19/00 12:10p Aldie
// Added some chargeup functionality
// 
// 8     12/07/99 6:09p Aldie
// Added weapon charging
// 
// 7     11/12/99 6:24p Steven
// Added an attack_vector to melee attacks.
// 
// 6     11/12/99 3:15p Aldie
// Added bouncesound
// 
// 5     11/11/99 6:40p Aldie
// Added some grenade type functionality
// 
// 4     11/10/99 6:13p Steven
// Added means of death to melee attack.
// 
// 3     11/05/99 5:24p Steven
// Added attack_width to melee attacks.
// 
// 2     10/21/99 2:51p Aldie
// Added some more beam functions
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 8     8/11/99 5:57p Steven
// Added melee attacks.
// 
// 7     8/03/99 6:26p Steven
// Added means of death stuff to weapons.
// 
// 6     7/30/99 6:24p Aldie
// Updated weapons and utils to use new methods
// 
// 5     7/29/99 7:38p Aldie
// Updated weapons to new system
// 
// 4     7/23/99 3:27p Aldie
//
// DESCRIPTION:
// 

#ifndef __WEAPUTILS_H__
#define __WEAPUTILS_H__

#include "g_local.h"
#include "animate.h"
#include "beam.h"
#include "sword.h"

#define P_BOUNCE_TOUCH  0x00000001
#define P_CHARGE_LIFE   0x00000002
#define P_CHARGE_SPEED  0x00000004

extern Event EV_Projectile_Explode;
extern Event EV_Projectile_UpdateBeam;

class Projectile : public Animate
	{
   public:
      CLASS_PROTOTYPE( Projectile );

      float          fov;
      int            owner;
      float          speed;
      float          minspeed;
      float          damage;
      float          knockback;
      float          life;
      float          minlife;
      float          dlight_radius;
      float          charge_fraction;

      Vector         dlight_color;     
      Vector         addvelocity;
      meansOfDeath_t meansofdeath;
      FuncBeam       *m_beam;
      int            projFlags;
      str            bouncesound;
      str            impactmarkshader;
      str            impactmarkorientation;
      float          impactmarkradius;
      str            explosionmodel;
      EntityPtr      target;
      bool           addownervelocity;
      bool           drunk;
		bool				can_hit_owner;
		bool				remove_when_stopped;

                     Projectile();
      virtual void   Archive( Archiver &arc );
      virtual void   Touch( Event *ev );
      virtual void   Explode( Event *ev );                         
      virtual void   DoDecal( void );

      void           SetAvelocity( Event *ev );
      void           SetAddVelocity( Event *ev );      
      void           SetDLight( Event *ev );
      void           SetLife( Event *ev );
      void           SetMinLife( Event *ev );
      void           SetChargeLife( Event *ev );
      void           SetSpeed( Event *ev );
      void           SetMinSpeed( Event *ev );
      void           SetChargeSpeed( Event *ev );
      void           SetDamage( Event *ev );
      void           SetKnockback( Event *ev );
      void           SetProjectileDLight( Event *ev );
		void           SetMeansOfDeath( Event *ev );
      void           SetBounceFactor( Event *ev );
      void           SetBounceTouch( Event *ev );
      void           SetBounceSound( Event *ev );
      void           SetImpactMarkShader( Event *ev );
      void           SetImpactMarkRadius( Event *ev );
      void           SetImpactMarkOrientation( Event *ev );
      void           SetExplosionModel( Event *ev );
      void           UpdateBeam( Event *ev );
      void           BeamCommand( Event *ev );
      void           HeatSeek( Event *ev );
      void           Drunk( Event *ev );
      void           AddOwnerVelocity( Event *ev );
      void           Prethink( Event *ev );
      float          ResolveMinimumDistance(	Entity *potential_target, float currmin );
      float          AdjustAngle( float maxadjust, float currangle, float targetangle );
		void           SetCanHitOwner( Event *ev );
		void           ClearOwner( Event *ev );
		void           RemoveWhenStopped( Event *ev );
		void           Stopped( Event *ev );
   };

inline void Projectile::Archive
	(
	Archiver &arc
	)
   {
   Animate::Archive( arc );

   arc.ArchiveFloat( &fov );
   arc.ArchiveInteger( &owner );
   arc.ArchiveFloat( &speed );
   arc.ArchiveFloat( &minspeed );
   arc.ArchiveFloat( &damage );
   arc.ArchiveFloat( &knockback );
   arc.ArchiveFloat( &life );
   arc.ArchiveFloat( &minlife );
   arc.ArchiveFloat( &dlight_radius );
   arc.ArchiveFloat( &charge_fraction );
   arc.ArchiveVector( &dlight_color );
   arc.ArchiveVector( &addvelocity );
   ArchiveEnum( meansofdeath, meansOfDeath_t );
   arc.ArchiveObjectPointer( ( Class ** )&m_beam );
   arc.ArchiveInteger( &projFlags );
   arc.ArchiveString( &bouncesound );
   arc.ArchiveString( &impactmarkshader );
   arc.ArchiveString( &impactmarkorientation );
   arc.ArchiveFloat( &impactmarkradius );
   arc.ArchiveString( &explosionmodel );
   arc.ArchiveBool( &drunk );
   arc.ArchiveBool( &addownervelocity );
	arc.ArchiveBool( &can_hit_owner );
	arc.ArchiveBool( &remove_when_stopped );
   }

class Explosion : public Projectile
   {
   public:
      float flash_r, 
            flash_g,
            flash_b, 
            flash_a,
            flash_radius,
            flash_time;
      int   flash_type;
      float radius_damage;


      CLASS_PROTOTYPE( Explosion );

		float				radius;
		qboolean			constant_damage;
		qboolean			damage_every_frame;

							Explosion();
		void				SetRadius( Event *ev );
		void				SetRadiusDamage( Event *ev );
		void				SetConstantDamage( Event *ev );
		void				SetDamageEveryFrame( Event *ev );
      void           SetFlash( Event *ev );

      void				DamageAgain( Event *ev );
      virtual void   Archive( Archiver &arc );
   };

inline void Explosion::Archive
	(
	Archiver &arc
	)
   {
   Projectile::Archive( arc );

   arc.ArchiveFloat( &flash_r );
   arc.ArchiveFloat( &flash_g );
   arc.ArchiveFloat( &flash_b );
   arc.ArchiveFloat( &flash_a );
   arc.ArchiveFloat( &flash_radius );
   arc.ArchiveFloat( &flash_time );
   arc.ArchiveInteger( &flash_type );
   arc.ArchiveFloat( &radius_damage );
   }

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
	float knockback = 0,
	qboolean hit_dead = true,
   Container<Entity *>*victimlist=NULL
   );

qboolean SwordAttack
   (
   Vector start,
   Vector end,
   Sword *sword,
   Entity *attacker,
	float damage_multiplier
   );

Projectile *ProjectileAttack
   (
   Vector         start,
   Vector         dir,
   Entity         *owner,
   str            projectileModel,
   float          speedfraction,
	float				real_speed = 0
   );

void ExplosionAttack
   (
   Vector         pos,
   Entity         *owner,
   str            projectileModel,
   Vector         dir = Vector( 0,0,0),
   Entity         *ignore = NULL,
   float          scale=1.0f
   );

void StunAttack
	(
   Vector   pos,
   Entity   *attacker,
   Entity   *inflictor,
   float    radius,
   float    time,
   Entity   *ignore
   );

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
   );

void RadiusDamage
	(
	Entity   *inflictor,
	Entity   *attacker, 
	float    damage, 
	Entity   *ignore,
   int      mod,
	float		radius = 0,
	float		knockback = 0,
	qboolean	constant_damage = false
	);

#endif // __WEAPUTILS_H__
