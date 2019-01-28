#include "TransformComponent.h"

/**
	Constructor that takes in the gameobject owner.
 */
TransformComponent::TransformComponent(Gameobject* _owner)
	: BaseComponent(_owner)
{

}

/**
	Called before any updates.
	Use this to setup the components
 */
void TransformComponent::Start()
{
}
