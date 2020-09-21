//-----------------------------------------------------------------------------
//
//  $Logfile:: /FAKK2/code/game/actor.cpp                        $
// $Revision:: 3                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 2/22/99 5:50p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /FAKK2/code/game/actor.cpp                             $
//
// DESCRIPTION:
//

#include <assert.h>
#include "cmdlib.h"
#include "mathlib.h"
#include "qfiles.h"
#include "models.h"
#include "vector.h"
#include "list.h"
#include "progmesh.h"
#include "tikidata.h"
#include "calclod.h"

void CalculateLOD
   (
   md3SurfaceData_t *surf
   )

   {
	int	i;
   List<Vector> verts;
   List<tridata> tris;
   List<int> permutation;
   List<int> collapse_map;
   int minresolution;

   // clear out collapse map
   memset( surf->collapseMap, 0, sizeof( surf->collapseMap ) );

   // convert vertices
	for( i = 0; i < surf->header.numVerts;i++ )
      {
		float *vp = surf->baseVertexes[ i ].xyz;
		verts.Add( Vector( vp[0],vp[1],vp[2] ) );
	   }

   // convert triangles
	for( i = 0; i < surf->header.numTriangles; i++ )
      {
		tridata td;

		td.v[ 0 ] = surf->baseTriangles[ i ].v[ 0 ].index;
      td.v[ 1 ] = surf->baseTriangles[ i ].v[ 1 ].index;
      td.v[ 2 ] = surf->baseTriangles[ i ].v[ 2 ].index;
		tris.Add( td );
	   }

   ProgressiveMesh( verts, tris, collapse_map, permutation, &minresolution );

	// rearrange the vertex list 
	assert( permutation.num == verts.num );

   for( i = 0; i < verts.num; i++ )
      {
      surf->permutationMap[ i ] = permutation[ i ];
      surf->collapseMap[ i ] = collapse_map[ i ];
      }

   surf->header.minLod = minresolution;
   }
