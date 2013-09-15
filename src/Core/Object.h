//////////////////////////////////////////////////////////////////////////
/*! \class		Object
 *  \brief		This is the Base Object all objects who need to interact should be absed off.
 *	\details	this object gives RTTI tracking. and allows for safe dynamic casting.
 *  \details	allows any object to find out what another object's inheritance tree.
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		18/02/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _OBJECT_H_
# define _OBJECT_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "Rtti.h"

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 

//////////////////////////////////////////////////////////////////////////
class Object
{
public:
	
	virtual const Rtti& GetType() const;
	static const Rtti& Type() { return TYPE;}
	virtual operator Rtti() { return TYPE;}
	// <Type Comparison functions>
	//@{
	/*! \brief Check if the Object passed in is the same type or derived from the same object. from respective name appropriate functions
	 *	this allows any object to see if it has certain members available to it (handy for if all objects are stored in a list as a base class. and you want to see if it is a certain class.)
	 *  \return bool - indicate if it matches or not. 
	 */
	bool IsExsactly(const Rtti& a_kType) const;
	bool IsDerived(const Rtti& a_kType) const;
	bool IsExsactlyTypeOf(const Object* a_pkObj) const;
	bool IsDerivedTypeOf(const Object* a_pkObj) const;
	//@}

protected:
	static const Rtti TYPE;
};
//////////////////////////////////////////////////////////////////////////
#endif // _OBJECT_H_
//////////////////////////////////////////////////////////////////////////
