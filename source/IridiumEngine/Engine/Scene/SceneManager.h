#pragma once
#include "../../Helper/BaseSingleton.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"
#include <vector>

//FORWARD DECLARATIONS
class Gameobject;
class Scene;

class SceneManager : public BaseSingleton<SceneManager>
{
	static unsigned int nextGoID;

private:
	std::vector<Gameobject*> gameobjectList;
	Scene* currentScene;

private:
#pragma region EVENT_HANDLERS

	void OnNewGameobjectCreated(IEventDataPtr _event);

#pragma endregion EVENT_HANDLERS

#pragma region GAMEOBJECT_FUNCS

	friend Gameobject;
	unsigned int GetNewInstanceID();

#pragma endregion GAMEOBJECT_FUNCS

public:
	friend BaseSingleton;
	SceneManager();

#pragma region GAME_FLOW_FUNCS

	void Initialize();

	void Create();

	void Start();

	void Update(float _deltaTime);

#pragma endregion GAME_FLOW_FUNCS

#pragma region SCENE_MANAGER_FUNCS

	template <class T>
	T* CreateNewGameobject(bool _isRendered = true, Gameobject* _parent = nullptr);

	template <class T>
	T* CreateNewScene();

	void LoadScene(Scene* _scene);

#pragma endregion SCENE_MANAGER_FUNCS

#pragma region GETTERS_AND_SETTERS

	Gameobject* GetSceneNodeGameobject() const;

#pragma endregion GETTERS_AND_SETTERS

};
