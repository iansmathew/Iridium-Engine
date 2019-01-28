#pragma once
#include "RenderComponent.h"
#include "Transform.h"

class Gameobject
{
public:

private:
	Transform* transform;
	RenderComponent* renderComponent;

private:

public:
	Gameobject();

	Transform* GetTransform() const;
	RenderComponent* GetRenderComponent() const;

	void Start();

};