//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 18 - 2 - 2013 >
/// < Class Brief >	< AVObject is the base for all objects that require a location and a rotation managed  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _AVOBJECT_H_
#define _AVOBJECT_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "Object.h"
#include "Transform.h"
#include <boost/container/string.hpp>
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >
class Node;
//////////////////////////////////////////////////////////////////////////
class AVObject : public Object
{
public:
	friend class Node;
	// Required for Rtti;
	virtual const Rtti& GetType() const { return TYPE; }
	static const Rtti& Type() { return TYPE;}
	boost::container::string GetName();
	void SetName(const char* a_cpName);
	AVObject* GetRoot();
	//Node* GetParent();

	AVObject();
	~AVObject();
	
	virtual void Update(float a_fDeltaTime);
	
	/// <Positional Related Funcitons> 
	void SetTranslate(float3 a_kVec);
	void SetWorldTranslate(float3 a_kVec);
	float3 GetTranslate();
	float3 GetWorldTranslate();
	void SetScale(float a_fScale);
	Transform GetTransform();
	Transform GetWorldTransform();

protected:
	static const Rtti TYPE;
	Transform m_kWorldTransform;
	Transform m_kLocalTransform;
	AVObject* m_pkParent;
	boost::container::string m_kName;

private:
	

};
//////////////////////////////////////////////////////////////////////////
#endif // _AVOBJECT_H_
//////////////////////////////////////////////////////////////////////////
