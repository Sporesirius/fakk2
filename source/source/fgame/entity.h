//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/entity.h                           $
// $Revision:: 59                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 7/25/00 8:00a                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/entity.h                                $
// 
// 59    7/25/00 8:00a Markd
// Added GLobal_FindRandomAlias to alias code
// 
// 58    7/23/00 1:47p Aldie
// Added detach all children command
// 
// 57    7/21/00 3:47p Steven
// Made showModel a virtual function.
// 
// 56    7/11/00 8:55p Aldie
// Added in an autoaim flag
// 
// 55    6/30/00 3:08p Markd
// fixed rise animation issues
// 
// 54    6/26/00 5:50p Markd
// re-did some renderfx commands, fixed anti-sb juice stuff
// 
// 53    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 52    6/14/00 11:18a Markd
// cleaned up code using Intel compiler
// 
// 51    6/09/00 6:55p Markd
// fixed camera being bound to other objects
// 
// 50    5/31/00 5:34p Steven
// Added look at me stuff.
// 
// 49    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 48    5/26/00 7:44p Markd
// 2nd phase save games
// 
// 47    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 46    5/05/00 2:18p Steven
// Made EV_RemoveAttachedModel visible to other classes.
// 
// 45    4/15/00 5:43p Steven
// Made damage fractioanl again.
// 
// 44    4/15/00 5:18p Aldie
// Added stun events and fixed yet another bug with Ammo and AutoPutaway
// 
// 43    4/13/00 3:45p Aldie
// Added more flashbang support.  Added damage_type to entities used to specify
// what type of damage they take.
// 
// 42    4/11/00 5:43p Steven
// Sinking into ground work.
// 
// 41    4/10/00 6:49p Steven
// Added  bind_use_my_angles so that a bound entity could use its angles for
// its local offset or its bindmaster.
// 
// 40    4/01/00 3:55p Markd
// Added FL_TOUCH_TRIGGERS support
// 
// 39    4/01/00 3:45p Markd
// added FL_TOUCH_TRIGGERS flag and implementation
// 
// 38    3/21/00 5:06p Markd
// added vehicle support
// 
// 37    3/20/00 3:01p Markd
// added more functionality to falling rock
// 
// 36    3/16/00 10:50a Markd
// Fixed some bad syntax in headers that exhibited itself in non-visualc
// compilers
// 
// 35    3/15/00 5:52p Aldie
// Added pushsound to func_pushobject and removed a printf.
// 
// 34    3/15/00 4:09p Aldie
// Fixed a bug with using weapons, and added some ability to force a state in
// the player
// 
// 33    3/14/00 4:56p Aldie
// Added new script damage command
// 
// 32    3/04/00 5:05p Steven
// Added a skipent to CanDamage.
// 
// 31    3/04/00 11:48a Markd
// Added light style support
// 
// 30    3/01/00 10:58a Jimdose
// added TriggerEvent
// 
// 29    2/26/00 12:59p Jimdose
// externed EV_Kill
// 
// 28    2/26/00 11:23a Steven
// Added partial immobile flag.
// 
// 27    2/21/00 4:39p Markd
// Added fade command to entity
// 
// 26    2/21/00 3:33p Steven
// Added a GetControllerAngles function.
// 
// 25    1/31/00 3:56p Aldie
// working on the auto aim / tracking code
// 
// 24    1/19/00 7:59p Markd
// Rewrote Surface Model Event and also added changeoutfit command to player
// 
// 23    1/19/00 7:09p Steven
// Added a removeattachedmodel event.
// 
// 22    1/15/00 3:57p Markd
// Eliminated multiple "angle" events and replaced them with EV_SetAngle
// 
// 21    1/14/00 5:06p Markd
// Removed surface num, tri_num and damage_multiplier from multiple functions
// and events
// 
// 20    1/13/00 7:08p Steven
// Made a SetControllerAngles event so I could post them in the future.
// 
// 19    1/10/00 6:17p Jimdose
// more code cleanup
// 
// 18    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 17    12/17/99 8:26p Jimdose
// got rid of unused vars and functions
// 
// 16    12/17/99 6:35p Jimdose
// changed spawnarg code
// added Level class for spawning and map control
// got rid of unused or superflous variables
// changed setjmp/longjmp calls to try/throw/catch exception handling
// 
// 15    12/14/18 2:43p Jimdose
// moved blood_model to Sentient
// 
// 14    12/02/99 6:57p Jimdose
// removed classname variable from Entity
// 
// 13    11/19/99 2:27p Steven
// Made sure all entity stuff would save correctly.
// 
// 12    11/18/99 6:26p Steven
// Fixed some tag stuff because CurrentAnim and CurrentFrame had different
// paramters in Entity and Animate which made the virtual stuff not work
// properly.
// 
// 11    11/12/99 6:52p Markd
// fixed up sound manager saving and loading
// 
// 10    11/01/99 4:01p Jimdose
// added SetControllerAngles and SetControllerTag
// 
// 9     10/28/99 6:08p Steven
// Added a use_angles flag and an offset to the entity attach stuff.
// 
// 8     10/25/99 6:39p Markd
// removed size and other unused variables, added radius and centroid to both
// server and game code
// 
// 7     10/21/99 10:58a Markd
// Added fadein
// 
// 6     10/19/99 7:52p Markd
// Removed three part model system
// 
// 5     10/01/99 2:42p Markd
// moved all the binding code back into Entity from Mover
// 
// 4     9/29/99 7:43p Markd
// Made items behave better when dropping to floor
// 
// 3     9/27/99 5:44p Markd
// began documentation and cleanup phase after merge
// 
// 2     9/16/99 4:50p Jimdose
// removed unused code
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 42    9/02/99 5:41p Markd
// made CacheResource utility functions changed code every where else
// 
// 41    9/02/99 2:33p Markd
// Added cache ability to entities
// 
// 40    9/01/99 8:21p Steven
// Fixed a typo.
// 
// 39    9/01/99 12:03p Steven
// Added blood spurts.
// 
// 38    8/31/99 2:46p Steven
// Added detach_at_death flag for attached models.
// 
// 37    8/30/99 3:25p Steven
// Added an event to kill all of an entities attachments.
// 
// 36    8/30/99 2:37p Steven
// Added support for volume and minimum distance for loop sounds.
// 
// 35    8/28/99 11:46a Steven
// Removed global from sound function calls.
// 
// 34    8/27/99 5:07p Steven
// Added anti Sucknblaugh juice powerup.
// 
// 33    8/25/99 9:01p Markd
// working on RF_ stuff and local color for entities on client
// 
// 32    8/17/99 4:59p Steven
// Added new immobile flag.
// 
// 31    8/06/99 3:35p Markd
// Cleaned up cgame, added shader commands and shader manipulation support
// 
// 30    7/30/99 6:45p Aldie
// Added explosion command
// 
// 29    7/30/99 4:49p Steven
// Added a stationary command to entities and a gas explode flag.
// 
// 28    7/06/99 8:33p Jimdose
// removed unused player code
// added state machine for player animation
//
// DESCRIPTION:
// Base class for all enities that are controlled by Sin.  If you have any
// object that should be called on a periodic basis and it is not an entity,
// then you have to have an dummy entity that calls it.
//
// An entity in Sin is any object that is not part of the world.  Any non-world
// object that is visible in Sin is an entity, although it is not required that
// all entities be visible to the player.  Some objects are basically just virtual
// constructs that act as an instigator of certain actions, for example, some
// triggers are invisible and cannot be touched, but when activated by other
// objects can cause things to happen.
//
// All entities are capable of receiving messages from Sin or from other entities.
// Messages received by an entity may be ignored, passed on to their superclass,
// or acted upon by the entity itself.  The programmer must decide on the proper
// action for the entity to take to any message.  There will be many messages
// that are completely irrelevant to an entity and should be ignored.  Some messages
// may require certain states to exist and if they are received by an entity when
// it these states don't exist may indicate a logic error on the part of the
// programmer or map designer and should be reported as warnings (if the problem is
// not severe enough for the game to be halted) or as errors (if the problem should
// not be ignored at any cost).
//

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "g_local.h"
#include "class.h"
#include "vector.h"
#include "script.h"
#include "listener.h"


// modification flags
#define FLAG_IGNORE  0
#define FLAG_CLEAR   1
#define FLAG_ADD     2

typedef enum
	{
	DAMAGE_NO,
	DAMAGE_YES,			// will take damage if hit
	DAMAGE_AIM			// auto targeting recognizes this
	} damage_t;

typedef enum
   {
   legs,
   torso,
   all
   } bodypart_t;

//deadflag
#define DEAD_NO						0
#define DEAD_DYING					1
#define DEAD_DEAD						2
#define DEAD_RESPAWNABLE			3

// flags
#define	FL_FLY					(1<<0)
#define	FL_SWIM					(1<<1)      // implied immunity to drowining
#define	FL_INWATER				(1<<2)
#define	FL_GODMODE				(1<<3)
#define	FL_NOTARGET				(1<<4)
#define	FL_PARTIALGROUND		(1<<5)      // not all corners are valid
#define	FL_TEAMSLAVE			(1<<6)      // not the first on the team
#define	FL_NO_KNOCKBACK		(1<<7)
#define	FL_THINK				   (1<<8)
#define  FL_BLOOD             (1<<9)      // when hit, it should bleed.
#define  FL_DIE_GIBS          (1<<10)     // when it dies, it should gib
#define  FL_DIE_EXPLODE       (1<<11)     // when it dies, it will explode
#define  FL_ROTATEDBOUNDS     (1<<12)     // model uses rotated mins and maxs
#define  FL_DONTSAVE          (1<<13)     // don't add to the savegame
#define  FL_IMMOBILE				(1<<14)     // entity has been immobolized somehow
#define  FL_PARTIAL_IMMOBILE	(1<<15)     // entity has been immobolized somehow
#define  FL_POSTTHINK			(1<<17)     // call a think function after the physics have been run
#define  FL_TOUCH_TRIGGERS		(1<<18)     // should this entity touch triggers
#define  FL_AUTOAIM           (1<<19)     // Autoaim on this entity


// damage flags
#define DAMAGE_RADIUS			0x00000001	// damage was indirect
#define DAMAGE_NO_ARMOR			0x00000002	// armour does not protect from this damage
#define DAMAGE_ENERGY			0x00000004	// damage is from an energy based weapon
#define DAMAGE_NO_KNOCKBACK	0x00000008	// do not affect velocity, just view angles
#define DAMAGE_BULLET			0x00000010  // damage is from a bullet (used for ricochets)
#define DAMAGE_NO_PROTECTION	0x00000020  // armor, shields, invulnerability, and godmode have no effect
#define DAMAGE_NO_SKILL       0x00000040  // damage is not affected by skill level

extern Event EV_ClientMove;
extern Event EV_ClientEndFrame;

// Generic entity events
extern Event EV_Classname;
extern Event EV_Activate;
extern Event EV_Use;
extern Event EV_FadeNoRemove;
extern Event EV_FadeOut;
extern Event EV_FadeIn;
extern Event EV_Fade;
extern Event EV_Killed;
extern Event EV_GotKill;
extern Event EV_Pain;
extern Event EV_Damage;
extern Event EV_Stun;
extern Event EV_Gib;
extern Event EV_Kill;
extern Event EV_DeathSinkStart;

// Physics events
extern Event EV_MoveDone;
extern Event EV_Touch;
extern Event EV_Blocked;
extern Event EV_Attach;
extern Event EV_AttachModel;
extern Event EV_RemoveAttachedModel;
extern Event EV_Detach;
extern Event EV_UseBoundingBox;

// Animation events
extern Event EV_NewAnim;
extern Event EV_LastFrame;
extern Event EV_TakeDamage;
extern Event EV_NoDamage;

// script stuff
extern Event EV_Model;
extern Event EV_Hide;
extern Event EV_Show;
extern Event EV_BecomeSolid;
extern Event EV_BecomeNonSolid;
extern Event EV_Sound;
extern Event EV_StopSound;
extern Event EV_Bind;
extern Event EV_Unbind;
extern Event EV_JoinTeam;
extern Event EV_QuitTeam;
extern Event EV_SetHealth;
extern Event EV_SetSize;
extern Event EV_SetAlpha;
extern Event EV_SetOrigin;
extern Event EV_SetTargetName;
extern Event EV_SetTarget;
extern Event EV_SetKillTarget;
extern Event EV_SetAngles;
extern Event EV_SetAngle;
extern Event EV_RegisterAlias;
extern Event EV_Anim;
extern Event EV_StartAnimating;
extern Event EV_SurfaceModelEvent;
extern Event EV_ProcessInitCommands;
extern Event EV_Stop;
extern Event EV_StopLoopSound;
extern Event EV_SetControllerAngles;

// dir is 1
// power is 2
// minsize is 3
// maxsize is 4
// percentage is 5
// thickness 6
// entity is 7
// origin 8

// AI sound events
extern Event EV_BroadcastSound;
extern Event EV_HeardSound;
extern Event EV_Hurt;
extern Event EV_IfSkill;


// Define ScriptMaster
class ScriptMaster;

//
// Spawn args
//
// "spawnflags"
// "alpha" default 1.0
// "model"
// "origin"
// "targetname"
// "target"
//
#define MAX_MODEL_CHILDREN 8

class Entity;

typedef SafePtr<Entity> EntityPtr;

class Entity : public Listener
	{
	public:
		CLASS_PROTOTYPE( Entity );

		// spawning variables
		int					entnum;
      gentity_t         *edict;
		gclient_t			*client;
		int					spawnflags;

      // standard variables
		str					model;

		// physics variables
      float             move_time;     // how much time total_delta will take
      Vector            total_delta;   // total unprocessed movement
		Vector				mins;
		Vector				maxs;
		Vector				absmin;
		Vector				absmax;
		Vector				centroid;
		Vector				velocity;
		Vector				avelocity;
      Vector            origin;
      Vector            angles;
      Vector            size;
		int					movetype;
		int					mass;
		float					gravity;			// per entity gravity multiplier (1.0 is normal)
		float					orientation[3][3];

      gentity_t         *groundentity;
		cplane_t				groundplane;
		int					groundcontents;

      // Model Binding variables
      int               numchildren;
      int               children[MAX_MODEL_CHILDREN];

      // Surface variables
      int               numsurfaces;

      // Light variables
      float             lightRadius;

      // Team variables
		str					moveteam;
		Entity				*teamchain;
		Entity 				*teammaster;

		// Binding variables
		Entity 				*bindmaster;
		qboolean				bind_use_my_angles;
      Vector            localorigin;
      Vector            localangles;

		// targeting variables
		str					target;
		str					targetname;
		str			      killtarget;

		// Character state
		float					health;
		float             max_health;
		int					deadflag;
		int					flags;

		// underwater variables
		int					watertype;
		int					waterlevel;

		// Pain and damage variables
		damage_t				takedamage;
		EntityPtr			enemy;
		float					pain_finished;
		float					damage_debounce_time;
      int               damage_type;

		qboolean				detach_at_death;

		qboolean				look_at_me;

								Entity();
		virtual				~Entity();

      void              SetEntNum( int num );
      void              ClassnameEvent( Event *ev );
      void              SpawnFlagsEvent( Event *ev );

      qboolean				DistanceTo( Vector pos );
      qboolean				DistanceTo( Entity *ent );
		qboolean				WithinDistance( Vector pos, float dist );
		qboolean				WithinDistance( Entity *ent, float dist );

		const char			*Target( void );
		void					SetTarget( const char *target );
		qboolean				Targeted( void );
		const char			*TargetName( void );
		void					SetTargetName( const char *target );
      void              SetKillTarget( const char *killtarget );
      const char        *KillTarget( void );

		virtual void		setModel( const char *model );
		void		         setModel( str &mdl );
		void					SetModelEvent( Event *ev );
      void              SetTeamEvent( Event *ev );
      virtual void      TriggerEvent( Event *ev );
		void					hideModel( void );
		void					EventHideModel( Event *ev );
		virtual void		showModel( void );
		void					EventShowModel( Event *ev );
		qboolean				hidden( void );
      void              ProcessInitCommandsEvent( Event *ev );
      void              ProcessInitCommands( int index, qboolean cache = qfalse );

		void					setAlpha( float alpha );
		float					alpha( void );

		void					setMoveType( int type );
		int					getMoveType( void );

		void					setSolidType( solid_t type );
		int					getSolidType( void );

		virtual Vector		getParentVector( Vector vec );
		Vector				getLocalVector( Vector vec );

		virtual void		setSize( Vector min, Vector max );
		virtual void		setOrigin( Vector org );
      virtual void      setOrigin( void );
		virtual void		addOrigin( Vector org );

      void              GetRawTag( int tagnum, orientation_t * orient );
      qboolean          GetRawTag( const char * tagname, orientation_t * orient );

      void              GetTag( int tagnum, orientation_t * orient );
      qboolean          GetTag( const char *name, orientation_t * orient );
		void  				GetTag( int tagnum, Vector *pos, Vector *forward = NULL, Vector *left = NULL, Vector *up = NULL );
		qboolean				GetTag( const char *name, Vector *pos, Vector *forward = NULL, Vector *left = NULL, Vector *up = NULL );

      virtual int       CurrentFrame( bodypart_t part = legs );
		virtual int       CurrentAnim( bodypart_t part = legs );

      virtual void      setAngles( Vector ang );
		virtual void		setAngles( void );
		void					SetOrigin( Event *ev );

		Vector            GetControllerAngles( int num );
      void              SetControllerAngles( int num, vec3_t angles );
		void              SetControllerAngles( Event *ev );
      void              SetControllerTag( int num, int tag_num );

		void					link( void );
		void					unlink( void );

		void					setContents( int type );
		int					getContents( void );
      void              setScale( float scale );

		qboolean				droptofloor( float maxfall );
		qboolean				isClient( void );

      virtual void		SetDeltaAngles( void );
		virtual void		DamageEvent( Event *event );
      void              Damage( Entity *inflictor,
                                Entity *attacker,
                                float damage,
                                Vector position,
                                Vector direction,
                                Vector normal,
                                int knockback,
                                int flags,
                                int meansofdeath );
      void              Stun( float time );

      void              DamageType( Event *ev );
		virtual qboolean	CanDamage( Entity *target, Entity *skip_ent = NULL );

		qboolean				IsTouching( Entity *e1 );

		void					FadeNoRemove( Event *ev );
		void					FadeOut( Event *ev );
		void					FadeIn( Event *ev );
		void					Fade( Event *ev );

		virtual void		CheckGround( void );
		virtual qboolean	HitSky( trace_t *trace );
		virtual qboolean	HitSky( void );

		void					BecomeSolid( Event *ev );
		void					BecomeNonSolid( Event *ev );
		void					SetHealth( Event *ev );
		void					SetSize( Event *ev );
		void					SetMins( Event *ev );
		void					SetMaxs( Event *ev );
		void					SetScale( Event *ev );
		void					SetAlpha( Event *ev );
		void					SetTargetName( Event *ev );
		void					SetTarget( Event *ev );
		void		         SetKillTarget( Event *ev );
		void					SetAngles( Event *ev );
		void					SetAngleEvent( Event *ev );
		void					TouchTriggersEvent( Event *ev );

      str               GetRandomAlias( str name );
      void              SetWaterType( void );

      // model binding functions
      qboolean          attach( int parent_entity_num, int tag_num, qboolean use_angles = qtrue, Vector attach_offset = "0 0 0");
      void              detach( void );

      void              RegisterAlias( Event *ev );
      void              RegisterAliasAndCache( Event *ev );
      void              Cache( Event *ev ); 

		qboolean				GlobalAliasExists( const char *name );
		qboolean				AliasExists( const char *name );

		void              Sound( Event *ev );
		virtual void		Sound( str sound_name, int channel = CHAN_BODY, float volume = -1.0,
								float min_dist = -1.0, Vector *origin = NULL );
		void					StopSound( int channel );
		void					StopSound( Event *ev );
		void					LoopSound( Event *ev );
		void					LoopSound( str sound_name, float volume = -1.0, float min_dist = -1.0 );
		void					StopLoopSound( Event *ev );
		void					StopLoopSound( void );

      void              SetLight(Event *ev);
      void              LightOn(Event *ev);
      void              LightOff(Event *ev);
      void              LightRed(Event *ev);
      void              LightGreen(Event *ev);
      void              LightBlue(Event *ev);
      void              LightRadius(Event *ev);
      void              LightStyle(Event *ev);
      void              Flags( Event *ev );
      void              Effects( Event *ev );
      void              RenderEffects( Event *ev );
      void              SVFlags( Event *ev );

		void					BroadcastSound( float pos = SOUND_RADIUS );
		void					BroadcastSound( Event *ev );
      void              Kill( Event *ev );
      void              SurfaceModelEvent( Event *ev );
      void              SurfaceCommand( const char * surf_name, const char * token );

		virtual void		Postthink( void );
		virtual void		Think( void );
      void              DamageSkin( trace_t * trace, float damage );

		void					AttachEvent( Event *ev );
		void					AttachModelEvent( Event *ev );
		void					RemoveAttachedModelEvent( Event *ev );
		void					DetachEvent( Event *ev );
      void              TakeDamageEvent( Event *ev );
      void              NoDamageEvent( Event *ev );
      void              Gravity( Event *ev );
      void              GiveOxygen( float time );
      void              UseBoundingBoxEvent( Event *ev );
      void              HurtEvent( Event *ev );
      void              IfSkillEvent( Event *ev );
      void              SetMassEvent( Event *ev );
      void              Censor( Event *ev );
      void              Ghost( Event *ev );

		void					StationaryEvent( Event *ev );
      void              Explosion( Event *ev );

      void              Shader( Event *ev );

		void              KillAttach( Event *ev );
		void					SetBloodModel( Event *ev );

		void					DropToFloorEvent( Event *ev );

      // Binding methods
		void					joinTeam( Entity *teammember );
		void					quitTeam( void );
      qboolean          isBoundTo( Entity *master );
		virtual void		bind( Entity *master, qboolean use_my_angles=false );
		virtual void		unbind( void );

		void					JoinTeam( Event *ev );
		void					EventQuitTeam( Event *ev );
		void					BindEvent( Event *ev );
		void					EventUnbind( Event *ev );
		void					AddToSoundManager( Event *ev );
      void              NoLerpThisFrame( void );

      virtual void		addAngles( Vector add );

		void					DeathSinkStart( Event *ev );
		void					DeathSink( Event *ev );

		void					LookAtMe( Event *ev );
      void              DetachAllChildren( Event *ev );

      virtual void      VelocityModified( void );
      virtual void      Archive( Archiver &arc );
	};

inline int Entity::getSolidType
	(
	void
	)

	{
	return edict->solid;
	}


inline qboolean Entity::DistanceTo
	(
	Vector pos
	)

	{
	Vector delta;

   delta = origin - pos;
	return delta.length();
	}

inline qboolean Entity::DistanceTo
	(
	Entity *ent
	)

	{
	Vector delta;

	assert( ent );

	if ( !ent )
		{
		// "Infinite" distance
		return 999999;
		}

   delta = origin - ent->origin;
	return delta.length();
	}

inline qboolean Entity::WithinDistance
	(
	Vector pos,
	float dist
	)

	{
	Vector delta;

   delta = origin - pos;

	// check squared distance
	return ( ( delta * delta ) < ( dist * dist ) );
	}

inline qboolean Entity::WithinDistance
	(
	Entity *ent,
	float dist
	)

	{
	Vector delta;

	assert( ent );

	if ( !ent )
		{
		return false;
		}

   delta = origin - ent->origin;

	// check squared distance
	return ( ( delta * delta ) < ( dist * dist ) );
	}

inline const char *Entity::Target
	(
	void
	)

	{
	return target.c_str();
	}

inline qboolean Entity::Targeted
	(
	void
	)

	{
	if ( !targetname.length() )
		{
		return false;
		}
	return true;
	}

inline const char *Entity::TargetName
	(
	void
	)

	{
	return targetname.c_str();
	}

inline const char * Entity::KillTarget
	(
	void
	)

	{
	return killtarget.c_str();
	}

inline qboolean Entity::hidden
	(
	void
	)

	{
	if ( edict->s.renderfx & RF_DONTDRAW )
		{
		return true;
		}
	return false;
	}

inline void Entity::setModel
	(
	str &mdl
	)

	{
	setModel( mdl.c_str() );
	}

inline void Entity::SetModelEvent
	(
	Event *ev
	)

	{
	setModel( ev->GetString( 1 ) );
	}

inline void Entity::hideModel
	(
	void
	)

	{
	edict->s.renderfx |= RF_DONTDRAW;
	if ( getSolidType() <= SOLID_TRIGGER )
		{
		edict->svflags |= SVF_NOCLIENT;
		}
	}

inline void Entity::showModel
	(
	void
	)

	{
	edict->s.renderfx &= ~RF_DONTDRAW;
	edict->svflags &= ~SVF_NOCLIENT;
	}

inline float Entity::alpha
	(
	void
	)

	{
	return edict->s.alpha;
	}

inline void Entity::setMoveType
	(
	int type
	)

	{
	movetype = type;
	}

inline int Entity::getMoveType
	(
	void
	)

	{
	return movetype;
	}

inline void Entity::unlink
	(
	void
	)

	{
	gi.unlinkentity( edict );
	}

inline void Entity::setContents
	(
	int type
	)

	{
	edict->contents = type;
	}

inline int Entity::getContents
	(
	void
	)

	{
	return edict->contents;
	}

inline qboolean Entity::isClient
	(
	void
	)

	{
	if ( client )
		{
		return true;
		}
	return false;
	}

inline void Entity::SetDeltaAngles
   (
   void
   )

   {
   int i;

   if ( client )
      {
	   for( i = 0; i < 3; i++ )
         {
		   client->ps.delta_angles[ i ] = ANGLE2SHORT( client->ps.viewangles[ i ] );
         }
      }
   }

inline qboolean Entity::GlobalAliasExists
	(
	const char *name
	)

	{
	assert( name );

	return ( gi.GlobalAlias_FindRandom( name ) != NULL );
	}

inline qboolean Entity::AliasExists
	(
	const char *name
	)

	{
	assert( name );

	return ( gi.Alias_FindRandom( edict->s.modelindex, name ) != NULL );
	}

inline str Entity::GetRandomAlias
	(
   str name
	)

	{
	str realname;
   const char *s;

   s = gi.Alias_FindRandom( edict->s.modelindex, name.c_str() );
   if ( s )
      {
      realname = s;
      }
   else
      {
      s = gi.GlobalAlias_FindRandom( name.c_str() );
      if ( s )
         {
         realname = s;
         }
      }

   return realname;
	}

inline int Entity::CurrentFrame
	(
   bodypart_t part
	)

	{
   part = part;
	return 0;
	}

inline int Entity::CurrentAnim
	(
   bodypart_t part
	)

	{
   part = part;
	return 0;
	}

inline void Entity::Archive
	(
	Archiver &arc
	)

   {
   int tempInt;

   Listener::Archive( arc );

   G_ArchiveEdict( arc, edict );

   arc.ArchiveInteger( &spawnflags );

   arc.ArchiveString( &model );
   if ( arc.Loading() && model.length() )
      {
      setModel( model );
      }

   arc.ArchiveFloat( &move_time );
   arc.ArchiveVector( &total_delta );
   arc.ArchiveVector( &mins );
   arc.ArchiveVector( &maxs );
   arc.ArchiveVector( &absmin );
   arc.ArchiveVector( &absmax );
   arc.ArchiveVector( &centroid );
   arc.ArchiveVector( &velocity );
   arc.ArchiveVector( &avelocity );
   arc.ArchiveVector( &origin );
   arc.ArchiveVector( &angles );
   arc.ArchiveVector( &size );
   arc.ArchiveInteger( &movetype );
   arc.ArchiveInteger( &mass );
   arc.ArchiveFloat( &gravity );
   arc.ArchiveRaw( orientation, sizeof( orientation ) );

   if ( arc.Saving() )
      {
      if ( groundentity )
         {
         tempInt = groundentity - g_entities;
         }
      else
         {
         tempInt = -1;
         }
      }

   arc.ArchiveInteger( &tempInt );

   if ( arc.Loading() )
      {
      if ( tempInt == -1 )
         {
         groundentity = NULL;
         }
      else
         {
         groundentity = &g_entities[ tempInt ];
         }
      }

   arc.ArchiveRaw( &groundplane, sizeof( groundplane ) );
   arc.ArchiveInteger( &groundcontents );

   arc.ArchiveInteger( &numchildren );
   arc.ArchiveRaw( children, sizeof( children ) );

   arc.ArchiveInteger( &numsurfaces );

   arc.ArchiveFloat( &lightRadius );

   arc.ArchiveString( &moveteam );
   arc.ArchiveObjectPointer( ( Class ** )&teamchain );
   arc.ArchiveObjectPointer( ( Class ** )&teammaster );

   arc.ArchiveObjectPointer( ( Class ** )&bindmaster );
	arc.ArchiveBoolean( &bind_use_my_angles );
   arc.ArchiveVector( &localorigin );
   arc.ArchiveVector( &localangles );

   arc.ArchiveString( &target );
   arc.ArchiveString( &targetname );
   // add to target list to rebuild targetlists
   arc.ArchiveString( &killtarget );

   if ( arc.Loading() )
      {
	   // reset target stuff
	   SetTargetName( targetname.c_str() );
	   SetTarget( target.c_str() );
      }

   arc.ArchiveFloat( &health );
   arc.ArchiveFloat( &max_health );
   arc.ArchiveInteger( &deadflag );
   arc.ArchiveInteger( &flags );

   arc.ArchiveInteger( &watertype );
   arc.ArchiveInteger( &waterlevel );

   ArchiveEnum( takedamage, damage_t );

   arc.ArchiveSafePointer( &enemy );
   arc.ArchiveFloat( &pain_finished );
   arc.ArchiveFloat( &damage_debounce_time );
   arc.ArchiveInteger( &damage_type );

	arc.ArchiveBoolean( &detach_at_death );

	arc.ArchiveBoolean( &look_at_me );
   }

#include "worldspawn.h"

#endif

