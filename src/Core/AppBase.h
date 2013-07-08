//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 20 - 1 - 2013 >
/// < Class Brief >	< This is the core Aplication base that Application will derive from  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _APPBASE_H_
#define _APPBASE_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >

//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class AppBase
{
	enum FLAGS
	{
		FLAGS_CREATED	= (1<<0),
		FLAGS_DESTROYED	= (1<<1),
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
	
	virtual bool	OnCreate(const char* a_sCmdLine) = 0;
	virtual bool	OnUpdate() = 0;
	virtual bool	OnIdle() = 0;
	virtual void	OnDestroy() = 0;
	virtual void	OnRender() = 0;
	

private:


	// Application flags (created/destroyed) add your own if desired
	unsigned int			m_uiFlags;

	// Singleton handle to the Application instance
	static AppBase*			sm_pSingleton;
};
//////////////////////////////////////////////////////////////////////////
#endif // _APPBASE_H_
//////////////////////////////////////////////////////////////////////////
