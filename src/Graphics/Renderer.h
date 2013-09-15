//////////////////////////////////////////////////////////////////////////
/*! \class		Renderer
 *  \brief		Handles drawing images to the screen at runtime.
 *	\details	
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		18/01/2013
 *	\todo finish implementing this class properly without test objects
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _RENDERER_H_
# define _RENDERER_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include <Windows.h>
#include "bpMesh.h"
#include "../Graphics/ShaderProgram.h"

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
class Window;
class Camera;
class Node;
class ShaderProgram;
class bpMesh;

//////////////////////////////////////////////////////////////////////////
class Renderer
{
public:
	/*! \brief Creates the singleton object.
	 *  \param a_pWindow - Takes in the window object so the renderer knows which window it is rendering to.
	 *  \return Renderer* - returns the singleton object.
	 */
	static Renderer* Create(Window* a_pWindow);

	/*! \brief This fucntions gets the signleton object.
	 *  \return Renderer - returns an object of the renderer. 
	 */
	static Renderer* Get();

	/*! \brief Releases the Singleton clearing all memory.
	 */
	virtual void Release();

	/*! \brief prepares the next frame for rendering. all draw calls should happen after this per frame.
	 */
	void BeginFrame();

	/*! \brief Sends the frame off to be displayed on the window. all render calls per frame need to happen before this call.
	 */
	void EndFrame();

	/*! \brief Draws all objects under this Node from the current viewpoint supplied by the Camera object. this call needs to happen between Renderer::BeginFrame() and Renderer::EndFrame()
	 *  \param a_kNode - root object that all objects will be rendered from.
	 *	\param a_kCamera - Camera perspective to be rendered from.
	 *	\sa Renderer::BeginFrame()
	 *	\sa Renderer::EndFrame()
	 */
	void DrawScene(Node& a_kNode , Camera& a_kCamera, ShaderProgram a_kProgram);

	void SetDefaultShaderprogram(ShaderProgram a_kProgram);

private:
	Renderer(Window* a_pWindow);
	~Renderer();
	static Renderer* m_pSingleton;
	HDC m_hDC;
	HGLRC m_hRC;
	// other stuff needed for opengl renderer to function (limited includes in header)
	// temp stuff
	unsigned int m_uiMVPID; 

	ShaderProgram m_kDefaultProgram;

};
//////////////////////////////////////////////////////////////////////////
#endif // _RENDERER_H_
//////////////////////////////////////////////////////////////////////////
