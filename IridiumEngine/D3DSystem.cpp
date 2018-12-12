#include "stdafx.h"
#include "Engine/Graphics/D3DSystem.h"

D3DSystem::D3DSystem()
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

D3DSystem::~D3DSystem()
{

}

bool D3DSystem::Initialize(int screenWidth, int screenHeight, bool isVysncEnabled, HWND HWnd, bool isFullScreenEnabled, float screenDepth, float screenNear)
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

	bIsVsyncEnabled = isVysncEnabled;

	//Create DirectX Graphics Interface Factory;
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
		return false;

	//Use the factory to create adapter for primary DXGI (video card or integrated GPU)
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
		return false;

	//Enumerate the primary adapter output (monitor)
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
		return false;

	//Get number of modes that for the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output
	numModes = 0;
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
		return false;

	//Filling display mode list structure
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	if (FAILED(result))
		return false;

	//Go through all the display modes and find one that fits the screen width and height
	//When match is found, store numerator and denominator of refresh rate
	for (int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (UINT)screenWidth)
		{
			if (displayModeList[i].Height == (UINT)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
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
	//TODO: Fix does not work with x86
	//int error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);
	//if (error != 0)
	//	return false;

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

	//initialize variables
	numerator = 0;
	denominator = 0;

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
	swapChainDesc.OutputWindow = HWnd;

	//Turn multi sampling off
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	//Set to full screen or windowed mode
	if (isFullScreenEnabled)
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



	//Create swap chain, Direct3D device and Direct3D device context
	//This might fail if the user does not have their Direct11 compatible video card set as a primary card.
	//If this is the case, cycle through all available cards and ask user which card to use to create the D3DDevice and context.

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	//Set feature level to DirectX 11
	featureLevel;// = D3D_FEATURE_LEVEL_11_0;

	//Support Direct2D
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, creationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &D3DDevice, &featureLevel, &deviceContext);
	if (FAILED(result))
		return false;

	//Get the pointer to the back buffer 
	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	if (FAILED(result))
		return false;

	//Create the render target view with the back buffer pointer
	result = D3DDevice->CreateRenderTargetView(backBufferPtr, nullptr, &renderTargetView);
	if (FAILED(result))
		return false;

	//Release pointer to the back buffer since its no longer needed
	backBufferPtr->Release();
	backBufferPtr = nullptr;

	//Initialize description of depth buffer
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	//Set up the description of depth buffer
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	//Create the texture for the depth buffer using the desc
	//The depth buffer is in essence a 2D texture hence we create a 2D texture
	result = D3DDevice->CreateTexture2D(&depthBufferDesc, nullptr, &depthStencilBuffer);
	if (FAILED(result))
		return false;

	//Setup depth stencil description

	//Initialize the desc of the stencil state
	ZeroMemory(&depthStencilDesc, sizeof(&depthStencilDesc));

	//Set up the description of the stencil state
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	//Stencil operations if pixel is front-facing
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//Stencil operations if pixel is back-facing
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//Create depth stencil state
	result = D3DDevice->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	if (FAILED(result))
		return false;

	//Set depth stencil state
	deviceContext->OMSetDepthStencilState(depthStencilState, 1);

	//Initialize depth stencil view
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//Setup the depth stencil view desc
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	//Create the depth stencil view
	result = D3DDevice->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView);
	if (FAILED(result))
		return false;

	//Bind the render target view and depth stencil buffer to the output render pipeline
	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	//Creating a customized raster desc so that we can add future effects if needed
	//The current desc has the same desc as the default raster
	//However, we create a custom one so that we have control over it

	//Setting up the raster desc
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	//Create raster state from the desc
	result = D3DDevice->CreateRasterizerState(&rasterDesc, &rasterState);
	if (FAILED(result))
		return false;

	//Set rasterizer state
	deviceContext->RSSetState(rasterState);

	//Setting up viewport for rendering
	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	//Create and set viewport
	deviceContext->RSSetViewports(1, &viewport);

	//Creating different matrices

	//Setting up projection matrix
	fieldOfView = 3.141592654f / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;

	//Create the projection matrix for 3D rendering
	projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

	//Initialize world matrix to identity
	worldMatrix = XMMatrixIdentity();

	//We do not create the view matrix since that is constrained to the camera class.

	//Create the orthographic projection matrix for 2D rendering UI elements
	orthoMatrix = XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, screenNear, screenDepth);

	return true;
}

void D3DSystem::Shutdown() 
{
	//Before shutting down set to windowed mode because a full screen swapchain tends to throw errors
	if (swapChain)
		swapChain->SetFullscreenState(false, nullptr);

	if (rasterState)
	{
		rasterState->Release();
		rasterState = nullptr;
	}

	if (depthStencilView)
	{
		depthStencilView->Release();
		depthStencilView = nullptr;
	}

	if (depthStencilState)
	{
		depthStencilState->Release();
		depthStencilState = nullptr;
	}

	if (depthStencilBuffer)
	{
		depthStencilBuffer->Release();
		depthStencilBuffer = nullptr;
	}

	if (renderTargetView)
	{
		renderTargetView->Release();
		renderTargetView = nullptr;
	}

	if (deviceContext)
	{
		deviceContext->Release();
		deviceContext = nullptr;
	}

	if (D3DDevice)
	{
		D3DDevice->Release();
		D3DDevice = nullptr;
	}

	if (swapChain)
	{
		swapChain->Release();
		swapChain = nullptr;
	}
}

void D3DSystem::BeginScene(float r, float g, float b, float a) const
{
	//Setup clear color
	float color[] = { r, g, b, a };

	//Clear back buffer
	deviceContext->ClearRenderTargetView(renderTargetView, color);

	//Clear the depth buffer
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3DSystem::EndScene() const
{
	//Present back buffer to screen once rendering is complete
	if (bIsVsyncEnabled)
	{
		//Lock to screen refresh rate
		swapChain->Present(1, 0);
	}
	else
	{
		//Present as fast as possible
		swapChain->Present(0, 0);
	}
}

