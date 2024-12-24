#include "GameScene.h"
#include "SceneManager.h"
#include "ui/CocosGUI.h"
#include "AudioManager.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0.f, 0.f));
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	establishBackground();
	gameStart.startGame(this);

	AudioManager::playMusic(ESoundType::GameMusic, true);

	return true;
}

void GameScene::onExit()
{
	gameStart.removeEventListeners();
	Scene::onExit();
}

void GameScene::establishBackground()
{
	Sprite* background = Sprite::create("image/background.jpg");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	this->addChild(background, -1);

	cocos2d::ui::Button* button = cocos2d::ui::Button::create("image/sound_on.png", "image/sound_off.png");
	button->setAnchorPoint(Vec2(0.f, 0.f));
	button->setPosition(Vec2(origin.x + button->getContentSize().width / 2, origin.y + button->getContentSize().height / 2));
	button->loadTextureNormal(AudioManager::getIsMuted() ? "image/sound_off.png" : "image/sound_on.png");

	button->addClickEventListener([button](Ref* sender)
		{
			bool isSoundEnabled = !AudioManager::getIsMuted();
			AudioManager::setIsMuted(isSoundEnabled);
			button->loadTextureNormal(isSoundEnabled ? "image/sound_off.png" : "image/sound_on.png");
		});

	this->addChild(button);
}