#include "TestScene.h"
#include <string>
#include "../SceneManager.h"

TestScene::TestScene()
{

}

void TestScene::Start()
{
	this->GetRigidbodyComponent()->enabled = false;

	crashGo = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, this);
	crashGo->name = "Crash";
	crashGo->GetRenderComponent()->SetTexture("../../assets/engine/images/splashImage.png");
	crashGo->GetAudioComponent()->AddSoundClip("spaceSound", "../../assets/engine/sounds/testSound.wav");

	Gameobject* testSprite = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, this);
	testSprite->name = "Splash";
	testSprite->GetRenderComponent()->SetTexture("../../assets/engine/images/splashImage.png");
	testSprite->GetTransformComponent()->move(150, 0);

	//Call base
	__super::Start();
}

void TestScene::Update(float _deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		crashGo->GetRigidbodyComponent()->AddForce(-150, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		crashGo->GetRigidbodyComponent()->AddForce(150, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		crashGo->GetRigidbodyComponent()->AddForce(0.0f, -150);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		crashGo->GetRigidbodyComponent()->AddForce(0.0f, 150);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		crashGo->GetAudioComponent()->PlaySound("spaceSound");
	}



	__super::Update(_deltaTime);
}

void TestScene::Shutdown()
{
	__super::Shutdown();
}
