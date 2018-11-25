#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;


class D3DSystem
{
public:
	D3DSystem();
	~D3DSystem();

	bool Initialize(int screenWidth, int screenHeight, bool isVysncEnabled, HWND HWnd, bool isFullScreenEnabled, float screenDepth, float screenNear);

	void Shutdown();
	void BeginScene(float r, float g, float b, float a) const;
	void EndScene() const;

private:
	bool bIsVsyncEnabled;
	int videoCardMemory;
	char videoCardDescription[128];
	IDXGISwapChain* swapChain;
	ID3D11Device* D3DDevice;
	ID3D11DeviceContext* deviceContext;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RasterizerState* rasterState;
	XMMATRIX projectionMatrix;
	XMMATRIX worldMatrix;
	XMMATRIX orthoMatrix;

};