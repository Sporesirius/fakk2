#include "uquat.h"
#include "umatrix.h"
#include "ueuler.h"

static const float s_slerpDelta = float ( 1e-6 );

UQuat::UQuat 
   (
   const UEuler &angles
   )

   {
   UQuat working;

   vec3 ().setXYZ ( 0.f, 1.f, 0.f );
   SetupRotation ( angles.yaw );

   working.vec3 ().setXYZ ( 1.f, 0.f, 0.f );
   working.SetupRotation ( angles.pitch );
   *this *= working;

   working.vec3 ().setXYZ ( 0.f, 0.f, 1.f );
   working.SetupRotation ( angles.roll );
   *this *= working;
   }

void UQuat::operator = 
   (
   const UMat3 &mat
   )

   {
   float 
      trace,
      s;

   trace = mat.vecs[0].x + mat.vecs[1].y + mat.vecs[2].z;

   if ( trace > 0.f )
      {
      s = Sqrt ( trace + 1.f );
      UQuat::w = s * 0.5f;
      s = 0.5f / s;

      UQuat::x = ( mat.vecs[2].y - mat.vecs[1].z ) * s;
      UQuat::y = ( mat.vecs[0].z - mat.vecs[2].x ) * s;
      UQuat::z = ( mat.vecs[1].x - mat.vecs[0].y ) * s;
      }
   else
      {
      int 
         i,
         j,
         k;
      static int 
         s_next[3] = { 1, 2, 0 };

      i = 0;
      if ( mat.vecs[1].y > mat.vecs[0].x )
         i = 1;
      if ( mat.vecs[2].z > mat.vecs[i][i] )
         i = 2;

      j = s_next[i];
      k = s_next[j];

      s = Sqrt ( ( mat.vecs[i][i] - ( mat.vecs[j][j] + mat.vecs[k][k] ) ) + 1.f );
      UQuat::operator[](i) = s * 0.5f;
       
      s = 0.5f / s;

      UQuat::w =             ( mat.vecs[k][j] - mat.vecs[j][k] ) * s;
      UQuat::operator[](j) = ( mat.vecs[j][i] + mat.vecs[i][j] ) * s;
      UQuat::operator[](k) = ( mat.vecs[k][i] + mat.vecs[i][k] ) * s;
      }
   }

void UQuat::Slerp 
   ( 
   const UQuat &from, 
   const UQuat &to, 
   float t 
   ) 

   {
   float omega, cosom, sinom, scale0, scale1;
   float scaleto;

   if ( from == to ) 
      {
      *this = from;
      return;
      }
   
   cosom = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;
   scaleto = 1.f;

   if ( cosom < 0.f )
      {
      cosom = -cosom;
      scaleto = -1.f;
      }

   if ( 1.f - cosom > s_slerpDelta )
      {
      omega = Acos ( cosom );
      sinom = Sin ( omega );
      scale0 = Sin ( ( 1.f - t ) * omega ) / sinom;
      scale1 = Sin ( t * omega ) / sinom;
      }
   else
      {
      scale0 = 1.f - t;
      scale1 = t;
      }
   
   *this = ( scale0 * from ) + ( scaleto * scale1 * to );
   }

