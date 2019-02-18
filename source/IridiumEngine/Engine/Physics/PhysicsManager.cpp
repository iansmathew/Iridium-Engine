#include "PhysicsManager.h"
#include "../Window/WindowManager.h"
#include <iostream>

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

void PhysicsManager::CollisionResolution()
{
	for (int rigidbodyAIndex = 0; rigidbodyAIndex < rigidbodyList.size(); rigidbodyAIndex++)
	{
		RigidbodyComponent* rigidbodyA = rigidbodyList[rigidbodyAIndex];
		for (int rigidbodyBIndex = rigidbodyAIndex; rigidbodyBIndex < rigidbodyList.size(); rigidbodyBIndex++)
		{
			RigidbodyComponent* rigidbodyB = rigidbodyList[rigidbodyBIndex];
			if (rigidbodyA != rigidbodyB)
			{
				if (OverlapTest(rigidbodyA,rigidbodyB))
				{
					std::cout << "Collision" << std::endl;
				}
			}
		}
	}
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
