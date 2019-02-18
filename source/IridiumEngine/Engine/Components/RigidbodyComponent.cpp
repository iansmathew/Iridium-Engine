#include "Gameobject.h"
#include <iostream>
#include "../Physics/PhysicsManager.h"


#define VECTOR2ZERO sf::Vector2f(0,0)

RigidbodyComponent::RigidbodyComponent(Gameobject* _owner) : BaseComponent(_owner)
{
}

RigidbodyComponent::~RigidbodyComponent()
{
}

void RigidbodyComponent::Start()
{
	SetAABB();
}

void RigidbodyComponent::Update(float _deltaTime)
{
	sf::Vector2f velocity = sf::Vector2f();

	if (enabled)
	{
		if (enableGravity)
		{
			velocity = PhysicsManager::Instance()->gravity;
		}

		velocity += totalForces / mass;

		if (mass <= 0)
		{
			velocity = VECTOR2ZERO;
		}

		currentVelocity += velocity * _deltaTime;

		sf::Vector2f position = GetGameobject()->GetTransformComponent()->getPosition();
		position += currentVelocity * _deltaTime;

		GetGameobject()->GetTransformComponent()->setPosition(position);

		SetAABB();

		totalForces = VECTOR2ZERO;

		//PositionCorrection();
	}
}

sf::Vector2f RigidbodyComponent::GetCurrentVelocity() const
{
	return currentVelocity;
}
//
//void RigidbodyComponent::PositionCorrection()
//{
//	if (GetGameobject()->name == "Crash")
//	{
//		std::cout << this->axisAlignedCorners.bottomLeft.y << std::endl;
//
//		float windowHeight = WindowManager::Instance()->GetWindow()->getSize().y;
//
//		float imageHeight = GetGameobject()->GetTransformComponent()->getPosition().y - this->axisAlignedCorners.bottomLeft.y;
//
//
//		if (this->axisAlignedCorners.bottomLeft.y >= (windowHeight))
//		{
//			float imageSize = axisAlignedCorners.bottomLeft.y - GetGameobject()->GetTransformComponent()->getPosition().y;
//
//			sf::Vector2f newPosition = sf::Vector2f(GetGameobject()->GetTransformComponent()->getPosition().x, windowHeight - imageSize);
//
//			GetGameobject()->GetTransformComponent()->setPosition(newPosition);
//		}
//	}
//
//}

void RigidbodyComponent::AddForce(sf::Vector2f forces)
{
	totalForces += forces;
}

void RigidbodyComponent::AddForce(float _x, float _y)
{
	totalForces += sf::Vector2f(_x, _y);
}

void RigidbodyComponent::SetAABB()
{
	float bottomX = GetGameobject()->GetTransformComponent()->getPosition().x;
	float bottomY = GetGameobject()->GetTransformComponent()->getPosition().y + GetGameobject()->GetRenderComponent()->GetSprite().getTextureRect().height;

	float topX = GetGameobject()->GetTransformComponent()->getPosition().x + GetGameobject()->GetRenderComponent()->GetSprite().getTextureRect().width;
	float topY = GetGameobject()->GetTransformComponent()->getPosition().y;

	axisAlignedCorners.bottomLeft = sf::Vector2f(bottomX, bottomY);
	axisAlignedCorners.topRight = sf::Vector2f(topX, topY);
}
