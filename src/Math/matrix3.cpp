//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 13/12/2012 >
/// < File >	< matrix3 >
/// < Brief >	< Matrix 3 class implementation used for 2D objects mainly >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "matrix3.h"
#include <math.h>
#include "Quaternion.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
matrix3::matrix3()
{

}
//////////////////////////////////////////////////////////////////////////
matrix3::matrix3(float3 a_kRowX , float3 a_kRowY , float3 a_kRowZ)
	:m_kRowX(a_kRowX) , m_kRowY(a_kRowY) , m_kRowZ(a_kRowZ)
{

}

//////////////////////////////////////////////////////////////////////////
matrix3::matrix3(float a_f00 , float a_f01 , float a_f02 , float a_f10 , float a_f11 , float a_f12 , float a_f20 , float a_f21 , float a_f22 )
	:m_kRowX(float3(a_f00 , a_f01 , a_f02)) , m_kRowY(float3(a_f10, a_f11 , a_f12)) , m_kRowZ(float3(a_f20 , a_f21 , a_f22))
{

}

//////////////////////////////////////////////////////////////////////////
//matrix3::matrix3(float2 a_kTransform , float a_fRotation , float a_fScale)
//	:m_f02(a_kTransform.X) , m_f12(a_kTransform.Y) , m_f00(a_fScale) , m_f11(a_fScale) , m_f22(a_fScale) , 
//{
//
//	m_f01 m_f10 // rotations
//	m_f20 m_f21 // useless
//
//}

//////////////////////////////////////////////////////////////////////////
matrix3::~matrix3()
{

}

//////////////////////////////////////////////////////////////////////////
matrix3 matrix3::CreateIdentity()
{
	matrix3 kResult;
	kResult.m_f00 = 1; kResult.m_f01 = 0; kResult.m_f02 = 0;
	kResult.m_f10 = 0; kResult.m_f11 = 1; kResult.m_f12 = 0;
	kResult.m_f20 = 0; kResult.m_f21 = 0; kResult.m_f22 = 1;
	return kResult;
}

//////////////////////////////////////////////////////////////////////////
matrix3::matrix3(const matrix3& a_kMat)
	:m_kRowX(a_kMat.m_kRowX) , m_kRowY(a_kMat.m_kRowY) , m_kRowZ(a_kMat.m_kRowZ)
{

}

void matrix3::operator = (const matrix3 &a_kMat)
{
	for(int i = 0; i < 9; ++i)
	{
		m_afData1D[i] = a_kMat.m_afData1D[i];
	}
}

//////////////////////////////////////////////////////////////////////////
matrix3 matrix3::operator * (const matrix3& a_kMat) const
{
	// pass in child element. result = this * child matrix. gives world matrix of child. 
	matrix3 kResult;
	// X row;
	kResult.m_f00 = 
		m_f00 * a_kMat.m_f00 + 
		m_f01 * a_kMat.m_f10 + 
		m_f02 * a_kMat.m_f20;

	kResult.m_f01 =
		m_f00 * a_kMat.m_f01 +
		m_f01 * a_kMat.m_f11 +
		m_f02 * a_kMat.m_f21;

	kResult.m_f02 =
		m_f00 * a_kMat.m_f02 +
		m_f01 * a_kMat.m_f12 +
		m_f02 * a_kMat.m_f22;

	// Y Row
	kResult.m_f10 = 
		m_f10 * a_kMat.m_f00 +
		m_f11 * a_kMat.m_f10 +
		m_f12 * a_kMat.m_f20;

	kResult.m_f11 = 
		m_f10 * a_kMat.m_f01 +
		m_f11 * a_kMat.m_f11 +
		m_f12 * a_kMat.m_f21;

	kResult.m_f12 = 
		m_f10 * a_kMat.m_f02 +
		m_f11 * a_kMat.m_f12 +
		m_f12 * a_kMat.m_f22;

	// Z Row
	kResult.m_f20 =
		m_f20 * a_kMat.m_f00 +
		m_f21 * a_kMat.m_f10 +
		m_f22 * a_kMat.m_f20;

	kResult.m_f21 =
		m_f20 * a_kMat.m_f01 +
		m_f21 * a_kMat.m_f11 +
		m_f22 * a_kMat.m_f21;

	kResult.m_f22 =
		m_f20 * a_kMat.m_f02 +
		m_f21 * a_kMat.m_f12 +
		m_f22 * a_kMat.m_f22;

	return kResult;
}

//////////////////////////////////////////////////////////////////////////
matrix3 matrix3::operator * (const float &a_fScale ) const
{
	matrix3 kResult = (*this);
	kResult.m_f00 *= a_fScale;
	kResult.m_f01 *= a_fScale;
	kResult.m_f02 *= a_fScale;
	kResult.m_f10 *= a_fScale;
	kResult.m_f11 *= a_fScale;
	kResult.m_f12 *= a_fScale;
	kResult.m_f22 *= a_fScale;
	kResult.m_f20 *= a_fScale;
	kResult.m_f21 *= a_fScale;
	
	return kResult;
}

//////////////////////////////////////////////////////////////////////////
float2 matrix3::operator * (const float2 &a_kVec) const
{
	float2 kResult;
	kResult.X = a_kVec.X * m_f00 + a_kVec.Y * m_f10;
	kResult.Y = a_kVec.X * m_f01 + a_kVec.Y * m_f11;
	return kResult;
}

//////////////////////////////////////////////////////////////////////////
float3 matrix3::operator * (const float3 &a_kVec) const
{
	float3 kResult;
	kResult.X = a_kVec.X * m_f00 + a_kVec.Y * m_f10 + a_kVec.Z * m_f20;
	kResult.Y = a_kVec.X * m_f01 + a_kVec.Y * m_f11 + a_kVec.Z * m_f21;
	kResult.Z = a_kVec.X * m_f02 + a_kVec.Y * m_f12 + a_kVec.Z * m_f22;
	return kResult;
}

//////////////////////////////////////////////////////////////////////////
void matrix3::Set(float a_f00 , float a_f01 , float a_f02 , float a_f10 , float a_f11 , float a_f12 , float a_f20 , float a_f21 , float a_f22 )
{
	m_f00 = a_f00;
	m_f01 = a_f01;
	m_f02 = a_f02;

	m_f10 = a_f10;
	m_f11 = a_f11;
	m_f12 = a_f12;

	m_f20 = a_f20;
	m_f21 = a_f21;
	m_f22 = a_f22;

}

void matrix3::MakeXRotate(float a_fTheta)
{
	float c = cosf(a_fTheta);
	float s = sinf(a_fTheta);

	m_f00 = 1; m_f01 = 0; m_f02 = 0;
	m_f10 = 0; m_f11 = c; m_f12 = s;
	m_f20 = 0; m_f21 = -s; m_f22 = c;
}

void matrix3::MakeYRotate(float a_fTheta)
{
	float c = cosf(a_fTheta);
	float s = sinf(a_fTheta);

	m_f00 = c; m_f01 = 0; m_f02 = s;
	m_f10 = 0; m_f11 = 1; m_f12 = 0;
	m_f20 = -s; m_f21 = 0; m_f22 = c;
}

void matrix3::MakeZRotate(float a_fTheta)
{
	float c = cosf(a_fTheta);
	float s = sinf(a_fTheta);

	m_f00 = c; m_f01 = s; m_f02 = 0;
	m_f10 = -s; m_f11 = c; m_f12 = 0;
	m_f20 = 0; m_f21 = 0; m_f22 = 1;
}

void matrix3::CreateTranslation(const float a_fX , const float a_fY )
{
	(*this) = CreateIdentity();
	m_f02 = a_fX;
	m_f12 = a_fY;
}

void matrix3::CreateScale(const float a_fScale)
{
	(*this) = CreateIdentity();
	m_f00 = a_fScale;
	m_f11 = a_fScale;
	m_f22 = a_fScale;
}

matrix3 matrix3::CreateRotation(const float3 a_kAxis , float a_fAngle)
{
	Quaternion oQuat;
	oQuat = Quaternion::FromAxisAngle(a_kAxis,a_fAngle);
	matrix3 mReturn;
	oQuat.ToMatrix3(mReturn);
	return mReturn;
}


float matrix3::GetScale()
{
	return m_f00;
}

