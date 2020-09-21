#ifndef __UEULER_H__
#define __UEULER_H__

class UVector3;
class UMat3;

class UEuler
   {
   public:
      float yaw;
      float pitch;
      float roll;
      
      inline UEuler () {} // Do nothing
      UEuler ( float, float, float );
      void setYPR ( float, float, float );
      
      friend UEuler operator + ( const UEuler &, const UEuler & );
      friend UEuler operator - ( const UEuler &, const UEuler & );
      friend UEuler operator * ( const UEuler &, float );
      inline friend UEuler operator * ( float a, UEuler &b ) { return b * a; }
      
      UEuler &operator += ( const UEuler & );
      UEuler &operator -= ( const UEuler & );
      UEuler &operator *= ( float );
      bool operator == ( const UEuler & ) const;
      bool operator != ( const UEuler &a ) const { return ! ( *this == a ); }
      
      void operator = ( const UMat3 & );

      void AngleVectors ( UVector3 *right, UVector3 *up, UVector3 *forward ) const;
   };

inline      UEuler::UEuler ( float yy, float pp, float rr ) { yaw = yy; pitch = pp; roll = rr; }
inline void UEuler::setYPR ( float yy, float pp, float rr ) { yaw = yy; pitch = pp; roll = rr; }

inline UEuler &UEuler::operator += ( const UEuler &a )       { yaw += a.yaw; pitch += a.pitch; roll += a.roll; }
inline UEuler &UEuler::operator -= ( const UEuler &a )       { yaw -= a.yaw; pitch -= a.pitch; roll -= a.roll; }
inline UEuler &UEuler::operator *= ( float f )               { yaw *= f;     pitch *= f;       roll *= f;      }
inline bool    UEuler::operator == ( const UEuler &a ) const { return ( pitch == a.pitch && roll == a.roll && yaw == a.yaw ); }

inline UEuler operator + 
   (
   const UEuler &a,
   const UEuler &b 
   )

   {
   UEuler c;

   c.yaw = a.yaw + b.yaw;
   c.pitch = a.pitch + b.pitch;
   c.roll = a.roll + b.roll;

   return c;
   }

inline UEuler operator - 
   (
   const UEuler &a,
   const UEuler &b 
   )

   {
   UEuler c;

   c.yaw = a.yaw - b.yaw;
   c.pitch = a.pitch - b.pitch;
   c.roll = a.roll - b.roll;

   return c;
   }

inline UEuler operator *
   (
   const UEuler &a,
   float b 
   )

   {
   UEuler c;

   c.yaw = a.yaw * b;
   c.pitch = a.pitch * b;
   c.roll = a.roll * b;

   return c;
   }

#endif /* !__UEULER_H__ */