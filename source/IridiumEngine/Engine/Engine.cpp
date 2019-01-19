#include "Engine.h"
#include "Window/Window.h"
#include <iostream>

/** 
	A static method that returns an instance of the engine. A new static instance is created 
	on run time if not previously initialized.

	@return A pointer to the static instance of the Iridium Engine.
*/

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
	//TODO: Implement run
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

}
