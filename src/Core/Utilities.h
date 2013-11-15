//////////////////////////////////////////////////////////////////////////
/*! \class		Utilities
 *  \brief		Utility code to help program.
 *	\details	Holds tools and functions to help debug and store repetitive
 *  \details	helper code in a commonly found location
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		5/05/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _UTILITIES_H_
# define _UTILITIES_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include <stdio.h>
#include <assert.h>
#include "Object.h"
#include <boost/algorithm/string.hpp>
#include <stdio.h>
#include <windows.h>
//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
namespace Utilities
{
	void ConsoleShow(bool a_bShow = true);
	void ConsoleClear();

	void Debug_ConsoleWrite(const char* pFormat, ...);
	void Debug_OutputWrite(const char* pFormat, ...);

	LPCWSTR StdStringToLPCWSTR(std::string a_kString);

	
	/*! \brief cast the passed in object to the template type. without checking if it can happen safely.
	 *  \param a_pkObj [in] - type to be converted to output type.
	 *  \return Template type object of passed in object.
	 *	\sa Object::DynamicCast(Object* a_pkObj)
	 */
	template <class T>
	inline const T* StaticCast(const Object* a_pkObj) { return (const T)a_pkObj; }

	//@{
	/*! \brief Check if object can safely be casted before casting. if object can be casted to another type safely. it is done and returned else returns 0.
	 *  \param a_pkObj [in] - Object to be casted to templated type
	 *  \return Template type object of a_pkObj or 0 if its not possible to cast safely.
	 */
	template <class T>
	inline T* DynamicCast(Object* a_pkObj) { return a_pkObj && a_pkObj->IsDerived(T().GetType()) ? (T*)a_pkObj : 0 ; }

	template <class T>
	inline const T* DynamicCast( const Object* a_pkObj) {	return a_pkObj && a_pkObj->IsDerived(T().GetType()) ? (const T*)a_pkObj : 0 ; }
	//@}

}


//////////////////////////////////////////////////////////////////////////
#endif // _UTILITIES_H_
//////////////////////////////////////////////////////////////////////////