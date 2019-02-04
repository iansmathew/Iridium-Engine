#pragma once
#include "../Components/Gameobject.h"
#include "../Components/MusicComponent.h"


class SceneManager;

class Scene : public Gameobject
{
private:
	MusicComponent* musicComponent;

protected:
	/* The constructor is protected so that an instance of Scene cannot be created
	unless through the Scene Manager*/
	friend SceneManager;
	Scene();
public:
#pragma region GAME_FLOW_FUNCS

	virtual void Start() override;

	virtual void Update(float _deltaTime) override;

	virtual void Shutdown() override;

#pragma endregion GAME_FLOW_FUNCS

#pragma region GETTERS

	inline MusicComponent* GetMusicComponent() const { return musicComponent; }

#pragma endregion GETTERS
};