#include "RenderComponent.h"

/**
	Loads and sets the default purple texture for the GO
*/
void RenderComponent::LoadDefaultTexture()
{
	//TODO:[iansmathew] Make a static instance of default textures so that all unassigned sprites can share. (Tag: Optimization)
	//Set default texture properties
	if (!texture.loadFromFile("../../assets/engine/images/defaultTexture.png"))
		throw std::runtime_error("Failed to find texture");


	texture.setSmooth(true);
	texture.setRepeated(false);

	//Set default sprite properties
	sprite.setTexture(texture);
	sprite.setOrigin(0.5f, 0.5f);

	//If sprite is not to be rendered, make transparent
	if (!isRendered)
		sprite.setColor(sf::Color(0, 0, 0, 0));
}

/**
	Constructor
 */
RenderComponent::RenderComponent(Gameobject* _owner, bool _isRendered /*= true*/)
	: BaseComponent(_owner)
{
	isRendered = _isRendered;
	texture = sf::Texture();
	sprite = sf::Sprite();

	LoadDefaultTexture();
}

/**
	Called initially before updates to set up the gameobject
 */
void RenderComponent::Start()
{
	
}

sf::Sprite& RenderComponent::GetSprite()
{
	return sprite;
}

/**
	Sets the texture of the gameobject
 */
void RenderComponent::SetTexture(std::string _filePath)
{
	//TODO:[iansmathew] Make sure this isn't actually using two textures thus increasing memory usage
	texture = sf::Texture();

	if (!texture.loadFromFile(_filePath))
		throw std::runtime_error("Failed to find texture");

	texture.setSmooth(true);
	texture.setRepeated(false);

}

