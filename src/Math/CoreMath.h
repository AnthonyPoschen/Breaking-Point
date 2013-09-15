//////////////////////////////////////////////////////////////////////////
/*! \class		CoreMath
 *  \brief		Main Math include it includes all math files and supplies helper varriables.
 *	\details	
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		05/12/2012
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _COREMATH_H_
# define _COREMATH_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "float4.h"
#include "float3.h"
#include "float2.h"
#include "matrix3.h"
#include "Quaternion.h"
#include "UniversalTypes.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
#ifndef __SPU__
const Float32 BP_PI = 3.1415926535897932f;
const Float32 BP_HALF_PI = 0.5f * BP_PI;
const Float32 BP_TWO_PI = 2.0f * BP_PI;
const Float32 BP_E = 2.7182818284590452f;

// Conversion macros
#define toRadians(Degrees) (Degrees * BP_DEGREES_TO_RADIANS)
#define toDegrees(Radians) (Radians * BP_RADIANS_TO_DEGREES)
const Float32 BP_DEGREES_TO_RADIANS = BP_PI / 180.0f;
const Float32 BP_RADIANS_TO_DEGREES = 180.0f / BP_PI;

#else
// SPU compiler does not like global static constant variables
#define BP_INFINITY     FLT_MAX
#define BP_PI           3.1415926535897932f
#define BP_HALF_PI      0.5f * BP_PI
#define BP_TWO_PI       2.0f * BP_PI
#define BP_E            2.7182818284590452f
#endif

float __fastcall bzSqrt(float a_fValue);
float bzFastInvSqrt(float a_fValue);

//////////////////////////////////////////////////////////////////////////
#endif // _COREMATH_H_
//////////////////////////////////////////////////////////////////////////