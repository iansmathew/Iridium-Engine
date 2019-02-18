#include <vector>
#include "../Events/EventManager.h"
#include "../Events/Events.h"
#include "../../Helper/BaseSingleton.h"
#include "../Components/Gameobject.h"
#include "SFML/System//Vector2.hpp"

class PhysicsManager : public BaseSingleton<PhysicsManager>
{

private:

	struct CollisionInfo {
		RigidbodyComponent* rigidbodyA = nullptr;
		RigidbodyComponent* rigidbodyB = nullptr;

		sf::Vector2i collisionNormal = sf::Vector2i(0,0);

		CollisionInfo() = default;
		CollisionInfo(RigidbodyComponent* _rigidbodyA, RigidbodyComponent* _rigidbodyB) : rigidbodyA(_rigidbodyA), rigidbodyB(_rigidbodyB) {}
	};

	std::vector<RigidbodyComponent*> rigidbodyList;
	std::vector<CollisionInfo> collisionList;

public:

	


	float groundTolerance = 0.01f;

	sf::Vector2f gravity = sf::Vector2f(0, 9.8f);

public:

	friend BaseSingleton;
	PhysicsManager();

	~PhysicsManager();

#pragma region GAME_FLOW_FUNCS

	void Initialize();

	void Start();

	void Update(float _deltaTime);

#pragma endregion GAME_FLOW_FUNCS

private:

	bool OverlapTest(RigidbodyComponent* rigidbodyA, RigidbodyComponent* rigidbodyB);

	void CollisionDetection();

	void CollisionResolution();

	void GroundCorrection();
	

#pragma region EVENT_HANDLERS

	void OnNewGameobjectCreated(IEventDataPtr _event);

#pragma endregion EVENT_HANDLERS

	void AddRigidbody(RigidbodyComponent* _rigidbody);

	void RemoveRigidbodies(IEventDataPtr _event);

};