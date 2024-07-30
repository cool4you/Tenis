#include "Board.h"
#include "Definition.h"

USING_NS_CC;

Board::Board()
{

}

Board::~Board()
{

}

void Board::initialize(cocos2d::Scene* scene, EBoardType boardType, int _boardSize)
{
    gameScene = scene;
    boardSize = _boardSize;
    setTextureBoard(boardType);
    DrawBoard();
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

cocos2d::Node* Board::getBoardNode() const
{
    return boardNode;
}

void Board::resizeBoard(int size)
{
    if (size != 0 && size <= boardMaxSize)
    {
        boardSize = size;
    }
    cocos2d::Vec2 tempPosition = boardNode->getPosition();
    DrawBoard();
    setBoardPosition(tempPosition);
}

void Board::setBoardVelocity(int value)
{
    if (boardNode->getPhysicsBody())
    {
        boardPhysicsBody->setVelocity(boardDefaultVelocity * value);
    }
}

void Board::setBoardPosition(Vec2 position)
{
    boardNode->setPosition(position);
}

void Board::setTextureBoard(EBoardType boardType)
{
    if (boardType == EBoardType::STOCK)
    {
        textureName = "boardStock.png";
        texureMaterial = PhysicsMaterial(0.f, 1.f, 0.f);
    }
    else if (boardType == EBoardType::STICKY)
    {
        textureName = "boardSticky.png";
        texureMaterial = PhysicsMaterial(0.f, 0.f, 0.f);
    }
}

void Board::createBoard()
{
    if (boardNode != nullptr)
    {
        boardNode->removeAllChildrenWithCleanup(true);
    }

    boardNode = Node::create();

    createBoardCell();

    boardNode->setContentSize(cocos2d::Size(boardSprite->getContentSize().width * boardSize, boardSprite->getContentSize().height));
    boardNode->setAnchorPoint(Vec2(0.5f, 0.f));
    boardNode->setPosition(defaultPosition);

    createBoardPhysicBody();
}

void Board::createBoardCell()
{
    for (int i = 0; i < boardSize; ++i)
    {
        boardSprite = Sprite::create(textureName);
        boardSprite->setPosition(Vec2(boardSprite->getContentSize().width * i, 0.f));
        boardSprite->setAnchorPoint(Vec2(0.f, 0.f));
        boardNode->addChild(boardSprite);
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    defaultPosition = Vec2(visibleSize.width / 2, boardSprite->getContentSize().height);
}

void Board::createBoardPhysicBody()
{
    if (boardPhysicsBody != nullptr)
    {
        boardPhysicsBody->removeFromWorld();
    }

    boardPhysicsBody = PhysicsBody::createBox(boardNode->getContentSize(), PhysicsMaterial(texureMaterial));
    boardPhysicsBody->setDynamic(false);
    boardPhysicsBody->setCollisionBitmask(BOARD_COLLISION_BITMASK);
    boardPhysicsBody->setContactTestBitmask(true);
    boardPhysicsBody->setVelocityLimit(600);
    boardPhysicsBody->setVelocity(Vec2(0.f, 0.f));
    boardNode->setPhysicsBody(boardPhysicsBody);
}

void Board::DrawBoard()
{
    createBoard();
    gameScene->addChild(boardNode);
}
