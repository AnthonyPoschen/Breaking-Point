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
	float aspect =  (float)Window::Get()->GetWidth() / (float)Window::Get()->GetHeight() ;
	float h = 1.0f / tan(m_oFrustrum.m_fFieldOfView / 2 * BP_PI / 360);
	float w = h / aspect;

	float zn = m_oFrustrum.m_fNear;
	float zf = m_oFrustrum.m_fFar;
	float Q = zf/ ( zf - zn);

	m_mProj.m_m[0][0] = w;
	m_mProj.m_m[1][1] = h;
	m_mProj.m_m[2][2] = Q;
	m_mProj.m_m[2][3] = 1.0f;
	m_mProj.m_m[3][2] = -zn*Q;
	m_mProj.m_m[3][3] = 0.0f;
	
	/*
	float aspectratio =  (float)Window::Get()->GetWidth() / (float)Window::Get()->GetHeight() ;
	float znear = m_oFrustrum.m_fNear;
	float zfar = m_oFrustrum.m_fFar;
	float fov = m_oFrustrum.m_fFieldOfView;
	float ymax,xmax;

	ymax = (float) (znear * tan(fov * BP_PI / 360));
	xmax = ymax * aspectratio;

	glFrustrum(m_mProj,-xmax,xmax,-ymax,ymax,znear,zfar);
	*/
}

void Camera::glFrustrum(matrix4 &a_mMat, float left, float right, float bottom , float top, float znear , float zfar )
{
	float twoZNear, deltaW, deltaH, deltaZ;
	twoZNear = 2.0f * znear;
	deltaW = right - left;
	deltaH = top - bottom;
	deltaZ = zfar - znear;

	m_mProj.m_f00 = twoZNear / deltaW;
	m_mProj.m_f11 = twoZNear / deltaH;
	m_mProj.m_f20 = (right + left) / deltaW;
	m_mProj.m_f21 = (top + bottom) / deltaZ;
	m_mProj.m_f22 = (-zfar - znear) / deltaZ;
	m_mProj.m_f23 = -1.0f;
	m_mProj.m_f32 = (-twoZNear * zfar) / deltaZ;
	//m_mProj.Transpose();
}

//////////////////////////////////////////////////////////////////////////
void Camera::UpdateViewMat()
{
	float3 xAxis , yAxis , zAxis , kPosition;
	kPosition = m_kWorldTransform.m_kTranslate;

	zAxis = m_kLookAt - kPosition;
	zAxis.Unitise();

	xAxis = m_kUpVec.Cross(-zAxis);
	if(xAxis.X == 0.0f && xAxis.Y == 0.0f && xAxis.Z == 0.0f)
		xAxis.Z = zAxis.Y;
	xAxis.Unitise();

	yAxis = zAxis.Cross(-xAxis);
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

	m_mView.m_v[12]= -(xAxis.Dot(kPosition));
	m_mView.m_v[13]= -(yAxis.Dot(kPosition));
	m_mView.m_v[14]= -(zAxis.Dot(kPosition));
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