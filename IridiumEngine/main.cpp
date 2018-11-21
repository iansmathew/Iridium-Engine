#include "stdafx.h"
#include "Engine/IrEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	IrEngine* Engine;

	//Create system object
	Engine = IrEngine::Get();

	if (!Engine)
	{
		return 0;
	}

	//Initialize and run system
	bool result = Engine->Initialize();
	if (result)
	{
		Engine->Run();
	}

	//Shutdown and release system object
	Engine->Shutdown();
	delete Engine;
	Engine = nullptr;

	return 0;
}