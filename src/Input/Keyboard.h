//////////////////////////////////////////////////////////////////////////
/*! \class		Keyboard
 *  \brief		This class Managed keystroke input from the end users keyboard.
 *	\details	can determine if keys are held down or just pressed or released.
 *  \details	
 *  \author		Anthony Poschen
 *  \version	1.0
 *  \date		10/10/2011
 *  \copyright N/A
 */
//////////////////////////////////////////////////////////////////////////
#ifndef _KEYBOARD_H_
# define _KEYBOARD_H_
//////////////////////////////////////////////////////////////////////////
//	Includes 


//////////////////////////////////////////////////////////////////////////
//  Forward Declares 


//////////////////////////////////////////////////////////////////////////
class Keyboard
{
public:

	/*! \brief Create the Singleton object for this class
	 *  \return Keyboard* - returns a refrence to the singleton object.
	 */
	static Keyboard*	Create();

	/*! \brief Get the Singleton object.
	 *  \return Keyboard* - refrence to the singleton object.
	 */
	static Keyboard*	Get();

	/*! \brief Release the singleton object freeing all of its memory.
	 */
	virtual void		Release();

	/*! \brief Update the state of the keyboard getting its current state. should only be called once per update.
	 */
	static void		Update();

	/*! \brief Is a Particular Keyboard key currently NOT pressed.
	 *  \param a_cKey - The KEY to be checked (USE ENUM KEY)
	 *  \return bool - True if key is up. False if the key is down.
	 */
	static bool		IsKeyUp(unsigned char a_cKey);

	/*! \brief Is a Particular keyboard key being pressed.
	 *  \param a_cKey - the KEY to be checked (USE ENUM KEY)
	 *  \return bool - TRUE if key is being pressed. FALSE if key is not being pressed.
	 */
	static bool		IsKeyDown(unsigned char a_cKey);

	/*! \brief Check if a key was only just pressed now. checks if the key was up last time but now is down.
	 *  \param a_cKey - the KEY to be checked (USE ENUM KEY)
	 *  \return bool - TRUE if key was just pressed. False if it wasnt just pressed.
	 */
	static bool		IsKeyPressed(unsigned char a_cKey);

	/*! \brief Check if a key was just released. checks if key was down last update but now is up.
	 *  \param a_cKey - the KEY to be checked (USE ENUM KEY)
	 *  \return bool - TRUE if key was just released. FALSE if it wasnt just released.
	 *	\sa foo::bar()
	 */
	static bool		IsKeyReleased(unsigned char a_cKey);


private:

	Keyboard();
	~Keyboard();

protected:
	static Keyboard*	m_pSingleton;
	char				m_acKeys[256];
	char				m_acKeysPrevious[256];
};

/*! \enum KEY
 *  \brief keycodes to be passed to Keyboard functions. this enum puts a human recognisable name to the hex code for that key.
 *	\sa Keyboard::IsKeyUp(unsigned char a_cKey)
 *	\sa Keyboard::IsKeyDown(unsigned char a_cKey)
 *	\sa Keyboard::IsKeyPressed(unsigned char a_cKey)
 *	\sa keyboard::IsKeyReleased(unsigned char a_cKey)
 *	\todo document the keycodes even though they should be obvious. really cbf.
 */
enum KEY : unsigned int
{
	//Number Keys
	KEY_0				= 0x30,
	KEY_1				= 0x31,
	KEY_2				= 0x32,
	KEY_3				= 0x33,
	KEY_4				= 0x34,
	KEY_5				= 0x35,
	KEY_6				= 0x36,
	KEY_7				= 0x37,
	KEY_8				= 0x38,
	KEY_9				= 0x39,

	//--------------------------------------------------------------------------------//

	//Letter Keys
	KEY_A				= 0x41,
	KEY_B				= 0x42,
	KEY_C				= 0x43,
	KEY_D				= 0x44,
	KEY_E				= 0x45,
	KEY_F				= 0x46,
	KEY_G				= 0x47,
	KEY_H				= 0x48,
	KEY_I				= 0x49,
	KEY_J				= 0x4A,
	KEY_K				= 0x4B,
	KEY_L				= 0x4C,
	KEY_M				= 0x4D,
	KEY_N				= 0x4E,
	KEY_O				= 0x4F,
	KEY_P				= 0x50,
	KEY_Q				= 0x51,
	KEY_R				= 0x52,
	KEY_S				= 0x53,
	KEY_T				= 0x54,
	KEY_U				= 0x55,
	KEY_V				= 0x56,
	KEY_W				= 0x57,
	KEY_X				= 0x58,
	KEY_Y				= 0x59,
	KEY_Z				= 0x5A,

	//--------------------------------------------------------------------------------//

	//Arrow Keys
	KEY_LEFT			= 0x25,
	KEY_UP				= 0x26,
	KEY_RIGHT			= 0x27,
	KEY_DOWN			= 0x28,

	//--------------------------------------------------------------------------------//

	//Function Keys
	KEY_F1				= 0x70,
	KEY_F2				= 0x71,
	KEY_F3				= 0x72,
	KEY_F4				= 0x73,
	KEY_F5				= 0x74,
	KEY_F6				= 0x75,
	KEY_F7				= 0x76,
	KEY_F8				= 0x77,
	KEY_F9				= 0x78,
	KEY_F10				= 0x79,
	KEY_F11				= 0x7A,
	KEY_F12				= 0x7B,
	KEY_F13				= 0x7C,
	KEY_F14				= 0x7D,
	KEY_F15				= 0x7E,
	KEY_F16				= 0x7F,
	KEY_F17				= 0x80,
	KEY_F18				= 0x81,
	KEY_F19				= 0x82,
	KEY_F20				= 0x83,
	KEY_F21				= 0x84,
	KEY_F22				= 0x85,
	KEY_F23				= 0x86,
	KEY_F24				= 0x87,

	//--------------------------------------------------------------------------------//

	//Numpad Keys
	KEY_NUMPAD0			= 0x60,
	KEY_NUMPAD1			= 0x61,
	KEY_NUMPAD2			= 0x62,
	KEY_NUMPAD3			= 0x63,
	KEY_NUMPAD4			= 0x64,
	KEY_NUMPAD5			= 0x65,
	KEY_NUMPAD6			= 0x66,
	KEY_NUMPAD7			= 0x67,
	KEY_NUMPAD8			= 0x68,
	KEY_NUMPAD9			= 0x69,
	KEY_NUMPADMUL		= 0x6A,
	KEY_NUMPADADD		= 0x6B,
	KEY_NUMPADSEP		= 0x6C, // seperator key (idk which that is but thats the doc)
	KEY_NUMPADSUB		= 0x6D,
	KEY_NUMPADDEC		= 0x6E, // decimal key
	KEY_NUMPADDIVIDE	= 0x6F,
	KEY_NUMLOCK			= 0x90,
	//--------------------------------------------------------------------------------//

	//Control Keys
	KEY_SHIFT			= 0x10,
	KEY_CTRL			= 0x11,
	KEY_ALT				= 0x12,

	KEY_LSHIFT			= 0xA0,
	KEY_LCTRL			= 0xA2,
	KEY_LALT			= 0xA4,
	KEY_RALT			= 0xA5,
	KEY_RCTRL			= 0xA3,
	KEY_RSHIFT			= 0xA1,
	KEY_RETURN			= 0x0D,
	KEY_BACKSPACE		= 0x08,
	KEY_SPACE			= 0x20,
	KEY_ESCAPE			= 0x1B,
	KEY_TAB				= 0x09,
	KEY_CAPS			= 0x14,

	KEY_PAGEUP			= 0x21,
	KEY_PAGEDOWN		= 0x22,
	KEY_END				= 0x23,
	KEY_HOME			= 0x24,


	KEY_SELECT			= 0x29,
	KEY_PRINT			= 0x2A,
	//KEY_EXECUTE			= 0x2B,

	KEY_INS				= 0x2D,
	KEY_HELP			= 0x2F,
		
	KEY_SCRLLOCK		= 0x91,
	KEY_PRNTSCRN		= 0x2C,
	KEY_PAUSE			= 0x13,

	KEY_LWIN			= 0x5B,
	KEY_RWIN			= 0x5C,
	KEY_APPS			= 0x5D, // weird key between RALT and RCTRL,
	KEY_SLEEP			= 0x5F,

	KEY_COLON			= 0xBA,
	KEY_PLUS			= 0xBB,
	KEY_EQUAL			= 0xBB,
	KEY_LESSTHAN		= 0xBC, 
	KEY_COMMA			= 0xBC,
	KEY_MINUS			= 0xBD,
	KEY_UNDERSCORE		= 0xBD,
	KEY_PERIOD			= 0xBE,
	KEY_GRATERTHAN		= 0xBE,
	KEY_FWDSLASH		= 0xBF,
	KEY_QMARK			= 0xBF,
	KEY_TILDE			= 0xC0,
	KEY_LEFTBRACE		= 0xDB,
	KEY_BACKSLASH		= 0xDC,
	KEY_PIPE			= 0xDC,
	KEY_RIGHTBRACE		= 0xDD,
	KEY_QUOTE			= 0xDE,
	KEY_DOUBLEQUOTE		= 0xDE
};

//////////////////////////////////////////////////////////////////////////
#endif // _KEYBOARD_H_
//////////////////////////////////////////////////////////////////////////
