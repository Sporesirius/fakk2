//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2skl/max2skl.h                            $
// $Revision:: 14                                                             $
//     $Date:: 4/25/00 12:15p                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2skl/max2skl.h                                 $
// 
// 14    4/25/00 12:15p Jimdose
// merged changes
// 
// 3     4/17/00 2:55p Jimdose
// added ConvertToQuake3Worldspace
// added FixMirroredBones
// 
// 13    3/16/00 6:10p Jimdose
// added MAX_LOADBLENDBONES for when the model starts with more than
// MAX_BLENDBONES per vertex
// 
// 12    1/19/00 5:18p Jimdose
// added AddBone
// 
// 11    10/20/99 2:50p Jimdose
// added CopyBones
// 
// 10    10/14/99 6:37p Jimdose
// added SaveMD4
// 
// 9     10/12/99 3:35p Markd
// fixed max2skl for the new qfiles.h
// 
// 8     10/11/99 5:49p Jimdose
// added ScaleModel, ReverseAnimation, ReduceBonesPerVertex, and
// RemoveUnusedBones
// 
// 7     10/08/99 7:19p Jimdose
// got tags and deltas working
// 
// 6     10/06/99 12:46p Jimdose
// added ComputeVertexNormals
// 
// 5     10/04/99 7:05p Jimdose
// moved lod to surfaces
// added radius to frames
// 
// 4     9/27/99 5:01p Jimdose
// fixed some errors in saving animations
// 
// 3     9/27/99 12:35p Jimdose
// changed TIKI_ANIM_IDENT to TIKI_SKEL_ANIM_IDENT
// 
// 2     9/24/99 4:39p Jimdose
// first working version
//
// DESCRIPTION:
// 

#ifndef __MAX2SKL_H__
#define __MAX2SKL_H__

#include "cmdlib.h"
#include "script.h"
#include "mathlib.h"
#include "qfiles.h"
#include "str.h"
#include "container.h"
#include "uvector3.h"
#include "umatrix.h"

#define UV_FILE_VERSION       2

#define MAX_BONES             256
#define MAX_BLENDBONES        8
#define MAX_LOADBLENDBONES    16

#define MAX_SURFACE_TRIS	   (SHADER_MAX_INDEXES / 3)
#define MAX_SURFACE_VERTS	   SHADER_MAX_VERTEXES

#define UNUSED_BONE           -1

// output file version number
#define SKL_VERSION           1

typedef struct
   {
   float                offset[ 3 ];
   float                matrix[ 3 ][ 3 ];
   } loadbone_t;

typedef struct          
   {
   int                  bone;
	float	               offset[ 3 ];
   float                weight;
   } blendvert_t;

typedef struct
   {
   int                  numbones;
   blendvert_t          blend[ MAX_LOADBLENDBONES ];
   float                normal[ 3 ];

   int                  index;
	vec2_t		         texCoords;
   } loadvertx_t;

typedef struct
   {
   int                  vertindex;
	vec2_t		         texCoords;
   } loadfacevertx_t;

typedef struct
   {
   int                  id;
   loadfacevertx_t      verts[ 3 ];
   } loadtriangle_t;

typedef struct
   {
   loadbone_t           *bones;
   vec3_t		         bounds[ 2 ];
	float		            radius;				// dist from localOrigin to corner
   vec3_t               delta;
   vec3_t               origin;
   } loadframe_t;

typedef struct
   {
   int                  id;
   char                 name[ MAX_QPATH ];
   int                  numtris;
   int                  numverts;
   int                  minLod;
   int                  collapseMap[ TIKI_MAX_VERTS ];
   int                  tris[ TIKI_MAX_TRIANGLES ][ 3 ];
   loadvertx_t          verts[ TIKI_MAX_VERTS ];
   } surface_t;

typedef struct
   {
   char                 name[ MAX_QPATH ];

   float                framerate;
   int                  numverts;
   int                  numfaces;
   int                  numbones;
   int                  numframes;
   int                  numsurfaces;
   vec3_t               totaldelta;

   loadvertx_t          *verts;
   loadtriangle_t       *faces;
   loadframe_t          *anim;
   skelBoneName_t       *bones;
   surface_t            *surfaces;
   } loadmodel_t;

class SkelModel
   {
   private :
      void              LoadSurfaces( Script &script );
      void              LoadBones( Script &script );
      void              LoadVerts( Script &script );
      void              LoadFaces( Script &script );
      void              LoadFrames( Script &script );

      Container<str>    ignorelist;
      loadmodel_t       model;

   public :
                        SkelModel();
                        ~SkelModel();

      void              FreeModel( void );
      void              SaveBaseFrame( const char *name );
      void              SaveAnimation( const char *name );
      void              SaveMD4( const char *name );

      void              LoadIgnoreFile( const char *filename );
      bool              IgnoreSurface( const char *name );

      void              LoadSKL( const char *filename );
      void              LoadUVFile( const char *filename );
      void              CopyBaseModel( SkelModel &base );
      void              CopyBones( SkelModel &base );

      void              CreateSurfaces( void );
      void              ComputeVertexNormals( void );
      void              CalculateLOD( void );
      void              CalcFrameBones( int framenum, UMat3 bones[ MAX_BONES ], UVector3 offsets[ MAX_BONES ] );
      void              CalcVerts( vec3_t *outverts, UMat3 bones[ MAX_BONES ], UVector3 offsets[ MAX_BONES ] );
      void              CalcFrame( int framenum, vec3_t *outverts );
      void              CalcStaticFrame( vec3_t *outverts );
      void              CalculateTriStrips( void );
      void              CalculateBounds( void );
      void              ComputeTagFromTri( loadbone_t *bone, const float pTri[ 3 ][ 3 ] );
      void              CalculateTags( void );
      void              ScaleModel( float scale );
      void              ConvertToQuake3Worldspace( void );
      void              ReverseAnimation( void );
      void              ReduceBonesPerVertex( int maxbones, float minweight );
      int               AddBone( int parent, const char *name );
      void              RemoveUnusedBones( void );
      void              FixMirroredBones( void );
   };

#endif /* !__MAX2SKL_H__ */
