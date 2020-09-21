//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/fgame/vector.h                           $
// $Revision:: 12                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 3/13/00 7:15p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/fgame/vector.h                                $
// 
// 12    3/13/00 7:15p Jimdose
// made normalize return the length
// 
// 11    1/24/00 7:53p Jimdose
// removed vec3
// 
// 10    1/22/00 12:28p Jimdose
// added vec3_t conversions for FuzzyEqual and CrossProduct
// 
// 9     1/22/00 12:19p Jimdose
// added some missing cases for vec3_t conversion
// 
// 8     1/22/00 12:13p Jimdose
// added vec3_t conversions so that .vec3() is no longer needed
// 
// 7     1/21/00 7:32p Markd
// Put in fuzzy equal support into script variables
// 
// 6     1/05/00 6:39p Jimdose
// AngleVectors now returns left instead of right.
// 
// 5     1/05/00 5:29p Jimdose
// made toAngles consitant with vectoangles
// 
// 4     12/10/99 11:16a Jimdose
// made right and up optional in AngleVectors
// 
// 3     10/05/99 2:03p Markd
// Added warning about files being in multiple projects
// 
// 2     9/28/99 4:26p Markd
// merged listener, class and vector between 3 projects
// 
// 1     9/10/99 10:55a Jimdose
// 
// 1     9/08/99 3:16p Aldie
// 
// 4     8/28/99 3:40p Jimdose
// changed all doubles to floats
// 
// DESCRIPTION:
// C++ implemention of a Vector object.  Handles standard vector operations
// such as addition, subtraction, normalization, scaling, dot product,
// cross product, length, and decomposition into Euler angles.
//
// WARNING: This file is shared between fgame, cgame and possibly the user interface.
// It is instanced in each one of these directories because of the way that SourceSafe works.
// 

#ifndef __VECTOR_H__
#define __VECTOR_H__

#ifdef GAME_DLL
#include "g_local.h"
#endif

#include <math.h>
#include <stdio.h>

#ifdef __Q_FABS__
#define VECTOR_FABS  Q_fabs
#else
#define VECTOR_FABS  fabs
#endif

class Vector
	{
	public:
		float		x;
		float		y;
		float		z;

								Vector();
								Vector( vec3_t src );
								Vector( float x, float y, float z );
								Vector( const char *text );

                        operator float * ();

					float		pitch( void );
					float		yaw( void );
					float		roll( void );
					float		operator[]( int index ) const;
					float&	operator[]( int index );
					void 		copyTo( vec3_t vec );
					void		setPitch( float x );
					void 		setYaw( float y );
					void 		setRoll( float z );
					void 		setXYZ( float x, float y, float z );
					void		operator=( Vector a );
					void		operator=( vec3_t a );
		friend	Vector	operator+( Vector a, Vector b );
		friend	Vector	operator+( vec3_t a, Vector b );
		friend	Vector	operator+( Vector a, vec3_t b );
					Vector&	operator+=( Vector a );
		friend	Vector	operator-( Vector a, Vector b );
		friend	Vector	operator-( vec3_t a, Vector b );
		friend	Vector	operator-( Vector a, vec3_t b );
					Vector&	operator-=( Vector a );
		friend	Vector	operator*( Vector a, float b );
		friend	Vector	operator*( float a, Vector b );
		friend	float		operator*( Vector a, Vector b );
      friend	float		operator*( vec3_t a, Vector b );
		friend	float		operator*( Vector a, vec3_t b );
					Vector&	operator*=( float a );
		friend	int		operator==(	Vector a, Vector b );
      friend	int		operator==(	vec3_t a, Vector b );
      friend	int		operator==(	Vector a, vec3_t b );
		friend	int		operator!=(	Vector a, Vector b );
      friend	int		operator!=(	vec3_t a, Vector b );
		friend	int		operator!=(	Vector a, vec3_t b );
              	int		FuzzyEqual( Vector b, float epsilon );
              	int		FuzzyEqual( vec3_t b, float epsilon );
					Vector&	CrossProduct( Vector a, Vector b	);
					Vector&	CrossProduct( vec3_t a, Vector b	);
					Vector&	CrossProduct( Vector a, vec3_t b	);
					float		length( void );
					float    normalize( void );
#if 0
//FIXME
// Some kind of compiler bug in VC++ prevents this from working.
// Returns result of ( -x, -y, -x ) for some reason
					Vector&	operator-();
#endif
		friend	Vector	fabs( Vector a );
					float		toYaw( void	);
					float		toPitch( void );
					Vector	toAngles( void );	
					void		AngleVectors( Vector *forward, Vector *left = NULL, Vector *up = NULL );
		friend	Vector	LerpVector( Vector w1, Vector w2, float t );
		friend	float		MaxValue( Vector a );
	};

inline float Vector::pitch( void )					{ return x; }
inline float Vector::yaw( void )						{ return y; }
inline float Vector::roll( void )					{ return z; }
inline void  Vector::setPitch( float pitch )	   { x = pitch; }
inline void  Vector::setYaw( float yaw )			{ y = yaw; }
inline void  Vector::setRoll( float roll )		{ z = roll; }

inline void Vector::copyTo
	(
	vec3_t vec
	)

	{
	vec[ 0 ] = x;
	vec[ 1 ] = y;
	vec[ 2 ] = z;
	}

inline float Vector::operator[]
	( 
	int index 
	) const

	{
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &x )[ index ];
	}

inline float& Vector::operator[]
	( 
	int index 
	)

	{
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &x )[ index ];
	}

inline void  Vector::setXYZ
	( 
	float x,
	float y,
	float z 
	) 
	
	{
	this->x = x;
	this->y = y;
	this->z = z;
	}

inline Vector::Vector()
	{
	x = 0;
	y = 0;
	z = 0;
	}

inline Vector::Vector
	( 
	vec3_t src 
	)

	{
	x = src[ 0 ];
	y = src[ 1 ];
	z = src[ 2 ];
	}

inline Vector::Vector
	( 
	float x,
	float y,
	float z
	)

	{
	this->x = x;
	this->y = y;
	this->z = z;
	}

inline Vector::Vector
	(
	const char *text
	)

	{
	if ( text )
		{
		sscanf( text, "%f %f %f", &x, &y, &z );
		}
	else
		{
		x = 0;
		y = 0;
		z = 0;
		}
	}

inline Vector::operator float *
   (
   void
   )

   {
   return &x;
   }

inline void Vector::operator=
	(
	Vector a
	)

	{
	x = a.x;
	y = a.y;
	z = a.z;
	}

inline void Vector::operator=
	(
	vec3_t a
	)

	{
	x = a[ 0 ];
	y = a[ 1 ];
	z = a[ 2 ];
	}

inline Vector operator+
	(
	Vector a,
	Vector b
	)

	{
	return Vector( a.x + b.x, a.y + b.y, a.z + b.z );
	}

inline Vector operator+
	(
	vec3_t a,
	Vector b
	)

	{
	return Vector( a[ 0 ] + b.x, a[ 1 ] + b.y, a[ 2 ] + b.z );
	}

inline Vector operator+
	(
	Vector a,
	vec3_t b
	)

	{
	return Vector( a.x + b[ 0 ], a.y + b[ 1 ], a.z + b[ 2 ] );
	}

inline Vector& Vector::operator+=
	(
	Vector a
	)

	{
	x += a.x;
	y += a.y;
	z += a.z;

	return *this;
	}

inline Vector operator-
	(
	Vector a,
	Vector b
	)

	{
	return Vector( a.x - b.x, a.y - b.y, a.z - b.z );
	}

inline Vector operator-
	(
	vec3_t a,
	Vector b
	)

	{
	return Vector( a[ 0 ] - b.x, a[ 1 ] - b.y, a[ 2 ] - b.z );
	}

inline Vector operator-
	(
	Vector a,
	vec3_t b
	)

	{
	return Vector( a.x - b[ 0 ], a.y - b[ 1 ], a.z - b[ 2 ] );
	}

inline Vector& Vector::operator-=
	(
	Vector a
	)

	{
	x -= a.x;
	y -= a.y;
	z -= a.z;

	return *this;
	}

inline Vector operator*
	(
	Vector a,
	float b
	)

	{
	return Vector( a.x * b, a.y * b, a.z * b );
	}

inline Vector operator*
	(
	float a,
	Vector b
	)

	{
	return b * a;
	}

inline float operator*
	(
	Vector a,
	Vector b
	)

	{
	return a.x * b.x + a.y * b.y + a.z * b.z;
	}

inline float operator*
	(
	vec3_t a,
	Vector b
	)

	{
	return a[ 0 ] * b.x + a[ 1 ] * b.y + a[ 2 ] * b.z;
	}

inline float operator*
	(
	Vector a,
	vec3_t b
	)

	{
	return a.x * b[ 0 ] + a.y * b[ 1 ] + a.z * b[ 2 ];
	}

inline Vector& Vector::operator*=
	(
	float a
	)

	{
	x *= a;
	y *= a;
	z *= a;

	return *this;
	}

inline int Vector::FuzzyEqual
	(
	Vector b,
   float epsilon
	)

   {
   return
      ( 
         ( VECTOR_FABS( x - b.x ) < epsilon ) &&
         ( VECTOR_FABS( y - b.y ) < epsilon ) &&
         ( VECTOR_FABS( z - b.z ) < epsilon )
      );
	}

inline int Vector::FuzzyEqual
	(
	vec3_t b,
   float epsilon
	)

   {
   return
      ( 
         ( VECTOR_FABS( x - b[ 0 ] ) < epsilon ) &&
         ( VECTOR_FABS( y - b[ 1 ] ) < epsilon ) &&
         ( VECTOR_FABS( z - b[ 2 ] ) < epsilon )
      );
	}

inline int operator==
	(
	Vector a,
	Vector b
	)

	{
	return ( ( a.x == b.x ) && ( a.y == b.y ) && ( a.z == b.z ) );
	}

inline int operator==
	(
	vec3_t a,
	Vector b
	)

	{
	return ( ( a[ 0 ] == b.x ) && ( a[ 1 ] == b.y ) && ( a[ 2 ] == b.z ) );
	}

inline int operator==
	(
	Vector a,
	vec3_t b
	)

	{
	return ( ( a.x == b[ 0 ] ) && ( a.y == b[ 1 ] ) && ( a.z == b[ 2 ] ) );
	}

inline int operator!=
	(
	Vector a,
	Vector b
	)

	{
	return ( ( a.x != b.x ) || ( a.y != b.y ) || ( a.z != b.z ) );
	}

inline int operator!=
	(
	vec3_t a,
	Vector b
	)

	{
	return ( ( a[ 0 ] != b.x ) || ( a[ 1 ] != b.y ) || ( a[ 2 ] != b.z ) );
	}

inline int operator!=
	(
	Vector a,
	vec3_t b
	)

	{
	return ( ( a.x != b[ 0 ] ) || ( a.y != b[ 1 ] ) || ( a.z != b[ 2 ] ) );
	}

inline Vector& Vector::CrossProduct
	(
	Vector a,
	Vector b
	)

	{
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;

	return *this;
	}

inline Vector& Vector::CrossProduct
	(
	vec3_t a,
	Vector b
	)

	{
	x = a[ 1 ] * b.z - a[ 2 ] * b.y;
	y = a[ 2 ] * b.x - a[ 0 ] * b.z;
	z = a[ 0 ] * b.y - a[ 1 ] * b.x;

	return *this;
	}

inline Vector& Vector::CrossProduct
	(
	Vector a,
	vec3_t b
	)

	{
	x = a.y * b[ 2 ] - a.z * b[ 1 ];
	y = a.z * b[ 0 ] - a.x * b[ 2 ];
	z = a.x * b[ 1 ] - a.y * b[ 0 ];

	return *this;
	}

inline float Vector::length
	(
	void
	)
	
	{
	float	length;
	
	length = x * x + y * y + z * z;
	return ( float )sqrt( length );
	}

inline float Vector::normalize
	(
	void
	)

	{
	float	length, ilength;

	length = this->length();
	if ( length )
		{
		ilength = 1 / length;
		x *= ilength;
		y *= ilength;
		z *= ilength;
		}
		
	return length;
	}

#if 0
//FIXME
// Some kind of compiler bug in VC++ prevents this from working.
// Returns result of ( -x, -y, -x ) for some reason
inline Vector& Vector::operator-()
	{
	return Vector( -x, -y, -z );
	}
#endif

inline Vector fabs
	( 
	Vector a 
	)

	{
   return Vector( VECTOR_FABS( a.x ), VECTOR_FABS( a.y ), VECTOR_FABS( a.z ) );
	}

inline float MaxValue
	( 
	Vector a 
	)

	{
   float maxy;
   float maxz;
   float max;

   max = VECTOR_FABS( a.x );
   maxy = VECTOR_FABS( a.y );
   maxz = VECTOR_FABS( a.z );

   if ( maxy > max )
      {
      max = maxy;
      }
   if ( maxz > max )
      {
      max = maxz;
      }
	return max;
	}

inline float Vector::toYaw
	(
	void
	)
	
	{
	float yaw;
	
	if ( ( y == 0 ) && ( x == 0 ) )
		{
		yaw = 0;
		}
	else
		{
		yaw = ( float )( ( int )( atan2( y, x ) * 180 / M_PI ) );
		if ( yaw < 0 )
			{
			yaw += 360;
			}
		}

	return yaw;
	}

inline float Vector::toPitch
	(
	void
	)

	{
	float	forward;
	float	pitch;
	
	if ( ( x == 0 ) && ( y == 0 ) )
		{
		if ( z > 0 )
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
		forward = ( float )sqrt( x * x + y * y );
		pitch = ( float )( ( int )( atan2( z, forward ) * 180 / M_PI ) );
		if ( pitch < 0 )
			{
			pitch += 360;
			}
		}

	return pitch;
	}

inline Vector Vector::toAngles
	(
	void
	)

	{
	float	forward;
	float	yaw, pitch;
	
	if ( ( x == 0 ) && ( y == 0 ) )
		{
		yaw = 0;
		if ( z > 0 )
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
		yaw = atan2( y, x ) * 180 / M_PI;
		if ( yaw < 0 )
			{
			yaw += 360;
			}

		forward = ( float )sqrt( x * x + y * y );
		pitch = atan2( z, forward ) * 180 / M_PI;
		if ( pitch < 0 )
			{
			pitch += 360;
			}
		}

	return Vector( -pitch, yaw, 0 );
	}

inline void Vector::AngleVectors
	(
	Vector *forward,
	Vector *left,
	Vector *up
	)

	{
	float				angle;
	static float	sr, sp, sy, cr, cp, cy; // static to help MS compiler fp bugs
	
	angle = yaw() * ( M_PI * 2 / 360 );
	sy = sin( angle );
	cy = cos( angle );

	angle = pitch() * ( M_PI * 2 / 360 );
	sp = sin( angle );
	cp = cos( angle );

	angle = roll() * ( M_PI * 2 / 360 );
	sr = sin( angle );
	cr = cos( angle );

	if ( forward )
		{
		forward->setXYZ( cp * cy, cp * sy, -sp );
		}

	if ( left )
		{
		left->setXYZ( sr * sp * cy + cr * -sy, sr * sp * sy + cr * cy, sr * cp );
		}

	if ( up )
		{
		up->setXYZ( cr * sp * cy + -sr * -sy, cr * sp * sy + -sr * cy, cr * cp );
		}
	}


#define LERP_DELTA 1e-6
inline Vector LerpVector
	(
   Vector w1,
   Vector w2,
   float t
	)
   {
	float	omega, cosom, sinom, scale0, scale1;

	w1.normalize();
	w2.normalize();

	cosom = w1 * w2;
	if ( ( 1.0 - cosom ) > LERP_DELTA )
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

	return ( w1 * scale0 + w2 * scale1 );
   }

class Quat
	{
	public:
		float		x;
		float		y;
		float		z;
      float    w;

								Quat();
								Quat( Vector angles );
								Quat( float scrMatrix[ 3 ][ 3 ] );
								Quat( float x, float y, float z, float w );

					float		*vec4( void );
					float		operator[]( int index ) const;
					float&	operator[]( int index );
					void 		set( float x, float y, float z, float w );
					void		operator=( Quat a );
		friend	Quat	   operator+( Quat a, Quat b );
					Quat&	   operator+=( Quat a );
		friend	Quat	   operator-( Quat a, Quat b );
					Quat&	   operator-=( Quat a );
		friend	Quat	   operator*( Quat a, float b );
		friend	Quat	   operator*( float a, Quat b );
					Quat&	   operator*=( float a );
		friend	int		operator==(	Quat a, Quat b );
		friend	int		operator!=(	Quat a, Quat b );
					float		length( void );
					Quat&	   normalize( void );
					Quat	   operator-();
					Vector   toAngles( void );	
	};

inline float Quat::operator[]
	( 
	int index 
	) const

	{
	assert( ( index >= 0 ) && ( index < 4 ) );
	return ( &x )[ index ];
	}

inline float& Quat::operator[]
	( 
	int index 
	)

	{
	assert( ( index >= 0 ) && ( index < 4 ) );
	return ( &x )[ index ];
	}

inline float *Quat::vec4
	( 
	void
	)

	{
	return &x;
	}

inline void  Quat::set
	( 
	float x,
	float y,
	float z,
   float w
	) 
	
	{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	}

inline Quat::Quat()
	{
	x = 0;
	y = 0;
	z = 0;
   w = 0;
	}

inline Quat::Quat
	( 
   Vector Angles
	)

	{
   EulerToQuat( Angles, this->vec4() );
	}

inline Quat::Quat
	( 
   float srcMatrix[ 3 ][ 3 ]
	)

	{
   MatToQuat( srcMatrix, this->vec4() );
	}

inline Quat::Quat
	( 
	float x,
	float y,
	float z,
   float w
	)

	{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	}

inline void Quat::operator=
	(
	Quat a
	)

	{
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;
	}

inline Quat operator+
	(
	Quat a,
	Quat b
	)

	{
	return Quat( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w );
	}

inline Quat& Quat::operator+=
	(
	Quat a
	)

	{
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
	}

inline Quat operator-
	(
	Quat a,
	Quat b
	)

	{
	return Quat( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w );
	}

inline Quat& Quat::operator-=
	(
	Quat a
	)

	{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
	}

inline Quat operator*
	(
	Quat a,
	float b
	)

	{
	return Quat( a.x * b, a.y * b, a.z * b, a.w * b );
	}

inline Quat operator*
	(
	float a,
	Quat b
	)

	{
	return b * a;
	}

inline Quat& Quat::operator*=
	(
	float a
	)

	{
	x *= a;
	y *= a;
	z *= a;
	w *= a;

	return *this;
	}

inline int operator==
	(
	Quat a,
	Quat b
	)

	{
	return ( ( a.x == b.x ) && ( a.y == b.y ) && ( a.z == b.z ) && ( a.w == b.w ) );
	}

inline int operator!=
	(
	Quat a,
	Quat b
	)

	{
	return ( ( a.x != b.x ) || ( a.y != b.y ) || ( a.z != b.z ) && ( a.w != b.w ) );
	}

inline float Quat::length
	(
	void
	)
	
	{
	float	length;
	
	length = x * x + y * y + z * z + w * w;
	return ( float )sqrt( length );
	}

inline Quat& Quat::normalize
	(
	void
	)

	{
	float	length, ilength;

	length = this->length();
	if ( length )
		{
		ilength = 1 / length;
		x *= ilength;
		y *= ilength;
		z *= ilength;
		w *= ilength;
		}
		
	return *this;
	}

inline Quat Quat::operator-()
	{
	return Quat( -x, -y, -z, -w );
	}

inline Vector Quat::toAngles
	(
	void
	)

	{
   float m[ 3 ][ 3 ];
   vec3_t angles;

   QuatToMat( this->vec4(), m );
   MatrixToEulerAngles( m, angles );
   return Vector( angles );
	}

extern Vector vec_zero;

#undef VECTOR_FABS

#endif /* Vector.h */
