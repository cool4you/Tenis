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
    switch (moveDirection)
    {
    case EMoveDirection::MOVE_LEFT:
        board.setBoardVelocity(-1);
        break;
    case EMoveDirection::MOVE_RIGHT:
        board.setBoardVelocity(1);
        break;
    case EMoveDirection::STOP:
        board.setBoardVelocity(0);
        break;
    }
}
