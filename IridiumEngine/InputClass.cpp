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

void InputClass::KeyDown(UINT key, LPARAM lParam)
{
	//Create a buffer to store the string value
	LPSTR buffer = new char[10];
	GetKeyNameTextA(lParam, buffer, 10); //convert lParam of uMsg to char

	keyStates[key] = true;
	std::string outputText = "Key down: ";
	outputText.append(buffer);

	DWriteRef->UpdateTextLayout(outputText);	

	delete buffer;
	buffer = nullptr;
}

void InputClass::KeyUp(UINT key, LPARAM lParam)
{
	LPSTR buffer = new char[10];
	GetKeyNameTextA(lParam, buffer, 10);

	keyStates[key] = false;
	std::string outputText = "Key up: ";
	std::string value(buffer);

	outputText.append(value);


	DWriteRef->UpdateTextLayout(outputText);

	delete buffer;
	buffer = nullptr;
}

bool InputClass::IsKeyDown(UINT key)
{
	return keyStates[key];
}

void InputClass::SetDirectWriteRef(DWClass* _DWriteRef)
{
	DWriteRef = _DWriteRef;
}
