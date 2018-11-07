#include "stdafx.h"
#include "Engine/Input/InputClass.h"

InputClass::InputClass()
{
}


InputClass::~InputClass()
{
}

void InputClass::Initialize()
{
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}
}

void InputClass::Shutdown()
{
	
}

void InputClass::KeyDown(UINT key)
{
	keyStates[key] = true;
}

void InputClass::KeyUp(UINT key)
{
	keyStates[key] = false;
}

bool InputClass::IsKeyDown(UINT key)
{
	return keyStates[key];
}
