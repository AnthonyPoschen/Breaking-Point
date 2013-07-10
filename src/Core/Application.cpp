//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 3/2/2013 >
// < File >	< Application >
// < Brief >	< Main Application Loop Management >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	< Includes >

//#include <Python.h>
//#include <boost/python.hpp>
//#include <boost/python/exec.hpp>
#include "Application.h"

#include "../include/glew.h"
#include "../include/wglew.h"
#include <gl/glu.h>
#include <boost/filesystem.hpp>
#include "Node.h"
#include "Camera.h"
#include "../Graphics/ShaderFactory.h"
#include "../Graphics/ShaderProgram.h"
#include "bzPython.h"
#include <iostream>
#include <string>
#include "Utilities.h"

//////////////////////////////////////////////////////////////////////////
// < Forward Declares >

//////////////////////////////////////////////////////////////////////////
bool Application::OnCreate(const char* a_sCmdLine)
{
	
	Window::Create("my Window",1024 , 768 , true , true);
	Utilities::ConsoleShow();
	bzPython::Create();
	bzTime::Create();
	Mouse::Create();
	Keyboard::Create();
	Renderer::Create(Window::Get());
	ShaderFactory::Create();
	ShaderFactory::Get()->Initilise(".\\Data\\Shaders\\");
	m_kShaderProgram.LoadShaderProgram("oProgram");
	bzPython::exec("import MyModule");
	m_kRootNode = NodePtr( new Node());

	Camera::Frustrum oFrustrum;
	oFrustrum.m_fNear = 0.001f;
	oFrustrum.m_fFar = 1000.0f;
	oFrustrum.m_fFieldOfView = 90.0f;
	oFrustrum.m_fScreenAspectRatio = (float)Window::Get()->GetWidth() / (float)Window::Get()->GetHeight();
	Camera* oCam = new Camera(oFrustrum);
	oCam->SetWorldTranslate(float3(0,0,10));
	oCam->LookAt(float3(0,0,0),float3(0,1,0));
	m_kRootNode->AttachChild(oCam);
	m_kpCamera = oCam;
	m_kRootNode->Update(0);
	m_kRootNode->SetName("root");

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool Application::OnUpdate()
{
	bzTime::Get()->Update();
	Mouse::Get()->Update();
	Keyboard::Get()->Update();

	if(Mouse::Get()->IsButtonDoublePress(Mouse::LEFT))
	{
		int i = 10;
	}
	
	float3 kPos = m_kpCamera->GetTranslate();
	if(m_bfilp == true)
	{
		kPos.X -= 1.0f * bzTime::Get()->DeltaTime();
		if(kPos.X < -5.0f)
			m_bfilp = false;
	}
	else
	{
		kPos.X += 1.0f * bzTime::Get()->DeltaTime();
		if(kPos.X > 5.0f)
			m_bfilp = true;
	}


	m_kpCamera->LookAt(float3(0,0,0),float3(0,1,0));
	m_kpCamera->SetTranslate(kPos);
	bzPython::exec("MyModule.Speak();");

	m_kRootNode->Update(bzTime::Get()->DeltaTime());
	return Window::Get()->Tick();
}

//////////////////////////////////////////////////////////////////////////
bool Application::OnIdle()
{
	bzTime::Get()->Update();
	Mouse::Get()->Update();
	Keyboard::Get()->Update();
	Window::Get()->Tick();
	return true;
}
//////////////////////////////////////////////////////////////////////////
void Application::OnRender()
{
	Renderer::Get()->BeginFrame();
	Renderer::Get()->DrawScene(*m_kRootNode.get(),*m_kpCamera,m_kShaderProgram);

	Renderer::Get()->EndFrame();
}

//////////////////////////////////////////////////////////////////////////
void Application::OnDestroy()
{
	bzPython::Get()->Release();
	Renderer::Get()->Release();
	Mouse::Get()->Release();
	Keyboard::Get()->Release();
	bzTime::Get()->Release();
	Utilities::ConsoleShow(false);
	Window::Get()->Release();
	m_kRootNode.reset();
}

