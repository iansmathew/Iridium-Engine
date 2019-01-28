#pragma once
#include <sfml/Graphics.hpp>

class RenderComponent
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	RenderComponent();

	void Start();
	sf::Sprite& GetSprite();
};