#include "InputManager.h"
#include <iostream>

void InputManager::OnKeyPressed(sf::Event _keyEvent)
{
	std::cout << "Key Pressed: " << _keyEvent.key.code << std::endl;
}

void InputManager::OnKeyReleased(sf::Event _keyEvent)
{
	std::cout << "Key Released: " << _keyEvent.key.code << std::endl;
}
