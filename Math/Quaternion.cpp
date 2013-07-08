//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 1/2/2013 >
/// < File >	< Quaternion >
/// < Brief >	< Quaternion class implementation >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "Quaternion.h"

//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
Quaternion::Quaternion()
	:s(0),v(float3(0.0f,0.0f,0.0f))
{

}

//////////////////////////////////////////////////////////////////////////
Quaternion::Quaternion(float a_fReal , float a_fX , float a_fY , float a_fZ)
	:s(a_fReal),v(a_fX,a_fY,a_fZ)
{

}

//////////////////////////////////////////////////////////////////////////
Quaternion::Quaternion(float a_fReal , const float3 &a_kVec)
	:s(a_fReal),v(a_kVec)
{

}

//////////////////////////////////////////////////////////////////////////
Quaternion::Quaternion(float a_fEulerX , float a_fEulerY , float a_fEulerZ)
{
	float cos_z_2 = cosf(0.5f * a_fEulerZ);
	float cos_y_2 = cosf(0.5f * a_fEulerY);
	float cos_x_2 = cosf(0.5f * a_fEulerX);

	float sin_z_2 = sinf(0.5f * a_fEulerZ);
	float sin_y_2 = sinf(0.5f * a_fEulerY);
	float sin_x_2 = sinf(0.5f * a_fEulerX);

	s =   cos_z_2 * cos_y_2 * cos_x_2 + sin_z_2 * sin_y_2 * sin_x_2;
	v.X = cos_z_2 * cos_y_2 * sin_x_2 - sin_z_2 * sin_y_2 * cos_x_2;
	v.Y = cos_z_2 * sin_y_2 * cos_x_2 + sin_z_2 * cos_y_2 * sin_x_2;
	v.Z = sin_z_2 * cos_y_2 * cos_x_2 - cos_z_2 * sin_y_2 * sin_x_2;

}

//////////////////////////////////////////////////////////////////////////
Quaternion::Quaternion(const float3 &a_kEulerAngles)
{
	float cos_z_2 = cosf(0.5f * a_kEulerAngles.Z);
	float cos_y_2 = cosf(0.5f * a_kEulerAngles.Y);
	float cos_x_2 = cosf(0.5f * a_kEulerAngles.X);

	float sin_z_2 = sinf(0.5f * a_kEulerAngles.Z);
	float sin_y_2 = sinf(0.5f * a_kEulerAngles.Y);
	float sin_x_2 = sinf(0.5f * a_kEulerAngles.X);

	s =   cos_z_2 * cos_y_2 * cos_x_2 + sin_z_2 * sin_y_2 * sin_x_2;
	v.X = cos_z_2 * cos_y_2 * sin_x_2 - sin_z_2 * sin_y_2 * cos_x_2;
	v.Y = cos_z_2 * sin_y_2 * cos_x_2 + sin_z_2 * cos_y_2 * sin_x_2;
	v.Z = sin_z_2 * cos_y_2 * cos_x_2 - cos_z_2 * sin_y_2 * sin_x_2;
}

//////////////////////////////////////////////////////////////////////////
Quaternion::~Quaternion()
{

}

//////////////////////////////////////////////////////////////////////////
float Quaternion::Length()
{
	return (float)sqrt(s * s + v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}

//////////////////////////////////////////////////////////////////////////
float Quaternion::LengthSquared()
{
	return (float)(s * s + v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}

//////////////////////////////////////////////////////////////////////////
void Quaternion::Normalise()
{
	*this /= Length();
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::Normalised()
{
	return *this / Length();
}
//////////////////////////////////////////////////////////////////////////
void Quaternion::Conjugate()
{
	v = -v;
}

//////////////////////////////////////////////////////////////////////////
void Quaternion::Invert()
{
	Conjugate();
	*this /= LengthSquared();
}

//////////////////////////////////////////////////////////////////////////
void Quaternion::operator = (const Quaternion &a_kQuat)
{
	s = a_kQuat.s;
	v = a_kQuat.v;
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator + (const Quaternion &a_kQuat)
{
	return Quaternion(s + a_kQuat.s , v + a_kQuat.v);
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator - (const Quaternion &a_kQuat)
{
	return Quaternion(s - a_kQuat.s , v - a_kQuat.v);
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator * (const Quaternion &a_kQuat)
{
	return Quaternion(s * a_kQuat.s - (v.X * a_kQuat.v.X + v.Z * a_kQuat.v.X + v.Z * a_kQuat.v.Z),
			v.Y * a_kQuat.v.Z - v.Z * a_kQuat.v.Y + s * a_kQuat.v.X + v.X * a_kQuat.s,
			v.Z * a_kQuat.v.X - v.X * a_kQuat.v.Z + s * a_kQuat.v.Y + v.Y * a_kQuat.s,
			v.X * a_kQuat.v.Y - v.Y * a_kQuat.v.X + s * a_kQuat.v.Z + v.Z * a_kQuat.s);
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator / (const Quaternion &a_kQuat)
{
	Quaternion p(a_kQuat);
	p.Invert();
	return *this * p;
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator * (float a_fScale) const
{
	return Quaternion(s*a_fScale , (float3)v * a_fScale);
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator / (float a_fScale)
{
	return Quaternion(s*a_fScale , (float3)v * a_fScale);
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator - ()
{
	return Quaternion(-s , -v);
}

//////////////////////////////////////////////////////////////////////////
void Quaternion::operator += (const Quaternion &a_kQuat)
{
	s += a_kQuat.s;
	v += a_kQuat.v;
}

//////////////////////////////////////////////////////////////////////////
void Quaternion::operator -= (const Quaternion &a_kQuat)
{
	s -= a_kQuat.s;
	v -= a_kQuat.v;
}

//////////////////////////////////////////////////////////////////////////
void Quaternion::operator *= (const Quaternion &a_kQuat)
{
	float x = v.X, y = v.Y , z = v.Z , sn = s*a_kQuat.s - (v.X * a_kQuat.v.X + v.Y * a_kQuat.v.Y + v.Z * a_kQuat.v.Z);
	v.X = y * a_kQuat.v.Z - z * a_kQuat.v.Y + s * a_kQuat.v.X + x * a_kQuat.s;
	v.Y = z * a_kQuat.v.X - x * a_kQuat.v.Z + s * a_kQuat.v.Y + y * a_kQuat.s;
	v.Z = x * a_kQuat.v.Y - y * a_kQuat.v.X + s * a_kQuat.v.Z + z * a_kQuat.s;
	s = sn;
}

//////////////////////////////////////////////////////////////////////////
void Quaternion::operator *= (float a_fScale)
{
	s *= a_fScale;
	v *= a_fScale;

}

//////////////////////////////////////////////////////////////////////////
void Quaternion::operator /= (float a_fScale)
{
	s /= a_fScale;
	v /= a_fScale;
}

//////////////////////////////////////////////////////////////////////////
float Quaternion::Dot(const Quaternion &a_kQ1 , const Quaternion &a_kQ2)
{
	return a_kQ1.v.X * a_kQ2.v.X + a_kQ1.v.Y * a_kQ2.v.Y + a_kQ1.v.Z * a_kQ2.v.Z + a_kQ1.s * a_kQ2.s;
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::Lerp(const Quaternion &a_kQ1 , const Quaternion &a_kQ2 , float t)
{
	Quaternion q = (a_kQ1 * (1.0f - t )) + a_kQ2 * t;
	return q;
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::Slerp(const Quaternion &a_kQ1 , const Quaternion &a_kQ2, float t)
{
	Quaternion q3;
	float fDot = Quaternion::Dot(a_kQ1,a_kQ2);
	// if dot < 0, Q1 & Q2 greater than 90 degrees apart so we invert one to reduce spinning

	if( fDot < 0 )
	{
		fDot = -fDot;
		q3 = -(Quaternion)a_kQ2;
	}
	else
		q3 = a_kQ2;

	if(fDot < 0.95f)
	{
		float fAngle = acosf(fDot);
		Quaternion kResult =  (( a_kQ1 * sinf(fAngle * (1.0f-t)) + q3 * sinf(fAngle * t)) / sinf(fAngle));
		return kResult;
	}
	else // if angle is small use linear interpolation
		return Lerp(a_kQ1,q3,t);
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::SlerpNoInvert(const Quaternion &a_kQ1 , const Quaternion &a_kQ2 , float t)
{
	float fDot = Quaternion::Dot(a_kQ1,a_kQ2);

	if( fDot > -0.95f && fDot < 0.95f)
	{
		float fAngle = acosf(fDot);
		return (a_kQ1 * sinf(fAngle*(1.0f-t)) + a_kQ2 * sinf(fAngle * t)) / sinf(fAngle);
	}
	else // if angle small jsut use lerp
		return Lerp(a_kQ1,a_kQ2,t);
}

//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::FromAxisAngle(const float3 &a_vAxis , float a_fAngle)
{
	return Quaternion(cosf(a_fAngle/2) , (float3)a_vAxis * sinf(a_fAngle/2));
}

//////////////////////////////////////////////////////////////////////////
void Quaternion::ToAxisAngle(float3 &a_vAxis , float &a_fAngle)
{
	a_fAngle = acosf(s);
	float sinf_theta_inv = 1.0f / sinf(a_fAngle);

	a_vAxis.X = v.X * sinf_theta_inv;
	a_vAxis.Y = v.Y * sinf_theta_inv;
	a_vAxis.Z = v.Z * sinf_theta_inv;
	a_fAngle *= 2;
}

//////////////////////////////////////////////////////////////////////////
void Quaternion::ToMatrix3(matrix3 &a_kMat)
{
	// might be wrong needs checking
	Quaternion q = Normalised();
	// top collum
	a_kMat.m_afData1D[0] = 1 - 2 * (q.v.Y * q.v.Y + q.v.Z * q.v.Z);
	a_kMat.m_afData1D[1] = 2 * ( q.v.X * q.v.Y - q.s * q.v.Z);
	a_kMat.m_afData1D[2] = 2 * ( q.v.X * q.v.Z + q.s * q.v.Y);

	// middle collum
	a_kMat.m_afData1D[3] = 2 * ( q.v.X * q.v.Y + q.s * q.v.Z);
	a_kMat.m_afData1D[4] = 1 - 2 * (q.v.X * q.v.X + q.v.Z * q.v.Z);
	a_kMat.m_afData1D[5] = 2 * ( q.v.Y * q.v.Z - q.s * q.v.X);
	
	// last collum
	a_kMat.m_afData1D[6] = 2 * ( q.v.X * q.v.Z - q.s * q.v.Y );
	a_kMat.m_afData1D[7] = 2 * ( q.v.Y * q.v.Z + q.s * q.v.X);
	a_kMat.m_afData1D[8] = 1 - 2 * (q.v.X * q.v.X + q.v.Y * q.v.Y);

}

void Quaternion::ToMatrix4(matrix4 &a_kMat)
{
	Quaternion q = Normalised();
	//top columm
	a_kMat.m_m[0][0] = 1 - 2 * (q.v.Y * q.v.Y + q.v.Z * q.v.Z);
	a_kMat.m_m[1][0] = 2 * ( q.v.X * q.v.Y - q.s * q.v.Z);
	a_kMat.m_m[2][0] = 2 * ( q.v.X * q.v.Z + q.s * q.v.Y);
	a_kMat.m_m[3][0] = 0;

	a_kMat.m_m[0][1] = 2 * ( q.v.X * q.v.Y + q.s * q.v.Z);
	a_kMat.m_m[1][1] = 1 - 2 * (q.v.X * q.v.X + q.v.Z * q.v.Z);
	a_kMat.m_m[2][1] = 2 * ( q.v.Y * q.v.Z - q.s * q.v.X);
	a_kMat.m_m[3][1] = 0;

	a_kMat.m_m[0][2] = 2 * ( q.v.X * q.v.Z - q.s * q.v.Y );
	a_kMat.m_m[1][2] = 2 * ( q.v.Y * q.v.Z + q.s * q.v.X);
	a_kMat.m_m[2][2] = 1 - 2 * (q.v.X * q.v.X + q.v.Y * q.v.Y);
	a_kMat.m_m[3][2] = 0;

	a_kMat.m_m[0][3] = 0;
	a_kMat.m_m[1][3] = 0;
	a_kMat.m_m[2][3] = 0;
	a_kMat.m_m[3][3] = 1;

}

//////////////////////////////////////////////////////////////////////////
float3 Quaternion::GetEulerAngles(bool homogenous /* = true */)
{
	float sqw = s*s;
	float sqx = v.X * v.X;
	float sqy = v.Y * v.Y;
	float sqz = v.Z * v.Z;
	 
	float3 vEuler;
	if(homogenous)
	{
		vEuler.X = atan2f(2.f * (v.Y* v.Z + v.X * s), -sqx - sqy - sqz + sqw);
		vEuler.Y = asinf(-2.f * (v.X * v.Z - v.Y * s));
		vEuler.Z = atan2f(2.f * (v.X*v.Y + v.Z * s),sqx - sqy - sqz + sqw);
	}
	else
	{
		vEuler.X = atan2f( 2.f * (v.X * v.Y + v.Z * s) , 1 - 2 * (sqy + sqz));
		vEuler.Y = asinf( -2.f * (v.X * v.Z - v.Y * s));
		vEuler.Z = atan2f( 2.f * (v.Z * v.Y + v.X * s) , 1 - 2 * (sqx + sqy));
	}
	return vEuler;
}