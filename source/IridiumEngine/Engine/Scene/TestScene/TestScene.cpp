#include "TestScene.h"
#include <string>
#include "../SceneManager.h"

TestScene::TestScene()
{

}

void TestScene::Start()
{
	this->GetComponent<RigidbodyComponent>()->enabled = false;

	crashGo = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, this);
	crashGo->name = "Crash";
	crashGo->GetComponent<RenderComponent>()->SetTexture("../../assets/engine/images/splashImage.png");
	crashGo->GetComponent<AudioComponent>()->AddSoundClip("spaceSound", "../../assets/engine/sounds/testSound.wav");

	Gameobject* testSprite = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, this);
	testSprite->name = "Splash";
	testSprite->GetComponent<RenderComponent>()->SetTexture("../../assets/engine/images/splashImage.png");
	testSprite->GetComponent<TransformComponent>()->move(300, 300);

	//Call base
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
		crashGo->GetComponent<AudioComponent>()->PlaySound("spaceSound");
	}



	__super::Update(_deltaTime);
}

void TestScene::Shutdown()
{
	__super::Shutdown();
}
