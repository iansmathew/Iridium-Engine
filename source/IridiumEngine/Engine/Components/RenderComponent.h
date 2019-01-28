#pragma once
#include <sfml/Graphics.hpp>
#include "BaseComponent.h"

class RenderComponent : public BaseComponent
{
private:
	bool isRendered;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	RenderComponent(bool _isRendered = true);

	virtual void Start() override;
	sf::Sprite& GetSprite();
};