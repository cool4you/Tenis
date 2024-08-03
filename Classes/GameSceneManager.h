#pragma once

#include "cocos2d.h"
#include "Ball.h"
#include "Board.h"
#include "Blocks.h"

enum class ELevel
{
	DEFAULT,
	NEXT_LEVEL
};

enum class EMoveDirection
{
	STOP,
	STOP2,
	MOVE_LEFT,
	MOVE_RIGHT,
	START
};

enum class EVelocityMultiplier
{
	ZERO,
	ONE_TIME = 1,
	TWO_TIME = 2
};


class GameSceneManager
{
public:
	void createLevel(cocos2d::Scene* scene, ELevel level);
	void moveBoard(EMoveDirection moveDirection);
	void moveBall(EMoveDirection moveDirection);
	bool onContactBegin(cocos2d::PhysicsContact& contact);

private:
	cocos2d::Size visibleSize;
	void updateScore(int points);
	void infoPanel(cocos2d::Scene* scene);
	int score = 0;
	cocos2d::Label* scoreLabel;
	cocos2d::Node* lifeNode;
	cocos2d::Sprite* lifeSprite;
	bool levelStarted = false;

	Board board;
	Ball ball;
	Block blocks;
};
