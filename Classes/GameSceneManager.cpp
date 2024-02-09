#include "GameSceneManager.h"

USING_NS_CC;

void GameSceneManager::createLevel(Scene* scene, ELevel level)
{
	if (level == ELevel::DEFAULT)
	{
		board.initialize(scene, EBoardType::STOCK);
	}
}

void GameSceneManager::moveBoard(EMoveDirection moveDirection)
{
	if (moveDirection == EMoveDirection::MOVE_LEFT)
	{
		int value = -1;
		board.setBoardVelocity(value);
	}
	else if (moveDirection == EMoveDirection::MOVE_RIGTH)
	{
		int value = 1;
		board.setBoardVelocity(value);
	}
	else if (moveDirection == EMoveDirection::STOP)
	{
		int value = 0;
		board.setBoardVelocity(value);
	}
}
