//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/misc.h                             $
// $Revision:: 50                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/27/00 6:31p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/misc.h                                  $
// 
// 50    7/27/00 6:31p Markd
// made useAnim's work with doors, added key ability
// 
// 49    7/17/00 4:58p Markd
// fixed useobjects and skins
// 
// 48    7/14/00 11:45p Markd
// Added ambient sounds to func_supllywater
// 
// 47    7/11/00 9:28p Markd
// Added MaxWater event to func_watersupply
// 
// 46    7/10/00 11:54p Markd
// added exit level code
// 
// 45    7/07/00 4:32p Steven
// Teleporter stuff : no_effects flag, warp sentient to middle of teleporter
// and fixed some teleporting multiple times problems.
// 
// 44    7/06/00 6:25p Steven
// Added new teleport stuff.
// 
// 43    6/28/00 4:17p Markd
// fixed small UseAnim bug
// 
// 42    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 41    6/09/00 7:36p Markd
// Added activate and deactive to useobjects
// 
// 40    6/07/00 5:36p Markd
// fixed falling rock code
// 
// 39    6/04/00 6:52p Markd
// Added camera support to TouchAnim's cleaned up player camera interface
// 
// 38    6/04/00 6:16p Markd
// Added TouchAnim support
// 
// 37    5/26/00 7:44p Markd
// 2nd phase save games
// 
// 36    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 35    4/21/00 6:16p Markd
// Fixed bounce sound stuff
// 
// 34    4/19/00 9:25a Markd
// added bouncesound to falling rock code
// 
// 33    4/06/00 5:45p Aldie
// Added func_supplywater
// 
// 32    4/05/00 12:20p Markd
// added damage type 
// 
// 31    4/04/00 5:30p Markd
// Removed sounds from UseObject
// 
// 30    3/31/00 6:07p Markd
// improved the functionality of UseObjects
// 
// 29    3/31/00 3:19p Markd
// Added UseObject functionality
// 
// 28    3/27/00 4:16p Markd
// added state to the UseAnim headers
// 
// 27    3/21/00 5:05p Markd
// Added state variable to func_useanim_destination
// 
// 26    3/20/00 3:01p Markd
// added more functionality to falling rock
// 
// 25    3/18/00 2:43p Aldie
// Changed some func_spawn functionality
// 
// 24    3/16/00 10:20a Markd
// fixed useanim firing its targets before the animation was completed
// 
// 23    3/15/00 5:52p Aldie
// Added pushsound to func_pushobject and removed a printf.
// 
// 22    3/13/00 7:46p Jimdose
// added fallingrock
// 
// 21    3/01/00 11:25a Jimdose
// UseAnim now sends the entity that used it as the activator instead of itself
// when triggering targets
// 
// 20    2/25/00 7:27p Markd
// Added useanim_numloop support and fixed useanim_orientation
// 
// 19    2/24/00 3:17p Jimdose
// added canBeUsed to UseAnim
// added canPush to PushObject
// 
// 18    2/22/00 6:57p Jimdose
// pushobjects now do damage when blocked
// push objects are now solid_bsp
// 
// 17    2/22/00 1:57p Jimdose
// added PushObject
// 
// 16    2/02/00 7:14p Markd
// Added func_explodeobject and TossObject
// 
// 15    1/31/00 4:25p Jimdose
// added dir variable to monkeybar and horizontalpipe
// 
// 14    1/22/00 12:42p Jimdose
// added HorizontalPipe
// 
// 13    1/20/00 6:54p Aldie
// Removed bloodsplats until we do them the right way
// 
// 12    1/19/00 7:46p Aldie
// Fixed func_spawns of various types and removed some unused misc classes
// 
// 11    1/19/00 5:16p Markd
// Added thread and triggertarget to UseAnim
// 
// 10    1/18/00 2:38p Markd
// Made UseAnim not multi-trigger by default
// 
// 9     1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 8     1/15/00 1:36p Markd
// Added UseAnim and TouchUseAnim functionality to Player and game
// 
// 7     1/12/00 6:13p Jimdose
// added base_velocity and random_velocity
// 
// 6     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 5     12/14/18 2:44p Jimdose
// added func_monkeybar
// 
// 4     11/04/99 10:03a Markd
// complete overhaul of the camera system
// 
// 3     10/14/99 5:08p Markd
// removed a lot of G_GetMoveDir calls from the initialization code
// 
// 2     9/23/99 7:30p Markd
// Added misc_model support and fixed shadows
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 7     7/08/99 4:28p Markd
// Removed obsolete QUAKED functions
// 
// DESCRIPTION:
// Basically the big stew pot of the DLLs, or maybe a garbage bin, whichever
// metaphore you prefer.  This really should be cleaned up.  Anyway, this
// should contain utility functions that could be used by any entity.
// Right now it contains everything from entities that could be in their
// own file to my mother pot roast recipes.
// 

#ifndef __MISC_H__
#define __MISC_H__

#include "g_local.h"
#include "entity.h"
#include "mover.h"
#include "animate.h"

class InfoNull : public Entity
	{
	public:
      CLASS_PROTOTYPE( InfoNull );
		
		InfoNull();
	};

class FuncRemove : public Entity
	{
	public:
      CLASS_PROTOTYPE( FuncRemove );
		
		FuncRemove();
	};

class MiscModel : public Entity
	{
	public:
      CLASS_PROTOTYPE( MiscModel );
		
		MiscModel();
	};

class InfoNotNull : public Entity
	{
	public:
      CLASS_PROTOTYPE( InfoNotNull );
	};

class ExplodingWall : public Trigger
	{
	protected:
		int      dmg;
		int      explosions;
		float    attack_finished;
      Vector   land_angles;
      float    land_radius;
      float    angle_speed;
      int      state;
      Vector   base_velocity;
      Vector   random_velocity;
      Vector   orig_mins, orig_maxs;
      qboolean on_ground;

	public:
      CLASS_PROTOTYPE( ExplodingWall );

							ExplodingWall();
      void           Setup( Event *ev );
      void           AngleSpeed( Event *ev );
      void           LandRadius( Event *ev );
      void           LandAngles( Event *ev );
      void           BaseVelocity( Event *ev );
      void           RandomVelocity( Event *ev );
      void           SetDmg( Event *ev );
      void           SetExplosions( Event *ev );
      void           SetupSecondStage( void );
		void	         Explode( Event *ev );
		void	         DamageEvent( Event *ev );
		void	         GroundDamage( Event *ev );
		void	         TouchFunc( Event *ev );
		void	         StopRotating( Event *ev );
		void	         CheckOnGround( Event *ev );
	   void           Archive( Archiver &arc );
	};

inline void ExplodingWall::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.ArchiveInteger( &dmg );
   arc.ArchiveInteger( &explosions );
   arc.ArchiveFloat( &attack_finished );
   arc.ArchiveVector( &land_angles );
   arc.ArchiveFloat( &land_radius );
   arc.ArchiveFloat( &angle_speed );
   arc.ArchiveInteger( &state );
   arc.ArchiveVector( &base_velocity );
   arc.ArchiveVector( &random_velocity );
   arc.ArchiveVector( &orig_mins );
   arc.ArchiveVector( &orig_maxs );
   arc.ArchiveBoolean( &on_ground );
   }


class Teleporter : public Trigger
	{
	public:
		str					teleport_thread;
		qboolean				in_use;

      CLASS_PROTOTYPE( Teleporter );
		
								Teleporter();
		virtual void		StartTeleport( Event *ev );
		virtual void		Teleport( Event *ev );
		virtual void		StopTeleport( Event *ev );
		void					SetThread( Event *ev );
		virtual void      Archive( Archiver &arc );
	};

inline void Teleporter::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.ArchiveString( &teleport_thread );
	arc.ArchiveBoolean( &in_use );
   }

class TeleporterDestination : public Entity
	{
	public:
		Vector				movedir;

      CLASS_PROTOTYPE( TeleporterDestination );

						TeleporterDestination();
		void	            SetMoveDir( Event *ev );
	   virtual void      Archive( Archiver &arc );
	};

inline void TeleporterDestination::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.ArchiveVector( &movedir );
   }

class UseAnim : public Entity
	{
	public:
      int               count;
      qboolean          active;
      str               thread;
      str               triggertarget;
      int               num_loops;
      str               state;
      str               camera;
      str               anim;
      str               key;
      float             delay;
      float             last_active_time;

      CLASS_PROTOTYPE( UseAnim );
		
								UseAnim();
		virtual void		Touched( Event *ev );
      void              Reset( Event *ev );
      void              SetThread( Event * ev );
      void              SetTriggerTarget( Event * ev );
      void              SetCount( Event * ev );
		void	            SetAnim( Event *ev );
		void	            SetState( Event *ev );
		void	            SetKey( Event *ev );
		void	            SetCamera( Event *ev );
		void	            SetNumLoops( Event *ev );
		void	            SetDelay( Event *ev );
      bool              canBeUsed( Entity *activator );
      bool              GetInformation( Entity *activator, Vector * org, Vector * angles, str * animatoin, int * loopcount, str * state, str * camera );
      void              TriggerTargets( Entity *activator );
	   virtual void      Archive( Archiver &arc );
	};

inline void UseAnim::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.ArchiveInteger( &count );
   arc.ArchiveBoolean( &active );
   arc.ArchiveString( &thread );
   arc.ArchiveString( &triggertarget );
   arc.ArchiveInteger( &num_loops );
   arc.ArchiveString( &state );
   arc.ArchiveString( &camera );
   arc.ArchiveString( &anim );
   arc.ArchiveString( &key );
   arc.ArchiveFloat( &delay );
   arc.ArchiveFloat( &last_active_time );
   }

class TouchAnim : public UseAnim
	{
	public:

      CLASS_PROTOTYPE( TouchAnim );
		
								TouchAnim();
	};


class UseAnimDestination : public Entity
	{
	public:
      int               num_loops;
      str               state;
      str               anim;

      CLASS_PROTOTYPE( UseAnimDestination );

						      UseAnimDestination();
		void	            SetAnim( Event *ev );
		void	            SetState( Event *ev );
		void	            SetNumLoops( Event *ev );
		int	            GetNumLoops( void );
		str               GetAnim( void );
		str               GetState( void );
	   virtual void      Archive( Archiver &arc );
	};

inline void UseAnimDestination::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.ArchiveInteger( &num_loops );
   arc.ArchiveString( &state );
   arc.ArchiveString( &anim );
   }

class UseObject : public Animate
	{
	public:
      str               move_thread;
      str               stop_thread;
      str               reset_thread;
      str               triggertarget;
      Vector            offset;
      float             yaw_offset;
      int               count;
      float             cone;
      str               state;
      str               state_backwards;
      str               useMaterial;
      int               objectState;
      float             reset_time;
      qboolean          active;

      CLASS_PROTOTYPE( UseObject );
		
								UseObject();
      void              SetMoveThread( Event * ev );
      void              SetStopThread( Event * ev );
      void              SetResetThread( Event * ev );
      void              SetTriggerTarget( Event * ev );
      void              SetOffset( Event * ev );
      void              SetYawOffset( Event * ev );
      void              SetCount( Event * ev );
      void              SetCone( Event * ev );
      void              SetState( Event * ev );
      void              SetBackwardsState( Event * ev );
      void              SetResetTime( Event * ev );
      void              Reset( Event * ev );
      void              Resetting( Event * ev );
      void              DamageTriggered( Event * ev );
      void              DamageFunc( Event * ev );
      bool              canBeUsed( Vector org, Vector dir );
      void              Setup( Entity *activator, Vector *org, Vector *ang, str *newstate );
      void              Start( Event * ev = NULL );
      bool              Loop( void );
      void              SetActiveState( Event *ev );
      void              Stop( Entity *activator );
      void              ActivateEvent( Event *ev );
      void              DeactivateEvent( Event *ev );
      void              UseMaterialEvent( Event *ev );
	   virtual void      Archive( Archiver &arc );
	};

inline void UseObject::Archive
	(
	Archiver &arc
	)
   {
   Animate::Archive( arc );

   arc.ArchiveString( &move_thread );
   arc.ArchiveString( &stop_thread );
   arc.ArchiveString( &reset_thread );
   arc.ArchiveString( &triggertarget );
   arc.ArchiveVector( &offset );
   arc.ArchiveFloat( &yaw_offset );
   arc.ArchiveInteger( &count );
   arc.ArchiveFloat( &cone );
   arc.ArchiveString( &state );
   arc.ArchiveString( &state_backwards );
   arc.ArchiveString( &useMaterial );
   arc.ArchiveInteger( &objectState );
   arc.ArchiveFloat( &reset_time );
   arc.ArchiveBoolean( &active );
   }


class Waypoint : public Mover
	{
	public:
      CLASS_PROTOTYPE( Waypoint );
	};

class MonkeyBars : public Entity
	{
 	public:
      float          dir;

      CLASS_PROTOTYPE( MonkeyBars );

                     MonkeyBars();
      void           SetAngleEvent( Event *ev );

      virtual void   Archive( Archiver &arc );
	};

inline void MonkeyBars::Archive
	(
	Archiver &arc
	)

   {
   Entity::Archive( arc );

   arc.ArchiveFloat( &dir );
   }

class HorizontalPipe : public Entity
	{
 	public:
      float          dir;

      CLASS_PROTOTYPE( HorizontalPipe );

                     HorizontalPipe();
      void           SetAngleEvent( Event *ev );

      virtual void   Archive( Archiver &arc );
	};

inline void HorizontalPipe::Archive
	(
	Archiver &arc
	)

   {
   Entity::Archive( arc );

   arc.ArchiveFloat( &dir );
   }

class TossObject : public Animate
	{
   private:
      str            bouncesound;
      float          bouncesoundchance;
      void           Stop( Event *ev );
      void           Touch( Event *ev );
      void           SetBounceSound( Event *ev );
      void           SetBounceSoundChance( Event *ev );
   public:
      CLASS_PROTOTYPE( TossObject );

                     TossObject();
                     TossObject( str modelname );
      void           SetBounceSound( str bounce );
      void           SetBounceSoundChance( float chance );
      void           SetVelocity( float severity );
      virtual void   Archive( Archiver &arc );
   };

inline void TossObject::Archive
	(
	Archiver &arc
	)

   {
   Animate::Archive( arc );

   arc.ArchiveString( &bouncesound );
   arc.ArchiveFloat( &bouncesoundchance );
   }


class PushObject : public Entity
	{
   private:
      EntityPtr      owner;
		float			   attack_finished;
		int				dmg;
      str            pushsound;

 	public:
      CLASS_PROTOTYPE( PushObject );

                     PushObject();
      void           Start( Event *ev );
      void           SetDamage( Event *ev );
      void           BlockFunc( Event *ev );
      void           SetPushSound( Event *ev );
      qboolean       Push( Entity *pusher, Vector move );
      qboolean       canPush( Vector dir );

      Entity         *getOwner( void );

      virtual void   Archive( Archiver &arc );
	};

inline void PushObject::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.ArchiveSafePointer( &owner );
   arc.ArchiveFloat( &attack_finished );
   arc.ArchiveInteger( &dmg );
   arc.ArchiveString( &pushsound );
   }

class FallingRock : public Entity
	{
   private:
      int            active;
      Vector         start_origin;
      Vector         last_bounce_origin;
      Entity         *current;
      Entity         *activator;
      Vector         bounce_dir;
      Vector         rotateaxis;
      float          attack_finished;
      float          wait;
      float          speed;
      int            dmg;
      str            bouncesound;

      void           Touch( Event *ev );
      void           Bounce( Event *ev );
      void           Rotate( Event *ev );
      void           Activate( Event *ev );
      void           NextBounce( void );
      void           StartFalling( Event *ev );
      void           SetWait( Event *ev );
      void           SetSpeed( Event *ev );
      void           SetDmg( Event *ev );
      Entity         *SetNextBounceDir( void );
      void           SetBounceSound( str sound );
      void           SetBounceSound( Event *ev );
      virtual void   Archive( Archiver &arc );

   public:
      CLASS_PROTOTYPE( FallingRock );

                     FallingRock();
   };

inline void FallingRock::Archive
	(
	Archiver &arc
	)

   {
   Entity::Archive( arc );

   arc.ArchiveInteger( &active );
   arc.ArchiveVector( &start_origin );
   arc.ArchiveVector( &last_bounce_origin );
   arc.ArchiveObjectPointer( ( Class ** )&current );
   arc.ArchiveObjectPointer( ( Class ** )&activator );
   arc.ArchiveVector( &bounce_dir );
   arc.ArchiveVector( &rotateaxis );
   arc.ArchiveFloat( &attack_finished );
   arc.ArchiveFloat( &wait );
   arc.ArchiveFloat( &speed );
   arc.ArchiveInteger( &dmg );
   arc.ArchiveString( &bouncesound );
   if ( arc.Loading() )
      {
      SetBounceSound( bouncesound );
      }
   }


class SupplyWater : public Trigger
   {
   private:
      int   maxwater;
      int   amount;
   public:
      CLASS_PROTOTYPE( SupplyWater );
   
                        SupplyWater();
      void              Activate( Event *ev );
      void              MaxWater( Event *ev );
      void              ChargeOff( Event *ev );
      virtual void      Archive( Archiver &arc );
   };

inline void SupplyWater::Archive
	(
	Archiver &arc
	)

   {
   Trigger::Archive( arc );

   arc.ArchiveInteger( &amount );
   arc.ArchiveInteger( &maxwater );
   }

#endif /* misc.h */
