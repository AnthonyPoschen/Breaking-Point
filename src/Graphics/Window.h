//////////////////////////////////////////////////////////////////////////
/*! \class		Window
 *  \brief		This class handles loading a Win32 window in windows. 
 *	\details	all options for this window are managed from within this object.
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		19/01/2013
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _WINDOW_H_
# define _WINDOW_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include <Windows.h>
#include <WindowsX.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 


//////////////////////////////////////////////////////////////////////////
class Window
{
public:

	/*! \brief Creates the Application window from the windows operating system.
	 *  \param a_pcName [in] - This names the application window on the top right. can be blank
	 *	\param a_iWidth [in] - Width of the window to be created
	 *	\param a_iHeight [in] - Height of the window to be created
	 *	\param a_bWindowed [in] - should the window start in windowed mode.
	 *	\param a_bBordered [in] - should the application be bordered.
	 *  \return Window* - the pointer to the window singleton.
	 */
	static Window* Create(const char* a_pcName = "New Application", int a_iWidth = 480, int a_iHeight = 640, bool a_bWindowed = true, bool a_bBordered = true );
	
	/*! \brief Returns the singleton object of this class
	 *  \return Window* - refrence to the singleton object.
	 */
	static Window* Get();
	
	/*! \brief Release the singleton object freeing all used memory.
	 */
	virtual void Release();

	/*! \brief Gets the window Height
	 *  \return int - Height of the window
	 *	\sa Window::GetWidth()
	 */
	int GetHeight();

	/*! \brief Gets the Window Width
	 *  \return int - Width of the Window
	 *	\sa Window::GetWidth()
	 */
	int GetWidth();

	/*! \brief Gets the HWND object assigned by the operating system
	 *  \return HWND - returns the assigned object from the OS. (windows Object)
	 */
	HWND GetHandle();

	/*! \brief This Tick is to check if the window is still alive. it also handles all windows commands which can either be ignored or passed on to windows to handle with a default response
	 *  \return bool - Is the window still alive or has it closed.
	 */
	bool Tick();

	/*! \brief Returns the status of if this is the Active window on the OS. Returns false if say you are alt tabbed out. very usefull to help minimilse cpu usage if the application is only in the background.
	 *  \return bool - Is this Window the currently Active window on the OS.
	 */
	bool IsActive();

private:

	Window(const char* a_pcName , int a_iWidth , int a_iHeight , bool a_bWindowed , bool a_bBordered);
	~Window();
	static Window* m_pSingleton;

	WNDCLASSEX sm_oWindowClass;
	HINSTANCE m_hInstance;

	HWND m_oHwnd;
	int m_iHeight , m_iWidth;
	ATOM  m_WC;
	static LRESULT CALLBACK WindowProc(HWND Handle, unsigned int msg, WPARAM wParam, LPARAM lParam);

	// console pointer
	FILE** m_ppConsole;

};
//////////////////////////////////////////////////////////////////////////
#endif // _WINDOW_H_
//////////////////////////////////////////////////////////////////////////
