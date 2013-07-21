//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 24/2/2013 >
//	< File >	< Camera >
//	< Brief >	< camera class  >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Includes 
#include "Camera.h"
#include "../Graphics/Window.h"
#include "../Math/CoreMath.h"
//////////////////////////////////////////////////////////////////////////
// Forward Declares 
const Rtti Camera::TYPE("Camera", &AVObject::TYPE);

//////////////////////////////////////////////////////////////////////////
Camera::Camera(const Frustrum &a_oFrustrum)
	:m_oFrustrum(a_oFrustrum) , m_kLookAt(float3(0,0,1)), m_kUpVec(0,1,0)
{
	matrix4::MakeIdentity(m_mProj);
	matrix4::MakeIdentity(m_mView);
}

//////////////////////////////////////////////////////////////////////////
Camera::~Camera()
{
	
}

//////////////////////////////////////////////////////////////////////////
Camera::Frustrum Camera::GetFrustrum()
{
	return m_oFrustrum;
}

//////////////////////////////////////////////////////////////////////////
void Camera::SetFrustrum(Frustrum &a_oFrustrum)
{
	m_oFrustrum = a_oFrustrum;
}

//////////////////////////////////////////////////////////////////////////
void Camera::Update(float a_fDeltaTime)
{
	// update child class
	AVObject::Update(a_fDeltaTime);

	//calc proj matrix;
	UpdateProjMat();

	// calc view matrix;
	UpdateViewMat();

	// calc ViewProj Matrix;
	m_mViewProj =  m_mView * m_mProj;

}

//////////////////////////////////////////////////////////////////////////
void Camera::UpdateProjMat()
{
	
	float fRad = toRadians(m_oFrustrum.m_fFieldOfView);
	float h = cos(0.5f * fRad) / sin(0.5f * fRad);
	float w = h * (float)Window::Get()->GetHeight() / (float)Window::Get()->GetWidth();
	float zn = m_oFrustrum.m_fNear;
	float zf = m_oFrustrum.m_fFar;

	m_mProj.m_m[0][0] = w;
	m_mProj.m_m[1][1] = h;
	m_mProj.m_m[2][2] = (zf + zn) / (zf - zn);
	m_mProj.m_m[2][3] = 1.0f;
	m_mProj.m_m[3][2] = -(2.0f * zf * zn) / (zf - zn);
	m_mProj.m_m[3][3] = 0;
	
}

//////////////////////////////////////////////////////////////////////////
void Camera::UpdateViewMat()
{
	float3 xAxis , yAxis , zAxis , kPosition;
	kPosition = m_kWorldTransform.m_kTranslate;

	zAxis = kPosition - m_kLookAt;
	zAxis.Unitise();

	xAxis = m_kUpVec.Cross(zAxis);
	xAxis.Unitise();

	yAxis = zAxis.Cross(xAxis);
	yAxis.Unitise();
	m_mView.m_v[0] = xAxis.X; 
	m_mView.m_v[1] = yAxis.X;
	m_mView.m_v[2] = zAxis.X;
	m_mView.m_v[3] = 0;

	m_mView.m_v[4] = xAxis.Y;
	m_mView.m_v[5] = yAxis.Y;
	m_mView.m_v[6] = zAxis.Y;
	m_mView.m_v[7] = 0;

	m_mView.m_v[8] = xAxis.Z;
	m_mView.m_v[9] = yAxis.Z;
	m_mView.m_v[10]= zAxis.Z;
	m_mView.m_v[11]= 0;

	m_mView.m_v[12]= (xAxis.Dot(kPosition));
	m_mView.m_v[13]= (yAxis.Dot(kPosition));
	m_mView.m_v[14]= (zAxis.Dot(kPosition));
	m_mView.m_v[15]= 1;
}

//////////////////////////////////////////////////////////////////////////
void Camera::LookAt(const float3 &a_kTarget , const float3 &a_kUpVec)
{
	
	m_kUpVec = a_kUpVec;
	m_kUpVec.Unitise();

	m_kLookAt = a_kTarget;
}

matrix4 Camera::GetViewProjMatrix()
{
	return m_mViewProj;
}

matrix4 Camera::GetViewMatrix()
{
	return m_mView;
}

matrix4 Camera::GetProjMatrix()
{
	return m_mProj;
}