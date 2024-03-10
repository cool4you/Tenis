#pragma once

#include "cocos2d.h"

enum class EBallUpgrade
{
    DEFAULT,
    RED,
    YELLOW,
    GREEN,
    BLUE,
    PURPLE
};

enum class EBallType
{
    DEFAULT,
    DAMAGED
};

class Ball
{
public:
    Ball();
    ~Ball();

   // void initialize(cocos2d::Scene* scene, EBoardType ballType);

private:
    cocos2d::Sprite* ballSprite = nullptr;
    cocos2d::PhysicsBody* ballPhysicsBody = nullptr;
    cocos2d::Vec2 ballDefaultVelocity = cocos2d::Vec2(150.f, 0.f);
    int damage;
};