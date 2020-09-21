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
// header file for saving out tan files
//

#ifndef __TIKIDATA_H__
#define __TIKIDATA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "cmdlib.h"
#include "mathlib.h"
#include "qfiles.h"
#include "models.h"

#define MAX_SURFACE_TRIS	(SHADER_MAX_INDEXES / 3)
#define MAX_SURFACE_VERTS	SHADER_MAX_VERTEXES

typedef struct {
	vec3_t		xyz;
	vec3_t		normal;
	vec3_t		color;
	float		   st[2];
	int			index;
} baseVertex_t;

typedef struct 
   {
	int			index;
   } triVertex_t;
	
typedef struct {
	triVertex_t	v[3];
} baseTriangle_t;

//================================================================

typedef struct
{
	tikiSurface_t	header;
	md3Shader_t		shaders[TIKI_MAX_SHADERS];
	// all verts (xyz_normal)
	float	*verts[TIKI_MAX_FRAMES];

	baseTriangle_t	baseTriangles[TIKI_MAX_TRIANGLES];

	// the triangles will be sorted so that they form long generalized tristrips
	int				orderedTriangles[TIKI_MAX_TRIANGLES][3];
	int				lodTriangles[TIKI_MAX_TRIANGLES][3];
	baseVertex_t	baseVertexes[TIKI_MAX_VERTS];
   int            collapseMap[TIKI_MAX_VERTS];
   int            permutationMap[TIKI_MAX_VERTS];

} md3SurfaceData_t;

typedef struct
{
	int			   skinwidth, skinheight;
	
	md3SurfaceData_t surfData[TIKI_MAX_SURFACES*2];

	tikiTag_t	   tags[TIKI_MAX_TAGS];
	tikiTagData_t	tagdata[TIKI_MAX_TAGS][TIKI_MAX_FRAMES];
	tikiFrame_t	   frames[TIKI_MAX_FRAMES];
   vec3_t         origins[TIKI_MAX_FRAMES];

	tikiHeader_t	model;
	float		      scale_up;			// set by $scale
	vec3_t		   adjust;				// set by $origin
	vec3_t		   aseAdjust;
	int			   fixedwidth, fixedheight;	// set by $skinsize

	int			   maxSurfaceTris;

	int			   lowerSkipFrameStart, lowerSkipFrameEnd;
	int			   maxUpperFrames;
	int			   maxHeadFrames;
	int			   currentLod;
	float		      lodBias;
   int            minLod;

	int			   type;		
   float          framerate;

   char           originname[ 128 ];
   char           **ignorelist;
   int            numignore;

} q3data;

#ifdef __cplusplus
   }
#endif

#endif
