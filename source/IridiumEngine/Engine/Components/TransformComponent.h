#pragma once
#include <SFML/Graphics/Transform.hpp>
#include "BaseComponent.h"

class TransformComponent : public BaseComponent, public sf::Transformable
{
private:
	sf::Transform selfTransform;

public:
	TransformComponent(Gameobject* _owner);

	virtual void Start() override;

	virtual void Update() override;

	sf::Transform GetWorldTransform() const;

	void SetLocalTransform(sf::Transform _transform);

	void Translate(float _x, float _y);
};