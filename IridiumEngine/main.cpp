#include "stdafx.h"
#include "Engine/SystemClass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;

	//Create system object
	System = new SystemClass();
	if (!System)
	{
		return 0;
	}

	//Initialize and run system
	bool result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	//Shutdown and release system object
	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;
}