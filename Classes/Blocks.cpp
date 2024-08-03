#include "Blocks.h"
#include "Definition.h"

USING_NS_CC;

Block::Block()
{

}
Block::~Block()
{

}

bool Block::initialize(Scene* scene, EBlocksType ballGrade)
{
	createBlocksField(1);

    scene->addChild(blocksFieldNode);
    return true;
}

void Block::createBlockSprite()
{
	blockSprite = Sprite::create("defaultBlock.png");
}

cocos2d::Node* Block::getBlockFieldNode() const
{
	return blocksFieldNode;
}

void Block::createPhysicBody()
{
	if (blockPhysicsBody != nullptr)
	{
		blockPhysicsBody->removeFromWorld();
	}

	blockPhysicsBody = PhysicsBody::createBox(blockSprite->getContentSize(), PhysicsMaterial(0.f, 1.f, 0.f));
	blockPhysicsBody->setDynamic(false);
	blockPhysicsBody->setCollisionBitmask(BLOCKS_COLLISION_BITMASK);
	blockPhysicsBody->setContactTestBitmask(true);
	blockSprite->setPhysicsBody(blockPhysicsBody);
}

void Block::createBlocksField(int level)
{
	blocksFieldNode = Node::create();
	int itWidth = 11;
	int itHeight = 10;
	for (int i = 0; i < itWidth; ++i)
	{
		for (int j = 0; j < itHeight; j++)
		{
			createBlockSprite();
			blockSprite->setPosition(Vec2(blockSprite->getContentSize().width * i, blockSprite->getContentSize().height * j));
			blockSprite->setAnchorPoint(Vec2(0.f, 0.f));
			createPhysicBody();
			blocksFieldNode->addChild(blockSprite);
		}
	}
	blocksFieldNode->setContentSize(cocos2d::Size(blockSprite->getContentSize().width * itWidth, blockSprite->getContentSize().height * itHeight));
	blocksFieldNode->setAnchorPoint(Vec2(0.5f, 1.f));
	blocksFieldNode->setPosition(Vec2(150.f, 520.f));
}