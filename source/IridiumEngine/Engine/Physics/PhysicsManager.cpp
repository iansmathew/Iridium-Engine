#include "PhysicsManager.h"
#include "../Window/WindowManager.h"
#include <iostream>
#include <cstdlib>

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}


void PhysicsManager::Initialize()
{
	EventListenerDelegate delegateGOCreateFunc = fastdelegate::MakeDelegate(this, &PhysicsManager::OnNewGameobjectCreated);
	EventManager::Instance()->AddListener(delegateGOCreateFunc, EvtData_On_GO_Created::eventType);

	EventListenerDelegate delegateSceneChangeFunc = fastdelegate::MakeDelegate(this, &PhysicsManager::RemoveRigidbodies);
	EventManager::Instance()->AddListener(delegateSceneChangeFunc, EvtData_On_Scene_Change::eventType);
}

void PhysicsManager::Start()
{
}

void PhysicsManager::Update(float _deltaTime)
{
	for (auto rigidbody : rigidbodyList)
	{
		if (rigidbody->enabled)
		{
			rigidbody->Update(_deltaTime);
		}
	}
	
	CollisionDetection();

	CollisionResolution();

	GroundCorrection();
}

void PhysicsManager::AddRigidbody(RigidbodyComponent * _rigidbody)
{
	rigidbodyList.push_back(_rigidbody);
}

bool PhysicsManager::OverlapTest(RigidbodyComponent * rigidbodyA, RigidbodyComponent * rigidbodyB)
{
	RigidbodyComponent::AABB  boundingBoxA = rigidbodyA->axisAlignedCorners;
	RigidbodyComponent::AABB  boundingBoxB = rigidbodyB->axisAlignedCorners;

	if (boundingBoxA.topRight.x < boundingBoxB.bottomLeft.x || boundingBoxA.bottomLeft.x > boundingBoxB.topRight.x) return false;
	if (boundingBoxA.topRight.y > boundingBoxB.bottomLeft.y || boundingBoxA.bottomLeft.y < boundingBoxB.topRight.y) return false;

	return true;
}

void PhysicsManager::CollisionDetection()
{
	for (int rigidbodyAIndex = 0; rigidbodyAIndex < rigidbodyList.size(); rigidbodyAIndex++)
	{
		RigidbodyComponent* rigidbodyA = rigidbodyList[rigidbodyAIndex];
		for (int rigidbodyBIndex = rigidbodyAIndex; rigidbodyBIndex < rigidbodyList.size(); rigidbodyBIndex++)
		{
			RigidbodyComponent* rigidbodyB = rigidbodyList[rigidbodyBIndex];
			if (rigidbodyA->enabled)
			{
				if (rigidbodyA != rigidbodyB)
				{
					if (OverlapTest(rigidbodyA,rigidbodyB))
					{
						std::cout << "Overlapping" << std::endl;
						CollisionInfo collisionInfo(rigidbodyA,rigidbodyB);
						sf::Vector2f positionA, positionB;
	
						positionA = rigidbodyA->GetGameobject()->GetTransformComponent()->getPosition();
						positionB = rigidbodyB->GetGameobject()->GetTransformComponent()->getPosition();
	
						if (positionA.x < positionB.x)
						{
							collisionInfo.collisionNormal = sf::Vector2i(-1, collisionInfo.collisionNormal.y);
						}
						else {
							collisionInfo.collisionNormal = sf::Vector2i(1, collisionInfo.collisionNormal.y);
						}
	
						if (positionA.y < positionB.y)
						{
							collisionInfo.collisionNormal = sf::Vector2i(collisionInfo.collisionNormal.x, -1);
						}
						else {
							collisionInfo.collisionNormal = sf::Vector2i(collisionInfo.collisionNormal.x, 1);
						}
	
						collisionList.push_back(collisionInfo);
					}
				}
			}
		}
	}
}

void PhysicsManager::CollisionResolution()
{
	for (auto collision : collisionList) {
		float xDistance, yDistance;

		if (collision.collisionNormal.x == -1)
		{
			xDistance = collision.rigidbodyA->axisAlignedCorners.bottomLeft.x - collision.rigidbodyA->axisAlignedCorners.topRight.x;
		}

		xDistance = collision.rigidbodyA->axisAlignedCorners.bottomLeft.x - collision.rigidbodyA->axisAlignedCorners.topRight.x;
		xDistance = abs(xDistance);

		yDistance = collision.rigidbodyA->GetGameobject()->GetTransformComponent()->getPosition().y - collision.rigidbodyB->GetGameobject()->GetTransformComponent()->getPosition().y;
		yDistance = abs(yDistance);

		sf::Vector2f oldPosition = collision.rigidbodyB->GetGameobject()->GetTransformComponent()->getPosition();
		sf::Vector2f newPosition = sf::Vector2f(oldPosition.x + (collision.collisionNormal.x * xDistance), oldPosition.y + (collision.collisionNormal.y * yDistance));
		//sf::Vector2f newPosition = sf::Vector2f(300,300);

		collision.rigidbodyA->GetGameobject()->GetTransformComponent()->setPosition(newPosition);
	}

	collisionList.clear();
}

void PhysicsManager::GroundCorrection()
{
	float windowHeight = WindowManager::Instance()->GetWindow()->getSize().y;

	for (auto rigidbody : rigidbodyList)
	{ 
		if (rigidbody->enabled)
		{
			if (rigidbody->axisAlignedCorners.bottomLeft.y >= (windowHeight - groundTolerance))
			{
				float imageSize = rigidbody->axisAlignedCorners.bottomLeft.y - rigidbody->GetGameobject()->GetTransformComponent()->getPosition().y;

				sf::Vector2f newPosition = sf::Vector2f(rigidbody->GetGameobject()->GetTransformComponent()->getPosition().x, windowHeight - imageSize);

				rigidbody->GetGameobject()->GetTransformComponent()->setPosition(newPosition);
			}
		}
	}

	
}

void PhysicsManager::OnNewGameobjectCreated(IEventDataPtr _event)
{
	std::shared_ptr<EvtData_On_GO_Created> pCastEventData = std::static_pointer_cast<EvtData_On_GO_Created>(_event);
	Gameobject* GO = pCastEventData->GetOwnedGameobject();

	if (GO->GetRigidbodyComponent() != nullptr)
	{
		AddRigidbody(GO->GetRigidbodyComponent());
	}
}

void PhysicsManager::RemoveRigidbodies(IEventDataPtr _event)
{
	rigidbodyList.clear();
}
