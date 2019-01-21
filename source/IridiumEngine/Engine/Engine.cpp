#include "Engine.h"
#include "Window/Window.h"
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
	while (Window::Instance()->GetWindow()->isOpen())
	{
		sf::Event event;
		while (Window::Instance()->GetWindow()->pollEvent(event)) //poll all events for open window
		{
			if (event.type == sf::Event::Closed)
			{
				Window::Instance()->NotifyCloseRequest();
			}
		}
	}
}

/**
	Default base constructor for Engine. 
 */
IridiumEngine::IridiumEngine()
{
	//Check system requirements

	//Initialize engine components

}

/**
	Initializes various components of the Engine. 

	@return Returns the success value of initialization.
 */
bool IridiumEngine::Initialize()
{
	return true;
}

/**
	Checks if the user's system has the required hardware/software capabilities to run the program.

	@return Returns true if system check passes. 
 */
bool IridiumEngine::CheckSystemRequirements()
{
	return true;
}
