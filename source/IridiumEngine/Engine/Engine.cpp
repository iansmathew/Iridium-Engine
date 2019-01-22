#include "Engine.h"
#include "Window/Window.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>

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
	Checks if the user's system has the required hardware/software capabilities to run the program.

	@return Returns true if system check passes. 
 */
bool IridiumEngine::CheckSystemRequirements()
{
	if (!HasFreeDiskSpace())
		return false;

	return true;
}

/**
	Checks if the system has the required storage space needed to run the program.
	The required space is a placeholder value.
	Display's a message box with the result.

	@return Returns true if the system has free space.
*/
bool IridiumEngine::HasFreeDiskSpace()
{
	bool result = false;
	int requiredSpace = 300; //program space spec requirement in MB.
	ULARGE_INTEGER ulFreeSpace;
	ULARGE_INTEGER ulTotalSpace;
	ULARGE_INTEGER ulTotalFreeSpace;
	std::string msgTxt;

	GetDiskFreeSpaceEx("C:", &ulFreeSpace, &ulTotalSpace, &ulTotalFreeSpace);

	int totalFreeSpaceInMb = (ulTotalFreeSpace.QuadPart / (1024 * 1024));

	if (requiredSpace < totalFreeSpaceInMb)
	{
		msgTxt = "Sufficient space";
		result = true;
	}
	else
	{
		std::ostringstream buffer;
		buffer << "Insufficient space. \nDisk space required: " << requiredSpace << "MB" << ".\nDisk space available: " << totalFreeSpaceInMb << "MB";

		msgTxt = buffer.str();
		result = false;
	}

	int msgboxID = MessageBox(
		nullptr,
		msgTxt.c_str(),
		"Storage check",
		MB_ICONINFORMATION
	);
	
	return result;
}
