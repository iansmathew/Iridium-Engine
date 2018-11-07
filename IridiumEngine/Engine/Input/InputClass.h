#pragma once
class InputClass
{
public:
	InputClass();
	~InputClass();

	void Initialize();
	void Shutdown();

	void KeyDown(UINT key);
	void KeyUp(UINT key);

	bool IsKeyDown(UINT key);

private:
	bool keyStates[256];
};

