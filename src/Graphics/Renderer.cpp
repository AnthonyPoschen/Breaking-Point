//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 20/1/2013 >
// < File >	< Renderer >
// < Brief >	< implementation of the renderer (currently jsut OpenGl no bridge to Directx >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	< Includes >
#include "Renderer.h"

#include "../Graphics/Window.h"
#define GLEW_STATIC

#include "../Include/glew.h"

#include "../Core/Camera.h"
#include "../Graphics/ShaderProgram.h"

//////////////////////////////////////////////////////////////////////////
// < Forward Declares >
Renderer* Renderer::m_pSingleton = nullptr;
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};

//////////////////////////////////////////////////////////////////////////
Renderer* Renderer::Create(Window* a_pWindow)
{
	if(m_pSingleton == nullptr)
		m_pSingleton = new Renderer(a_pWindow);
	return m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
Renderer* Renderer::Get()
{
	return m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
void Renderer::Release()
{
	if(m_pSingleton)
		delete m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
Renderer::Renderer(Window* a_pWindow)
{
	//force GLEW to use a modern OpenGL method for checking if a function is available.


	m_hDC = GetDC(Window::Get()->GetHandle());
	
	int pf = 0;
	PIXELFORMATDESCRIPTOR pfd = {0};
	OSVERSIONINFO osvi = {0};

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
	if (!GetVersionEx(&osvi))
		throw std::runtime_error("GetVersionEx() failed.");

	pf = ChoosePixelFormat(m_hDC, &pfd);

	if (!SetPixelFormat(m_hDC, pf, &pfd))
		throw std::runtime_error("SetPixelFormat() failed.");


	if (osvi.dwMajorVersion > 6 || (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion >= 0))
		pfd.dwFlags |= PFD_SUPPORT_COMPOSITION;


	HGLRC tempContext = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, tempContext);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

	}

	int attribListGL42[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	
	if(wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		m_hRC = wglCreateContextAttribsARB(m_hDC,0,attribListGL42);
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(tempContext);
	}
	else
		m_hRC = tempContext;
	

	

	if (!wglMakeCurrent(m_hDC, m_hRC))
		throw std::runtime_error("wglMakeCurrent() failed for OpenGL 4.2 context.");
	
	const char* GLVersionString = (const char*)glGetString(GL_VERSION);
	
	glViewport(0,0,Window::Get()->GetWidth(),
		Window::Get()->GetHeight());


	// temp
	TestMesh = new bzMesh;
	m_uiMVPID  = 0; 
}

//////////////////////////////////////////////////////////////////////////
Renderer::~Renderer()
{
	delete TestMesh;
	wglDeleteContext(m_hRC);
}

//////////////////////////////////////////////////////////////////////////
void Renderer::BeginFrame()
{
	glClearColor(0.4f,0.4f,0.4f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

//////////////////////////////////////////////////////////////////////////
void Renderer::EndFrame()
{
	SwapBuffers(m_hDC);
}
 
//////////////////////////////////////////////////////////////////////////
void Renderer::DrawScene(Node& a_kNode , Camera& a_kCamera, ShaderProgram a_kProgram)
{

	matrix4 mViewProj = a_kCamera.GetViewProjMatrix();
	matrix4 mView = a_kCamera.GetViewMatrix();
	matrix4 mProj = a_kCamera.GetProjMatrix();
	matrix4 mModelMat , mTranslate , mRotate , mScale;
	matrix4 mMVP;
	
	//rotate testmesh
	matrix3 oMat = TestMesh->GetTransform().m_kRotate;
	
	// for every object do the below
	Transform oTransform = TestMesh->GetWorldTransform();
	matrix4::MakeScaleMatrix(mScale,oTransform.m_fScale);
	matrix4::MakeRotate(mRotate,oTransform.m_kRotate);
	matrix4::MakeTranslateMatrix(mTranslate,oTransform.m_kTranslate);
	
	// times the matricies together to get the MVP
	mModelMat = mScale * mRotate * mTranslate  ;
	mMVP = mModelMat * mView * mProj ;


	// render object with its shader
	glUseProgram(a_kProgram.m_uiProgramID);
	// get the uniform and put in the model view projection matrix (this needs to be called after use program
	m_uiMVPID = glGetUniformLocation(a_kProgram.m_uiProgramID,"MVP");
	glUniformMatrix4fv(m_uiMVPID,1,GL_FALSE,&mMVP.m_v[0]);

	TestMesh->Render();
	glUseProgram(0);
	

}
 
