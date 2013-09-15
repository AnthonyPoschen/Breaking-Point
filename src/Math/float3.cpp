//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 5/12/2012 >
/// < File >	< float3 >
/// < Brief >	< Float3 Math class >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "float3.h"
#include "CoreMath.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >

//////////////////////////////////////////////////////////////////////////
float3::float3()
	:X(0),Y(0),Z(0)
{

}

//////////////////////////////////////////////////////////////////////////
float3::float3(float a_fX, float a_fY, float a_fZ)
	:X(a_fX),Y(a_fY),Z(a_fZ)
{

}

//////////////////////////////////////////////////////////////////////////
float3::float3(const float3 &a_kVec)
	:X(a_kVec.X),Y(a_kVec.Y),Z(a_kVec.Z)
{

}

//////////////////////////////////////////////////////////////////////////
float3::~float3()
{

}

//////////////////////////////////////////////////////////////////////////
float float3::Length() const
{
	return bzSqrt(X * X + Y * Y + Z * Z);
}

//////////////////////////////////////////////////////////////////////////
float float3::SqrLength() const
{
	return (X * X + Y * Y + Z * Z);
}

//////////////////////////////////////////////////////////////////////////
float3 float3::Cross(const float3 &a_kFloat3) const
{
	// X = aY * bZ - aZ * bY
	// Y = aZ * bX - aX * bZ
	// Z = aX * bY - aY * bX
	float3 kResult;
	kResult.X = Y * a_kFloat3.Z - Z * a_kFloat3.Y;
	kResult.Y = Z * a_kFloat3.X - X * a_kFloat3.Z;
	kResult.Z = X * a_kFloat3.Y - Y * a_kFloat3.X;
	return kResult;
}

//////////////////////////////////////////////////////////////////////////
float float3::Dot(const float3 &a_kFloat3) const
{
	return ((X * a_kFloat3.X) + (Y * a_kFloat3.Y) + (Z * a_kFloat3.Z));
}

//////////////////////////////////////////////////////////////////////////
float3 float3::OffSetFrom(const float3 &a_kPointOfInterest) const
{
	float3 kResult;
	kResult = a_kPointOfInterest - *this;
	if(a_kPointOfInterest.X > X)
		kResult.X = -kResult.X;
	if(a_kPointOfInterest.Y > Y)
		kResult.Y = -kResult.Y;
	if(a_kPointOfInterest.Z > Z)
		kResult.Z = -kResult.Z;
	return kResult;
}

//////////////////////////////////////////////////////////////////////////
float float3::Unitise()
{
	float fSum = X + Y + Z;
	if(X < 0)
		fSum -= X*2;
	if(Y < 0)
		fSum -= Y*2;
	if(Z < 0)
		fSum -= Z*2;
	X /= fSum;
	Y /= fSum;
	Z /= fSum;
	return fSum;
}

//////////////////////////////////////////////////////////////////////////
float float3::UnitiseVector(float3 &a_kFloat3)
{
	float fSum = a_kFloat3.X + a_kFloat3.Y + a_kFloat3.Z;
	a_kFloat3.X /= fSum;
	a_kFloat3.Y /= fSum;
	a_kFloat3.Z /= fSum;
	return fSum;
}

//////////////////////////////////////////////////////////////////////////
float3 float3::Lerp(const float3 &a_kBegin, const float3 &a_kEnd, const float a_fTime )
{
	float3 kResult;
	kResult.X = a_kBegin.X + (a_fTime*(a_kEnd.X - a_kBegin.X));
	kResult.Y = a_kBegin.Y + (a_fTime*(a_kEnd.Y - a_kBegin.Y));
	kResult.Z = a_kBegin.Z + (a_fTime*(a_kEnd.Z - a_kBegin.Z));
	return kResult;
}

//////////////////////////////////////////////////////////////////////////
float3 float3::operator + (const float3 &a_kVec) const
{
	return float3(X + a_kVec.X, Y + a_kVec.Y, Z + a_kVec.Z);
}

//////////////////////////////////////////////////////////////////////////
float3 float3::operator - (const float3 &a_kVec) const
{
	return float3(X - a_kVec.X, Y - a_kVec.Y, Z - a_kVec.Z);
}

//////////////////////////////////////////////////////////////////////////
float3 float3::operator * (const float3 &a_kVec) const
{
	return float3(X * a_kVec.X, Y * a_kVec.Y, Z * a_kVec.Z);
}

//////////////////////////////////////////////////////////////////////////
float3 float3::operator / (const float3 &a_kVec) const
{
	return float3(X / a_kVec.X , Y / a_kVec.Y , Z / a_kVec.Z);
}

//////////////////////////////////////////////////////////////////////////
float3 float3::operator * (const float &a_fValue) const
{
	return float3(X * a_fValue , Y * a_fValue , Z * a_fValue );
}

//////////////////////////////////////////////////////////////////////////
float3 float3::operator / (const float &a_fValue) const
{
	return float3(X / a_fValue, Y / a_fValue , Z / a_fValue );
}

//////////////////////////////////////////////////////////////////////////
void float3::operator += ( const float3 &a_kVec)
{
	X += a_kVec.X;
	Y += a_kVec.Y;
	Z += a_kVec.Z;
}

//////////////////////////////////////////////////////////////////////////
void float3::operator -= (const float3 &a_kVec)
{
	X -= a_kVec.X;
	Y -= a_kVec.Y;
	Z -= a_kVec.Z;
}

//////////////////////////////////////////////////////////////////////////
void float3::operator *= (const float3 &a_kVec)
{
	X *= a_kVec.X;
	Y *= a_kVec.Y;
	Z *= a_kVec.Z;
}

//////////////////////////////////////////////////////////////////////////
void float3::operator /= (const float3 &a_kVec)
{
	X /= a_kVec.X;
	Y /= a_kVec.Y;
	Z /= a_kVec.Z;
}

//////////////////////////////////////////////////////////////////////////
void float3::operator *= (const float &a_fValue )
{
	X *= a_fValue;
	Y *= a_fValue;
	Z *= a_fValue;
}

//////////////////////////////////////////////////////////////////////////
void float3::operator /= ( const float &a_fValue )
{
	X /= a_fValue;
	Y /= a_fValue;
	Z /= a_fValue;
}

//////////////////////////////////////////////////////////////////////////
float3 float3::operator - ()
{
	return float3(-X,-Y,-Z);
}

//////////////////////////////////////////////////////////////////////////
bool float3::operator != (const float3 &a_kVec) const
{
	if(X == a_kVec.X && (Y == a_kVec.Y && Z == a_kVec.Z))
		return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool float3::operator == (const float3 &a_kVec) const
{
	if(X == a_kVec.X && (Y == a_kVec.Y && Z == a_kVec.Z))
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
void float3::operator = (const float3 &a_kVec)
{
	X = a_kVec.X;
	Y = a_kVec.Y;
	Z = a_kVec.Z;
}

//////////////////////////////////////////////////////////////////////////
bool float3::operator > (const float3 &a_kVec) const
{
	if(this->Length() > a_kVec.Length())
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
bool float3::operator < (const float3 &a_kVec) const
{
	if(this->Length() < a_kVec.Length())
		return true;
	return false;
}

