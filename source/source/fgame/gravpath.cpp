//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/gravpath.cpp                       $
// $Revision:: 14                                                             $
//   $Author:: Steven                                                         $
//     $Date:: 7/21/00 8:36p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/gravpath.cpp                            $
// 
// 14    7/21/00 8:36p Steven
// Got gravpaths working fairly well.
// 
// 13    7/08/00 6:07p Steven
// Added a PULL_UPWARDS spawn flag to gravpaths.
// 
// 12    7/06/00 12:58p Steven
// Changed gravpaths to pull you parallel to the path not towards it.
// 
// 11    6/23/00 8:41p Markd
// made a lot of changes to different constructors for saved game support
// 
// 10    6/14/00 2:17p Markd
// fixed compiler warnings for Intel Compiler
// 
// 9     1/22/00 12:42p Jimdose
// got rid of calls to vec3()
// 
// 8     1/06/00 11:08p Jimdose
// cleaning up unused code
// 
// 7     12/07/99 10:33a Jimdose
// made CalculateGravityPull early exit when there are no gravpaths
// 
// 6     10/26/99 5:27p Aldie
// Fix for gravpaths
// 
// 5     10/04/99 10:53a Aldie
// fix warning
// 
// 4     9/29/99 5:18p Steven
// Event formatting.
// 
// 3     9/22/99 4:47p Markd
// fixed more G_GetEntity, G_FindClass and G_GetNextEntity bugs
// 
// 2     9/21/99 7:51p Markd
// Fixed a lot of entitynum_none issues
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 10    8/18/99 3:28p Jimdose
// added cylindrical collision detection
// 
// 9     6/11/99 1:23p Phook
// 
// 8     6/11/99 12:58p Phook
// Changed from SINED comments to QUAKED
//
// DESCRIPTION:
// Gravity path - Used for underwater currents and wells.

#include "g_local.h"
#include "entity.h"
#include "gravpath.h"
#include "container.h"
#include "navigate.h"
#include "misc.h"
#include "player.h"

GravPathManager gravPathManager;

CLASS_DECLARATION( Class, GravPathManager, NULL )
   {
      { NULL,NULL }
   };

GravPathManager::~GravPathManager()
   {
   Reset();
   }

void GravPathManager::Reset( void )
   {
   while( pathList.NumObjects() > 0 )
		{
		delete ( GravPath * )pathList.ObjectAt( 1 );
      }

   pathList.FreeObjectList();
   }

void GravPathManager::AddPath(GravPath *p)
	{
	pathList.AddObject( p );
	}

void GravPathManager::RemovePath(GravPath *p)
	{
	pathList.RemoveObject( p );
	}

void GravPathManager::DrawGravPaths
   (
   void
   )

   {
   int i;
 	int num = pathList.NumObjects();

   for( i = 1; i <= num; i++ )
		{
		GravPath *p = ( GravPath * )pathList.ObjectAt( i );
      
      p->DrawPath( 1,0,0 );
      }
   }

Vector GravPathManager::CalculateGravityPull(Entity &ent, Vector pos, qboolean *force, float *max_speed)
   {
   int            i,num;
   GravPath       *p;
   GravPathNode   *node;
   Vector         point;
   Vector         newpoint;
   Vector         dir;
   float          bestdist = 99999;
   float          dist;
   float          speed;
   float          radius;
   Vector         velocity;
   int            bestpath = 0;
   int            entity_contents, grav_contents;

 	num = pathList.NumObjects();
   if ( !num )
      {
      return vec_zero;
      }

   entity_contents = gi.pointcontents( ent.origin, 0 );

   for( i = 1; i <= num; i++ )
		{
		p = ( GravPath * )pathList.ObjectAt( i );

      if ( !p )
         continue;

      // Check to see if path is active
      node = p->GetNode( 1 );
      if ( !node || !node->active )
         continue;

      // Check to see if the contents are the same
      grav_contents = gi.pointcontents( node->origin, 0 );

      // If grav node is in water, make sure ent is too.
      if ( ( grav_contents & CONTENTS_WATER ) && !( entity_contents & CONTENTS_WATER ) )
         continue;

      // Test to see if we are in this path's bounding box
      if ( (pos.x < p->maxs.x) && (pos.y < p->maxs.y) && (pos.z < p->maxs.z) &&
           (pos.x > p->mins.x) && (pos.y > p->mins.y) && (pos.z > p->mins.z) )
         {
         point = p->ClosestPointOnPath(pos, ent, &dist, &speed, &radius);

         // If the closest distance on the path is greater than the radius, then
         // do not consider this path.

         if (dist > radius)
            {
            continue;
            }
         else if (dist < bestdist)
            {
            bestpath = i;
            bestdist  = dist;
            }
         }
      }

   if (!bestpath)
      {
      return vec_zero;
      }

   p = ( GravPath * )pathList.ObjectAt( bestpath );
   if ( !p )
      return velocity;
   *force    = p->force;
   dist     = p->DistanceAlongPath(pos, &speed);
   newpoint = p->PointAtDistance( pos, dist + speed, ent.isSubclassOf( Player ), max_speed );
   dir      = newpoint-pos;
   dir.normalize();
   velocity = dir * speed;

	//velocity *= .75;
   return velocity;
   }

/*****************************************************************************/
/*QUAKED info_grav_pathnode (0 0 .5) (-16 -16 0) (16 16 32) HEADNODE FORCE PULL_UPWARDS
 "radius" Radius of the effect of the pull (Default is 256)
 "speed"  Speed of the pull (Use negative for a repulsion) (Default is 100)

  Set HEADNODE to signify the head of the path.
  Set FORCE if you want un-fightable gravity ( i.e. can't go backwards )
  Set PULL_UPWARDS if you want the gravnodes to pull you upwards also
******************************************************************************/

#define PULL_UPWARDS ( 1 << 2 )

Event EV_GravPath_Create
	( 
	"gravpath_create",
	EV_DEFAULT,
   NULL,
   NULL,
   "Create the grav path."
	);
Event EV_GravPath_Activate
	( 
	"activate",
	EV_DEFAULT,
   NULL,
   NULL,
   "Activate the grav path."
	);
Event EV_GravPath_Deactivate
	( 
	"deactivate",
	EV_DEFAULT,
   NULL,
   NULL,
   "Deactivate the grav path."
	);
Event EV_GravPath_SetSpeed
	( 
	"speed",
	EV_DEFAULT,
   "f",
   "speed",
   "Set the speed of the grav path."
	);
Event EV_GravPath_SetMaxSpeed
	( 
	"maxspeed",
	EV_DEFAULT,
   "f",
   "maxspeed",
   "Set the max speed of the grav path."
	);
Event EV_GravPath_SetRadius
	( 
	"radius",
	EV_DEFAULT,
   "f",
   "radius",
   "Set the radius of the grav path."
	);

CLASS_DECLARATION( Entity, GravPathNode, "info_grav_pathnode" )
	{
      { &EV_GravPath_Create,           CreatePath },
      { &EV_GravPath_Activate,         Activate },
      { &EV_GravPath_Deactivate,       Deactivate },
      { &EV_GravPath_SetSpeed,         SetSpeed },
		{ &EV_GravPath_SetMaxSpeed,         SetMaxSpeed },
      { &EV_GravPath_SetRadius,        SetRadius },
      { NULL, NULL }
   };

GravPathNode::GravPathNode()
	{
   if ( LoadingSavegame )
      {
      // all data will be setup by the archive function
      return;
      }

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_NOT );
   hideModel();

   speed     = 100.0f;
	max_speed = 200.0f;
   radius    = 256.0f;
   headnode  = spawnflags & 1;
   active    = true;

   // This is the head of a new path, post an event to create the path
   if ( headnode )
      {
      PostEvent( EV_GravPath_Create, 0 );
      }
	}

void GravPathNode::SetSpeed
   (
   Event *ev
   )

   {
   speed = ev->GetFloat( 1 );
   }

void GravPathNode::SetMaxSpeed
   (
   Event *ev
   )

   {
   max_speed = ev->GetFloat( 1 );
   }

void GravPathNode::SetRadius
   (
   Event *ev
   )

   {
   radius = ev->GetFloat( 1 );
   }

float GravPathNode::Speed
   (
   void
   )

   {
   if ( active )
      return speed;
   else
      return 0;
   }

float GravPathNode::MaxSpeed
   (
   void
   )

   {
   return max_speed;
   }

void GravPathNode::Activate
   (
   Event *ev
   )

   {
   GravPathNode   *node;
   Entity         *ent;
   const char     *target;

   active = true;
   node = this;
   // Go through the entire path and activate it
   target = node->Target();
   while (target[0])
      {
      ent = G_FindTarget( NULL, target );
      if ( ent )
         {
         node = (GravPathNode *)ent;
         assert( node );
         node->active = true;
         }
      else
         {
         gi.Error( ERR_DROP, "GravPathNode::CreatePath: target %s not found\n",target);
         }
      target = node->Target();
      }
   }

void GravPathNode::Deactivate(Event *ev)
   {
   GravPathNode   *node;
   Entity         *ent;
   const char     *target;

   active = false;
   node = this;
   // Go through the entire path and activate it
   target = node->Target();
   while (target[0])
      {
      ent = G_FindTarget( NULL, target);
      if ( ent )
         {
         node = (GravPathNode *)ent;
         assert( node );
         node->active = false;
         }
      else
         {
         gi.Error( ERR_DROP, "GravPathNode::CreatePath: target %s not found\n",target);
         }
      target = node->Target();
      }
   }

void GravPathNode::CreatePath(Event *ev)
   {
   const char     *target;
   GravPath       *path = new GravPath;
   GravPathNode   *node;
   Entity         *ent;

   ClearBounds( path->mins, path->maxs );

   // This node is the head of a path, create a new path in the path manager.
   // and add it in, then add all of it's children in the path.
   node = this;
   path->AddNode(node);
   path->force = spawnflags & 2;

   // Make the path from the targetlist.
   target = node->Target();
   while (target[0])
      {
      ent = G_FindTarget( NULL, target );
      if ( ent ) 
         {
         node = (GravPathNode *)ent;
         assert( node );
         path->AddNode(node);
         }
      else
         {
         gi.Error( ERR_DROP, "GravPathNode::CreatePath: target %s not found\n",target);
         }
      target = node->Target();
      }

   // Set the origin.
   path->origin = path->mins + path->maxs;
   path->origin *= 0.5f;
   }

CLASS_DECLARATION( Listener, GravPath, NULL )
   {
		{ NULL, NULL }
	};

GravPath::GravPath()
	{
   pathlength  = 0;
	from        = NULL;
	to          = NULL;
	nextnode    = 1;

   if ( !LoadingSavegame )
      {
      gravPathManager.AddPath(this);
      }
	}

GravPath::~GravPath()
	{
	pathlength  = 0;
	from        = NULL;
	to          = NULL;
	nextnode    = 1;
   gravPathManager.RemovePath(this);
	}

void GravPath::Clear
	(
	void
	)

	{
	nextnode = 1;
	pathlength = 0;
	from = NULL;
	to = NULL;
	pathlist.FreeObjectList();
	}

void GravPath::Reset
	(
	void
	)

	{
	nextnode = 1;
	}

GravPathNode *GravPath::Start
	(
	void
	)

	{
	return from;
	}

GravPathNode *GravPath::End
	(
	void
	)

	{
	return to;
	}

void GravPath::AddNode
	(
	GravPathNode *node
	)

	{
	int num;
   Vector r,addp;

	if ( !from )
		{
		from = node;
		}

	to = node;
	pathlist.AddObject( GravPathNodePtr( node ) );

	num = NumNodes();
	if ( num > 1 )
		{
      pathlength += ( node->origin - GetNode( num )->origin ).length();
		}

   r.setXYZ(node->Radius(),node->Radius(),node->Radius());
   addp = node->origin + r;
   AddPointToBounds(addp,mins,maxs);
   addp = node->origin - r;
   AddPointToBounds(addp,mins,maxs);
	}

GravPathNode *GravPath::GetNode
	(
	int num
	)

	{
	return pathlist.ObjectAt( num );
	}

GravPathNode *GravPath::NextNode
	(
	void
	)

	{
	if ( nextnode <= NumNodes() )
		{
		return pathlist.ObjectAt( nextnode++ );
		}
	return NULL;
	}

Vector GravPath::ClosestPointOnPath
	(
	Vector pos,
	Entity &ent,
   float  *ret_dist,
   float  *speed,
   float  *radius
	)

	{
	GravPathNode	*s;
	GravPathNode	*e;
	int	      	num;
	int		      i;
	float		      bestdist;
	Vector	      bestpoint;
	float		      dist;
	float		      segmentlength;
	Vector	      delta;
	Vector	      p1;
	Vector      	p2;
	Vector	      p3;
	float		      t;
	trace_t	      trace;

	num = NumNodes();
	s = GetNode( 1 );
   trace = G_Trace( pos, ent.mins, ent.maxs, s->origin, &ent, MASK_PLAYERSOLID, false, "GravPath::ClosestPointOnPath 1" );
   bestpoint = s->origin;
	delta = bestpoint - pos;
	bestdist = delta.length();
   *speed = s->Speed();
   *radius = s->Radius();

	for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

		// check if we're closest to the endpoint
      delta = e->origin - pos;
		dist = delta.length();

		if ( dist < bestdist )
			{
         trace = G_Trace( pos, ent.mins, ent.maxs, e->origin, &ent, MASK_PLAYERSOLID, false, "GravPath::ClosestPointOnPath 2" );
			bestdist = dist;
         bestpoint = e->origin;
         *speed = e->Speed();
         *radius = e->Radius();
			}

		// check if we're closest to the segment
      p1 = e->origin - s->origin;
		segmentlength = p1.length();
		p1	 *= 1 / segmentlength;
      p2 = pos - s->origin;

		t = p1 * p2;
		if ( ( t > 0 ) && ( t < segmentlength ) )
			{
         p3 = ( p1 * t ) + s->origin;

			delta = p3 - pos;
			dist = delta.length();
			if ( dist < bestdist )
				{
				trace = G_Trace( pos, ent.mins, ent.maxs, p3, &ent, MASK_PLAYERSOLID, false, "GravPath::ClosestPointOnPath 3" );
				bestdist = dist;
				bestpoint = p3;
            *speed  = (e->Speed() * t) + (s->Speed() * (1.0f - t));
            *radius = (e->Radius() * t) + (s->Radius() * (1.0f - t));
				}
			}

		s = e;
		}
   *ret_dist = bestdist;
	return bestpoint;
	}

float GravPath::DistanceAlongPath
	(
	Vector pos,
   float *speed
	)

	{
	GravPathNode	*s;
	GravPathNode	*e;
	int	      	num;
	int		      i;
	float		      bestdist;
	float		      dist;
	float		      segmentlength;
	Vector	      delta;
	Vector	      segment;
	Vector      	p1;
	Vector	      p2;
	Vector	      p3;
	float		      t;
	float		      pathdist;
	float		      bestdistalongpath;
   float          oosl;
	pathdist = 0;

	num = NumNodes();
	s = GetNode( 1 );
   delta = s->origin - pos;
	bestdist = delta.length();
	bestdistalongpath = 0;
   *speed = s->Speed();

	for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

      segment = e->origin - s->origin;
		segmentlength = segment.length();

		// check if we're closest to the endpoint
      delta = e->origin - pos;
		dist = delta.length();

		if ( dist < bestdist )
			{
			bestdist = dist;
			bestdistalongpath = pathdist + segmentlength;
         *speed = e->Speed();
			}

		// check if we're closest to the segment
      oosl = ( 1 / segmentlength );
		p1 = segment * oosl;
		p1.normalize();
      p2 = pos - s->origin;

		t = p1 * p2;
		if ( ( t > 0 ) && ( t < segmentlength ) )
			{
         p3 = ( p1 * t ) + s->origin;

			delta = p3 - pos;
			dist = delta.length();
			if ( dist < bestdist )
				{
				bestdist = dist;
				bestdistalongpath = pathdist + t;

            t *= oosl;
            *speed = (e->Speed() * t) + (s->Speed() * (1.0f - t));
            }
			}

		s = e;
		pathdist += segmentlength;
		}

	return bestdistalongpath;
	}

Vector GravPath::PointAtDistance
	(
	Vector pos,
	float dist,
	qboolean is_player,
	float *max_speed
	)

	{
	GravPathNode	*s;
	GravPathNode	*e;
	int      		num;
	int		      i;
	Vector	      delta;
	Vector	      p1;
	float	      	t;
	float		      pathdist;
	float		      segmentlength;

	num = NumNodes();
	s = GetNode( 1 );
	pathdist = 0;

	for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

      delta = e->origin - s->origin;
		segmentlength = delta.length();

		if ( ( pathdist + segmentlength ) > dist )
			{
			t = dist - pathdist;

			p1 = delta * ( t / segmentlength );
//         return p1 + s->origin;

			if ( e->spawnflags & PULL_UPWARDS && is_player )
				p1.z = p1.length() / 2;

			*max_speed = e->MaxSpeed();

         return p1 + pos;
			}

		s = e;
		pathdist += segmentlength;
		}

	*max_speed = s->MaxSpeed();

	// cap it off at start or end of path
   return s->origin;
	}

void GravPath::DrawPath
	(
   float r,
   float g,
   float b
   )

	{
	Vector	      s;
	Vector	      e;
	Vector	      offset;
	GravPathNode	*node;
	int		      num;
	int		      i;

	num = NumNodes();
	node = GetNode( 1 );
   s = node->origin;
   G_DebugBBox( s, Vector(8,8,8), Vector(-8,-8,-8), 0,1,0,1 );
	offset = Vector( r, g, b ) * 4 + Vector( 0, 0, 0 );
   offset = Vector(0, 0, 0);

	for( i = 2; i <= num; i++ )
		{
		node = GetNode( i );
      e = node->origin;

		G_DebugLine( s + offset, e + offset, r, g, b, 1 );
      G_DebugBBox( e, Vector(8,8,8), Vector(-8,-8,-8), 0,1,0,1 );
		s = e;
		}

   G_DebugBBox(origin,mins-origin,maxs-origin,1,0,0,1);
	}

int GravPath::NumNodes
	(
	void
	)

	{
	return pathlist.NumObjects();
	}

float GravPath::Length
	(
	void
	)

	{
	return pathlength;
	}
