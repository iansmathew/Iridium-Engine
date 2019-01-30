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
public:

private:
	unsigned int instanceID;

	TransformComponent* transformComponent;
	RenderComponent* renderComponent;

	Gameobject* parent;
	std::vector<Gameobject*> children;
	
private:
	friend SceneManager;
	Gameobject(unsigned int _instanceId, bool _isRendered = true);

public:
	~Gameobject();

	void Start();


	void Update(float _deltaTime);

	void Draw(sf::RenderWindow& _windowRef);

	void AddChild(Gameobject* _child);

	bool RemoveChild(Gameobject* _child);

	/* Returns the unique instance ID of the gameobject */
	inline int GetInstanceID() const { return instanceID; }

	/* Returns the parents of the gameobject */
	inline Gameobject* GetParent() const { return parent; }

	/* Returns the transform component */
	inline TransformComponent* GetTransformComponent() const { return transformComponent; }

	/* Return the render component */
	inline RenderComponent* GetRenderComponent() const { return renderComponent; }

	//TODO:[iansmathew] Create a remove child
};