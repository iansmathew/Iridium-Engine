#pragma once
#include <SFML/Graphics.hpp>
#include "../../Helper/BaseSingleton.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"
#include "../Components/Gameobject.h"
#include <vector>




class GraphicsManager : public BaseSingleton<GraphicsManager>
{
private:
	sf::RenderWindow* window;
	std::vector<Gameobject*> gameobjectList;

	//TODO:[Diego Camacho] Update Ghetto Splash
	sf::Texture splashTexture;
	sf::Sprite splashSprite;
	bool playingSplash = false;
	float elapsedTime = 0;
	sf::Clock startClock;
	float totalSeconds = 10;

private:
	friend BaseSingleton;
	GraphicsManager();

	void OnNewGameobjectCreated(IEventDataPtr _event);

public:
	void Initialize();
	void Start();
	void Update();
	void DisplaySplashScreen();
};