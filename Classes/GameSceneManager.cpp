#include "GameSceneManager.h"
#include "GameOverScene.h"
#include "Definition.h"
#include <CCEventListenerKeyboard.h>
#include <math.h>

USING_NS_CC;

void GameSceneManager::createLevel(Scene* scene, ELevel level)
{
	if (level == ELevel::DEFAULT)
	{
		board.initialize(scene, EBoardType::STOCK);
		ball.initialize(scene, EBallUpgrade::DEFAULT);
		blocks.initialize(scene, EBlocksType::DEFAULT);
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundField = Sprite::create("backgroundField.jpg");
	backgroundField->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 - 25.f));
	backgroundField->setContentSize(Size(visibleSize.width, visibleSize.height - 50.f));
	auto physicsBody = PhysicsBody::createEdgeBox(Size(300, 550), PhysicsMaterial(0.f, 1.f, 0.f));
	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	physicsBody->setContactTestBitmask(true);
	backgroundField->addComponent(physicsBody);
	scene->addChild(backgroundField, -1);

	infoPanel(scene);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameSceneManager::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, scene);
}

void GameSceneManager::moveBoard(EMoveDirection moveDirection)
{
	switch (moveDirection)
	{
	case EMoveDirection::MOVE_LEFT:
		if ((int)board.getBoardNode()->getPositionX() - (board.getBoardSprite()->getContentSize().width * board.getBoardSize()) / 2 > 0)
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
	default:
		break;
	}
}

void GameSceneManager::moveBall(EMoveDirection moveDirection)
{
	switch (moveDirection)
	{
	case EMoveDirection::STOP:
		if (!levelStarted)
		{
			ball.setVelocity(0, levelStarted);
			ball.setBallPosition(Vec2((int)board.getBoardNode()->getPositionX(), ball.getBallSprite()->getContentSize().height * 2));
		}

		break;
	case EMoveDirection::MOVE_LEFT:
		if (!levelStarted)
		{
			ball.setVelocity(-1, levelStarted);
		}
		break;
	case EMoveDirection::MOVE_RIGHT:
		if (!levelStarted)
		{
			ball.setVelocity(1, levelStarted);
		}
		break;
	case EMoveDirection::START:
	{
		levelStarted = true;
		ball.setVelocity(1, levelStarted);
		//ball.setBallPosition(Vec2(200.f,300.f));
	}
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
		moveBall(EMoveDirection::STOP);
		if ((int)board.getBoardNode()->getPositionX() - (board.getBoardSprite()->getContentSize().width * board.getBoardSize()) / 2 < 0)
		{
			board.setBoardPosition(Vec2((board.getBoardSprite()->getContentSize().width * board.getBoardSize()) / 2, board.getBoardNode()->getPositionY()));
		}
		else if (ceil(board.getBoardNode()->getPositionX()) + (board.getBoardSprite()->getContentSize().width * board.getBoardSize()) / 2 > visibleSize.width)
		{
			board.setBoardPosition(Vec2(visibleSize.width - (board.getBoardSprite()->getContentSize().width * board.getBoardSize()) / 2, board.getBoardNode()->getPositionY()));
		}
	}

	if ((BALL_COLLISION_BITMASK == a->getCollisionBitmask() && BOARD_COLLISION_BITMASK == b->getCollisionBitmask()) || (BALL_COLLISION_BITMASK == b->getCollisionBitmask() && BOARD_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		auto velocity = ball.getBallSprite()->getPhysicsBody()->getVelocity();
		if (ball.getBallSprite()->getPositionX() > board.getBoardNode()->getPositionX())
		{
			if (velocity.x == 0)
			{
				velocity.x = velocity.y / 2;
				ball.getBallSprite()->getPhysicsBody()->setVelocity(Vec2(abs(velocity.x), -velocity.y));
			}
		}
		else if (ball.getBallSprite()->getPositionX() < board.getBoardNode()->getPositionX())
		{
			if (velocity.x == 0)
			{
				velocity.x = velocity.y / 2;
				ball.getBallSprite()->getPhysicsBody()->setVelocity(Vec2(velocity.x, -velocity.y));
			}
		}
	}
	if ((a->getCollisionBitmask() == BLOCKS_COLLISION_BITMASK && b->getCollisionBitmask() == BALL_COLLISION_BITMASK) || (b->getCollisionBitmask() == BLOCKS_COLLISION_BITMASK && a->getCollisionBitmask() == BALL_COLLISION_BITMASK))
	{
		Node* blockNode = (a->getCollisionBitmask() == BLOCKS_COLLISION_BITMASK) ? a->getNode() : b->getNode();
		blocks.getBlockFieldNode()->removeChild(blockNode, true);

		updateScore(10);
	}
 	if ((BALL_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BALL_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		if (ball.getBallSprite()->getPositionY() < board.getBoardNode()->getPositionY())
		{
			levelStarted = false;
			moveBall(EMoveDirection::STOP);		
			//lifeNode->removeChild(lifeSprite);
		}
	}

	return true;
}

void GameSceneManager::updateScore(int points)
{
	score += points;
	scoreLabel->setString("Score: " + std::to_string(score));
}

void GameSceneManager::infoPanel(Scene* scene)
{
	lifeNode = Node::create();

	for (int i = 0; i < 3; i++)
	{
		lifeSprite = Sprite::create("hp.png");
		lifeSprite->setPosition(Vec2(lifeSprite->getContentSize().width * i, 0.f));
		lifeNode->setContentSize(Size(lifeSprite->getContentSize().width * 3, lifeSprite->getContentSize().height));
		lifeNode->setPosition(Vec2(visibleSize.width, visibleSize.height - 25.f));
		lifeNode->setAnchorPoint(Vec2(1.f, 0.f));
		lifeNode->addChild(lifeSprite);
	}
	scene->addChild(lifeNode, 1);

	scoreLabel = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 16);
	scoreLabel->setAnchorPoint(Vec2(0.f, 0.5f));
	scoreLabel->setPosition(Vec2(10.f, visibleSize.height - 25.f));

	scene->addChild(scoreLabel, 1);
}

