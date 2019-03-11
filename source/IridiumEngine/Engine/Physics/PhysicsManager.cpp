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
			rigidbody->PhysicsUpdate(_deltaTime);
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
	
						positionA = rigidbodyA->GetGameobject()->GetComponent<TransformComponent>()->getPosition();
						positionB = rigidbodyB->GetGameobject()->GetComponent<TransformComponent>()->getPosition();
	
						if (positionA.x < positionB.x)
						{
							collisionInfo.collisionNormal = sf::Vector2i(-1, 0);
						}
						else {
							collisionInfo.collisionNormal = sf::Vector2i(1, 0);
						}
						
						int collisionOffset = 5;
						float size = rigidbodyA->GetGameobject()->GetComponent<RenderComponent>()->GetSprite().getTextureRect().width - collisionOffset;
						if (positionA.x > rigidbodyB->axisAlignedCorners.bottomLeft.x - size && positionA.x < rigidbodyB->axisAlignedCorners.topRight.x - collisionOffset)
						{
							if (positionA.y < positionB.y)
							{
								collisionInfo.collisionNormal = sf::Vector2i(0, -1);
							}
							else {
								collisionInfo.collisionNormal = sf::Vector2i(0, 1);
							}
							
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

		if (collision.collisionNormal.x == -1 || collision.collisionNormal.x == 1)
		{
			xDistance = collision.rigidbodyA->axisAlignedCorners.bottomLeft.x - collision.rigidbodyA->axisAlignedCorners.topRight.x;
			xDistance = abs(xDistance);

			sf::Vector2f oldPosition = collision.rigidbodyB->GetGameobject()->GetComponent<TransformComponent>()->getPosition();

			sf::Vector2f newPosition = sf::Vector2f(oldPosition.x + (collision.collisionNormal.x * xDistance), collision.rigidbodyA->GetGameobject()->GetComponent<TransformComponent>()->getPosition().y);

			collision.rigidbodyA->GetGameobject()->GetComponent<TransformComponent>()->setPosition(newPosition);
		}
		else
		{
			if (collision.collisionNormal.y == -1 || collision.collisionNormal.y == 1)
			{

				yDistance = collision.rigidbodyA->axisAlignedCorners.bottomLeft.y - collision.rigidbodyA->axisAlignedCorners.topRight.y;
				yDistance = yDistance;

				sf::Vector2f oldPosition = collision.rigidbodyB->GetGameobject()->GetComponent<TransformComponent>()->getPosition();

				sf::Vector2f newPosition = sf::Vector2f(collision.rigidbodyA->GetGameobject()->GetComponent<TransformComponent>()->getPosition().x, oldPosition.y + (collision.collisionNormal.y * yDistance));

				collision.rigidbodyA->GetGameobject()->GetComponent<TransformComponent>()->setPosition(newPosition);
			}
		}
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
				float imageSize = rigidbody->axisAlignedCorners.bottomLeft.y - rigidbody->GetGameobject()->GetComponent<TransformComponent>()->getPosition().y;

				sf::Vector2f newPosition = sf::Vector2f(rigidbody->GetGameobject()->GetComponent<TransformComponent>()->getPosition().x, windowHeight - imageSize);

				rigidbody->GetGameobject()->GetComponent<TransformComponent>()->setPosition(newPosition);
			}
		}
	}

	
}

void PhysicsManager::OnNewGameobjectCreated(IEventDataPtr _event)
{
	std::shared_ptr<EvtData_On_GO_Created> pCastEventData = std::static_pointer_cast<EvtData_On_GO_Created>(_event);
	Gameobject* GO = pCastEventData->GetOwnedGameobject();

	if (GO->GetComponent<RigidbodyComponent>() != nullptr)
	{
		AddRigidbody(GO->GetComponent<RigidbodyComponent>());
	}
}

void PhysicsManager::RemoveRigidbodies(IEventDataPtr _event)
{
	rigidbodyList.clear();
}
