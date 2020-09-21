//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/lipsync/code/mathlib.h                       $
// $Revision:: 1                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 2/15/00 12:17p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/lipsync/code/mathlib.h                            $
// 
// 1     2/15/00 12:17p Steven
// 
// 6     9/23/98 6:41p Markd
// Put in angles from vector functionality into camera
// 
// 5     4/06/98 6:22p Markd
// Added AngleVectors
// 
// 4     2/22/98 3:42p Markd
// Added Cplusplus stuff
// 
// 3     12/30/97 6:30p Jimdose
// Added header text
//
// DESCRIPTION:
// 

#ifndef __MATHLIB__
#define __MATHLIB__

// mathlib.h

#include <math.h>

#ifdef DOUBLEVEC_T
typedef double vec_t;
#else
typedef float vec_t;
#endif
typedef vec_t vec3_t[3];

#define	SIDE_FRONT		0
#define	SIDE_ON			2
#define	SIDE_BACK		1
#define	SIDE_CROSS		-2

#define	Q_PI	3.14159265358979323846

extern vec3_t vec3_origin;

#define	EQUAL_EPSILON	0.001

#ifdef SIN
#ifdef __cplusplus
extern "C" {
#endif
#endif

qboolean VectorCompare (vec3_t v1, vec3_t v2);

#define DotProduct(x,y) (x[0]*y[0]+x[1]*y[1]+x[2]*y[2])
#define VectorSubtract(a,b,c) {c[0]=a[0]-b[0];c[1]=a[1]-b[1];c[2]=a[2]-b[2];}
#define VectorAdd(a,b,c) {c[0]=a[0]+b[0];c[1]=a[1]+b[1];c[2]=a[2]+b[2];}
#define VectorCopy(a,b) {b[0]=a[0];b[1]=a[1];b[2]=a[2];}
#define VectorScale(a,b,c) {c[0]=b*a[0];c[1]=b*a[1];c[2]=b*a[2];}
#define VectorClear(x) {x[0] = x[1] = x[2] = 0;}
#define	VectorNegate(x) {x[0]=-x[0];x[1]=-x[1];x[2]=-x[2];}

vec_t Q_rint (vec_t in);
vec_t _DotProduct (vec3_t v1, vec3_t v2);
void _VectorSubtract (vec3_t va, vec3_t vb, vec3_t out);
void _VectorAdd (vec3_t va, vec3_t vb, vec3_t out);
void _VectorCopy (vec3_t in, vec3_t out);
void _VectorScale (vec3_t v, vec_t scale, vec3_t out);

double VectorLength(vec3_t v);

void VectorMA (vec3_t va, double scale, vec3_t vb, vec3_t vc);

void CrossProduct (vec3_t v1, vec3_t v2, vec3_t cross);
vec_t VectorNormalize (vec3_t in, vec3_t out);
vec_t ColorNormalize (vec3_t in, vec3_t out);
void VectorInverse (vec3_t v);

void ClearBounds (vec3_t mins, vec3_t maxs);
void AddPointToBounds (vec3_t v, vec3_t mins, vec3_t maxs);

#ifdef SIN
void AngleVectors (vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
void VectorToAngles( vec3_t vec, vec3_t angles );
#endif

#ifdef SIN
#ifdef __cplusplus
   }
#endif
#endif

#endif
