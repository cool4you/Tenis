#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"

class Ball : public cocos2d::Sprite
{
public:
    Ball* createBall(const std::string& filename);
    bool initBall(const std::string& filename);
};

#endif // __BALL_H__
