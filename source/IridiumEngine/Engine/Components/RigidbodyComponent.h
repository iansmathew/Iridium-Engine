#include "BaseComponent.h"
#include <SFML/System/Vector2.hpp>

class RigidbodyComponent : public BaseComponent<RigidbodyComponent>
{
public:
	bool enabled = true;
	bool enableGravity = false;

	float mass = 1.0f;

	struct AABB {
		sf::Vector2f bottomLeft;
		sf::Vector2f topRight;
	};

	AABB axisAlignedCorners;

private:
	sf::Vector2f currentVelocity;

	sf::Vector2f totalForces;

public:
	RigidbodyComponent(Gameobject* _owner);

	~RigidbodyComponent();

#pragma region GAME_FLOW_FUNCS

	virtual void Start() override;
	
	virtual void Update() override;

	void PhysicsUpdate(float _deltaTime);

#pragma endregion GAME_FLOW_FUNCS

	sf::Vector2f GetCurrentVelocity() const;

	//void PositionCorrection();

	void AddForce(sf::Vector2f forces);

	void AddForce(float _x, float _y);

	void SetAABB();

private:
};

