//////////////////////////////////////////////////////////////////////////
/*! \class		Renderer
 *  \brief		Handles drawing images to the screen at runtime.
 *	\details	
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		18/01/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _RENDERER_H_
# define _RENDERER_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include <Windows.h>
#include "bzMesh.h"

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 
class Window;
class Camera;
class Node;
class ShaderProgram;
class bzMesh;

//////////////////////////////////////////////////////////////////////////
class Renderer
{
public:

	static Renderer* Create(Window* a_pWindow);
	static Renderer* Get();
	void Release();
	void BeginFrame();
	void EndFrame();
	void DrawScene(Node& a_kNode , Camera& a_kCamera, ShaderProgram a_kProgram);

private:
	Renderer(Window* a_pWindow);
	~Renderer();
	static Renderer* m_pSingleton;
	HDC m_hDC;
	HGLRC m_hRC;
	// other stuff needed for opengl renderer to function (limited includes in header)

	// temp stuff
	bzMesh* TestMesh;
	unsigned int m_uiMVPID;
};
//////////////////////////////////////////////////////////////////////////
#endif // _RENDERER_H_
//////////////////////////////////////////////////////////////////////////
