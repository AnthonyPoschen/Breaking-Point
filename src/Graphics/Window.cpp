//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 19/1/2013 >
//  < File >	< Window >
//  < Brief >	< window implementation for Windows.  >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	< Includes >
#include "Window.h"
#include "../Input/Mouse.h"
#include <stdlib.h>
#include "../Core/Utilities.h"
//////////////////////////////////////////////////////////////////////////
// < Forward Declares >
Window* Window::m_pSingleton = nullptr;

//////////////////////////////////////////////////////////////////////////
Window* Window::Create(const char* a_pcName /* = "New Application" */, int a_iWidth /* = 480 */, int a_iHeight /* = 640 */, bool a_bWindowed /* = true */, bool a_bBordered /* = true */ )
{
	if(m_pSingleton == nullptr)
		m_pSingleton = new Window(a_pcName,a_iWidth,a_iHeight,a_bWindowed,a_bBordered);
	return m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
void Window::Release()
{
	if(m_pSingleton)
		delete m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
Window::Window(const char* a_pcName , int a_iWidth , int a_iHeight , bool a_bWindowed , bool a_bBordered)
	:m_oHwnd(0),
	m_iWidth(a_iWidth),
	m_iHeight(a_iHeight),
	m_ppConsole(nullptr)
{
	int iPosX , iPosY;
	DEVMODE dmScreenSettings;

	m_hInstance = GetModuleHandle(0);
	// Setup the windows class with default settings.
	sm_oWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;
	sm_oWindowClass.lpfnWndProc = WindowProc;
	sm_oWindowClass.cbClsExtra = 0;
	sm_oWindowClass.cbWndExtra = 0;
	sm_oWindowClass.hInstance = m_hInstance;
	sm_oWindowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	sm_oWindowClass.hIconSm = sm_oWindowClass.hIcon;
	sm_oWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	sm_oWindowClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	sm_oWindowClass.lpszMenuName = NULL;
	sm_oWindowClass.lpszClassName = Utilities::StdStringToLPCWSTR(a_pcName);
	sm_oWindowClass.cbSize = sizeof(WNDCLASSEX);


	// Register the window class.
	RegisterClassEx(&sm_oWindowClass);
	RECT kRect = {0,0,m_iWidth,m_iHeight};
	int iWndWidth = m_iWidth;
	int iWndHeight = m_iHeight;
	if(a_bWindowed == false)
	{
		m_iWidth  = GetSystemMetrics(SM_CXSCREEN);
		m_iHeight = GetSystemMetrics(SM_CYSCREEN);
		kRect.right = a_iWidth;
		kRect.top = a_iHeight;

		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0 , sizeof(dmScreenSettings));
		dmScreenSettings.dmSize	= sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)m_iWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)m_iHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// put the window to the top left corner for fullscreen
		iPosX = iPosY = 0;
	}
	else
	{


		if(a_bBordered)
		{
			AdjustWindowRect(&kRect,WS_OVERLAPPEDWINDOW,false);
			iWndWidth = kRect.right - kRect.left;
			iWndHeight = kRect.bottom - kRect.top;
		}

		// Place the window in the middle of the screen.
		iPosX = (GetSystemMetrics(SM_CXSCREEN) - iWndWidth)  / 2;
		iPosY = (GetSystemMetrics(SM_CYSCREEN) - iWndHeight) / 2;
	}


	m_oHwnd = CreateWindowEx(WS_EX_APPWINDOW, Utilities::StdStringToLPCWSTR(a_pcName), Utilities::StdStringToLPCWSTR(a_pcName), 
		a_bBordered ? WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU : WS_POPUP,
		iPosX, iPosY, iWndWidth , iWndHeight , NULL, NULL, m_hInstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_oHwnd, SW_SHOWNORMAL);
	SetForegroundWindow(m_oHwnd);
	SetFocus(m_oHwnd);
}

//////////////////////////////////////////////////////////////////////////
Window::~Window()
{
	if(m_oHwnd)
	{
		DestroyWindow(m_oHwnd);
		m_oHwnd = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
bool Window::Tick()
{
	MSG	msg;

	while(PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
	{
		if(!GetMessage(&msg, 0, 0, 0))
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

LRESULT CALLBACK Window::WindowProc(HWND Handle, unsigned int msg, WPARAM wParam, LPARAM lParam)
{
	//TwEventWin(Handle,msg,wParam,lParam);

	switch (msg)
	{
	case WM_SYSCOMMAND:
		{
			if (wParam == SC_CLOSE)
			{
				PostMessage(Handle,WM_DESTROY,0,0);
			}
			//drag move
			else if(wParam == 0xf012)
			{
				DefWindowProc(Handle,msg,wParam,lParam);
			}
			//resize window
			//0xf001 (left)
			//0xf002 (right)
			//0xf003 (top)
			//0xf004 (top left)
			//0xf005 (top Right)
			//0xf006 (bottom)
			//0xf007 (bottom left)
			//0xf008 (bottom Right)
			else if(wParam >= 0xf001 && wParam <= 0xf008)
			{
				// do nothing (blocks resizing the window)
			}
			// click on top bar applicaiton icon
			else if(wParam == 0xf093)
			{
				// nopthing needed to do yet?
			}
			else
				DefWindowProc(Handle,msg,wParam,lParam);
			break;
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

	case WM_MOUSEWHEEL:
		{
			if(Mouse::Get())
				Mouse::Get()->m_uiScrollVal = GET_WHEEL_DELTA_WPARAM(wParam);
			break;
		}

	case WM_DROPFILES:
		{
			HDROP hDrop = (HDROP)wParam;
			int iFileCount = DragQueryFile(hDrop,0xFFFFFFFF, nullptr, MAX_PATH);
			for(int i = 0;i < iFileCount;++i)
			{
				char a_szFileDir[256];
				DragQueryFile(hDrop,i,(LPWSTR)a_szFileDir,MAX_PATH);
				//m_pSingleton->OnDropFile(a_szFileDir);
			}
			DragFinish(hDrop);
			break;
		}
	case WM_HOTKEY:
	case WM_SYSCHAR:	// prevent ALT + key combinations from creating 'ding' sounds
		break;
	default: 
		return DefWindowProc(Handle,msg,wParam,lParam);
	};
	return 0;

}

Window* Window::Get()
{
	return m_pSingleton;
}

HWND Window::GetHandle()
{
	return m_oHwnd;
}

bool Window::IsActive()
{
	return (GetFocus() == m_oHwnd);
}

int Window::GetHeight()
{
	return m_iHeight;
}

int Window::GetWidth()
{
	return m_iWidth;
}
