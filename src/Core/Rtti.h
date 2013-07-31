//////////////////////////////////////////////////////////////////////////
/*! \class		Rtti
 *  \brief		RTTI (Run time type information). this class stores the type information of a object (class)
 *	\details	and allows for it to determine if other objects inherit from a certain type or match its type.
 *  \details	this gains most effective use for comparing objects who have all been typecasted back to a common type for storage purposes. 
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		28/02/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _RTTI_H_
# define _RTTI_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 


//////////////////////////////////////////////////////////////////////////
//  Forward Declares 

//////////////////////////////////////////////////////////////////////////
class Rtti
{
public:
	/*! \brief sets the base Rtti Name and stores a link to its parent. if supplited
	 *  \param a_cpName [in] - Identifying name used to identify this object.
	 */
	Rtti(const char* a_cpName, const Rtti* a_pkBaseType = 0);

	/*! \brief get the name of this object. 
	 *  \return char* - returns the name of this object. 
	 */
	const char* GetName() const;

	/*! \brief Checks to see if the passed in Rtti's name is the same as itself. this is case sensitive
	 *  \param a_kType [in] - Rtti object to compare against to see if there is a match.
	 *  \return bool - Returns true if they match exactly, false otherwise
	 *	\sa Rtti::IsDerived(const Rtti& a_kType)
	 */
	bool IsExsactly(const Rtti& a_kType ) const; 

	// returns true if itself or anything it inherits from is identical to the passed in type
	/*! \brief This function checks if the bassed in object or any of its parents match this current object. 
	 *  \param a_kType - the object to be used for comparisions. 
	 *  \return bool - Resturns true if this object or its parent's (recusively) match this object. false otherwise. 
	 *	\sa Rtti::IsExsactly(const Rtti& a_kType)
	 */
	bool IsDerived(const Rtti& a_kType ) const;

private:
	const char* m_cpName;//!<		The name of the object.
	const Rtti* m_pkBaseType;//!<	The Parent object. NULL if this is the root. 
};
//////////////////////////////////////////////////////////////////////////
#endif // _RTTI_H_
//////////////////////////////////////////////////////////////////////////
