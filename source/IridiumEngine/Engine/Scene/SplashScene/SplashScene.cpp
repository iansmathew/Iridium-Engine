#include "SplashScene.h"
#include "../SceneManager.h"
#include "../TestScene/TestScene.h"

SplashScene::SplashScene()
{
}

void SplashScene::Start()
{
	this->GetComponent<RigidbodyComponent>()->enabled = false;
	//Add image
	Gameobject* splashImage = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, this);
	splashImage->GetComponent<RenderComponent>()->SetTexture("../../assets/engine/images/splashImage.png");
	splashImage->GetComponent<RenderComponent>()->SetIsRendered(false);

	//Gameobject* testObj = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, splashImage);
	//testObj->GetComponent<RenderComponent>()->SetTexture("../../assets/engine/images/splashImage.png");
	//testObj->GetComponent<TransformComponent>()->move(300, 0);

	////Add background music
	//GetMusicComponent()->AddMusicClip("bgMusic", "../../assets/splash_scene/splashSceneBgMusic.wav");
	//GetMusicComponent()->PlayMusic("bgMusic");

	//elapsedTime = 0.f;

	__super::Start();
}

void SplashScene::Update(float _deltaTime)
{
	//If time up, switch scenes
	//if (elapsedTime > 5.f)
	//{
	//	auto newScene = SceneManager::Instance()->CreateNewScene<TestScene>();
	//	SceneManager::Instance()->LoadScene(newScene);
	//}

	//elapsedTime += _deltaTime;

	//Call base update on end
	__super::Update(_deltaTime);
}

void SplashScene::Shutdown()
{
	__super::Shutdown();
}

