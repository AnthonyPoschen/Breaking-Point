//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 17/2/2013 >
//	< File >	< Node >
//	< Brief >	< Node class Implementation >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	< Includes >
#include "Node.h"
#include <boost/smart_ptr.hpp>
#include "Utilities.h"
//////////////////////////////////////////////////////////////////////////
// < Forward Declares >
const Rtti Node::TYPE("Node",&AVObject::TYPE);

//////////////////////////////////////////////////////////////////////////
Node::Node()
{

}

//////////////////////////////////////////////////////////////////////////
Node::~Node()
{

}

//////////////////////////////////////////////////////////////////////////
void Node::AttachChild(AVObject* a_pkObj)
{
	a_pkObj->m_kLocalTransform.m_kTranslate = a_pkObj->m_kWorldTransform.m_kTranslate - m_kWorldTransform.m_kTranslate;
	m_vkChildren.push_back(a_pkObj);
	a_pkObj->m_pkParent = this;
	a_pkObj->Update(0);
}

void Node::DetachChild(AVObject* a_pkObj)
{
	m_vkChildren;
}


//////////////////////////////////////////////////////////////////////////
void Node::Update(float a_fDelta)
{
	AVObject::Update(a_fDelta);
	for ( unsigned int i = 0; i < m_vkChildren.size(); ++i)
	{
		AVObject* kObj = m_vkChildren[i];
		if(kObj != nullptr)
			m_vkChildren[i]->Update(a_fDelta);
	}
}

//////////////////////////////////////////////////////////////////////////
void Node::GetChildByType(const Rtti& a_TYPE, boost::container::vector<AVObject*>& a_vResult)
{
	boost::container::vector<AVObject*> vRecurResult;

	for(unsigned int i = 0; i < m_vkChildren.size(); ++i)
	{
		AVObject* kObj = m_vkChildren.at(i);
		if(kObj->IsExsactly(a_TYPE))
		{
			a_vResult.push_back(kObj);
		}
		Node* kNode = Utilities::DynamicCast<Node>(kObj);
		
		if(kNode != nullptr)
		{
			// recursive search children if Nodes and append their result back until all children searched
			kNode->GetChildByType(a_TYPE,vRecurResult);
			if(vRecurResult.size())
			{
				a_vResult.insert(a_vResult.end(),vRecurResult.begin(),vRecurResult.end());
			}
		}
	}

}

//////////////////////////////////////////////////////////////////////////
AVObject* Node::GetChildByName(const char* a_cpName)
{
	boost::container::string kName(a_cpName);

	for( unsigned int i = 0; i < m_vkChildren.size(); ++i)
	{
		AVObject* kObj = m_vkChildren.at(i);
		if(kObj->GetName() == a_cpName)
		{
			return kObj;
		}
		Node* kNode = Utilities::DynamicCast<Node>(kObj);

		if(kNode != nullptr)
		{
			AVObject* kRecurObj = kNode->GetChildByName(a_cpName);
			if(kRecurObj != nullptr)
			{
				return kRecurObj;
			}
		}
	}
	return nullptr;
}
