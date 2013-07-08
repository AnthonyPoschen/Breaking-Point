//////////////////////////////////////////////////////////////////////////
///	< Author >	< Anthony Poschen >
///	< Date >	< 20/1/2013 >
/// < File >	< Mouse >
/// < Brief >	< Mouse implementation  >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "Mouse.h"
#include "../Graphics/Window.h"
#include "../Core/bzTime.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >
Mouse* Mouse::m_pSingleton = nullptr;

//////////////////////////////////////////////////////////////////////////
Mouse::Mouse()
	:m_iXPrev(-1), m_iYPrev(-1), m_uiScrollVal(0) , m_bScrollDown(0) , m_bScrollUp(0) , m_bLockToScreen(false) , m_bLockToWindow(false)
{

	m_pVKMap[0] = VK_LBUTTON;
	m_pVKMap[1] = VK_RBUTTON;
	m_pVKMap[2] = VK_MBUTTON;

	memset(m_bButtonCurr,0,sizeof(m_bButtonCurr));
	memset(m_bButtonPrev,0,sizeof(m_bButtonPrev));
	memset(m_fLastClickTime,0,sizeof(m_fLastClickTime));
	memset(m_bDoubleClicked,0,sizeof(m_bDoubleClicked));


	// need a proper system timer before this can be implemented.
	unsigned int uiDoubleClickTime = GetDoubleClickTime(); // gets the double click time in miliseconds
	m_fDoubleClickTime = (float)uiDoubleClickTime / 1000;
}

//////////////////////////////////////////////////////////////////////////
Mouse::~Mouse()
{

}

//////////////////////////////////////////////////////////////////////////
Mouse* Mouse::Create()
{
	if(m_pSingleton == nullptr)
		m_pSingleton = new Mouse();
	return m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
Mouse* Mouse::Get()
{
	return m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
void Mouse::Release()
{
	if(m_pSingleton != nullptr)
		delete m_pSingleton;
}

//////////////////////////////////////////////////////////////////////////
void Mouse::Update()
{
	
	if((m_bLockToWindow || m_bLockToScreen) & Window::Get()->IsActive())
	{
		RECT kWndRect, kScrnRect, kScrntoWndRect;
		//LPRECT
		GetWindowRect(Window::Get()->GetHandle(),&kWndRect);
		GetClientRect(Window::Get()->GetHandle(),&kScrnRect);
		if(m_bLockToScreen)
		{
			// clips the cursor to within the borders of the window leaving it inside the game
			unsigned int uiThinBorder = (kWndRect.right - kWndRect.left - kScrnRect.right) / 2;  
			kScrntoWndRect.left = kWndRect.left + uiThinBorder;
			kScrntoWndRect.right = kWndRect.right - uiThinBorder;
			kScrntoWndRect.bottom = kWndRect.bottom - uiThinBorder;
			kScrntoWndRect.top = kWndRect.bottom - uiThinBorder - kScrnRect.bottom;
			ClipCursor(&kScrntoWndRect);
		}
		else
			ClipCursor(&kWndRect);
	}

	else
	{
		ClipCursor(nullptr);
	}

	m_iXPrev = m_iXCurr;
	m_iYPrev = m_iYCurr;

	POINT oPos;
	GetCursorPos(&oPos);
	
	m_iXCurr = oPos.x;
	m_iYCurr = oPos.y;
	
	ScreenToClient(Window::Get()->GetHandle(),&oPos);
	m_iXLocalCurr = oPos.x;
	m_iYLocalCurr = oPos.y;

	for(int i = 0; i < BUTTON_COUNT; ++i)
	{
		m_bButtonPrev[i] = m_bButtonCurr[i];
		short iResult = GetAsyncKeyState(m_pVKMap[i]);
		if(iResult != 0)
			m_bButtonCurr[i] = true;
		else
			m_bButtonCurr[i] = false;
	}
	if(m_uiScrollVal > 0)
	{
		m_bScrollUp = true;
		m_bScrollDown = false;
	}
	else if(m_uiScrollVal < 0)
	{
		m_bScrollUp = false;
		m_bScrollDown = true;
	}
	else
	{
		m_bScrollUp = false;
		m_bScrollDown = false;
	}
	m_uiScrollVal = 0;
	
	// handle double clicks
	if(bzTime::Get() != nullptr)
	{
		m_fCurrentTime = bzTime::Get()->ElapsedTime();

		for(int i = 0; i < BUTTON_COUNT; ++i)
		{
			if(IsButtonPressed(i) && m_bDoubleClicked[i])
			{
				m_bDoubleClicked[i] = false;
				m_fLastClickTime[i] = m_fCurrentTime;
				continue;
			}

			m_bDoubleClicked[i] = false;

			if(IsButtonPressed(i))
			{
				if(m_fCurrentTime - m_fLastClickTime[i] < m_fDoubleClickTime)
				{
					m_bDoubleClicked[i] = true;
				}
				m_fLastClickTime[i] = m_fCurrentTime;
			}
		}
	}


	// handle if their was a double click now

}

//////////////////////////////////////////////////////////////////////////
void Mouse::LockToWindow(bool a_bLock)
{
	m_bLockToWindow = a_bLock;
}

//////////////////////////////////////////////////////////////////////////
void Mouse::LockToScreen(bool a_bLock)
{
	m_bLockToScreen = a_bLock;
}

//////////////////////////////////////////////////////////////////////////
bool Mouse::IsLockedToScreen()
{
	return m_bLockToScreen;
}

//////////////////////////////////////////////////////////////////////////
bool Mouse::IsLockedToWindow()
{
	return m_bLockToWindow;
}

//////////////////////////////////////////////////////////////////////////
bool Mouse::IsButtonDown(unsigned int a_uiButton)
{
	return (Mouse::Get()->m_bButtonCurr[a_uiButton] == true &&
		Mouse::Get()->m_bButtonPrev[a_uiButton] == true);
}

//////////////////////////////////////////////////////////////////////////
bool Mouse::IsButtonUp(unsigned int a_uiButton)
{
	return (Mouse::Get()->m_bButtonCurr[a_uiButton] == false &&
		Mouse::Get()->m_bButtonPrev[a_uiButton] == false);
}

//////////////////////////////////////////////////////////////////////////
bool Mouse::IsButtonPressed(unsigned int a_uiButton)
{
	return (Mouse::Get()->m_bButtonCurr[a_uiButton] == true &&
		Mouse::Get()->m_bButtonPrev[a_uiButton] == false);
}

//////////////////////////////////////////////////////////////////////////
bool Mouse::IsButtonDoublePress(unsigned int a_uiButton)
{
	if(IsButtonPressed(a_uiButton))
	{
		if(Mouse::Get()->m_bDoubleClicked[a_uiButton])
		{
			Get()->m_bDoubleClicked[a_uiButton] = false;
			return true;
		}
		
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
bool Mouse::IsButtonReleased(unsigned int a_uiButton)
{
	return (Mouse::Get()->m_bButtonCurr[a_uiButton] == false &&
		Mouse::Get()->m_bButtonPrev[a_uiButton] == true);
}

//////////////////////////////////////////////////////////////////////////
bool Mouse::IsScrollingUp()
{
	return Mouse::Get()->m_bScrollUp;
}

//////////////////////////////////////////////////////////////////////////
bool Mouse::IsScrollingDown()
{
	return Mouse::Get()->m_bScrollDown;
}

void Mouse::GetPositionToScreen(int& a_iX , int& a_iY)
{
	a_iX = m_iXCurr;
	a_iY = m_iYCurr;
}

void Mouse::GetPosition(int& a_iX , int& a_iY)
{
	a_iX = m_iXLocalCurr;
	a_iY = m_iYLocalCurr;
}

float2 Mouse::bpGetPos()
{
	return float2((float)Get()->m_iXLocalCurr,(float)Get()->m_iYLocalCurr);
}

float2 Mouse::bpGetPosToScreen()
{
	return float2((float)Get()->m_iXCurr,(float)Get()->m_iYCurr);
}

void Mouse::Show(bool a_bShow)
{
	if(Get()->m_bShow == a_bShow)
		return;
	Get()->m_bShow = a_bShow;
	if(a_bShow == false)
		while(ShowCursor(false) > 0);
	else
		while(ShowCursor(true) < 1);
}