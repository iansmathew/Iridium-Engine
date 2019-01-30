#include "SceneManager.h"
#include <type_traits>

#include "../Components/Gameobject.h"

Gameobject* testNode; //TODO: [iansmathew] Remove test node from global scope
Gameobject* testNode2;


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
	EventManager::Instance()->AddListener(delegateFunc, EvtDat_On_GO_Created::eventType);

	//Create root scene
	sceneNode = new Gameobject(GetNewInstanceID(), false);
}

/**
	Called before start methods are run.
	Create GOs here.
 */
void SceneManager::Create()
{
	//TODO: [Create a scene that holds these gameobjects and calls the update inside the scene]
	testNode = CreateNewGameobject<Gameobject>();
	testNode2 = CreateNewGameobject<Gameobject>(true, testNode);

	testNode2->GetTransformComponent()->Translate(200, 200);
}

/**
	Calls start on the different gameobjects
 */
void SceneManager::Start()
{
	sceneNode->Start();
}

/**
	Calls update on all gameobjects
 */
void SceneManager::Update(float _deltaTime)
{
	testNode->GetTransformComponent()->Translate(10.0f * _deltaTime, 10.0f * _deltaTime);
	sceneNode->Update(_deltaTime);
}

template <class T>
/**
	Creates a new gameobject of a given Gameobject Derived class.
	Follows a factory method design pattern
 */
T* SceneManager::CreateNewGameobject(bool _isRendered /*= true*/, Gameobject* _parent /*= nullptr*/)
{
	//Ensure that only of type Gameobject can be created 
	static_assert(std::is_base_of<Gameobject, T>::value, "T should inherit from Gameobject");

	//Create the instance of type template
	T* newGo = new T(GetNewInstanceID(), _isRendered);

	//set the parent if given, else default to root
	if (_parent)
		_parent->AddChild(newGo);
	else
		sceneNode->AddChild(newGo);

	return newGo;
}

/**
	Called when a new gameobject is created.
	Adds the created gameobject to the list of gameobjects.
 */
void SceneManager::OnNewGameobjectCreated(IEventDataPtr _event)
{
	std::shared_ptr<EvtDat_On_GO_Created> pCastEventData = std::static_pointer_cast<EvtDat_On_GO_Created>(_event);
	gameobjectList.push_back(pCastEventData->GetOwnedGameobject());
}

unsigned int SceneManager::GetNewInstanceID()
{
	return ++nextGoID;
}
