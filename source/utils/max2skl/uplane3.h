//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/uplane3.h                        $
// $Revision:: 1                                                              $
//     $Date:: 9/21/99 2:34p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/uplane3.h                             $
// 
// 1     9/21/99 2:34p Jimdose
// 
// 4     9/17/99 4:11p Morbid
// Fixed main #define from PLANE3_H to UPLANE3_H
// 
// 3     6/17/99 2:09p Morbid
// Lots of misc shit
// 
// 
// 2     5/27/99 8:40p Jimdose
// merged math and gui code
//
// DESCRIPTION:
// 

#ifndef __UPLANE3_H__
#define __UPLANE3_H__

#include "UVector3.h"

class UPlane3 
{
public:
   UPlane3 ();
   UPlane3 ( const UVector3 &vec, float dist = 0.f );
   UPlane3 ( const UPlane3 & );

   UVector3 n;
   float d;

   float DistanceFromPlane ( const UVector3 &in ) const;
   void ProjectToPlane ( const UVector3 &in, UVector3 &out ) const;
   UVector3 IntersectRay ( const UVector3 &p1, const UVector3 &p2) const;
   float getIntersectTime ( const UVector3 &p1, const UVector3 &p2_minus_p1 ) const;

};

inline UPlane3::UPlane3 
   (
   void
   )

   {   
   }

inline UPlane3::UPlane3 
   (
   const UVector3 &vec, 
   float dist 
   )

   {
   n = vec;
   d = dist;
   }

inline UPlane3::UPlane3
   (
   const UPlane3 &copy 
   )

   {
   n = copy.n;
   d = copy.d;
   }

inline float UPlane3::DistanceFromPlane 
   ( 
   const UVector3 &in
   ) const

   {
   return -( in DOT n ) - d;
   }

inline void UPlane3::ProjectToPlane 
   (
   const UVector3 &in,
   UVector3 &out 
   ) const

   {
   out = in + ( n * DistanceFromPlane ( in ) );
   }


#endif /* __UPLANE3_H__ */