#pragma once
#include "cocos2d.h"

enum class EBallType
{
    DEFAULT,
    GREEN,
    PURPLE
};

class Ball
{
public:
    Ball();
    ~Ball();

    void init(EBallType ballType);

    void setBallPosition(cocos2d::Vec2 position);
    void setBallVelocity(cocos2d::Vec2 ballVelocity);
    void changeBallType(int changeGrade);

    cocos2d::Sprite* Ball::getballSprite() const;
    cocos2d::Size getBallContentSize() const;
    cocos2d::Vec2 getBallPosition() const;
    int getBallDamage() const;
    EBallType getBallType() const;
private:
    void createBall();
    void createBallPhysicsBoydy();
    void setBallType(EBallType ballType);
    void setBallDamage();
    void setBallTexture();

    cocos2d::Sprite* ballSprite = nullptr;
    cocos2d::PhysicsBody* ballPhysicsBody = nullptr;
    int damage = 0;
    const float speed_limit = 500.f;
    EBallType ballType = EBallType::DEFAULT;
};