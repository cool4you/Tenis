#include "GameSceneManager.h"
#include "Definition.h"

USING_NS_CC;

void GameSceneManager::createLevel(Scene* scene, ELevel level)
{
	if (level == ELevel::DEFAULT)
	{
		board.initialize(scene, EBoardType::STOCK);
        ball.initialize(scene, EBallUpgrade::DEFAULT);
	}


    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundField = Sprite::create("backgroundField.jpg");
    backgroundField->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 25.f));
    backgroundField->setContentSize(Size(300, 550));
    auto physicsBody = PhysicsBody::createEdgeBox(Size(300, 550), PhysicsMaterial(0.f, 0.f, 0.f));
    physicsBody->setDynamic(false);
    physicsBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    physicsBody->setContactTestBitmask(true);
    backgroundField->addComponent(physicsBody);
    scene->addChild(backgroundField, -1);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameSceneManager::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, scene);
}

void GameSceneManager::moveBoard(EMoveDirection moveDirection)
{
    switch (moveDirection)
    {
    case EMoveDirection::MOVE_LEFT:
        if ((int)board.getBoardNode()->getPositionX() - (board.getBoardSprite()->getContentSize().width*board.getBoardSize()) / 2 > 0)
        {
            board.setBoardVelocity(-(int)EVelocityMultiplier::ONE_TIME);
        }
        break;
    case EMoveDirection::MOVE_RIGHT:
        if (ceil(board.getBoardNode()->getPositionX()) + (board.getBoardSprite()->getContentSize().width * board.getBoardSize()) / 2 < visibleSize.width) // ceil для округления значение к большему из флоат
        {
            board.setBoardVelocity((int)EVelocityMultiplier::ONE_TIME);
        }
        break;
    case EMoveDirection::STOP:
        board.setBoardVelocity((int)EVelocityMultiplier::ZERO);
        break;
    case EMoveDirection::START:
        board.resizeBoard(board.getBoardSize() + 1);
        break;
    }
}

void GameSceneManager::moveBall(EMoveDirection moveDirection)
{
    switch (moveDirection)
    {
    case EMoveDirection::STOP:
        ball.setVelocity(0);
        break;
    case EMoveDirection::MOVE_LEFT:
        break;
    case EMoveDirection::MOVE_RIGHT:
        break;
    case EMoveDirection::START:
        ball.setVelocity(1);
        break;
    default:
        break;
    }
}

bool GameSceneManager::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    if ((OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask() && BOARD_COLLISION_BITMASK == b->getCollisionBitmask()) || (OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() && BOARD_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        moveBoard(EMoveDirection::STOP);

        if ((int)board.getBoardNode()->getPositionX() - (board.getBoardSprite()->getContentSize().width * board.getBoardSize()) / 2 < 0)
        {
            board.setBoardPosition(Vec2((board.getBoardSprite()->getContentSize().width * board.getBoardSize()) / 2, board.getBoardNode()->getPositionY()));
        }
        else if (ceil(board.getBoardNode()->getPositionX()) + (board.getBoardSprite()->getContentSize().width * board.getBoardSize()) / 2 > visibleSize.width)
        {
            board.setBoardPosition(Vec2(visibleSize.width - (board.getBoardSprite()->getContentSize().width * board.getBoardSize()) / 2, board.getBoardNode()->getPositionY()));
        }
    }

    return true;
}