#pragma once

#include "cocos2d.h"
#include "Ball.h"
#include "Board.h"
#include "Blocks.h"
#include <CCEventListenerKeyboard.h>
#include <vector>

enum class ELevel
{
	DEFAULT,
	NEXT_LEVEL
};

enum class EMoveDirection
{
	STOP,
	MOVE_LEFT,
	MOVE_RIGHT
};

class GameSceneManager
{
public:
	void createLevel(cocos2d::Scene* scene, ELevel level);
	void moveBoard(EMoveDirection moveDirection);

private:
	Board board;
};
