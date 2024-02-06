#include "GameSceneManager.h"

USING_NS_CC;

void GameSceneManager::createBall(Scene* scene)
{
    Ball* ball = Ball::createBall("defaultBall.png");
    ball->setPosition(Vec2(240, 160));  // Начальные координаты мяча
    scene->addChild(ball);
}



void GameSceneManager::createBoard(Scene* scene)
{  
    Board* board = Board::createBoard("boardStock.png");
    board->setPosition(Vec2(600, 125));
    
    auto boardBody = PhysicsBody::createBox(board->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    boardBody->setDynamic(false);  
    boardBody->setContactTestBitmask(0x000002);  
    boardBody->setVelocity(Vec2(0 + moveValue, 0));
    board->setPhysicsBody(boardBody);
    
    board->getBoardSize();
    
    scene->addChild(board);

    for (int i = 0; i < board->getBoardSize(); ++i)
    {
        Sprite* blockBoard = Sprite::create("boardStock.png");
        blockBoard->setPosition(Vec2(board->getContentSize().width * (i+1) +25, board->getContentSize().height / 2)); // +25 погрнешность размера блока , так как якорь стоит по середине

        auto blockBody = PhysicsBody::createBox(blockBoard->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
        blockBody->setDynamic(false);  
        blockBody->setContactTestBitmask(0x000002);  
        blockBoard->setPhysicsBody(blockBody);
        
        board->addChild(blockBoard);
    }
}

void GameSceneManager::createBlocks(Scene* scene)
{
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            Block* block = Block::createBlock("defaultBlock.png");
            float x = (i + 1) * 2.f;
            float y = 200 - (j + 1) * 40.0f;
            block->setPosition(Vec2(x, y));
            scene->addChild(block);
        }
    }
}

void GameSceneManager::setMoveValue(const int value)
{
    moveValue = value;
 
}



