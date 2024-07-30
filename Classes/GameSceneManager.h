#pragma once

#include "cocos2d.h"
#include "Ball.h"
#include "Board.h"
#include "Blocks.h"
#include <CCEventListenerKeyboard.h>
#include <vector>
#include <math.h>
#include <map>

enum class ELevel
{
	DEFAULT,
	NEXT_LEVEL
};

enum class EMoveDirection
{
	STOP,
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

	Board board;
	Ball ball;

};
