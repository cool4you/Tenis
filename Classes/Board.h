#pragma once
#include "cocos2d.h"

enum class EBoardType
{
    DEFAULT,
    STICKYBOARD
};

class Board
{
public:
    Board();
    ~Board();

    void init(const EBoardType boardType,const int boardLength);

    void setBoardVelocity(const cocos2d::Vec2 boardVelocity);
    void setBoardPosition(const cocos2d::Vec2 position);
    void setBoardType(const EBoardType boardType);
    void changeBoardSize(const int modSize);
    void changeBoardType();

    cocos2d::Node* getBoardNode() const;
    cocos2d::Vec2 getBoardPosition() const;
    EBoardType getBoardType() const;

private:
    void createBoardCell();
    void createBoard();
    void createBoardPhysicBody();

    cocos2d::Node* boardNode = nullptr;
    cocos2d::Sprite* boardSprite = nullptr;
    cocos2d::PhysicsBody* boardPhysicsBody = nullptr;
    std::string textureName;
    cocos2d::PhysicsMaterial textureMaterial;
    int boardLength = 0;
    int boardLengthMax = 10;
    const float speed_limit = 500.f;
    EBoardType boardType = EBoardType::DEFAULT;
};


