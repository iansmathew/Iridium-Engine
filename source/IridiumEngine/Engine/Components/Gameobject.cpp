#include "Gameobject.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"
#include "../irincludes.h"

#include <iostream>

/**
	Constructor that sends out the GO_Created event
 */
Gameobject::Gameobject(bool _isRendered /*= true*/)
{
	instanceID = IridiumEngine::Instance()->GetSceneManager()->GetNewInstanceID();
	transformComponent = new TransformComponent(this);
	renderComponent = new RenderComponent(this, _isRendered);
	audioComponent = new AudioComponent(this);

	//post GO created event
	std::shared_ptr<EvtData_On_GO_Created> pEvent(new EvtData_On_GO_Created(this));
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
	std::cout << "Base start method called on instance: " << GetInstanceID() << std::endl;

	transformComponent->Start();
	renderComponent->Start();
	audioComponent->Start();

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
	//TODO: Check if AddChild properly reparents the child so that it only lives under ONE parent and is not shared.
	//i.e two parents do not have _child in their children vector

	//if child already has a parent, remove it from the parent's list
	if (_child->parent)
	{
		_child->parent->RemoveChild(_child);
	}

	_child->parent = this;
	children.push_back(_child);
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

/**
	Calls update on GO and recursively on children.

	@param _deltaTime: The time elapsed as seconds since last frame
 */
void Gameobject::Update(float _deltaTime)
{
	//Perform own update
	transformComponent->Update();

	//Call update on children
	for (auto child : children)
		child->Update(_deltaTime);
}

/**
	Calls draw from the window passed into it.
	Also recursively calls draw for its children
 */
void Gameobject::Draw(sf::RenderWindow& _windowRef)
{
	_windowRef.draw(renderComponent->GetSprite(), GetTransformComponent()->GetWorldTransform());

	for (auto child : children)
	{
		child->Draw(_windowRef);
	}
}

/**
	Takes care of marking the gameobject to be deleted
 */
void Gameobject::Shutdown()
{
	audioComponent->Shutdown();

	//Call shutdown on children
	for (auto child : children)
		child->Shutdown();
}
