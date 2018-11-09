#pragma once
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <d2d1_2.h>
#include <dwrite.h>
#include <wrl/client.h>

class DWClass
{
public:
	DWClass();
	~DWClass();

	bool Initialize(Microsoft::WRL::ComPtr<ID2D1DeviceContext> _D2DDeviceContext);

	IDWriteTextLayout* GetTextLayout();
	ID2D1SolidColorBrush* GetYellowBrush();

private:
	Microsoft::WRL::ComPtr<IDWriteFactory> factory;
	ID2D1SolidColorBrush* yellowBrush;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormatFPS;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayoutFPS;

	
};
