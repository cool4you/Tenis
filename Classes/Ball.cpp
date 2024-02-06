#include "Ball.h"

USING_NS_CC;

Ball* Ball::createBall(const std::string& filename)
{
    Ball* ball = new Ball();
    if (ball && ball->initBall(filename))
    {
        ball->autorelease();
        return ball;
    }
    CC_SAFE_DELETE(ball);
    return nullptr;
}

bool Ball::initBall(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
    {
        return false;
    }

    // Дополнительная инициализация мяча (если необходимо)

    return true;
}
