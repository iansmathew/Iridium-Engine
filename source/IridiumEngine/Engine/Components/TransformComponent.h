#pragma once
#include <SFML/Graphics/Transformable.hpp>
#include "BaseComponent.h"

class TransformComponent : public BaseComponent, public sf::Transformable
{
private:
	sf::Transform selfTransform;

public:
	TransformComponent(Gameobject* _owner);

	virtual void Start() override;

	virtual void Update() override;
};