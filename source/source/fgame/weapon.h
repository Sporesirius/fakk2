//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/weapon.h                           $
// $Revision:: 47                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/29/00 2:28p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/weapon.h                                $
// 
// 47    7/29/00 2:28p Aldie
// Added a nosound weapon check
// 
// 46    7/25/00 8:38p Markd
// added no ammo sounds to weapons
// 
// 45    7/15/00 1:06p Aldie
// Added specialmove stuff for weapons so we can do special movement with some
// dualhanded weapons
// 
// 44    7/12/00 3:21p Aldie
// Added alternate modes to sword
// 
// 43    7/11/00 9:57p Aldie
// Added torsoaim command
// 
// 42    7/05/00 4:00p Steven
// Added a makenoise event.
// 
// 41    6/27/00 7:17p Aldie
// Added worldhitspawn
// 
// 40    6/27/00 2:48p Aldie
// Changed some weapon aiming stuff again.  Aimed shots are automatically
// determined now.
// 
// 39    6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 38    5/31/00 5:06p Aldie
// New aiming method
// 
// 37    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 36    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 35    5/08/00 3:20p Aldie
// Added initial crosshair work
// 
// 34    5/06/00 1:55p Aldie
// Added even more ammo checking fixes
// 
// 33    5/06/00 10:40a Steven
// Made it so there is action level and means of death variables for each
// weapon mode.
// 
// 32    5/05/00 5:17p Aldie
// Flamethrower
// 
// 31    5/05/00 2:19p Steven
// Added means of death to weapons.
// 
// 30    4/15/00 2:29p Aldie
// Added fix for ammo checking with weapons that don't use ammo
// 
// 29    4/15/00 1:43p Aldie
// Added usenoammo command for a weapon that cannot be used when it has no ammo
// 
// 28    4/14/00 7:12p Aldie
// Fixed some ammo checking bugs
// 
// 27    4/10/00 11:28a Aldie
// Added weapon attaching to the sentients
// 
// 26    4/07/00 6:00p Aldie
// Added flashing and fixed radius damage for explosions
// 
// 25    4/07/00 4:01p Aldie
// Code changes to support flashbangs
// 
// 24    3/22/00 6:45p Aldie
// Added some checks to prevent firing through walls
// 
// 23    3/02/00 4:43p Aldie
// Added some ammo functionality for the HUD
// 
// 22    2/25/00 5:02p Aldie
// Changed some reloading and put in a fix for the animation problem with the
// firing of the weapons 
// 
// 21    2/17/00 6:26p Aldie
// Fixed naming conventions for weapon hand and also added various attachtotag
// functionality for weapons that attach to different tags depending on which
// hand they are wielded in.
// 
// 20    2/14/00 11:41a Aldie
// Added melee to firetype and getfiretype
// 
// 19    2/09/00 8:02p Aldie
// Added loopfire weapons
// 
// 18    2/09/00 3:00p Steven
// Fixed up some BroadcastSound issues with the weapons.
// 
// 17    2/07/00 7:38p Aldie
// Fixed swiping, also various weapons fixes for sword and for sling
// 
// 16    2/04/00 3:11p Aldie
// Changed sword attack method for water usage
// 
// 15    2/01/00 5:28p Aldie
// More updates for auto aiming
// 
// 14    1/22/00 3:38p Aldie
// Fixed some weapons code
// 
// 13    1/19/00 7:46p Aldie
// Fixed func_spawns of various types and removed some unused misc classes
// 
// 12    12/17/99 8:27p Jimdose
// got rid of unused vars and functions
// 
// 11    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 10    12/07/99 6:09p Aldie
// Added weapon charging
// 
// 9     12/03/99 7:02p Aldie
// More ammo joy
// 
// 8     12/02/99 6:53p Aldie
// Changed naming conventions from "both" to "dualhanded"  Also put in the
// inventory renderer for the hud file
// 
// 7     12/01/99 11:26a Aldie
// Couple of fixes for emitters and more ammo stuff
// 
// 6     11/29/99 6:32p Aldie
// Lots of changes for ammo system
// 
// 5     11/22/99 6:46p Aldie
// Started working on ammo changes - will finish after Thanksgiving break
// 
// 4     11/19/99 5:45p Aldie
// Update for primary and alternate fire weapons.  Removed PRIMARY and SECONDAY
// mode weapons of Sin, removed SILENCED properties, and changed ammo types to
// use the new system.  Still need to fix ammo checking for weapons.
// 
// 3     9/30/99 1:50p Aldie
// documentation of commands
// 
// 2     9/16/99 4:51p Jimdose
// removed unused variables
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 12    8/11/99 7:35p Aldie
// Added hand checking to weapons
// 
// 11    8/09/99 5:07p Aldie
// More changes to accomodate weapons system
// 
// 10    8/06/99 6:40p Aldie
// Started moving over to new weapons system
// 
// 9     7/30/99 6:24p Aldie
// Updated weapons and utils to use new methods
// 
// 8     7/29/99 7:38p Aldie
// Updated weapons to new system
// 
// 7     7/23/99 3:27p Aldie
//
// DESCRIPTION:
// Header file for Weapon class.  The weapon class is the base class for
// all weapons in Sin.  Any entity created from a class derived from the weapon
// class will be usable by any Sentient (players and monsters) as a weapon.
// 

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "g_local.h"
#include "item.h"
#include "ammo.h"
#include "queue.h"
#include "sentient.h"

extern Event EV_Weapon_GiveStartingAmmo;

typedef enum
   {
   FT_NONE,
   FT_BULLET,
   FT_PROJECTILE,
   FT_MELEE,
   FT_SPECIAL_PROJECTILE
   } firetype_t;

typedef enum
	{
	WEAPON_READY,
	WEAPON_FIRING,
	WEAPON_LOWERING,
	WEAPON_RAISING,
	WEAPON_HOLSTERED,
	WEAPON_RELOADING,
   WEAPON_CHANGING
	} weaponstate_t;

#define INITIALIZE_WEAPONMODE_VAR(var,value) \
   { \
   int _ii; \
   for( _ii=0; _ii<MAX_FIREMODES; _ii++ ) \
      { \
      var[_ii] = value; \
      } \
   }

class Player;

class Weapon : public Item
	{
	private:
      qboolean					attached;                  // Is this weapon attached to something?
		float						nextweaponsoundtime;       // The next time this weapon should sound off
      str                  current_attachToTag;       // The current name of the tag to attach itself to on the owner      
      str                  left_attachToTag;          // Tag to use when weapon is wielded in the left hand
      str                  right_attachToTag;         // ...right hand
      str                  dual_attachToTag;          // ...dual handed
      str                  leftholster_attachToTag;   // Tag to use when weapon is put away from left hand
      str                  rightholster_attachToTag;  // ...right hand
      str                  dualholster_attachToTag;   // ...dual handed
      float                lastScale;                 // Used for attaching to holster
      Vector               lastAngles;                // Used for attaching to holster
      qboolean             lastValid;                 // Used for attaching to holster
      qboolean             auto_putaway;              // Weapon will put itself away when out of ammo
      qboolean             use_no_ammo;               // Weapon will be able to be used when it has no ammo
      qboolean             crosshair;                 // Whether or not to display a crosshair with this weapon
      qboolean             torsoaim;                  // Whether or not to torso aim with this weapon
      qboolean             special_move;              // Allows special movement or not
      EntityPtr            aim_target;                // Current target of the weapon

   protected:
		float						maxrange;				      // maximum effective firing distance (for AI)
		float						minrange;				      // minimum safe firing distance (for AI)
      str						viewmodel;                 // View model of the weapon (not used in FAKK)
		str						worldmodel;                // the worldmodel of the weapon
		weaponstate_t			weaponstate;               // current state of the weapon
		int						rank;                      // rank of the weapon (relative to other weapons)
		int						order;                     // The order of this weapon in the inventory
		SentientPtr				last_owner;                // The last owner of the weapon
      float						last_owner_trigger_time;   // The time when the last owner may re-pickup this weapon
      qboolean             notdroppable;              // makes the weapon not able to be dropped
      int                  aimanim;                   // The aim animation to use for this weapon (so it shoots straight)
      int                  aimframe;                  // The aim frame to use for this weapon (so it shoots straight)
      Vector               leftHolsterAngles;         // Angles to set the weapon to when it's holstered
      Vector               rightHolsterAngles;        // Angles to set the weapon to when it's holstered
      Vector               dualHolsterAngles;         // Angles to set the weapon to when it's holstered
      float                holsterScale;              // Scale the weapon should be set to when it's holstered
		qboolean					quiet;                     // Makes the weapon not alert actors
		float						next_noise_time;           // next time weapon will alert actors
      float                next_noammo_time;          // next time we can play out of ammo sound

      // Each of these arrays is used to describe the properties of the weapon 
      // in its primary(index 0) and alternate(index 1) mode

      str                  ammo_type[MAX_FIREMODES];       // The type of ammo used
		int						ammorequired[MAX_FIREMODES];    // The amount of ammo required to fire this weapon
		int						startammo[MAX_FIREMODES];       // The starting amount of ammo when the weapon is picked up
      str                  projectileModel[MAX_FIREMODES]; // The model of the projectile fired
      float                bulletdamage[MAX_FIREMODES];    // The amount of damate a single bullet causes
      float                bulletcount[MAX_FIREMODES];     // The number of bullets the weapon fires
      float                bulletrange[MAX_FIREMODES];     // The range of the bullet
      float                bulletknockback[MAX_FIREMODES]; // The amount of knockback a bullet causes
      float						projectilespeed[MAX_FIREMODES]; // The speed of the projectile fired
      Vector               bulletspread[MAX_FIREMODES];    // The amount of spread bullets can have
      firetype_t           firetype[MAX_FIREMODES];        // The type of fire (projectile or bullet)
      int						ammo_clip_size[MAX_FIREMODES];  // The amount of rounds the clip can hold
      int						ammo_in_clip[MAX_FIREMODES];    // The current amount of ammo in the clip
      float                max_charge_time[MAX_FIREMODES]; // The max amount of time the weapon may be charged.
		meansOfDeath_t       meansofdeath[MAX_FIREMODES];	  // The means of death for this mode
		qboolean             loopfire[MAX_FIREMODES];        // The weapon loopfires and will not idle when shooting
      int                  action_level_increment[MAX_FIREMODES]; // Increments the action level everytime the weapon is fired
      str                  worldhitspawn[MAX_FIREMODES];   // The models to spawn when the weapon strikes the world
      
      qboolean             autoaim;                        // Whether or not the weapon will autoaim
      float                charge_fraction;                // Fraction of a charge up time 
      qboolean             putaway;                        // This is set to true by the state system to signal a weapon to be putaway
      firemode_t           firemodeindex;                  // This is used as an internal index to indicate which mode to apply commands to
      weaponhand_t         hand;                           // which hand the weapon may be wielded in

      void						SetMaxRangeEvent( Event *ev );  
      void						SetMinRangeEvent( Event *ev );		
      void                 SetSecondaryAmmo( const char *type, int amount, int startamount );
      friend               class Player;
      void			         DetachGun( void );
      void			         AttachGun( weaponhand_t hand, qboolean holstering=qfalse );
      void			         PickupWeapon( Event *ev );
      void			         DoneRaising( Event *ev );
      void			         DoneFiring( Event *ev );
      void			         Idle( Event *ev );
      qboolean		         CheckReload( firemode_t mode );
      void			         DoneReloading( Event *ev );
      void                 SetAimAnim( Event *ev );
      virtual void         Shoot( Event *ev );      
      void                 Alternate( Event *ev );
      void                 SetFireType( Event *ev );
      void                 SetProjectile( Event *ev );
      void                 SetBulletDamage( Event *ev );
      void                 SetBulletRange( Event *ev );
      void                 SetBulletKnockback( Event *ev );
      void                 SetBulletCount( Event *ev );
      void                 SetBulletSpread( Event *ev );
      void                 SetAutoPutaway( Event *ev );
      void                 SetRange( Event *ev );
      void                 SetSpecialMove( Event *ev );
      void                 SetUseNoAmmo( Event *ev );
      void                 LeftAttachToTag( Event *ev );
      void                 RightAttachToTag( Event *ev );
      void                 DualAttachToTag( Event *ev );
      void                 LeftHolsterAttachToTag( Event *ev );
      void                 RightHolsterAttachToTag( Event *ev );
      void                 DualHolsterAttachToTag( Event *ev );
      void                 SetLeftHolsterAngles( Event *ev );
      void                 SetRightHolsterAngles( Event *ev );
      void                 SetDualHolsterAngles( Event *ev );
      void                 SetHolsterScale( Event *ev );
      void                 SetWorldHitSpawn( Event *ev );

   public:
      CLASS_PROTOTYPE( Weapon );

						         Weapon();
                           Weapon( const char *file );
				               ~Weapon();
                        
      int				      GetRank( void );
      int				      GetOrder( void );
      void		   	      SetRank( int order, int rank );
      float				      GetMaxRange( void );
      float				      GetMinRange( void );
      inline qboolean      GetPutaway( void ){ return putaway; };
      inline void          SetPutAway( qboolean p ){ putaway = p; };
      void				      SetMaxRange( float val );
      void				      SetMinRange( float val );
      void                 SetHand( Event *ev );
      inline weaponhand_t  GetHand( void ){ return hand; };
      void                 ForceIdle( void );
      void                 SetAmmoRequired( Event *ev );
      void                 SetStartAmmo( Event *ev );
      int                  GetStartAmmo( firemode_t mode );
      int                  GetMaxAmmo( firemode_t mode );
      str                  GetAmmoType( firemode_t mode );
      firetype_t           GetFireType( firemode_t mode );
      void                 SetAmmoType( Event *ev );      
      void			         SetAmmoAmount( int amount, firemode_t mode );
      void                 UseAmmo( int amount, firemode_t mode );
      void			         SetAmmoClipSize( Event *ev );
      void                 SetAmmoInClip( Event *ev );
      void			         SetModels( const char *world, const char *view );
      void			         SetOwner( Sentient *ent );
      void                 SetMaxChargeTime( Event *ev );
      int				      AmmoAvailable( firemode_t mode );
      qboolean             UnlimitedAmmo( firemode_t mode );
      qboolean		         HasAmmo( firemode_t mode );
      qboolean             HasAmmoInClip( firemode_t mode );
      int                  GetClipSize( firemode_t mode );
      qboolean		         ReadyToFire( firemode_t mode, qboolean playsound=qtrue );
      qboolean		         MuzzleClear( void );
      void			         PutAway( void );
      qboolean		         Drop( void );
      void			         Fire( firemode_t mode );
      void                 Charge( firemode_t mode );
      void                 ReleaseFire( firemode_t mode, float chargetime );
      void			         ClientFireDone( void );
      qboolean	            Removable( void );
      qboolean             Pickupable( Entity *other );
      void                 DetachFromOwner( void );
      void                 AttachToOwner( weaponhand_t hand );
      void			         WeaponSound( Event *ev );
      void			         GetMuzzlePosition( Vector *position, Vector *forward = NULL, Vector *right = NULL, Vector *up = NULL );
      qboolean             AutoChange( void );
      int                  ClipAmmo( firemode_t mode );
      void                 ProcessWeaponCommandsEvent(Event *ev);
      qboolean             IsDroppable( void );
      int                  ActionLevelIncrement( firemode_t mode );
      void                 SetActionLevelIncrement( Event *ev );
      void                 ForceState( weaponstate_t state );
      void                 NotDroppableEvent( Event *ev );
      void                 GiveStartingAmmoToOwner( Event *ev );
      void                 AutoAim( Event *ev );
      void                 Crosshair( Event *ev );
      void                 TorsoAim( Event *ev );
      void                 AttachToTag( Event *ev );
		void                 SetQuiet( Event *ev );
      void                 SetLoopFire( Event *ev );
      inline virtual void  SpecialFireProjectile( Vector pos, Vector forward, Vector right, Vector up, Entity *owner, str projectileModel, float charge_fraction ) {};
      void                 AttachToHolster( weaponhand_t hand );
      inline str           GetCurrentAttachToTag( void ){ return current_attachToTag; };
      inline void          SetCurrentAttachToTag( str s ){ current_attachToTag = s; };
      inline str           GetLeftHolsterTag( void ){ return leftholster_attachToTag; };
      inline str           GetRightHolsterTag( void ){ return rightholster_attachToTag; };
      inline str           GetDualHolsterTag( void ){ return dualholster_attachToTag; };
      inline qboolean      GetUseNoAmmo( void ){ return use_no_ammo; };
		void						SetMeansOfDeath( Event *ev );
		meansOfDeath_t			GetMeansOfDeath( firemode_t mode );
      inline qboolean      GetSpecialMove( void ){ return special_move; };
      void                 SetAimTarget( Entity * );
      void                 WorldHitSpawn( firemode_t mode, Vector org, Vector angles, float life );
		void						MakeNoise( Event *ev );
      void                 Archive(	Archiver &arc );
      
   };
inline void Weapon::Archive
	(
	Archiver &arc
	)
   {
   Item::Archive( arc );

   arc.ArchiveBoolean( &attached );
   arc.ArchiveFloat( &nextweaponsoundtime );
   arc.ArchiveString( &current_attachToTag );

   arc.ArchiveString( &left_attachToTag );
   arc.ArchiveString( &right_attachToTag );
   arc.ArchiveString( &dual_attachToTag );
   arc.ArchiveString( &leftholster_attachToTag );
   arc.ArchiveString( &rightholster_attachToTag );
   arc.ArchiveString( &dualholster_attachToTag );

   arc.ArchiveFloat( &lastScale );
   arc.ArchiveVector( &lastAngles );
   arc.ArchiveBoolean( &lastValid );
   arc.ArchiveBoolean( &auto_putaway );
   arc.ArchiveBoolean( &use_no_ammo );
   arc.ArchiveBoolean( &crosshair );
   arc.ArchiveBoolean( &torsoaim );

   arc.ArchiveFloat( &maxrange );
   arc.ArchiveFloat( &minrange );
   arc.ArchiveString( &viewmodel );
   arc.ArchiveString( &worldmodel );
   ArchiveEnum( weaponstate, weaponstate_t );
   arc.ArchiveInteger( &rank );
   arc.ArchiveInteger( &order );

	arc.ArchiveSafePointer( &last_owner );
   arc.ArchiveFloat( &last_owner_trigger_time );
   arc.ArchiveBoolean( &notdroppable );
   arc.ArchiveInteger( &aimanim );
   arc.ArchiveInteger( &aimframe );
   arc.ArchiveVector( &leftHolsterAngles );
   arc.ArchiveVector( &rightHolsterAngles );
   arc.ArchiveVector( &dualHolsterAngles );
   arc.ArchiveFloat( &holsterScale );
   arc.ArchiveBoolean( &quiet );
   arc.ArchiveFloat( &next_noise_time );
   arc.ArchiveFloat( &next_noammo_time );

   arc.ArchiveString( &ammo_type[0] );
   arc.ArchiveString( &ammo_type[1] );
   arc.ArchiveInteger( &ammorequired[0] );
   arc.ArchiveInteger( &ammorequired[1] );
   arc.ArchiveInteger( &startammo[0] );
   arc.ArchiveInteger( &startammo[1] );
   arc.ArchiveString( &projectileModel[0] );
   arc.ArchiveString( &projectileModel[1] );
   arc.ArchiveFloat( &bulletdamage[0] );
   arc.ArchiveFloat( &bulletdamage[1] );   
   arc.ArchiveFloat( &bulletcount[0] );
   arc.ArchiveFloat( &bulletcount[1] );
   arc.ArchiveFloat( &bulletrange[0] );
   arc.ArchiveFloat( &bulletrange[1] );
   arc.ArchiveFloat( &bulletknockback[0] );
   arc.ArchiveFloat( &bulletknockback[1] );
   arc.ArchiveFloat( &projectilespeed[0] );
   arc.ArchiveFloat( &projectilespeed[1] );
   arc.ArchiveVector( &bulletspread[0] );
   arc.ArchiveVector( &bulletspread[1] );
//   arc.ArchiveString( &worldhitspawn[0] );
//   arc.ArchiveString( &worldhitspawn[1] );

   ArchiveEnum( firetype[0], firetype_t );
   ArchiveEnum( firetype[1], firetype_t );

   arc.ArchiveInteger( &ammo_clip_size[0] );
   arc.ArchiveInteger( &ammo_clip_size[1] );
   arc.ArchiveInteger( &ammo_in_clip[0] );
   arc.ArchiveInteger( &ammo_in_clip[1] );
   arc.ArchiveFloat( &max_charge_time[ 0 ] );
   arc.ArchiveFloat( &max_charge_time[ 1 ] );

   ArchiveEnum( meansofdeath[ 0 ], meansOfDeath_t );
   ArchiveEnum( meansofdeath[ 1 ], meansOfDeath_t );

   arc.ArchiveBoolean( &loopfire[ 0 ] );
   arc.ArchiveBoolean( &loopfire[ 1 ] );

	arc.ArchiveInteger( &action_level_increment[0] );
	arc.ArchiveInteger( &action_level_increment[1] );

   arc.ArchiveBoolean( &autoaim );
   arc.ArchiveFloat( &charge_fraction );
   arc.ArchiveBoolean( &putaway );
   arc.ArchiveBoolean( &special_move );

   ArchiveEnum( firemodeindex, firemode_t );

   ArchiveEnum( hand, weaponhand_t );
   }

typedef SafePtr<Weapon> WeaponPtr;

#endif /* weapon.h */
