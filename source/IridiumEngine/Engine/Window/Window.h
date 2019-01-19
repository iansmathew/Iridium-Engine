/**
	Window.h
	Purpose: The window class takes care of instantiating a single instance of the engine window.

	@author Ian Sebastian Mathew
	@version 1.0 0.19-01-09
 */
#pragma once
#include "../../Helper/BaseSingleton.h"
#include <SFML/Window.hpp>

class Window : public BaseSingleton<Window>
{
private:
	sf::Window window;

private:
	friend BaseSingleton;
	Window();

	void InitializeWindow(int screenWidth = 800, int screenHeight = 600, bool isFullScreen = false);
};
