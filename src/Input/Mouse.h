//////////////////////////////////////////////////////////////////////////
///	< Author >		< Anthony Poschen >
/// < Date >		< 20 - 1 - 2013 >
/// < Class Brief >	< This keeps track of the mouse and helps does anything needed to be known about what the mouse is doing  >
//////////////////////////////////////////////////////////////////////////
///	< File Define >
#ifndef _MOUSE_H_
#define _MOUSE_H_
//////////////////////////////////////////////////////////////////////////
///	< Includes >
#include "../Math/float2.h"
//////////////////////////////////////////////////////////////////////////
/// < Forward Declares >


//////////////////////////////////////////////////////////////////////////
class Mouse
{
	friend class Window;
public:

	enum eBUTTONS : unsigned int
	{
		LEFT,
		RIGHT,
		MIDDLE,
		BUTTON_COUNT
	};

	static Mouse* Create();
	static Mouse* Get();
	void Release();

	// python support functions
	static float2 bpGetPos();
	static float2 bpGetPosToScreen();
	 



	void Update();
	void GetPosition(int& a_iX , int& a_iY);
	void GetPositionToScreen(int& a_iX , int& a_iY);


	static void Show(bool a_bShow);
	void LockToWindow(bool a_bLock);
	void LockToScreen(bool a_bLock);

	bool IsLockedToScreen();
	bool IsLockedToWindow();

	static bool IsButtonDown(unsigned int a_uiButton);
	static bool IsButtonUp(unsigned int a_uiButton);
	static bool IsButtonPressed(unsigned int a_uiButton);
	static bool IsButtonDoublePress(unsigned int a_uiButton);
	static bool IsButtonReleased(unsigned int a_uiButton);

	static bool IsScrollingUp();
	static bool IsScrollingDown();

protected:
	

private:
	Mouse();
	~Mouse();

	static Mouse* m_pSingleton;
	int m_iXCurr , m_iYCurr , m_iXPrev , m_iYPrev , m_iXLocalCurr , m_iYLocalCurr;

	short m_uiScrollVal;
	int m_pVKMap[BUTTON_COUNT];

	bool m_bButtonCurr[3] , m_bButtonPrev[3];
	bool m_bScrollUp , m_bScrollDown;
	bool m_bLockToWindow, m_bLockToScreen, m_bShow;

	float 	m_fDoubleClickTime;
	float	m_fLastClickTime[3];
	bool	m_bDoubleClicked[3];
	float	m_fCurrentTime;
};
//////////////////////////////////////////////////////////////////////////
#endif // _MOUSE_H_
//////////////////////////////////////////////////////////////////////////
