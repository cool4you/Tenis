#ifndef __BLOCKS_H__
#define __BLOCKS_H__

#include "cocos2d.h"

class Block : public cocos2d::Sprite
{
public:
    static Block* createBlock(const std::string& filename);
    bool initBlock(const std::string& filename);
};

#endif // __BLOCKS_H__
