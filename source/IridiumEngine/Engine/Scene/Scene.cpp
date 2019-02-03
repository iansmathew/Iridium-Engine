#include "Scene.h"

Scene::Scene() : 
	Gameobject(false)
{
	musicComponent = new MusicComponent(this);
}

/**
	Recursively calls start on all children
 */
void Scene::Start()
{
	musicComponent->Start();
	__super::Start();
}

/**
	Recursively calls update on all children through base
 */
void Scene::Update(float _deltaTime)
{
	__super::Update(_deltaTime);
}

/**
	Recursively calls shutdown on all children through base
 */
void Scene::Shutdown()
{
	musicComponent->Shutdown();

	__super::Shutdown();
}


