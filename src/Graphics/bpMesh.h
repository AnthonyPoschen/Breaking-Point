//////////////////////////////////////////////////////////////////////////
/*! \class		bpMesh
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
#ifndef _BPMESH_H_
# define _BPMESH_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "../core/Property.h"

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
class Property;

///////////////////////////////////////////////////////////////////////
class bpMesh : public Property
{
public:
	friend class Renderer;
	virtual const Rtti& GetType() const { return TYPE; }
	static const Rtti& Type() { return TYPE;}
	virtual operator Rtti() { return TYPE;}
	bpMesh();
	~bpMesh();
protected:
	static const Rtti TYPE;

	unsigned int m_uiVAOID; // Vertex Array Object.
	unsigned int m_uiVertexBuffer;
	unsigned int m_uiVertColorBuffer; 
	unsigned int m_uiIndicieBuffer;
	float* vertexdatatest;
	float* vertcolors;
	unsigned int* Indicies;
private:
	// used internally by Renderer Class to render its contents
	virtual void Render();
};
//////////////////////////////////////////////////////////////////////////
#endif // _bpMesh_H_
//////////////////////////////////////////////////////////////////////////
