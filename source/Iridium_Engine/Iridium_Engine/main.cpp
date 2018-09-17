//#define DEBUG | _DEBUG

#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <Windows.h>
#include <winnt.h>
#include <string>
extern "C" {
#include <Powrprof.h>

}
#pragma comment(lib, "Powrprof.lib")


HWND g_hWnd;
TCHAR debugText[];

//---------------------------
// FUNCTION DECLARATIONS
//---------------------------
bool IsInstanceRunning(LPCWSTR className, LPCWSTR windowTitle);
void CheckDiskCapacity();
void CheckMemoryCapacity();
void CheckCPUStats();
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
	CheckDiskCapacity();
	CheckMemoryCapacity();
	CheckCPUStats();


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
		FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 2));
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
	Checks if device has required disk space needed.
	Displays confirmation to user through message box
*/
void CheckDiskCapacity()
{
	wchar_t text[200];
	ULARGE_INTEGER ulFreeSpace;
	ULARGE_INTEGER ulTotalSpace;
	ULARGE_INTEGER ulTotalFreeSpace;

	GetDiskFreeSpaceEx(L"C:", &ulFreeSpace, &ulTotalSpace, &ulTotalFreeSpace);

	if (300 > (ulTotalFreeSpace.QuadPart / 1024 * 1024))
		swprintf(text, 200, L"Insufficient disk space \nDisk space required: 300 \nDisk space available: %llu MB.", ulTotalFreeSpace.QuadPart / (1024 * 1024));
	else
		swprintf(text, 200, L"Sufficient disk space \nDisk space required: 300 \nDisk space available: %llu MB.", ulTotalFreeSpace.QuadPart / (1024 * 1024));

	int msgboxID = MessageBox(
		g_hWnd,
		text,
		L"Disk Space Available",
		NULL
	);
}

/*
	Displays the size of physical and virtual memory available to use.
	Displays information to user via message box.
*/
void CheckMemoryCapacity()
{
	wchar_t text[200];
	MEMORYSTATUSEX memoryStruct = {};
	memoryStruct.dwLength = sizeof(memoryStruct);

	GlobalMemoryStatusEx(&memoryStruct);

	int bufferSize = swprintf(text, 200, L"Physical Memory Available: %I64d MB \nVirtual Memory Available: %I64d MB", memoryStruct.ullAvailPhys / (1024 * 1024), memoryStruct.ullAvailVirtual / (1024 * 1024));
	int msgboxID = MessageBox(
		g_hWnd,
		text,
		L"Memory Available",
		NULL
	);
}

typedef struct _PROCESSOR_POWER_INFORMATION {
	ULONG Number;
	ULONG MaxMhz;
	ULONG CurrentMhz;
	ULONG MhzLimit;
	ULONG MaxIdleState;
	ULONG CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;


/*
	Displays the CPU speed and architecture of the device.
	Displays information to user via message box.
*/
void CheckCPUStats()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	// allocate buffer to get info for each processor
	const int size = sysInfo.dwNumberOfProcessors * sizeof(PROCESSOR_POWER_INFORMATION);
	LPBYTE pBuffer = new BYTE[size];
	CallNtPowerInformation(ProcessorInformation, NULL, 0, pBuffer, size);
	PPROCESSOR_POWER_INFORMATION ppi = (PPROCESSOR_POWER_INFORMATION)pBuffer;

	wchar_t text[200];
	swprintf(text, 200, L"Proccesor Speed: %d MHz \nCPU Architecture Value: %u", ppi->MaxMhz, sysInfo.wProcessorArchitecture);
	int msgboxID = MessageBox(
		g_hWnd,
		text,
		L"CPU Specs",
		NULL
	);
}	