#include "ueuler.h"
#include "uvector3.h"
#include "umatrix.h"

#include <float.h>

void UEuler::AngleVectors
	(
   UVector3 *right,
   UVector3 *up,
   UVector3 *forward
	) const

	{
	float				angle;
	static float	sr, sp, sy, cr, cp, cy; // static to help MS compiler fp bugs
	
	angle = yaw * ( M_PI * 2 / 360 );
	sy = Sin( angle );
	cy = Cos( angle );

	angle = pitch * ( M_PI * 2 / 360 );
	sp = Sin( angle );
	cp = Cos( angle );

	angle = roll * ( M_PI * 2 / 360 );
	sr = Sin( angle );
	cr = Cos( angle );

	if ( right )
		{
		right->setXYZ( cp * cy, cp * sy, -sp );
		}

	if ( up )
		{
		up->setXYZ( -1 * sr * sp * cy + -1 * cr * -sy, -1 * sr * sp * sy + -1 * cr * cy,	-1 * sr * cp );
		}

	if ( forward )
		{
		forward->setXYZ( cr * sp * cy + -sr * -sy, cr * sp * sy + -sr * cy, cr * cp );
		}
	}

void UEuler::operator = 
   (
   const UMat3 &mat
   )

   {
   float 
      theta,
      cp,
      sp;
   
   sp = mat.vecs[0][2];
   // cap off our sin value so that we don't get any NANs
   if ( sp > 1.f )
      sp = 1.f;
   if ( sp < -1.f )
      sp = -1.f;
   
   theta = -Asin( sp );
   cp = Cos( theta );
   
   if ( cp > 8192.f * FLT_EPSILON )
      {
      yaw   = theta * 180.f / M_PI;
      pitch = Atan2( mat.vecs[ 0 ][ 1 ], mat.vecs[ 0 ][ 0 ] ) * 180.f / M_PI;
      roll  = Atan2( mat.vecs[ 1 ][ 2 ], mat.vecs[ 2 ][ 2 ] ) * 180.f / M_PI;
      }
   else
      {
      yaw   = theta * 180.f / M_PI;
      pitch = -Atan2( mat.vecs[ 1 ][ 0 ], mat.vecs[ 1 ][ 1 ] ) * 180.f / M_PI;
      roll  = 0.f;
      }
   }
