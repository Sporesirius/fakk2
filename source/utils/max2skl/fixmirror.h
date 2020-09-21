//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2skl/fixmirror.h                          $
// $Revision:: 1                                                              $
//     $Date:: 4/25/00 11:30a                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2skl/fixmirror.h                               $
// 
// 1     4/25/00 11:30a Jimdose
// 
// 2     4/17/00 2:55p Jimdose
// created file
// 
// DESCRIPTION:
// 

#ifndef __FIXMIRROR_H__
#define __FIXMIRROR_H__

#include "vector.h"
#include "list.h"

class Tri;
class Vert;

class Tri
   {
   public:
	   Vert              *vertex[ 3 ];  // the 3 points that make this tri
	   Vector            normal;        // unit vector othogonal to this face
      bool              modified;

	                     Tri( Vert *v0, Vert *v1, Vert *v2 );
	                     ~Tri();
	   void              ComputeNormal( void );
      void              InvertFace( void );
      int               CheckFlip( void );
	   int               HasVertex( Vert *v );
      Tri               *GetAdjacentTriangle( int edge );
   };

class Vert
   {
   public:
	   Vector            position;    // location of point in euclidean space
	   bool              modified;    // whether this vertex has been modified by inverted bones
	   List<Vert *>      neighbor;    // adjacent vertices
	   List<Tri *>       face;        // adjacent triangles

	                     Vert( Vector v, bool mod );
	                     ~Vert();
	   void              RemoveIfNonNeighbor( Vert *n );
   };

#endif
