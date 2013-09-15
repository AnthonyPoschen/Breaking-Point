//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 18/2/2013 >
//	< File >	< AVObject >
//	< Brief >	< AVObject implementation >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	< Includes >
#include "AVObject.h"

//////////////////////////////////////////////////////////////////////////
// < Forward Declares >
const Rtti AVObject::TYPE("AVObject", &Object::TYPE);

//////////////////////////////////////////////////////////////////////////
AVObject::AVObject()
	:m_pkParent(nullptr),m_kName(""),m_bMarker(false)//this marker is used for searches
{

}

//////////////////////////////////////////////////////////////////////////
AVObject::~AVObject()
{

}

//////////////////////////////////////////////////////////////////////////
void AVObject::Update(float a_fDeltaTime)
{
	// update world transform.
	if(m_pkParent != nullptr)
	{
		AVObject* kObj = m_pkParent;
		m_kWorldTransform = kObj->m_kWorldTransform * m_kLocalTransform;

	}
	else
		m_kWorldTransform = m_kLocalTransform;
	
	// update properties
	
}

AVObject* AVObject::GetRoot()
{
	AVObject* pkResult = this;
	while(pkResult->m_pkParent != nullptr)
	{
		pkResult = pkResult->m_pkParent;
	}
	return pkResult;
}

//////////////////////////////////////////////////////////////////////////
void AVObject::SetTranslate(float3 a_kVec)
{
	float3 kOldtrans = m_kLocalTransform.m_kTranslate;

	m_kLocalTransform.m_kTranslate = a_kVec;

	m_kWorldTransform.m_kTranslate -= kOldtrans - m_kLocalTransform.m_kTranslate; 
}

//////////////////////////////////////////////////////////////////////////
void AVObject::SetWorldTranslate(float3 a_kVec)
{
	float3 kDiff = m_kWorldTransform.m_kTranslate - a_kVec;
	m_kLocalTransform.m_kTranslate = m_kLocalTransform.m_kTranslate - kDiff;
	m_kWorldTransform.m_kTranslate = a_kVec;
}

//////////////////////////////////////////////////////////////////////////
float3 AVObject::GetTranslate()
{
	return m_kLocalTransform.m_kTranslate;
}

//////////////////////////////////////////////////////////////////////////
float3 AVObject::GetWorldTranslate()
{
	return m_kWorldTransform.m_kTranslate;
}

//////////////////////////////////////////////////////////////////////////
Transform AVObject::GetTransform()
{
	return m_kLocalTransform;
}

//////////////////////////////////////////////////////////////////////////
Transform AVObject::GetWorldTransform()
{
	return m_kWorldTransform;
}

//////////////////////////////////////////////////////////////////////////
boost::container::string AVObject::GetName()
{
	return m_kName;
}

//////////////////////////////////////////////////////////////////////////
void AVObject::SetName(const char* a_cpName)
{
	m_kName = a_cpName;
}

//////////////////////////////////////////////////////////////////////////
void AVObject::SetScale(float a_fScale)
{
	m_kLocalTransform.m_fScale = a_fScale;
	m_kWorldTransform.m_fScale = a_fScale;
}

void AVObject::SetTransform(Transform a_kTransform)
{
	m_kLocalTransform = a_kTransform;
}

void AVObject::SetWorldTransform(Transform a_kTransform)
{
	m_kWorldTransform = a_kTransform;
}