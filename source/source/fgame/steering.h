//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/steering.h                         $
// $Revision:: 13                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 6/26/00 4:53p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/steering.h                              $
// 
// 13    6/26/00 4:53p Steven
// Fixed some save/load game issues.
// 
// 12    6/06/00 2:51p Steven
// Added use_nearest_node to chase.
// 
// 11    5/27/00 2:56p Markd
// Save games 2nd pass
// 
// 10    5/24/00 3:14p Markd
// first phase of save/load games
// 
// 9     4/24/00 3:47p Steven
// Added allow fail and last_avoidvec.
// 
// 8     3/17/00 12:03p Steven
// Added jumping stuff.
// 
// 7     2/18/00 6:56p Steven
// Made many more improvements to path finding.
// 
// 6     1/21/00 6:46p Steven
// Fixed/improved obstacle avoidance and added it to the chase behavior and
// also added opening doors to chase.
// 
// 5     1/13/00 7:09p Steven
// Lots and lots of cleanup.
// 
// 4     1/07/00 8:12p Jimdose
// cleaning up unused code
// 
// 3     1/06/00 7:02p Steven
// Cleaned up the chase behavior a lot.
// 
// 2     12/22/99 6:00p Steven
// Some cleanup.
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 4     8/27/99 5:08p Steven
// Optimized movement code a little.
//
// DESCRIPTION:
// Steering behaviors for AI.
// 

#ifndef __STEERING_H__
#define __STEERING_H__

#include "g_local.h"
#include "entity.h"
#include "path.h"

class Actor;

class Steering : public Listener
	{
	public:
		Vector					steeringforce;
		Vector					origin;
		Vector					movedir;
		float						maxspeed;

      CLASS_PROTOTYPE( Steering );

									Steering();

      virtual void         ShowInfo( Actor &self );
		virtual void			Begin( Actor &self );
		virtual qboolean		Evaluate( Actor &self );
		virtual void			End( Actor &self );

      void						ResetForces( void );
		void						SetPosition( Vector pos );
		void						SetDir( Vector dir );
		void						SetMaxSpeed( float speed );

		virtual void			DrawForces( void );
	   virtual void         Archive( Archiver &arc );
	};

inline void Steering::Archive
	(
	Archiver &arc
	)

   {
   Listener::Archive( arc );

   arc.ArchiveVector( &steeringforce );
	arc.ArchiveVector( &origin );
	arc.ArchiveVector( &movedir );
	arc.ArchiveFloat( &maxspeed );
   }

class Seek : public Steering
	{
	protected:
		Vector					targetposition;
		Vector					targetvelocity;

	public:
      CLASS_PROTOTYPE( Seek );

									Seek();
		void						SetTargetPosition( Vector pos );
		void						SetTargetVelocity( Vector vel );
      void                 ShowInfo( Actor &self );
		qboolean					Evaluate( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Seek::Archive
	(
	Archiver &arc
	)

   {
   Steering::Archive( arc );

   arc.ArchiveVector( &targetposition );
	arc.ArchiveVector( &targetvelocity );
   }

class ObstacleAvoidance : public Steering
	{
	protected:
      qboolean             avoidwalls;
		EntityPtr				target_ent;

	public:
      CLASS_PROTOTYPE( ObstacleAvoidance );

                           ObstacleAvoidance();
      void                 AvoidWalls( qboolean );
		void						SetTargetEnt( Entity *ent );
      void                 ShowInfo( Actor &self );
		qboolean					Evaluate( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void ObstacleAvoidance::Archive
	(
	Archiver &arc
	)

   {
   Steering::Archive( arc );

	arc.ArchiveBoolean( &avoidwalls );
	arc.ArchiveSafePointer( &target_ent );
   }

class Jump : public Steering
	{
	private:
		float						endtime;
		float						speed;
		str						anim;
      int                  state;
		qboolean					animdone;
      Vector               goal;

	public:
      CLASS_PROTOTYPE( Jump );

									Jump();
		void						SetGoal( const char *node_name );
		void						SetEntity( Entity *ent_to_jump_to );
		void						SetSpeed( float jump_speed );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Jump::Archive
	(
	Archiver &arc
	)
   {
   Steering::Archive( arc );

   arc.ArchiveFloat( &endtime );
   arc.ArchiveFloat( &speed );
   arc.ArchiveString( &anim );
   arc.ArchiveInteger( &state );
   arc.ArchiveBoolean( &animdone );
   arc.ArchiveVector( &goal );
   }

class FollowPath : public Steering
	{
	protected:
		PathPtr					path;
		Seek						seek;
      PathNodePtr          currentNode;
		Jump						jump;
		qboolean					jumping;
		str						old_anim;

      void                 FindCurrentNode( Actor &self );

	public:
      CLASS_PROTOTYPE( FollowPath );
						
									FollowPath();
									~FollowPath();
		void						SetPath( Path *newpath );
		Path						*SetPath( Actor &self, Vector from, Vector to );
		qboolean					DoneWithPath( Actor &self );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		virtual void			DrawForces( void );
	   virtual void         Archive( Archiver &arc );
	};

inline void FollowPath::Archive
	(
	Archiver &arc
	)

   {
	qboolean temp_bool;
	Path *path_ptr;


   Steering::Archive( arc );

	if ( arc.Saving() )
		{
		if ( path )
			{
			temp_bool = true;
			arc.ArchiveBoolean( &temp_bool );
			path_ptr = path;
			arc.ArchiveObject( path_ptr );
			}
		else
			{
			temp_bool = false;
			arc.ArchiveBoolean( &temp_bool );
			}
		}
   else
		{
		arc.ArchiveBoolean( &temp_bool );

		if ( temp_bool )
			path = ( Path * )arc.ReadObject();
		else
			path = NULL;
		}

   arc.ArchiveObject( &seek );
   arc.ArchiveSafePointer( &currentNode );
   arc.ArchiveObject( &jump );
   arc.ArchiveBoolean( &jumping );
   arc.ArchiveString( &old_anim );
   }

class Chase : public Steering
	{
	private:
		Seek						seek;
		FollowPath				follow;
		ObstacleAvoidance		avoid;
		float						nextpathtime;
		float						nextwalktotime;
		PathPtr					path;
		Vector					goal;
		EntityPtr				goalent;
		PathNodePtr          goalnode;
		qboolean					usegoal;
      float                newpathrate;

      Vector               wanderstart;
      int                  wander_mode;
      float                wandertime;
      int                  stuck;
      Vector               avoidvec;
		Vector               last_avoidvec;
		int						mode;

		qboolean					blocked_by_door;
		str						old_anim;

		qboolean					allow_fail;
		qboolean					use_nearest_node;

	public:
      CLASS_PROTOTYPE( Chase );

									Chase();
		void						SetPath( Path *newpath );
		void						SetGoalPos( Vector pos );
		void						SetGoal( PathNode *node );
		void						SetTarget( Entity *ent );
      void                 SetPathRate( float rate );
		void						AllowFail( qboolean fail );
		void						UseNearestNode( qboolean use_nearest );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		Vector					ChooseRandomDirection( Actor &self );
	   virtual void         Archive( Archiver &arc );
	};

inline void Chase::Archive
	(
	Archiver &arc
	)

   {
   Steering::Archive( arc );

   arc.ArchiveObject( &seek );
   arc.ArchiveObject( &follow );
	arc.ArchiveObject( &avoid );
   arc.ArchiveFloat( &nextpathtime );
	arc.ArchiveFloat( &nextwalktotime );

   arc.ArchiveSafePointer( &path );

   arc.ArchiveVector( &goal );
   arc.ArchiveSafePointer( &goalent );
   arc.ArchiveSafePointer( &goalnode );
   arc.ArchiveBoolean( &usegoal );
   arc.ArchiveFloat( &newpathrate );
   arc.ArchiveVector( &wanderstart );
   arc.ArchiveInteger( &wander_mode );
   arc.ArchiveFloat( &wandertime );
   arc.ArchiveInteger( &stuck );
   arc.ArchiveVector( &avoidvec );
	arc.ArchiveVector( &last_avoidvec );
   arc.ArchiveInteger( &mode );
	arc.ArchiveBoolean( &blocked_by_door );
	arc.ArchiveString( &old_anim );
	arc.ArchiveBoolean( &allow_fail );
	arc.ArchiveBoolean( &use_nearest_node );
   }

#endif /* steering.h */
