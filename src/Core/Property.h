//////////////////////////////////////////////////////////////////////////
/*! \class		Property
 *  \brief		this class is the base class for all property based elements.
 *	\details	property's are part of Node's. they contain things that any object can swap or add a copy of. 
 *  \details	should be inherited from and have the type added to the base classes enum. the enum is used to identify what property it is for when an object searches to see if it has a certain property.
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		15/03/2013
 *  \copyright N/A
 *	\todo		Finish Implementing this class and making it interact with Node Class
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _PROPERTY_H_
# define _PROPERTY_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include <boost/smart_ptr.hpp>
#include "Object.h"
//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
class Property;
typedef boost::shared_ptr<Property> PropertyPtr;

//////////////////////////////////////////////////////////////////////////
class Property : public Object
{
public:
	virtual const Rtti& GetType() const { return TYPE; }
	enum PROPERTY_TYPE : unsigned int
	{
		SHADER_PROGRAM = 0,
		MESH = 1
	};
	Property();
	Property(PROPERTY_TYPE a_eType);
	virtual ~Property();
	PROPERTY_TYPE GetPropertyType();


protected:
	unsigned int m_uiPropertyType;
	static const Rtti TYPE;
private:
	
};

//typedef Property::TYPES Property::PROPERTY_TYPE

//////////////////////////////////////////////////////////////////////////
#endif // _PROPERTY_H_
//////////////////////////////////////////////////////////////////////////
