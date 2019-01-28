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
	Gameobject(bool _isRendered = true);

	Transform* GetTransform() const;
	RenderComponent* GetRenderComponent() const;

	void Start();

};