#include "RenderComponent.h"

/**
	Constructor
 */
RenderComponent::RenderComponent(Gameobject* _owner, bool _isRendered /*= true*/)
	: BaseComponent(_owner)
{
	isRendered = _isRendered;
	texture = sf::Texture();
	sprite = sf::Sprite();
}

/**
	Called initially before updates to set up the gameobject
 */
void RenderComponent::Start()
{
	//TODO:[iansmathew] Make a static instance of default textures so that all unassigned sprites can share. (Tag: Optimization)
	//Set default texture properties
	if (!texture.loadFromFile("../../assets/engine/images/defaultTexture.png"))
		throw std::runtime_error("Failed to find texture");
	

	texture.setSmooth(true);
	texture.setRepeated(false);

	//Set default sprite properties
	sprite.setTexture(texture);
	//sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); //making sure our default sprites scale to 32x32
	sprite.setOrigin(0.5f, 0.5f);

	//If sprite is not to be rendered, make transparent
	if (!isRendered)
		sprite.setColor(sf::Color(0, 0, 0, 0));
}

sf::Sprite& RenderComponent::GetSprite()
{
	return sprite;
}

