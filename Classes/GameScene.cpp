#include "GameScene.h"
#include "GameSceneManager.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();  // Создаем сцену с физическим миром
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  // Опционально: установим режим отладки для отображения границ физических тел
	auto layer = GameScene::create();  // Создаем ваш слой с игровым контентом
	scene->addChild(layer);  // Добавляем слой к сцене

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
	physicsBody->setContactTestBitmask(0x000001);
	backgroundField->addComponent(physicsBody);
	this->addChild(backgroundField, -1);

	//GameSceneManager::createBall(this);
	GameSceneManager::createBoard(this);
	//GameSceneManager::createBlocks(this);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_1(GameScene::keyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_1(GameScene::keyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	return true;
}
void GameScene::update(float delta) 
{
	GameSceneManager::setMoveValue(move);
}


void GameScene::keyPressed(EventKeyboard::KeyCode keyCode) 
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		isKeyPressed = true;
		move = -100;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		isKeyPressed = true;
		move = 100;
	}
}

void GameScene::keyReleased(EventKeyboard::KeyCode keyCode) 
{
	if (keyCode != EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode != EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		isKeyPressed = false;
	} 
}