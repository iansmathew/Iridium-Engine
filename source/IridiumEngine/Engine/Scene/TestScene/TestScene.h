#pragma once
#include "../Scene.h"

class TestScene : public Scene
{

private:
	Gameobject* crashGo;

protected:
	friend SceneManager;
	TestScene();
public:
#pragma region GAME_FLOW_FUNCS

	virtual void Start() override;


	virtual void Update(float _deltaTime) override;


	virtual void Shutdown() override;

#pragma endregion GAME_FLOW_FUNCS
};