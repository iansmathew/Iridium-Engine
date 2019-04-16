#include "Scene.h"
#include "../../ExternalTools/json.hpp"
#include <iomanip>
#include <iosfwd>
#include <fstream>
#include "../Components/Gameobject.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"

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
	if (player)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player->GetComponent<RigidbodyComponent>()->AddForce(-150, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player->GetComponent<RigidbodyComponent>()->AddForce(150, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player->GetComponent<RigidbodyComponent>()->AddForce(0.0f, -150);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player->GetComponent<RigidbodyComponent>()->AddForce(0.0f, 150);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			auto autdo = player->GetComponent<AudioComponent>();
			autdo->PlaySound("spaceSound");
		}


	}

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

