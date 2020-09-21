//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/q_math.c                           $
// $Revision:: 17                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/14/00 12:14p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/q_math.c                                $
// 
// 17    6/14/00 12:14p Markd
// more intel compiler bug fixes
// 
// 16    4/01/00 2:07p Markd
// replaced constant with #define
// 
// 15    4/01/00 2:02p Markd
// Added BoundsClear function
// 
// 14    1/05/00 7:25p Jimdose
// made angle functions all use the same coordinate system
// AngleVectors now returns left instead of right
// no longer need to invert pitch
// 
// 13    12/16/99 5:03p Aldie
// AnglesDelta utility fcn
// 
// 12    12/11/99 3:37p Markd
// q3a gold checkin, first time
// 
// 11    11/10/99 1:18p Markd
// Added LerpAngleFromCurrent function
// 
// 10    10/29/99 6:48p Jimdose
// added trivial case for no rotation in EulerToQuat
// 
// 9     10/22/99 3:24p Jimdose
// removed SetPlaneYaw
// 
// 8     10/05/99 6:01p Aldie
// Added headers
//
// DESCRIPTION:
// stateless support routines that are included in each code dll

#include "q_shared.h"
#include <math.h>
#include "float.h"


#define X 0
#define Y 1
#define Z 2
#define W 3
#define QUAT_EPSILON 0.00001

vec3_t	vec3_origin = {0,0,0};
vec3_t	axisDefault[3] = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };


vec4_t		colorBlack	= {0, 0, 0, 1};
vec4_t		colorRed	= {1, 0, 0, 1};
vec4_t		colorGreen	= {1, 1, 0, 1};
vec4_t		colorBlue	= {0, 0, 1, 1};
vec4_t		colorYellow	= {1, 1, 0, 1};
vec4_t		colorMagenta= {1, 0, 1, 1};
vec4_t		colorCyan	= {0, 1, 1, 1};
vec4_t		colorWhite	= {1, 1, 1, 1};
vec4_t		colorLtGrey	= {0.75, 0.75, 0.75, 1};
vec4_t		colorMdGrey	= {0.5, 0.5, 0.5, 1};
vec4_t		colorDkGrey	= {0.25, 0.25, 0.25, 1};

vec4_t	g_color_table[8] =
	{
	{0.0, 0.0, 0.0, 1.0},
	{1.0, 0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0, 1.0},
	{1.0, 1.0, 0.0, 1.0},
	{0.0, 0.0, 1.0, 1.0},
	{0.0, 1.0, 1.0, 1.0},
	{1.0, 0.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	};


vec3_t	bytedirs[NUMVERTEXNORMALS] =
{
{-0.525731, 0.000000, 0.850651}, {-0.442863, 0.238856, 0.864188}, 
{-0.295242, 0.000000, 0.955423}, {-0.309017, 0.500000, 0.809017}, 
{-0.162460, 0.262866, 0.951056}, {0.000000, 0.000000, 1.000000}, 
{0.000000, 0.850651, 0.525731}, {-0.147621, 0.716567, 0.681718}, 
{0.147621, 0.716567, 0.681718}, {0.000000, 0.525731, 0.850651}, 
{0.309017, 0.500000, 0.809017}, {0.525731, 0.000000, 0.850651}, 
{0.295242, 0.000000, 0.955423}, {0.442863, 0.238856, 0.864188}, 
{0.162460, 0.262866, 0.951056}, {-0.681718, 0.147621, 0.716567}, 
{-0.809017, 0.309017, 0.500000},{-0.587785, 0.425325, 0.688191}, 
{-0.850651, 0.525731, 0.000000},{-0.864188, 0.442863, 0.238856}, 
{-0.716567, 0.681718, 0.147621},{-0.688191, 0.587785, 0.425325}, 
{-0.500000, 0.809017, 0.309017}, {-0.238856, 0.864188, 0.442863}, 
{-0.425325, 0.688191, 0.587785}, {-0.716567, 0.681718, -0.147621}, 
{-0.500000, 0.809017, -0.309017}, {-0.525731, 0.850651, 0.000000}, 
{0.000000, 0.850651, -0.525731}, {-0.238856, 0.864188, -0.442863}, 
{0.000000, 0.955423, -0.295242}, {-0.262866, 0.951056, -0.162460}, 
{0.000000, 1.000000, 0.000000}, {0.000000, 0.955423, 0.295242}, 
{-0.262866, 0.951056, 0.162460}, {0.238856, 0.864188, 0.442863}, 
{0.262866, 0.951056, 0.162460}, {0.500000, 0.809017, 0.309017}, 
{0.238856, 0.864188, -0.442863},{0.262866, 0.951056, -0.162460}, 
{0.500000, 0.809017, -0.309017},{0.850651, 0.525731, 0.000000}, 
{0.716567, 0.681718, 0.147621}, {0.716567, 0.681718, -0.147621}, 
{0.525731, 0.850651, 0.000000}, {0.425325, 0.688191, 0.587785}, 
{0.864188, 0.442863, 0.238856}, {0.688191, 0.587785, 0.425325}, 
{0.809017, 0.309017, 0.500000}, {0.681718, 0.147621, 0.716567}, 
{0.587785, 0.425325, 0.688191}, {0.955423, 0.295242, 0.000000}, 
{1.000000, 0.000000, 0.000000}, {0.951056, 0.162460, 0.262866}, 
{0.850651, -0.525731, 0.000000},{0.955423, -0.295242, 0.000000}, 
{0.864188, -0.442863, 0.238856}, {0.951056, -0.162460, 0.262866}, 
{0.809017, -0.309017, 0.500000}, {0.681718, -0.147621, 0.716567}, 
{0.850651, 0.000000, 0.525731}, {0.864188, 0.442863, -0.238856}, 
{0.809017, 0.309017, -0.500000}, {0.951056, 0.162460, -0.262866}, 
{0.525731, 0.000000, -0.850651}, {0.681718, 0.147621, -0.716567}, 
{0.681718, -0.147621, -0.716567},{0.850651, 0.000000, -0.525731}, 
{0.809017, -0.309017, -0.500000}, {0.864188, -0.442863, -0.238856}, 
{0.951056, -0.162460, -0.262866}, {0.147621, 0.716567, -0.681718}, 
{0.309017, 0.500000, -0.809017}, {0.425325, 0.688191, -0.587785}, 
{0.442863, 0.238856, -0.864188}, {0.587785, 0.425325, -0.688191}, 
{0.688191, 0.587785, -0.425325}, {-0.147621, 0.716567, -0.681718}, 
{-0.309017, 0.500000, -0.809017}, {0.000000, 0.525731, -0.850651}, 
{-0.525731, 0.000000, -0.850651}, {-0.442863, 0.238856, -0.864188}, 
{-0.295242, 0.000000, -0.955423}, {-0.162460, 0.262866, -0.951056}, 
{0.000000, 0.000000, -1.000000}, {0.295242, 0.000000, -0.955423}, 
{0.162460, 0.262866, -0.951056}, {-0.442863, -0.238856, -0.864188}, 
{-0.309017, -0.500000, -0.809017}, {-0.162460, -0.262866, -0.951056}, 
{0.000000, -0.850651, -0.525731}, {-0.147621, -0.716567, -0.681718}, 
{0.147621, -0.716567, -0.681718}, {0.000000, -0.525731, -0.850651}, 
{0.309017, -0.500000, -0.809017}, {0.442863, -0.238856, -0.864188}, 
{0.162460, -0.262866, -0.951056}, {0.238856, -0.864188, -0.442863}, 
{0.500000, -0.809017, -0.309017}, {0.425325, -0.688191, -0.587785}, 
{0.716567, -0.681718, -0.147621}, {0.688191, -0.587785, -0.425325}, 
{0.587785, -0.425325, -0.688191}, {0.000000, -0.955423, -0.295242}, 
{0.000000, -1.000000, 0.000000}, {0.262866, -0.951056, -0.162460}, 
{0.000000, -0.850651, 0.525731}, {0.000000, -0.955423, 0.295242}, 
{0.238856, -0.864188, 0.442863}, {0.262866, -0.951056, 0.162460}, 
{0.500000, -0.809017, 0.309017}, {0.716567, -0.681718, 0.147621}, 
{0.525731, -0.850651, 0.000000}, {-0.238856, -0.864188, -0.442863}, 
{-0.500000, -0.809017, -0.309017}, {-0.262866, -0.951056, -0.162460}, 
{-0.850651, -0.525731, 0.000000}, {-0.716567, -0.681718, -0.147621}, 
{-0.716567, -0.681718, 0.147621}, {-0.525731, -0.850651, 0.000000}, 
{-0.500000, -0.809017, 0.309017}, {-0.238856, -0.864188, 0.442863}, 
{-0.262866, -0.951056, 0.162460}, {-0.864188, -0.442863, 0.238856}, 
{-0.809017, -0.309017, 0.500000}, {-0.688191, -0.587785, 0.425325}, 
{-0.681718, -0.147621, 0.716567}, {-0.442863, -0.238856, 0.864188}, 
{-0.587785, -0.425325, 0.688191}, {-0.309017, -0.500000, 0.809017}, 
{-0.147621, -0.716567, 0.681718}, {-0.425325, -0.688191, 0.587785}, 
{-0.162460, -0.262866, 0.951056}, {0.442863, -0.238856, 0.864188}, 
{0.162460, -0.262866, 0.951056}, {0.309017, -0.500000, 0.809017}, 
{0.147621, -0.716567, 0.681718}, {0.000000, -0.525731, 0.850651}, 
{0.425325, -0.688191, 0.587785}, {0.587785, -0.425325, 0.688191}, 
{0.688191, -0.587785, 0.425325}, {-0.955423, 0.295242, 0.000000}, 
{-0.951056, 0.162460, 0.262866}, {-1.000000, 0.000000, 0.000000}, 
{-0.850651, 0.000000, 0.525731}, {-0.955423, -0.295242, 0.000000}, 
{-0.951056, -0.162460, 0.262866}, {-0.864188, 0.442863, -0.238856}, 
{-0.951056, 0.162460, -0.262866}, {-0.809017, 0.309017, -0.500000}, 
{-0.864188, -0.442863, -0.238856}, {-0.951056, -0.162460, -0.262866}, 
{-0.809017, -0.309017, -0.500000}, {-0.681718, 0.147621, -0.716567}, 
{-0.681718, -0.147621, -0.716567}, {-0.850651, 0.000000, -0.525731}, 
{-0.688191, 0.587785, -0.425325}, {-0.587785, 0.425325, -0.688191}, 
{-0.425325, 0.688191, -0.587785}, {-0.425325, -0.688191, -0.587785}, 
{-0.587785, -0.425325, -0.688191}, {-0.688191, -0.587785, -0.425325}
};

int		Q_rand( int *seed ) {
	*seed = (69069 * *seed + 1);
	return *seed;
}

float	Q_random( int *seed ) {
	return ( Q_rand( seed ) & 0xffff ) / (float)0x10000;
}

float	Q_crandom( int *seed ) {
	return 2.0 * ( Q_random( seed ) - 0.5 );
}

/*
grandom

This function produces a random number with a gaussian
distribution.  This also also known as a normal or bell
curve distribution; it has a mean value of zero and a
standard deviation of one.
*/
float grandom ( void ) {
  double			v1;
  double			v2;
  double			s;
  float				x1;
  static float		x2 = 0;
  static int		toggle = 0;

  if ( toggle ) {
	  toggle = 0;
	  return x2;
  }

  do {
      v1 = -1.0 + 2.0 * random ();
      v2 = -1.0 + 2.0 * random ();
      s = v1 * v1 + v2 * v2;
  }
  while ( s >= 1.0 || s == 0 );

  s = sqrt ( -2.0 * log ( s ) / s );
  x1 = v1 * s;
  x2 = v2 * s;
  toggle = 1;
  return x1;
}


/*
erandom

This function produces a random number with a exponential
distribution and the specified mean value.
*/
float erandom( float mean ) {
	float	r;

	do {
		r = random();
	} while ( r == 0.0 );

	return -mean * log( r );
}


signed char ClampChar( int i ) {
	if ( i < -128 ) {
		return -128;
	}
	if ( i > 127 ) {
		return 127;
	}
	return i;
}

signed short ClampShort( int i ) {
	if ( i < (short)0x8000 ) {
		return (short)0x8000;
	}
	if ( i > 0x7fff ) {
		return 0x7fff;
	}
	return i;
}


// this isn't a real cheap function to call!
int DirToByte( vec3_t dir ) {
	int		i, best;
	float	d, bestd;

	if ( !dir ) {
		return 0;
	}

	bestd = 0;
	best = 0;
	for (i=0 ; i<NUMVERTEXNORMALS ; i++)
	{
		d = DotProduct (dir, bytedirs[i]);
		if (d > bestd)
		{
			bestd = d;
			best = i;
		}
	}

	return best;
}

void ByteToDir( int b, vec3_t dir ) {
	if ( b < 0 || b >= NUMVERTEXNORMALS ) {
		VectorCopy( vec3_origin, dir );
		return;
	}
	VectorCopy (bytedirs[b], dir);
}


unsigned ColorBytes3 (float r, float g, float b) {
	unsigned	i;

	( (byte *)&i )[0] = r * 255;
	( (byte *)&i )[1] = g * 255;
	( (byte *)&i )[2] = b * 255;

	return i;
}

unsigned ColorBytes4 (float r, float g, float b, float a) {
	unsigned	i;

	( (byte *)&i )[0] = r * 255;
	( (byte *)&i )[1] = g * 255;
	( (byte *)&i )[2] = b * 255;
	( (byte *)&i )[3] = a * 255;

	return i;
}

float NormalizeColor( const vec3_t in, vec3_t out ) {
	float	max;
   USES_CLAMP_ZERO;
   
	max = in[0] - in[1];
   ClampZero ( max );
   max = ( max + in[1] ) - in[2];
   ClampZero ( max );
   max += in[2];

	if ( !max ) {
		VectorClear( out );
	} else {
      float oomax = 1.f / max;
      
      out[0] = in[0] * oomax;
		out[1] = in[1] * oomax;
		out[2] = in[2] * oomax;
	}
	return max;
}


//============================================================================

void RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point,
							 float degrees )
{
	float	m[3][3];
	float	im[3][3];
	float	zrot[3][3];
	float	tmpmat[3][3];
	float	rot[3][3];
	int	i;
	vec3_t vr, vup, vf;
	float	rad;

	vf[0] = dir[0];
	vf[1] = dir[1];
	vf[2] = dir[2];

	PerpendicularVector( vr, dir );
	CrossProduct( vr, vf, vup );

	m[0][0] = vr[0];
	m[1][0] = vr[1];
	m[2][0] = vr[2];

	m[0][1] = vup[0];
	m[1][1] = vup[1];
	m[2][1] = vup[2];

	m[0][2] = vf[0];
	m[1][2] = vf[1];
	m[2][2] = vf[2];

	memcpy( im, m, sizeof( im ) );

	im[0][1] = m[1][0];
	im[0][2] = m[2][0];
	im[1][0] = m[0][1];
	im[1][2] = m[2][1];
	im[2][0] = m[0][2];
	im[2][1] = m[1][2];

	memset( zrot, 0, sizeof( zrot ) );
	zrot[0][0] = zrot[1][1] = zrot[2][2] = 1.0F;

	rad = DEG2RAD( degrees );
	zrot[0][0] = cos( rad );
	zrot[0][1] = sin( rad );
	zrot[1][0] = -sin( rad );
	zrot[1][1] = cos( rad );

	MatrixMultiply( m, zrot, tmpmat );
	MatrixMultiply( tmpmat, im, rot );

	for ( i = 0; i < 3; i++ )
	{
		dst[i] = rot[i][0] * point[0] + rot[i][1] * point[1] + rot[i][2] * point[2];
	}
}

/*
===============
RotateAroundDirection
===============
*/
void RotateAroundDirection( vec3_t axis[3], float yaw ) {

	// create an arbitrary axis[1] 
	PerpendicularVector( axis[1], axis[0] );

	// rotate it around axis[0] by yaw
	if ( yaw ) {
		vec3_t	temp;

		VectorCopy( axis[1], temp );
		RotatePointAroundVector( axis[1], axis[0], temp, yaw );
	}

	// cross to get axis[2]
	CrossProduct( axis[0], axis[1], axis[2] );
}


void vectoangles( const vec3_t value1, vec3_t angles ) {
	float	forward;
	float	yaw, pitch;
	
	if ( value1[1] == 0 && value1[0] == 0 ) {
		yaw = 0;
		if ( value1[2] > 0 ) {
			pitch = 90;
		}
		else {
			pitch = 270;
		}
	}
	else {
		if ( value1[0] ) {
			yaw = ( atan2 ( value1[1], value1[0] ) * 180 / M_PI );
		}
		else if ( value1[1] > 0 ) {
			yaw = 90;
		}
		else {
			yaw = 270;
		}
		if ( yaw < 0 ) {
			yaw += 360;
		}

		forward = sqrt ( value1[0]*value1[0] + value1[1]*value1[1] );
		pitch = ( atan2(value1[2], forward) * 180 / M_PI );
		if ( pitch < 0 ) {
			pitch += 360;
		}
	}

	angles[PITCH] = -pitch;
	angles[YAW] = yaw;
	angles[ROLL] = 0;
}

float vectoyaw( const vec3_t vec ) {
	float	yaw;
	
	if (vec[YAW] == 0 && vec[PITCH] == 0) {
		yaw = 0;
	} else {
		if (vec[PITCH]) {
			yaw = ( atan2( vec[YAW], vec[PITCH]) * 180 / M_PI );
		} else if (vec[YAW] > 0) {
			yaw = 90;
		} else {
			yaw = 270;
		}
		if (yaw < 0) {
			yaw += 360;
		}
	}

	return yaw;
}

void AxisClear( vec3_t axis[3] ) {
	axis[0][0] = 1;
	axis[0][1] = 0;
	axis[0][2] = 0;
	axis[1][0] = 0;
	axis[1][1] = 1;
	axis[1][2] = 0;
	axis[2][0] = 0;
	axis[2][1] = 0;
	axis[2][2] = 1;
}

void AxisCopy( vec3_t in[3], vec3_t out[3] ) {
	VectorCopy( in[0], out[0] );
	VectorCopy( in[1], out[1] );
	VectorCopy( in[2], out[2] );
}

void ProjectPointOnPlane( vec3_t dst, const vec3_t p, const vec3_t normal )
{
	float d;
	vec3_t n;
	float inv_denom;

	inv_denom = 1.0F / DotProduct( normal, normal );

	d = DotProduct( normal, p ) * inv_denom;

	n[0] = normal[0] * inv_denom;
	n[1] = normal[1] * inv_denom;
	n[2] = normal[2] * inv_denom;

	dst[0] = p[0] - d * n[0];
	dst[1] = p[1] - d * n[1];
	dst[2] = p[2] - d * n[2];
}

/*
================
MakeNormalVectors

Given a normalized forward vector, create two
other perpendicular vectors
================
*/
void MakeNormalVectors (const vec3_t forward, vec3_t right, vec3_t up)
{
	float		d;

	// this rotate and negate guarantees a vector
	// not colinear with the original
	right[1] = -forward[0];
	right[2] = forward[1];
	right[0] = forward[2];

	d = DotProduct (right, forward);
	VectorMA (right, -d, forward, right);
	VectorNormalize (right);
	CrossProduct (right, forward, up);
}

void VectorRotate( vec3_t in, vec3_t matrix[3], vec3_t out )
{
	out[0] = DotProduct( in, matrix[0] );
	out[1] = DotProduct( in, matrix[1] );
	out[2] = DotProduct( in, matrix[2] );
}

void AccumulateTransform( vec3_t dstOrigin, vec3_t dstAxes[3],
						  vec3_t childOrigin, vec3_t childAxes[3], 
						  vec3_t parentOrigin, vec3_t parentAxes[3] )
{
	vec3_t tmpVector;

	// compute final angles
	MatrixMultiply( childAxes, parentAxes, dstAxes );

	// compute final origin as parent * p
	VectorRotate( childOrigin, parentAxes, tmpVector );
	VectorAdd( tmpVector, parentOrigin, dstOrigin );
}

void AccumulatePosition( vec3_t dstOrigin, vec3_t childOrigin, vec3_t parentOrigin, vec3_t parentAxes[3] )
{
	vec3_t tmpVector;

	// compute final origin as parent * p
	VectorRotate( childOrigin, parentAxes, tmpVector );
	VectorAdd( tmpVector, parentOrigin, dstOrigin );
}


//============================================================================

/*
** float q_rsqrt( float number )
*/
#if !id386
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;						// evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}
#else
static const float ONE_HALF = 0.5f;
static const float THREE_HALVES = 1.5f;
__declspec(naked) float Q_rsqrt ( float f )
{
	__asm
	{
		fld			dword ptr [esp + 4]
		fmul		dword ptr [ONE_HALF]

		mov			eax, [esp + 4]
		mov			ecx, 0x5f3759df

		shr			eax, 1

		sub			ecx, eax

		mov			[esp + 4], ecx

		fmul		dword ptr [esp + 4]
		fld			dword ptr [esp + 4]
		fmul		dword ptr [esp + 4]
		fld			dword ptr [THREE_HALVES]
		fmul		dword ptr [esp + 4]
		fxch		st(2)
		fmulp		st(1), st
		fsubp		st(1), st
		ret
	}
}
#endif

float Q_fabs( float f ) {
	int tmp = * ( int * ) &f;
	tmp &= 0x7FFFFFFF;
	return * ( float * ) &tmp;
}

//============================================================

/*
===============
LerpAngle

===============
*/
float LerpAngle (float from, float to, float frac) {
	float	a;

	if ( to - from > 180 ) {
		to -= 360;
	}
	if ( to - from < -180 ) {
		to += 360;
	}
	a = from + frac * (to - from);

	return a;
}

/*
===============
LerpAngleFromCurrent

===============
*/
float LerpAngleFromCurrent (float from, float to, float current, float frac) {
	float	a;

	if ( to - current > 180 ) {
		to -= 360;
	}
	if ( to - current < -180 ) {
		to += 360;
	}
	a = from + frac * (to - from);

	return a;
}

/*
=================
AngleSubtract

Always returns a value from -180 to 180
=================
*/
float	AngleSubtract( float a1, float a2 ) {
	float	a;

	a = a1 - a2;
	while ( a > 180 ) {
		a -= 360;
	}
	while ( a < -180 ) {
		a += 360;
	}
	return a;
}


void AnglesSubtract( vec3_t v1, vec3_t v2, vec3_t v3 ) {
	v3[0] = AngleSubtract( v1[0], v2[0] );
	v3[1] = AngleSubtract( v1[1], v2[1] );
	v3[2] = AngleSubtract( v1[2], v2[2] );
}


float	AngleMod(float a)
{
#if 0
	if (a >= 0)
		a -= 360*(int)(a/360);
	else
		a += 360*( 1 + (int)(-a/360) );
#endif
	a = (360.0/65536) * ((int)(a*(65536/360.0)) & 65535);
	return a;
}


/*
=================
AngleNormalize360

returns angle normalized to the range [0 <= angle < 360]
=================
*/
float AngleNormalize360 ( float angle ) {
	return (360.0 / 65536) * ((int)(angle * (65536 / 360.0)) & 65535);
}


/*
=================
AngleNormalize180

returns angle normalized to the range [-180 < angle <= 180]
=================
*/
float AngleNormalize180 ( float angle ) {
	angle = AngleNormalize360( angle );
	if ( angle > 180.0 ) {
		angle -= 360.0;
	}
	return angle;
}


/*
=================
AngleDelta

returns the normalized delta from angle1 to angle2
=================
*/
float AngleDelta ( float angle1, float angle2 ) {
	return AngleNormalize180( angle1 - angle2 );
}

/*
=================
AnglesDelta

returns the normalized delta from angle1 to angle2
=================
*/
void AnglesDelta( vec3_t v1, vec3_t v2, vec3_t v3 ) {
	v3[0] = AngleDelta( v1[0], v2[0] );
	v3[1] = AngleDelta( v1[1], v2[1] );
	v3[2] = AngleDelta( v1[2], v2[2] );
}


//============================================================


/*
=================
SetPlaneSignbits
=================
*/
void SetPlaneSignbits (cplane_t *out) {
	int	bits, j;

	// for fast box on planeside test
	bits = 0;
	for (j=0 ; j<3 ; j++) {
		if (out->normal[j] < 0) {
			bits |= 1<<j;
		}
	}
	out->signbits = bits;
}

/*
==================
BoxOnPlaneSide

Returns 1, 2, or 1 + 2

// this is the slow, general version
int BoxOnPlaneSide2 (vec3_t emins, vec3_t emaxs, struct cplane_s *p)
{
	int		i;
	float	dist1, dist2;
	int		sides;
	vec3_t	corners[2];

	for (i=0 ; i<3 ; i++)
	{
		if (p->normal[i] < 0)
		{
			corners[0][i] = emins[i];
			corners[1][i] = emaxs[i];
		}
		else
		{
			corners[1][i] = emins[i];
			corners[0][i] = emaxs[i];
		}
	}
	dist1 = DotProduct (p->normal, corners[0]) - p->dist;
	dist2 = DotProduct (p->normal, corners[1]) - p->dist;
	sides = 0;
	if (dist1 >= 0)
		sides = 1;
	if (dist2 < 0)
		sides |= 2;

	return sides;
}

==================
*/
#if !id386
int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct cplane_s *p)
{
	float	dist1, dist2;
	int		sides;

// fast axial cases
	if (p->type < 3)
	{
		if (p->dist <= emins[p->type])
			return 1;
		if (p->dist >= emaxs[p->type])
			return 2;
		return 3;
	}
	
// general case
	switch (p->signbits)
	{
	case 0:
		dist1 = p->normal[0]*emaxs[0] + p->normal[1]*emaxs[1] + p->normal[2]*emaxs[2];
		dist2 = p->normal[0]*emins[0] + p->normal[1]*emins[1] + p->normal[2]*emins[2];
		break;
	case 1:
		dist1 = p->normal[0]*emins[0] + p->normal[1]*emaxs[1] + p->normal[2]*emaxs[2];
		dist2 = p->normal[0]*emaxs[0] + p->normal[1]*emins[1] + p->normal[2]*emins[2];
		break;
	case 2:
		dist1 = p->normal[0]*emaxs[0] + p->normal[1]*emins[1] + p->normal[2]*emaxs[2];
		dist2 = p->normal[0]*emins[0] + p->normal[1]*emaxs[1] + p->normal[2]*emins[2];
		break;
	case 3:
		dist1 = p->normal[0]*emins[0] + p->normal[1]*emins[1] + p->normal[2]*emaxs[2];
		dist2 = p->normal[0]*emaxs[0] + p->normal[1]*emaxs[1] + p->normal[2]*emins[2];
		break;
	case 4:
		dist1 = p->normal[0]*emaxs[0] + p->normal[1]*emaxs[1] + p->normal[2]*emins[2];
		dist2 = p->normal[0]*emins[0] + p->normal[1]*emins[1] + p->normal[2]*emaxs[2];
		break;
	case 5:
		dist1 = p->normal[0]*emins[0] + p->normal[1]*emaxs[1] + p->normal[2]*emins[2];
		dist2 = p->normal[0]*emaxs[0] + p->normal[1]*emins[1] + p->normal[2]*emaxs[2];
		break;
	case 6:
		dist1 = p->normal[0]*emaxs[0] + p->normal[1]*emins[1] + p->normal[2]*emins[2];
		dist2 = p->normal[0]*emins[0] + p->normal[1]*emaxs[1] + p->normal[2]*emaxs[2];
		break;
	case 7:
		dist1 = p->normal[0]*emins[0] + p->normal[1]*emins[1] + p->normal[2]*emins[2];
		dist2 = p->normal[0]*emaxs[0] + p->normal[1]*emaxs[1] + p->normal[2]*emaxs[2];
		break;
	default:
		dist1 = dist2 = 0;		// shut up compiler
		break;
	}

	sides = 0;
	if (dist1 >= p->dist)
		sides = 1;
	if (dist2 < p->dist)
		sides |= 2;

	return sides;
}
#else
#pragma warning( disable: 4035 )

__declspec( naked ) int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct cplane_s *p)
{
	static int bops_initialized;
	static int Ljmptab[8];

	__asm {

		push ebx
			
		cmp bops_initialized, 1
		je  initialized
		mov bops_initialized, 1
		
		mov Ljmptab[0*4], offset Lcase0
		mov Ljmptab[1*4], offset Lcase1
		mov Ljmptab[2*4], offset Lcase2
		mov Ljmptab[3*4], offset Lcase3
		mov Ljmptab[4*4], offset Lcase4
		mov Ljmptab[5*4], offset Lcase5
		mov Ljmptab[6*4], offset Lcase6
		mov Ljmptab[7*4], offset Lcase7
			
initialized:

		mov edx,ds:dword ptr[4+12+esp]
		mov ecx,ds:dword ptr[4+4+esp]
		xor eax,eax
		mov ebx,ds:dword ptr[4+8+esp]
		mov al,ds:byte ptr[17+edx]
		cmp al,8
		jge Lerror
		fld ds:dword ptr[0+edx]
		fld st(0)
		jmp dword ptr[Ljmptab+eax*4]
Lcase0:
		fmul ds:dword ptr[ebx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ebx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase1:
		fmul ds:dword ptr[ecx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ebx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase2:
		fmul ds:dword ptr[ebx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ecx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase3:
		fmul ds:dword ptr[ecx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ecx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase4:
		fmul ds:dword ptr[ebx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ebx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase5:
		fmul ds:dword ptr[ecx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ebx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase6:
		fmul ds:dword ptr[ebx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ecx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ecx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
		jmp LSetSides
Lcase7:
		fmul ds:dword ptr[ecx]
		fld ds:dword ptr[0+4+edx]
		fxch st(2)
		fmul ds:dword ptr[ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[4+ecx]
		fld ds:dword ptr[0+8+edx]
		fxch st(2)
		fmul ds:dword ptr[4+ebx]
		fxch st(2)
		fld st(0)
		fmul ds:dword ptr[8+ecx]
		fxch st(5)
		faddp st(3),st(0)
		fmul ds:dword ptr[8+ebx]
		fxch st(1)
		faddp st(3),st(0)
		fxch st(3)
		faddp st(2),st(0)
LSetSides:
		faddp st(2),st(0)
		fcomp ds:dword ptr[12+edx]
		xor ecx,ecx
		fnstsw ax
		fcomp ds:dword ptr[12+edx]
		and ah,1
		xor ah,1
		add cl,ah
		fnstsw ax
		and ah,1
		add ah,ah
		add cl,ah
		pop ebx
		mov eax,ecx
		ret
Lerror:
		int 3
	}
}
#pragma warning( default: 4035 )
#endif

/*
=================
RadiusFromBounds
=================
*/
float RadiusFromBounds( const vec3_t mins, const vec3_t maxs ) {
	int		i;
	vec3_t	corner;
	float	a, b;

	for (i=0 ; i<3 ; i++) {
		a = fabs( mins[i] );
		b = fabs( maxs[i] );
		corner[i] = a > b ? a : b;
	}

	return VectorLength (corner);
}

#define BOUNDS_CLEAR_VALUE 99999

void ClearBounds( vec3_t mins, vec3_t maxs ) {
	mins[0] = mins[1] = mins[2] = BOUNDS_CLEAR_VALUE;
	maxs[0] = maxs[1] = maxs[2] = -BOUNDS_CLEAR_VALUE;
}

qboolean BoundsClear( vec3_t mins, vec3_t maxs ) 
   {
   if ( 
         ( mins[ 0 ] == BOUNDS_CLEAR_VALUE ) &&
         ( mins[ 1 ] == BOUNDS_CLEAR_VALUE ) &&
         ( mins[ 2 ] == BOUNDS_CLEAR_VALUE ) &&
         ( maxs[ 0 ] == -BOUNDS_CLEAR_VALUE ) &&
         ( maxs[ 1 ] == -BOUNDS_CLEAR_VALUE ) &&
         ( maxs[ 2 ] == -BOUNDS_CLEAR_VALUE )
      )
      {
      return qtrue;
      }
   else
      {
      return qfalse;
      }
   }

void AddPointToBounds( const vec3_t v, vec3_t mins, vec3_t maxs ) {
	if ( v[0] < mins[0] ) {
		mins[0] = v[0];
	}
	if ( v[0] > maxs[0]) {
		maxs[0] = v[0];
	}

	if ( v[1] < mins[1] ) {
		mins[1] = v[1];
	}
	if ( v[1] > maxs[1]) {
		maxs[1] = v[1];
	}

	if ( v[2] < mins[2] ) {
		mins[2] = v[2];
	}
	if ( v[2] > maxs[2]) {
		maxs[2] = v[2];
	}
}


int VectorCompare( const vec3_t v1, const vec3_t v2 ) {
	if (v1[0] != v2[0] || v1[1] != v2[1] || v1[2] != v2[2]) {
		return 0;
	}
			
	return 1;
}


vec_t VectorNormalize( vec3_t v ) {
	float	length, ilength;

	length = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
	length = sqrt (length);

	if ( length ) {
		ilength = 1/length;
		v[0] *= ilength;
		v[1] *= ilength;
		v[2] *= ilength;
	}
		
	return length;
}

//
// fast vector normalize routine that does not check to make sure
// that length != 0, nor does it return length
//
void VectorNormalizeFast( vec3_t v )
{
	float ilength;

	ilength = Q_rsqrt( DotProduct( v, v ) );

	v[0] *= ilength;
	v[1] *= ilength;
	v[2] *= ilength;
}

vec_t VectorNormalize2( const vec3_t v, vec3_t out) {
	float	length, ilength;

	length = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
	length = sqrt (length);

	if (length)
	{
		ilength = 1/length;
		out[0] = v[0]*ilength;
		out[1] = v[1]*ilength;
		out[2] = v[2]*ilength;
	} else {
		VectorClear( out );
	}
		
	return length;

}

void _VectorMA( const vec3_t veca, float scale, const vec3_t vecb, vec3_t vecc) {
	vecc[0] = veca[0] + scale*vecb[0];
	vecc[1] = veca[1] + scale*vecb[1];
	vecc[2] = veca[2] + scale*vecb[2];
}


vec_t _DotProduct( const vec3_t v1, const vec3_t v2 ) {
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void _VectorSubtract( const vec3_t veca, const vec3_t vecb, vec3_t out ) {
	out[0] = veca[0]-vecb[0];
	out[1] = veca[1]-vecb[1];
	out[2] = veca[2]-vecb[2];
}

void _VectorAdd( const vec3_t veca, const vec3_t vecb, vec3_t out ) {
	out[0] = veca[0]+vecb[0];
	out[1] = veca[1]+vecb[1];
	out[2] = veca[2]+vecb[2];
}

void _VectorCopy( const vec3_t in, vec3_t out ) {
	out[0] = in[0];
	out[1] = in[1];
	out[2] = in[2];
}

void _VectorScale( const vec3_t in, vec_t scale, vec3_t out ) {
	out[0] = in[0]*scale;
	out[1] = in[1]*scale;
	out[2] = in[2]*scale;
}

void CrossProduct( const vec3_t v1, const vec3_t v2, vec3_t cross ) {
	cross[0] = v1[1]*v2[2] - v1[2]*v2[1];
	cross[1] = v1[2]*v2[0] - v1[0]*v2[2];
	cross[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

vec_t VectorLength( const vec3_t v ) {
	return sqrt (v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}


vec_t Distance( const vec3_t p1, const vec3_t p2 ) {
	vec3_t	v;

	VectorSubtract (p2, p1, v);
	return VectorLength( v );
}

vec_t DistanceSquared( const vec3_t p1, const vec3_t p2 ) {
	vec3_t	v;

	VectorSubtract (p2, p1, v);
	return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
}


void VectorInverse( vec3_t v ){
	v[0] = -v[0];
	v[1] = -v[1];
	v[2] = -v[2];
}

void Vector4Scale( const vec4_t in, vec_t scale, vec4_t out ) {
	out[0] = in[0]*scale;
	out[1] = in[1]*scale;
	out[2] = in[2]*scale;
	out[3] = in[3]*scale;
}


int Q_log2( int val ) {
	int answer;

	answer = 0;
	while ( ( val>>=1 ) != 0 ) {
		answer++;
	}
	return answer;
}

/*
** NormalToLatLong
**
** Lat = 0 at (1,0,0) to 360 (-1,0,0), encoded in 8-bit sine table format
** Lng = 0 at (0,0,1) to 180 (0,0,-1), encoded in 8-bit sine table format
**
** Latitude is encoded in high 8 bits
*/
unsigned short NormalToLatLong( vec3_t normal )
{
   unsigned short ll;

   // check for singularities
   if ( normal[0] == 0 && normal[1] == 0 )
   {
      if ( normal[2] > 0 )
      {
         ll = 0;        // lat = 0, long = 0
      }
      else
      {
         ll = 128;         // lat = 0, long = 128
      }
   }
   else
   {
      unsigned short a, b;

      a = RAD2DEG( atan2( normal[1], normal[0] ) ) * (255.0f / 360.0f );
      a &= 0xff;

      b = RAD2DEG( acos( normal[2] ) ) * ( 255.0f / 360.0f );
      b &= 0xff;

      ll = ( a << 8 ) | b;
   }

   return ll;
}
 

float bias(float a, float b)
{
	return pow(a, log(b) / log(0.5));
}

float gain(float a, float b)
{
	float p = log(1. - b) / log(0.5);

	if (a < .001)
		return 0.;
	else if (a > .999)
		return 1.;
	if (a < 0.5)
		return pow(2 * a, p) / 2;
	else
		return 1. - pow(2 * (1. - a), p) / 2;
}

float noise(float vec[], int len)
{
	switch (len) {
	case 0:
		return 0.;
	case 1:
		return noise1(vec[0]);
	case 2:
		return noise2(vec);
	default:
		return noise3(vec);
	}
}

float turbulence(float *v, float freq)
{
	float t, vec[3];

	for (t = 0. ; freq >= 1. ; freq /= 2) {
		vec[0] = freq * v[0];
		vec[1] = freq * v[1];
		vec[2] = freq * v[2];
		t += fabs(noise3(vec)) / freq;
	}
	return t;
}

/* noise functions over 1, 2, and 3 dimensions */

#define B 0x100
#define BM 0xff

#define N 0x1000
#define NP 12   /* 2^N */
#define NM 0xfff

static int p[B + B + 2];
static float g3[B + B + 2][3];
static float g2[B + B + 2][2];
static float g1[B + B + 2];
static int start = 1;

static void init(void);

#define s_curve(t) ( t * t * (3. - 2. * t) )

#define lerp(t, a, b) ( a + t * (b - a) )

#define setup(i,b0,b1,r0,r1)\
	t = vec[i] + N;\
	b0 = ((int)t) & BM;\
	b1 = (b0+1) & BM;\
	r0 = t - (int)t;\
	r1 = r0 - 1.;

float noise1(float arg)
{
	int bx0, bx1;
	float rx0, rx1, sx, t, u, v, vec[1];

	vec[0] = arg;
	if (start) {
		start = 0;
		init();
	}

	setup(0, bx0,bx1, rx0,rx1);

	sx = s_curve(rx0);

	u = rx0 * g1[ p[ bx0 ] ];
	v = rx1 * g1[ p[ bx1 ] ];

	return lerp(sx, u, v);
}

float noise2(float vec[2])
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
	register int i, j;

	if (start) {
		start = 0;
		init();
	}

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

#define at2(rx,ry) ( rx * q[0] + ry * q[1] )

	q = g2[ b00 ] ; u = at2(rx0,ry0);
	q = g2[ b10 ] ; v = at2(rx1,ry0);
	a = lerp(sx, u, v);

	q = g2[ b01 ] ; u = at2(rx0,ry1);
	q = g2[ b11 ] ; v = at2(rx1,ry1);
	b = lerp(sx, u, v);

	return lerp(sy, a, b);
}

float noise3(float vec[3])
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	register int i, j;

	if (start) {
		start = 0;
		init();
	}

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	setup(2, bz0,bz1, rz0,rz1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

	q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
	q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
	a = lerp(t, u, v);

	q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
	q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
	q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
	a = lerp(t, u, v);

	q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
	q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	return lerp(sz, c, d);
}

static void normalize2(float v[2])
{
	float s;

	s = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
}

static void normalize3(float v[3])
{
	float s;

	s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
}

static void init(void)
{
	int i, j, k;

	for (i = 0 ; i < B ; i++) {
		p[i] = i;

		g1[i] = (float)((rand() % (B + B)) - B) / B;

		for (j = 0 ; j < 2 ; j++)
			g2[i][j] = (float)((rand() % (B + B)) - B) / B;
		normalize2(g2[i]);

		for (j = 0 ; j < 3 ; j++)
			g3[i][j] = (float)((rand() % (B + B)) - B) / B;
		normalize3(g3[i]);
	}

	while (--i) {
		k = p[i];
		p[i] = p[j = rand() % B];
		p[j] = k;
	}

	for (i = 0 ; i < B + 2 ; i++) {
		p[B + i] = p[i];
		g1[B + i] = g1[i];
		for (j = 0 ; j < 2 ; j++)
			g2[B + i][j] = g2[i][j];
		for (j = 0 ; j < 3 ; j++)
			g3[B + i][j] = g3[i][j];
	}
}


/*
================
R_ConcatRotations
================
*/
void R_ConcatRotations (float in1[3][3], float in2[3][3], float out[3][3])
{
	out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
				in1[0][2] * in2[2][0];
	out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
				in1[0][2] * in2[2][1];
	out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
				in1[0][2] * in2[2][2];
	out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
				in1[1][2] * in2[2][0];
	out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
				in1[1][2] * in2[2][1];
	out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
				in1[1][2] * in2[2][2];
	out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
				in1[2][2] * in2[2][0];
	out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
				in1[2][2] * in2[2][1];
	out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
				in1[2][2] * in2[2][2];
}


/*
================
R_ConcatTransforms
================
*/
void R_ConcatTransforms (float in1[3][4], float in2[3][4], float out[3][4])
{
	out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
				in1[0][2] * in2[2][0];
	out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
				in1[0][2] * in2[2][1];
	out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
				in1[0][2] * in2[2][2];
	out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] +
				in1[0][2] * in2[2][3] + in1[0][3];
	out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
				in1[1][2] * in2[2][0];
	out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
				in1[1][2] * in2[2][1];
	out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
				in1[1][2] * in2[2][2];
	out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] +
				in1[1][2] * in2[2][3] + in1[1][3];
	out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
				in1[2][2] * in2[2][0];
	out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
				in1[2][2] * in2[2][1];
	out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
				in1[2][2] * in2[2][2];
	out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] +
				in1[2][2] * in2[2][3] + in1[2][3];
}


//============================================================================


float	anglemod(float a)
{
#if 0
	if (a >= 0)
		a -= 360*(int)(a/360);
	else
		a += 360*( 1 + (int)(-a/360) );
#endif
	a = (360.0/65536) * ((int)(a*(65536/360.0)) & 65535);
	return a;
}

float angledist( float ang )
	{
	float a;

	a = anglemod( ang );
	if ( a > 180 )
		{
		a -= 360;
		}

	return a;
	}

	int		i;
	vec3_t	corners[2];


// this is the slow, general version
int BoxOnPlaneSide2 (vec3_t emins, vec3_t emaxs, struct cplane_s *p)
{
	int		i;
	float	dist1, dist2;
	int		sides;
	vec3_t	corners[2];

	for (i=0 ; i<3 ; i++)
	{
		if (p->normal[i] < 0)
		{
			corners[0][i] = emins[i];
			corners[1][i] = emaxs[i];
		}
		else
		{
			corners[1][i] = emins[i];
			corners[0][i] = emaxs[i];
		}
	}
	dist1 = DotProduct (p->normal, corners[0]) - p->dist;
	dist2 = DotProduct (p->normal, corners[1]) - p->dist;
	sides = 0;
	if (dist1 >= 0)
		sides = 1;
	if (dist2 < 0)
		sides |= 2;

	return sides;
}

/*
=================
CalculateRotatedBounds
=================
*/         
void CalculateRotatedBounds( vec3_t angles, vec3_t mins, vec3_t maxs )
   {
   int i;
   vec3_t rotmins, rotmaxs;
   float trans[3][3];

   AnglesToAxis( angles, trans );
   ClearBounds( rotmins, rotmaxs );
	for ( i = 0; i < 8; i++ )
   	{
		vec3_t   tmp, rottemp;

		if ( i & 1 )
			tmp[0] = mins[0];
		else
			tmp[0] = maxs[0];

		if ( i & 2 )
			tmp[1] = mins[1];
		else
			tmp[1] = maxs[1];

		if ( i & 4 )
			tmp[2] = mins[2];
		else
			tmp[2] = maxs[2];

      MatrixTransformVector( tmp, trans, rottemp );
      AddPointToBounds( rottemp, rotmins, rotmaxs );
		}
   VectorCopy( rotmins, mins );
   VectorCopy( rotmaxs, maxs );
   }

/*
=================
CalculateRotatedBounds2
=================
*/         
void CalculateRotatedBounds2( float trans[3][3], vec3_t mins, vec3_t maxs )
   {
   int i;
   vec3_t rotmins, rotmaxs;

   ClearBounds( rotmins, rotmaxs );
	for ( i = 0; i < 8; i++ )
   	{
		vec3_t   tmp, rottemp;

		if ( i & 1 )
			tmp[0] = mins[0];
		else
			tmp[0] = maxs[0];

		if ( i & 2 )
			tmp[1] = mins[1];
		else
			tmp[1] = maxs[1];

		if ( i & 4 )
			tmp[2] = mins[2];
		else
			tmp[2] = maxs[2];

      MatrixTransformVector( tmp, trans, rottemp );
      AddPointToBounds( rottemp, rotmins, rotmaxs );
		}
   VectorCopy( rotmins, mins );
   VectorCopy( rotmaxs, maxs );
   }

#define BBOX_XBITS 9
#define BBOX_YBITS 8
#define BBOX_ZBOTTOMBITS 5
#define BBOX_ZTOPBITS 9

#define BBOX_MAX_X ( 1 << BBOX_XBITS )
#define BBOX_MAX_Y ( 1 << BBOX_YBITS )
#define BBOX_MAX_BOTTOM_Z ( 1 << ( BBOX_ZBOTTOMBITS - 1 ) )
#define BBOX_REALMAX_BOTTOM_Z ( 1 << BBOX_ZBOTTOMBITS )
#define BBOX_MAX_TOP_Z ( 1 << BBOX_ZTOPBITS )

/*
=================
BoundingBoxToInteger
=================
*/         
int BoundingBoxToInteger( vec3_t mins, vec3_t maxs )
   {
   int x, y, zd, zu, result;

   x = maxs[ 0 ];
   if ( x < 0 )
      x = 0;
   if ( x >= BBOX_MAX_X )
      x = BBOX_MAX_X - 1;

   y = maxs[ 1 ];
   if ( y < 0 )
      y = 0;
   if ( y >= BBOX_MAX_Y )
      y = BBOX_MAX_Y - 1;

   zd = mins[ 2 ] + BBOX_MAX_BOTTOM_Z;
   if ( zd < 0 )
      {
      zd = 0;
      }
   if ( zd >= BBOX_REALMAX_BOTTOM_Z )
      {
      zd = BBOX_REALMAX_BOTTOM_Z - 1;
      }

   zu = maxs[ 2 ];
   if ( zu < 0 )
      zu = 0;
   if ( zu >= BBOX_MAX_TOP_Z )
      zu = BBOX_MAX_TOP_Z - 1;

   result = x |
            ( y << BBOX_XBITS ) |
            ( zd << ( BBOX_XBITS + BBOX_YBITS ) ) |
            ( zu << ( BBOX_XBITS + BBOX_YBITS + BBOX_ZBOTTOMBITS ) );

   return result;
   }

/*
=================
IntegerToBoundingBox
=================
*/         
void IntegerToBoundingBox( int num, vec3_t mins, vec3_t maxs )
   {
   int x, y, zd, zu;

   x = num & ( BBOX_MAX_X - 1 );
   y = ( num >> ( BBOX_XBITS ) ) & ( BBOX_MAX_Y -1 );
   zd = ( num >> ( BBOX_XBITS + BBOX_YBITS ) ) & ( BBOX_REALMAX_BOTTOM_Z - 1 );
   zd -= BBOX_MAX_BOTTOM_Z;
   zu = ( num >> ( BBOX_XBITS + BBOX_YBITS + BBOX_ZBOTTOMBITS ) ) & ( BBOX_MAX_TOP_Z - 1 );

   mins[ 0 ] = -x;
   mins[ 1 ] = -y;
   mins[ 2 ] = zd;

   maxs[ 0 ] = x;
   maxs[ 1 ] = y;
   maxs[ 2 ] = zu;
   }

//====================================================================


void MatrixTransformVector
	(
	vec3_t in,
	float mat[ 3 ][ 3 ],
	vec3_t out
	)

	{
	out[ 0 ] = in[ 0 ] * mat[ 0 ][ 0 ] + in[ 1 ] * mat[ 1 ][ 0 ] + in[ 2 ] * mat[ 2 ][ 0 ];
	out[ 1 ] = in[ 0 ] * mat[ 0 ][ 1 ] + in[ 1 ] * mat[ 1 ][ 1 ] + in[ 2 ] * mat[ 2 ][ 1 ];
	out[ 2 ] = in[ 0 ] * mat[ 0 ][ 2 ] + in[ 1 ] * mat[ 1 ][ 2 ] + in[ 2 ] * mat[ 2 ][ 2 ];
	}

void Matrix4TransformVector
	(
	vec3_t in,
	float mat[ 4 ][ 4 ],
	vec3_t out
	)

	{
	out[ 0 ] = in[ 0 ] * mat[ 0 ][ 0 ] + in[ 1 ] * mat[ 1 ][ 0 ] + in[ 2 ] * mat[ 2 ][ 0 ] + mat[ 3 ][ 0 ];
	out[ 1 ] = in[ 0 ] * mat[ 0 ][ 1 ] + in[ 1 ] * mat[ 1 ][ 1 ] + in[ 2 ] * mat[ 2 ][ 1 ] + mat[ 3 ][ 1 ];
	out[ 2 ] = in[ 0 ] * mat[ 0 ][ 2 ] + in[ 1 ] * mat[ 1 ][ 2 ] + in[ 2 ] * mat[ 2 ][ 2 ] + mat[ 3 ][ 2 ];
	}

void MatrixToEulerAngles
	(
	float mat[ 3 ][ 3 ],
	vec3_t ang
	)

	{
	double theta;
	double cp;
	double sp;

	sp = mat[ 0 ][ 2 ];

	// cap off our sin value so that we don't get any NANs
	if ( sp > 1.0 )
		{
		sp = 1.0;
		}
	if ( sp < -1.0 )
		{
		sp = -1.0;
		}

	theta = -asin( sp );
	cp = cos( theta );

	if ( cp > 8192 * FLT_EPSILON )
		{
		ang[ 0 ] = theta * 180 / M_PI;
		ang[ 1 ] = atan2( mat[ 0 ][ 1 ], mat[ 0 ][ 0 ] ) * 180 / M_PI;
		ang[ 2 ] = atan2( mat[ 1 ][ 2 ], mat[ 2 ][ 2 ] ) * 180 / M_PI;
		}
	else
		{
		ang[ 0 ] = theta * 180 / M_PI;
		ang[ 1 ] = -atan2( mat[ 1 ][ 0 ], mat[ 1 ][ 1 ] ) * 180 / M_PI;
		ang[ 2 ] = 0;
		}
	}

void TransposeMatrix
	(
	float in[ 3 ][ 3 ],
	float out[ 3 ][ 3 ]
	)

	{
	out[ 0 ][ 0 ] = in[ 0 ][ 0 ];
	out[ 0 ][ 1 ] = in[ 1 ][ 0 ];
	out[ 0 ][ 2 ] = in[ 2 ][ 0 ];
	out[ 1 ][ 0 ] = in[ 0 ][ 1 ];
	out[ 1 ][ 1 ] = in[ 1 ][ 1 ];
	out[ 1 ][ 2 ] = in[ 2 ][ 1 ];
	out[ 2 ][ 0 ] = in[ 0 ][ 2 ];
	out[ 2 ][ 1 ] = in[ 1 ][ 2 ];
	out[ 2 ][ 2 ] = in[ 2 ][ 2 ];
	}

void OrthoNormalize
	(
	float mat[3][3]
	)

	{
	VectorNormalize( mat[ 0 ] );
	CrossProduct( mat[ 0 ], mat[ 1 ], mat[ 2 ] );
	VectorNormalize( mat[ 2 ] );
	CrossProduct( mat[ 2 ], mat[ 0 ], mat[ 1 ] );
	VectorNormalize( mat[ 1 ] );
	}

float NormalizeQuat
	(
	float q[ 4 ]
	)

	{
	float	length, ilength;

	length = q[ 0 ] * q[ 0 ] + q[ 1 ] * q[ 1 ] + q[ 2 ] * q[ 2 ] + q[ 3 ] * q[ 3 ];
	length = sqrt( length );

	if ( length )
		{
		ilength = 1 / length;
		q[ 0 ] *= ilength;
		q[ 1 ] *= ilength;
		q[ 2 ] *= ilength;
		q[ 3 ] *= ilength;
		}
		
	return length;
	}

void MatToQuat
	(
	float srcMatrix[ 3 ][ 3 ],
	float destQuat[ 4 ]
	)
	
	{
	double  	trace, s;
	int     	i, j, k;
	static int 	next[3] = {Y, Z, X};

	trace = srcMatrix[X][X] + srcMatrix[Y][Y]+ srcMatrix[Z][Z];

	if (trace > 0.0)
		{
		s = sqrt(trace + 1.0);
		destQuat[W] = s * 0.5;
		s = 0.5 / s;
    
		destQuat[X] = (srcMatrix[Z][Y] - srcMatrix[Y][Z]) * s;
		destQuat[Y] = (srcMatrix[X][Z] - srcMatrix[Z][X]) * s;
		destQuat[Z] = (srcMatrix[Y][X] - srcMatrix[X][Y]) * s;
		} 
	else 
		{
		i = X;
		if (srcMatrix[Y][Y] > srcMatrix[X][X])
			i = Y;
		if (srcMatrix[Z][Z] > srcMatrix[i][i])
			i = Z;
		j = next[i];  
		k = next[j];
    
		s = sqrt( (srcMatrix[i][i] - (srcMatrix[j][j]+srcMatrix[k][k])) + 1.0 );
		destQuat[i] = s * 0.5;
    
		s = 0.5 / s;
    
		destQuat[W] = (srcMatrix[k][j] - srcMatrix[j][k]) * s;
		destQuat[j] = (srcMatrix[j][i] + srcMatrix[i][j]) * s;
		destQuat[k] = (srcMatrix[k][i] + srcMatrix[i][k]) * s;
		}
	}

void RotateAxis
	(
	float axis[ 3 ],
	float angle,
	float q[ 4 ]
	)

	{
	float sin_a;
	float inv_sin_a;
	float cos_a;
	float r;

	r = angle * M_PI / 360;
	
	sin_a = sin( r );
	if ( fabs( sin_a ) > 0.00000001 )
		{
		inv_sin_a = 1 / sin_a;
		}
	else
		{
		inv_sin_a = 0;
		}
	cos_a = cos( r );

	q[ X ] = axis[ 0 ] * inv_sin_a;
	q[ Y ] = axis[ 1 ] * inv_sin_a;
	q[ Z ] = axis[ 2 ] * inv_sin_a;
	q[ W ] = cos_a;
	}

void MultQuat
	(
	float q1[ 4 ],
	float q2[ 4 ],
	float out[ 4 ]
	)

	{
	out[ 0 ] = q1[X]*q2[X] - q1[Y]*q2[Y] - q1[Z]*q2[Z] - q1[W]*q2[W];
	out[ 1 ] = q1[X]*q2[Y] + q1[Y]*q2[X] + q1[Z]*q2[W] - q1[W]*q2[Z];
	out[ 2 ] = q1[X]*q2[Z] - q1[Y]*q2[W] + q1[Z]*q2[X] + q1[W]*q2[Y];
	out[ 3 ] = q1[X]*q2[W] + q1[Y]*q2[Z] - q1[Z]*q2[Y] + q1[W]*q2[X];
	}

void QuatToMat
	(
	float q[ 4 ],
	float m[ 3 ][ 3 ]
	)

	{
	float wx, wy, wz;
	float xx, yy, yz;
	float xy, xz, zz;
	float x2, y2, z2;

	x2 = q[ X ] + q[ X ];
	y2 = q[ Y ] + q[ Y ];
	z2 = q[ Z ] + q[ Z ];

	xx = q[ X ] * x2;
	xy = q[ X ] * y2;
	xz = q[ X ] * z2;

	yy = q[ Y ] * y2;
	yz = q[ Y ] * z2;
	zz = q[ Z ] * z2;

	wx = q[ W ] * x2;
	wy = q[ W ] * y2;
	wz = q[ W ] * z2;

	m[ 0 ][ 0 ] = 1.0 - ( yy + zz );
	m[ 0 ][ 1 ] = xy - wz;
	m[ 0 ][ 2 ] = xz + wy;

	m[ 1 ][ 0 ] = xy + wz;
	m[ 1 ][ 1 ] = 1.0 - ( xx + zz );
	m[ 1 ][ 2 ] = yz - wx;

	m[ 2 ][ 0 ] = xz - wy;
	m[ 2 ][ 1 ] = yz + wx;
	m[ 2 ][ 2 ] = 1.0 - ( xx + yy );
	}

#define DELTA 1e-6

void SlerpQuaternion
	(
	float from[ 4 ],
	float to[ 4 ],
	float t,
	float res[ 4 ]
	)

	{
	float		to1[ 4 ];
	double	omega, cosom, sinom, scale0, scale1;

	cosom = from[ X ] * to[ X ] + from[ Y ] * to[ Y ] + from[ Z ] * to[ Z ] + from[ W ] * to [ W ];
	if ( cosom < 0.0 )
		{
		cosom = -cosom;
		to1[ X ] = -to[ X ];
		to1[ Y ] = -to[ Y ];
		to1[ Z ] = -to[ Z ];
		to1[ W ] = -to[ W ];
		}
	else if 
      (
         ( from[ X ] == to[ X ] ) &&
         ( from[ Y ] == to[ Y ] ) &&
         ( from[ Z ] == to[ Z ] ) &&
         ( from[ W ] == to[ W ] ) 
      )
		{
      // equal case, early exit
	   res[ X ] = to[ X ];
	   res[ Y ] = to[ Y ];
	   res[ Z ] = to[ Z ];
	   res[ W ] = to[ W ];
      return;
      }
	else
		{
		to1[ X ] = to[ X ];
		to1[ Y ] = to[ Y ];
		to1[ Z ] = to[ Z ];
		to1[ W ] = to[ W ];
		}

	if ( ( 1.0 - cosom ) > DELTA )
		{
		omega = acos( cosom );
		sinom = sin( omega );
		scale0 = sin( ( 1.0 - t ) * omega ) / sinom;
		scale1 = sin( t * omega ) / sinom;
		}
	else
		{
		scale0 = 1.0 - t;
		scale1 = t;
		}

	res[ X ] = scale0 * from[ X ] + scale1 * to1[ X ];
	res[ Y ] = scale0 * from[ Y ] + scale1 * to1[ Y ];
	res[ Z ] = scale0 * from[ Z ] + scale1 * to1[ Z ];
	res[ W ] = scale0 * from[ W ] + scale1 * to1[ W ];
	}

void EulerToQuat
	(
	float ang[ 3 ],
	float q[ 4 ]
	)

	{
	float mat[ 3 ][ 3 ];
   int *i;

   i = ( int * )ang;
   if ( !i[ 0 ] && !i[ 1 ] && !i[ 2 ] )
      {
      q[ 0 ] = 0;
      q[ 1 ] = 0;
      q[ 2 ] = 0;
      q[ 3 ] = 1.0f;
      }
   else
      {
	   AnglesToAxis( ang, mat );
   	MatToQuat( mat, q );
      }
	}

/*
=====================
PlaneFromPoints

Returns false if the triangle is degenrate.
The normal will point out of the clock for clockwise ordered points
=====================
*/
qboolean PlaneFromPoints( vec4_t plane, const vec3_t a, const vec3_t b, const vec3_t c ) {
	vec3_t	d1, d2;

	VectorSubtract( b, a, d1 );
	VectorSubtract( c, a, d2 );
	CrossProduct( d2, d1, plane );
	if ( VectorNormalize( plane ) == 0 ) {
		return qfalse;
	}

	plane[3] = DotProduct( a, plane );
	return qtrue;
}

/*
=================
PlaneTypeForNormal
=================
*/
int	PlaneTypeForNormal (vec3_t normal) {
	if ( normal[0] == 1.0 )
		return PLANE_X;
	if ( normal[1] == 1.0 )
		return PLANE_Y;
	if ( normal[2] == 1.0 )
		return PLANE_Z;
	
	return PLANE_NON_AXIAL;
}



