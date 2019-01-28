/**
	Window.h
	Purpose: The window class takes care of instantiating a single instance of the engine window.

	@author Ian Sebastian Mathew
	@version 1.0 0.19-01-09
 */
#pragma once
#include "../../Helper/BaseSingleton.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class WindowManager : public BaseSingleton<WindowManager>
{
private:
	sf::RenderWindow* window;

private:
	friend BaseSingleton;
	WindowManager();

public:
	sf::RenderWindow* GetWindow() const;

	void Initialize(int screenWidth = 800, int screenHeight = 600, bool isFullScreen = false);
	void Shutdown();
};
