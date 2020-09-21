//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/qcommon/cm_public.h                      $
// $Revision:: 8                                                              $
//     $Date:: 7/09/00 5:42p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/qcommon/cm_public.h                           $
// 
// 8     7/09/00 5:42p Markd
// added routines to save and restore the areaportal state
// 
// 7     6/15/00 8:03p Markd
// Added ResetAreaPortals
// 
// 6     5/11/00 11:09a Steven
// Added PointBrushNum a proc that tells you what brush number a point is in.
// 
// 5     3/31/00 11:51a Markd
// changed temp bboxes to support contents type
// 
// 4     1/18/00 5:58p Markd
// fixed massive lighting bug and fixed issue where vis info was not being
// shared between renderer and client
// 
// 3     12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 2     9/10/99 12:28p Jimdose
//
// DESCRIPTION:
// 

#ifndef __CM_PUBLIC_H__
#define __CM_PUBLIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "qfiles.h"


void		CM_LoadMap( const char *name, qboolean clientload, int *checksum);
clipHandle_t CM_InlineModel( int index );		// 0 = world, 1 + are bmodels
clipHandle_t CM_TempBoxModel( const vec3_t mins, const vec3_t maxs, int contents );

void		CM_ModelBounds( clipHandle_t model, vec3_t mins, vec3_t maxs );

int			CM_NumClusters (void);
int			CM_NumInlineModels( void );
char		*CM_EntityString (void);

// returns an ORed contents mask
int			CM_PointContents( const vec3_t p, clipHandle_t model );
int			CM_PointBrushNum( const vec3_t p, clipHandle_t model );
int			CM_TransformedPointContents( const vec3_t p, clipHandle_t model, const vec3_t origin, const vec3_t angles );

void		CM_BoxTrace ( trace_t *results, const vec3_t start, const vec3_t end,
						  const vec3_t mins, const vec3_t maxs,
						  clipHandle_t model, int brushmask, qboolean cylinder);
void		CM_TransformedBoxTrace( trace_t *results, const vec3_t start, const vec3_t end,
						  const vec3_t mins, const vec3_t maxs,
						  clipHandle_t model, int brushmask,
						  const vec3_t origin, const vec3_t angles, qboolean cylinder);

byte		*CM_ClusterPVS (int cluster);

int			CM_PointLeafnum( const vec3_t p );

// only returns non-solid leafs
// overflow if return listsize and if *lastLeaf != list[listsize-1]
int			CM_BoxLeafnums( const vec3_t mins, const vec3_t maxs, int *list,
		 					int listsize, int *lastLeaf );

int			CM_LeafCluster (int leafnum);
int			CM_LeafArea (int leafnum);

void		CM_AdjustAreaPortalState( int area1, int area2, qboolean open );
qboolean	CM_AreasConnected( int area1, int area2 );
void     CM_ResetAreaPortals( void );
void     CM_WritePortalState( fileHandle_t );
void	   CM_ReadPortalState( fileHandle_t );

int			CM_WriteAreaBits( byte *buffer, int area );
byte        *CM_VisibilityPointer( void );

// cm_tag.c
void		CM_LerpTag( orientation_t *tag,  clipHandle_t model, int startFrame, int endFrame, 
					 float frac, const char *tagName );


// cm_marks.c
int	CM_MarkFragments( int numPoints, const vec3_t *points, const vec3_t projection,
				   int maxPoints, vec3_t pointBuffer, int maxFragments, markFragment_t *fragmentBuffer );

// cm_patch.c
void CM_DrawDebugSurface( void (*drawPoly)(int color, int numPoints, float *points) );

#ifdef __cplusplus
	}
#endif

#endif
