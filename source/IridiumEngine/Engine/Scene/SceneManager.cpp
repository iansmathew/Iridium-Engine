#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult);}
#endif

#include "SceneManager.h"
#include "../../ExternalTools/tinyxml2.h"
#include <iostream>

using namespace tinyxml2;

/**
	Initializing static member
 */
unsigned int SceneManager::nextGoID = 0;

/**
	Constructor
 */
SceneManager::SceneManager()
{
	gameobjectList = std::vector<std::unique_ptr<Gameobject>>();
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
	Loads a scene from a JSON file and creates it accordingly
 */
void SceneManager::LoadSceneFromFile(std::string _filePath)
{
	//Opem xml file
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile(_filePath.c_str());
	XMLCheckResult(eResult);

	//Get reference to root node
	XMLNode* sceneNode = xmlDoc.FirstChildElement("root");
	assert(sceneNode && "Root node could not be found!");

	auto scene = CreateNewScene<Scene>();

	for (XMLNode* xmlGo = sceneNode->FirstChildElement("Gameobject"); xmlGo != nullptr; xmlGo =  xmlGo->NextSiblingElement())
	{
		//auto go = CreateNewGameobject<Gameobject>(true);
		auto thing = xmlGo->FirstChildElement("name")->GetText();
		std::cout << thing << std::endl;
	}

	//Load the created scene
	LoadScene(scene);
}

/**
	Returns the current scene node casted as a Gameobject
 */
Scene* SceneManager::GetSceneNode() const
{
	return currentScene;
}

/**
	Called when a new gameobject is created.
	Adds the created gameobject to the list of gameobjects.
 */
void SceneManager::OnNewGameobjectCreated(IEventDataPtr _event)
{
	std::shared_ptr<EvtData_On_GO_Created> pCastEventData = std::static_pointer_cast<EvtData_On_GO_Created>(_event);
	gameobjectList.emplace_back(pCastEventData->GetOwnedGameobject());
}

unsigned int SceneManager::GetNewInstanceID()
{
	return ++nextGoID;
}