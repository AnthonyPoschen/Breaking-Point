//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 11 - 12 - 2012 >
/// < Class Brief >	< matrix4 class. used for 3D elements.   >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _MATRIX4_H_
#define _MATRIX4_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "CoreMath.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class matrix4
{
public:
	matrix4();
	~matrix4();
	matrix4(const matrix4& a_kMat);
	matrix4(float a_f00 , float a_f01 , float a_f02 , float a_f03 , 
			float a_f10 , float a_f11 , float a_f12 , float a_f13 , 
			float a_f20 , float a_f21 , float a_f22 , float a_f23 ,
			float a_f30 , float a_f31 , float a_f32 , float a_f33 );
	matrix4(float4 a_kRowX , float4 a_kRowY , float4 a_kRowZ , float4 a_kRowW);

	union 
	{
		struct
		{
			float m_f00;
			float m_f01;
			float m_f02;
			float m_f03;

			float m_f10;
			float m_f11;
			float m_f12;
			float m_f13;

			float m_f20;
			float m_f21;
			float m_f22;
			float m_f23;

			float m_f30;
			float m_f31;
			float m_f32;
			float m_f33;
		};
		struct
		{
			float4 m_kRowX;
			float4 m_kRowY;
			float4 m_kRowZ;
			float4 m_kRowW;
		};
		float m_m[4][4];
		float m_v[16];
	};
	void Transpose();
	static void MakeIdentity(matrix4& a_kMat);
	void MakeXRotate(float a_fTheta);
	void MakeYRotate(float a_fTheta);
	void MakeZRotate(float a_fTheta);
	static void MakeScaleMatrix(matrix4& a_kMat, float a_fScale);
	static void MakeTranslateMatrix(matrix4& a_kMat , float3 a_kTransLate);
	static void MakeRotate(matrix4& a_kResult ,const matrix3& a_kRotation);
	void Set(float a_f00 , float a_f01 , float a_f02 , float a_f03 , 
		float a_f10 , float a_f11 , float a_f12 , float a_f13 , 
		float a_f20 , float a_f21 , float a_f22 , float a_f23 , 
		float a_f30 , float a_f31 , float a_f32 , float a_f33 );

	void operator = (const matrix4 &a_kMat);
	matrix4 operator * ( const matrix4 &a_kMat);
	matrix4 operator * (const float &a_fScale);
	float3 operator * (const float3 &a_kVec);

protected:
	

private:

};
//////////////////////////////////////////////////////////////////////////
#endif // _MATRIX4_H_
//////////////////////////////////////////////////////////////////////////
