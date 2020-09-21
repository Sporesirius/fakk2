//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/uvector3.h                       $
// $Revision:: 1                                                              $
//     $Date:: 9/21/99 2:24p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/uvector3.h                            $
// 
// 1     9/21/99 2:24p Jimdose
// 
// 9     9/17/99 4:12p Morbid
// Moved streaming to ustdstreams
// 
// 8     8/12/99 6:40p Morbid
// Streaming changes
// 
// 7     7/06/99 12:42p Morbid
// Various changes
// 
// 6     6/25/99 7:43p Morbid
// 
// 5     6/17/99 2:09p Morbid
// Lots of misc shit
// 
// 
// 4     5/28/99 6:58p Morbid
// Initial implementations
// 
// 3     5/28/99 3:11p Jimdose
// use type( x ) casts instead of static_cast<type>(x)
// 
// 2     5/27/99 8:40p Jimdose
// merged math and gui code
//
// DESCRIPTION:
// 

#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include "ucommon.h"

#define CROSS ^
#define DOT *

class UVector3
	{
   private:
      static const float LERP_DELTA;

   public:
      float		x;
		float		y;
		float		z;

      static const UVector3 origin;
      static const UVector3 zero;

								UVector3( void );
								UVector3( float x, float y, float z );
								UVector3( const char *text );
                        UVector3 ( const float *src );

					float		   *vec3( void );
               const float *vec3 ( void ) const;
               // Gets
               void     copyTo ( float * ) const;
					float		operator[]( int index ) const;

               // Sets
               float&	operator[]( int index );
					void 		setXYZ( float x, float y, float z );
                  
               // Operators

					void     operator=( const UVector3 &a );
					void     operator=( const float *a );
		friend	UVector3	operator+( const UVector3 &a, const UVector3 &b );
					UVector3&	operator+=( const UVector3 &a );
		friend	UVector3	operator-( const UVector3 &a, const UVector3 &b );
      friend   UVector3 operator- ( const UVector3 &a );
					UVector3&	operator-=( const UVector3 &a );
		friend	UVector3	operator*( const UVector3 &a, float b );
		friend	UVector3	operator*( float a, const UVector3 &b );
		friend	float		operator*( const UVector3 &a, const UVector3 &b );
					UVector3&	operator*=( float a );
		friend	bool		operator==(	const UVector3 &a, const UVector3 &b );
		friend	bool		operator!=(	const UVector3 &a, const UVector3 &b );
      friend   UVector3 operator ^ ( const UVector3 &a, const UVector3 &b );
					void  	CrossProduct( const UVector3 &a, const UVector3 &b );
					float		Length ( void ) const;
					void  	Normalize( void );
               UVector3 getNormalized ( void );
               void     ScaleAdd ( const UVector3 &mult, float by, const UVector3 &add );
               void     Scale ( const UVector3 &mult, float by );
               void     RotatePointAroundVector ( const UVector3 &dir, const UVector3 &point, float deg );
               void     MakePerp ( const UVector3 &to );
               UVector3 NormalOffOf ( const UVector3 &, const UVector3 & );

#if 0
//FIXME
// Some kind of compiler bug in VC++ prevents this from working.
// Returns result of ( -x, -y, -x ) for some reason
					UVector3&	operator-();
#endif
//		friend	UVector3	fabs( const UVector3 &a ) const;
					float		toYaw( void	);
					float		toPitch( void );
					UVector3	toAngles( void );	
		         void  	LerpVector( UVector3 w1, UVector3 w2, float t );
		friend	float		MaxValue( UVector3 a );
	};

// Simple inlines...  One liners
inline UVector3::UVector3 ()                               { } // Do nothing
inline UVector3::UVector3 ( const float *src )             { x = src[0]; y = src[1]; z = src[2]; }
inline UVector3::UVector3 ( float xx, float yy, float zz ) { setXYZ ( xx, yy, zz ); }

inline void   UVector3::copyTo ( float *vec ) const             { vec[0] = x; vec[1] = y; vec[2] = z; }
inline void   UVector3::setXYZ ( float xx, float yy, float zz ) { x = xx; y = yy; z = zz; }
inline float *UVector3::vec3   ()                               { return &x; }
inline const float *UVector3::vec3 () const                     { return &x; }

inline void      UVector3::operator =  ( const UVector3 &a ) { x = a.x;  y = a.y;  z = a.z;                }
inline void      UVector3::operator =  ( const float *a )    { x = a[0]; y = a[1]; z = a[2];               }
inline UVector3 &UVector3::operator += ( const UVector3 &a ) { x += a.x; y += a.y; z += a.z; return *this; }
inline UVector3 &UVector3::operator -= ( const UVector3 &a ) { x -= a.x; y -= a.y; z -= a.z; return *this; }
inline UVector3            operator -  ( const UVector3 &a ) { UVector3 v; v.x = -a.x; v.y = -a.y; v.z = -a.z; return v; }

inline float UVector3::operator[]
	( 
	int index 
	) const

	{
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &x )[ index ];
	}

inline float& UVector3::operator[]
	( 
	int index 
	)

	{
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &x )[ index ];
	}

inline UVector3::UVector3
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

inline UVector3 operator+
	(
	const UVector3 &a,
	const UVector3 &b
	)

	{
	return UVector3( a.x + b.x, a.y + b.y, a.z + b.z );
	}

inline UVector3 operator-
	(
	const UVector3 &a,
	const UVector3 &b
	)

	{
	return UVector3( a.x - b.x, a.y - b.y, a.z - b.z );
	}

inline UVector3 operator*
	(
	const UVector3 &a,
	float b
	)

	{
	return UVector3( a.x * b, a.y * b, a.z * b );
	}

inline UVector3 operator*
	(
	float a,
	const UVector3 &b
	)

	{
	return b * a;
	}

inline float operator*
	(
	const UVector3 &a,
	const UVector3 &b
	)

	{
	return a.x * b.x + a.y * b.y + a.z * b.z;
	}

inline UVector3& UVector3::operator*=
	(
	float a
	)

	{
	x *= a;
	y *= a;
	z *= a;

	return *this;
	}

inline bool operator==
	(
	const UVector3 &a,
	const UVector3 &b
	)

	{
	return ( ( a.x == b.x ) && ( a.y == b.y ) && ( a.z == b.z ) );
	}

inline bool operator!=
	(
	const UVector3 &a,
	const UVector3 &b
	)

	{
	return ( ( a.x != b.x ) || ( a.y != b.y ) || ( a.z != b.z ) );
	}

inline UVector3 UVector3::NormalOffOf 
   ( 
   const UVector3 &a, 
   const UVector3 &b 
   )

   {
   UVector3 a1 = a;
   UVector3 b1 = b;
   UVector3 cross;

   a1 -= *this;
   b1 -= *this;

   a1.Normalize ();
   b1.Normalize ();
   
   cross.CrossProduct ( a1, b1 );
   cross.Normalize ();

   return cross;
   }


inline void UVector3::CrossProduct
	(
	const UVector3 &a,
	const UVector3 &b
	)

	{
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
	}

inline UVector3 operator ^
   (
	const UVector3 &a,
	const UVector3 &b
	)

	{
   UVector3 u;

   u.CrossProduct ( a, b );
   return u;
   }   

inline float UVector3::Length
	(
	void
	) const
	
	{
	float	length;
	
	length = x * x + y * y + z * z;
	return float( sqrt( length ) );
	}

inline void UVector3::Normalize
	(
	void
	)

	{
	float	length, ilength;

   length = Length();
	if ( length )
		{
		ilength = 1 / length;
		x *= ilength;
		y *= ilength;
		z *= ilength;
		}
   else
      {
      x = y = z = 0;
      }
	}

inline UVector3 UVector3::getNormalized 
   (
   void
   )
   
   {
   UVector3 v = *this;

   v.Normalize ();
   return v;
   }

#if 0
//FIXME
// Some kind of compiler bug in VC++ prevents this from working.
// Returns result of ( -x, -y, -x ) for some reason
inline UVector3& UVector3::operator-()
	{
	return UVector3( -x, -y, -z );
	}
#endif

inline UVector3 fabs
	( 
	UVector3 a 
	)

	{
	return UVector3( Fabs( a.x ), Fabs( a.y ), Fabs( a.z ) );
	}

inline float MaxValue
	( 
	UVector3 a 
	)

	{
   float maxy;
   float maxz;
   float max;

   max = Fabs( a.x );
   maxy = Fabs( a.y );
   maxz = Fabs( a.z );
   if ( maxy > max )
      max = maxy;
   if ( maxz > max )
      max = maxz;
	return max;
	}

inline void UVector3::ScaleAdd ( 
                               const UVector3 &mult, 
                               float by, 
                               const UVector3 &add 
                               ) 
{
   x = mult.x * by + add.x;
   y = mult.y * by + add.y;
   z = mult.z * by + add.z;
}

inline void UVector3::Scale (
                             const UVector3 &mult,
                             float by 
                             ) 
   {
   x = mult.x * by;
   y = mult.y * by;
   z = mult.z * by;
   }

#endif /* UVector3.h */
