#include "Scene.h"

Scene::Scene(unsigned int _instanceID)
	: Gameobject(_instanceID, false)
{

}

void Scene::Start()
{
	__super::Start();
}

void Scene::Update(float _deltaTime)
{
	__super::Update(_deltaTime);
}
