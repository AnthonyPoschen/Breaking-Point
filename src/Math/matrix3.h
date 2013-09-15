//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 11 - 12 - 2012 >
/// < Class Brief >	< Matrix3x3 class stores rotation data only of 3D objects.  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _MATRIX3_H_
#define _MATRIX3_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "float2.h"
#include "float3.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >
class float2;
class float3;

//////////////////////////////////////////////////////////////////////////
class matrix3
{
public:
	// only use this matrix class for Rotational Data;
	friend class Quaternion;
	matrix3();
	static matrix3 CreateIdentity();
	void CreateTranslation(const float a_fX , const float a_fY);
	void CreateScale(const float a_fScale);
	static matrix3 CreateRotation(const float3 a_kAngle , float a_fAngle);
	float GetScale();
	matrix3(const matrix3& a_kMat);
	matrix3(float a_f00 , float a_f01 , float a_f02 ,
			float a_f10 , float a_f11 , float a_f12 , 
			float a_f20 , float a_f21 , float a_f22 );
	matrix3(float3 a_kRowX , float3 a_kRowY , float3 a_kRowZ);
	//matrix3(float2 a_kTransform , flaot a_fRotation , float a_fScale);
	~matrix3();
	void Set(float a_f00 , float a_f01 , float a_f02 ,
		float a_f10 , float a_f11 , float a_f12 , 
		float a_f20 , float a_f21 , float a_f22 );

	void operator = (const matrix3 &a_kMat);
	matrix3 operator * ( const matrix3 &a_kMat) const;
	matrix3 operator * (const float &a_fScale ) const;
	float2 operator * (const float2 &a_kVec) const;
	float3 operator * (const float3 &a_kVec) const;
protected:
	

private:
	union 
	{
		struct  
		{
			float m_f00;
			float m_f01;
			float m_f02;

			float m_f10;
			float m_f11;
			float m_f12;

			float m_f20;
			float m_f21;
			float m_f22;
		};
		struct 
		{
			float3 m_kRowX;
			float3 m_kRowY;
			float3 m_kRowZ;
		};
		float m_afData2D[3][3];
		float m_afData1D[9];


	};

	void MakeXRotate(float a_fTheta);
	void MakeYRotate(float a_fTheta);
	void MakeZRotate(float a_fTheta);
};
//////////////////////////////////////////////////////////////////////////
#endif // _MATRIX3_H_
//////////////////////////////////////////////////////////////////////////
