#include <Windows.h>
#include "Core/Application.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iShowCmd)
{
	AppBase* MyApp = new Application;
	if(MyApp->Create(lpCmdLine))
	{
		MyApp->Execute();
	}
	delete MyApp;
	return 0;
}