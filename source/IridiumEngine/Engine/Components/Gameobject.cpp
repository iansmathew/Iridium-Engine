#include "Gameobject.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

#include <iostream>

/**
	Constructor that sends out the GO_Created event
 */
Gameobject::Gameobject(unsigned int _instanceId, bool _isRendered /*= true*/)
{
	instanceID = _instanceId;
	transformComponent = new TransformComponent(this);
	renderComponent = new RenderComponent(this, _isRendered);

	//post GO created event
	std::shared_ptr<EvtDat_On_GO_Created> pEvent(new EvtDat_On_GO_Created(this));
	EventManager::Instance()->QueueEvent(pEvent);
}

Gameobject::~Gameobject()
{
	//TODO:[iansmathew] Take care of destroying created components and setting parents and children's parents to none.
}

/**
	Called on engine graphics initialization.
	Used to set up components
 */
void Gameobject::Start()
{
	transformComponent->Start();
	renderComponent->Start();

	for (auto child : children)
	{
		child->Start();
	}
}

/**
	Adds a child to the node
	and set the parent node to this.
 */
void Gameobject::AddChild(Gameobject* _child)
{
		_child->parent = this;
		children.push_back(_child);
		//TODO: This will currently not allow any new go to be parented until a remove child is implemented
}

/**
	Removes a child from the children vector 
	and sets the parent of the child to null.

	Iterates through the children vector and removes
	child based on instance id

	@return Success of remove operation. Fails if child was not found
 */
bool Gameobject::RemoveChild(Gameobject* _child)
{
	if (!_child->parent) //if child GO does not have a parent, why bother removing it? Return false so that dev knows this is stupid
		return false;

	for (int childIndex = 0; childIndex < children.size(); childIndex++)
	{
		if (_child->GetInstanceID() == children[childIndex]->GetInstanceID())
		{
			children[childIndex]->parent = nullptr;
			children.erase(children.begin() + childIndex);
			return true;
		}
	}

	return false;
}

void Gameobject::Update()
{
	//Perform own update

	//Call update on children
	for (auto child : children)
		child->Update();
}

/**
	Calls draw from the window passed into it.
	Also recursively calls draw for its children
 */
void Gameobject::Draw(sf::RenderWindow& _windowRef)
{
	_windowRef.draw(renderComponent->GetSprite());

	for (auto child : children)
	{
		child->Draw(_windowRef);
	}
}
