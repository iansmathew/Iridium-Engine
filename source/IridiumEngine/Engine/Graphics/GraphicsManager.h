#pragma once
#include <SFML/Graphics.hpp>
#include "../../Helper/BaseSingleton.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"
#include <vector>

class Gameobject;

class GraphicsManager : public BaseSingleton<GraphicsManager>
{
private:
	sf::RenderWindow* window;

private:
	friend BaseSingleton;
	GraphicsManager();

	void OnNewGameobjectCreated(IEventDataPtr _event);

public:
	void Initialize();
	void Start();
	void Update(Gameobject* _sceneNode);
	void DisplaySplashScreen();
};