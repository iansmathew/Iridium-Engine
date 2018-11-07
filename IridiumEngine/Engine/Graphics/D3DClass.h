#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

class D3DClass
{
public:
	D3DClass();
	~D3DClass();

	bool Initialize(int screenWidth, int screenHeight, bool isVsyncEnabled, HWND hWnd, bool isFullscreen, float screenDepth, float screenNear);
	void Shutdown();

	void BeginScene(float red, float green, float blue, float alpha);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX& _projectionMatrix);
	void GetWorldMatrix(XMMATRIX& _worldMatrix);
	void GetOrthoMatrix(XMMATRIX& _orthoMatrix);

	void GetVideoCardInfo(char* cardName, int& memory);

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