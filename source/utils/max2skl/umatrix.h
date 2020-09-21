//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils/max2skl/umatrix.h                            $
// $Revision:: 3                                                              $
//     $Date:: 4/25/00 11:26a                                                 $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils/max2skl/umatrix.h                                 $
// 
// 3     4/25/00 11:26a Jimdose
// fixed a bug in UMat3::OrthoNormalize
// 
// 2     10/04/99 7:04p Jimdose
// added * operators to UMat3
// 
// 1     9/21/99 2:24p Jimdose
// 
// 6     8/04/99 6:08p Morbid
// * Ported curve test over
// * Added polygon mode (read: wireframe) to UPrim
// * Added another overload to UMat4::Translate
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

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "ucommon.h"
#include "uvector3.h"

///////////////////////////
// UMat4 Definition
///////////////////////////

// These are column-major, which means:

/*
 -          -
| 1  5  9 13 |
| 2  6 10 14 | 
| 3  7 11 15 |
| 4  8 12 16 |
 -          -

  or 

 -                           -
| [0][0] [1][0] [2][0] [3][0] |
| [0][1] [1][1] [2][1] [3][1] | 
| [0][2] [1][2] [2][2] [3][2] |
| [0][3] [1][3] [2][3] [3][3] |
 -                           -

*/

class UQuat;
class UEuler;
class UMat3;

class UMat4 {
   public:
      UMat4 ();
      UMat4 ( const UMat4 &copy );
      UMat4 ( const UMat3 & );
      UMat4 ( const UQuat & );
      float floats[4][4];
      
      void setIdentity ();
      void Transpose ();

      // Static matrix generation functions
      static UMat4 Ortho ( float left, float right, float bottom, float top, float nearz, float farz );
      static UMat4 Frustum ( float left, float right, float bottom, float top, float nearz, float farz );
      static UMat4 Translate ( float x, float y, float z );
      inline static UMat4 Translate ( const UVector3 &in ) { return Translate ( in.x, in.y, in.z ); }
      
      void MultiplyMatrix ( const UMat4 &in1, const UMat4 &in2 );
      void MultiplyThis ( const UMat4 &in );
      float MultiplyVector ( const UVector3 &in, UVector3 &out ) const; // returns w

      friend UMat4 operator* ( const UMat4 &in1, const UMat4 &in2 );
      UMat4 &operator *= ( const UMat4 &in );
      operator const float * ();
   };

///////////////////////////
// UMat3 Definition
///////////////////////////

class UMat3 {
   public:
      UMat3 ();
      UMat3 ( const UQuat & );
      
      UVector3 vecs[3];

      float *getFloats ();
      void setIdentity ();

      void operator = ( const UEuler & );

      void MultiplyMatrix ( const UMat3 &, const UMat3 & );
      void MultiplyThis ( const UMat3 & );

      void ProjectVector ( const UVector3 &in, UVector3 &out ) const;
      void UnprojectVector ( const UVector3 &in, UVector3 &out ) const;

      void OrthoNormalize ();
      void Transpose ();

      friend UMat3 operator* ( const UMat3 &in1, const UMat3 &in2 );
      UMat3 &operator *= ( const UMat3 &in );
      operator const float * ();
   };

///////////////////////////
// UMat4 inlines
///////////////////////////

inline UMat4::UMat4 (
                     )
   {
   }

inline UMat4::UMat4 ( 
                     const UMat4 &copy 
                     )
   {
   umem::Copy ( floats, copy.floats );
   }

inline UMat4::UMat4
   (
   const UQuat &q
   )

   {
   *this = static_cast<UMat3>(q);
   }


inline UMat4 operator* ( 
                        const UMat4 &in1, 
                        const UMat4 &in2 
                        ) 
   {
   UMat4 that;

   that.MultiplyMatrix ( in1, in2 );
   return that;
   }

inline UMat4 &UMat4::operator *= ( 
                                  const UMat4 &in 
                                  ) 
   {
   MultiplyThis ( in );
   return *this;
   }

inline UMat4::operator const float * 
   (
   void
   )

   {
   return &floats[0][0];
   }

///////////////////////////
// UMat3 inlines
///////////////////////////

inline UMat3::UMat3 
   (
   void
   )

   {
   }

inline float *UMat3::getFloats ( 
                                void 
                                )
   {
   return &vecs[0].x;
   }

inline void UMat3::setIdentity (
                                void 
                                )
   {
   vecs[0].setXYZ ( 1.f, 0.f, 0.f );
   vecs[1].setXYZ ( 0.f, 1.f, 0.f );
   vecs[2].setXYZ ( 0.f, 0.f, 1.f );
   }

inline void UMat3::OrthoNormalize 
   (
   void
   )

   {
   vecs[0].Normalize ();
   vecs[2].CrossProduct ( vecs[0], vecs[1] );
   vecs[2].Normalize ();
   vecs[1].CrossProduct ( vecs[2], vecs[0] );
   vecs[1].Normalize ();
   }

inline UMat3 operator* ( 
                        const UMat3 &in1, 
                        const UMat3 &in2 
                        ) 
   {
   UMat3 that;

   that.MultiplyMatrix ( in1, in2 );
   return that;
   }

inline UMat3 &UMat3::operator *= ( 
                                  const UMat3 &in 
                                  ) 
   {
   MultiplyThis ( in );
   return *this;
   }

inline UMat3::operator const float * 
   (
   void
   )

   {
   return vecs[0].vec3();
   }

#endif