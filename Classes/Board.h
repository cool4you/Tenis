#pragma once

#include "cocos2d.h"
#include "string"

enum class EBoardType
{
    STOCK,
    STICKY
};

enum class EBoardContact
{
    LEFT,
    RIGHT
};

class Board
{
public:
    Board();
    ~Board();

    void initialize(cocos2d::Scene* scene,EBoardType boardType, int _boardSize = 5);
    int getBoardSize() const;
    cocos2d::Vec2 getBoardDefaultVelocity() const;
    cocos2d::Sprite* getBoardSprite() const;
    cocos2d::Node* getBoardNode() const;

    void resizeBoard(int size);
    void setBoardVelocity(int value);
    void setBoardPosition(cocos2d::Vec2 position);

private:
    void createBoard();
    void createBoardCell();
    void createBoardPhysicBody();
    void setTextureBoard(EBoardType boardType);
    void DrawBoard();

    cocos2d::Node* boardNode = nullptr;
    cocos2d::Sprite* boardSprite = nullptr;
    cocos2d::PhysicsBody* boardPhysicsBody = nullptr;
    cocos2d::Vec2 boardDefaultVelocity = cocos2d::Vec2(150.f,0.f);
    int boardSize = 0;
    const int boardMaxSize = 10;
    std::string textureName = "";
    cocos2d::PhysicsMaterial texureMaterial;
    cocos2d::Vec2 defaultPosition;
    cocos2d::Scene* gameScene = nullptr;
};


