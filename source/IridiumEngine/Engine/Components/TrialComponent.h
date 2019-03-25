#pragma once
#include "BaseComponent.h"

class TrialComponent :
	public BaseComponent
{
public:
	TrialComponent(Gameobject* owner);

	void Start() override;

	void Update() override;

	~TrialComponent();
};

