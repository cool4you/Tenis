#include "SceneManager.h"
#include "SplashScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "LeaderboardScene.h"
#include "TutorialScene.h"
#include "AudioManager.h"

USING_NS_CC;

void SceneManager::runScene(const ESceneType sceneType)
{
	Scene* scene = nullptr;

	AudioManager::stopAll();

	switch (sceneType)
	{
		case ESceneType::SplashScene: scene = SplashScene::create(); break;
		case ESceneType::MainMenuScene: scene = MainMenuScene::create(); break;
		case ESceneType::GameScene: scene = GameScene::createScene(); break;
		case ESceneType::GameOverScene: scene = GameOverScene::create(); break;
		case ESceneType::LeaderboardScene: scene = LeaderboardScene::create(); break;
		case ESceneType::TutorialScene: scene = TutorialScene::create(); break;
		default: break;
	}

	if (scene)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
	}
}

void SceneManager::deferredRunScene(const ESceneType sceneType,const float delay,void* target)
{
	Director::getInstance()->getScheduler()->schedule([=](float dt) {
		SceneManager::runScene(sceneType);
		}, target, delay, false, "deferredRunKey");
}