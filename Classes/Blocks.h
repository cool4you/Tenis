#pragma once

#include "cocos2d.h"

enum class EBlocksType
{
    DEFAULT,
    RED,
    YELLOW,
    GREEN,
    BLUE,
    PURPLE
};

class Block
{
public:
    Block();
    ~Block();

    bool initialize(cocos2d::Scene* scene, EBlocksType ballGrade);
    void createBlockSprite();
    cocos2d::Node* getBlockFieldNode() const;

private:
    void createPhysicBody();
    void createBlocksField(int level);

    int hp = 0;
    int blocksMaxCount = 20;
    cocos2d::Sprite* blockSprite = nullptr;
    cocos2d::PhysicsBody* blockPhysicsBody = nullptr;
    cocos2d::Node* blocksFieldNode = nullptr;
};
