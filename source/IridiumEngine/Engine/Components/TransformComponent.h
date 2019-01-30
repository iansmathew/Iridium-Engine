#pragma once
#include <SFML/Graphics/Transform.hpp>
#include "BaseComponent.h"

class TransformComponent : public BaseComponent
{
private:
	sf::Transform selfTransform;

public:
	TransformComponent(Gameobject* _owner);

	virtual void Start() override;


	virtual void Update() override;

	sf::Transform GetWorldTransform() const;

	void SetLocalTransform(sf::Transform _transform);
};