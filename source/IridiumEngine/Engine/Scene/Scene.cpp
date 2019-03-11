#include "Scene.h"

Scene::Scene() : 
	Gameobject(false)
{
	AddComponent<MusicComponent>();
}

/**
	Recursively calls start on all children
 */
void Scene::Start()
{
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
	__super::Shutdown();
}

