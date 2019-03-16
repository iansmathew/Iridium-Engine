#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "AudioComponent.h"
#include "RigidbodyComponent.h"

class SceneManager;

class Gameobject
{
private:
	unsigned int instanceID;

	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	//AudioComponent* audioComponent;
	//RigidbodyComponent* rigidbodyComponent;

	Gameobject* parent;
	std::vector<Gameobject*> children;
	std::vector<BaseComponent*> componentList;
	
protected:
	/* The constructor is protected so that an instance of GO cannot be created
	unless through the Scene Manager or through derived classes*/
	friend SceneManager;
	Gameobject(bool _isRendered = true);

public:
	std::string name = "Gameobject";

public:
	~Gameobject();

#pragma region GAME_FLOW_FUNCS

	virtual void Start();

	virtual void Update(float _deltaTime);

	virtual void Draw(sf::RenderTarget& _windowRef, sf::RenderStates _states);

	virtual void Shutdown();

#pragma endregion GAME_FLOW_FUNCS
	
#pragma region GETTERS

	/* Returns the unique instance ID of the gameobject */
	inline int GetInstanceID() const { return instanceID; }

	/* Returns the parents of the gameobject */
	inline Gameobject* GetParent() const { return parent; }

	///* Returns the transform component */
	//inline TransformComponent* GetComponent<TransformComponent>() const { return transformComponent; }

	///* Return the render component */
	//inline RenderComponent* GetComponent<RenderComponent>() const { return renderComponent; }

	///* Returns the audio component */
	//inline AudioComponent* GetComponent<AudioComponent>() const { return audioComponent; }

	///* Returns the rigidbody component */
	//inline RigidbodyComponent* GetComponent<RigidbodyComponent>() const { return rigidbodyComponent; }

#pragma endregion GETTERS

#pragma region GAMEOBJECT_FUNCS

	void AddChild(Gameobject* _child);

	bool RemoveChild(Gameobject* _child);

	template <class T>
	void AddComponent()
	{
		componentList.push_back(new T(this));
	}

	template <class T>
	T* GetComponent()
	{
		for (auto comp : componentList)
		{
			if (T* requestComp = dynamic_cast<T*>(comp))
			{
				return requestComp;
			}
		}

		return nullptr;
	}

	virtual void SerializeData(std::string _jsonString);

#pragma endregion GAMEOBJECT_FUNCS
};