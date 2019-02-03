#include "SplashScene.h"
#include "../SceneManager.h"

SplashScene::SplashScene()
{
}

void SplashScene::Start()
{
	//Add image
	auto splashImage = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, this);
	splashImage->GetRenderComponent()->SetTexture("../../assets/engine/images/splashImage.png");

	//Add background music
	GetMusicComponent()->AddMusicClip("bgMusic", "../../assets/splash_scene/splashSceneBgMusic.wav");
	GetMusicComponent()->PlayMusic("bgMusic");

	elapsedTime = 0.f;

	__super::Start();
}

void SplashScene::Update(float _deltaTime)
{
	//If time up, switch scenes
	if (elapsedTime > 2.f)
	{
		auto newScene = SceneManager::Instance()->CreateNewScene<TestScene>();
		SceneManager::Instance()->LoadScene(newScene);
	}

	elapsedTime += _deltaTime;

	//Call base update on end
	__super::Update(_deltaTime);
}

void SplashScene::Shutdown()
{
	__super::Shutdown();
}

