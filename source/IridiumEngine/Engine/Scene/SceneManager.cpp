#include "SceneManager.h"
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
	rootNode = new Gameobject(GetNewInstanceID(), false);
}

/**
	Called before start methods are run.
	Create GOs here.
 */
void SceneManager::Create()
{
	//TODO: [Create a scene that holds these gameobjects and calls the update inside the scene]
	testNode = CreateNewGameobject();
	testNode2 = CreateNewGameobject(true, testNode);

	testNode2->GetTransformComponent()->Translate(200, 200);
}

/**
	Calls start on the different gameobjects
 */
void SceneManager::Start()
{
	rootNode->Start();
}

/**
	Calls update on all gameobjects
 */
void SceneManager::Update(float _deltaTime)
{
	testNode->GetTransformComponent()->Translate(10.0f * _deltaTime, 10.0f * _deltaTime);
	rootNode->Update(_deltaTime);
}

/**
	Creates a new gameobject
 */
Gameobject* SceneManager::CreateNewGameobject(bool _isRendered /*= true*/, Gameobject* _parent /*= nullptr*/)
{
	Gameobject* newGo = new Gameobject(GetNewInstanceID(), _isRendered);

	//set the parent if given, else default to root
	if (_parent)
		_parent->AddChild(newGo);
	else
		rootNode->AddChild(newGo);

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
