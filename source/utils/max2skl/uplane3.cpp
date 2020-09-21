#include "ucommon.h"
#include "uplane3.h"

float UPlane3::getIntersectTime 
   ( 
   const UVector3 &p1, 
   const UVector3 &p2_minus_p1 
   ) const

   {
   return - ( n DOT p1 + d ) / ( n DOT p2_minus_p1 );
   }

UVector3 UPlane3::IntersectRay 
   ( 
   const UVector3 &p1, 
   const UVector3 &p2 
   ) const

   {
   UVector3 p2_minus_p1 = p2;

   p2_minus_p1 -= p1;

   p2_minus_p1 *= getIntersectTime ( p1, p2_minus_p1 );
   p2_minus_p1 += p1;

   return p2_minus_p1;
   }



 