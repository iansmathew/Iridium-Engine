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
