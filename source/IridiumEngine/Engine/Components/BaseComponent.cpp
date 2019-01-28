#include "BaseComponent.h"

/**
	Constructor that takes in the owned gameobject.
 */
BaseComponent::BaseComponent(Gameobject* _owner)
{
	isUpdated = true;
	owner = _owner;
}

/**
	Called before any updates are run.
	Use this to set up the component
 */
void BaseComponent::Start()
{

}

/**
	The update function for the component
 */
void BaseComponent::Update()
{
	
}

/**
	Returns a pointer to the gameobject it belongs to.

	@return Gameobject owner
 */
Gameobject* BaseComponent::GetGameobject() const
{
	return owner;
}
