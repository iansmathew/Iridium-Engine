#include "TransformComponent.h"
#include "Gameobject.h"

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
}

/**
	Update call that applies the matrix transformation.
 */
void TransformComponent::Update()
{

}

/**
	Returns the transform of the GO in relation to the world space coordinates.
	Calls recursively to multiply parent transforms.

	@param Transform in world space coordinates
 */
sf::Transform TransformComponent::GetWorldTransform() const
{
	//Recursive exit condition
	if (GetGameobject()->GetParent() == nullptr)
		return sf::Transform::Identity * selfTransform;
	else
	{
		return GetGameobject()->GetParent()->GetTransformComponent()->GetWorldTransform() * selfTransform;
	}

}

/**
	Sets the local transform of the GO 
 */
void TransformComponent::SetLocalTransform(sf::Transform _transform)
{
	selfTransform = _transform;
}
