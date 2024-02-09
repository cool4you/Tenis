#include "Board.h"

USING_NS_CC;

Board::Board()
{
}

Board::~Board()
{

}

void Board::initialize(cocos2d::Scene* scene, EBoardType boardType, int _boardSize)
{
    board = Node::create();
    boardSize = _boardSize;

    for (int i = 0; i < boardSize; ++i)
    {
        std::string textureName = "";
        if (boardType == EBoardType::STOCK)
        {
            textureName = "boardStock.png";
        }
        else if (boardType == EBoardType::STICKY)
        {
            textureName = "boardSticky.png";
        }

        boardSprite = Sprite::create(textureName);
        boardSprite->setPosition(Vec2(boardSprite->getContentSize().width * i, 0.f));
        boardSprite->setAnchorPoint(Vec2(0, 0));
        board->addChild(boardSprite);
    }

    board->setContentSize(cocos2d::Size(boardSprite->getContentSize().width * boardSize, boardSprite->getContentSize().height));
    board->setAnchorPoint(Vec2(0.5, 0.5));
    board->setPosition(Vec2(600.f, 75.f));
    boardPhysicsBody = PhysicsBody::createBox(board->getContentSize());
    boardPhysicsBody->setDynamic(false);
    board->setPhysicsBody(boardPhysicsBody);

    scene->addChild(board);
}

int Board::getBoardSize() const
{
    return boardSize;
}

cocos2d::Vec2 Board::getBoardDefaultVelocity() const
{
    return boardDefaultVelocity;
}

cocos2d::Sprite* Board::getBoardSprite() const
{
    return boardSprite;
}

void Board::setBoardSize(int size)
{
    if (size <= boardMaxSize)
    {
        boardSize = boardMaxSize;
    }
}

void Board::setBoardVelocity(int value)
{
    boardPhysicsBody->setVelocity(boardDefaultVelocity*value);
}
