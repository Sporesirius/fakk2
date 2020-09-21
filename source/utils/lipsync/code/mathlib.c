//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/lipsync/code/mathlib.c                       $
// $Revision:: 1                                                              $
//   $Author:: Steven                                                         $
//     $Date:: 2/15/00 12:14p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/lipsync/code/mathlib.c                            $
// 
// 1     2/15/00 12:14p Steven
// 
// 6     9/23/98 6:41p Markd
// Put in angles from vector functionality into camera
// 
// 5     4/06/98 6:20p Markd
// Added AngleVectors
// 
// 4     3/09/98 5:12p Markd
// 
// 3     12/30/97 6:30p Jimdose
// Added header text
//
// DESCRIPTION:
// math primitives
//

#include "cmdlib.h"
#include "mathlib.h"

vec3_t vec3_origin = {0,0,0};


double VectorLength(vec3_t v)
{
	int		i;
	double	length;
	
	length = 0;
	for (i=0 ; i< 3 ; i++)
		length += v[i]*v[i];
	length = sqrt (length);		// FIXME

	return length;
}

qboolean VectorCompare (vec3_t v1, vec3_t v2)
{
	int		i;
	
	for (i=0 ; i<3 ; i++)
		if (fabs(v1[i]-v2[i]) > EQUAL_EPSILON)
			return false;
			
	return true;
}

vec_t Q_rint (vec_t in)
{
	return floor (in + 0.5);
}

void VectorMA (vec3_t va, double scale, vec3_t vb, vec3_t vc)
{
	vc[0] = va[0] + scale*vb[0];
	vc[1] = va[1] + scale*vb[1];
	vc[2] = va[2] + scale*vb[2];
}

void CrossProduct (vec3_t v1, vec3_t v2, vec3_t cross)
{
	cross[0] = v1[1]*v2[2] - v1[2]*v2[1];
	cross[1] = v1[2]*v2[0] - v1[0]*v2[2];
	cross[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

vec_t _DotProduct (vec3_t v1, vec3_t v2)
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void _VectorSubtract (vec3_t va, vec3_t vb, vec3_t out)
{
	out[0] = va[0]-vb[0];
	out[1] = va[1]-vb[1];
	out[2] = va[2]-vb[2];
}

void _VectorAdd (vec3_t va, vec3_t vb, vec3_t out)
{
	out[0] = va[0]+vb[0];
	out[1] = va[1]+vb[1];
	out[2] = va[2]+vb[2];
}

void _VectorCopy (vec3_t in, vec3_t out)
{
	out[0] = in[0];
	out[1] = in[1];
	out[2] = in[2];
}

void _VectorScale (vec3_t v, vec_t scale, vec3_t out)
{
	out[0] = v[0] * scale;
	out[1] = v[1] * scale;
	out[2] = v[2] * scale;
}

vec_t VectorNormalize (vec3_t in, vec3_t out)
{
	vec_t	length, ilength;

	length = sqrt (in[0]*in[0] + in[1]*in[1] + in[2]*in[2]);
	if (length == 0)
	{
		VectorClear (out);
		return 0;
	}

	ilength = 1.0/length;
	out[0] = in[0]*ilength;
	out[1] = in[1]*ilength;
	out[2] = in[2]*ilength;

	return length;
}

vec_t ColorNormalize (vec3_t in, vec3_t out)
{
	float	max, scale;

	max = in[0];
	if (in[1] > max)
		max = in[1];
	if (in[2] > max)
		max = in[2];

	if (max == 0)
		return 0;

	scale = 1.0 / max;

	VectorScale (in, scale, out);

	return max;
}



void VectorInverse (vec3_t v)
{
	v[0] = -v[0];
	v[1] = -v[1];
	v[2] = -v[2];
}

void ClearBounds (vec3_t mins, vec3_t maxs)
{
	mins[0] = mins[1] = mins[2] = 99999;
	maxs[0] = maxs[1] = maxs[2] = -99999;
}

void AddPointToBounds (vec3_t v, vec3_t mins, vec3_t maxs)
{
	int		i;
	vec_t	val;

	for (i=0 ; i<3 ; i++)
	{
		val = v[i];
		if (val < mins[i])
			mins[i] = val;
		if (val > maxs[i])
			maxs[i] = val;
	}
}
#ifdef SIN
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over
#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

void AngleVectors (vec3_t angles, vec3_t forward, vec3_t right, vec3_t up)
{
	float		angle;
	static float		sr, sp, sy, cr, cp, cy;
	// static to help MS compiler fp bugs

	angle = angles[YAW] * (M_PI*2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[PITCH] * (M_PI*2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[ROLL] * (M_PI*2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = -sr*sp*cy+cr*sy;
		right[1] = -sr*sp*sy-cr*cy;
		right[2] = -sr*cp;
	}
	if (up)
	{
		up[0] = cr*sp*cy+sr*sy;
		up[1] = cr*sp*sy-sr*cy;
		up[2] = cr*cp;
	}
}

void VectorToAngles( vec3_t vec, vec3_t angles )
   {
   float forward;
   float yaw, pitch;
   
   if ( ( vec[ 0 ] == 0 ) && ( vec[ 1 ] == 0 ) )
      {
      yaw = 0;
      if ( vec[ 2 ] > 0 )
         {
         pitch = 90;
         }
      else
         {
         pitch = 270;
         }
      }
   else
      {
      yaw = atan2( vec[ 1 ], vec[ 0 ] ) * 180 / M_PI;
      if ( yaw < 0 )
         {
         yaw += 360;
         }

      forward = ( float )sqrt( vec[ 0 ] * vec[ 0 ] + vec[ 1 ] * vec[ 1 ] );
      pitch = atan2( vec[ 2 ], forward ) * 180 / M_PI;
      if ( pitch < 0 )
         {
         pitch += 360;
         }
      }

   angles[ 0 ] = pitch;
   angles[ 1 ] = yaw;
   angles[ 2 ] = 0;
   }

#endif