//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2tan/models.h                $
// $Revision:: 12                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 8/17/99 4:27p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2tan/models.h                     $
// 
// 12    8/17/99 4:27p Jimdose
// added clearxy
// 
// 11    8/11/99 7:19p Jimdose
// added -clearz
// 
// 10    7/08/99 7:38p Markd
// Added noorigin flag to max2tan
// 
// 9     6/29/99 2:26p Markd
// Added Z clamping and Z zeroing for models
//
// DESCRIPTION:
// Header file for saving out tan files.
//

#ifndef __MODELS_H__
#define __MODELS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "cmdlib.h"
#include "mathlib.h"

#define MAX_ANIM_FRAMES		512
#define MAX_ANIM_SURFACES	64
#define MAX_ANIM_VERTICES	2048

#define MODELS_MAXTRIANGLES	4096
#define MODELS_MAXSURFACES		64

typedef struct 
   {
	vec3_t	xyz;
   vec3_t   normal;
   } vertex_t;

typedef struct
   {
   vertex_t verts[ MAX_ANIM_VERTICES ];
   int      numverts;
   } animframe_t;

typedef float st_t[2];

typedef struct 
   {
   int      map;
   vertex_t xyz;
	st_t	   tex;
   } trivert_t;

typedef struct 
   {
   int      verts[3];
   } surftriangle_t;

typedef struct
   {
	char        name[100];
	char        materialname[100];
   trivert_t   triverts[ MAX_ANIM_VERTICES ];
	surftriangle_t triangles[ TIKI_MAX_TRIANGLES ];
	int         numtriangles;
   int         numvertices;
   } trisurf_t;

typedef struct
   {
   trisurf_t   surfaces[MODELS_MAXSURFACES];
	int         numSurfaces;
   } baseframe_t;

void ConvertAnim
   ( 
   const char *filename, 
   int numFrames, 
   float framerate, 
   qboolean optimize, 
   baseframe_t * base,
   animframe_t * anim,
   const char *originame,
   qboolean dolod,
   qboolean clampz,
   qboolean zeroz,
   qboolean clearzero,
   qboolean clearxy,
   qboolean noorigin,
   qboolean verbose
   );

#ifdef __cplusplus
   }
#endif

#endif