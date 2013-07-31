//////////////////////////////////////////////////////////////////////////
/*! \class		Node
 *  \brief		Base Object Class for proper ingame objects to derive from.
 *	\details	this class properly manages parent and child elements and manages
 *  \details	position and rotation of itself and its children.
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		17/02/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _NODE_H_
# define _NODE_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "AVObject.h"
#include <boost/container/vector.hpp>
#include <boost/smart_ptr.hpp>

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
typedef boost::shared_ptr<Node> NodePtr;

//////////////////////////////////////////////////////////////////////////
class Node : public AVObject
{
public:

	virtual const Rtti& GetType() const { return TYPE; }
	static const Rtti& Type() { return TYPE;}
	Node();
	~Node();

	/*! \brief Attach an external Object as this objects child. 
	 *  \param a_pkObj - AVObject* to be attached to this object
	 *	\sa Node::DetachChild(AVObject* a_pkObj)
	 */
	void AttachChild(AVObject* a_pkObj);

	/*! \brief Detach a child element from this parent. element has to be this elements child to be able to be detached from its parent.
	 *  \param a_pkObj - AVObject* to be detached from this object.
	 *	\sa Node::AttachChild()
	 */
	void DetachChild(AVObject* a_pkObj);

	/*! \brief This functions returns all children by a certain type
	 *  \param a_TYPE [in] - Rtti object to be checked against all children for matches.
	 *	\param a_vResult [out] -  results will be placed in this list. 
	 *	\sa Node::getChildByName()
	 */
	void GetChildByType(const Rtti& a_TYPE, boost::container::vector<AVObject*>&a_vResult); 
	
	// returns the first object with this name. (depth first search)
	/*! \brief gets the first object who's name matches whats given. a depth first search pattern is used to find a match.
	 *  \param a_cpName [in] - the name of the object to search for. 
	 */
	AVObject* GetChildByName(const char* a_cpName);

	/*! \brief Updates the objects World space position based off changes to its local. and propergates changes to all children and calls there Update()
	 *  \param a_fDelta [in] - Delta time (time since last update) to allow for smoth movements over time. regardless of framerate 
	 */
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
