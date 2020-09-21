// mathlib.c -- math primitives

#include "cmdlib.h"
#include "mathlib.h"

#ifdef _WIN32
//Improve floating-point consistency.
//without this option weird floating point issues occur
#pragma optimize( "p", on )
#endif

vec3_t vec3_origin = {0,0,0};



/*
** NormalToLatLong
**
** We use two byte encoded normals in some space critical applications.
** Lat = 0 at (1,0,0) to 360 (-1,0,0), encoded in 8-bit sine table format
** Lng = 0 at (0,0,1) to 180 (0,0,-1), encoded in 8-bit sine table format
**
*/
void NormalToLatLong( const vec3_t normal, byte bytes[2] ) {
	// check for singularities
	if ( normal[0] == 0 && normal[1] == 0 ) {
		if ( normal[2] > 0 ) {
			bytes[0] = 0;
			bytes[1] = 0;		// lat = 0, long = 0
		} else {
			bytes[0] = 128;
			bytes[1] = 0;		// lat = 0, long = 128
		}
	} else {
		int	a, b;

		a = RAD2DEG( atan2( normal[1], normal[0] ) ) * (255.0f / 360.0f );
		a &= 0xff;

		b = RAD2DEG( acos( normal[2] ) ) * ( 255.0f / 360.0f );
		b &= 0xff;

		bytes[0] = b;	// longitude
		bytes[1] = a;	// lattitude
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
	if ( VectorNormalize( plane, plane ) == 0 ) {
		return qfalse;
	}

	plane[3] = DotProduct( a, plane );
	return qtrue;
}

/*
================
MakeNormalVectors

Given a normalized forward vector, create two
other perpendicular vectors
================
*/
void MakeNormalVectors (vec3_t forward, vec3_t right, vec3_t up)
{
	float		d;

	// this rotate and negate guarantees a vector
	// not colinear with the original
	right[1] = -forward[0];
	right[2] = forward[1];
	right[0] = forward[2];

	d = DotProduct (right, forward);
	VectorMA (right, -d, forward, right);
	VectorNormalize (right, right);
	CrossProduct (right, forward, up);
}


void Vec10Copy( vec_t *in, vec_t *out ) {
	out[0] = in[0];
	out[1] = in[1];
	out[2] = in[2];
	out[3] = in[3];
	out[4] = in[4];
	out[5] = in[5];
	out[6] = in[6];
	out[7] = in[7];
	out[8] = in[8];
	out[9] = in[9];
}


void VectorRotate3x3( vec3_t v, float r[3][3], vec3_t d )
{
	d[0] = v[0] * r[0][0] + v[1] * r[1][0] + v[2] * r[2][0];
	d[1] = v[0] * r[0][1] + v[1] * r[1][1] + v[2] * r[2][1];
	d[2] = v[0] * r[0][2] + v[1] * r[1][2] + v[2] * r[2][2];
}

double VectorLength( const vec3_t v ) {
	int		i;
	double	length;

	length = 0;
	for (i=0 ; i< 3 ; i++)
		length += v[i]*v[i];
	length = sqrt (length);		// FIXME

	return length;
}

qboolean VectorCompare( const vec3_t v1, const vec3_t v2 ) {
	int		i;

	for (i=0 ; i<3 ; i++)
		if (fabs(v1[i]-v2[i]) > EQUAL_EPSILON)
			return qfalse;

	return qtrue;
}

vec_t Q_rint (vec_t in)
{
	return floor (in + 0.5);
}

void VectorMA( const vec3_t va, double scale, const vec3_t vb, vec3_t vc ) {
	vc[0] = va[0] + scale*vb[0];
	vc[1] = va[1] + scale*vb[1];
	vc[2] = va[2] + scale*vb[2];
}

void CrossProduct( const vec3_t v1, const vec3_t v2, vec3_t cross ) {
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

vec_t VectorNormalize( const vec3_t in, vec3_t out ) {
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

vec_t ColorNormalize( const vec3_t in, vec3_t out ) {
	float	max, scale;

	max = in[0];
	if (in[1] > max)
		max = in[1];
	if (in[2] > max)
		max = in[2];

	if (max == 0) {
		out[0] = out[1] = out[2] = 1.0;
		return 0;
	}

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

void AngleVectors( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up)
{
   float    angle;
   static float      sr, sp, sy, cr, cp, cy;
   // static to help MS compiler fp bugs

   angle = angles[YAW] * (Q_PI*2 / 360);
   sy = sin(angle);
   cy = cos(angle);
   angle = angles[PITCH] * (Q_PI*2 / 360);
   sp = sin(angle);
   cp = cos(angle);
   angle = angles[ROLL] * (Q_PI*2 / 360);
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
      right[0] = (-1*sr*sp*cy+-1*cr*-sy);
      right[1] = (-1*sr*sp*sy+-1*cr*cy);
      right[2] = -1*sr*cp;
   }
   if (up)
   {
      up[0] = (cr*sp*cy+-sr*-sy);
      up[1] = (cr*sp*sy+-sr*cy);
      up[2] = cr*cp;
   }
}

/*
=================
PlaneTypeForNormal
=================
*/
int	PlaneTypeForNormal (vec3_t normal) {
	if (normal[0] == 1.0 || normal[0] == -1.0)
		return PLANE_X;
	if (normal[1] == 1.0 || normal[1] == -1.0)
		return PLANE_Y;
	if (normal[2] == 1.0 || normal[2] == -1.0)
		return PLANE_Z;
	
	return PLANE_NON_AXIAL;
}

