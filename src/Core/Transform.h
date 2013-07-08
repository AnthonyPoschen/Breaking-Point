//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 17 - 2 - 2013 >
/// < Class Brief >	< This class handles an objects world and lcoal matrix and rotational operations  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "../Math/CoreMath.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class Transform
{
public:
	Transform();
	~Transform();
	matrix3 m_kRotate;
	float3 m_kTranslate;
	float m_fScale;

	Transform operator * (const Transform& a_kTrn) const;
protected:

private:

};
//////////////////////////////////////////////////////////////////////////
#endif // _TRANSFORM_H_
//////////////////////////////////////////////////////////////////////////