//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/uquat.h                          $
// $Revision:: 2                                                              $
//     $Date:: 10/04/99 7:04p                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/uquat.h                               $
// 
// 2     10/04/99 7:04p Jimdose
// added ProjectVector and UnprojectVector
// 
// 5     9/15/99 5:38p Morbid
// Added header
//
// DESCRIPTION:
// 

#ifndef __UQUAT_H__
#define __UQUAT_H__

#include "ucommon.h"
#include "uvector3.h"

class UMat3;
class UEuler;

class UQuat 
   {
   public:
      float 
         x, y, z, w;

      UQuat ();
      UQuat ( float xx, float yy, float zz, float ww );
      UQuat ( const UVector3 &, float ww = 0.f );
      UQuat ( const UEuler & );

      void set ( float xx, float yy, float zz, float ww );

      UVector3 &vec3 ();

      float *vec4 ();
      float operator[] ( int index ) const;
      float &operator[] ( int index );

      friend UQuat operator + ( const UQuat &, const UQuat & );
      friend UQuat operator - ( const UQuat &, const UQuat & );
      friend UQuat operator * ( const UQuat &, float );
      friend UQuat operator * ( float, const UQuat & );
      friend UQuat operator * ( const UQuat &, const UQuat & );
      inline friend UQuat operator * ( float a, UQuat &b ) { return b * a; }

      UQuat &operator += ( const UQuat & );
      UQuat &operator -= ( const UQuat & );
      UQuat &operator *= ( float );
      UQuat &operator *= ( const UQuat & );

      bool operator == ( const UQuat & ) const;
      bool operator != ( const UQuat &a ) const { return ! ( *this == a ); }
   
      void operator = ( const UMat3 & );

      float Length ();
      void Normalize ();
      UQuat getNormalized ();
      void Invert ();
      UQuat getInverse ();
      void Slerp ( const UQuat &from, const UQuat &to, float t );
      void SetupRotation ( float angles );

      UVector3    ProjectVector( const UVector3 &b ) const;
      UVector3    UnprojectVector( const UVector3 &b ) const;
   };

inline UQuat::UQuat () {}
inline UQuat::UQuat ( float xx, float yy, float zz, float ww ) { x = xx; y = yy; z = zz; w = ww; }
inline UQuat::UQuat ( const UVector3 &v, float ww ) { x = v.x; y = v.y; z = v.z; w = ww; }

inline void UQuat::set ( float xx, float yy, float zz, float ww ) { x = xx; y = yy; z = zz; w = ww; }
inline UVector3 &UQuat::vec3 () { return *reinterpret_cast<UVector3 *>(&x); }

inline float *UQuat::vec4 () { return &x; }

inline UQuat &UQuat::operator += ( const UQuat &a ) { x += a.x; y += a.y; z += a.z; w += a.w; return *this; }
inline UQuat &UQuat::operator -= ( const UQuat &a ) { x -= a.x; y -= a.y; z -= a.z; w -= a.w; return *this; }
inline UQuat &UQuat::operator *= ( float f )        { x *= f; y *= f; z *= f; w *= f; return *this; }
inline UQuat &UQuat::operator *= ( const UQuat &a ) { *this = *this * a; return *this; }
inline bool   UQuat::operator == ( const UQuat &a ) const { return x == a.x && y == a.y && z == a.z && w == a.w; }
inline UQuat         operator *  ( float a, const UQuat &b ) { return b * a; }

inline void UQuat::SetupRotation 
   (
   float angles 
   )

   {
   float halftheta = Deg2Rad ( angles ) * 0.5f;

   w = Cos ( halftheta );
   vec3 () *= Sin ( halftheta );
   }

inline UQuat operator + 
   ( 
   const UQuat &a, 
   const UQuat &b 
   ) 
   
   { 
   UQuat c;

   c.x = a.x + b.x;
   c.y = a.y + b.y;
   c.z = a.z + b.z;
   c.w = a.w + b.w;

   return c;
   }

inline UQuat operator -
   ( 
   const UQuat &a, 
   const UQuat &b 
   ) 
   
   { 
   UQuat c;

   c.x = a.x - b.x;
   c.y = a.y - b.y;
   c.z = a.z - b.z;
   c.w = a.w - b.w;

   return c;
   }

inline UQuat operator * 
   (
   const UQuat &a,
   float b 
   )

   {
   UQuat c;

   c.x = a.x * b;
   c.y = a.y * b;
   c.z = a.z * b;
   c.w = a.w * b;

   return c;
   }

inline UQuat operator *
   (
   const UQuat &a,
   const UQuat &b 
   )

   {
   UQuat c;
/* old one.  Way differnt! 
   c.x = a.x * b.x - a.y * b.y - a.z * b.z - a.w * b.w;
   c.y = a.x * b.y + a.y * b.x + a.z * b.w - a.w * b.z;
   c.z = a.x * b.z - a.y * b.w + a.z * b.x + a.w * b.y;
   c.w = a.x * b.w + a.y * b.z - a.z * b.y + a.w * b.x;
*/

   c.x = a.w * b.x + b.w * a.x + a.y * b.z - a.z * b.y;
   c.y = a.w * b.y + b.w * a.y + a.z * b.x - a.x * b.z;
   c.z = a.w * b.z + b.w * a.z + a.x * b.y - a.y * b.x;
   c.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;

   return c;
   }

inline float UQuat::operator[]
	( 
	int index 
	) const

	{
	assert( ( index >= 0 ) && ( index < 4 ) );
	return ( &x )[ index ];
	}

inline float& UQuat::operator[]
	( 
	int index 
	)

	{
	assert( ( index >= 0 ) && ( index < 4 ) );
	return ( &x )[ index ];
	}

inline float UQuat::Length
   (
   void
   )

   {
   return Sqrt ( x * x + y * y + z * z + w * w );
   }

inline void UQuat::Normalize 
   (
   void 
   ) 

   {
   float length, ilength;

   length = Length ();
   if ( length )
      {
      ilength = 1.f / length;
		x *= ilength;
		y *= ilength;
		z *= ilength;
		w *= ilength;
		}
   }

inline UQuat UQuat::getNormalized
   (
   void
   )

   {
   UQuat q = *this;

   q.Normalize ();
   return q;
   }

inline void UQuat::Invert 
   (
   void
   )

   {
   vec3 () *= -1.f;
   }

inline UQuat UQuat::getInverse 
   (
   void
   )

   {
   UQuat u ( *this );

   u.vec3 () *= -1.f;
   return u;
   }

inline UVector3 UQuat::ProjectVector
   (
   const UVector3 &b
   ) const

   {
   // convert b to a quat and multiply (c = this * UQuat( b ))
   UQuat c
      (
       w * b.x + y * b.z - z * b.y,
       w * b.y + z * b.x - x * b.z,
       w * b.z + x * b.y - y * b.x,
      -x * b.x - y * b.y - z * b.z
      );

   // construct in return memory ( c * this.Inverse ).vec3()
   return UVector3
      (
      c.w * -x - w * c.x - c.y * z + c.z * y,
      c.w * -y - w * c.y - c.z * x + c.x * z,
      c.w * -z - w * c.z - c.x * y + c.y * x
      );
   }

inline UVector3 UQuat::UnprojectVector
   (
   const UVector3 &b
   ) const

   {
   // convert b to a quat and multiply (c = this.Inverse * UQuat( b ))
   UQuat c
      (
      w * b.x - y * b.z + z * b.y,
      w * b.y - z * b.x + x * b.z,
      w * b.z - x * b.y + y * b.x,
      x * b.x + y * b.y + z * b.z
      );

   // construct in return memory ( c * this ).vec3()
   return UVector3
      (
      c.w * x + w * c.x + c.y * z - c.z * y,
      c.w * y + w * c.y + c.z * x - c.x * z,
      c.w * z + w * c.z + c.x * y - c.y * x
      );
   }

#endif /* !__UQUAT_H__ */
