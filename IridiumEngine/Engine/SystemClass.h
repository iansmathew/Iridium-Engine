#pragma once
#include <windows.h>

#include "Engine/Graphics/GraphicsClass.h"
#include "Engine/Input/InputClass.h"

class SystemClass
{
public:
	SystemClass();
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	bool Frame();
	void InitializeWindows(int& screenWidth, int& screenHeight);
	void ShutdownWindows();

private:
	LPCWSTR ApplicationName;
	HINSTANCE HInstance;
	HWND HWnd;

	InputClass* Input;
	GraphicsClass* Graphics;
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static SystemClass* ApplicationHandle = nullptr;