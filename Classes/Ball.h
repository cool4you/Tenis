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

    void init(const EBallType ballType);

    void setBallPosition(const cocos2d::Vec2 position);
    void setBallVelocity(const cocos2d::Vec2 ballVelocity);
    void changeBallType(const int changeGrade);

    cocos2d::Sprite* Ball::getballSprite() const;
    cocos2d::Size getBallContentSize() const;
    cocos2d::Vec2 getBallPosition() const;
    int getBallDamage() const;
    EBallType getBallType() const;
private:
    void createBall();
    void createBallPhysicsBoydy();
    
    void setBallType(const EBallType ballType);
    void setBallDamage();
    void setBallTexture();

    cocos2d::Sprite* ballSprite = nullptr;
    cocos2d::PhysicsBody* ballPhysicsBody = nullptr;
    int damage = 0;
    const float speed_limit = 500.f;
    EBallType ballType = EBallType::DEFAULT;
};