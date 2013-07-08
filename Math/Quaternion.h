//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 1 - 2 - 2013 >
/// < Class Brief >	< Quaternion class for messuring angles and caluating rotations without gimbal lock  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _QUATERNION_H_
#define _QUATERNION_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "float3.h"
#include "matrix3.h"
#include "matrix4.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class Quaternion
{
public:

	Quaternion();
	Quaternion(float a_fReal , float a_fX , float a_fY , float a_fZ);
	Quaternion(float a_fReal , const float3 &a_kVec);
	// from euler angles
	Quaternion(float a_fEulerX , float a_fEulerY , float a_fEulerZ);
	Quaternion(const float3 &a_kEulerAngles);
	~Quaternion();
	 

	float Length();
	float LengthSquared();
	void Normalise();
	Quaternion Normalised();
	void ToMatrix3(matrix3 &a_kMat);
	void ToMatrix4(matrix4 &a_kMat);
	float3 GetEulerAngles(bool homogenous = true);
	void ToAxisAngle(float3 &a_vAxis , float &a_fAngle);


	// static functions
	static float Dot(const Quaternion &a_kQ1 , const Quaternion &a_kQ2);
	static Quaternion Lerp(const Quaternion &a_kQ1 , const Quaternion &a_kQ2 , float t);
	static Quaternion Slerp(const Quaternion &a_kQ1 , const Quaternion &a_kQ2, float t);
	static Quaternion SlerpNoInvert(const Quaternion &a_kQ1 , const Quaternion &a_kQ2 , float t);
	static Quaternion FromAxisAngle(const float3 &a_vAxis , float a_fAngle);
	


	// Operators
	void operator = (const Quaternion &a_kQuat);
	Quaternion operator + (const Quaternion &a_kQuat);
	Quaternion operator - (const Quaternion &a_kQuat);
	Quaternion operator * (const Quaternion &a_kQuat);
	Quaternion operator / (const Quaternion &a_kQuat);
	Quaternion operator * (float a_fScale) const;
	Quaternion operator / (float a_fScale);
	Quaternion operator - ();

	void operator += (const Quaternion &a_kQuat);
	void operator -= (const Quaternion &a_kQuat);
	void operator *= (const Quaternion &a_kQuat);
	void operator *= (float a_fScale);
	void operator /= (float a_fScale);

protected:
	

private:
	void Conjugate();
	void Invert();
	union
	{
		struct
		{
			float    s; //!< the real component
			float3   v; //!< the imaginary components
		};
		struct
		{ 
			float elem[4]; //! the raw elements of the quaternion
		}; 
	};
};
//////////////////////////////////////////////////////////////////////////
#endif // _QUATERNION_H_
//////////////////////////////////////////////////////////////////////////
