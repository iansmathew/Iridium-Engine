#include "SceneManager.h"
#include <type_traits>
#include <assert.h>

#include "../Components/Gameobject.h"
#include "../Scene/SplashScene/SplashScene.h"

/**
	Initializing static member
 */
unsigned int SceneManager::nextGoID = 0;

/**
	Constructor
 */
SceneManager::SceneManager()
{
	gameobjectList = std::vector<Gameobject*>();
}

/**
	Initializes required components 
	Subscribes to the game object creation event
 */
void SceneManager::Initialize()
{
	//Subscribe to gameobject created event
	EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &SceneManager::OnNewGameobjectCreated);
	EventManager::Instance()->AddListener(delegateFunc, EvtData_On_GO_Created::eventType);

	//Create root scene
	//currentScene = new SplashScene();
	auto splashScene = CreateNewScene<SplashScene>();
	LoadScene(splashScene);
}

/**
	Called before start methods are run.
	Create GOs here.
 */
void SceneManager::Create()
{
	//TODO:[iansmathew] Create a scene that holds these gameobjects and calls the update inside the scene
	
}

/**
	Calls start on the different gameobjects
 */
void SceneManager::Start()
{
	currentScene->Start();
}

/**
	Calls update on all gameobjects
 */
void SceneManager::Update(float _deltaTime)
{
	if (!currentScene)
	{
		//TODO[iansmathew]: Log null scene
		return;
	}

	currentScene->Update(_deltaTime);
}

template <class T>
/**
	Creates a new gameobject of a given Gameobject Derived class.
	Follows a factory method design pattern
 */
T* SceneManager::CreateNewGameobject(bool _isRendered /*= true*/, Gameobject* _parent /*= nullptr*/)
{
	//Do not create a gameobject if there is no scene to create it in
	assert(currentScene);

	//Ensure that only of type Gameobject can be created 
	static_assert(std::is_base_of<Gameobject, T>::value, "T should inherit from Gameobject");

	//Create the instance of type template
	T* newGo = new T(GetNewInstanceID(), _isRendered);

	//set the parent if given, else default to root
	if (_parent)
		_parent->AddChild(newGo);
	else
		currentScene->AddChild(newGo);

	return newGo;
}

/**
	Creates and returns a new sceneNode. 
	Use this to create new scenes.

	Follows the factory design patern.
 */
template <class T>
T* SceneManager::CreateNewScene()
{
	//Ensure that only of type Scene can be created 
	static_assert(std::is_base_of<Scene, T>::value, "T should inherit from Scene");

	T* newScene = new T();
	return newScene;
}

/**
	Switches the current scene to the passed in scene.
	Flow is as follows:
		Call destroy / shutdown on current scene
		Switch scene
		Call start on new scene

	Update should follow as usual
 */
void SceneManager::LoadScene(Scene* _scene)
{
	if (currentScene)
		currentScene->Shutdown();

	//Update current scene, event will take care of calling Start
	currentScene = _scene;
	
	//Post scene change event
	std::shared_ptr<EvtData_On_Scene_Change> pEvent(new EvtData_On_Scene_Change());
	EventManager::Instance()->QueueEvent(pEvent);
}

/**
	Returns the current scene node casted as a Gameobject
 */
Gameobject* SceneManager::GetSceneNodeGameobject() const
{
	return static_cast<Gameobject*>(currentScene);
}

/**
	Called when a new gameobject is created.
	Adds the created gameobject to the list of gameobjects.
 */
void SceneManager::OnNewGameobjectCreated(IEventDataPtr _event)
{
	std::shared_ptr<EvtData_On_GO_Created> pCastEventData = std::static_pointer_cast<EvtData_On_GO_Created>(_event);
	gameobjectList.push_back(pCastEventData->GetOwnedGameobject());
}

unsigned int SceneManager::GetNewInstanceID()
{
	return ++nextGoID;
}
