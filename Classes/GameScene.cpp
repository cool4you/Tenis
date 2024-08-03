#include "GameScene.h"
#include "Definition.h"
#include <CCEventListenerKeyboard.h>

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0.f, 0.f));
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("background.jpg");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	this->addChild(background, -1);

	Start.createLevel(this, ELevel::DEFAULT);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_1(GameScene::keyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_1(GameScene::keyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	return true;
}

void GameScene::keyPressed(EventKeyboard::KeyCode keyCode) 
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		Start.moveBoard(EMoveDirection::MOVE_LEFT);
		Start.moveBall(EMoveDirection::MOVE_LEFT);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		Start.moveBoard(EMoveDirection::MOVE_RIGHT);
		Start.moveBall(EMoveDirection::MOVE_RIGHT);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		Start.moveBall(EMoveDirection::START);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_SHIFT)
	{

	}
}

void GameScene::keyReleased(EventKeyboard::KeyCode keyCode) 
{
	if (keyCode != EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode != EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		Start.moveBoard(EMoveDirection::STOP);
		Start.moveBall(EMoveDirection::STOP);
	}
}

void GameScene::update(float delta)
{
	Scene::update(delta);

	//CCLOG("Position %p : %f", Start.board.getBoardNode(),Start.board.getBoardNode()->getPositionX());
}