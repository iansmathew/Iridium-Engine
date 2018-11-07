#pragma once

#include "Engine/Graphics/D3DClass.h"

//-----------------//
//RENDERING GLOBALS//
//-----------------//
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	~GraphicsClass();

	bool Initialize(int screenWidth, int screenHeight, HWND hWnd);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	D3DClass* Direct3D;
};

