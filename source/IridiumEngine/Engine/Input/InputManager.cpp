#include "InputManager.h"
#include <iostream>

InputManager::InputManager()
{

}

/**
	Called by engine whenever a key is pressed.
 */
void InputManager::OnKeyPressed(sf::Event _keyEvent)
{
	std::cout << "Key Pressed: " << _keyEvent.key.code << std::endl;
}

/**
	Called by engine whenever a key is released.
 */
void InputManager::OnKeyReleased(sf::Event _keyEvent)
{
	std::cout << "Key Released: " << _keyEvent.key.code << std::endl;
}

/**
	Shuts down and releases references in the component.
 */
void InputManager::Shutdown()
{
	
}
