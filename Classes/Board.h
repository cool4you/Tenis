#pragma once

#include "cocos2d.h"

enum class EBoardType
{
    STOCK,
    STICKY
};

class Board
{
public:
    Board();
    ~Board();

    void initialize(cocos2d::Scene* scene,EBoardType boardType, int _boardSize = 5);
    void setTextureBoard(EBoardType boardType);
    void createBoard();
    void createPhysicBody();
    int getBoardSize() const;
    cocos2d::Vec2 getBoardDefaultVelocity() const;
    cocos2d::Sprite* getBoardSprite() const;
    void setBoardSize(int size);
    void setBoardVelocity(int value);
private:
    void reDrawBoard();

    cocos2d::Node* board = nullptr;
    cocos2d::Sprite* boardSprite = nullptr;
    cocos2d::PhysicsBody* boardPhysicsBody = nullptr;
    cocos2d::Vec2 boardDefaultVelocity = cocos2d::Vec2(150.f,0.f);
    int boardSize = 0;
    const int boardMaxSize = 12;
    std::string textureName = "";
    cocos2d::Vec2 defaultPosition = cocos2d::Vec2(600.f, 75.f);

};


