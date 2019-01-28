#pragma once
#include <sfml/Graphics.hpp>

class RenderComponent
{
private:
	bool isRendered;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	RenderComponent(bool _isRendered = true);

	void Start();
	sf::Sprite& GetSprite();
};