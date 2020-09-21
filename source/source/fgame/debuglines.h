//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/debuglines.h                       $
// $Revision:: 4                                                              $
//     $Date:: 3/15/00 2:04p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/debuglines.h                            $
// 
// 4     3/15/00 2:04p Markd
// fixed up camera node system and added new debug oriented circle
// 
// 3     3/02/00 6:04p Markd
// Added Debug Arrow and DebugHighlightFacet
// 
// 2     1/06/00 11:08p Jimdose
// cleaning up unused code
//
// DESCRIPTION:
// 

#ifndef __DEBUGLINES_H__
#define __DEBUGLINES_H__

#include "g_local.h"

void G_InitDebugLines( void );
void G_DebugLine( Vector start, Vector end, float r, float g, float b, float alpha );
void G_LineStipple( int factor, unsigned short pattern );
void G_LineWidth( float width );
void G_Color3f( float r, float g, float b	);
void G_Color3v( Vector color );
void G_Color4f( float r, float g,	float b,	float alpha	);
void G_Color3vf( Vector color, float alpha );
void G_BeginLine( void );
void G_Vertex( Vector v );
void G_EndLine( void );
void G_DebugBBox( Vector org, Vector mins, Vector maxs, float r, float g, float b, float alpha );
void G_DrawDebugNumber( Vector org, float number, float scale, float r, float g, float b, int precision = 0 );
void G_DebugCircle( Vector org, float radius, float r, float g, float b, float alpha, qboolean horizontal = false );
void G_DebugOrientedCircle( Vector org, float radius, float r, float g, float b, float alpha, Vector angles );
void G_DebugPyramid( Vector org, float radius, float r, float g, float b, float alpha );
void G_DrawCoordSystem( Vector pos, Vector f, Vector r, Vector u, int len );
void G_DebugArrow( Vector org, Vector dir, float  length, float r, float g, float b, float alpha );
void G_DrawCSystem( void );

typedef enum
   {
   north,
   south,
   east,
   west,
   up,
   down
   } facet_t;

void G_DebugHighlightFacet( Vector org, Vector mins, Vector maxs, facet_t facet, float r, float g, float b, float alpha );

#endif /* !__DEBUGLINES_H__ */
