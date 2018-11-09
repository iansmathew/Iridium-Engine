#pragma once
#pragma comment(lib, "Dwrite.lib")

#include <dwrite.h>
#include <wrl/client.h>

class DWClass
{
public:
	DWClass();
	~DWClass();

	bool Initialize();

private:
	Microsoft::WRL::ComPtr<IDWriteFactory> factory;

	
};
