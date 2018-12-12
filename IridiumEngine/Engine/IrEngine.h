#pragma once

#include "Engine/Graphics/GraphicsManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Lua/LuaScriptManager.h"

#include <windows.h>

class IrEngine
{
public:
	~IrEngine();

	//Returns a static instance of the engine
	static IrEngine* Get();

	bool Initialize();

	void Shutdown();

	void Run();

	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	IrEngine();

	bool Frame();
	void InitializeWindows(int& screenWidth, int& screenHeight);
	void ShutdownWindows();

private:
	LPCWSTR ApplicationName;
	HINSTANCE HInstance;
	HWND HWnd;

	InputManager* Input;
	GraphicsManager* Graphics;
	LuaScriptManager* LuaScripts;
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//static IrEngine* ApplicationHandle = nullptr;

