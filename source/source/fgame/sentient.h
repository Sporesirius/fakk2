//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/sentient.h                         $
// $Revision:: 63                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 7/27/00 10:31a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/sentient.h                              $
// 
// 63    7/27/00 10:31a Steven
// Had to move SpawnEffect to public.
// 
// 62    7/23/00 8:49p Aldie
// Added some safety nets to the weapon code in sentient and player
// 
// 61    7/15/00 12:49p Steven
// Made people immune to fire they start.
// 
// 60    7/13/00 12:34p Steven
// Made EV_Sentient_StopOnFire available outside of Sentient.
// 
// 59    7/12/00 5:36p Markd
// fixed ammo reporting to support bullets in clip
// 
// 58    7/12/00 11:38a Steven
// Added CanBlock.
// 
// 57    7/10/00 9:27p Markd
// added ammo variables for how much ammo the player has.  Added levelvars and
// gamevars commands
// 
// 56    7/10/00 8:09p Markd
// fixed cool item pickup problems
// 
// 55    7/01/00 2:41p Steven
// Added stop on fire event.
// 
// 54    6/29/00 6:24p Steven
// Balanced small gibs stuff a little.
// 
// 53    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 52    6/19/00 6:21p Steven
// Improved ShouldBleed stuff.
// 
// 51    6/17/00 3:48p Aldie
// 
// 50    6/14/00 5:44p Steven
// Added nextbleedtime stuff.
// 
// 49    6/03/00 3:14p Aldie
// Added damage effects to player and sentient 
// 
// 48    6/03/00 2:55p Steven
// Added EV_Sentient_SpawnBloodyGibs to extern list.
// 
// 47    6/01/00 7:02p Markd
// removed activeWeapon variable
// 
// 46    6/01/00 3:18p Markd
// rewrote giveItem and item management in sentient
// 
// 45    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 44    5/23/00 6:43p Steven
// Moved small gib stuff to sentient.
// 
// 43    5/10/00 10:37a Steven
// Added next_catch_on_fire_time and added meansofdeath to TryCatchOnFire call.
// 
// 42    5/06/00 11:12a Aldie
// Added block effect and fixed some problems with ammo
// 
// 41    5/05/00 2:18p Steven
// Added catch on fire stuff.
// 
// 40    5/03/00 12:25p Steven
// Made attack_blocked and attack_blocked_time public instead of protected and
// made attack_blocked_time a float instead of an int.
// 
// 39    4/27/00 4:00p Aldie
// Fix for take command
// 
// 38    4/26/00 5:25p Aldie
// Changes to weapons to avoid having to specify the classname
// 
// 37    4/15/00 11:51a Steven
// Added a TurnOnShadow event and added a bunch of blood stuff.
// 
// 36    4/10/00 11:18a Markd
// Added new rope code
// 
// 35    4/06/00 3:48p Markd
// Made SetOffsetColor a public function instead of protected
// 
// 34    3/20/00 6:10p Steven
// Added SetMouthAngle event and max_mouth_angle stuff.
// 
// 33    3/13/00 5:18p Aldie
// Made some changes for usable inventory item stuff
// 
// 32    3/11/00 2:16p Steven
// Added stun stuff (so the AI knows when the player is incapable of doing
// anything :)
// 
// 31    3/02/00 4:43p Aldie
// Added some ammo functionality for the HUD
// 
// 30    2/24/00 4:18p Jimdose
// removed some unused variables
// 
// 29    2/23/00 3:19p Aldie
// Added more inventory functionality with the player
// 
// 28    2/17/00 6:26p Aldie
// Fixed naming conventions for weapon hand and also added various attachtotag
// functionality for weapons that attach to different tags depending on which
// hand they are wielded in.
// 
// 27    2/09/00 8:02p Aldie
// Added loopfire weapons
// 
// 26    2/08/00 6:35p Aldie
// Added more blocking code to player and sentient
// 
// 25    2/04/00 7:28p Aldie
// Combat code - blocking and combos
// 
// 24    2/02/00 7:08p Aldie
// Added new sword code and water damage
// 
// 23    1/29/00 6:17p Aldie
// Fixed some problems when state doesn't exist.
// 
// 22    1/29/00 12:32p Jimdose
// removed ImpactDamage
// 
// 21    1/27/00 11:48a Aldie
// Added player command and takeweapon
// 
// 20    1/26/00 3:33p Aldie
// Change Amount to getAmount. Added some 'listinventory' command.  Added give
// all cheat to execute the script in global/giveall.txt
// 
// 19    1/20/00 6:54p Aldie
// Removed bloodsplats until we do them the right way
// 
// 18    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 17    1/14/00 4:22p Steven
// Added a remove immunity event.
// 
// 16    1/07/00 8:12p Jimdose
// cleaning up unused code
// 
// 15    12/22/99 5:16p Steven
// Added some variables to keep track when sentients are melee attacking or
// blocking.
// 
// 14    12/20/99 6:51p Steven
// Moved jumpxy to sentient.
// 
// 13    12/17/99 8:27p Jimdose
// got rid of unused vars and functions
// 
// 12    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 11    12/14/18 2:43p Jimdose
// moved blood_model from Entity
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
// 7     11/29/99 6:32p Aldie
// Lots of changes for ammo system
// 
// 6     11/22/99 6:46p Aldie
// Started working on ammo changes - will finish after Thanksgiving break
// 
// 5     11/15/99 11:55a Aldie
// Added rope archiver
// 
// 4     10/28/99 11:56a Aldie
// Rope stuff
// 
// 3     10/28/99 10:42a Aldie
// Added rope functions
// 
// 2     10/19/99 7:53p Markd
// Eliminated 3 part model system
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 16    9/02/99 4:35p Markd
// Added Color Offset support for sentients
// 
// 15    8/31/99 2:46p Steven
// Added a means_of_death variable so it could be saved and checked by new
// death state machine.
// 
// 14    8/11/99 7:35p Aldie
// Added hand checking to weapons
// 
// 13    8/09/99 5:07p Aldie
// More changes to accomodate weapons system
// 
// 12    8/06/99 6:40p Aldie
// Started moving over to new weapons system
// 
// 11    8/04/99 4:53p Steven
// Added immunities to sentient.
// 
// 10    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
//
// DESCRIPTION:
// Base class of entity that can carry other entities, and use weapons.
//

#ifndef __SENTIENT_H__
#define __SENTIENT_H__

#include "g_local.h"
#include "container.h"
#include "animate.h"

extern Event EV_Sentient_Attack;
extern Event EV_Sentient_Charge;
extern Event EV_Sentient_ReleaseAttack;
extern Event EV_Sentient_GiveWeapon;
extern Event EV_Sentient_GiveAmmo;
extern Event EV_Sentient_GiveArmor;
extern Event EV_Sentient_GiveItem;
extern Event EV_Sentient_GiveTargetname;
extern Event EV_Sentient_GiveInventoryItem;
extern Event EV_Sentient_GiveHealth;
extern Event EV_Sentient_SetBloodModel;
extern Event EV_Sentient_UselessCheck;
extern Event EV_Sentient_TurnOffShadow;
extern Event EV_Sentient_TurnOnShadow;
extern Event EV_Sentient_AddImmunity;
extern Event EV_Sentient_RemoveImmunity;
extern Event EV_Sentient_UpdateOffsetColor;
extern Event EV_Sentient_JumpXY;
extern Event EV_Sentient_MeleeAttackStart;
extern Event EV_Sentient_MeleeAttackEnd;
extern Event EV_Sentient_BlockStart;
extern Event EV_Sentient_BlockEnd;
extern Event EV_Sentient_SetMouthAngle;
extern Event EV_Sentient_SpawnBloodyGibs;
extern Event EV_Sentient_StopOnFire;

// Shutup compiler
class Weapon;
class Item;
class InventoryItem;
class Ammo;

#define MAX_ACTIVE_WEAPONS NUM_ACTIVE_WEAPONS

typedef SafePtr<Weapon> WeaponPtr;

class Sentient : public Animate
	{
	protected:
      Container<int>		inventory;
      Container<Ammo *> ammo_inventory;

		WeaponPtr         newWeapon;
      int               poweruptype;
      int               poweruptimer;
      int               firing_frame;
      int               firing_anim;
      Vector            offset_color;
      Vector            offset_delta;
      float             offset_time;
      float             charge_start_time;

		str					blood_model;

		Container<int>		immunities;
      WeaponPtr         activeWeaponList[ MAX_ACTIVE_WEAPONS ];

      virtual void      EventTake( Event *ev );
		virtual void		EventGiveAmmo( Event *ev );
      virtual void		EventGiveItem( Event *ev );
      virtual void		EventGiveHealth( Event *ev );
      void              SetBloodModel( Event *ev );
      virtual void		EventGiveTargetname( Event *ev );
				
      virtual void      ArmorDamage( Event *ev );
		virtual qboolean	CanBlock( int meansofdeath, qboolean full_block	);
		void			      AddBloodSpurt( Vector direction );
		qboolean				ShouldBleed( int meansofdeath, qboolean dead );
		qboolean				ShouldGib( int meansofdeath, float damage );
		str					GetBloodSpurtName( void );
		str					GetBloodSplatName( void );
		float					GetBloodSplatSize( void );
		str					GetGibName( void );
      virtual void      TurnOffShadow( Event *ev );
		virtual void      TurnOnShadow( Event *ev );
		virtual void      WeaponKnockedFromHands( void );
		virtual void		AddImmunity( Event *ev );
		virtual void		RemoveImmunity( Event *ev );
      
      void		         UpdateOffsetColor( Event *ev );

      void              DetachAllActiveWeapons( void );
      void              AttachAllActiveWeapons( void );

      qboolean          IsActiveWeapon( Weapon *weapon );
      void              ActivateWeapon( Weapon *weapon, weaponhand_t hand );
      void              DeactivateWeapon( Weapon *weapon );
      void              DeactivateWeapon( weaponhand_t hand );
      void              CheckAnimations( Event *ev );

	public:
		Vector				gunoffset;
		Vector				eyeposition;
      int               viewheight;
      
		int					means_of_death;
		qboolean				in_melee_attack;
		qboolean				in_block;
		qboolean				in_stun;

		qboolean				on_fire;
		float					on_fire_stop_time;
		float					next_catch_on_fire_time;
		int					on_fire_tagnums[3];
		EntityPtr			fire_owner;

		qboolean          attack_blocked;
      float             attack_blocked_time;

		float					max_mouth_angle;

		int					max_gibs;

		float					next_bleed_time;

      CLASS_PROTOTYPE( Sentient );

								Sentient();
		virtual				~Sentient();
		Vector				EyePosition( void );

      virtual Vector		GunPosition( void );	
      void		         FireWeapon( Event *ev );
      void		         StopFireWeapon( Event *ev );
      void		         ChargeWeapon( Event *ev );
      void		         ReleaseFireWeapon( Event *ev );
      void		         ChangeWeapon( Weapon *weapon, weaponhand_t hand );
		Weapon		      *GetActiveWeapon( weaponhand_t hand );
		Weapon		      *BestWeapon( Weapon *ignore = NULL );
		Weapon		      *NextWeapon( Weapon *weapon );
		Weapon		      *PreviousWeapon( Weapon *weapon );
		virtual void      useWeapon( const char *weaponname, weaponhand_t hand );
      int               NumWeapons( void );
      inline  int       GetFiringFrame( void ){ return firing_frame; };
      inline  int       GetFiringAnim( void ){ return firing_anim; };
      int               AmmoCount( str ammo_type );
      int               MaxAmmoCount( str ammo_type );
      int               AmmoIndex( str ammo_type );
      int               UseAmmo( str ammo_type, int amount );
      void              GiveAmmo( str type, int amount, int max_amount=-1 );
      Ammo              *FindAmmoByName( str name );
      Item              *giveItem( str itemname, int amount = 1 );
      void              takeItem( const char *itemname );
		void		         AddItem( Item *object );
		void		         RemoveItem( Item *object );
		Item		         *FindItemByClassName( const char *classname );
      Item		         *FindItemByModelname( const char *modelname );
      Item              *FindItemByExternalName( const char *externalname );
      Item              *FindItem( const char *itemname );
      void		         FreeInventory( void );
		qboolean	         HasItem( const char *itemname );
      int               NumInventoryItems( void );
      Item              *NextItem( Item *item );
      Item              *PrevItem( Item *item );
      virtual void      DropInventoryItems( void );
      void              ListInventory( void );

      qboolean          PowerupActive( void );

		virtual void		setModel( const char *model );
      virtual void      Archive( Archiver &arc );
      void              ArchivePersistantData( Archiver &arc );
      void              DoubleArmor( void );
      virtual qboolean  DoGib( int meansofdeath, Entity *inflictor );
		qboolean				Immune( int meansofdeath );
		void              JumpXY( Event *ev );
		void              MeleeAttackStart( Event *ev );
		void              MeleeAttackEnd( Event *ev );
		void              BlockStart( Event *ev );
		void              BlockEnd( Event *ev );
		void              StunStart( Event *ev );
		void              StunEnd( Event *ev );
      void              SetAttackBlocked( qboolean blocked );
      void		         SetOffsetColor( float r, float g, float b, float time );
      virtual void      ReceivedItem( Item * item );
      virtual void      RemovedItem( Item * item );
      virtual void      AmmoAmountChanged( Ammo * ammo, int inclip = 0 );
      void              AmmoAmountInClipChanged( str ammo_type, int amount );

		void					SetMaxMouthAngle( Event *ev );
		void					TryLightOnFire( int meansofdeath, Entity *attacker );
		void					OnFire( Event *ev );
		void					StopOnFire( Event *ev );
		void					SpawnBloodyGibs( Event *ev );
		void					SetMaxGibs( Event *ev );
      virtual void      GetStateAnims( Container<const char *> *c );
		void              SpawnEffect( str modelname, Vector pos );
   };

typedef SafePtr<Sentient> SentientPtr;

extern Container<Sentient *> SentientList;

#endif /* sentient.h */
