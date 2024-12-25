#pragma once
#include "cocos2d.h"

enum class EBlockType
{
    DEFAULT,
    GREEN,
    PURPLE
};

class Block
{
public:
    Block();
    ~Block();

    void init(const EBlockType blockType);

    void setBlockPosition(const cocos2d::Vec2 position);

    cocos2d::Sprite* getBlockSprite() const;
    int getCurrentBlockHP() const;
    int getDefaultBlockHP() const;
    void changeHP(const int damage);

private:
    void createBlock();
    void createBlockPhysicsBoydy();
    void setBlockHP();
    void setBlockTexture();
    void setBlockType(EBlockType blockType);
    void changeTexture();
   
    int currentHP;
    int defaultHP;
    EBlockType blockType;
    cocos2d::Sprite* blockSprite = nullptr;
    cocos2d::PhysicsBody* blockPhysicsBody = nullptr;
};
