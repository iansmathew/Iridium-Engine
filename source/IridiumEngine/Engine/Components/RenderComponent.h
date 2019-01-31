#pragma once
#include <SFML/Graphics.hpp>
#include "BaseComponent.h"

class RenderComponent : public BaseComponent
{
private:
	bool isRendered;
	sf::Sprite sprite;
	sf::Texture texture;

private:
	void LoadDefaultTexture();

public:
	RenderComponent(Gameobject* _owner, bool _isRendered = true);

	virtual void Start() override;
	sf::Sprite& GetSprite();

	void SetTexture(std::string _filePath);
};