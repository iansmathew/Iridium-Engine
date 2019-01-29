#pragma once
#include "../../Helper/BaseSingleton.h"
#include "../Events/EventManager.h"
#include "../Events/Events.h"
#include <vector>

//FORWARD DECLARATIONS
class Gameobject;

class SceneManager : public BaseSingleton<SceneManager>
{
	static unsigned int nextGoID;

private:
	std::vector<Gameobject*> gameobjectList;
	Gameobject* rootNode;

private:
	void OnNewGameobjectCreated(IEventDataPtr _event);

	unsigned int GetNewInstanceID();

public:
	friend BaseSingleton;
	SceneManager();

	void Initialize();

	void Start();

	void Update();

	Gameobject* CreateNewGameobject(bool _isRendered = true);

	inline Gameobject* GetRootNode() const { return rootNode; }

};