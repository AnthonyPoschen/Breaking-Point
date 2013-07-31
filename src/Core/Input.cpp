//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 5/5/2013 >
//	< File >	< Input >
//	< Brief >	< input setup >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Includes 
#include "bpPython.h"
#include "../input/Mouse.h"
#include "../Input/Keyboard.h"
//////////////////////////////////////////////////////////////////////////
//  Forward Declares 

/*! \defgroup bzInput 
 *	\ingroup PyModules
 *	\brief This Module handles mouse and keyboard input. 
 *	\details To use this module import bzInput.
 *	\page bzInputOverview bzInput Overview
 */
PYTHON_MODULE(bzInput)
{


	using namespace boost::python;
	// <Keyboard Funcitons >
	/**  
	 * @addtogroup bzInput 
	 * @{   
	 *
	 *		\page KeyBoardOverview KeyBoard Overview
	 *		\details Here is a list of keyboard functions for Python within the bzInput Module.
	 *		
	 *
	 *		\page KeyUp KeyUp( KEY )
	 *      returns bool - True if key on keyboard is Up. False otherwise
	 *	    
	 *		\page KeyDown KeyDown( KEY )
	 *		returns bool - True if key on keyboard is down. False otherwise
	 *
	 *		\page KeyPress KeyPress( KEY )
	 *		returns bool - Returns true on the first instance only the key is down. false if held down or up.
	 *
	 *		\page KeyRelease KeyRelease( KEY )
	 *		returns bool - Returns true first instance key is not down. returns false if key is up or down. 
	 */ 
	def("KeyUp",&Keyboard::IsKeyUp);
	def("KeyDown",&Keyboard::IsKeyDown);
	def("KeyPress",&Keyboard::IsKeyPressed);
	def("KeyRelease",&Keyboard::IsKeyReleased);
	// <Mouse Funcitons>
	
	/**
	 *	\page MouseOverview Mouse Overview
	 *	\details These are the Mouse Based Commands
	 *	\page CursorPos CursorPos()
	 *	returns float2 - current mouse cordinates relative to game window
	 *
	 *	\page CursorScreenPos CursorScreenPos()
	 *	returns float2 - Current Mouse Cordinates relative to computer monitors.
	 *
	 *	\page CursorShow CursorShow( BOOL )
	 *	returns void - takes in a Bool to determine if mouse should be visible while over window. ( turn off if drawing a custom mouse at mouse location)
	*/
	// to do list.. implement mouse.
	def("CursorPos",&Mouse::bpGetPos);
	def("CursorScreenPos",&Mouse::bpGetPosToScreen);
	def("CursorShow",Mouse::Show);

	/**
	*	\page KEYS Keyboard KEYS
	*	\details this is a list of all input (case sensative) that is accepted by the keyboard functions to check key input<br>
	*	\details <br><b>Numeric Keys</b><br>
	*	\details KEY_0 , KEY_1 , KEY_2 , KEY_3 , KEY_4 , KEY_5 , KEY_6 , KEY_7 , KEY_8 , KEY_9<br>
	*	\details NUMPAD0 , NUMPAD1 , NUMPAD2 , NUMPAD3 , NUMPAD4 , NUMPAD5 NUMPAD6 , NUMPAD7 , NUMPAD8 , NUMPAD9<br>
	*	\details <br><b>AlphaBetic</b><br>
	*	\details A , a , B , b , C , c , D , d , E , e , F , f , G , g , H , h , I , i , J , j , K , k , L , l , M , m , N , n , O , o , P , p , Q , q , R , r , S , s , T , t , U , u , V , v , W , w , X , x , Y , y , Z , z<br>
	*	\details <br><b>Arrow Keys</b><br>
	*	\details LEFT , RIGHT , UP , DOWN<br>
	*	\details <br><b>Special Keys</b><br>
	*	\details NUMPADMUL ( * ), NUMPADADD ( + ), NUMPADSEP ( enter key), NUMPADSUB ( - ), NUMPADDEC( . ), NUMPADDIVIDE( / ), NUMLOCK (numlock key)<br> 
	*	\details CTRL , ALT , SHIFT - recognises Left and Right versions of these keys<br>
	*	\details LCTRL , LATL , LSHIFT - only left hand side versions reconised.<br>
	*	\details RCTRL , RALT , RSHIFT - only right hand side versions reconised.<br>
	*	\details RETURN | ENTER , BACKSPACE , SPACE , ESCAPE | ESC , TAB , CAPSLOCK , CAPS<br>
	*	\details PAGEUP , PAGEDOWN , END , HOME , SELECT , PRINT , INS (insert) , HELP , SCRLLOCK | SCROLLLOCK , PRINTSCREEN , PRNTSCRN<br>
	*	\details PAUSE , LWIN , RWIN (windows keys) , APPS , SLEEP , COLON , PLUS , EQUAL , LESSTHAN , COMMA , MINUS , UNDERSCORE , PERIOD , GREATERTHAN , FWDSLASH<br>
	*	\details QMARK , QUESTIONMARK , TILDE | ` | ~ , LEFTBRACE , RIGHTBRACE , BCKSLASH | BACKSLASH, PIPE , QUOTE , DOUBLEQUOTE<br>
	*/		
	/** @} */

	// <Keyboard Extentions>
	enum_<KEY>("KEY")
		.value("KEY_0",KEY_0)
		.value("KEY_1",KEY_1)
		.value("KEY_2",KEY_2)
		.value("KEY_3",KEY_3)
		.value("KEY_4",KEY_4)
		.value("KEY_5",KEY_5)
		.value("KEY_6",KEY_6)
		.value("KEY_7",KEY_7)
		.value("KEY_8",KEY_8)
		.value("KEY_9",KEY_9)
		.value("A",KEY_A)
		.value("a",KEY_A)
		.value("B",KEY_B)
		.value("b",KEY_B)
		.value("C",KEY_C)
		.value("c",KEY_C)
		.value("D",KEY_D)
		.value("d",KEY_D)
		.value("E",KEY_E)
		.value("e",KEY_E)
		.value("F",KEY_F)
		.value("f",KEY_F)
		.value("G",KEY_G)
		.value("g",KEY_G)
		.value("H",KEY_H)
		.value("h",KEY_H)
		.value("I",KEY_I)
		.value("i",KEY_I)
		.value("J",KEY_J)
		.value("j",KEY_J)
		.value("K",KEY_K)
		.value("k",KEY_K)
		.value("L",KEY_L)
		.value("l",KEY_L)
		.value("M",KEY_M)
		.value("m",KEY_M)
		.value("N",KEY_N)
		.value("n",KEY_N)
		.value("O",KEY_O)
		.value("o",KEY_O)
		.value("P",KEY_P)
		.value("p",KEY_P)
		.value("Q",KEY_Q)
		.value("q",KEY_Q)
		.value("R",KEY_R)
		.value("r",KEY_R)
		.value("S",KEY_S)
		.value("s",KEY_S)
		.value("T",KEY_T)
		.value("t",KEY_T)
		.value("U",KEY_U)
		.value("u",KEY_U)
		.value("V",KEY_V)
		.value("v",KEY_V)
		.value("W",KEY_W)
		.value("w",KEY_W)
		.value("X",KEY_X)
		.value("x",KEY_X)
		.value("Y",KEY_Y)
		.value("y",KEY_Y)
		.value("Z",KEY_Z)
		.value("z",KEY_Z)

		// Arrow KEYS
		.value("LEFT",KEY_LEFT)
		.value("UP",KEY_UP)
		.value("RIGHT",KEY_RIGHT)
		.value("DOWN",KEY_DOWN)
		
		// Function KEYS (included extension ones i.e g15 enabled keys)
		.value("F1",KEY_F1)
		.value("F2",KEY_F2)
		.value("F3",KEY_F3)
		.value("F4",KEY_F4)
		.value("F5",KEY_F5)
		.value("F6",KEY_F6)
		.value("F7",KEY_F7)
		.value("F8",KEY_F8)
		.value("F9",KEY_F9)
		.value("F10",KEY_F10)
		.value("F11",KEY_F11)
		.value("F12",KEY_F12)
		.value("F13",KEY_F13)
		.value("F14",KEY_F14)
		.value("F15",KEY_F15)
		.value("F16",KEY_F16)
		.value("F17",KEY_F17)
		.value("F18",KEY_F18)
		.value("F19",KEY_F19)
		.value("F20",KEY_F20)
		.value("F21",KEY_F21)
		.value("F22",KEY_F22)
		.value("F23",KEY_F23)
		.value("F24",KEY_F24)

		//Numpad Keys
		.value("NUMPAD0",KEY_NUMPAD0)
		.value("NUMPAD1",KEY_NUMPAD1)
		.value("NUMPAD2",KEY_NUMPAD2)
		.value("NUMPAD3",KEY_NUMPAD3)
		.value("NUMPAD4",KEY_NUMPAD4)
		.value("NUMPAD5",KEY_NUMPAD5)
		.value("NUMPAD6",KEY_NUMPAD6)
		.value("NUMPAD7",KEY_NUMPAD7)
		.value("NUMPAD8",KEY_NUMPAD8)
		.value("NUMPAD9",KEY_NUMPAD9)

		.value("NUMPADMUL",KEY_NUMPADMUL)
		.value("NUMPADADD",KEY_NUMPADADD)
		.value("NUMPADSEP",KEY_NUMPADSEP)
		.value("NUMPADSUB",KEY_NUMPADSUB)
		.value("NUMPADDEC",KEY_NUMPADDEC)
		.value("NUMPADDIVIDE",KEY_NUMPADDIVIDE)
		.value("NUMLOCK",KEY_NUMLOCK)

		//Control KEYS
		.value("SHIFT",KEY_SHIFT)
		.value("CTRL",KEY_CTRL)
		.value("ALT",KEY_ALT)
		.value("LSHIFT",KEY_LSHIFT)
		.value("LCTRL",KEY_LCTRL)
		.value("LALT",KEY_LALT)
		.value("RSHIFT",KEY_RSHIFT)
		.value("RCTRL",KEY_RCTRL)
		.value("RALT",KEY_RALT)
		.value("RETURN",KEY_RETURN)
		.value("ENTER",KEY_RETURN)
		.value("BACKSPACE",KEY_BACKSPACE)
		.value("SPACE",KEY_SPACE)
		.value("ESCAPE",KEY_ESCAPE)
		.value("ESC",KEY_ESCAPE)
		.value("TAB",KEY_TAB)
		.value("CAPSLOCK",KEY_CAPS)
		.value("CAPS",KEY_CAPS)
		.value("PAGEUP",KEY_PAGEUP)
		.value("PAGEDOWN",KEY_PAGEDOWN)
		.value("END",KEY_END)
		.value("HOME",KEY_HOME)
		.value("SELECT",KEY_SELECT)
		.value("PRINT",KEY_PRINT)
		.value("INS",KEY_INS)
		.value("HELP",KEY_HELP)
		.value("SCRLLOCK",KEY_SCRLLOCK)
		.value("SCROLLLOCK",KEY_SCRLLOCK)
		.value("PRINTSCREEN",KEY_PRNTSCRN)
		.value("PRNTSCRN",KEY_PRNTSCRN)
		.value("PAUSE",KEY_PAUSE)
		.value("LWIN",KEY_LWIN)
		.value("RWIN",KEY_RWIN)
		.value("APPS",KEY_APPS)
		.value("SLEEP",KEY_SLEEP)
		.value("COLON",KEY_COLON)
		.value("PLUS",KEY_PLUS)
		.value("EQUAL",KEY_EQUAL)
		.value("LESSTHAN",KEY_LESSTHAN)
		.value("COMMA",KEY_COMMA)
		.value("MINUS",KEY_MINUS)
		.value("UNDERSCORE",KEY_UNDERSCORE)
		.value("PERIOD",KEY_PERIOD)
		.value("GRATERTHAN",KEY_GRATERTHAN)
		.value("FWDSLASH",KEY_FWDSLASH)
		.value("FORWARDSLASH",KEY_FWDSLASH)
		.value("QMARK",KEY_QMARK)
		.value("QUESTIONMARK",KEY_QMARK)
		.value("TILDE",KEY_TILDE)
		.value("`",KEY_TILDE)
		.value("~",KEY_TILDE)
		.value("LEFTBRACE",KEY_LEFTBRACE)
		.value("BCKSLASH",KEY_BACKSLASH)
		.value("BACKSLASH",KEY_BACKSLASH)
		.value("PIPE",KEY_PIPE)
		.value("RIGHTBRACE",KEY_RIGHTBRACE)
		.value("QUOTE",KEY_QUOTE)
		.value("DUOBLEQUOTE",KEY_DOUBLEQUOTE);
}

//////////////////////////////////////////////////////////////////////////
