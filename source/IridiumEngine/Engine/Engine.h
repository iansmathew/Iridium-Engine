/**
	Engine.h
	Purpose: Defines the main Iridium engine class  and methods.

	@author Ian Sebastian Mathew
	@version 1.0 2019-01-19
 */

#pragma once

#include "../Helper/BaseSingleton.h"

/*FORWARD DECLARATIONS*/
class WindowManager;
class InputManager;

class IridiumEngine : public BaseSingleton<IridiumEngine>
{
private:
	WindowManager* windowManager;
	InputManager* inputManager;

public:

public:
	~IridiumEngine();

	bool Initialize();

	void Run();

	void Shutdown();

private:
	friend BaseSingleton<IridiumEngine>;
	IridiumEngine();
	IridiumEngine(const IridiumEngine &_copy) = delete; //no copy constructor

	bool CheckSystemRequirements();
};