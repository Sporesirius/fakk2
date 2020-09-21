//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2skl/umatrix.cpp                          $
// $Revision:: 3                                                              $
//     $Date:: 4/25/00 11:26a                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2skl/umatrix.cpp                               $
// 
// 3     4/25/00 11:26a Jimdose
// Fixed a bug in UQuat to UMat3 conversion.
// 
// 2     4/07/00 2:25p Jimdose
// optimized quat to UMat3 conversion
// 
// 1     9/21/99 2:24p Jimdose
// 
// 5     7/06/99 12:42p Morbid
// Various changes
// 
// 4     6/25/99 7:43p Morbid
// 
// 3     5/28/99 6:58p Morbid
// Initial implementations
// 
// 2     5/27/99 8:40p Jimdose
// merged math and gui code
//
// DESCRIPTION:
// 

#include "ucommon.h"
#include "umatrix.h"
#include "uquat.h"
#include "ueuler.h"

///////////////////////////
// UMat4 Implementation
///////////////////////////

UMat4::UMat4
   (
   const UMat3 &mat3
   )

   {
   int i;

   for( i = 0; i < 3; i++ )
      {
      floats[ i ][ 0 ] = mat3.vecs[ 0 ][ i ];
      floats[ i ][ 1 ] = mat3.vecs[ 1 ][ i ];
      floats[ i ][ 2 ] = mat3.vecs[ 2 ][ i ];
      floats[ i ][ 3 ] = 0.f;
      }

   floats[ 3 ][ 0 ] = 0.f;
   floats[ 3 ][ 1 ] = 0.f;
   floats[ 3 ][ 2 ] = 0.f;
   floats[ 3 ][ 3 ] = 1.f;
   }

void UMat4::setIdentity 
   (
   void 
   ) 

   {
   int i;
   
   umem::Zero( *this );
   for( i = 0; i < 4; i++ )
      {
      floats[ i ][ i ] = 1.f;
      }
   }

void UMat4::Transpose 
   (
   void
   )

   {
   float f;
   int   i;
   int   i1;
   
   for( i = 0; i < 4; i++ ) 
      {
      for( i1 = i + 1; i1 < 4; i1++ )
         {
         f = floats[ i ][ i1 ];
         floats[ i ][ i1 ] = floats[ i1 ][ i ];
         floats[ i1 ][ i ] = f;
         }
      }
   }

void UMat4::MultiplyMatrix 
   ( 
   const UMat4 &in1, 
   const UMat4 &in2 
   )

   {
   int i;
   int i1;
   
   for( i = 0; i < 4; i++ )
      {
      for( i1 = 0; i1 < 4; i1++ )
         {
         floats[ i1 ][ i ] = 
            in1.floats[ 0 ][ i ] * in2.floats[ i1 ][ 0 ] +
            in1.floats[ 1 ][ i ] * in2.floats[ i1 ][ 1 ] +
            in1.floats[ 2 ][ i ] * in2.floats[ i1 ][ 2 ] +
            in1.floats[ 3 ][ i ] * in2.floats[ i1 ][ 3 ];
         }
      }
   }

void UMat4::MultiplyThis 
   (
   const UMat4 &in 
   ) 

   {
   float tmp[ 4 ][ 4 ];
   int i;
   int i1;

   for( i = 0; i < 4; i++ )
      {
      for( i1 = 0; i1 < 4; i1++ )
         {
         tmp[ i1 ][ i ] = 
            floats[ 0 ][ i ] * in.floats[ i1 ][ 0 ] +
            floats[ 1 ][ i ] * in.floats[ i1 ][ 1 ] +
            floats[ 2 ][ i ] * in.floats[ i1 ][ 2 ] +
            floats[ 3 ][ i ] * in.floats[ i1 ][ 3 ];
         }
      }

   umem::Copy( floats, tmp );
   }

float UMat4::MultiplyVector 
   (
   const UVector3 &in,
   UVector3 &out 
   ) const

   {
   int   i;
   float w_inv;
   float w;

   for( i = 0; i < 3; i++ )
      {
      out[ i ] = 
         in[ 0 ] * floats[ i ][ 0 ] + 
         in[ 1 ] * floats[ i ][ 1 ] + 
         in[ 2 ] * floats[ i ][ 2 ] + 
         floats[ i ][ 3 ]; // w == 1.0f
      }
   
   w = in[ 0 ] * floats[ 3 ][ 0 ] + in[ 1 ] * floats[ 3 ][ 1 ] + 
       in[ 2 ] * floats[ 3 ][ 2 ] + floats[ 3 ][ 3 ];
   w_inv = 1.f / w;

   out *= w_inv;

   return w;
   }

UMat4 UMat4::Ortho 
   (
   float left,
   float right,
   float bottom,
   float top,
   float nearz, 
   float farz
   ) 

   {
   UMat4 that;

   that.setIdentity();
   that.floats[ 0 ][ 0 ] = 2.f / ( right - left );
   that.floats[ 1 ][ 1 ] = 2.f / ( top - bottom );
   that.floats[ 2 ][ 2 ] = -2.f / ( farz - nearz );
   that.floats[ 3 ][ 3 ] = 1.f;

   that.floats[ 3 ][ 0 ] = ( right + left ) / ( right - left );
   that.floats[ 3 ][ 1 ] = ( top + bottom ) / ( top - bottom );
   that.floats[ 3 ][ 2 ] = ( farz + nearz ) / ( farz - nearz );

   return that;
   }

UMat4 UMat4::Frustum 
   (
   float left,
   float right,
   float bottom,
   float top,
   float nearz, 
   float farz
   ) 

   {
   UMat4 that;

   that.setIdentity ();
   that.floats[ 0 ][ 0 ] = 2.f * nearz / ( right - left );
   that.floats[ 1 ][ 1 ] = 2.f * nearz / ( top - bottom );
   that.floats[ 2 ][ 2 ] = - ( farz + nearz ) / ( farz - nearz );

   that.floats[ 2 ][ 0 ] = ( right + left ) / ( right - left );
   that.floats[ 2 ][ 1 ] = ( top + bottom ) / ( top - bottom );
   that.floats[ 3 ][ 2 ] = -2.f * farz * nearz / ( farz - nearz );

   return that;
   }

UMat4 UMat4::Translate 
   ( 
   float x,
   float y,
   float z 
   )

   {
   UMat4 that;

   that.setIdentity ();

   that.floats[ 3 ][ 0 ] = x;
   that.floats[ 3 ][ 1 ] = y;
   that.floats[ 3 ][ 2 ] = z;

   return that;
   }

///////////////////////////
// UMat3 Implementation
///////////////////////////

void UMat3::ProjectVector 
   (
   const UVector3 &in, 
   UVector3 &out 
   ) const

   {
   out.x = in DOT vecs[ 0 ];
   out.y = in DOT vecs[ 1 ];
   out.z = in DOT vecs[ 2 ];
   }

void UMat3::UnprojectVector 
   (
   const UVector3 &in, 
   UVector3 &out 
   ) const

   {
   out.Scale   ( vecs[ 0 ], in.x      );
   out.ScaleAdd( vecs[ 1 ], in.y, out );
   out.ScaleAdd( vecs[ 2 ], in.z, out );
   }

UMat3::UMat3
   (
   const UQuat &q
   )

   {
   float x2 = q.x * 2.0f;
   float y2 = q.y * 2.0f;
   float z2 = q.z * 2.0f;

   float xy = q.x * y2;
   float xz = q.x * z2;
   float yz = q.y * z2;

   float wx = q.w * x2;
   float wy = q.w * y2;
   float wz = q.w * z2;

   float xs = q.x * x2;
   float ys = q.y * y2;
   float zs = q.z * z2;

   vecs[0].setXYZ( 1.f - ( ys + zs ), xy - wz, xz + wy );
   vecs[1].setXYZ( xy + wz, 1.f - ( xs + zs ), yz - wx );
   vecs[2].setXYZ( xz - wy, yz + wx, 1.f - ( xs + ys ) );
   }

void UMat3::operator =
   (
   const UEuler &e
   )
   
   {
   e.AngleVectors ( &vecs[ 0 ], &vecs[ 1 ], &vecs[ 2 ] );
   vecs[ 1 ] *= -1.f;
   }

void UMat3::Transpose
   (
   void
   )

   {
   float f;
   int   i;
   int   i1;
   
   for( i = 0; i < 3; i++ ) 
      {
      for( i1 = i + 1; i1 < 3; i1++ ) 
         {
         f = vecs[ i ][ i1 ];
         vecs[ i ][ i1 ] = vecs[ i1 ][ i ];
         vecs[ i1 ][ i ] = f;
         }
      }
   }

void UMat3::MultiplyMatrix 
   ( 
   const UMat3 &in1, 
   const UMat3 &in2 
   )

   {
   int i;
   int i1;
   
   for( i = 0; i < 3; i++ )
      {
      for( i1 = 0; i1 < 3; i1++ )
         {
         vecs[ i ][ i1 ] = 
            in1.vecs[ i ][ 0 ] * in2.vecs[ 0 ][ i1 ] +
            in1.vecs[ i ][ 1 ] * in2.vecs[ 1 ][ i1 ] +
            in1.vecs[ i ][ 2 ] * in2.vecs[ 2 ][ i1 ];
         }
      }
   }

void UMat3::MultiplyThis 
   (
   const UMat3 &in 
   ) 

   {
   UVector3 tmp[ 3 ];
   int i;
   int i1;

   for( i = 0; i < 3; i++ )
      {
      for( i1 = 0; i1 < 3; i1++ )
         {
         tmp[ i ][ i1 ] = 
            vecs[ i ][ 0 ] * in.vecs[ 0 ][ i1 ] +
            vecs[ i ][ 1 ] * in.vecs[ 1 ][ i1 ] +
            vecs[ i ][ 2 ] * in.vecs[ 2 ][ i1 ];
         }
      }

   umem::Copy( vecs, tmp );
   }
