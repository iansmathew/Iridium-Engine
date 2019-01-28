#pragma once
#include <SFML/Graphics.hpp>
#include "BaseComponent.h"

class RenderComponent : public BaseComponent
{
private:
	bool isRendered;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	RenderComponent(Gameobject* _owner, bool _isRendered = true);

	virtual void Start() override;
	sf::Sprite& GetSprite();
};