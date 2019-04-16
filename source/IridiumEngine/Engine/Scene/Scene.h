#pragma once
#include "../Components/Gameobject.h"
#include "../Components/MusicComponent.h"


class SceneManager;

class Scene
{
private:
	std::vector<std::unique_ptr<Gameobject>> gameobjects;


protected:
	/* The constructor is protected so that an instance of Scene cannot be created
	unless through the Scene Manager*/
	friend SceneManager;
	Scene();
	~Scene();

public:
#pragma region GAME_FLOW_FUNCS

	virtual void Start();

	virtual void Update(float _deltaTime);

	virtual void Draw(sf::RenderTarget& _windowRef, sf::RenderStates _states);

	virtual void Shutdown();

#pragma endregion GAME_FLOW_FUNCS

	void AddChild(Gameobject* _child);

	bool RemoveChild(Gameobject* _child);

	Gameobject* player;
};