//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 18 - 1 - 2013 >
/// < Class Brief >	< Rendering class for rendering to screen  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _RENDERER_H_
#define _RENDERER_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include <Windows.h>
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >
class Window;
class Camera;
class Node;
class ShaderProgram;
class bzMesh;
#include "bzMesh.h"
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
