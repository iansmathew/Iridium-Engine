#include "TrialComponent.h"
#include <iostream>



TrialComponent::TrialComponent(Gameobject* owner) : BaseComponent(owner)
{
}


void TrialComponent::Start()
{
	std::cout << "ComponentStarted";

}

void TrialComponent::Update()
{
	std::cout << "Updating";

}

TrialComponent::~TrialComponent()
{
}
