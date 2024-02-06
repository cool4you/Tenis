#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definition.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
	return SplashScene::create();
}

bool SplashScene::init()
{
	
	if (!Scene::init())
	{
		return false;
	}

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->schedule(CC_SCHEDULE_SELECTOR(SplashScene::GoToMainMenu), DISPLAY_TIME_SLASH_SCENE);

	cocos2d::Sprite* splashsceneSprite = Sprite::create("SplashScreen.png");
	splashsceneSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(splashsceneSprite, 0);

	return true;
}

void SplashScene::GoToMainMenu(float dt)
{
	cocos2d::Scene* scene = MainMenuScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(TRANSITION_TIME, scene));	
}


