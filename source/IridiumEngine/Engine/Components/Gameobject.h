#pragma once
#include "RenderComponent.h"
#include "Transform.h"

class Gameobject
{
public:
	Gameobject();

	Transform* GetTransform() const { return transform; }
	RenderComponent* GetRenderComponent() const { return renderComponent; }
protected:

private:
	Transform* transform;
	RenderComponent* renderComponent;

private:

public:

};