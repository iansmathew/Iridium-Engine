#include "Scene.h"

Scene::Scene() : 
	Gameobject(false)
{

}

/**
	Recursively calls start on all children
 */
void Scene::Start()
{
	__super::Start();
}

/**
	Recursively calls update on all children
 */
void Scene::Update(float _deltaTime)
{
	__super::Update(_deltaTime);
}

/**
	Recursively calls shutdown on all children
 */
void Scene::Shutdown()
{
	throw std::logic_error("The method or operation is not implemented.");
}
