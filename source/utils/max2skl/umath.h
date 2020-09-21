//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/umath.h                          $
// $Revision:: 1                                                              $
//     $Date:: 9/21/99 2:24p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/umath.h                               $
// 
// 1     9/21/99 2:24p Jimdose
// 
// 6     7/30/99 2:17p Morbid
// 
// 5     6/17/99 2:09p Morbid
// Lots of misc shit
// 
// 
// 4     5/28/99 6:58p Morbid
// Initial implementations
// 
// 3     5/28/99 3:12p Jimdose
// use type( x ) casts instead of static_cast<type>(x)
// 
// 2     5/27/99 8:40p Jimdose
// merged math and gui code
//
// DESCRIPTION:
// 

#ifndef __UMATH_H__
#define __UMATH_H__

#include "ucasts.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846f	// matches value in gcc v2 math.h
#endif

namespace umath 
   {  
   extern const int m_tableSize;
   extern const float m_tableMultiply;

   inline float Deg2Rad ( float f );
   inline float Rad2Deg ( float f );
   inline float Fabs ( float f );
   inline void FabsInPlace ( float &f );

   inline float Sin ( float );
   inline float Cos ( float );
   inline float Sqrt ( float );
   inline float Acos ( float );
   inline float Atan2 ( float, float );
   inline float Asin ( float );
   
   inline float Atof ( const char * );

   float InvSqrt ( float );

   int RandomInt ();
   float RandomFloat ();
   float RandomSignedFloat ();

   extern float sinTable[];
   extern float signedSinTable[];
   extern float cosTable[];
   extern float sawtoothTable[];
   extern float squareTable[];

   void InitMath ();

   inline float TableLookup ( float degrees, const float *table );

   inline float TableSin ( float degrees );
   inline float TableCos ( float degrees );
   inline float TableSquare ( float degrees );
   inline float TableSawtooth ( float degrees );
   };

inline float umath::Sin   ( float f ) { return float(  sin ( f )); }
inline float umath::Cos   ( float f ) { return float(  cos ( f )); }
inline float umath::Sqrt  ( float f ) { return float( sqrt ( f )); }
inline float umath::Acos  ( float f ) { return float( acos ( f )); }
inline float umath::Asin  ( float f ) { return float( asin ( f )); }

inline float umath::Atan2 ( float f, float f2 ) { return float(atan2 ( f, f2 )); }

inline float umath::Atof  ( const char *s ) { return float ( atof ( s ) ); }

inline float umath::Deg2Rad ( float f ) { return ( f * M_PI ) / 180.f; }
inline float umath::Rad2Deg ( float f ) { return ( f * 180.f ) / M_PI; }

inline float umath::Fabs        ( float f )  { uint_cast(f) &= 0x7FFFFFFF; return f; }
inline void  umath::FabsInPlace ( float &f ) { uint_cast(f) &= 0x7FFFFFFF; }

inline float umath::TableLookup 
   (
   float degrees,
   const float *table
   )

   {
   return table [ int ( degrees * m_tableMultiply ) & ( m_tableSize - 1 ) ];
   }

inline float umath::TableSin ( float degrees ) { return TableLookup ( degrees, sinTable ); }
inline float umath::TableCos ( float degrees ) { return TableLookup ( degrees + 90.f, sinTable ); }
inline float umath::TableSquare ( float degrees ) { return TableLookup ( degrees, squareTable ); }
inline float umath::TableSawtooth ( float degrees ) { return TableLookup ( degrees, sawtoothTable ); }

using namespace umath;
   
#endif