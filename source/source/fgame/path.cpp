//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/path.cpp                           $
// $Revision:: 2                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 3:50p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/path.cpp                                $
// 
// 2     6/14/00 3:50p Markd
// Cleaned up more Intel Compiler warnings
// 
// 1     9/10/99 10:54a Jimdose
// 
// 1     9/08/99 3:16p Aldie
//
// DESCRIPTION:
//

#include "g_local.h"
#include "entity.h"
#include "path.h"
#include "container.h"
#include "navigate.h"
#include "misc.h"

CLASS_DECLARATION( Class, Path, NULL )
	{
		{ NULL, NULL }
	};

Path::Path()
	{
	pathlength = 0;
	from = NULL;
	to = NULL;
	nextnode = 1;
	}

Path::Path
	(
	int numnodes
	)

	{
	pathlength = 0;
	from = NULL;
	to = NULL;
	nextnode = 1;
	pathlist.Resize( numnodes );
   dirToNextNode.Resize( numnodes );
   distanceToNextNode.Resize( numnodes );
	}

void Path::Clear
	(
	void
	)

	{
	nextnode = 1;
	pathlength = 0;
	from = NULL;
	to = NULL;
	pathlist.FreeObjectList();
   dirToNextNode.FreeObjectList();
   distanceToNextNode.FreeObjectList();
	}

void Path::Reset
	(
	void
	)

	{
	nextnode = 1;
	}

PathNode *Path::Start
	(
	void
	)

	{
	return from;
	}

PathNode *Path::End
	(
	void
	)

	{
	return to;
	}

void Path::AddNode
	(
	PathNode *node
	)

	{
   Vector dir;
   float len;
	int num;

	if ( !from )
		{
		from = node;
		}

	to = node;
	pathlist.AddObject( PathNodePtr( node ) );

   len = 0;
   distanceToNextNode.AddObject( len );
   dirToNextNode.AddObject( vec_zero );

	num = NumNodes();
	if ( num > 1 )
		{
      dir = node->origin - GetNode( num - 1 )->origin;
      len = dir.length();
      dir *= 1 / len;

      distanceToNextNode.SetObjectAt( num - 1, len );
      dirToNextNode.SetObjectAt( num - 1, dir );

		pathlength += len;
		}
	}

PathNode *Path::GetNode
	(
	int num
	)

	{
   PathNode *node;

   node = pathlist.ObjectAt( num );
   assert( node != NULL );
   if ( node == NULL )
      {
      error( "GetNode", "Null pointer in node list\n" );
      }

	return node;
	}

PathNode	*Path::NextNode
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

PathNode	*Path::NextNode
	(
	PathNode	*node
	)

	{
   int i;
   int num;
   PathNode *n;

   num = NumNodes();

   // NOTE: We specifically DON'T check the last object (hence the i < num instead
   // of the usual i <= num, so don't go doing something stupid like trying to fix
   // this without keeping this in mind!! :)
   for( i = 1; i < num; i++ )
      {
		n = pathlist.ObjectAt( i );
      if ( n == node )
         {
         // Since we only check up to num - 1, it's ok to do this.
         // We do this since the last node in the list has no next node (duh!).
         return pathlist.ObjectAt( i + 1 );
         }
		}

	return NULL;
	}

Vector Path::ClosestPointOnPath
	(
	Vector pos
	)

	{
	PathNode	*s;
	PathNode	*e;
	int		num;
	int		i;
	float		bestdist;
	Vector	bestpoint;
	float		dist;
	float		segmentlength;
	Vector	delta;
	Vector	p1;
	Vector	p2;
	Vector	p3;
	float		t;

	num = NumNodes();
	s = GetNode( 1 );

   bestpoint = s->origin;
	delta = bestpoint - pos;
	bestdist = delta * delta;

   for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

		// check if we're closest to the endpoint
      delta = e->origin - pos;
		dist = delta * delta;

		if ( dist < bestdist )
			{
			bestdist = dist;
         bestpoint = e->origin;
			}

		// check if we're closest to the segment
      segmentlength = distanceToNextNode.ObjectAt( i - 1 );
      p1 = dirToNextNode.ObjectAt( i - 1 );
      p2 = pos - s->origin;

		t = p1 * p2;
		if ( ( t > 0 ) && ( t < segmentlength ) )
			{
         p3 = ( p1 * t ) + s->origin;

			delta = p3 - pos;
			dist = delta * delta;
			if ( dist < bestdist )
				{
				bestdist = dist;
				bestpoint = p3;
				}
			}

		s = e;
		}

	return bestpoint;
	}

float Path::DistanceAlongPath
	(
	Vector pos
	)

	{
	PathNode	*s;
	PathNode	*e;
	int		num;
	int		i;
	float		bestdist;
	float		dist;
	float		segmentlength;
	Vector	delta;
	Vector	p1;
	Vector	p2;
	Vector	p3;
	float		t;
	float		pathdist;
	float		bestdistalongpath;

	pathdist = 0;

	num = NumNodes();
	s = GetNode( 1 );
   delta = s->origin - pos;
	bestdist = delta * delta;
	bestdistalongpath = 0;

	for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

		segmentlength = distanceToNextNode.ObjectAt( i - 1 );

      // check if we're closest to the endpoint
      delta = e->origin - pos;
		dist = delta * delta;

		if ( dist < bestdist )
			{
			bestdist = dist;
			bestdistalongpath = pathdist + segmentlength;
			}

		// check if we're closest to the segment
      p1 = dirToNextNode.ObjectAt( i - 1 );
      p2 = pos - s->origin;

		t = p1 * p2;
		if ( ( t > 0 ) && ( t < segmentlength ) )
			{
         p3 = ( p1 * t ) + s->origin;

			delta = p3 - pos;
			dist = delta * delta;
			if ( dist < bestdist )
				{
				bestdist = dist;
				bestdistalongpath = pathdist + t;
				}
			}

		s = e;

		pathdist += segmentlength;
		}

	return bestdistalongpath;
	}

Vector Path::PointAtDistance
	(
	float dist
	)

	{
	PathNode	*s;
	PathNode	*e;
	int		num;
	int		i;
	float		t;
	float		pathdist;
	float		segmentlength;

	num = NumNodes();
	s = GetNode( 1 );
	pathdist = 0;

	for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

      segmentlength = distanceToNextNode.ObjectAt( i - 1 );
		if ( ( pathdist + segmentlength ) > dist )
			{
			t = dist - pathdist;
         return s->origin + dirToNextNode.ObjectAt( i - 1 ) * t;
			}

		s = e;
		pathdist += segmentlength;
		}

	// cap it off at start or end of path
   return s->origin;
	}

PathNode *Path::NextNode
	(
	float dist
	)

	{
	PathNode	*s;
	PathNode	*e;
	int		num;
	int		i;
	float		pathdist;
	float		segmentlength;

	num = NumNodes();
	s = GetNode( 1 );
	pathdist = 0;

	for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

      segmentlength = distanceToNextNode.ObjectAt( i - 1 );
		if ( ( pathdist + segmentlength ) > dist )
			{
			return e;
			}

		s = e;
		pathdist += segmentlength;
		}

	// cap it off at start or end of path
	return s;
	}

void Path::DrawPath
	(
	float r,
	float g,
	float b,
	float time
	)

	{
	Vector	s;
	Vector	e;
	Vector	offset;
	PathNode	*node;
	int		num;
	int		i;

	num = NumNodes();

   if ( ai_debugpath->integer )
		{
      gi.DPrintf( "numnodes %d, len %d, nodes %d :", PathManager.NumNodes(), ( int )Length(), num );
		for( i = 1; i <= num; i++ )
			{
			node = GetNode( i );
         gi.DPrintf( " %d", node->nodenum );
			}

      gi.DPrintf( "\n" );
		}

	node = GetNode( 1 );
   s = node->origin;

	offset = Vector( r, g, b ) * 4 + Vector( 0, 0, 20 );
	for( i = 2; i <= num; i++ )
		{
		node = GetNode( i );
      e = node->origin;

		G_DebugLine( s + offset, e + offset, r, g, b, 1 );
		s = e;
		}
	}

int Path::NumNodes
	(
	void
	)

	{
	return pathlist.NumObjects();
	}

float Path::Length
	(
	void
	)

	{
	return pathlength;
	}

