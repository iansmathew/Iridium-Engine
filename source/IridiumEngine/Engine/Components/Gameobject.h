#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TransformComponent;
class RenderComponent;

class Gameobject
{
public:

private:
	TransformComponent* transform;
	RenderComponent* renderComponent;

	Gameobject* parent;
	std::vector<Gameobject*> children;
	
private:

public:
	Gameobject(bool _isRendered = true);

	TransformComponent* GetTransform() const;
	RenderComponent* GetRenderComponent() const;

	void Start();

	void AddChild(Gameobject* _child);

	void Draw(sf::RenderWindow& _windowRef);

	//TODO:[iansmathew] Create a remove child
};