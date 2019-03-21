#include "TestScene.h"
#include <string>
#include "../SceneManager.h"
#include "../../Components/RigidbodyComponent.h"
#include "../../Components/AudioComponent.h"
#include "../../Components/RenderComponent.h"
#include "../../Components/TransformComponent.h"

TestScene::TestScene()
{

}

void TestScene::Start()
{

	crashGo = SceneManager::Instance()->CreateNewGameobject<Gameobject>(this);

	crashGo->name = "Crash";
	crashGo->AddComponent<RenderComponent>(crashGo);
	crashGo->GetComponent<RenderComponent>()->SetTexture("../../assets/test_scene/crashTestSprite.png");

	crashGo->AddComponent<RigidbodyComponent>(crashGo);
	
	
	auto crashAudio = crashGo->AddComponent<AudioComponent>(crashGo);
	//auto crashAudio = crashGo->GetComponent<AudioComponent>();
	crashAudio->AddSoundClip("spaceSound", "../../assets/engine/sounds/testSound.wav");
	crashAudio->PlaySound("spaceSound");
	
	Gameobject* testSprite = SceneManager::Instance()->CreateNewGameobject<Gameobject>(this);
	
	testSprite->name = "Splash";
	testSprite->AddComponent<RenderComponent>(crashGo)->SetTexture("../../assets/engine/images/splashImage.png");
	testSprite->GetComponent<TransformComponent>()->move(300, 300);
	
	////Call base
	__super::Start();
}

void TestScene::Update(float _deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		crashGo->GetComponent<RigidbodyComponent>()->AddForce(-150, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		crashGo->GetComponent<RigidbodyComponent>()->AddForce(150, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		crashGo->GetComponent<RigidbodyComponent>()->AddForce(0.0f, -150);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		crashGo->GetComponent<RigidbodyComponent>()->AddForce(0.0f, 150);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		auto autdo = crashGo->GetComponent<AudioComponent>();
 		autdo->PlaySound("spaceSound");
	}



	__super::Update(_deltaTime);
}

void TestScene::Shutdown()
{
	__super::Shutdown();
}
