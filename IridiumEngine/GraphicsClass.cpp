#include "stdafx.h"
#include "Engine/Graphics/GraphicsClass.h"

using Microsoft::WRL::ComPtr;

GraphicsClass::GraphicsClass()
{
	Direct3D = nullptr;
	Direct2D = nullptr;
}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hWnd)
{
	/*******************
		Direct 3D 
	********************/

	//Create Direct3D object
	Direct3D = new D3DClass();
	if (!Direct3D)
	{
		return false;
	}

	//Initialize Direct3D object
	bool result = Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hWnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hWnd, L"Could not initialize Direct3D", L"Error", MB_OK);
	}

	/*******************
		Direct2D
	********************/

	//Create Direct2D object
	Direct2D = new D2DClass();
	if (!Direct2D)
		return false;

	//Initialize Direct2D object
	result = Direct2D->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), Direct3D->GetSwapChain());
	if (!result)
	{
		MessageBox(hWnd, L"Could not initialize Direct2D", L"Error", MB_OK);
	}

	/*******************
		DirectWrite
	********************/

	//Create DirectWrite object
	DirectWrite = new DWClass();
	if (!DirectWrite)
		return false;

	//Initialize DirectWrite object
	result = DirectWrite->Initialize(Direct2D->GetDeviceContext());
	if (!result)
		MessageBox(hWnd, L"Could not initialize DirectWrite", L"Error", MB_OK);

	return true;
}

void GraphicsClass::Shutdown()
{
	////Release Direct2D object
	//if (Direct2D)
	//{
	//	Direct2D->Shutdown();
	//	delete Direct2D;
	//	Direct2D = nullptr;
	//}

	////Release DirectWrite object
	//if (DirectWrite)
	//{
	//	DirectWrite->Shutdown();
	//	delete DirectWrite;
	//	DirectWrite = nullptr;

	//}

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

Microsoft::WRL::ComPtr<ID3D11Device> GraphicsClass::GetD3DDevice()
{
	return Direct3D->GetDevice();
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext> GraphicsClass::GetD3DDeviceContext()
{
	return Direct3D->GetDeviceContext();
}

Microsoft::WRL::ComPtr<IDXGISwapChain> GraphicsClass::GetSwapChain()
{
	return Direct3D->GetSwapChain();
}

bool GraphicsClass::Render()
{
	//Clear the buffer
	Direct3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f); //Gray color

	//Present rendered scene to screen

	//TODO: Add Direct2D render function here
	Direct2D->BeginScene(DirectWrite->GetTextLayout(), DirectWrite->GetYellowBrush());
	Direct2D->EndScene();

	Direct3D->EndScene();
	//TODO: Add DirectWrite render function here

	return true;
}
