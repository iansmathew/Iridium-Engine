#pragma once
#include "../IridiumEngine/Engine/Components/Gameobject.h"
#include "../IridiumEngine/Engine/Components/BaseComponent.h"


class PyBehaviour : public BaseComponent
{
public:
	PyBehaviour(Gameobject* owner);

	virtual void Start() override;

	virtual void Update() override;

	virtual void Shutdown() override;

	~PyBehaviour();
};

