#pragma once
#include "../Components/Gameobject.h"

class SceneManager;

class Scene : public Gameobject
{
private:
	friend SceneManager;
	Scene(unsigned int _instanceID);
public:
#pragma region GAME_FLOW_FUNCS

	virtual void Start() override;

	virtual void Update(float _deltaTime) override;

	virtual void Shutdown() override;

#pragma endregion GAME_FLOW_FUNCS



};