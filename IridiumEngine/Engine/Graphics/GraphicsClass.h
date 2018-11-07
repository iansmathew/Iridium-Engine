#pragma once
class GraphicsClass
{
public:
	GraphicsClass();
	~GraphicsClass();

	bool Initialize(int screenWidth, int screenHeight);
	void Shutdown();
	bool Frame();

private:
	bool Render();
};

