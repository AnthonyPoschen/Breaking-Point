//////////////////////////////////////////////////////////////////////////
//	< Author >	< Anthony Poschen >
//	< Date >	< 5/5/2013 >
//  < File >	< Utilities >
//  < Brief >	< Utilities for Debugging programs >
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	< Includes >
#include "Utilities.h"
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include "bpPython.h"

//////////////////////////////////////////////////////////////////////////
// < Forward Declares >

PYTHON_MODULE(bpUtil)
{
	using namespace boost::python;
	def("ConsoleShow",&Utilities::ConsoleShow);
	def("ConsoleClear",&Utilities::ConsoleClear);
}

//////////////////////////////////////////////////////////////////////////
void Utilities::ConsoleShow(bool a_bShow /* = true */)
{
#ifdef _DEBUG
	if (a_bShow)
	{
		if(AllocConsole() == NULL)
			return;

		HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
		int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
		FILE* hf_out = _fdopen(hCrt, "w");
		setvbuf(hf_out, NULL, _IONBF, 1);
		*stdout = *hf_out;

		HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
		hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
		FILE* hf_in = _fdopen(hCrt, "r");
		setvbuf(hf_in, NULL, _IONBF, 128);
		*stdin = *hf_in;

		SetConsoleTitle("Debug Console");

		//move the window to the upper left corner
		HWND hwnd = GetConsoleWindow();
		RECT rect;
		GetWindowRect(hwnd, &rect);
		MoveWindow(hwnd, 0, 0, rect.right - rect.left, rect.bottom - rect.top, TRUE);

		ConsoleClear();
	}
	else
	{
		FreeConsole();
	}
#endif
}

//////////////////////////////////////////////////////////////////////////
void Utilities::ConsoleClear()
{
#ifdef _DEBUG
	COORD topLeft  = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	SetConsoleCursorPosition(console, topLeft);
#endif
}

//////////////////////////////////////////////////////////////////////////
void Utilities::Debug_ConsoleWrite(const char* pFormat, ...)
{
#ifdef _DEBUG
	char caString[512];
	va_list arglist;
	va_start(arglist,pFormat);
	vsprintf_s(caString,pFormat,arglist);
	va_end(arglist);

	printf_s(caString);
#endif
}

//////////////////////////////////////////////////////////////////////////
void Utilities::Debug_OutputWrite(const char* pFormat, ...)
{
#ifdef _DEBUG
	char caString[512];
	va_list arglist;
	va_start(arglist,pFormat);
	vsprintf_s(caString,pFormat,arglist);
	va_end(arglist);

	OutputDebugString(caString);
#endif
}