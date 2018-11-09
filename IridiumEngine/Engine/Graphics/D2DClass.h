#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <d2d1_2.h>
#include <d2d1_1.h>
#include <d2d1.h>

#include <wrl/client.h>

class D2DClass
{
public:
	D2DClass();
	~D2DClass();

	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device> _D3DDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> _D3DDeviceContext, Microsoft::WRL::ComPtr<IDXGISwapChain > _swapChain);

	Microsoft::WRL::ComPtr<ID2D1DeviceContext> GetDeviceContext();
	void BeginScene(IDWriteTextLayout* param1, ID2D1SolidColorBrush* param2);
	void EndScene();
private:
	Microsoft::WRL::ComPtr<ID2D1Factory2> factory;
	Microsoft::WRL::ComPtr<ID2D1Device1> D2DDevice;
	Microsoft::WRL::ComPtr<ID2D1DeviceContext> deviceContext;

};

