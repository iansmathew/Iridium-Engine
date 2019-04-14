#define _DEBUG //TODO: [iansmathew] Remove in release. Redefinition on purpose since SFML release libraries have not been implemented

#include "Engine.h"

#include <iostream>

#include "../Helper/SysCheck.h"
#include "Events/Events.h"
#include "Window/WindowManager.h"
#include "Input/InputManager.h"
#include "Graphics/GraphicsManager.h"
#include "Scene/SceneManager.h"
#include "Audio/AudioManager.h"
#include "Physics/PhysicsManager.h"
#include "Components/Gameobject.h"
#include "Scene/SplashScene/SplashScene.h"

/**
	Default destructor for Engine.
*/
IridiumEngine::~IridiumEngine()
{

}

/**
	Main update loop that takes care of handling events.
 */
void IridiumEngine::Run()
{
	engineClock = sf::Clock(); //Create a clock

	while (WindowManager::Instance()->GetWindow()->isOpen())
	{
		//Handle window events followed by game events
		HandleWindowEvents();
		eventManager->Update(); 

		//Choose which update loop to run
		if (GetEngineState() == ENGINE_STATE::Initialization)
		{
			graphicsManager->DisplaySplashScreen();
		}
		else if (GetEngineState() == ENGINE_STATE::Start)
		{
			sceneManager->Start();
			SetEngineState(ENGINE_STATE::Update);
		}
		else if (GetEngineState() == ENGINE_STATE::Update)
		{
			float elapsedTime = engineClock.restart().asSeconds();

			physicsManager->Update(elapsedTime);
			//Update GOs
			sceneManager->Update(elapsedTime); //Pass in elapsed time as deltaTime

			//Update graphics, pass in the scene node to recursively call graphics draw
			graphicsManager->Update(sceneManager->GetSceneNode());
		}
	}
}

/**
	Dispatch and handle various SFML events
*/
void IridiumEngine::HandleWindowEvents()
{
	sf::Event event;
	while (WindowManager::Instance()->GetWindow()->pollEvent(event)) //poll all events for open window
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			Shutdown();
			break;

		case sf::Event::KeyPressed:
			inputManager->OnKeyPressed(event);
			break;

		case sf::Event::KeyReleased:
			inputManager->OnKeyReleased(event);
			break;

		default:
			break;
		}
	}
}

/**
	Takes care of releasing and destroying various engine components.
 */
void IridiumEngine::Shutdown()
{
	//Destroying components in reverse order of initialization
	inputManager->Shutdown();
	windowManager->Shutdown();
	//TODO: [iansmathew] Add scenemanager shutdown
}

/**
	Default base constructor for Engine. 
 */
IridiumEngine::IridiumEngine()
{
	//Initialize engine components
	windowManager = WindowManager::Instance();
	graphicsManager = GraphicsManager::Instance();
	inputManager = InputManager::Instance();
	eventManager = EventManager::Instance();
	sceneManager = SceneManager::Instance();
	audioManager = AudioManager::Instance();
	physicsManager = PhysicsManager::Instance();
}

/**
	Checks if an instance of the engine is already running,
	performs various spec checks and 
	initializes various components of the Engine. 

	@return Returns the success value of initialization.
 */
bool IridiumEngine::Initialize()
{
#ifndef _DEBUG
	if (!CheckSystemRequirements())
		return false;
#endif

	SetEngineState(ENGINE_STATE::Initialization);

	//Initialize managers
	windowManager->Initialize();
	graphicsManager->Initialize();
	sceneManager->Initialize();
	audioManager->Initialize();
	physicsManager->Initialize();

	//Subscribe to events
	EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &IridiumEngine::OnSceneChange);
	EventManager::Instance()->AddListener(delegateFunc, EvtData_On_Scene_Change::eventType);

	//auto splashScene = sceneManager->CreateNewScene<SplashScene>();
	//sceneManager->LoadScene(splashScene);

	sceneManager->LoadSceneFromFile("../MySaveFile.xml");

	return true;
}


/**
	Creates an instance of the system checker and uses it to 
	checks if the user's system has the required hardware/software capabilities 
	to run the program.

	@return Returns true if system check passes. 
 */
bool IridiumEngine::CheckSystemRequirements()
{
	SysCheck systemCheck;
	systemCheck.DisplayCPUStats();

	if (!systemCheck.HasFreeMemory())
		return false;

	if (!systemCheck.HasFreeDiskSpace())
		return false;

	return true;
}

void IridiumEngine::OnSceneChange(IEventDataPtr _event)
{
	//std::shared_ptr<EvtData_On_Scene_Change> pCastEventData = std::static_pointer_cast<EvtData_On_Scene_Change>(_event);
	SetEngineState(ENGINE_STATE::Start);
}

