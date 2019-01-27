#include "WindowManager.h"

/**
	Constructor. Takes care of creating the SFML window
 */
WindowManager::WindowManager()
{
	InitializeWindow();
}

/**
	Creates an instance of the window. 
	@param screenWidth (optional = 800) The size of the screen width in pixels
	@param screenHeight (optional = 600) The size of the screen height in pixels
	@param isFullScreen (optional = false) Sets the screen to either fullscreen or windowed mode. 
 */
void WindowManager::InitializeWindow(int _screenWidth, int _screenHeight, bool _isFullScreen)
{
	//TODO: Implement screen
	window = new sf::Window(sf::VideoMode(_screenWidth, _screenHeight), "Iridium Engine");
}

/**
	Shutdowns and destroys all open windows and clears pointers
 */
void WindowManager::Shutdown()
{
	window->close();
}

/**
	Returns a pointer to the currently held window.

	@return A pointer to the current window of type sf::Window.
 */
sf::Window* WindowManager::GetWindow() const
{
	return window;
}

