//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 19 - 1 - 2013 >
/// < Class Brief >	< Window class this handles creating a Win32 Window  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _WINDOW_H_
#define _WINDOW_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include <Windows.h>
#include <WindowsX.h>
#include <iostream>
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class Window
{
public:
	static Window* Create(const char* a_pcName = "New Application", int a_iWidth = 480, int a_iHeight = 640, bool a_bWindowed = true, bool a_bBordered = true );
	static Window* Get();
	int GetHeight();
	int GetWidth();
	void Release();
	HWND GetHandle();
	bool Tick();
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
