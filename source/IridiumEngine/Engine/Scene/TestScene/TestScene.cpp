#include "TestScene.h"
#include "../SceneManager.h"

TestScene::TestScene()
{

}

void TestScene::Start()
{
	crashGo = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, this);
	crashGo->GetRenderComponent()->SetTexture("../../assets/test_scene/crashTestSprite.png");
	crashGo->GetAudioComponent()->AddSoundClip("spaceSound", "../../assets/engine/sounds/testSound.wav");

	Gameobject* testSprite = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, crashGo);
	testSprite->GetRenderComponent()->SetTexture("../../assets/engine/images/splashImage.png");
	testSprite->GetTransformComponent()->move(150, 0);

	//Call base
	__super::Start();
}

void TestScene::Update(float _deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		crashGo->GetTransformComponent()->move(-100 * _deltaTime, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		crashGo->GetTransformComponent()->move(100 * _deltaTime, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		crashGo->GetTransformComponent()->move(0.0f, -100 * _deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		crashGo->GetTransformComponent()->move(0.0f, 100 * _deltaTime);
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
