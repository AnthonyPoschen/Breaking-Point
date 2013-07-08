//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 24 - 2 - 2013 >
/// < Class Brief >	< this is the "Camera class" it handles the viewport for rendering  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _CAMERA_H_
#define _CAMERA_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >

#include "AVObject.h"
#include "../Math/matrix4.h"
#include "../Math/float3.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class Camera : public AVObject
{
public:
	struct Frustrum
	{
		float m_fFieldOfView;
		float m_fScreenAspectRatio;
		float m_fNear;
		float m_fFar;
	};
	Camera(const Frustrum &a_oFrustrum);
	~Camera();
	virtual const Rtti& GetType() const { return TYPE; }
	static const Rtti& Type() { return TYPE;}


	Frustrum GetFrustrum();
	void SetFrustrum(Frustrum &a_oFrustrum);

	// look at a world point
	void LookAt(const float3 &a_kTarget , const float3 &a_kUpVec);
	// update all the 
	void Update(float a_fDeltaTime);

	matrix4 GetViewMatrix();
	matrix4 GetProjMatrix();
	matrix4 GetViewProjMatrix();

	operator AVObject()  {return (AVObject)*this;}
protected:
	static const Rtti TYPE;
	Frustrum m_oFrustrum;

	float3 m_kLookAt;
	float3 m_kUpVec;
	matrix4 m_mProj; // this is for view frustum fov stuff etc
	matrix4 m_mView; // this puts objects in "camera Space"
	matrix4 m_mViewProj;
private:
	void UpdateProjMat();
	void UpdateViewMat();
};
//////////////////////////////////////////////////////////////////////////
#endif // _CAMERA_H_
//////////////////////////////////////////////////////////////////////////
