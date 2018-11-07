#include "stdafx.h"
#include "Engine/SystemClass.h"

SystemClass::SystemClass()
{
	Input = nullptr;
}


SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	int screenWidth = 0;
	int screenHeight = 0;

	//Initialize windows api
	InitializeWindows(screenWidth, screenHeight);
	
	//Create input object
	Input = new InputClass();
	if (!Input)
	{
		return false;
	}

	//Initialize input
	Input->Initialize();

	//Create graphics object
	Graphics = new GraphicsClass();
	if (!Graphics)
	{
		return false;
	}

	//Initialize graphics object
	bool result = Graphics->Initialize(screenWidth, screenHeight, HWnd);
	if (!result)
	{
		false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	//Release graphics object
	if (Graphics)
	{
		Graphics->Shutdown();
		delete Graphics;
		Graphics = nullptr;
	}

	//Release input object
	if (Input)
	{
		Input->Shutdown();
		delete Input;
		Input = nullptr;

	}

	//Shutdown windows
	ShutdownWindows();
}

void SystemClass::Run()
{
	MSG msg;
	bool done = false;
	bool result;

	//Initialize message structure
	ZeroMemory(&msg, sizeof(MSG));

	//Loop until quit message from window or user
	while (!done)
	{
		//Handle window messages
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//If finwos signals to quit, then exit
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			//Otherwise process frame
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
	}
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//Check if key has been pressed and pass input to InputClass
		case WM_KEYDOWN:
		{
			Input->KeyDown((UINT)wParam);
			return 0;
		}

		//Check if key has been released
		case WM_KEYUP:
		{
			Input->KeyUp((UINT)wParam);
			return 0;
		}

		//Send other messages to default message handler
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

bool SystemClass::Frame()
{
	bool result = Graphics->Frame();
	if (!result)
	{
		return false;
	}

	return true;
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	//Get external pointer to this
	ApplicationHandle = this;

	//Get instance of application
	HInstance = GetModuleHandle(nullptr);

	//Give application name
	ApplicationName = L"Iridium Engine";

	//Setup windows class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = HInstance;
	wc.hIcon = LoadIcon(HInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ApplicationName;
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	//Register window class
	RegisterClassEx(&wc);

	// If windowed then set it to 800x600 resolution.
	screenWidth = 800;
	screenHeight = 600;

	// Place the window in the middle of the screen.
	posX = CW_USEDEFAULT;
	posY = CW_USEDEFAULT;

	// Create the window with the screen settings and get the handle to it.
	HWnd = CreateWindowEx(WS_EX_APPWINDOW, ApplicationName, ApplicationName,
		WS_OVERLAPPEDWINDOW,
		posX, posY, screenWidth, screenHeight, NULL, NULL, HInstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(HWnd, SW_SHOW);
	SetForegroundWindow(HWnd);
	SetFocus(HWnd);
}

void SystemClass::ShutdownWindows()
{
	// Remove the window.
	DestroyWindow(HWnd);
	HWnd = NULL;

	// Remove the application instance.
	UnregisterClass(ApplicationName, HInstance);
	HInstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}