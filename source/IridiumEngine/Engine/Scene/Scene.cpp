#include "Scene.h"
#include "../../ExternalTools/json.hpp"
#include <iomanip>
#include <iosfwd>
#include <fstream>

using json = nlohmann::json;


Scene::Scene()
{

}

Scene::~Scene()
{

}

/**
	Recursively calls start on all children
 */
void Scene::Start()
{
	for (auto& child : gameobjects)
		child->Start();
}

/**
	Recursively calls update on all children through base
 */
void Scene::Update(float _deltaTime)
{
		for (auto& child : gameobjects)
		child->Update(_deltaTime);
}

void Scene::Draw(sf::RenderTarget& _windowRef, sf::RenderStates _states)
{
	for (auto& child : gameobjects)
	{
		child->Draw(_windowRef, _states);
	}
}

/**
	Recursively calls shutdown on all children through base
 */
void Scene::Shutdown()
{
	for (auto& child : gameobjects)
		child->Shutdown();

}

void Scene::AddChild(Gameobject* _child)
{
	gameobjects.emplace_back(std::move(_child));

}

bool Scene::RemoveChild(Gameobject* _child)
{
	for (int childIndex = 0; childIndex < gameobjects.size(); childIndex++)
	{
		if (_child->GetInstanceID() == gameobjects[childIndex]->GetInstanceID())
		{
			gameobjects.erase(gameobjects.begin() + childIndex);
			return true;
		}
	}

	return false;

}

