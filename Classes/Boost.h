#pragma once
#include "cocos2d.h"

enum class EBoostType
{
    None,
    BALL_DOWNGRADE,
    BOARD_MINUS,
    BALL_UPGRADE,
    BOARD_PLUS,
    HP_FREEZ,
    HP_PLUS,
    BOARD_CHANGE_TYPE
};

class Boost
{
public:
    Boost();
    ~Boost();
    void init(cocos2d::Vec2 position, EBoostType boostType);
    void boostClear();
    void setPosition(cocos2d::Vec2 position);
    cocos2d::Sprite* getBoostSprite() const;
    EBoostType getBoostType() const;
private:

    void createBoost();
    void createBoostPhysicsBody();
    cocos2d::Sprite* boostSprite = nullptr;
    EBoostType boostType;
};