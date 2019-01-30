#pragma once
#include "../Scene.h"

class SplashScene : public Scene
{
protected:
	friend SceneManager;
	SplashScene();
public:
#pragma region GAME_FLOW_FUNCS

	virtual void Start() override;

	virtual void Update(float _deltaTime) override;

	virtual void Shutdown() override;

#pragma endregion GAME_FLOW_FUNCS



};