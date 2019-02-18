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

	Gameobject* testSprite = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, crashGo);
	testSprite->name = "Splash";
	testSprite->GetRenderComponent()->SetTexture("../../assets/engine/images/splashImage.png");
	testSprite->GetTransformComponent()->move(300, 300);

	//Call base
	__super::Start();
}

void TestScene::Update(float _deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		crashGo->GetTransformComponent()->move(-150 *_deltaTime, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		crashGo->GetTransformComponent()->move(150 * _deltaTime, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		crashGo->GetTransformComponent()->move(0.0f, -150 * _deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		crashGo->GetTransformComponent()->move(0.0f, 150 * _deltaTime);
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
