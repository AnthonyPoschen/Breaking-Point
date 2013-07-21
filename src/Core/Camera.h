//////////////////////////////////////////////////////////////////////////
/*! \class		Camera
 *  \brief		Handles Viewport for rendering scene graphs.
 *	\details	The camera class can render to multiple render targets. 
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		24/02/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _CAMERA_H_
# define _CAMERA_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "AVObject.h"
#include "../Math/matrix4.h"
#include "../Math/float3.h"

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 


//////////////////////////////////////////////////////////////////////////
class Camera : public AVObject
{
public:

	/*! \brief Frustrum object. holds all needed camera data for constructing a camera.
	 */
	struct Frustrum
	{
		float m_fFieldOfView;//!<		holds the FOV that the camera will use. aka ammount of degrees left to right.
		float m_fScreenAspectRatio;//!<	this holds the aspect ratio. aka ammount of pixels across compared to up and down
		float m_fNear;//!<				this is the value of the near culling plane. where objects will no longer be drawn if they are too close to the camera, this prevents artifacts
		float m_fFar;//!<				this is the far cliping plane. this stops objects very very far away from being drawn. 
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

	float3 m_kLookAt;//!<		tells the camera to look at a certain point in space.
	float3 m_kUpVec;//!<		this is used to help the camera look at things. as it needs to have a world up direction. to stop the camera from flipping upside down randomly. 
	matrix4 m_mProj;//!<		this is for view frustum fov stuff etc.
	matrix4 m_mView;//!<		this puts objects in "camera Space"
	matrix4 m_mViewProj;//!<	this is the combined view and projection matrix to put any object in camera space for immediate rendering. 
private:
	void UpdateProjMat();
	void UpdateViewMat();
};
//////////////////////////////////////////////////////////////////////////
#endif // _CAMERA_H_
//////////////////////////////////////////////////////////////////////////
