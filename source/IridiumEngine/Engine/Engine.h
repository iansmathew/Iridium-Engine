/**
	Engine.h
	Purpose: Defines the main Iridium engine class  and methods.

	@author Ian Sebastian Mathew
	@version 1.0 2019-01-19
 */

#pragma once

#include "../Helper/BaseSingleton.h"
#include "EngineStates/EngineState.h"

/*FORWARD DECLARATIONS*/
class WindowManager;
class InputManager;
class EventManager;
class GraphicsManager;
class SceneManager;

class IridiumEngine : public BaseSingleton<IridiumEngine>
{
private:
	WindowManager* windowManager;
	GraphicsManager* graphicsManager;
	InputManager* inputManager;
	SceneManager* sceneManager;
	EventManager* eventManager;

	ENGINE_STATE engineState;

public:
	~IridiumEngine();

	bool Initialize();

	void Run();

	void HandleWindowEvents();

	void Shutdown();

	void Create();

	void Start();

	inline ENGINE_STATE GetEngineState() const { return engineState; }

	inline void SetEngineState(ENGINE_STATE _val) { engineState = _val; }


private:
	friend BaseSingleton<IridiumEngine>;
	IridiumEngine();
	IridiumEngine(const IridiumEngine &_copy) = delete; //no copy constructor

	bool CheckSystemRequirements();
};