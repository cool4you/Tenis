#include "GameScene.h"
#include "GameSceneManager.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();  // Создаем сцену с физическим миром
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  // Опционально: установим режим отладки для отображения границ физических тел
	auto layer = GameScene::create();  // Создаем слой с игровым контентом
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

	auto backgroundField = Sprite::create("backgroundField.jpg");
	backgroundField->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 50));
	backgroundField->setContentSize(Size(1200, 800));
	auto physicsBody = PhysicsBody::createEdgeBox(Size(1200, 800), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(0x000001);
	physicsBody->setContactTestBitmask(true);
	backgroundField->addComponent(physicsBody);
	this->addChild(backgroundField, -1);

	Start.createLevel(this, ELevel::DEFAULT);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_1(GameScene::keyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_1(GameScene::keyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();

	return true;
}

void GameScene::keyPressed(EventKeyboard::KeyCode keyCode) 
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		Start.moveBoard(EMoveDirection::MOVE_LEFT);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		Start.moveBoard(EMoveDirection::MOVE_RIGHT);
	}
}

void GameScene::keyReleased(EventKeyboard::KeyCode keyCode) 
{
	if (keyCode != EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode != EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		Start.moveBoard(EMoveDirection::STOP);
	}
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((0x000001 == a->getCollisionBitmask() && 0x000002 == b->getCollisionBitmask()) || (0x000001 == b->getCollisionBitmask() && 0x000002 == a->getCollisionBitmask()))
	{
		Start.moveBoard(EMoveDirection::STOP);
	}
	return true;
}
