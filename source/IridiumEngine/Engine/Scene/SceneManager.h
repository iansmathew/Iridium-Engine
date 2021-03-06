#pragma once
//----------------------------------------------------
#include "../../Helper/BaseSingleton.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"
#include <vector>
//----------------------------------------------------
#include <type_traits>
#include <assert.h>
//----------------------------------------------------
#include "Scene.h"

class SceneManager : public BaseSingleton<SceneManager>
{
	static unsigned int nextGoID;

private:
	std::vector<std::unique_ptr<Gameobject>> gameobjectList;
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

	template <class T, class = typename std::enable_if<std::is_base_of<Gameobject,T>::value,void*>::type>
	T* CreateNewGameobject(Gameobject* _parent = nullptr, bool _isRendered = true)
	{
		//Do not create a gameobject if there is no scene to create it in
		assert(currentScene);

		//Ensure that only of type Gameobject can be created 
		static_assert(std::is_base_of<Gameobject, T>::value, "T should inherit from Gameobject");

		//Create the instance of type template
		T* newGo = new T(_isRendered);

		//set the parent if given, else default to root
		if (_parent)
			_parent->AddChild(newGo);
		else
			currentScene->AddChild(newGo);

		return newGo;
	}

	template <class T, class = typename std::enable_if<std::is_base_of<Gameobject, T>::value, void*>::type>
	T* CreateNewGameobject(bool _isRendered = true)
	{
		//Do not create a gameobject if there is no scene to create it in
		//assert(currentScene);

		////Ensure that only of type Gameobject can be created 
		//static_assert(std::is_base_of<Gameobject, T>::value, "T should inherit from Gameobject");

		//Create the instance of type template
		T* newGo = new T(_isRendered);

		//set the parent if given, else default to root
		//currentScene->AddChild(newGo);
		//TODO: Remove scene dependancies on creating go


		return newGo;
	}

	/**
		Creates and returns a new sceneNode.
		Use this to create new scenes.

		Follows the factory design patern.
	 */
	template <class T  , class = typename std::enable_if<std::is_base_of<Scene,T>::value,void*>::type>
	T* CreateNewScene()
	{
		//Ensure that only of type Scene can be created 
		/*static_assert(std::is_base_of<Scene, T>::value, "T should inherit from Scene");*/

		T* newScene = new T();
		return newScene;
	}

	void LoadScene(Scene* _scene);

	void LoadSceneFromFile(std::string _filePath);

#pragma endregion SCENE_MANAGER_FUNCS

#pragma region GETTERS_AND_SETTERS

	Scene* GetSceneNode() const;

#pragma endregion GETTERS_AND_SETTERS

};
