#ifndef __GAMESCENEMANAGER_H__
#define __GAMESCENEMANAGER_H__

#include "cocos2d.h"
#include "Ball.h"
#include "Board.h"
#include "Blocks.h"
#include <CCEventListenerKeyboard.h>

class GameSceneManager
{
public:
    static void createBall(cocos2d::Scene* scene);
    static void createBoard(cocos2d::Scene* scene);
    static void createBlocks(cocos2d::Scene* scene);

    static void setMoveValue(const int value);

private:

    static int moveValue;
    
};

#endif // __GAMESCENEMANAGER_H__
