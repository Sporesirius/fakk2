//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/steering.cpp                       $
// $Revision:: 24                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 7/29/00 7:10p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/steering.cpp                            $
// 
// 24    7/29/00 7:10p Steven
// Fixed a jumping bug.
// 
// 23    7/29/00 1:24p Steven
// Fixed a jumping problem and fixed ChooseRandomDirection not using feet width
// stuff.
// 
// 22    6/23/00 4:55p Steven
// Made actors use doors correctly.
// 
// 21    6/07/00 5:35p Steven
// More no path work.
// 
// 20    6/06/00 2:51p Steven
// Added use_nearest_node to chase.
// 
// 19    5/03/00 11:27a Steven
// Small cleanup.
// 
// 18    5/01/00 11:26a Steven
// Made no path found warning message print out more info.
// 
// 17    4/24/00 3:13p Steven
// Added allow fail to chase and improved wander mode in chase a little.
// 
// 16    3/24/00 6:33p Steven
// Made an optimization to Chase::ChooseRandomDirection.
// 
// 15    3/17/00 11:52a Steven
// Added jumping stuff.
// 
// 14    2/18/00 6:56p Steven
// Made many more improvements to path finding.
// 
// 13    2/17/00 5:45p Steven
// Lots of path finding improvements.
// 
// 12    2/16/00 10:43a Steven
// Made chase return if no path found to goal.
// 
// 11    1/21/00 6:46p Steven
// Fixed/improved obstacle avoidance and added it to the chase behavior and
// also added opening doors to chase.
// 
// 10    1/13/00 7:08p Steven
// Lots and lots of cleanup.
// 
// 9     1/07/00 8:12p Jimdose
// cleaning up unused code
// 
// 8     1/06/00 7:02p Steven
// Cleaned up the chase behavior a lot.
// 
// 7     1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 6     12/22/99 6:00p Steven
// Some cleanup.
// 
// 5     10/01/99 4:52p Markd
// Made Warning level 4 work on all projects
// 
// 4     10/01/99 2:14p Steven
// Removing doaction stuff.
// 
// 3     9/20/99 6:57p Steven
// Use CanWalkTo instead of CanMoveTo when trying to walk straight to
// destination.
// 
// 2     9/16/99 11:18a Markd
// Continuing merge of code, not functional yet but closer
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 9     8/31/99 9:22p Steven
// Improved path finding some.
// 
// 8     8/27/99 5:08p Steven
// Optimized movement code a little.
// 
// 7     8/18/99 3:29p Jimdose
// added cylindrical collision detection
//
// DESCRIPTION:
// Steering behaviors for AI.
//

#include "g_local.h"
#include "steering.h"
#include "actor.h"

/****************************************************************************

  Steering Class Definition

****************************************************************************/

CLASS_DECLARATION( Listener, Steering, NULL )
	{
		{ NULL, NULL }
	};

Steering::Steering()
	{
	steeringforce = vec_zero;

	origin = vec_zero;
	movedir  = vec_zero;
	maxspeed = 320;
	}

void Steering::ShowInfo
	(
	Actor &self
	)

	{
   gi.Printf( "steeringforce: ( %f, %f, %f )\n", steeringforce.x, steeringforce.y, steeringforce.z );
   gi.Printf( "origin: ( %f, %f, %f )\n", origin.x, origin.y, origin.z );
   gi.Printf( "movedir: ( %f, %f, %f )\n", movedir.x, movedir.y, movedir.z );
   gi.Printf( "maxspeed: %f\n", maxspeed );
	}

void Steering::Begin
	(
	Actor &self
	)

	{
	}

qboolean	Steering::Evaluate
	(
	Actor &self
	)

	{
	return false;
	}

void Steering::End
	(
	Actor &self
	)

	{
	}

void Steering::DrawForces
	(
	void
	)

	{
	G_Color3f( 0.3, 0.5, 1 );
	G_BeginLine();
	G_Vertex( origin );
	G_Vertex( origin + steeringforce * FRAMETIME );
	G_EndLine();

	G_Color3f( 1, 0, 1 );
	G_BeginLine();
	G_Vertex( origin );
	G_Vertex( origin + movedir * maxspeed * FRAMETIME );
	G_EndLine();
	}

void Steering::SetPosition
	(
	Vector pos
	)

	{
	origin = pos;
	}

void Steering::SetDir
	(
	Vector dir
	)

	{
	movedir = dir;
	}

void Steering::SetMaxSpeed
	(
	float speed
	)

	{
	maxspeed = speed;
	}


void Steering::ResetForces
	(
	void
	)

	{
	steeringforce = vec_zero;
	}

/****************************************************************************

  Seek Class Definition

****************************************************************************/

CLASS_DECLARATION( Steering, Seek, NULL )
	{
		{ NULL, NULL }
	};

Seek::Seek()
	{
	targetposition = vec_zero;
	targetvelocity = vec_zero;
	}

void Seek::SetTargetPosition
	(
	Vector pos
	)

	{
	targetposition = pos;
	}

void Seek::SetTargetVelocity
	(
	Vector vel
	)

	{
	targetvelocity = vel;
	}

void Seek::ShowInfo
	(
	Actor &self
	)

	{
   Steering::ShowInfo( self );

   gi.Printf( "\ntargetposition: ( %f, %f, %f )\n", targetposition.x, targetposition.y, targetposition.z );
   gi.Printf( "targetvelocity: ( %f, %f, %f )\n", targetvelocity.x, targetvelocity.y, targetvelocity.z );
	}

qboolean	Seek::Evaluate
	(
	Actor &self
	)

	{
	Vector	predictedposition;
	Vector	dir;
	Vector	delta;
	Vector	ang1;
	Vector	ang2;
	float		dist;
   float    xydist;


	ResetForces();

	delta = targetposition - origin;
	dist = delta.length();
  
   // null out z component
   
   delta.z = 0;
	xydist = delta.length();

	predictedposition = targetposition + targetvelocity * ( dist / maxspeed );

	dir = predictedposition - origin;
	dir.normalize();

	ang1 = dir.toAngles();
	ang2 = movedir.toAngles();

	steeringforce[PITCH] = ang1[PITCH] - ang2[PITCH];
	if ( steeringforce[PITCH] <= -180 )
		{
		steeringforce[PITCH] += 360;
		}
	if ( steeringforce[PITCH] >= 180 )
		{
		steeringforce[PITCH] -= 360;
		}

	steeringforce[YAW] = ang1[YAW] - ang2[YAW];
	if ( steeringforce[YAW] <= -180 )
		{
		steeringforce[YAW] += 360;
		}
	if ( steeringforce[YAW] >= 180 )
		{
		steeringforce[YAW] -= 360;
		}

	// If we're nearly there, turn directly toward our goal

	if ( xydist < self.movespeed / 10 )
		{
		self.angles[YAW] = ang1[YAW];
		self.setAngles( self.angles );
		steeringforce = vec_zero;
		}

	if ( xydist <= self.total_delta.length() )
		{
		self.total_delta = self.animdir * xydist;
		return false;
		}

	steeringforce[ROLL] = 0;

	return true;
	}

/****************************************************************************

  ObstacleAvoidance Class Definition

****************************************************************************/

CLASS_DECLARATION( Steering, ObstacleAvoidance, NULL )
	{
		{ NULL, NULL }
	};

ObstacleAvoidance::ObstacleAvoidance()
   {
   avoidwalls = true;
   }

void ObstacleAvoidance::AvoidWalls
   (
   qboolean avoid
   )

   {
   avoidwalls = avoid;
   }

void ObstacleAvoidance::SetTargetEnt
   (
   Entity *ent
   )

   {
   target_ent = ent;
   }

void ObstacleAvoidance::ShowInfo
	(
	Actor &self
	)

	{
   Steering::ShowInfo( self );

   gi.Printf( "\navoidwalls: %d\n", avoidwalls );
	}

qboolean	ObstacleAvoidance::Evaluate
	(
	Actor &self
	)

	{
	Vector	predictedposition;
	Vector	normal;
	Vector	angles;
	Vector	dir;
	Vector	left;
	Vector	delta;
	float		urgency;
	float		dot;
	trace_t	trace;
	Entity	*ent;

	ResetForces();

	angles = self.movedir.toAngles();
	angles.AngleVectors( NULL, &left, NULL );

   origin.z += 1;
	predictedposition = origin + movedir * maxspeed * 2;

	trace = G_Trace( origin, self.mins, self.maxs, predictedposition, &self, self.edict->clipmask, false, "ObstacleAvoidance" );

	if ( trace.fraction < 1 )
		{
		urgency = 1.0 - trace.fraction;
		normal  = trace.plane.normal;
		ent     = trace.ent->entity;

		if ( ent->getSolidType() != SOLID_BSP )
			{
			if ( ent == target_ent )
				return true;

         dot = left * ( ent->origin - origin );
			}
		else
			{
         if ( !avoidwalls )
            {
   			return true;
            }

         dot = left * normal;
			}

		if ( dot < 0 )
			{
			// turn left
			steeringforce = Vector( 0, 90, 0 ) * urgency;
			}
		else
			{
			// turn right
			steeringforce = Vector( 0, -90, 0 ) * urgency;
			}
		}
	else
		{
		return true;
		}

	return true;
	}

/****************************************************************************

  FollowPath Class Definition

****************************************************************************/

CLASS_DECLARATION( Steering, FollowPath, NULL )
	{
		{ NULL, NULL }
	};

FollowPath::FollowPath()
	{
	path = NULL;
   currentNode = NULL;
	}

FollowPath::~FollowPath()
	{
   currentNode = NULL;
   if ( path )
      {
	   delete path;
      }
	}

void FollowPath::FindCurrentNode
   (
   Actor &self
   )

   {
   // Sometimes the second node on the path is the proper node to start from.
   // This happens because instead of creating the shortest path from the actor,
   // we create the shortest path from his nearest node.  Often, this creates a
   // path where he may already be further along the path than the first node,
   // causing him to "go back" along the path.  By checking if we can get to the
   // second node, we get rid of the backtracking.
   PathNode *node;

   if ( !path )
      {
      currentNode = NULL;
      return;
      }

   currentNode = path->NextNode();

   if ( path->NumNodes() < 2 )
      {
      return;
      }

   node = path->GetNode( 2 );

	if ( self.CanWalkTo( node->origin ) )
      {
      currentNode = path->NextNode();
      }
   }

void FollowPath::SetPath
	(
	Path *newpath
	)

	{
	if ( path )
		{
		delete path;
		}

   currentNode = NULL;

   path = newpath;
	}

Path *FollowPath::SetPath
	(
	Actor &self,
	Vector from,
	Vector to
	)

	{
	PathNode *goal;
	PathNode *node;
	StandardMovePath find;

	if ( path )
		{
		delete path;
		path = NULL;
		}

   currentNode = NULL;

   goal = PathManager.NearestNode( to, &self );
	if ( !goal )
		{
	   return NULL;
		}

	node = PathManager.NearestNode( from, &self );
	if ( !node || ( goal == node ) )
		{
		return NULL;
		}

	find.heuristic.setSize( self.size );
	find.heuristic.entnum = self.entnum;
	find.heuristic.can_jump = self.CanJump();

	path = find.FindPath( node, goal );

	return path;
	}

void FollowPath::DrawForces
	(
	void
	)

	{
   seek.DrawForces();
	}

qboolean FollowPath::DoneWithPath
	(
	Actor &self
	)

	{
	if ( !path )
		{
		return true;
		}

	return ( currentNode == NULL );
	}

void FollowPath::ShowInfo
	(
	Actor &self
	)

	{
   Steering::ShowInfo( self );

   if ( path )
      {
      gi.Printf( "\npath : ( %f, %f, %f ) to ( %f, %f, %f )\n",
         path->Start()->origin.x, path->Start()->origin.y, path->Start()->origin.z,
         path->End()->origin.x, path->End()->origin.y, path->End()->origin.z );
      }
   else
      {
      gi.Printf( "\npath : NULL\n" );
      }

   gi.Printf( "seek:\n" );
   seek.ShowInfo( self );

   if ( currentNode )
      {
      gi.Printf( "currentNode: ( %f, %f, %f )\n",
         currentNode->origin.x, currentNode->origin.y, currentNode->origin.z );
      }
   else
      {
      gi.Printf( "currentNode: NULL\n" );
      }
	}

void FollowPath::Begin
	(
	Actor &self
	)

	{
	seek.Begin( self );
	jumping = false;
	}

qboolean	FollowPath::Evaluate
	(
	Actor &self
	)

	{
	PathNode *lastnode;
   Vector delta;
   Vector targetpos;

   ResetForces();

   if ( !path )
      {
      return false;
      }

   // the first time we come through here with a path, currentNode is NULL.
   if ( !currentNode )
      {
      FindCurrentNode( self );
      if ( !currentNode )
         {
         delete path;
         path = NULL;
         return false;
         }
      }

	if ( jumping )
		{
		if ( !jump.Evaluate( self ) )
			{
			jump.End( self );
			jumping = false;
			self.SetAnim( old_anim );
			}
		return true;
		}

   targetpos = currentNode->origin;

   // check if the remaining distance is less than the
   // distance we'll travel this frame.
   delta = targetpos - self.origin;

   // check if the squared distance remaining is less than
   // the squared distance we'll travel
   if ( delta * delta <= self.frame_delta * self.frame_delta )
      {
      lastnode = currentNode;
      currentNode = path->NextNode();

      // if we're not done with the path, steer toward the next node
      if ( currentNode )
         {
         targetpos = currentNode->origin;

			//if ( lastnode->nodeflags & AI_JUMP && currentNode->nodeflags & AI_JUMP )
			if ( lastnode->nodeflags & AI_JUMP && lastnode->target.length() && lastnode->target == currentNode->targetname )
				{
				jumping = true;
				old_anim = self.animname;
				jump.SetGoal( currentNode->targetname );
				jump.Begin( self );
				}
         }
      else
         {
         delete path;
         path = NULL;

         return false;
         }
		}

   // steer toward our next path node
	seek.SetTargetPosition( targetpos );
	seek.SetTargetVelocity( vec_zero );
	seek.SetMaxSpeed( self.movespeed );
	seek.SetPosition( origin );
	seek.SetDir( self.movedir );
	seek.Evaluate( self );

	steeringforce = seek.steeringforce;

	return ( currentNode != NULL );
	}

void FollowPath::End
	(
	Actor &self
	)

	{
	seek.End( self );
	}

/****************************************************************************

  Chase Class Definition

****************************************************************************/

#define CHASE_MODE_DIRECT    0
#define CHASE_MODE_USE_PATH  1
#define CHASE_MODE_WANDER    2

#define CHASE_WANDER_MODE_START   0
#define CHASE_WANDER_MODE_WANDER  1

CLASS_DECLARATION( Steering, Chase, NULL )
	{
		{ NULL, NULL }
	};

Chase::Chase()
	{
	goalent = NULL;
	goal = vec_zero;
	goalnode = NULL;
   usegoal = false;
   newpathrate = 2;
	mode = CHASE_MODE_DIRECT;
	allow_fail = false;
	use_nearest_node = true;
	}

void Chase::SetPath
	(
	Path *newpath
	)

	{
	follow.SetPath( newpath );
	path = newpath;
	}

void Chase::SetGoalPos
	(
	Vector goalpos
	)

	{
	goal = goalpos;
   usegoal = true;
	goalent = NULL;
   goalnode = NULL;
	}

void Chase::SetGoal
	(
	PathNode *node
	)

	{
   goalnode = node;
   usegoal = false;
   goalent = NULL;
	}

void Chase::SetTarget
	(
	Entity *ent
	)

	{
	goalent = ent;
   goalnode = NULL;
   usegoal = false;
	}

void Chase::SetPathRate
   (
   float rate
   )

   {
   newpathrate = rate;
   }

void Chase::AllowFail
   (
   qboolean fail
   )

   {
   allow_fail = fail;
   }

void Chase::UseNearestNode
	(
	qboolean use_nearest
	)

	{
	use_nearest_node = use_nearest;
	}

void Chase::ShowInfo
	(
	Actor &self
	)

	{
   Steering::ShowInfo( self );

	if ( mode == CHASE_MODE_DIRECT )
		gi.Printf( "mode = DIRECT\n" );
	else if ( mode == CHASE_MODE_USE_PATH )
		gi.Printf( "mode = USE PATH\n" );
	else if ( mode == CHASE_MODE_WANDER )
		gi.Printf( "mode = WANDER\n" );

   gi.Printf( "\nseek:\n" );
   seek.ShowInfo( self );

   gi.Printf( "\nfollow:\n" );
   follow.ShowInfo( self );

   gi.Printf( "\nnextpathtime: %f\n", nextpathtime );

   if ( path )
      {
      gi.Printf( "\npath : ( %f, %f, %f ) to ( %f, %f, %f )\n",
         path->Start()->origin.x, path->Start()->origin.y, path->Start()->origin.z,
         path->End()->origin.x, path->End()->origin.y, path->End()->origin.z );
      }
   else
      {
      gi.Printf( "\npath : NULL\n" );
      }

   gi.Printf( "goal: ( %f, %f, %f )\n", goal.x, goal.y, goal.z );

   if ( goalent )
      {
      gi.Printf( "\ngoalent: #%d '%s'\n", goalent->entnum, goalent->targetname.c_str() );
      }
   else
      {
      gi.Printf( "\ngoalent: NULL\n" );
      }

   if ( goalnode )
      {
      gi.Printf( "\ngoalnode: #%d '%s' ( %f, %f, %f )\n", goalnode->nodenum, goalnode->targetname.c_str(),
         goalnode->origin.x, goalnode->origin.y, goalnode->origin.z );
      }
   else
      {
      gi.Printf( "\ngoalnode: NULL\n" );
      }

   gi.Printf( "usegoal: %d\n", usegoal );
   gi.Printf( "newpathrate: %f\n", newpathrate );
   gi.Printf( "wander_mode: %d\n", wander_mode );
   gi.Printf( "stuck: %d\n", stuck );
   gi.Printf( "avoidvec : ( %f, %f, %f )\n", avoidvec.x, avoidvec.y, avoidvec.z );
	}

void Chase::Begin
	(
	Actor &self
	)

	{
	nextpathtime = 0;
	nextwalktotime = 0;
	path = NULL;
	seek.Begin( self );
	follow.Begin( self );

	avoid.AvoidWalls( false );
	avoid.Begin( self );

   stuck = 0;
	blocked_by_door = false;
	}

qboolean	Chase::Evaluate
	(
	Actor &self
	)

	{
	qboolean result;
	trace_t trace;
	Vector target;
	int target_entnum;
	Vector pos;
	Vector dir;
	Vector avoid_dir;
	Vector steering_angles;
	Vector steering_dir;
	Vector new_avoidvec;


	if ( !usegoal && !goalnode && ( !goalent || goalent->deadflag ) )
		{
		return false;
		}

	ResetForces();

	if ( self.lastmove == STEPMOVE_BLOCKED_BY_DOOR && !blocked_by_door )
		{
		blocked_by_door = true;

		old_anim = self.animname;

		self.SetAnim( "idle" );
		}

	if ( blocked_by_door )
		{
		Entity *door;

		trace = G_Trace( self.origin, self.mins, self.maxs, self.origin + self.movedir * 50, &self, self.edict->clipmask, false, "ChaseDoor" );

		if ( trace.ent )
         {
		   door = trace.ent->entity;
		   if ( door && door->isSubclassOf( Door ) )
            {            
				//Event *ev = new Event( EV_Door_TryOpen );
				Event *ev = new Event( EV_Use );
				ev->AddEntity( &self );
				door->PostEvent( ev, 0 );

				return true;
				}
			}

		blocked_by_door = false;
		self.SetAnim( old_anim );
		}

   if ( mode != CHASE_MODE_WANDER )
      {
      if ( self.lastmove == STEPMOVE_OK )
         {
         stuck = 0;
         }
      else
         {
         stuck++;
         if ( stuck >= 2 )
            {
            stuck = 0;

				if ( mode == CHASE_MODE_DIRECT )
					{
					mode = CHASE_MODE_USE_PATH;
					}
				else
					{
					mode = CHASE_MODE_WANDER;
					wander_mode = CHASE_WANDER_MODE_START;
					}
            }
         }
      }

	if ( mode == CHASE_MODE_WANDER )
		{
		if ( self.lastmove != STEPMOVE_OK )
         {
         stuck++;
			}
        
		if ( wander_mode == CHASE_WANDER_MODE_START || stuck >= 4 )
			{
			//avoidvec[0] = G_Random( 100 ) - 50 + self.origin[0];
			//avoidvec[1] = G_Random( 100 ) - 50 + self.origin[1];
			//avoidvec[2] = self.origin[2];

			new_avoidvec = ChooseRandomDirection( self );

			last_avoidvec = avoidvec;
			avoidvec      = new_avoidvec;
			stuck = 0;
			}

		if ( wander_mode == CHASE_WANDER_MODE_START )
			{
			wanderstart = self.origin;
			wandertime  = level.time + 2;
			wander_mode = CHASE_WANDER_MODE_WANDER;
			}

		// Wander
		seek.SetTargetPosition( avoidvec );
		seek.SetTargetVelocity( vec_zero );
		seek.SetPosition( self.origin );
		seek.SetDir( self.movedir );
		seek.SetMaxSpeed( self.movespeed );

		if ( wandertime <= level.time || !seek.Evaluate( self ) )
			{
			mode = CHASE_MODE_DIRECT;
			stuck = 0;
			}

		steeringforce = seek.steeringforce;
		}

	if ( path && follow.DoneWithPath( self ) )
		{
		path = NULL;
		nextpathtime = 0;
		}

	if ( goalent && ( goalent->edict->solid != SOLID_NOT ) && ( goalent->edict->solid != SOLID_TRIGGER ) )
		{
      trace = G_Trace( self.origin, self.mins, self.maxs, self.origin +
			Vector( self.orientation[ 0 ] ) * self.movespeed * 0.1, &self, self.edict->clipmask, false, "Chase" );
		if ( trace.ent && trace.ent->entity == goalent )
			{
			stuck = 0;
			return false;
			}
      }

	if ( goalnode )
		{
		target        = goalnode->origin;
		target_entnum = ENTITYNUM_NONE;
		}
	else if ( goalent )
		{
		target        = goalent->origin;
		target_entnum = goalent->entnum;
		}
	else
		{
		target        = goal;
		target_entnum = ENTITYNUM_NONE;
		}

	if ( mode == CHASE_MODE_DIRECT )
		{
		// See if we should stop direct mode

		if ( nextwalktotime < level.time )
			{
			if ( !self.CanWalkTo( target, target_entnum ) )
				{
				mode = CHASE_MODE_USE_PATH;		
				return true;
				}
			nextwalktotime = level.time + newpathrate;
			}

		// Path is now invalid
		nextpathtime = 0;
		path = NULL;

		// Walk straight towards goal
		seek.SetTargetPosition( target );

		seek.SetPosition( self.origin );
		seek.SetDir( self.movedir );
		seek.SetMaxSpeed( self.movespeed );
		result = seek.Evaluate( self );

		steeringforce = seek.steeringforce;

		if ( !result )
			{
			return false;
			}
		}
	else if ( mode != CHASE_MODE_WANDER )
		{
		mode = CHASE_MODE_USE_PATH;

		// See if we need to find a new path
		if ( nextpathtime < level.time )
			{
			if ( nextwalktotime < level.time && self.CanWalkTo( target, target_entnum ) )
				{
				mode = CHASE_MODE_DIRECT;
				nextwalktotime = level.time + newpathrate;
				return true;
				}
			else
				{
				nextpathtime = level.time + newpathrate;

				path = follow.SetPath( self, self.origin, target );

				if ( !path )
					{
					Vector trace_end_pos;
					trace_t trace;
					PathNode *goal_node;
					qboolean found_node;
					Vector diff;
					float length;

					trace_end_pos = target - "0 0 1000";

					trace = G_Trace( target, vec_zero, vec_zero, trace_end_pos, NULL, MASK_SOLID, false, "Chase" );

					goal_node = self.NearestNodeInPVS( trace.endpos );

					found_node = false;

					if ( goal_node )
						{
						if ( use_nearest_node )
							found_node = true;
						else
							{
							diff = goal_node->origin - target;

							if ( diff.z < 50 && diff.z > -50 )
								{
								diff.z = 0;
								length = diff.length();

								if ( length < 100 )
									found_node = true;
								}
							}
						}

					if ( found_node )
						path = follow.SetPath( self, self.origin, goal_node->origin );

					if ( !path )
						{
						if ( allow_fail )
							{
							gi.DPrintf( "No path found for actor %d", self.entnum );

							if ( goalnode )
								gi.DPrintf( " , target node %s\n", goalnode->targetname.c_str() );
							else if ( goalent )
								gi.DPrintf( " , target ent %d\n", goalent->entnum );
							else
								gi.DPrintf( " , target pos (%f,%f,%f)\n", goal.x, goal.y, goal.z );

							return false;
							}
						else
							{
							PathNode *node;

							node = PathManager.NearestNode( self.origin, &self );

							if ( node && self.CanWalkTo( node->origin ) )
								{
								// Have a node nearby but can't get path to destination

								self.AddStateFlag( STATE_FLAG_NO_PATH );
								return false;
								}
							}
						}
					}
				}
			}

		if ( path )
			{
			follow.SetPosition( self.origin );
			follow.SetDir( self.movedir );
			follow.SetMaxSpeed( self.movespeed );

			if ( !follow.Evaluate( self ) )
				{
				nextpathtime = 0;
				if ( goalnode )
					{
					self.frame_delta = goalnode->origin - self.origin;
					return false;
					}
				}

         steeringforce = follow.steeringforce;
			}
		else
			{
			return false;
			}
		}

	// Try to avoid entites

	avoid.SetMaxSpeed( self.movespeed );
   avoid.SetPosition( self.origin );

	steering_angles = self.movedir.toAngles() + steeringforce;
	steering_angles.AngleVectors( &steering_dir );
	avoid.SetDir( steering_dir );

	if ( goalent )
		avoid.SetTargetEnt( goalent );

	avoid.Evaluate( self );

	if ( avoid.steeringforce != vec_zero )
		steeringforce += avoid.steeringforce;

	// Don't allow stuck to build up if still turning

	if ( steeringforce[YAW] < -self.turnspeed || steeringforce[YAW] > self.turnspeed )
		stuck = 0;

	// Actually turn the player

	self.Accelerate( steeringforce );

	return true;
	}

void Chase::End
	(
	Actor &self
	)

	{
	seek.End( self );
	follow.End( self );
	avoid.End( self );
	path = NULL;
	}

Vector Chase::ChooseRandomDirection
   (
   Actor &self
   )

   {
   Vector dir;
   Vector ang;
   Vector bestdir;
   float bestfraction;
   trace_t trace;
   trace_t groundtrace;
   int i;
   int j;
   int t;
   int u;
   Vector step;
   Vector start;
   Vector end;
   Vector groundend;

	step = Vector( 0, 0, STEPSIZE );
   start = self.origin + step;

   // quantize to nearest 45 degree
	//u = ( ( int )( ( self.angles.y + 22.5 ) / 45 ) ) * 45;
	u = self.angles.y;
   bestfraction = -1;
   //
   // in case we don't find anything!
   //
   bestdir = self.origin - ( Vector( self.orientation[ 0 ] ) * 100 );

   for( i = 0; i <= 180; i += 20 )
      {
      if ( rand() < 0.3 )
         {
         i += 20;
         }
      t = i;
      if ( rand() < 0.5 )
         {
         // sometimes we choose left first, other times right.
         t = -t;
         }
      for( j = -1; j < 2; j += 2 )
         {
         if ( ( j == 1 ) && ( i == 180 ) )
            {
            ang.y = self.angles.y + ( t * j );
            }
         else
            {
            ang.y = u + t * j;
            }

         ang.AngleVectors( &dir, NULL, NULL );

         end = self.origin + dir * 140 + step;
         trace = G_Trace( start, self.mins, self.maxs, end, &self,
            self.edict->clipmask, false, "Chase::ChooseRandomDirection 1" );
         if ( ( trace.fraction > bestfraction ) && ( !trace.startsolid ) && !( trace.allsolid ) )
            {
            if ( trace.endpos != avoidvec && trace.endpos != last_avoidvec )
               {
               // check if we're near the ground
               end = self.origin + dir * 32 + step;
               groundend = end;
               groundend.z -= STEPSIZE * 2;
               groundtrace = G_Trace( end, self.mins, self.maxs, groundend, &self,
                  self.edict->clipmask, false, "Chase::ChooseRandomDirection 2" );

					if ( groundtrace.fraction != 1 && self.feet_width )
						{
						Vector temp_mins;
						Vector temp_maxs;

						temp_mins[0] = -self.feet_width;
						temp_mins[1] = -self.feet_width;
						temp_mins[2] = self.mins[2];

						temp_maxs[0] = self.feet_width;
						temp_maxs[1] = self.feet_width;
						temp_maxs[2] = self.maxs[2];

						groundtrace = G_Trace( end, temp_mins, temp_maxs, groundend, &self, self.edict->clipmask, false, "Chase::ChooseRandomDirection 2.5" );
						}

               if ( groundtrace.fraction != 1 )
                  {
                  bestdir = trace.endpos;
                  bestfraction = trace.fraction;

						if ( bestfraction > .9 )
							return bestdir;
                  }
               }
            }

         if ( i == 0 )
            {
            break;
            }
         }
      }

   return bestdir;
   }

/****************************************************************************

  Jump Class Definition

****************************************************************************/

CLASS_DECLARATION( Steering, Jump, NULL )
	{
		{ NULL, NULL }
	};

Jump::Jump()
	{
	endtime = 0;
	speed = 200;
   state = 0;
	}

void Jump::SetGoal
	(
	const char *node_name
	)
	{
	PathNode *movegoal;

  	movegoal = AI_FindNode( node_name );

   if ( movegoal )
      goal = movegoal->origin;
	}

void Jump::SetEntity
	(
	Entity *entity_to_jump_to
	)
	{
	if ( entity_to_jump_to )
		goal = entity_to_jump_to->origin;
	}

void Jump::SetSpeed
	(
	float jump_speed
	)
	{
   speed	= jump_speed;
	}

void Jump::Begin
	(
	Actor &self
	)

	{
   float traveltime;

	self.SetAnim( "jump", EV_Anim_Done );

   traveltime = self.JumpTo( goal, speed );
	endtime = traveltime + level.time;

   self.last_jump_time = endtime;

   state = 0;
	}

qboolean	Jump::Evaluate
	(
	Actor &self
	)

	{
	animdone = self.GetActorFlag( ACTOR_FLAG_ANIM_DONE );
	self.SetActorFlag( ACTOR_FLAG_ANIM_DONE, false );

   switch( state )
      {
      case 0:
         state = 1;
         // this is here so that we at least hit this function at least once
         // this gaves the character the chance to leave the ground, nulling out
         // self.groundentity
         break;
		case 1:
			if ( animdone && self.HasAnim( "fall" ) )
            {
            animdone = false;
         	self.SetAnim( "fall", EV_Anim_Done );
            state = 2;
            }
			if ( self.groundentity )
				state = 2;
			break;
      case 2:
         //
         // wait for the character to hit the ground
         //
	      if ( self.groundentity )
            {
            state = 3;
            //
            // if we have an anim, we go to state 3
            //
            if ( self.HasAnim( "land" ) )
               {
               animdone = false;
         		self.SetAnim( "land", EV_Anim_Done );
               state = 4;
               }
            else
               {
               return false;
               }
            }
         break;
      case 3:
         //
         // we are on the ground and waiting to timeout
         //
	      if ( level.time > endtime )
	         return false;
         break;
      case 4:
         //
         // we are on the ground and waiting for our landing animation to finish
         //
         if ( animdone )
            {
            return false;
            }
         break;
      }

	return true;
	}

void Jump::End
	(
	Actor &self
	)

	{
	self.SetAnim( "idle" );
	}