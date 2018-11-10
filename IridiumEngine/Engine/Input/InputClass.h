#pragma once
#include <d3d11.h>
#include <d2d1_2.h>
#include <dwrite.h>
#include <wrl/client.h>
#include <sstream>
#include "Engine/Graphics/UI/Text/DWClass.h"


class InputClass
{
public:
	InputClass();
	~InputClass();

	void Initialize();
	void Shutdown();

	void KeyDown(UINT key, LPARAM lParam);
	void KeyUp(UINT key, LPARAM lParam);

	bool IsKeyDown(UINT key);

	void SetDirectWriteRef(DWClass* _DWriteRef);
private:
	bool keyStates[256];
	DWClass* DWriteRef;
};

