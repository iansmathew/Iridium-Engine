#include "stdafx.h"
#include "Engine/Graphics/GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	Direct3D = nullptr;
}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hWnd)
{
	//Create Direct3D object
	Direct3D = new D3DClass();
	if (Direct3D)
	{
		return false;
	}

	//Initialize Direct3D object
	bool result = Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hWnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hWnd, L"Could not initialize Direct3D", L"Error", MB_OK);
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	//Release Direct3D object
	if (Direct3D)
	{
		Direct3D->Shutdown();
		delete Direct3D;
		Direct3D = nullptr;
	}
}

bool GraphicsClass::Frame()
{
	//Render graphics scene
	bool result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render()
{
	//Clear the buffer
	Direct3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f); //Gray color

	//Present rendered scene to screen
	Direct3D->EndScene();

	return true;
}
