#pragma once

#include "Engine/Graphics/D3DClass.h"
#include "Engine/Graphics/D2DClass.h"
#include "Engine/Graphics/UI/Text/DWClass.h"

//-----------------//
//RENDERING GLOBALS//
//-----------------//
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#include <wrl/client.h>

class GraphicsClass
{
public:
	GraphicsClass();
	~GraphicsClass();

	bool Initialize(int screenWidth, int screenHeight, HWND hWnd);
	void Shutdown();
	bool Frame();

	Microsoft::WRL::ComPtr<ID3D11Device> GetD3DDevice();
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetD3DDeviceContext();

private:
	bool Render();

private:
	D3DClass* Direct3D;
	D2DClass* Direct2D;
	DWClass* DirectWrite;


};

