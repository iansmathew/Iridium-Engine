#pragma once
#pragma comment(lib, "D2d1.lib")

#include <d2d1.h>
#include <wrl/client.h>

class D2DClass
{
public:
	D2DClass();
	~D2DClass();

	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device> _D3DDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> _D3DDeviceContext);

private:
	Microsoft::WRL::ComPtr<ID2D1Factory> factory;

};

