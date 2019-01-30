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
	void OnNewGameobjectCreated(IEventDataPtr _event);

	unsigned int GetNewInstanceID();

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

	void LoadScene(Scene* _scene);

#pragma endregion SCENE_MANAGER_FUNCS

#pragma region GETTERS

	Gameobject* GetSceneNodeGameobject() const;

#pragma endregion GETTERS

};