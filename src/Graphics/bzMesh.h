//////////////////////////////////////////////////////////////////////////
/*! \class		bzMesh
 *  \brief		This is the root mesh class.
 *	\details	it handles the storing of 3d geometory. 
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		23/03/2013
 *	\todo Fix this class to be more self relient and have more helpfull features to make Renderer class easier to render this object. 
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _BZMESH_H_
# define _BZMESH_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "../core/AVObject.h"

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
class AVObject;

///////////////////////////////////////////////////////////////////////
class bzMesh : public AVObject
{
public:
	friend class Renderer;
	virtual const Rtti& GetType() const { return TYPE; }
	bzMesh();
	~bzMesh();

protected:
	static const Rtti TYPE;

	unsigned int m_uiVAOID; // Vertex Array Object.
	unsigned int m_uiVertexBuffer;
	unsigned int m_uiVertColorBuffer; 
	float* vertexdatatest;
	float* vertcolors;
private:
	// used internally by Renderer Class to render its contents
	virtual void Render();
};
//////////////////////////////////////////////////////////////////////////
#endif // _BZMESH_H_
//////////////////////////////////////////////////////////////////////////
