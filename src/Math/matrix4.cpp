//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 14/12/2012 >
/// < File >	< matrix4 >
/// < Brief >	< Matrix4 implementation >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "CoreMath.h"
#include "matrix4.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
matrix4::matrix4()
{

}

//////////////////////////////////////////////////////////////////////////
matrix4::matrix4(float4 a_kRowX , float4 a_kRowY , float4 a_kRowZ , float4 a_kRowW)
	:m_kRowX(a_kRowX) , m_kRowY(a_kRowY) , m_kRowZ(a_kRowZ) , m_kRowW(a_kRowW)
{

}

//////////////////////////////////////////////////////////////////////////
matrix4::matrix4(float a_f00 , float a_f01 , float a_f02 , float a_f03 , float a_f10 , float a_f11 , float a_f12 , float a_f13 , float a_f20 , float a_f21 , float a_f22 , float a_f23 , float a_f30 , float a_f31 , float a_f32 , float a_f33 )
	:m_f00(a_f00) , m_f01(a_f01) , m_f02(a_f02) , m_f03(a_f03) ,
	 m_f10(a_f10) , m_f11(a_f11) , m_f12(a_f12) , m_f13(a_f13) ,
	 m_f20(a_f20) , m_f21(a_f21) , m_f22(a_f22) , m_f23(a_f23) , 
	 m_f30(a_f30) , m_f31(a_f31) , m_f32(a_f32) , m_f33(a_f33)
{

}

//////////////////////////////////////////////////////////////////////////
matrix4::matrix4(const matrix4& a_kMat)
{
	(*this) = a_kMat;
}

//////////////////////////////////////////////////////////////////////////
matrix4::~matrix4()
{

}
//////////////////////////////////////////////////////////////////////////
void matrix4::MakeIdentity(matrix4& a_kMat)
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			if(i == j)
			{
				a_kMat.m_m[i][j] = 1;
			}
			else
				a_kMat.m_m[i][j] = 0;
		}
	}
}


void matrix4::MakeXRotate(float a_fTheta)
{
	float c = cosf(a_fTheta);
	float s = sinf(a_fTheta);

	m_f00 = 1; m_f01 = 0;  m_f02 = 0; m_f03 = 0;
	m_f10 = 0; m_f11 = c;  m_f12 = s; m_f13 = 0;
	m_f20 = 0; m_f21 = -s; m_f22 = c; m_f23 = 0;
	m_f30 = 0; m_f31 = 0;  m_f32 = 0; m_f33 = 1;
}

void matrix4::MakeYRotate(float a_fTheta)
{
	float c = cosf(a_fTheta);
	float s = sinf(a_fTheta);

	m_f00 = c;  m_f01 = 0; m_f02 = s; m_f03 = 0;
	m_f10 = 0;  m_f11 = 1; m_f12 = 0; m_f13 = 0;
	m_f20 = -s; m_f21 = 0; m_f22 = c; m_f23 = 0;
	m_f30 = 0;  m_f31 = 0; m_f32 = 0; m_f33 = 1;
}

void matrix4::MakeZRotate(float a_fTheta)
{
	float c = cosf(a_fTheta);
	float s = sinf(a_fTheta);

	m_f00 = c;  m_f01 = s; m_f02 = 0; m_f03 = 0;
	m_f10 = -s; m_f11 = c; m_f12 = 0; m_f13 = 0;
	m_f20 = 0;  m_f21 = 0; m_f22 = 1; m_f23 = 0;
	m_f30 = 0;  m_f31 = 0; m_f32 = 0; m_f33 = 1;
}

void matrix4::Set(float a_f00 , float a_f01 , float a_f02 , float a_f03 , float a_f10 , float a_f11 , float a_f12 , float a_f13 , float a_f20 , float a_f21 , float a_f22 , float a_f23 , float a_f30 , float a_f31 , float a_f32 , float a_f33 )
{
	m_f00 = a_f00; m_f01 = a_f01; m_f02 = a_f02; m_f03 = a_f03;
	m_f10 = a_f10; m_f11 = a_f11; m_f12 = a_f12; m_f03 = a_f13;
	m_f20 = a_f20; m_f21 = a_f21; m_f22 = a_f22; m_f23 = a_f23;
	m_f30 = a_f30; m_f31 = a_f31; m_f32 = a_f32; m_f33 = a_f33;
}

void matrix4::operator = (const matrix4 & a_kMat)
{
	for(int i = 0; i < 16; ++i)
	{
		m_v[i] = a_kMat.m_v[i];
	}
}

matrix4 matrix4::operator * (const matrix4 &a_kMat)
{
	matrix4 kResult;
	// X row
	kResult.m_f00 = 
		m_f00 * a_kMat.m_f00 +
		m_f01 * a_kMat.m_f10 +
		m_f02 * a_kMat.m_f20 +
		m_f03 * a_kMat.m_f30;

	kResult.m_f01 = 
		m_f00 * a_kMat.m_f01 +
		m_f01 * a_kMat.m_f11 +
		m_f02 * a_kMat.m_f21 +
		m_f03 * a_kMat.m_f31;

	kResult.m_f02 = 
		m_f00 * a_kMat.m_f02 +
		m_f01 * a_kMat.m_f12 +
		m_f02 * a_kMat.m_f22 +
		m_f03 * a_kMat.m_f32;

	kResult.m_f03 = 
		m_f00 * a_kMat.m_f03 +
		m_f01 * a_kMat.m_f13 +
		m_f02 * a_kMat.m_f23 +
		m_f03 * a_kMat.m_f33;

	// Y row
	kResult.m_f10 = 
		m_f10 * a_kMat.m_f00 +
		m_f11 * a_kMat.m_f10 +
		m_f12 * a_kMat.m_f20 +
		m_f13 * a_kMat.m_f30;

	kResult.m_f11 = 
		m_f10 * a_kMat.m_f01 +
		m_f11 * a_kMat.m_f11 +
		m_f12 * a_kMat.m_f21 +
		m_f13 * a_kMat.m_f31;

	kResult.m_f12 =
		m_f10 * a_kMat.m_f02 +
		m_f11 * a_kMat.m_f12 +
		m_f12 * a_kMat.m_f22 +
		m_f13 * a_kMat.m_f32;

	kResult.m_f13 =
		m_f10 * a_kMat.m_f03 +
		m_f11 * a_kMat.m_f13 +
		m_f12 * a_kMat.m_f23 +
		m_f13 * a_kMat.m_f33;

	// Z row
	kResult.m_f20 =
		m_f20 * a_kMat.m_f00 +
		m_f21 * a_kMat.m_f10 +
		m_f22 * a_kMat.m_f20 +
		m_f23 * a_kMat.m_f30;

	kResult.m_f21 =
		m_f20 * a_kMat.m_f01 +
		m_f21 * a_kMat.m_f11 +
		m_f22 * a_kMat.m_f21 +
		m_f23 * a_kMat.m_f31;

	kResult.m_f22 =
		m_f20 * a_kMat.m_f02 +
		m_f21 * a_kMat.m_f12 +
		m_f22 * a_kMat.m_f22 +
		m_f23 * a_kMat.m_f32;

	kResult.m_f23 =
		m_f20 * a_kMat.m_f03 +
		m_f21 * a_kMat.m_f13 +
		m_f22 * a_kMat.m_f23 +
		m_f23 * a_kMat.m_f33;

	// W row

	kResult.m_f30 =
		m_f30 * a_kMat.m_f00 +
		m_f31 * a_kMat.m_f10 +
		m_f32 * a_kMat.m_f20 +
		m_f33 * a_kMat.m_f30;

	kResult.m_f31 =
		m_f30 * a_kMat.m_f01 +
		m_f31 * a_kMat.m_f11 +
		m_f32 * a_kMat.m_f21 +
		m_f33 * a_kMat.m_f31;

	kResult.m_f32 =
		m_f30 * a_kMat.m_f02 +
		m_f31 * a_kMat.m_f12 + 
		m_f32 * a_kMat.m_f22 +
		m_f33 * a_kMat.m_f32;

	kResult.m_f33 =
		m_f30 * a_kMat.m_f03 +
		m_f31 * a_kMat.m_f13 +
		m_f32 * a_kMat.m_f23 +
		m_f33 * a_kMat.m_f33;

	return kResult;
}

matrix4 matrix4::operator * (const float &a_fScale)
{
	matrix4 kResult = (*this);
	kResult.m_f00 *= a_fScale;
	kResult.m_f01 *= a_fScale;
	kResult.m_f02 *= a_fScale;
	
	kResult.m_f10 *= a_fScale;
	kResult.m_f11 *= a_fScale;
	kResult.m_f12 *= a_fScale;

	kResult.m_f20 *= a_fScale;
	kResult.m_f21 *= a_fScale;
	kResult.m_f22 *= a_fScale;
	
	return kResult;
}

void matrix4::MakeScaleMatrix(matrix4& a_kMat, float a_fScale)
{
	matrix4::MakeIdentity(a_kMat);
	a_kMat.m_f00 = a_fScale;
	a_kMat.m_f11 = a_fScale;
	a_kMat.m_f22 = a_fScale;
	a_kMat.m_f33 = 1.0f;
}

void matrix4::MakeTranslateMatrix(matrix4& a_kMat , float3 a_kTransLate)
{
	MakeIdentity(a_kMat);
	a_kMat.m_m[0][3] = a_kTransLate.X;
	a_kMat.m_m[1][3] = a_kTransLate.Y;
	a_kMat.m_m[2][3] = a_kTransLate.Z;
}

void matrix4::MakeRotate(matrix4& a_kResult ,const matrix3& a_kRotation)
{
	MakeIdentity(a_kResult);
	a_kResult.m_f00 = a_kRotation.m_f00;
	a_kResult.m_f01 = a_kRotation.m_f01;
	a_kResult.m_f02 = a_kRotation.m_f02;

	a_kResult.m_f10 = a_kRotation.m_f10;
	a_kResult.m_f11 = a_kRotation.m_f11;
	a_kResult.m_f12 = a_kRotation.m_f12;

	a_kResult.m_f20 = a_kRotation.m_f20;
	a_kResult.m_f21 = a_kRotation.m_f21;
	a_kResult.m_f22 = a_kRotation.m_f22;
}

float3 matrix4::operator*(const float3& a_kVec)
{
	float3 kResult; // row vector
	kResult.X = 
		m_f00 * a_kVec.X +
		m_f10 * a_kVec.X +
		m_f20 * a_kVec.X +
		m_f30 * a_kVec.X;

	kResult.Y = 
		m_f01 * a_kVec.Y +
		m_f11 * a_kVec.Y +
		m_f21 * a_kVec.Y +
		m_f31 * a_kVec.Y;

	kResult.Z = 
		m_f02 * a_kVec.Z +
		m_f12 * a_kVec.Z +
		m_f22 * a_kVec.Z +
		m_f32 * a_kVec.Z;

	return kResult;
}

void matrix4::Transpose()
{
	float ftmp;
	ftmp = m_f01;
	m_f01 = m_f10;
	m_f10 = ftmp;

	ftmp = m_f02;
	m_f02 = m_f20;
	m_f20 = ftmp;

	ftmp = m_f03;
	m_f03 = m_f30;
	m_f30 = ftmp;

	ftmp = m_f12;
	m_f12 = m_f21;
	m_f21 = ftmp;

	ftmp = m_f13;
	m_f13 = m_f31;
	m_f31 = ftmp;

	ftmp = m_f23;
	m_f23 = m_f32;
	m_f32 = ftmp;
}