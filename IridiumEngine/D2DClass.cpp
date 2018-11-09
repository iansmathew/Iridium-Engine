#include "stdafx.h"
#include "Engine/Graphics/D2DClass.h"

using Microsoft::WRL::ComPtr;

D2DClass::D2DClass()
{
	factory = nullptr;
	//D2DDevice = nullptr;
	deviceContext = nullptr;
}

D2DClass::~D2DClass()
{
}

bool D2DClass::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> _D3DDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> _D3DDeviceContext, Microsoft::WRL::ComPtr<IDXGISwapChain > _swapChain)
{
	//Set the debug level info according to #define DEBUG
	D2D1_FACTORY_OPTIONS factoryOption;
#ifndef NDEBUG
	factoryOption.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#else
	factoryOption.debugLevel = D2D1_DEBUG_LEVEL_NONE;
#endif

	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory2), &factory);
	if (FAILED(result))
		return false;

	//Getting the DXGI device from Direct3D
	ComPtr<IDXGIDevice> dxgiDevice;
	result = _D3DDevice.Get()->QueryInterface(__uuidof(IDXGIDevice), &dxgiDevice);
	if (FAILED(result))
		return false;

	//Creating the Direct2D device
	result = factory->CreateDevice(dxgiDevice.Get(), D2DDevice.GetAddressOf());
	if (FAILED(result))
		return false;

	//Create device context
	result = D2DDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &deviceContext);
	if(FAILED(result))
		return false;

	//Telling Direct3D & Direct2D to work together

	//Creating Bitmap render target
	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format = DXGI_FORMAT_UNKNOWN;
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX = 96.0f;
	bp.dpiY = 96.0f;
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext = nullptr;

	//Get the back buffer from Direct3D

	ComPtr<IDXGISurface> dxgiSurface;
	result = _swapChain->GetBuffer(0, __uuidof(IDXGISurface), &dxgiSurface);
	if (FAILED(result))
		return false;

	//Create bitmap
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> targetBitmap;
	result = deviceContext->CreateBitmapFromDxgiSurface(dxgiSurface.Get(), &bp, &targetBitmap);
	if (FAILED(result))
		return false;

	deviceContext->SetTarget(targetBitmap.Get());

	return true;
}

Microsoft::WRL::ComPtr<ID2D1DeviceContext> D2DClass::GetDeviceContext()
{
	return deviceContext;
}

void D2DClass::BeginScene(IDWriteTextLayout* _textLayout, ID2D1SolidColorBrush* _yellowBrush)
{
	deviceContext->BeginDraw();
	deviceContext->DrawTextLayout(D2D1::Point2F(2.0f, 5.0f), _textLayout, _yellowBrush);
}

void D2DClass::EndScene()
{
	deviceContext->EndDraw();
}
