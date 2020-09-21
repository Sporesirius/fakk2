//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/behavior.h                         $
// $Revision:: 62                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 7/27/00 10:55p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/behavior.h                             $
// 
// 62    7/27/00 10:55p Steven
// Improved DragEnemy stuff.
// 
// 61    7/21/00 3:47p Steven
// Improved teleport a lot.
// 
// 60    7/18/00 4:27p Steven
// Added speed to FlyClimb.
// 
// 59    7/13/00 3:43p Steven
// Added next_think_time to GetCloseToEnemy for simple path finding.
// 
// 58    7/12/00 11:37a Steven
// Added return_to_original_location to investigate.
// 
// 57    7/07/00 8:06a Steven
// Improved the investigation behavior to always look towards the noise
// position.
// 
// 56    7/05/00 2:28p Steven
// Improved fleeing behavior a lot.
// 
// 55    7/02/00 1:11p Steven
// Changed TeleportToPosition to use named pathnodes instead of hardcoded
// positions.
// 
// 54    6/30/00 10:35a Steven
// Added max_pains to Pain behavior.
// 
// 53    6/22/00 3:45p Markd
// fixed a bunch of saved game issues
// 
// 52    6/07/00 5:34p Steven
// Added TeleportToPosition and Levitate.
// 
// 51    6/05/00 3:41p Steven
// Adde GotoDeadEnemy.
// 
// 50    5/27/00 2:32p Steven
// Added FlyCloseToPlayer.
// 
// 49    5/25/00 7:52p Markd
// 2nd pass save game stuff
// 
// 48    5/24/00 4:08p Steven
// Added a forever variable to the HeadWatch behavior.
// 
// 47    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 46    5/20/00 4:47p Steven
// Improved Shock behavior.
// 
// 45    5/06/00 3:00p Steven
// Added speed to FlyCloseToEnemy and fixed actor's getting stuck on top of
// the player.
// 
// 44    5/03/00 11:27a Steven
// Added some sounds to the ghost attack and added the spooky ghost attack.
// 
// 43    4/28/00 5:40p Steven
// Added use_last_known_pos to TurnToEnemy and BurrowAttack.
// 
// 42    4/25/00 10:12a Steven
// Lots of improvements to the GhostAttack behavior.
// 
// 41    4/15/00 3:39p Steven
// Made it so the pain animation will randomly choose between all available
// pain animations not just the first 2.
// 
// 40    4/13/00 5:34p Steven
// Added the Teleport behavior and the GhostAttack behavior.
// 
// 39    4/08/00 3:58p Steven
// Took out walking stuff from PickupEntity.
// 
// 38    4/01/00 2:39p Steven
// Made it so actor can fly clockwise or counter-clockwise in FlyCircle.
// 
// 37    4/01/00 2:00p Steven
// Added a forever flag to GetCloseToEnemy.
// 
// 36    3/30/00 2:03p Steven
// More work on TorsoTurn.
// 
// 35    3/28/00 6:49p Steven
// Lots of improvements to TorsoTurn.
// 
// 34    3/17/00 11:52a Steven
// Added jumping stuff.
// 
// 33    3/14/00 12:07p Steven
// Added walkwatch stuff.
// 
// 32    3/07/00 11:51a Steven
// Made lots of tweaks to the CircleEnemy behavior.
// 
// 31    3/03/00 5:26p Steven
// Fixed up some save stuff.
// 
// 30    2/24/00 7:07p Steven
// Made talk so it would not stand up if already sitting and made it so the
// actor always tries to face whoever its talking to.
// 
// 29    2/24/00 5:26p Steven
// Added a max speed parm to head watch.
// 
// 28    2/23/00 11:57a Steven
// Moved utility behaviors to actor.
// 
// 27    2/21/00 7:00p Steven
// Added a TorsoTurn behavior.
// 
// 26    2/17/00 5:43p Steven
// Moved NearestNode stuff out of Investigate to Actor.
// 
// 25    2/16/00 6:04p Steven
// Tweaked the investigate behavior a lot.
// 
// 24    2/16/00 10:43a Steven
// Added a Pain behavior, made an option for FlyWander to make the actor try
// to fly upwards, and improved the Investigate behavior.
// 
// 23    2/11/00 6:41p Steven
// Improved headwatch a little and added pickup/throw.
// 
// 22    2/07/00 6:45p Steven
// Made it so the FlyCloseToEnemy behavior doesn't choose a new goal so often.
// 
// 21    2/04/00 1:55p Steven
// Added the talk behavior.
// 
// 20    2/02/00 1:39p Steven
// Added turning animations to TurnTo, added the HeadWatch behavior, and
// cleaned up flying code a little more.
// 
// 19    1/29/00 5:28p Steven
// Improved the BurrowAttack and DragEnemy behaviors.
// 
// 18    1/27/00 2:54p Steven
// Improved a lot of the flying code.
// 
// 17    1/21/00 6:45p Steven
// Made flee use chase instead of FollowPath.
// 
// 16    1/19/00 12:12p Steven
// Improved the TurnToEnemy and BurrowAttack behaviors.
// 
// 15    1/14/00 5:02p Steven
// Added gotonextstage and burrowattack behaviors.
// 
// 14    1/13/00 7:08p Steven
// Lots and lots of cleanup.
// 
// 13    1/07/00 8:12p Jimdose
// cleaning up unused code
// 
// 12    1/06/00 6:50p Steven
// Cleaned up GetCloseToEnemy.
// 
// 11    12/22/99 5:14p Steven
// Fixed some animation issues, some general clean up, and removed
// FemaleLympAttack.
// 
// 10    12/17/99 5:51p Steven
// Added the following behaviors : TurnTowardsEnemy, FlyCircle, FlyDive, and
// FlyClimb.
// 
// 9     12/01/99 3:43p Steven
// Added a land behavior for flying creatures.
// 
// 8     11/24/99 11:05a Steven
// More work on flying.
// 
// 7     11/19/99 2:05p Steven
// Made sure all behavior stuff would save correctly.
// 
// 6     11/19/99 11:33a Steven
// Added new behaviors: CircleEnemy, ShockWater, Shock, and CircleAttack.
// 
// 5     11/10/99 6:11p Steven
// Added the FlyCloseToEnemy behavior.
// 
// 4     10/28/99 6:07p Steven
// Improved the drag behavior.
// 
// 3     10/27/99 10:29a Steven
// Added GetNearestEnemy behavior and added more to the DragEnemy behavior.
// 
// 2     10/19/99 7:11p Steven
// Lots of AI work.
// 
// 1     9/10/99 10:53a Jimdose
// 
// 1     9/08/99 3:15p Aldie
// 
// 10    8/28/99 7:06p Steven
// Added a speed parameter to the spin behavior.
// 
// 9     8/28/99 11:46a Steven
// Added some spinning plant stuff.
// 
// 8     8/27/99 5:05p Steven
// Worked on digest behavior,and added spin.
// 
// 7     8/18/99 3:23p Steven
// Added to Digest behavior.
// 
// 6     8/17/99 4:59p Steven
// New digest behavior for the Sucknblaugh plant.
// 
// 5     8/11/99 5:57p Steven
// More general AI work.
// 
// 4     8/05/99 9:15a Steven
// New AI stuff.
// 
// DESCRIPTION:
// Standard class for creating AI behaviors
//

#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

#include "g_local.h"
#include "entity.h"
#include "path.h"
#include "steering.h"
#include "beam.h"
#include "sentient.h"

extern Event EV_Behavior_Args;
extern Event EV_Behavior_AnimDone;

class Actor;

class Behavior : public Listener
	{
	protected:
		PathNodePtr				movegoal;

	public:
      CLASS_PROTOTYPE( Behavior );

									Behavior();

      virtual void         ShowInfo( Actor &self );
		virtual void			Begin( Actor &self );
		virtual qboolean		Evaluate( Actor &self );
		virtual void			End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Behavior::Archive
	(
	Archiver &arc
	)
   {
   Listener::Archive( arc );

   arc.ArchiveSafePointer( &movegoal );
   }

typedef SafePtr<Behavior> BehaviorPtr;

class Idle : public Behavior
	{
	private:
		float						nexttwitch;

	public:
      CLASS_PROTOTYPE( Idle );

      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Idle::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveFloat( &nexttwitch );
   }

class Pain : public Behavior
	{
	private:
		int						current_pain_type;
		int						pain_anim_number;
		qboolean					anim_done;
		int						number_of_pains;
		int						max_pains;

	public:
      CLASS_PROTOTYPE( Pain );

		void						AnimDone( Event *ev );

		void						SetPainAnim( Actor &self, int new_pain_type, int new_anim_number );
		int						GetNumberOfPainAnims( Actor &self, int new_pain_type );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Pain::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

	arc.ArchiveInteger( &current_pain_type );
	arc.ArchiveInteger( &pain_anim_number );
	arc.ArchiveBoolean( &anim_done );
	arc.ArchiveInteger( &number_of_pains );
	arc.ArchiveInteger( &max_pains );
   }

class Watch : public Behavior
	{
	private:
		EntityPtr				ent_to_watch;
		Seek						seek;
		float						turn_speed;
		float						old_turn_speed;

	public:
      CLASS_PROTOTYPE( Watch );

									Watch();
		void						SetArgs(	Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void Watch::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveSafePointer( &ent_to_watch );
	arc.ArchiveObject( &seek );
   arc.ArchiveFloat( &turn_speed );
	arc.ArchiveFloat( &old_turn_speed );
   }

class Turn : public Behavior
	{
	private:
		float						turn_speed;

	public:
      CLASS_PROTOTYPE( Turn );

									Turn();
		void						SetArgs(	Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void Turn::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveFloat( &turn_speed );
   }

class CircleEnemy : public Behavior
	{
	private:
		EntityPtr				ent_to_circle;
		str						center_part_name;
		float						last_angle_change;

	public:
      CLASS_PROTOTYPE( CircleEnemy );

		void						SetArgs( Event *ev );
		float						GetAngleDiff( Actor &self, Actor *center_actor, Vector origin );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void CircleEnemy::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveSafePointer( &ent_to_circle );
	arc.ArchiveString( &center_part_name );
	arc.ArchiveFloat( &last_angle_change );
   }

class BurrowAttack : public Behavior
	{
	private:
		Vector					goal;
		Vector					attack_origin;
		int						burrow_mode;
		AnimatePtr				leg1;
		AnimatePtr				leg2;
		AnimatePtr				leg3;
		AnimatePtr				leg4;
		int						stage;
		int						attacks_left;
		float						burrow_speed;
		qboolean					too_close;
		qboolean					use_last_known_position;
	public:
      CLASS_PROTOTYPE( BurrowAttack );

		void						SetArgs( Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		void						SpawnArm( Actor &self, AnimatePtr &leg, Vector arm_origin, const char *anim_name, float angle );
		virtual void         Archive( Archiver &arc );
	};

inline void BurrowAttack::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

	arc.ArchiveVector( &goal );
	arc.ArchiveVector( &attack_origin );
	arc.ArchiveInteger( &burrow_mode );
	arc.ArchiveSafePointer( &leg1 );
	arc.ArchiveSafePointer( &leg2 );
	arc.ArchiveSafePointer( &leg3 );
	arc.ArchiveSafePointer( &leg4 );
	arc.ArchiveInteger( &stage );
	arc.ArchiveInteger( &attacks_left );
	arc.ArchiveFloat( &burrow_speed );
	arc.ArchiveBoolean( &too_close );
	arc.ArchiveBoolean( &use_last_known_position );
   }

class ShockWater : public Behavior
	{
	private:
		EntityPtr				left_beam;
		EntityPtr				right_beam;
		EntityPtr				center_beam;
		qboolean					already_started;

	public:
      CLASS_PROTOTYPE( ShockWater );

									ShockWater();
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void ShockWater::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveSafePointer( &left_beam );
	arc.ArchiveSafePointer( &right_beam );
	arc.ArchiveSafePointer( &center_beam );
	arc.ArchiveBoolean( &already_started );
   }

class Shock : public Behavior
	{
	private:
		EntityPtr				beam;
		str						tag_name;
		float						damage;
		qboolean					already_started;
		float						random_angle;
	public:
      CLASS_PROTOTYPE( Shock );

									Shock();
		void						SetArgs( Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void Shock::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveSafePointer( &beam );
	arc.ArchiveString( &tag_name );
	arc.ArchiveFloat( &damage );
	arc.ArchiveBoolean( &already_started );
	arc.ArchiveFloat( &random_angle );
   }

class CircleAttack : public Behavior
	{
	private:
		EntityPtr				first_part;
		EntityPtr				current_part;
		str						command;
		str						direction;
		float						next_time;
		int						current_direction;
		int						number_of_attacks;
	public:
      CLASS_PROTOTYPE( CircleAttack );

									CircleAttack();
		Actor						*FindClosestPart( Actor &self, float angle );
		void						SetArgs( Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void CircleAttack::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveSafePointer( &first_part );
	arc.ArchiveSafePointer( &current_part );
	arc.ArchiveString( &command );
	arc.ArchiveString( &direction );
	arc.ArchiveFloat( &next_time );
	arc.ArchiveInteger( &current_direction );
	arc.ArchiveInteger( &number_of_attacks );
   }

class DragEnemy : public Behavior
	{
	private:
		EntityPtr				ent_to_drag;
		str						tag_name;
		int						damage;
		float						target_yaw;
		float						last_turn_time;
		qboolean					attached;
		Vector					offset;
		qboolean					drop;
	public:
      CLASS_PROTOTYPE( DragEnemy );

		void						SetArgs( Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void DragEnemy::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveSafePointer( &ent_to_drag );
	arc.ArchiveString( &tag_name );
	arc.ArchiveInteger( &damage );
	arc.ArchiveFloat( &target_yaw );
	arc.ArchiveFloat( &last_turn_time );
	arc.ArchiveBoolean( &attached );
	arc.ArchiveVector( &offset );
	arc.ArchiveBoolean( &drop );
   }

class Spin : public Behavior
	{
	private:
		float speed;

	public:
      CLASS_PROTOTYPE( Spin );

									Spin();
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		void						SetArgs( Event *ev );
		virtual void         Archive( Archiver &arc );
	};

inline void Spin::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveFloat( &speed );
   }

class Digest : public Behavior
	{
	private:
		float						digest_time;
		float						spit_time;
		Container<EntityPtr>	foodlist;
		qboolean					anim_done;
		qboolean					spitting;
		qboolean					spit;
		qboolean					yuck;

		void						AnimDone( Event *ev );

	public:
      CLASS_PROTOTYPE( Digest );

      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		void						Eat( Entity *food, Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void Digest::Archive
	(
	Archiver &arc
	)
   {
   EntityPtr *temp;
	int num;
	int i;

   Behavior::Archive( arc );

	arc.ArchiveFloat( &digest_time );
	arc.ArchiveFloat( &spit_time );

   if ( arc.Loading() )
      {
      foodlist.FreeObjectList();
      }
   else
      {
	   num = foodlist.NumObjects();
      }
   arc.ArchiveInteger( &num );
   if ( arc.Loading() )
      {
      foodlist.Resize( num );
      }
	for( i = 1; i <= num; i++ )
		{
      temp = foodlist.AddressOfObjectAt( i );
		arc.ArchiveSafePointer( temp );
		}

	arc.ArchiveBoolean( &anim_done );
	arc.ArchiveBoolean( &spitting );
	arc.ArchiveBoolean( &spit );
	arc.ArchiveBoolean( &yuck );
   }

class Aim : public Behavior
	{
	private:
		Seek						seek;
		EntityPtr				target;

	public:
      CLASS_PROTOTYPE( Aim );

		void						SetTarget( Entity *ent );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Aim::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveObject( &seek );
   arc.ArchiveSafePointer( &target );
   }

class TurnTo : public Behavior
	{
	private:
		Seek						seek;
		EntityPtr				ent;
		Vector					dir;
		float						yaw;
		int						mode;
		qboolean					anim_done;

	public:
      CLASS_PROTOTYPE( TurnTo );

									TurnTo();
		void						SetDirection( float yaw );
		void						SetTarget( Entity *ent );
		void						AnimDone( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void TurnTo::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveObject( &seek );
   arc.ArchiveSafePointer( &ent );
   arc.ArchiveVector( &dir );
   arc.ArchiveFloat( &yaw );
   arc.ArchiveInteger( &mode );
	arc.ArchiveBoolean( &anim_done );
   }

class PickupEntity : public Behavior
	{
	private:
		str						pickup_anim_name;
		qboolean					anim_done;
		EntityPtr				ent_to_pickup;

	public:
      CLASS_PROTOTYPE( PickupEntity );

		void						SetArgs( Event *ev );
		void						AnimDone( Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void PickupEntity::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &pickup_anim_name );
   arc.ArchiveBoolean( &anim_done );
   arc.ArchiveSafePointer( &ent_to_pickup );
   }

class ThrowEntity : public Behavior
	{
	private:
		str						throw_anim_name;
		qboolean					anim_done;

	public:
      CLASS_PROTOTYPE( ThrowEntity );

		void						SetArgs( Event *ev );
		void						AnimDone( Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void ThrowEntity::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &throw_anim_name );
   arc.ArchiveBoolean( &anim_done );
   }

class HeadWatch : public Behavior
	{
	private:
		EntityPtr				ent_to_watch;
		Vector					current_head_angles;
		float						max_speed;
		qboolean					forever;
	public:
      CLASS_PROTOTYPE( HeadWatch );

									HeadWatch();
		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void HeadWatch::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

	arc.ArchiveSafePointer( &ent_to_watch );
	arc.ArchiveVector( &current_head_angles );
	arc.ArchiveFloat( &max_speed );
   arc.ArchiveBoolean( &forever );
   }

class TorsoTurn : public Behavior
	{
	private:
		int						turn_towards_enemy;
		float						speed;
		int						forever;
		float						current_yaw;
		float						current_pitch;
		str						tag_name;
		float						tolerance;
	public:
      CLASS_PROTOTYPE( TorsoTurn );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void TorsoTurn::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

	arc.ArchiveInteger( &turn_towards_enemy );
	arc.ArchiveFloat( &speed );
	arc.ArchiveInteger( &forever );
	arc.ArchiveFloat( &current_yaw );
	arc.ArchiveFloat( &current_pitch );
	arc.ArchiveString( &tag_name );
	arc.ArchiveFloat( &tolerance );
   }

class GotoPathNode : public Behavior
	{
	private:
		TurnTo					turnto;
		Chase						chase;
		int						state;
		qboolean					usevec;
		float						time;
		str						anim;
		EntityPtr				goalent;
		Vector					goal;
		EntityPtr				entity_to_watch;
		HeadWatch				head_watch;

	public:
      CLASS_PROTOTYPE( GotoPathNode );

									GotoPathNode();
		void						SetArgs( Event *ev );
		void						SetGoal( PathNode *node );
		void						AnimDone( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void GotoPathNode::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveObject( &turnto );
   arc.ArchiveObject( &chase );
   arc.ArchiveInteger( &state );
   arc.ArchiveBoolean( &usevec );
   arc.ArchiveFloat( &time );
   arc.ArchiveString( &anim );
   arc.ArchiveSafePointer( &goalent );
   arc.ArchiveVector( &goal );
	arc.ArchiveSafePointer( &entity_to_watch );
	arc.ArchiveObject( &head_watch );
   }

class Flee : public Behavior
	{
	private:
		Chase						chase;
		str						anim;
		PathNodePtr				flee_node;

	public:
      CLASS_PROTOTYPE( Flee );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		void						FindFleeNode( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Flee::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

	arc.ArchiveObject( &chase );
   arc.ArchiveString( &anim );
	arc.ArchiveSafePointer( &flee_node );
   }

class PlayAnim : public Behavior
	{
	private:
		str						anim;
		
	public:
      CLASS_PROTOTYPE( PlayAnim );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void PlayAnim::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
   }

class Talk : public Behavior
	{
	private:
		TurnTo					turnto;
		SentientPtr				ent_listening;
		float						original_yaw;
		float						yaw;
		int						mode;
		qboolean					move_allowed;
		
	public:
      CLASS_PROTOTYPE( Talk );

		void						SetUser( Sentient *user );
		void						AnimDone( Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Talk::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

	arc.ArchiveObject( &turnto );
   arc.ArchiveSafePointer( &ent_listening );
	arc.ArchiveFloat( &original_yaw );
	arc.ArchiveFloat( &yaw );
	arc.ArchiveInteger( &mode );
	arc.ArchiveBoolean( &move_allowed );
   }

class FindCover : public Behavior
	{
	private:
		str						anim;
		str						crouch_anim;
		Chase						chase;
		int						state;
		float						nextsearch;
		
	public:
      CLASS_PROTOTYPE( FindCover );

		void						SetArgs( Event *ev );
		PathNode					*FindCoverNode( Actor &self );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void FindCover::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
   arc.ArchiveString( &crouch_anim );
   arc.ArchiveObject( &chase );
   arc.ArchiveInteger( &state );
   arc.ArchiveFloat( &nextsearch );
   }

class FindFlee : public Behavior
	{
	private:
		str						anim;
		Chase						chase;
		int						state;
		float						nextsearch;
		
	public:
      CLASS_PROTOTYPE( FindFlee );

		void						SetArgs( Event *ev );
		PathNode					*FindFleeNode( Actor &self );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void FindFlee::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
   arc.ArchiveObject( &chase );
   arc.ArchiveInteger( &state );
   arc.ArchiveFloat( &nextsearch );
   }

class FindEnemy : public Behavior
	{
	private:
		str						anim;
		Chase						chase;
		int						state;
		float						nextsearch;
      PathNodePtr          lastSearchNode;
      Vector               lastSearchPos;
		
	public:
      CLASS_PROTOTYPE( FindEnemy );

		PathNode					*FindClosestSightNode( Actor &self );
		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void FindEnemy::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
   arc.ArchiveObject( &chase );
   arc.ArchiveInteger( &state );
   arc.ArchiveFloat( &nextsearch );
   arc.ArchiveSafePointer( &lastSearchNode );
   arc.ArchiveVector( &lastSearchPos );
   }

class AimAndShoot : public Behavior
	{
	private:
		Aim						aim;
		int						mode;
		int						maxshots;
		int						numshots;
		qboolean					animdone;
      float                enemy_health;
      float                aim_time;
      str                  animprefix;
      str                  aimanim;
      str                  fireanim;

	public:
      CLASS_PROTOTYPE( AimAndShoot );

									AimAndShoot();
		void						SetMaxShots( int num );
		void						SetArgs( Event *ev );
		void						AnimDone( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void AimAndShoot::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveObject( &aim );
   arc.ArchiveInteger( &mode );
   arc.ArchiveInteger( &maxshots );
   arc.ArchiveInteger( &numshots );
   arc.ArchiveBoolean( &animdone );
   arc.ArchiveFloat( &enemy_health );
   arc.ArchiveFloat( &aim_time );
   arc.ArchiveString( &animprefix );
   arc.ArchiveString( &aimanim );
   arc.ArchiveString( &fireanim );
   }

class AimAndMelee : public Behavior
	{
	private:
		Aim						aim;
		int						mode;
		int						maxshots;
		int						numshots;
		qboolean					animdone;
		str						anim_name;

	public:
      CLASS_PROTOTYPE( AimAndMelee );

									AimAndMelee();
		void						SetArgs( Event *ev );
		void						AnimDone( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void AimAndMelee::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveObject( &aim );
   arc.ArchiveInteger( &mode );
   arc.ArchiveInteger( &maxshots );
   arc.ArchiveInteger( &numshots );
   arc.ArchiveBoolean( &animdone );
	arc.ArchiveString( &anim_name );
   }

class JumpToPathNode : public Behavior
	{
	private:
		Jump						jump;
	public:
      CLASS_PROTOTYPE( JumpToPathNode );

		void						SetArgs( Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void JumpToPathNode::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveObject( &jump );
   }

class FlyToPoint : public Behavior
	{
	private:
      float                avoidtime;
		Vector					target_angle;
		float						turn_speed;
		float						speed;
		float						old_forward_speed;
		Vector					goal;
		qboolean					random_allowed;
		qboolean					force_goal;
		int						stuck;
		Vector					temp_goal;
		qboolean					use_temp_goal;

	public:
      CLASS_PROTOTYPE( FlyToPoint );

									FlyToPoint();

		void						SetTurnSpeed( float new_turn_speed );
		void						SetGoalPoint( Vector goal_point );
		void						SetRandomAllowed( qboolean allowed );
		void						SetSpeed( float speed_value );
		void						ForceGoal( void );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		float						LerpAngle( float old_angle, float new_angle, float lerp_amount );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void FlyToPoint::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveFloat( &avoidtime );
   arc.ArchiveVector( &target_angle );
	arc.ArchiveFloat( &turn_speed );
	arc.ArchiveFloat( &speed );
	arc.ArchiveFloat( &old_forward_speed );
   arc.ArchiveVector( &goal );
	arc.ArchiveBoolean( &random_allowed );
	arc.ArchiveBoolean( &force_goal );
	arc.ArchiveInteger( &stuck );
	arc.ArchiveVector( &temp_goal );
	arc.ArchiveBoolean( &use_temp_goal );
   }

class FlyCloseToEnemy : public Behavior
	{
	private:
		str						anim;
		float						turn_speed;
		float						speed;
		FlyToPoint				fly;
		float						next_goal_time;

	public:
      CLASS_PROTOTYPE( FlyCloseToEnemy );

									FlyCloseToEnemy();

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void FlyCloseToEnemy::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
	arc.ArchiveFloat( &turn_speed );
	arc.ArchiveFloat( &speed );
	arc.ArchiveObject( &fly );
	arc.ArchiveFloat( &next_goal_time );
   }

class FlyCloseToPlayer : public Behavior
	{
	private:
		str						anim;
		float						turn_speed;
		float						speed;
		FlyToPoint				fly;
		float						next_goal_time;

	public:
      CLASS_PROTOTYPE( FlyCloseToPlayer );

									FlyCloseToPlayer();

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void FlyCloseToPlayer::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
	arc.ArchiveFloat( &turn_speed );
	arc.ArchiveFloat( &speed );
	arc.ArchiveObject( &fly );
	arc.ArchiveFloat( &next_goal_time );
   }

class FlyWander : public Behavior
	{
	private:
		str						anim;
		float						turn_speed;
		float						speed;
		FlyToPoint				fly;
		float						change_course_time;
		float						next_change_course_time;
		float						original_z;
		Vector					goal;
		qboolean					try_to_go_up;

	public:
      CLASS_PROTOTYPE( FlyWander );

									FlyWander();

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void FlyWander::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
	arc.ArchiveFloat( &turn_speed );
	arc.ArchiveFloat( &speed );
	arc.ArchiveObject( &fly );
	arc.ArchiveFloat( &change_course_time );
	arc.ArchiveFloat( &next_change_course_time );
	arc.ArchiveFloat( &original_z );
	arc.ArchiveVector( &goal );
	arc.ArchiveBoolean( &try_to_go_up );
   }

class FlyCircle : public Behavior
	{
	private:
		str						anim;
		FlyToPoint				fly;
		float						original_z;
		qboolean					fly_clockwise;

	public:
      CLASS_PROTOTYPE( FlyCircle );

									FlyCircle();

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void FlyCircle::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
	arc.ArchiveObject( &fly );
	arc.ArchiveFloat( &original_z );
	arc.ArchiveBoolean( &fly_clockwise );
   }


class FlyDive : public Behavior
	{
	private:
		str						anim;
		FlyToPoint				fly;
		Vector					goal;
		float						speed;
		float						old_speed;
		float						damage;

	public:
      CLASS_PROTOTYPE( FlyDive );

									FlyDive();

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void FlyDive::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
	arc.ArchiveObject( &fly );
	arc.ArchiveVector( &goal );
	arc.ArchiveFloat( &speed );
	arc.ArchiveFloat( &old_speed );
	arc.ArchiveFloat( &damage );
   }

class FlyClimb : public Behavior
	{
	private:
		str						anim;
		FlyToPoint				fly;
		Vector					goal;
		float						height;
		float						speed;
		float						next_height_check;
		float						last_check_height;

	public:
      CLASS_PROTOTYPE( FlyClimb );

									FlyClimb();

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void FlyClimb::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
	arc.ArchiveObject( &fly );
	arc.ArchiveVector( &goal );
	arc.ArchiveFloat( &height );
	arc.ArchiveFloat( &speed );
	arc.ArchiveFloat( &next_height_check );
	arc.ArchiveFloat( &last_check_height );
   }

class Land : public Behavior
	{
	private:
		str						anim;

	public:
      CLASS_PROTOTYPE( Land );

									Land();

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Land::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
   }

// Fixme / don't think this works right now

class Wander : public Behavior
	{
	private:
      Seek                 seek;
		//ObstacleAvoidance    avoid;
		str						anim;
      float                avoidtime;
      Vector               avoidvec;

	public:
      CLASS_PROTOTYPE( Wander );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Wander::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveObject( &seek );
   //arc.ArchiveObject( &avoid );
   arc.ArchiveString( &anim );
   arc.ArchiveFloat( &avoidtime );
   arc.ArchiveVector( &avoidvec );
   }

class GetCloseToEnemy : public Behavior
	{
	private:
		str						anim;
		Chase						chase;
		Wander					wander;
		qboolean					forever;
		float						next_think_time;
		
	public:
      CLASS_PROTOTYPE( GetCloseToEnemy );
                        
		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void GetCloseToEnemy::Archive
	(
	Archiver &arc
	)

   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
   arc.ArchiveObject( &chase );
	arc.ArchiveObject( &wander );
	arc.ArchiveBoolean( &forever );
	arc.ArchiveFloat( &next_think_time );
   }

class GotoDeadEnemy : public Behavior
	{
	private:
		str						anim;
		Chase						chase;
		
	public:
      CLASS_PROTOTYPE( GotoDeadEnemy );
                        
		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void GotoDeadEnemy::Archive
	(
	Archiver &arc
	)

   {
   Behavior::Archive( arc );

   arc.ArchiveString( &anim );
   arc.ArchiveObject( &chase );
   }

class Investigate : public Behavior
	{
	private:
		Chase						chase;
		str						anim;
		Vector					goal;
		Vector					real_goal_position;
      float                curioustime;
		TurnTo					turnto;
		float						investigate_time;
		int						mode;
		Vector					start_pos;
		float						start_yaw;
		qboolean					return_to_original_location;

	public:
      CLASS_PROTOTYPE( Investigate );
									Investigate();
		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Investigate::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveObject( &chase );
   arc.ArchiveString( &anim );
   arc.ArchiveVector( &goal );
	arc.ArchiveVector( &real_goal_position );
   arc.ArchiveFloat( &curioustime );
	arc.ArchiveObject( &turnto );
	arc.ArchiveFloat( &investigate_time );
	arc.ArchiveInteger( &mode );
	arc.ArchiveVector( &start_pos );
	arc.ArchiveFloat( &start_yaw );
	arc.ArchiveBoolean( &return_to_original_location  );
   }


class TurnInvestigate : public Behavior
	{
	private:
		Seek						seek;
		str						left_anim;
		str						right_anim;
		float						turn_speed;
		Vector					goal;
	public:
      CLASS_PROTOTYPE( TurnInvestigate );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void TurnInvestigate::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveObject( &seek );
   arc.ArchiveString( &left_anim );
	arc.ArchiveString( &right_anim );
	arc.ArchiveFloat( &turn_speed );
   arc.ArchiveVector( &goal );
   }

class TurnToEnemy : public Behavior
	{
	private:
		Seek						seek;
		str						left_anim;
		str						right_anim;
		float						turn_speed;
		qboolean					forever;
		qboolean					anim_done;
		qboolean					use_last_known_position;
	public:
      CLASS_PROTOTYPE( TurnToEnemy );

		void						SetArgs( Event *ev );
		void						AnimDone( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void TurnToEnemy::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.ArchiveObject( &seek );
   arc.ArchiveString( &left_anim );
	arc.ArchiveString( &right_anim );
	arc.ArchiveFloat( &turn_speed );
	arc.ArchiveBoolean( &forever );
	arc.ArchiveBoolean( &anim_done );
	arc.ArchiveBoolean( &use_last_known_position );
   }

class Teleport : public Behavior
	{
	private:
	public:
      CLASS_PROTOTYPE( Teleport );

      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					TestPosition( Actor &self, int test_pos, Vector &good_position, qboolean use_enemy_dir );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	};

class TeleportToPosition : public Behavior
	{
	private:
		str						teleport_position_name;
		int						number_of_teleport_positions;
	public:
      CLASS_PROTOTYPE( TeleportToPosition );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					TestPosition( Actor &self, int test_pos, Vector &good_position );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void TeleportToPosition::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

	arc.ArchiveString( &teleport_position_name );
	arc.ArchiveInteger( &number_of_teleport_positions );
   }

class GhostAttack : public Behavior
	{
	private:
		int						mode;
		Vector					attack_dir;
		Vector					attack_position;
		Vector					retreat_position;
		FlyToPoint				fly;
		qboolean					real_attack;
	public:
      CLASS_PROTOTYPE( GhostAttack );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void GhostAttack::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

	arc.ArchiveInteger( &mode );
	arc.ArchiveVector( &attack_dir );
	arc.ArchiveVector( &attack_position );
	arc.ArchiveVector( &retreat_position );
	arc.ArchiveObject( &fly );
	arc.ArchiveBoolean( &real_attack );
   }

class Levitate : public Behavior
	{
	private:
		float						distance;
		float						speed;
		float						final_z;
	public:
      CLASS_PROTOTYPE( Levitate );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void         Archive( Archiver &arc );
	};

inline void Levitate::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

	arc.ArchiveFloat( &distance );
	arc.ArchiveFloat( &speed );
	arc.ArchiveFloat( &final_z );
   }

#endif /* behavior.h */
