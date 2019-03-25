#include "PyBehaviour.h"
#include "../IridiumEngine/Engine/Components/RenderComponent.h"





PyBehaviour::PyBehaviour(Gameobject* owner) : BaseComponent(owner)
{
}


void PyBehaviour::Start()
{
	//GetGameobject()->GetComponent<RenderComponent>()->SetVisibility(false);

}

void PyBehaviour::Update()
{

}

void PyBehaviour::Shutdown()
{

}


PyBehaviour::~PyBehaviour()
{
}
