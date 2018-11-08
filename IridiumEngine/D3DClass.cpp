#include "stdafx.h"
#include "Engine/Graphics/D3DClass.h"

D3DClass::D3DClass()
{
	swapChain = nullptr;
	D3DDevice = nullptr;
	deviceContext = nullptr;
	renderTargetView = nullptr;
	depthStencilBuffer = nullptr;
	depthStencilState = nullptr;
	depthStencilView = nullptr;
	rasterState = nullptr;
}

D3DClass::~D3DClass()
{

}

bool D3DClass::Initialize(int screenWidth, int screenHeight, bool isVsyncEnabled, HWND hWnd, bool isFullscreen, float screenDepth, float screenNear)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	UINT numModes, numerator, denominator;
	unsigned long long stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;

	bIsVsyncEnabled = isVsyncEnabled;

	//Create a DirectX graphics interface factory;
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
		return false;

	//Use the factory to create adapter for the primary graphics interface  (video card or integrated gpu)
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
		return false;

	//Enumerate the primary adapter output (monitor)
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
		return false;

	//Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	if (FAILED(result))
		return false;

	//Create a list to hold all the possible display modes for the monitor / video card combination
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
		return false;

	//Now fill the display mode list struct
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
		return false;

	//Go through all display modes and find one that fits screen width and height
	//When match is found, store numerator and denominator of refresh rate for that monitor
	for (int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (UINT)screenWidth)
		{
			if (displayModeList[i].Height == (UINT)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				numerator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	//Get adapter (video card) descp
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
		return false;

	//Store video card memroy in MB
	videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	//Convert name of video card to char array and store it
	int error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);
	if (error != 0)
		return false;

	//Now that we've gotten the required info about refresh rate and video card info,
	//we will release the structures and interfaces

	//Release the display mode list
	delete[] displayModeList;
	displayModeList = nullptr;

	//Release adapter output
	adapterOutput->Release();
	adapterOutput = nullptr;

	//Release the adapter
	adapter->Release();
	adapter = nullptr;

	//Release the factory
	factory->Release();
	factory = nullptr;

	//Begin DirectX initialization

	//Initialize the swap chain desc
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	//Set to single back buffer
	swapChainDesc.BufferCount = 1;

	//Set width and height of back buffer
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	//Set regular 32 bit surface for the back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//Set refresh rate of the back buffer

	//if V-Sync enabled set refresh rate to monitors rate
	if (bIsVsyncEnabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	//Set the usage of the back buffer
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//Set the handle for the window to render in 
	swapChainDesc.OutputWindow = hWnd;

	//Turn multi sampling off
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	//Set to full screen or windowed mode
	if (isFullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	//Set scan line ordering and scaling to unspecified
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Discard the back buffer contents after presenting
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//Dont set the advanced flags
	swapChainDesc.Flags = 0;

	//Set feature level to DirectX 11
	featureLevel = D3D_FEATURE_LEVEL_11_0;
}



