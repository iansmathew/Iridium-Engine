#include "Gameobject.h"
#include <iostream>
#include "BaseComponent.h"
#include "RigidbodyComponent.h"
#include "../Physics/PhysicsManager.h"
#include "TransformComponent.h"
#include "RenderComponent.h"



#define VECTOR2ZERO sf::Vector2f(0,0)

void RigidbodyComponent::Shutdown()
{
	
}

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

void RigidbodyComponent::Update()
{

}

void RigidbodyComponent::PhysicsUpdate(float _deltaTime)
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

		sf::Vector2f position = GetGameobject()->GetComponent<TransformComponent>().getPosition();
		position += currentVelocity * _deltaTime;

		GetGameobject()->GetComponent<TransformComponent>().setPosition(position);

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
	float bottomX = GetGameobject()->GetComponent<TransformComponent>().getPosition().x;
	float bottomY = GetGameobject()->GetComponent<TransformComponent>().getPosition().y + GetGameobject()->GetComponent<RenderComponent>().GetSprite().getTextureRect().height;

	float topX = GetGameobject()->GetComponent<TransformComponent>().getPosition().x + GetGameobject()->GetComponent<RenderComponent>().GetSprite().getTextureRect().width;
	float topY = GetGameobject()->GetComponent<TransformComponent>().getPosition().y;

	axisAlignedCorners.bottomLeft = sf::Vector2f(bottomX, bottomY);
	axisAlignedCorners.topRight = sf::Vector2f(topX, topY);
}
