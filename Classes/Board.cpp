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
    board->setPosition(defaultPosition);
    setTextureBoard(boardType);

    scene->addChild(board);
}

void Board::setTextureBoard(EBoardType boardType)
{
    if (boardType == EBoardType::STOCK)
    {
        textureName = "boardStock.png";
    }
    else if (boardType == EBoardType::STICKY)
    {
        textureName = "boardSticky.png";
    }
    reDrawBoard();
}

void Board::createBoard()
{
    for (int i = 0; i < boardSize; ++i)
    {
        boardSprite = Sprite::create(textureName);
        boardSprite->setPosition(Vec2(boardSprite->getContentSize().width * i, 0.f));
        boardSprite->setAnchorPoint(Vec2(0, 0));
        board->addChild(boardSprite);
    }

    board->setContentSize(cocos2d::Size(boardSprite->getContentSize().width * boardSize, boardSprite->getContentSize().height));
    board->setAnchorPoint(Vec2(0.5, 0.5));
    board->setPosition(defaultPosition);
}

void Board::createPhysicBody()
{
    if (boardPhysicsBody != nullptr)
    {
        boardPhysicsBody->removeFromWorld();
    }

    boardPhysicsBody = PhysicsBody::createBox(board->getContentSize());
    boardPhysicsBody->setDynamic(false);
    boardPhysicsBody->setCollisionBitmask(0x000002);
    boardPhysicsBody->setContactTestBitmask(true);
    boardPhysicsBody->setVelocity(Vec2(0.f, 0.f));
    board->setPhysicsBody(boardPhysicsBody);
}

void Board::reDrawBoard()
{
    auto temPosition = board->getPosition();
    board->removeAllChildren();
    createBoard();
    board->setPosition(temPosition);
    createPhysicBody();
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
    if (size != 0 && size <= boardMaxSize)
    {
        boardSize = size;
        reDrawBoard();
    }
}

void Board::setBoardVelocity(int value)
{
    boardPhysicsBody->setVelocity(boardDefaultVelocity*value);
}