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
	if(a_pkObj->m_pkParent != nullptr)
	{
		Node* oNode = Utilities::DynamicCast<Node>(a_pkObj->m_pkParent);
		oNode != nullptr ? oNode->DetachChild(a_pkObj) : NULL;
	}

	a_pkObj->m_kLocalTransform.m_kTranslate = a_pkObj->m_kWorldTransform.m_kTranslate - m_kWorldTransform.m_kTranslate ;
	
	m_vkChildren.push_back(a_pkObj);

	a_pkObj->m_pkParent = this;
	//a_pkObj->Update(0);
}

void Node::DetachChild(AVObject* a_pkObj)
{
	auto oItr = m_vkChildren.begin();
	for(;oItr != m_vkChildren.end(); oItr++)
	{
		if((*oItr) == a_pkObj)
		{
			m_vkChildren.erase(oItr);
			break;
		}
	}
	AVObject* oChild = (*oItr);
	// convert childs local cords abck to world.
	oChild->m_kLocalTransform = oChild->m_pkParent->m_kWorldTransform * oChild->m_kLocalTransform;
	oChild->m_kWorldTransform = m_kLocalTransform;
	oChild->m_pkParent = 0;
	
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
/*
//////////////////////////////////////////////////////////////////////////
void Node::GetChildByType(const Rtti& a_TYPE, boost::container::vector<AVObject*>& a_vResult)
{
	boost::container::vector<AVObject*> vRecurResult;
	for(unsigned int i = 0; i < m_vkChildren.size(); ++i)
	{
		AVObject* kObj = m_vkChildren.at(i);
		if(kObj->IsExsactly(a_TYPE))
		{
			if(kObj->m_bMarker == false)
			{
				kObj->m_bMarker = true;
				a_vResult.push_back(kObj);
			}
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
*/
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

//////////////////////////////////////////////////////////////////////////
bool GetChildByTypeFP(AVObject* a_kObj, void* a_kType)
{
	return a_kObj->IsExsactly(*(Rtti*)a_kType);
}

//////////////////////////////////////////////////////////////////////////
void Node::GetChildByType(const Rtti& a_TYPE, boost::container::vector<AVObject*>& a_vResult)
{
	NodeDepthFirstSearch(a_vResult,(void*)&a_TYPE,GetChildByTypeFP);
}

//////////////////////////////////////////////////////////////////////////
bool GetChildByPropFP(AVObject* a_kObj, void* a_kType)
{
	Node* oNode = Utilities::DynamicCast<Node>(a_kObj);
	//			if not null		then if has property						then return true	else false	else false
	return oNode != nullptr ? oNode->GetProperty(*(Property::PROPERTY_TYPE*)a_kType) != nullptr ?  true:  false : false;
}

//////////////////////////////////////////////////////////////////////////
void Node::GetChildByProperty(Property::PROPERTY_TYPE a_ePROPTYPE, boost::container::vector<AVObject*>&a_vResult)
{
	NodeDepthFirstSearch(a_vResult,(void*)&a_ePROPTYPE,GetChildByPropFP);
}

void Node::NodeDepthFirstSearch( boost::container::vector<AVObject*>&a_vResult,void* a_vpExtraData,bool (*fp_bTestifWanted)(AVObject*,void*))
{
	// do search stuff. call callback once per object. keep track of shit. then reset everything once done.
	boost::container::vector<AVObject*> vVistedNodes;
	AVObject* kRoot = (AVObject*)this;
	AVObject* kCurrent = kRoot;
	//all control paths will eventually break this loop (cant use recursion function instyead in this scenario make function weird )
	while(true)
	{

		if(kCurrent->m_bMarker == false)
		{
			kCurrent->m_bMarker = true;
			vVistedNodes.push_back(kCurrent);
			if(fp_bTestifWanted(kCurrent,a_vpExtraData))
			{
				a_vResult.push_back(kCurrent);
			}
			continue;
		}
		else
		{
			Node* kNodeCurrent = Utilities::DynamicCast<Node>(kCurrent);
			bool bHasChildren = true;
			// the inception shorthand if in an if. because fucking sick of ifs in ifs (cant do && because kNodecurrent could be null which would cause error)
			//		statement			if true statement			if 2nd true| if 2nd false		if first statement false	
			kNodeCurrent != nullptr ? kNodeCurrent->m_vkChildren.size() ? 0: bHasChildren =false: bHasChildren = false;

			if(bHasChildren) // check if it is a node type so it could have more children.
			{
				//for loop to find first available child to switch to. if found continue
				for(int i = 0; i < kNodeCurrent->m_vkChildren.size(); ++i)
				{
					if(kNodeCurrent->m_vkChildren.at(i)->m_bMarker == false)
					{
						kCurrent = kNodeCurrent->m_vkChildren.at(i);
						break; // breaks current loop only
					}
				}
				//check if we have a valid new node to check if not end this madness
				if(kCurrent->m_bMarker == false)
					continue;
				else
					break;

			}
			else // node has no chance of having children so set it to its parent and continue
			{
				kCurrent = kCurrent->m_pkParent;
				if(kCurrent == nullptr )
					break; // node has no parent we are back at root
				else
					continue;// has a valid parent which could have more. so dont break yet.
			}
		}

		break; // incase a control path isnt hit break out for safety reasons
	}
	// done checking all nodes now reset all the ones we visited back to false for future checks
	auto oItr = vVistedNodes.begin();
	for(;oItr != vVistedNodes.end(); oItr++)
	{
		(*oItr)->m_bMarker = false;
	}


}