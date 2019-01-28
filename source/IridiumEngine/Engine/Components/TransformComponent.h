#pragma once
#include "BaseComponent.h"

class TransformComponent : public BaseComponent
{
public:
	TransformComponent(Gameobject* _owner);

	virtual void Start() override;

};