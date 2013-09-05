//////////////////////////////////////////////////////////////////////////
/*! \class		Mouse
 *  \brief		This handles all Mouse input from the end users computer.
 *	\details	Handles all presses and scroll wheel movement.
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		20/01/2013
 *  \copyright N/A
 *	\todo finish commenting this class
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _MOUSE_H_
# define _MOUSE_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 
#include "../Math/float2.h"

//////////////////////////////////////////////////////////////////////////
//  Forward Declares 


//////////////////////////////////////////////////////////////////////////
class Mouse
{
	friend class Window;
public:

	/*! \enum eBUTTONS
	 *  \brief Mouse Buttons refrence.
	 */
	enum eBUTTONS : unsigned int
	{
		LEFT,
		RIGHT,
		MIDDLE,
		BUTTON_COUNT
	};

	/*! \brief Create the Singleton object.
	 *  \return Mouse* - Refrence to the singleton object.
	 */
	static Mouse* Create();

	/*! \brief Get the singleton object.
	 *  \return Mouse* - Returns the Singleton object.
	 */
	static Mouse* Get();

	/*! \brief Release the singleton object freeing all memory.
	 */
	virtual void Release();

	// python support functions
	static float2 bpGetPos();
	static float2 bpGetPosToScreen();
	 



	void Update();

	/*! \brief Get the position of the Mouse cursor relative to the Window.
	 *  \param a_iX [out] - Sets this to the X position of the mouse relative to the windows top left corner.
	 *	\param a_iY [out] - Sets this to the Y position of the mouse relative to the windows top left corner.
	 */
	void GetPosition(int& a_iX , int& a_iY);

	/*! \brief Gets the position of the mouse cursor relative to the computer screen(s)
	 *  \param a_iX [out] - Sets this to the X position of the mouse relative to the computer screen(s)
	 *	\param a_iY [out] - Sets this to the Y position of the mouse relative to the computer screen(s)
	 */
	void GetPositionToScreen(int& a_iX , int& a_iY);

	/*! \brief Sets the visibility of the Mouse cursor. (usefull to turn off if using custom designed mouse cursor.
	 *  \param a_bShow [in] - TRUE = Show Mouse on window. FALSE = dont show mouse cursor on window.
	 */
	static void Show(bool a_bShow);

	/*! \brief Lock the mouse from leaving the window (includes border of window)
	 *  \param a_bLock [in] - To lock or not to lock the mouse.
	 */
	void LockToWindow(bool a_bLock);

	/*! \brief Lock the Mouse to only the screen space within the window. this does not allow access to the border area of the window.
	 *  \param a_bLock [in] - to lock or not to lock the mouse.
	 */
	void LockToScreenSpace(bool a_bLock);

	/*! \brief Check if the Mouse is currently locked to the screen space of the window
	 *  \return bool - Status of mouse lock state.
	 */
	bool IsLockedToScreenSpace();

	/*! \brief Check if the mouse is locked to the window of the application (includes border frame)
	 *  \return bool - status of mouse lock state.
	 */
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
	bool m_bLockToWindow, m_bLockToScreenSpace, m_bShow;

	float 	m_fDoubleClickTime;
	float	m_fLastClickTime[3];
	bool	m_bDoubleClicked[3];
	float	m_fCurrentTime;
};
//////////////////////////////////////////////////////////////////////////
#endif // _MOUSE_H_
//////////////////////////////////////////////////////////////////////////
