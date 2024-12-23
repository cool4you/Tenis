#include "GameplayCore.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "SaveManager.h"
#include "AudioManager.h"

USING_NS_CC;

namespace
{
	const int OBSTACLE_COLLISION_BITMASK = 0x000001;
	const int BALL_COLLISION_BITMASK = 0x000002;
	const int BOARD_COLLISION_BITMASK = 0x000003;
	const int BLOCKS_COLLISION_BITMASK = 0x000004;
	const int BOOST_COLLISION_BITMASK = 0x000000;
}

void GameplayCore::startGame(Scene* scene)
{
	this->scene = scene;

	uiManager.createInfoPanel(gameLevel, life, maxLife, isLifeFreez, scene);
	levelManager.createLevel(gameLevel, scene);

	SetupEventListeners();
}

void GameplayCore::SetupEventListeners()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameplayCore::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, scene);

	auto contactSeparateListener = EventListenerPhysicsContact::create();
	contactSeparateListener->onContactSeparate = CC_CALLBACK_1(GameplayCore::onContactSeparate, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactSeparateListener, scene);

	auto contactPreSolveListener = EventListenerPhysicsContact::create();
	contactPreSolveListener->onContactPreSolve = CC_CALLBACK_2(GameplayCore::onContactPreSolve, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactPreSolveListener, scene);

	auto contactPostSolveListener = EventListenerPhysicsContact::create();
	contactPostSolveListener->onContactPostSolve = CC_CALLBACK_2(GameplayCore::onContactPostSolve, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactPostSolveListener, scene);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_1(GameplayCore::keyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_1(GameplayCore::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, scene);

	listeners = { contactListener ,contactSeparateListener ,contactPreSolveListener ,contactPostSolveListener ,listener };
}

void GameplayCore::removeEventListeners()
{
	for (auto listener : listeners)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	}
}

bool GameplayCore::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();


	if ((a->getCollisionBitmask() == BOOST_COLLISION_BITMASK &&
		 b->getCollisionBitmask() == BOARD_COLLISION_BITMASK) ||
		(b->getCollisionBitmask() == BOOST_COLLISION_BITMASK &&
		 a->getCollisionBitmask() == BOARD_COLLISION_BITMASK))
	{
		Node* boostNode = (a->getCollisionBitmask() == BOOST_COLLISION_BITMASK) ? a->getNode() : b->getNode();
		levelManager.applyBoostEffect(levelManager.getBoost().getBoostType(),life,maxLife,isLifeFreez);
		uiManager.redrawLifePanel(life, maxLife, isLifeFreez);
		levelManager.removeBoost(boostNode);
	}

	if ((a->getCollisionBitmask() == BOOST_COLLISION_BITMASK &&
		 b->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK) ||
		(b->getCollisionBitmask() == BOOST_COLLISION_BITMASK &&
		 a->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK))
	{
		Node* boostNode = (a->getCollisionBitmask() == BOOST_COLLISION_BITMASK) ? a->getNode() : b->getNode();
		levelManager.removeBoost(boostNode);
	}

	// Check collision between obstacle && board
	if ((a->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK &&
		 b->getCollisionBitmask() == BOARD_COLLISION_BITMASK) ||
		(b->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK &&
		 a->getCollisionBitmask() == BOARD_COLLISION_BITMASK))
	{
		levelManager.getBoard().setBoardVelocity(Vec2::ZERO);

		if (!isBallMove)
		{
			levelManager.getBall().setBallVelocity(Vec2::ZERO);
		}
	}

	// Check collision between blocks && ball
	if ((a->getCollisionBitmask() == BLOCKS_COLLISION_BITMASK &&
		 b->getCollisionBitmask() == BALL_COLLISION_BITMASK) ||
		(b->getCollisionBitmask() == BLOCKS_COLLISION_BITMASK &&
		 a->getCollisionBitmask() == BALL_COLLISION_BITMASK))
	{

		//AudioManager::playMusic("audio/ball_hit.mp3", false, 1.0f);

		Node* blockNode = (a->getCollisionBitmask() == BLOCKS_COLLISION_BITMASK) ? a->getNode() : b->getNode();

		if ((levelManager.getBlock(blockNode)->getCurrentBlockHP() - levelManager.getBall().getBallDamage()) <= 0)
		{
			int blockHP = levelManager.getBlock(blockNode)->getDefaultBlockHP();
			int ballDamage = levelManager.getBall().getBallDamage();
			gameScore += blockHP * ballDamage * 10;
			uiManager.updateScore(gameScore);
			levelManager.removeBlock(blockNode, isLevelComplete);
		}
		else
		{
			levelManager.getBlock(blockNode)->changeHP(levelManager.getBall().getBallDamage());
		}
	}

	// Check collision between board && ball
	if ((a->getCollisionBitmask() == BOARD_COLLISION_BITMASK &&
		 b->getCollisionBitmask() == BALL_COLLISION_BITMASK) ||
		(b->getCollisionBitmask() == BOARD_COLLISION_BITMASK &&
		 a->getCollisionBitmask() == BALL_COLLISION_BITMASK))
	{

		//AudioManager::playMusic("audio/ball_obs.mp3", false, 1.0f);

		auto ballBody = (a->getCollisionBitmask() == BALL_COLLISION_BITMASK ? a : b);

		auto velocity = ballBody->getVelocity();

		Vec2 ballPosition = levelManager.getBall().getBallPosition();
		Vec2 boardPosition = levelManager.getBoard().getBoardPosition();

		if (ballPosition.x > boardPosition.x)
		{
			if (std::abs(velocity.x) <= 10.f)
			{
				velocity.x = std::abs(velocity.y) / 2;
			}
		}
		else if (ballPosition.x < boardPosition.x)
		{
			if (std::abs(velocity.x) <= 10.f)
			{
				velocity.x = -std::abs(velocity.y) / 2;
			}
		}

		levelManager.getBall().setBallVelocity(Vec2(velocity.x, -std::abs(velocity.y)));

		if (levelManager.getBoard().getBoardType() == EBoardType::STICKYBOARD)
		{
			levelManager.getBall().setBallVelocity(Vec2::ZERO);
			isBallMove = false;
		}
	}

	// Check collision between obstacle && ball
	if ((a->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK &&
		 b->getCollisionBitmask() == BALL_COLLISION_BITMASK) ||
		(b->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK &&
		 a->getCollisionBitmask() == BALL_COLLISION_BITMASK))
	{
		//AudioManager::playMusic("audio/ball_obs.mp3", false, 1.0f);

		if (levelManager.getBall().getBallPosition().y < levelManager.getBoard().getBoardPosition().y)
		{
			levelManager.getBall().setBallVelocity(Vec2::ZERO);

			Director::getInstance()->getScheduler()->schedule([=](float)
				{
					levelManager.getBall().setBallPosition(Vec2(levelManager.getBoard().getBoardPosition().x,
																levelManager.getBoard().getBoardPosition().y + levelManager.getBall().getBallContentSize().height));
					isBallMove = false;
				}, this, 0, 0, 0, false, "changePosition");
			
			if (!isLifeFreez)
			{
				--life;
				uiManager.redrawLifePanel(life, maxLife, isLifeFreez);
			}

			if (life <= 0)
			{
				isGameFinish = true;
			}
		}

		if (isGameFinish)
		{
			SaveManager::saveResultToFile(gameLevel, gameScore);
			SceneManager::runScene(ESceneType::GameOverScene);
		}
	}

	return true;
}

void GameplayCore::onContactSeparate(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	// Check collision between blocks && ball
	if ((a->getCollisionBitmask() == BLOCKS_COLLISION_BITMASK &&
		b->getCollisionBitmask() == BALL_COLLISION_BITMASK) ||
		(b->getCollisionBitmask() == BLOCKS_COLLISION_BITMASK &&
		a->getCollisionBitmask() == BALL_COLLISION_BITMASK))
	{
		if (isLevelComplete)
		{
			isLifeFreez = false;
			levelManager.getBall().setBallVelocity(Vec2::ZERO);
			isBallMove = false;
			++gameLevel;
			levelManager.createLevel(gameLevel, scene);
			isLevelComplete = false;
			uiManager.updateLevelInfo(gameLevel);
			uiManager.redrawLifePanel(life,maxLife,isLifeFreez);
		}
	}
}

bool GameplayCore::onContactPreSolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& preSolve)
{

	auto shapeA = contact.getShapeA()->getBody();
	auto shapeB = contact.getShapeB()->getBody();

	if ((shapeA->getCollisionBitmask() == BOARD_COLLISION_BITMASK &&
		 shapeB->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK) ||
		(shapeB->getCollisionBitmask() == BOARD_COLLISION_BITMASK &&
		 shapeA->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK))
	{
		levelManager.getBoard().setBoardVelocity(Vec2::ZERO);

		if (!isBallMove)
		{
			levelManager.getBall().setBallVelocity(Vec2::ZERO);
		}

		Vec2 boardPosition = levelManager.getBoard().getBoardPosition();
		auto boardSize = levelManager.getBoard().getBoardNode()->getContentSize();
		float leftBoundary = 0.0f;
		float rightBoundary = Director::getInstance()->getVisibleSize().width;

		if (boardPosition.x - boardSize.width / 2 < leftBoundary)
		{
			boardPosition.x = leftBoundary + boardSize.width / 2;
		}
		else if (boardPosition.x + boardSize.width / 2 > rightBoundary)
		{
			boardPosition.x = rightBoundary - boardSize.width / 2;
		}

		levelManager.getBoard().setBoardPosition(boardPosition);

		return false;
	}

	return true;
}

bool GameplayCore::onContactPostSolve(cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& postSolve)
{
	auto shapeA = contact.getShapeA()->getBody();
	auto shapeB = contact.getShapeB()->getBody();

	return true;
}

void GameplayCore::keyPressed(EventKeyboard::KeyCode keyCode)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		if (leftBoardMove)
		{
			levelManager.getBoard().setBoardVelocity(-boardSpeed);
			if (!isBallMove)
			{
				levelManager.getBall().setBallVelocity(-boardSpeed);
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		if (rightBoardMove)
		{
			levelManager.getBoard().setBoardVelocity(boardSpeed);
			if (!isBallMove)
			{
				levelManager.getBall().setBallVelocity(boardSpeed);
			}
		}
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (!isBallMove)
		{
			isBallMove = true;
			levelManager.getBall().setBallVelocity(ballSpeed * gameLevel);
		}
	}
}

void GameplayCore::keyReleased(EventKeyboard::KeyCode keyCode)
{
	if (keyCode != EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode != EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		levelManager.getBoard().setBoardVelocity(Vec2::ZERO);
		if (!isBallMove)
		{
			levelManager.getBall().setBallVelocity(Vec2::ZERO);
		}
	}
}