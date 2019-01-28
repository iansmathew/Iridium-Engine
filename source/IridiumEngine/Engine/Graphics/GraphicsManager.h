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

private:
	friend BaseSingleton;
	GraphicsManager();

	void OnNewGameobjectCreated(IEventDataPtr _event);

public:
	void Initialize();
	void Update();
};