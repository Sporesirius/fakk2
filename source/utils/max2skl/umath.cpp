#include "ucommon.h"
#include "umath.h"

static s_seed = 0;
const int umath::m_tableSize = 1024;
const float umath::m_tableMultiply = static_cast<float>(m_tableSize) / 360.f;

float umath::sinTable[umath::m_tableSize];
float umath::signedSinTable[umath::m_tableSize];
float umath::cosTable[umath::m_tableSize];
float umath::squareTable[umath::m_tableSize];
float umath::sawtoothTable[umath::m_tableSize];

class UMathInit
   {
   public:
   UMathInit ();
   };

static UMathInit s_mathinit;

UMathInit::UMathInit
   (
   void
   )

   {
   int i;

   for ( i=0; i < umath::m_tableSize; i++ )
      {
      umath::sinTable[i] = Sin ( Deg2Rad ( i * 360.f / float ( umath::m_tableSize - 1 ) ) );
      umath::signedSinTable[i] = Sin ( Deg2Rad ( i * 360.f / float ( umath::m_tableSize - 1 ) ) ) / 2.f + 0.5f;;
      umath::cosTable[i] = Cos ( Deg2Rad ( i * 360.f / float ( umath::m_tableSize - 1 ) ) );
      umath::squareTable[i] = ( i < umath::m_tableSize / 2 ) ? 1.f : 0.f;
      umath::sawtoothTable[i] = float ( i ) / float ( m_tableSize - 1 );
      }
   }

int umath::RandomInt
   (
   void
   )

   {
   s_seed = 69069 * s_seed + 1;
   return s_seed;
   }

float umath::RandomFloat 
   (
   void
   )

   {
   return ( RandomInt () & 0xFFFF ) / float ( 0x10000 );
   }

float umath::RandomSignedFloat 
   (
   void
   )

   {
   return 2.f * ( RandomFloat () - 0.5f );
   }

#if 1
inline float umath::InvSqrt
   (
   float number
   )

   {
	float y;
   int &y_int = *reinterpret_cast<int *>(&y);

	y     = number;
	y_int = 0x5f3759df - ( y_int >> 1 );      // what the fuck?
	y    *= 1.5f - 0.5f * number * y * y;   // 1st iteration
//	y    *= 1.5f - 0.5f * number * y * y;   // 2nd iteration = bye bye

	return y;
   }
#else
static const float ONE_HALF = 0.5f;
static const float THREE_HALVES = 1.5f;
__declspec(naked) float umath::InvSqrt 
   (
   float f
   )

   {
   __asm
      {
         fld			dword ptr [esp + 4]
         fmul		dword ptr [ONE_HALF]
         
         mov			eax, [esp + 4]
         mov			ecx, 0x5f3759df
         
         shr			eax, 1
         
         sub			ecx, eax
         
         mov			[esp + 4], ecx
         
         fmul		dword ptr [esp + 4]
         fld			dword ptr [esp + 4]
         fmul		dword ptr [esp + 4]
         fld			dword ptr [THREE_HALVES]
         fmul		dword ptr [esp + 4]
         fxch		st(2)
         fmulp		st(1), st
         fsubp		st(1), st
         ret
      }
   }
#endif

