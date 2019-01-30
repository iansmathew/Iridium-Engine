#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "RenderComponent.h"
#include "TransformComponent.h"

class SceneManager;
//class TransformComponent;
//class RenderComponent;

class Gameobject
{
private:
	unsigned int instanceID;

	TransformComponent* transformComponent;
	RenderComponent* renderComponent;

	Gameobject* parent;
	std::vector<Gameobject*> children;
	
protected:
	/* The constructor is protected so that an instance of GO cannot be created
	unless through the Scene Manager or through derived classes*/
	friend SceneManager;
	Gameobject(unsigned int _instanceId, bool _isRendered = true);

public:
	~Gameobject();

#pragma region GAME_FLOW_FUNCS

	virtual void Start();

	virtual void Update(float _deltaTime);

	void Draw(sf::RenderWindow& _windowRef);

	virtual void Shutdown();

#pragma endregion GAME_FLOW_FUNCS
	
#pragma region GETTERS

	/* Returns the unique instance ID of the gameobject */
	inline int GetInstanceID() const { return instanceID; }

	/* Returns the parents of the gameobject */
	inline Gameobject* GetParent() const { return parent; }

	/* Returns the transform component */
	inline TransformComponent* GetTransformComponent() const { return transformComponent; }

	/* Return the render component */
	inline RenderComponent* GetRenderComponent() const { return renderComponent; }

#pragma endregion GETTERS

#pragma region GAMEOBJECT_FUNCS

	void AddChild(Gameobject* _child);

	bool RemoveChild(Gameobject* _child);

#pragma endregion GAMEOBJECT_FUNCS
};