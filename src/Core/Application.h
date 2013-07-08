//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 3 - 2 - 2013 >
/// < Class Brief >	< Main Application Entry Point and management  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >

#include "../bzCore.h"
#include "AppBase.h"
#include "../Graphics/ShaderProgram.h"
#include <boost/python.hpp>
#include <Python.h>
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >
class Node;
class Camera;
class ShaderProgram;


//////////////////////////////////////////////////////////////////////////
class Application : public AppBase
{
public:
	Application(){};
	virtual ~Application(){};
	NodePtr			m_kRootNode;
	Camera*			m_kpCamera;
	ShaderProgram	m_kShaderProgram;
	bool m_bfilp;
protected:
	virtual bool	OnCreate(const char* a_sCmdLine);
	virtual bool	OnUpdate();
	virtual bool	OnIdle(); // if application is alt tabbed / not focus replaces OnUpdate
	virtual void	OnRender();
	virtual void	OnDestroy();

	
	
private:

	
};
//////////////////////////////////////////////////////////////////////////
#endif // _APPLICATION_H_
//////////////////////////////////////////////////////////////////////////
