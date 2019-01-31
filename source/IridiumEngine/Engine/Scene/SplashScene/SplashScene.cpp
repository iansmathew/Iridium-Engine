#include "SplashScene.h"
#include "../SceneManager.h"

SplashScene::SplashScene()
{
}

void SplashScene::Start()
{
	auto splashImage = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, this);
	splashImage->GetRenderComponent()->SetTexture("../../assets/engine/images/splashImage.png");

	__super::Start();
}

void SplashScene::Update(float _deltaTime)
{

	//Timer here. Do not make a loop The update function IS a loop. Clock can restart at the end of update before _super::update

	//On timer end call 
	/*auto newScene = SceneManager::Instance()->CreateNewScene<TestScene>();
	SceneManager::Instance()->LoadScene(newScene);*/

	//Call base update on end
	__super::Update(_deltaTime);
}

void SplashScene::Shutdown()
{
	//TODO: iMPLEMENT PROPER SHUTDOWN IN BASE
}

