//-----------------------------------------------------------------------------
//
//  $Logfile:: /fakk2_code/Utils_Q3A/max2skl/uvector3.cpp                     $
// $Revision:: 1                                                              $
//     $Date:: 9/21/99 2:24p                                                  $
//
// Copyright (C) 1999 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /fakk2_code/Utils_Q3A/max2skl/uvector3.cpp                          $
// 
// 1     9/21/99 2:24p Jimdose
// 
// 5     6/25/99 7:43p Morbid
// 
// 4     5/28/99 6:58p Morbid
// Initial implementations
// 
// 3     5/27/99 8:40p Jimdose
// merged math and gui code
//
// DESCRIPTION:
// 

#include "uvector3.h"
#include "umatrix.h"
#include "uplane3.h"
#include "uquat.h"

const float    UVector3::LERP_DELTA = 1e-6f;
const UVector3 UVector3::origin( 0, 0, 0 );
const UVector3 UVector3::zero( 0, 0, 0 );

void UVector3::LerpVector
	(
   UVector3 w1,
   UVector3 w2,
   float t
	)

   {
	float	omega, cosom, sinom, scale0, scale1;

	w1.Normalize();
	w2.Normalize();

	cosom = w1 * w2;
	if ( ( 1.0 - cosom ) > LERP_DELTA )
		{
		omega = Acos( cosom );
		sinom = Sin( omega );
		scale0 = Sin( ( 1.f - t ) * omega ) / sinom;
		scale1 = Sin( t * omega ) / sinom;
		}
	else
		{
		scale0 = 1.f - t;
		scale1 = t;
		}

	*this = w1 * scale0 + w2 * scale1;
   }

float UVector3::toYaw
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

float UVector3::toPitch
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

UVector3 UVector3::toAngles
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
		yaw = Atan2( y, x ) * 180.f / M_PI;
		if ( yaw < 0 )
			{
			yaw += 360;
			}

		forward = ( float )sqrt( x * x + y * y );
		pitch = Atan2( z, forward ) * 180 / M_PI;
		if ( pitch < 0 )
			{
			pitch += 360;
			}
		}

	return UVector3( pitch, yaw, 0 );
	}

void UVector3::RotatePointAroundVector 
   ( 
   const UVector3 &dir,
   const UVector3 &point, 
   float deg 
   )

   {
   UQuat about ( dir );
   float thetaover2 = Deg2Rad ( deg ) / 2.f;

   about.vec3 ().Normalize ();
   about.w = Cos ( thetaover2 );
   about.vec3 () *= Sin ( thetaover2 );

   *this = ( about * point * about.getInverse () ).vec3 ();
   }

void UVector3::MakePerp
   (
   const UVector3 &to
   )

   {
   int 
      pos,
      i;
   float minelem = 1.f;
   UVector3 tmp;

   for ( pos = 0, i = 0; i < 3; i++ ) 
      {
      if ( Fabs ( to[i] ) < minelem )
         {
         pos = i;
         minelem = Fabs ( to[i] );
         }
      }

   tmp.setXYZ ( 0.f, 0.f, 0.f );
   tmp[pos] = 1.f;
   UPlane3 ( to ).ProjectToPlane ( tmp, *this );

   Normalize ();
}
