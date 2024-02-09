#pragma once

#include "cocos2d.h"

class Ball
{
public:
    Ball();
    ~Ball();

   // void initialize(cocos2d::Scene* scene, EBoardType ballType);

private:
    cocos2d::Sprite* ballSprite = nullptr;
    cocos2d::PhysicsBody* ballPhysicsBody = nullptr;
};