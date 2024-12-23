#include "SplashScene.h"
#include "SceneManager.h"

USING_NS_CC;

bool SplashScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	establishBackground();
	SceneManager::deferredRunScene(ESceneType::MainMenuScene, delaySwapScene, this);

	return true;
}

void SplashScene::establishBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* splashsceneSprite = Sprite::create("image/SplashScreen.png");
	splashsceneSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(splashsceneSprite, 0);
}
