#include "GraphicsManager.h"
#include "../Window/WindowManager.h"
#include "../../Engine/Engine.h"
#include "../Components/Gameobject.h"


/**
	Constructor
 */
GraphicsManager::GraphicsManager()
{
}

/**
	Event delegate function that is called every time a new gameobject is created.
	This function takes care of adding the gameobject to list of gameobject to be 
	utilized by the graphics engine.
 */
void GraphicsManager::OnNewGameobjectCreated(IEventDataPtr _event)
{
	std::shared_ptr<EvtData_On_GO_Created> pCastEventData = std::static_pointer_cast<EvtData_On_GO_Created>(_event);
}

/** 
	Creates and sets references
 */
void GraphicsManager::Initialize()
{
	window = WindowManager::Instance()->GetWindow();

	//TODO:[diegocamacho] Create splash screen here.
}

/**
	Passes the window to all GOs recursively and asks them to display themselves
 */
void GraphicsManager::Update(Gameobject* _sceneNode)
{
	// if in between switching scenes, dont bother rendering.
	if (!_sceneNode)
	{
		//TODO:[iansmathew] Create a global Logger
		return;
	}

	window->clear();
	//Call draw on first gameobject which is root scene node created by engine
	//SceneManager::Instance()->GetRootNode()->Draw(*window);
	_sceneNode->Draw(*window);
	window->display();
}

/**
	Displays the splash screen for a set duration.
*/
void GraphicsManager::DisplaySplashScreen()
{
	window->clear();

	//TODO:[diegocamacho] Implement splash screen here

	window->display();
	//exit condition
	IridiumEngine::Instance()->SetEngineState(ENGINE_STATE::Start);
}
