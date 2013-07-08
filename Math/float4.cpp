//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 10/12/2012 >
/// < File >	< float4 >
/// < Brief >	< implementation of float4 class. for math. >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "float4.h"
#include "CoreMath.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
float4::float4()
	:X(0),Y(0),Z(0),W(0)
{

}
//////////////////////////////////////////////////////////////////////////
float4::float4(float a_fX, float a_fY, float a_fZ, float a_fW)
	:X(a_fX),Y(a_fY),Z(a_fZ),W(a_fW)
{

}

//////////////////////////////////////////////////////////////////////////
float4::float4(const float4 &a_kVec)
	:X(a_kVec.X),Y(a_kVec.Y),Z(a_kVec.Z),W(a_kVec.W)
{

}

//////////////////////////////////////////////////////////////////////////
float4::~float4()
{

}

//////////////////////////////////////////////////////////////////////////
float float4::Length() const
{
	return bzSqrt(X * X + Y * Y + Z * Z + W * W);
}

//////////////////////////////////////////////////////////////////////////
float float4::Unitise()
{
	float fSum = X + Y + Z + W;
	X /= fSum;
	Y /= fSum;
	Z /= fSum;
	W /= fSum;
	return fSum;
}

//////////////////////////////////////////////////////////////////////////
float float4::UnitiseVector(float4 &a_kVec)
{
	float fSum = a_kVec.X + a_kVec.Y + a_kVec.Z + a_kVec.W;
	a_kVec.X /= fSum;
	a_kVec.Y /= fSum;
	a_kVec.Z /= fSum;
	a_kVec.W /= fSum;
	return fSum;
}

//////////////////////////////////////////////////////////////////////////
float4 float4::Lerp(const float4 &a_kBegin , const float4 &a_kEnd , const float &a_fTime)
{
	float4 kResult;
	kResult.X = a_kBegin.X + (a_fTime*(a_kEnd.X - a_kBegin.X));
	kResult.Y = a_kBegin.Y + (a_fTime*(a_kEnd.Y - a_kBegin.Y));
	kResult.Z = a_kBegin.Z + (a_fTime*(a_kEnd.Z - a_kBegin.Z));
	kResult.W = a_kBegin.W + (a_fTime*(a_kEnd.W - a_kBegin.W));
	return kResult;
}

//////////////////////////////////////////////////////////////////////////
float4 float4::operator + ( const float4 &a_kVec)
{
	return float4(X + a_kVec.X , Y + a_kVec.Y , Z + a_kVec.Z , W + a_kVec.W);
}

//////////////////////////////////////////////////////////////////////////
float4 float4::operator - (const float4 &a_kVec)
{
	return float4(X - a_kVec.X , Y - a_kVec.Y , Z - a_kVec.Z , W - a_kVec.W);
}

//////////////////////////////////////////////////////////////////////////
float4 float4::operator * ( const float4 &a_kVec)
{
	return float4(X * a_kVec.X , Y * a_kVec.Y , Z * a_kVec.Z , W * a_kVec.W);
}

//////////////////////////////////////////////////////////////////////////
float4 float4::operator / ( const float4 &a_kVec)
{
	return float4(X / a_kVec.X , Y / a_kVec.Y , Z / a_kVec.Z , W / a_kVec.W);
}

//////////////////////////////////////////////////////////////////////////
float4 float4::operator * ( const float &a_fValue)
{
	return float4(X * a_fValue , Y * a_fValue , Z * a_fValue , W * a_fValue);
}

//////////////////////////////////////////////////////////////////////////
float4 float4::operator / ( const float &a_fValue)
{
	return float4(X / a_fValue , Y / a_fValue , Z / a_fValue , W / a_fValue);
}

//////////////////////////////////////////////////////////////////////////
void float4::operator += ( const float4 &a_kVec)
{
	X += a_kVec.X;
	Y += a_kVec.Y;
	Z += a_kVec.Z;
	W += a_kVec.W;
}

//////////////////////////////////////////////////////////////////////////
void float4::operator -= ( const float4 &a_kVec)
{
	X -= a_kVec.X;
	Y -= a_kVec.Y;
	Z -= a_kVec.Z;
	W -= a_kVec.W;
}

//////////////////////////////////////////////////////////////////////////
void float4::operator *= ( const float4 &a_kVec)
{
	X *= a_kVec.X;
	Y *= a_kVec.Y;
	Z *= a_kVec.Z;
	W *= a_kVec.W;
}

//////////////////////////////////////////////////////////////////////////
void float4::operator /= (const float4 &a_kVec)
{
	X /= a_kVec.X;
	Y /= a_kVec.Y;
	Z /= a_kVec.Z;
	W /= a_kVec.W;
}

//////////////////////////////////////////////////////////////////////////
void float4::operator *= (const float &a_fValue)
{
	X *= a_fValue;
	Y *= a_fValue;
	Z *= a_fValue;
	W *= a_fValue;
}

//////////////////////////////////////////////////////////////////////////
void float4::operator /= (const float &a_fValue)
{
	X /= a_fValue;
	Y /= a_fValue;
	Z /= a_fValue;
	W /= a_fValue;
}

//////////////////////////////////////////////////////////////////////////
float4 float4::operator - ()
{
	return float4(-X,-Y,-Z,-W);	
}

//////////////////////////////////////////////////////////////////////////
bool float4::operator != (const float4 &a_kVec)
{
	if(X == a_kVec.X && ( Y == a_kVec.Y && ( Z == a_kVec.Z && W == a_kVec.W ) ) )
		return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool float4::operator == (const float4 &a_kVec)
{
	if(X == a_kVec.X && ( Y == a_kVec.Y && ( Z == a_kVec.Z && W == a_kVec.W ) ) )
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
void float4::operator = ( const float4 &a_kVec)
{
	X = a_kVec.X;
	Y = a_kVec.Y;
	Z = a_kVec.Z;
	W = a_kVec.W;
}

//////////////////////////////////////////////////////////////////////////
bool float4::operator > (const float4 &a_kVec)
{
	if(Length() > a_kVec.Length())
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
bool float4::operator < (const float4 &a_kVec)
{
	if(Length() < a_kVec.Length())
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
