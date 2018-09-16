//#define DEBUG | _DEBUG

#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <Windows.h>
#include <string>

LPCWSTR debugText = L"ASDASD";
HWND g_hWnd;

//---------------------------
// FUNCTION DECLARATIONS
//---------------------------
bool IsInstanceRunning(LPCWSTR className, LPCWSTR windowTitle);
void CheckStorageCapacity();
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND CreateWindowInstance(const HINSTANCE &hInstance, const wchar_t  CLASS_NAME[14]);

//----------------------------
// APPLICATION START
//----------------------------

/*
	Application entry point
*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, PWSTR pCmdLine, int nCmdShow)
{
	// register window class
	const wchar_t CLASS_NAME[] = L"Editor Window";
	const wchar_t WINDOW_TITLE[] = L"Iridium Engine";

	// check if window is already open
	if (IsInstanceRunning(CLASS_NAME, WINDOW_TITLE))
	{
		return 0;
	}

	// create wc instance
	g_hWnd = CreateWindowInstance(hInstance, CLASS_NAME);

	if (g_hWnd == NULL)
		return 0; //create window failed

	ShowWindow(g_hWnd, nCmdShow);
	
	// check for storage capacity
	CheckStorageCapacity();

	//-----------------------
	// MESSAGE LOOP
	//-----------------------
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

HWND CreateWindowInstance(const HINSTANCE &hInstance, const wchar_t  CLASS_NAME[14])
{
	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// creating window
	return CreateWindowEx(
		0,
		CLASS_NAME,
		L"Iridium Engine",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
}

/*
	Defines the application's behavior of handling window messages.
*/
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: //calling quit function
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
		return 0;
	}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

/* 
	Checks if an instance of the application is already running and if so,
	puts the application into focus.
*/
bool IsInstanceRunning(LPCWSTR className, LPCWSTR windowTitle)
{
	HANDLE handle = CreateMutex(NULL, true, windowTitle);
	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(className, windowTitle);
		if (hWnd)
		{
			// set previous instance in focus
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);

			// display message
			int msgboxID = MessageBox(
			hWnd,
			L"An instance of the application is already running",
			L"Multiple Instances Detected",
			MB_ICONWARNING
			);
			return true;
		}
	}
	return false;
}

/*
	Check's if device has required physical and virtal memory space.
	Displays confirmation to user through message box
*/
void CheckStorageCapacity()
{
	PULARGE_INTEGER freeBytesAvailable = nullptr;
	GetDiskFreeSpaceEx(NULL, NULL, NULL, freeBytesAvailable);

}