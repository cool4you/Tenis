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

class Ball
{
public:
    Ball();
    ~Ball();

   void initialize(cocos2d::Scene* scene, EBallUpgrade ballGrade);
   void setVelocity(int speed);
   int getDamage();

private:
    void setDamage(int damage);
    void setTextureBall(EBallUpgrade ballGrade);
    void createPhysicBody();

    float speed = 150.f;
    int damage = 0;
    cocos2d::Sprite* ballSprite = nullptr;
    cocos2d::PhysicsBody* ballPhysicsBody = nullptr;
    cocos2d::Vec2 ballDefaultVelocity = cocos2d::Vec2(0.f,150.f);
};