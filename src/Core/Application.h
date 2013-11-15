//////////////////////////////////////////////////////////////////////////
/*! \class		Application
 *  \brief      Main Application Entry Point and management. 
 *  \details    this class inherits from AppBase and creates the 
				virtual functions needed to work
 *  \author     Anthony Poschen
 *  \version    1.0
 *  \date       03 / 02 / 2013
 *  \copyright  N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
//////////////////////////////////////////////////////////////////////////
// Includes
#include "../bzCore.h"
#include "AppBase.h"
#include "../Graphics/ShaderProgram.h"
#include <boost/python.hpp>
#include <Python.h>

//////////////////////////////////////////////////////////////////////////
// Forward Declares 
class Node;
class Camera;
class ShaderProgram;
class PhysicsWorld;

//////////////////////////////////////////////////////////////////////////
class Application : public AppBase
{
public:
	Application(){};
	virtual ~Application(){};
	NodePtr			m_kRootNode;//!<		Root Scene Node (used for rendering and managing a scene graph)
	Camera*			m_kpCamera;//!<			Main Camera.
	ShaderProgram	m_kShaderProgram;//!<	Temp var for testing purposes
	PhysicsWorld*	m_kpPhysicsWorld;//!<	Physics world simulation object
	bool m_bfilp;//!<						temp ver used for testing purposes
	float fDegree;
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

/*! \fn virtual bool Application::OnCreate(const char* a_sCmdLine)
 *  \brief This is where all objects / services needed are created
 *  \param a_sCmdLine const char* - this is the arguments passed to the app
 *  \return bool - result of setup. if fail application terminates.
 */

/*! \fn virtual bool Application::OnUpdate()
 *  \brief This function is called within the application loop. it is designed to handle all logic within the application
 *  \return bool - TRUE = app alive | FALSE = app finished close down
 */

/*! \fn virtual bool Application::OnIdle()
 *  \brief this is called when the application is idling. this is determined by if the application's window has the focus if not then it idles,
		   this allows a different update process to occur when the user is not using the application to reduce load on the computer
 *  \return bool - TRUE = app alive | FALSE = app finished
 */

/*! \fn virtual void Application::OnRender()
 *  \brief this is part of the constant loop. No logic should be placed in here, only rendering related calls should be made as this is called directly after Application::OnUpdate()
 */

/*! \fn virtual void Application::OnDestroy()
 *  \brief This Function Destroys all Objects / services. place all cleanup code in here.
 */