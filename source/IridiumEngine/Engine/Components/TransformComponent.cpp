#include "TransformComponent.h"
#include "Gameobject.h"

#include <iostream>

/**
	Constructor that takes in the gameobject owner.
 */
TransformComponent::TransformComponent(Gameobject* _owner)
	: BaseComponent(_owner)
{
	selfTransform = sf::Transform::Identity;
}

/**
	Called before any updates.
	Use this to setup the components
 */
void TransformComponent::Start()
{
	std::cout << "Transform called start" << std::endl;
}

/**
	Update call that applies the matrix transformation.
 */
void TransformComponent::Update()
{

}

void TransformComponent::Shutdown()
{
	
}
