//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 18 - 2 - 2013 >
/// < Class Brief >	< Object is the base class which all objects which require Rtti tracking inherit from  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _OBJECT_H_
#define _OBJECT_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "Rtti.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class Object
{
public:
	
	virtual const Rtti& GetType() const;
	operator Rtti() { return TYPE;}
	/// <Type Comparison functions>
	bool IsExsactly(const Rtti& a_kType) const;
	bool IsDerived(const Rtti& a_kType) const;
	bool IsExsactlyTypeOf(const Object* a_pkObj) const;
	bool IsDerivedTypeOf(const Object* a_pkObj) const;

	/// <Casting Functions>
	template <class T>
	inline const T* StaticCast(const Object* a_pkObj) { return (const T)a_pkObj; }

	template <class T>
	inline T* DynamicCast(Object* a_pkObj) {	return a_pkObj && a_pkObj->IsDerived(T::Type()) ? (T*)a_pkObj : 0 ; }

	template <class T>
	inline const T* DynamicCast( const Object* a_pkObj) {	return a_pkObj && a_pkObj->IsDerived(T::Type()) ? (const T*)a_pkObj : 0 ; }
protected:
	static const Rtti TYPE;
};
//////////////////////////////////////////////////////////////////////////
#endif // _OBJECT_H_
//////////////////////////////////////////////////////////////////////////
