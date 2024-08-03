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
   void setVelocity(int multFactor,bool levelStarted);
   void setBallPosition(cocos2d::Vec2 position);
   int getDamage() const;
   cocos2d::Sprite* getBallSprite() const;

private:
    void setDamage(int damage);
    void setTextureBall(EBallUpgrade ballGrade);
    void createBall();
    void createPhysicBody();

    float speed = 150.f;
    int damage = 0;
    cocos2d::Sprite* ballSprite = nullptr;
    cocos2d::PhysicsBody* ballPhysicsBody = nullptr;
    cocos2d::Vec2 ballDefaultVelocity = cocos2d::Vec2(0.f,150.f);
    cocos2d::Vec2 ballDefaultMove = cocos2d::Vec2(150.f, 0.f);
    cocos2d::Vec2 ballDefaultPosition = cocos2d::Vec2(150.f, 50.f);
    cocos2d::Scene* gameScene = nullptr;
};