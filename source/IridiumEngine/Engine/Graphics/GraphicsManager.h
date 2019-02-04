#pragma once
#include <SFML/Graphics.hpp>
#include "../../Helper/BaseSingleton.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"
#include <vector>

class Scene;

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
	void Update(Scene* _sceneNode);
	void DisplaySplashScreen();
};