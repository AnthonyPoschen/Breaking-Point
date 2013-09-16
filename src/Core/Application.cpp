//////////////////////////////////////////////////////////////////////////
// < Author >	< Anthony Poschen >
// < Date >		< 3/2/2013 >
// < File >		< Application >
// < Brief >	< Main Application Loop Management >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	< Includes >

#include "Application.h"

#include "../include/glew.h"
#include "../include/wglew.h"
#include <gl/glu.h>
#include <boost/filesystem.hpp>
#include "Node.h"
#include "Camera.h"
#include "../Graphics/ShaderFactory.h"
#include "../Graphics/ShaderProgram.h"
#include "bpPython.h"
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
	bpPython::Create();
	bzTime::Create();
	Mouse::Create();
	Keyboard::Create();
	Renderer::Create(Window::Get());
	ShaderFactory::Create();
	ShaderFactory::Get()->Initilise(".\\Data\\Shaders\\");
	m_kShaderProgram.LoadShaderProgram("oProgram");
	Renderer::Get()->SetDefaultShaderprogram(m_kShaderProgram);
	bpPython::exec("import MyModule");
	m_kRootNode = NodePtr( new Node());
	m_kRootNode->SetWorldTranslate(float3(0,0,0));
	Camera::Frustrum oFrustrum;
	oFrustrum.m_fNear = 0.001f;
	oFrustrum.m_fFar = 10000.0f;
	oFrustrum.m_fFieldOfView = 90.0f;
	oFrustrum.m_fScreenAspectRatio = (float)Window::Get()->GetWidth() / (float)Window::Get()->GetHeight();
	Camera* oCam = new Camera(oFrustrum);
	oCam->SetWorldTranslate(float3(-10,30,30));
	oCam->LookAt(float3(0,0,0),float3(0,1,0));
	oCam->SetName("cam");
	//m_kRootNode->AttachChild(oCam);
	m_kpCamera = oCam;
	m_kRootNode->SetName("root");
	m_kRootNode->SetScale(1.0f);

	// use case of adding a property then getting it back out
	PropertyPtr oPtr(new bpMesh());
	Node* oNode1 = new Node;
	oNode1->SetName("Node1");
	oNode1->AttachProperty(oPtr);
	oNode1->SetTranslate(float3(-10,0,0));
	PropertyPtr oProp = oNode1->GetProperty(Property::PROPERTY_TYPE::MESH);
	bpMesh* opMesh = Utilities::DynamicCast<bpMesh>((oProp.get()));
	m_kRootNode->AttachChild(oNode1);
	//end use case
	fDegree = 0;

	Node* oNode2 = new Node;
	oNode2->SetTranslate(float3(5,0,0));
	PropertyPtr oPropptr(new bpMesh());
	oNode2->AttachProperty(oPropptr);
	oNode2->SetName("Node2");
	oNode1->AttachChild(oNode2);

	m_kRootNode->Update(0);
	return true;
}


//////////////////////////////////////////////////////////////////////////
bool Application::OnUpdate()
{
	bzTime::Get()->Update();
	Mouse::Get()->Update();
	Keyboard::Get()->Update();

	fDegree +=1.25 * bzTime::Get()->DeltaTime();
	if(Mouse::Get()->IsButtonDoublePress(Mouse::LEFT))
	{
		int i = 10;
	}

	float3 kPos = m_kpCamera->GetTranslate();
	if(m_bfilp == true)
	{
		kPos.X -= 2.0f * bzTime::Get()->DeltaTime();
		if(kPos.X < -20.0f)
			m_bfilp = false;
	}
	else
	{
		kPos.X += 2.0f * bzTime::Get()->DeltaTime();
		if(kPos.X > 20.0f)
			m_bfilp = true;
	}


	m_kpCamera->LookAt(float3(-10,0,0),float3(0,1,0));
	//m_kpCamera->SetTranslate(kPos);

	Transform oTransform = m_kRootNode->GetChildByName("Node1")->GetTransform();
	Transform oTransform2 = m_kRootNode->GetChildByName("Node2")->GetTransform();

	Quaternion::FromAxisAngle(float3(0,1,0),fDegree).ToMatrix3(	oTransform.m_kRotate);
	Quaternion::FromAxisAngle(float3(0,1,0),-fDegree).ToMatrix3(oTransform2.m_kRotate);
	m_kRootNode->GetChildByName("Node1")->SetTransform(oTransform);
	m_kRootNode->GetChildByName("Node2")->SetTransform(oTransform2);
	bpPython::exec("MyModule.Speak();");
	
	m_kRootNode->Update(bzTime::Get()->DeltaTime());
	m_kpCamera->Update(bzTime::Get()->DeltaTime());
	AVObject* oObj;

	float3 kCamPos = m_kpCamera->GetWorldTransform().m_kTranslate;
	
	oObj = (AVObject*)m_kRootNode.get();
	float3 kRootPos = oObj->GetWorldTransform().m_kTranslate;

	oObj = m_kRootNode->GetChildByName("Node1");
	float3 kNode1 = oObj->GetWorldTransform().m_kTranslate;

	oObj = m_kRootNode->GetChildByName("Node2");
	float3 kNode2 = oObj->GetWorldTransform().m_kTranslate;


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
	bpPython::Get()->Release();
	Renderer::Get()->Release();
	Mouse::Get()->Release();
	Keyboard::Get()->Release();
	bzTime::Get()->Release();
	Utilities::ConsoleShow(false);
	Window::Get()->Release();
	m_kRootNode.reset();
}

