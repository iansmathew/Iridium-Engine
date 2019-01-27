#pragma once

#include "../../Helper/BaseSingleton.h"
#include "SFML/Window/Event.hpp"

class InputManager : public BaseSingleton<InputManager>
{
public:
	void OnKeyPressed(sf::Event _keyEvent);

	void OnKeyReleased(sf::Event _keyEvent);

};