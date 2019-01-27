#include "Engine.h"
#include "Window/WindowManager.h"
#include "Input/InputManager.h"
#include "../Helper/SysCheck.h"
#include <iostream>

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
	while (WindowManager::Instance()->GetWindow()->isOpen())
	{
		sf::Event event;
		while (WindowManager::Instance()->GetWindow()->pollEvent(event)) //poll all events for open window
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				windowManager->NotifyCloseRequest();
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
}

/**
	Default base constructor for Engine. 
 */
IridiumEngine::IridiumEngine()
{
	//Initialize engine components
	windowManager = WindowManager::Instance();
	inputManager = InputManager::Instance();

}

/**
	Checks if an instance of the engine is already running,
	performs various spec checks and 
	initializes various components of the Engine. 

	@return Returns the success value of initialization.
 */
bool IridiumEngine::Initialize()
{
	if (!CheckSystemRequirements())
		return false;

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

