/**
	Engine.h
	Purpose: Defines the main Iridium engine class  and methods.

	@author Ian Sebastian Mathew
	@version 1.0 2019-01-19
 */

#pragma once

#include <SFML/System/Clock.hpp>

#include "../Helper/BaseSingleton.h"
#include "EngineStates/EngineState.h"
#include "Events/EventManager.h"


/*FORWARD DECLARATIONS*/
class WindowManager;
class InputManager;
class EventManager;
class GraphicsManager;
class SceneManager;

class IridiumEngine : public BaseSingleton<IridiumEngine>
{
private:
	ENGINE_STATE engineState;

	//Managers
	WindowManager* windowManager;
	GraphicsManager* graphicsManager;
	InputManager* inputManager;
	SceneManager* sceneManager;
	EventManager* eventManager;

	sf::Clock engineClock;

private:
	friend BaseSingleton<IridiumEngine>;
	IridiumEngine();
	IridiumEngine(const IridiumEngine &_copy) = delete; //no copy constructor

	bool CheckSystemRequirements();

#pragma region EVENT_HANDLERS

	void OnSceneChange(IEventDataPtr _event);

#pragma endregion EVENT_HANDLERS

public:
	~IridiumEngine();

#pragma region GAME_FLOW_FUNCS

	bool Initialize();

	void Run();

	void HandleWindowEvents();

	void Shutdown();

#pragma endregion GAME_FLOW_FUNCS

#pragma region GETTERS_AND_SETTERS

	inline ENGINE_STATE GetEngineState() const { return engineState; }
	inline void SetEngineState(ENGINE_STATE _val) { engineState = _val; }

#pragma endregion GETTERS

};