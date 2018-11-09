#include "stdafx.h"
#include "Engine/Graphics/D2DClass.h"

using Microsoft::WRL::ComPtr;

D2DClass::D2DClass()
{
}

D2DClass::~D2DClass()
{
}

bool D2DClass::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> _D3DDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> _D3DDeviceContext)
{
	//Set the debug level info according to #define DEBUG
	D2D1_FACTORY_OPTIONS factoryOption;
#ifndef NDEBUG
	factoryOption.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#else
	factoryOption.debugLevel = D2D1_DEBUG_LEVEL_NONE;
#endif

	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory), &factoryOption, &factory);
	if (FAILED(result))
		return false;

	//Getting the DXGI device from Direct3D


	return true;
}
