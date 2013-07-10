//////////////////////////////////////////////////////////////////////////
/*! \class		AVObject
 *  \brief      AVObject is the Base for all Area type Objects
 *  \details    it handles all Positional and rotation information, as well as parenting to other objects
 *  \author     Anthony Poschen
 *  \version    1.0
 *  \date       18 / 02 / 2013
 *  \copyright  N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _AVOBJECT_H_
#define _AVOBJECT_H_
//////////////////////////////////////////////////////////////////////////
// Includes
#include "Object.h"
#include "Transform.h"
#include <boost/container/string.hpp>
//////////////////////////////////////////////////////////////////////////
// Forward Declares 
class Node;
//////////////////////////////////////////////////////////////////////////
class AVObject : public Object
{
public:
	friend class Node;

	/*! \brief Used in other functions to help identify it at runtime. what this class inherits from and if it can be typecast to certain types.
	 *  \return Rtti - returns the run time identifier for this class type
	 *	\sa AVObject::Type()
	 */
	virtual const Rtti& GetType() const { return TYPE; }

	/*! \brief Used in other functions to help identify it at runtime. what this class inherits from and if it can be typecast to certain types.
	 *  \return Rtti - returns the run time identifier for this class type
	 *	\sa AVObject::GetType()
	 */
	static const Rtti& Type() { return TYPE;}

	/*! \brief gets the name of this object
	 *  \return string - Current name of the object
	 *	\sa AVObject::SetName()
	 */
	boost::container::string GetName();

	/*! \brief Sets the name of this object
	 *  \param a_cpName const char* - this is the name to be used
	 *	\sa AVObject::GetName()
	 */
	void SetName(const char* a_cpName);

	/*! \brief returns the parent of this object. parents are used to transform local transforms to world transforms.
	 *  \return AVObject* - returns a pointer to its parent object
	 */
	AVObject* GetRoot();
	//Node* GetParent();

	AVObject();
	~AVObject();
	
	/*! \brief Updates the local and world transform. this behaviour can be modified or extended by inheritating classes.
	 *  \param a_fDeltaTime - Current delta time for loop
	 */
	virtual void Update(float a_fDeltaTime);
	
	// Positional Related Functions

	/*! \brief Sets the local position. This translate will be garentied to modify the world position on next update call 
	 *  \param a_kVec float3 - the 3D positional cordinate.
	 *	\sa AVObject::SetWorldTranslate()
	 *	\sa AVObject::GetTranslate()
	 *	\sa AVObject::GetWorldTranslate()
	 */
	void SetTranslate(float3 a_kVec);

	/*! \brief Sets the World position. This translate will be garentied to modify the world position on next update call 
	 *  \param a_kVec float3 - the 3D positional cordinate.
	 *	\sa AVObject::SetTranslate()
	 *	\sa AVObject::GetTranslate()
	 *	\sa AVObject::GetWorldTranslate()
	 */
	void SetWorldTranslate(float3 a_kVec);

	/*! \brief Gets the local position. This translate will be garentied to modify the world position on next update call 
	 *  \param a_kVec float3 - the 3D positional cordinate.
	 *	\sa AVObject::GetWorldTranslate()
	 *	\sa AVObject::SetTranslate()
	 *	\sa AVObject::SetWorldTranslate()
	 */
	float3 GetTranslate();

	/*! \brief Sets the World position. This translate will be garentied to modify the world position on next update call 
	 *  \param a_kVec float3 - the 3D positional cordinate.
	 *	\sa AVObject::GetTranslate()
	 *	\sa AVObject::SetTranslate()
	 *	\sa AVObject::SetWorldTranslate()
	 */
	float3 GetWorldTranslate();

	/*! \brief Set the scale of the Object. this propagates to child Objects increasing or decreasing their scale by this.
	 *  \param a_fScale float - value representing the scale ammount. 1.0f being normal size
	 *	\sa AVObject::GetScale()
	 */
	void SetScale(float a_fScale);

	/*! \brief Get the local Transform of this object.
	 *  \return Transform - local Transform of object
	 *	\sa AVObject::GetWorldTransform()
	 *	\sa Transform
	 */
	Transform GetTransform();

	/*! \brief Get the World Transform of this object
	 *  \return Transform - World Transform of object
	 *	\sa AVObject::GetTransform()
	 *	\sa Transform
	 */
	Transform GetWorldTransform();

protected:
	static const Rtti TYPE;//!<				Class Rtti type is stored in this.
	Transform m_kWorldTransform;//!<		World Transform of object
	Transform m_kLocalTransform;//!<		Local Transform of object
	AVObject* m_pkParent;//!<				Pointer to Parent AVObject
	boost::container::string m_kName;//!<	Name of Object

private:
	

};
//////////////////////////////////////////////////////////////////////////
#endif // _AVOBJECT_H_
//////////////////////////////////////////////////////////////////////////
