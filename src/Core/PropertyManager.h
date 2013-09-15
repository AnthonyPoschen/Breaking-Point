//////////////////////////////////////////////////////////////////////////
/*! \class		PropertyManager
 *  \brief		Manage Property Elements within an object.
 *	\details	This allows only 1 property of each type to be active in a manager at any given time
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		12/09/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _PROPERTYMANAGER_H_
# define _PROPERTYMANAGER_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "Property.h"
#include <boost/container/vector.hpp>

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 


//////////////////////////////////////////////////////////////////////////
class PropertyManager
{
public:
	//class untested
	PropertyManager();
	~PropertyManager();
	bool AttachProperty(PropertyPtr a_kProperty);
	bool AttachProperty(Property a_kProperty);
	bool DetachProperty(PropertyPtr a_kProperty);
	PropertyPtr DetachPropertyByType(Property::PROPERTY_TYPE a_eType);

	PropertyPtr GetProperty(Property::PROPERTY_TYPE a_eType);

protected:
	boost::container::vector<PropertyPtr> m_kPropertyVec;
private:

	
};

//////////////////////////////////////////////////////////////////////////
#endif // _PROPERTYMANAGER_H_
//////////////////////////////////////////////////////////////////////////