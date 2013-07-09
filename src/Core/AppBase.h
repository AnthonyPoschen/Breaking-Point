//////////////////////////////////////////////////////////////////////////
/*! \class		AppBase
 *  \brief      Main Application Singleton. 
 *  \details    this class is derived from and handles the main app loop
 *  \author     Anthony Poschen
 *  \version    1.0
 *  \date       20 / 01 / 2013
 *  \copyright  N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _APPBASE_H_
#define _APPBASE_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 


//////////////////////////////////////////////////////////////////////////
class AppBase
{
	/*! FLAGS enum, Application State*/
	enum FLAGS
	{
		FLAGS_CREATED	= (1<<0), /*< Application Currently Running  */
		FLAGS_DESTROYED	= (1<<1), /*< Application Not Running */
	};

public:

	static AppBase* GetSingleton()	{	return sm_pSingleton;	}

	// Create the app, passing in the command line
	bool	Create(const char* a_sCmdLine);

	// Our game loop
	void	Execute();

	// Closes the program
	void	Destroy();

	// Check if the application was created successfully
	bool	IsCreated();

	// Utility to display a windows Message Box
	void	DisplayErrorMessageBox(const char* a_sMessage);

	AppBase();
	virtual ~AppBase();

protected:
	/*! \brief Create application objects. this function must be derived. it is called from AppBase::Create() after the singleton is setup.
	 *  \param const char* a_sCmdLine - this is the entry arguments to the application
	 *  \exception fails if something can not be setup
	 *  \return bool - result of setting up
	 *	\sa AppBase::Create()
	 */
	virtual bool	OnCreate(const char* a_sCmdLine) = 0;

	/*! \brief This function is your apps loop. this is only called while the application is the focus (i.e is active window), and loops constantly. when this returns false Destroy is called.
	 *  \return bool - True = App still alive. | False = App has ended close me down
	 */
	virtual bool	OnUpdate() = 0;

	/*! \brief When the app is Idling. While idling this is called instead of update. this allows better management of what happens in the app,
				so their is less lagg for the end user who isnt using the app.
	 *  \return bool - result of the idle. 
	 */
	virtual bool	OnIdle() = 0;

	/*! \brief Destruction of the application. Destruction happens within this function at the end of the applications lifetime.
	 */
	virtual void	OnDestroy() = 0;

	/*! \brief Rendering Process. this function is where all rendering related calls should occur this is called after OnUpdate() per loop.
	 */
	virtual void	OnRender() = 0;
	

private:


	// Application flags (created/destroyed) add your own if desired
	unsigned int			m_uiFlags;//<!	Stores current State of AppBase

	// Singleton handle to the Application instance
	static AppBase*			sm_pSingleton;//<!	Stores singleton Pointer.
};
//////////////////////////////////////////////////////////////////////////
#endif // _APPBASE_H_
//////////////////////////////////////////////////////////////////////////

/*! \fn bool AppBase::Create(const char* a_sCmdLine);
 *  \brief Creates the application
 *  \param a_sCmdLine const char* which has the entry point arguments to the application prefrably
 *  \return bool -  If creating was successfull (also returns true if already exists)
 */

/*! \fn void AppBase::Execute()
 *  \brief Enters main loop which only exits once application is finished
 *  \return returns when program has finished.
 */

/*! \fn void AppBase::Destroy()
 *  \brief call singleton destructor and OnDestroy(). This should be called after Execute returns
 *  \return returns once AppBase has been destroyed.
 */

/*! \fn bool AppBase::IsCreated()
 *  \brief check to see if App Exists
 *  \return bool - result of if Singleton (sm_pSingleton) of AppBase is non NULL
 */

/*! \fn static AppBase* AppBase::GetSingleton()
 *  \brief Fetch the Application Pointer.
 *  \return returns a pointer to sm_pSingleton allowing direct access on its members.
 */

/*! \fn void AppBase::DisplayErrorMessageBox(const char* a_sMessage);
 *  \brief shows an error message to the screen
 *  \param const char* a_sMessage - this is the message to be displayed in the error box
 *	\todo This function is not implemented at all. just a function prototype.
 */

 