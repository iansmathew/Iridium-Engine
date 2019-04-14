#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult);}
#endif

#include "../../ExternalTools/tinyxml2.h"
//----------------------------------------------------
#include <iostream>
//----------------------------------------------------
#include "SceneManager.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/RenderComponent.h"
#include "../Components/AudioComponent.h"



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
	
	//Post scene change 
	std::shared_ptr<EvtData_On_Scene_Change> pEvent(new EvtData_On_Scene_Change());
	EventManager::Instance()->QueueEvent(pEvent);
}

/**
	Loads a scene from a JSON file and creates it accordingly
 */
void SceneManager::LoadSceneFromFile(std::string _filePath)
{
	//Notift managers to clear any previous held queues.
	std::shared_ptr<EvtData_Pre_Scene_Load> pEvent(new EvtData_Pre_Scene_Load());
	EventManager::Instance()->QueueEvent(pEvent);


	//Create scene node
	auto scene = CreateNewScene<Scene>();

	//Opem xml file
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile(_filePath.c_str());
	XMLCheckResult(eResult);

	//Get reference to root node
	XMLNode* sceneNode = xmlDoc.FirstChildElement("ArrayOfXMLGameobject");
	assert(sceneNode && "Root node could not be found!");


	for (XMLNode* xmlGo = sceneNode->FirstChildElement("XMLGameobject"); xmlGo != nullptr; xmlGo =  xmlGo->NextSiblingElement())
	{
		//Create a new gameobject and attach to scene
		auto newGo = CreateNewGameobject<Gameobject>(scene);
		scene->AddChild(newGo);
		
		//Set values according to XML
		newGo->name = xmlGo->FirstChildElement("nameDetails")->FirstChildElement("name")->GetText();
		
		float posX;
		float posY;
		float scaleX;
		float scaleY;

		//Transform
		auto transformDetails = xmlGo->FirstChildElement("transformDetails");
		transformDetails->FirstChildElement("posX")->QueryFloatText(&posX);
		transformDetails->FirstChildElement("posY")->QueryFloatText(&posY);
		transformDetails->FirstChildElement("scaleX")->QueryFloatText(&scaleX);
		transformDetails->FirstChildElement("scaleY")->QueryFloatText(&scaleY);

		newGo->GetComponent<TransformComponent>()->setPosition(posX, posY);
		newGo->GetComponent<TransformComponent>()->setScale(scaleX, scaleY);

		bool hasRenderer = false;
		bool hasRigidbody = false;
		bool hasAudio = false;

		xmlGo->FirstChildElement("hasRenderComponent")->QueryBoolText(&hasRenderer);
		xmlGo->FirstChildElement("hasRigidbodyComponent")->QueryBoolText(&hasRigidbody);
		xmlGo->FirstChildElement("hasAudioComponent")->QueryBoolText(&hasAudio);


		//Renderer
		if (hasRenderer)
		{
			bool isRendered = false;
			std::string imagePath = "";

			auto rendererDetails = xmlGo->FirstChildElement("rendererDetails");
			rendererDetails->FirstChildElement("isRendered")->QueryBoolText(&isRendered);
			imagePath = rendererDetails->FirstChildElement("imagePath")->GetText();

			//Apply values
			newGo->AddComponent<RenderComponent>(newGo);
			newGo->GetComponent<RenderComponent>()->SetVisibility(isRendered);
			newGo->GetComponent<RenderComponent>()->SetTexture(imagePath);
		}

		//Rigidbody
		if (hasRigidbody)
		{
			bool isEnabled = true;
			bool isAffectedByGravity = true;
			float mass = 1.0f;

			//Query values
			auto rigidbodyDetails = xmlGo->FirstChildElement("rigidbodyDetails");

			rigidbodyDetails->FirstChildElement("isEnabled")->QueryBoolText(&isEnabled);
			rigidbodyDetails->FirstChildElement("isAffectedByGravity")->QueryBoolText(&isAffectedByGravity);
			rigidbodyDetails->FirstChildElement("mass")->QueryFloatText(&mass);

			//Apply values
			newGo->AddComponent<RigidbodyComponent>(newGo);
			newGo->GetComponent<RigidbodyComponent>()->mass = mass;
			newGo->GetComponent<RigidbodyComponent>()->enabled = isEnabled;
			newGo->GetComponent<RigidbodyComponent>()->enableGravity = isAffectedByGravity;
		}

		//Audio 
		if (hasAudio) //TODO:Chagne
		{
			auto audioDetails = xmlGo->FirstChildElement("audioDetails");
			auto clipNameDetails = audioDetails->FirstChildElement("clipNames");
			auto clipPathDetails = audioDetails->FirstChildElement("clipPaths");

			newGo->AddComponent<AudioComponent>(newGo);

			auto xmlClipPath = clipPathDetails->FirstChildElement("string"); 
			for (auto xmlClipName = clipNameDetails->FirstChildElement("string"); xmlClipName != nullptr; xmlClipName = xmlClipName->NextSiblingElement())
			{

				//Get values
				std::string clipName = xmlClipName->GetText();
				std::string clipPath = xmlClipPath->GetText();

				//Iterate path var
				xmlClipPath = xmlClipPath->NextSiblingElement();

				//Apply values
				newGo->GetComponent<AudioComponent>()->AddSoundClip(clipName, clipPath);
			}
		}

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