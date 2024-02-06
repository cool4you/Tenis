#include "Blocks.h"

USING_NS_CC;

Block* Block::createBlock(const std::string& filename)
{
    Block* block = new Block();
    if (block && block->initBlock(filename))
    {
        block->autorelease();
        return block;
    }
    CC_SAFE_DELETE(block);
    return nullptr;
}

bool Block::initBlock(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
    {
        return false;
    }

    return true;
}
