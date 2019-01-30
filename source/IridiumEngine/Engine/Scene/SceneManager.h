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
	Gameobject* sceneNode;

private:
	void OnNewGameobjectCreated(IEventDataPtr _event);

	unsigned int GetNewInstanceID();

public:
	friend BaseSingleton;
	SceneManager();

	void Initialize();

	void Create();

	void Start();

	void Update(float _deltaTime);

	Gameobject* CreateNewGameobject(bool _isRendered = true, Gameobject* _parent = nullptr);

	inline Gameobject* GetSceneNode() const { return sceneNode; }
};