#include "SplashScene.h"
#include "../SceneManager.h"
#include "../TestScene/TestScene.h"
#include "../../Components/RenderComponent.h"
#include "../../Components/RigidbodyComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Components/TrialComponent.h"
#include "../../Components/AudioComponent.h"
#include "../../Components/PyBehaviour.h"




SplashScene::SplashScene()
{
}

void SplashScene::Start()
{

	////Add image
	Gameobject* splashImage = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true);
	
	splashImage->AddComponent<RenderComponent>(splashImage);
	splashImage->GetComponent<RenderComponent>()->SetTexture("../../assets/test_scene/crashTestSprite.png");
	splashImage->GetComponent<RenderComponent>()->SetVisibility(true);




	Gameobject* testObj = SceneManager::Instance()->CreateNewGameobject<Gameobject>(this);
	testObj->AddComponent<RenderComponent>(testObj);
	testObj->GetComponent<RenderComponent>()->SetTexture("../../assets/engine/images/splashImage.png");
	testObj->GetComponent<RenderComponent>()->SetVisibility(true);
	testObj->GetTransform()->move(500, 200);

	//Add background music
	auto audioManagerGO = SceneManager::Instance()->CreateNewGameobject<Gameobject>(false);
	//auto musicComponent = audioManagerGO->AddComponent<MusicComponent>(audioManagerGO);
	audioManagerGO->AddComponent<PyBehaviour>("module1" , audioManagerGO);
	//musicComponent->AddMusicClip("bgMusic", "../../assets/splash_scene/splashSceneBgMusic.wav");
	//musicComponent->PlayMusic("bgMusic");

	elapsedTime = 0.f;

	//TODO: Save the scene here
	SceneManager::Instance()->SaveScene("SplashScene", this);

	splashImage->SerializeData("jsonString");

	__super::Start();
}

void SplashScene::Update(float _deltaTime)
{
	//If time up, switch scenes
	if (elapsedTime > 5.f)
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

