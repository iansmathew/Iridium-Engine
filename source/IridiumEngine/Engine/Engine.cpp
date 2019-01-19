#include "Engine.h"
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
	Default base constructor for Engine. 
 */
IridiumEngine::IridiumEngine()
{
	std::cout << "Constructor initialized" << std::endl;
}

/**
	Initializes various components of the Engine. 

	@return Returns the success value of initialization.
 */
bool IridiumEngine::Initialize()
{
	return true;
}
