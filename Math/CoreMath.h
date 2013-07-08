//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 5/12/2012 >
/// < File >	< Math >
/// < Brief >	< Math includer. this auto includes all math files. and builds base funcitonality >
//////////////////////////////////////////////////////////////////////////
#ifndef _COREMATH_H_
#define _COREMATH_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "float4.h"
#include "float3.h"
#include "float2.h"
#include "matrix3.h"
#include "Quaternion.h"
#include "UniversalTypes.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >
#ifndef __SPU__
const Float32 BZ_PI = 3.1415926535897932f;
const Float32 BZ_HALF_PI = 0.5f * BZ_PI;
const Float32 BZ_TWO_PI = 2.0f * BZ_PI;
const Float32 BZ_E = 2.7182818284590452f;

// Conversion macros
#define toRadians(Degrees) (Degrees * BZ_DEGREES_TO_RADIANS)
#define toDegrees(Radians) (Radians * BZ_RADIANS_TO_DEGREES)
const Float32 BZ_DEGREES_TO_RADIANS = BZ_PI / 180.0f;
const Float32 BZ_RADIANS_TO_DEGREES = 180.0f / BZ_PI;

#else
// SPU compiler does not like global static constant variables
#define BZ_INFINITY     FLT_MAX
#define BZ_PI           3.1415926535897932f
#define BZ_HALF_PI      0.5f * BZ_PI
#define BZ_TWO_PI       2.0f * BZ_PI
#define BZ_E            2.7182818284590452f
#endif

float __fastcall bzSqrt(float a_fValue);
float bzFastInvSqrt(float a_fValue);

//////////////////////////////////////////////////////////////////////////
#endif // _COREMATH_H_
//////////////////////////////////////////////////////////////////////////