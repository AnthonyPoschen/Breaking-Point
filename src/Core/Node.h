//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 17 - 2 - 2013 >
/// < Class Brief >	< Node is a a Base object class which holds position rotation   >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _NODE_H_
#define _NODE_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "AVObject.h"
#include <boost/container/vector.hpp>
#include <boost/smart_ptr.hpp>

//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >

typedef boost::shared_ptr<Node> NodePtr;

//////////////////////////////////////////////////////////////////////////
class Node : public AVObject
{
public:

	virtual const Rtti& GetType() const { return TYPE; }
	static const Rtti& Type() { return TYPE;}
	Node();
	~Node();

	/// < child / parent functions>
	void AttachChild(AVObject* a_pkObj);
	void DetachChild(AVObject* a_pkObj);

	// searches all elements and all children for any
	void GetChildByType(const Rtti& a_TYPE, boost::container::vector<AVObject*>&a_vResult); 
	
	// returns the first object with this name. (depth first search)
	AVObject* getChildByName(const char* a_cpName);

	void Update(float a_fDelta);

	operator AVObject()  {return (AVObject)*this;}
	
protected:
	static const Rtti TYPE;
	
private:
	
	boost::container::vector<AVObject*> m_vkChildren;
};
//////////////////////////////////////////////////////////////////////////
#endif // _NODE_H_
//////////////////////////////////////////////////////////////////////////
