#include "Gameobject.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"
#include "../irincludes.h"
//#include "../../ExternalTools/json.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "RenderComponent.h"
#include "TransformComponent.h"

//using json = nlohmann::json;

/**
	Constructor that sends out the GO_Created event
 */
Gameobject::Gameobject(bool _isRendered /*= true*/)
{
	instanceID = IridiumEngine::Instance()->GetSceneManager()->GetNewInstanceID();

	componentArray.resize(maxComponents);

	AddComponent<TransformComponent>(this);


	//post GO created event
	std::shared_ptr<EvtData_On_GO_Created> pEvent(new EvtData_On_GO_Created(this));
	EventManager::Instance()->QueueEvent(pEvent);
	//std::vector<BaseComponent> test;
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


	for (auto& comp : componentArray)
	{
		if (comp == nullptr)
		{
			continue;
		}
		comp->Start();
	}

	for (auto& child : children)
	{
		child->Start();
	}
}

/**
	
	
 */
 /// <summary>
 /// Adds a child to the node
 /// and set the parent node to this.
 /// </summary>
 /// <param name="_child">The child gameobject.</param>
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


 /// <summary>
 /// Removes a child from the children vector.
 /// and sets the parent of the child to null.
 /// Iterates through the children vector and removes
 /// child based on instance id
 /// </summary>
 /// <param name="_child">The child gamemobject to remove.</param>
 /// <returns>Success of remove operation. Fails if child was not found</returns>
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


 /// <summary>
 /// Serializes the data into a json string .
 /// </summary>
 /// <param name="_jsonString">The json string.</param>
void Gameobject::SerializeData(std::string _jsonString)
{
	//json jsonObj = {
	//	{"name", this->name},
	//	{"instanceID", this->instanceID}
	//};

	//json newComp = {
	//	{"name", "NewGameobject"},
	//	{"instanceID", 24}
	//};

	//std::ofstream o("../savedScene.json");
	//o << std::setw(4) << jsonObj << newComp <<  std::endl;
}

 /// <summary>
 /// Calls update on GO and recursively on children.
 /// </summary>
 /// <param name="_deltaTime">The time elapsed as seconds since last frame</param>
void Gameobject::Update(float _deltaTime)
{
	//Perform own update
	for (auto& comp : componentArray)
	{

		if (comp == nullptr)
		{
			continue;
		}
		comp->Update();
	}

	//Call update on children
	for (auto& child : children)
		child->Update(_deltaTime);
}

/**
	Calls draw from the window passed into it.
	Also recursively calls draw for its children
 */
/// <summary>
/// Calls draw from the window passed into it.
/// Also recursively calls draw for its children
/// </summary>
/// <param name="_windowRef">Windows Target to which it will draw</param>
/// <param name="_states"></param>
void Gameobject::Draw(sf::RenderTarget& _windowRef, sf::RenderStates _states)
{
	_states.transform *= GetComponent<TransformComponent>()->getTransform();

	//Draw object if isRendered is set to true
	
	if (HasComponent<RenderComponent>())
	{
		auto renderComponent = GetComponent<RenderComponent>();
		if (renderComponent->GetVisibility())
			_windowRef.draw(renderComponent->GetSprite(), _states);

		for (auto& child : children)
		{
			child->Draw(_windowRef, _states);
		}
	}
}

/**
	Takes care of marking the gameobject to be deleted
 */
void Gameobject::Shutdown()
{
	for (auto& comp : componentArray)
	{
		if (comp == nullptr)
		{
			continue;
		}
		comp->Shutdown();
	}

	//Call shutdown on children
	for (auto& child : children)
		child->Shutdown();
}
