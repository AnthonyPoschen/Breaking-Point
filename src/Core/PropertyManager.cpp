//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 12/9/2013 >
//  < File >	< bpCubeShape >
//  < Brief >	< Manages property's to only allow one of each type >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Includes
#include "PropertyManager.h"

//////////////////////////////////////////////////////////////////////////
// Forward Declares

//////////////////////////////////////////////////////////////////////////
PropertyManager::PropertyManager()
{

}

//////////////////////////////////////////////////////////////////////////
PropertyManager::~PropertyManager()
{

}

//////////////////////////////////////////////////////////////////////////
bool PropertyManager::AttachProperty(PropertyPtr a_kProperty)
{
	auto oItr = m_kPropertyVec.begin();
	for(;oItr != m_kPropertyVec.end(); oItr++ )
	{
		if((*oItr)->GetPropertyType() == a_kProperty->GetPropertyType())
		{
			return false;
		}
	}
	// established no other property of this type is in the list so add it.
	m_kPropertyVec.push_back(a_kProperty);
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool PropertyManager::AttachProperty(Property a_kProperty)
{
	Property* oProp = new Property(a_kProperty);
	PropertyPtr ospProp(oProp);
	return AttachProperty(ospProp);
}

//////////////////////////////////////////////////////////////////////////
bool PropertyManager::DetachProperty(PropertyPtr a_kProperty)
{
	auto oItr = m_kPropertyVec.begin();
	for(;oItr != m_kPropertyVec.end(); oItr++)
	{
		if(a_kProperty.get() == oItr->get())
		{
			m_kPropertyVec.erase(oItr);
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
PropertyPtr PropertyManager::DetachPropertyByType(Property::PROPERTY_TYPE a_eType)
{
	auto oItr = m_kPropertyVec.begin();
	for(;oItr != m_kPropertyVec.end(); oItr++)
	{
		if((*oItr).get()->GetPropertyType() == a_eType)
		{
			PropertyPtr ospProp = (*oItr);
			m_kPropertyVec.erase(oItr);
			return ospProp;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
PropertyPtr PropertyManager::GetProperty(Property::PROPERTY_TYPE a_eType)
{
	auto oItr = m_kPropertyVec.begin();
	for(;oItr != m_kPropertyVec.end(); oItr++)
	{
		if((*oItr).get()->GetPropertyType() == a_eType)
		{
			PropertyPtr ospProp = (*oItr);
			return ospProp;
		}
	}
	return 0;
}