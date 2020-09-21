//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/fakk2_new/cgame/cg_vector.h                        $
// $Revision:: 1                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 9/10/99 2:46p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/fakk2_new/cgame/cg_vector.h                             $
// 
// 1     9/10/99 2:46p Aldie
// 
// 1     9/09/99 5:06p Aldie
// 
// DESCRIPTION:
// C++ implemention of a Vector object.  Handles standard vector operations
// such as addition, subtraction, normalization, scaling, dot product,
// cross product, length, and decomposition into Euler angles.
// 

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>
#include <stdio.h>

class Vector
	{
	public:
		float		x;
		float		y;
		float		z;

								Vector();
								Vector( vec3_t src );
								Vector( double x, double y, double z );
								Vector( const char *text );

					float		*vec3( void );
					float		pitch( void );
					float		yaw( void );
					float		roll( void );
					float		operator[]( int index ) const;
					float&	operator[]( int index );
					void 		copyTo( vec3_t vec );
					void		setPitch( double x );
					void 		setYaw( double y );
					void 		setRoll( double z );
					void 		setXYZ( double x, double y, double z );
					void		operator=( Vector a );
					void		operator=( vec3_t a );
		friend	Vector	operator+( Vector a, Vector b );
					Vector&	operator+=( Vector a );
		friend	Vector	operator-( Vector a, Vector b );
					Vector&	operator-=( Vector a );
		friend	Vector	operator*( Vector a, double b );
		friend	Vector	operator*( double a, Vector b );
		friend	float		operator*( Vector a, Vector b );
					Vector&	operator*=( double a );
		friend	int		operator==(	Vector a, Vector b );
		friend	int		operator!=(	Vector a, Vector b );
					Vector&	CrossProduct( Vector a, Vector b	);
					float		length( void );
					Vector&	normalize( void );
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
					void		AngleVectors( Vector *forward, Vector *right, Vector *up );
		friend	Vector	LerpVector( Vector w1, Vector w2, float t );
		friend	float		MaxValue( Vector a );
	};

inline float Vector::pitch( void )					{ return x; }
inline float Vector::yaw( void )						{ return y; }
inline float Vector::roll( void )					{ return z; }
inline void  Vector::setPitch( double pitch )	{ x = ( float )pitch; }
inline void  Vector::setYaw( double yaw )			{ y = ( float )yaw; }
inline void  Vector::setRoll( double roll )		{ z = ( float )roll; }

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
	double x,
	double y,
	double z 
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
	double x,
	double y,
	double z
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

inline float *Vector::vec3
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
	double b
	)

	{
	return Vector( a.x * b, a.y * b, a.z * b );
	}

inline Vector operator*
	(
	double a,
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

inline Vector& Vector::operator*=
	(
	double a
	)

	{
	x *= a;
	y *= a;
	z *= a;

	return *this;
	}

inline int operator==
	(
	Vector a,
	Vector b
	)

	{
	return ( ( a.x == b.x ) && ( a.y == b.y ) && ( a.z == b.z ) );
	}

inline int operator!=
	(
	Vector a,
	Vector b
	)

	{
	return ( ( a.x != b.x ) || ( a.y != b.y ) || ( a.z != b.z ) );
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

inline float Vector::length
	(
	void
	)
	
	{
	float	length;
	
	length = x * x + y * y + z * z;
	return ( float )sqrt( length );
	}

inline Vector& Vector::normalize
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
		
	return *this;
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
	return Vector( fabs( a.x ), fabs( a.y ), fabs( a.z ) );
	}

inline float MaxValue
	( 
	Vector a 
	)

	{
   float maxy;
   float maxz;
   float max;

   max = fabs( a.x );
   maxy = fabs( a.y );
   maxz = fabs( a.z );
   if ( maxy > max )
      max = maxy;
   if ( maxz > max )
      max = maxz;
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

	return Vector( pitch, yaw, 0 );
	}

inline void Vector::AngleVectors
	(
	Vector *forward,
	Vector *right,
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

	if ( right )
		{
		right->setXYZ( -1 * sr * sp * cy + -1 * cr * -sy, -1 * sr * sp * sy + -1 * cr * cy,	-1 * sr * cp );
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
	double	omega, cosom, sinom, scale0, scale1;

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
								Quat( double x, double y, double z, double w );

					float		*vec4( void );
					float		operator[]( int index ) const;
					float&	operator[]( int index );
					void 		set( double x, double y, double z, double w );
					void		operator=( Quat a );
		friend	Quat	   operator+( Quat a, Quat b );
					Quat&	   operator+=( Quat a );
		friend	Quat	   operator-( Quat a, Quat b );
					Quat&	   operator-=( Quat a );
		friend	Quat	   operator*( Quat a, double b );
		friend	Quat	   operator*( double a, Quat b );
					Quat&	   operator*=( double a );
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
	double x,
	double y,
	double z,
   double w
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
   EulerToQuat( Angles.vec3(), this->vec4() );
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
	double x,
	double y,
	double z,
   double w
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
	double b
	)

	{
	return Quat( a.x * b, a.y * b, a.z * b, a.w * b );
	}

inline Quat operator*
	(
	double a,
	Quat b
	)

	{
	return b * a;
	}

inline Quat& Quat::operator*=
	(
	double a
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
#endif /* Vector.h */
