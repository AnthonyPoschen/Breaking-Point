//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 17/2/2013 >
/// < File >	< Transform >
/// < Brief >	< Transform class implementation >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "transform.h"

//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
Transform::Transform()
	: m_kRotate(matrix3::CreateIdentity()) , m_kTranslate(float3(0,0,0)) , m_fScale(1)
{
	
}

//////////////////////////////////////////////////////////////////////////
Transform::~Transform()
{

}

//////////////////////////////////////////////////////////////////////////
Transform Transform::operator * (const Transform& a_kTran) const
{
	Transform kResult;
	kResult.m_kRotate = this->m_kRotate * a_kTran.m_kRotate;
	kResult.m_kTranslate = this->m_kTranslate + a_kTran.m_kTranslate;
	kResult.m_fScale = this->m_fScale * a_kTran.m_fScale;
	return kResult;
}