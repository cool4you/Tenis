#include "Block.h"

USING_NS_CC;

Block::Block()
{

}
Block::~Block()
{

}

void Block::init(const EBlockType blockType)
{
	this->blockType = blockType;

	createBlock();
}

// //////////
// Create function
// //////////

void Block::createBlock()
{
	//	Create block sprite
	if (blockSprite)
	{
		blockSprite = nullptr;
	}

	blockSprite = Sprite::create("image/defaultBlock.png");
	blockSprite->setAnchorPoint(Vec2(0.f, 0.f));
	setBlockType(blockType);
	createBlockPhysicsBoydy();
}

void Block::createBlockPhysicsBoydy()
{
	//	Create block physicsbody
	if (blockPhysicsBody)
	{
		blockPhysicsBody->removeFromWorld();
	}

	blockPhysicsBody = PhysicsBody::createBox(blockSprite->getContentSize(), PhysicsMaterial(0.f, 1.f, 0.f));
	blockPhysicsBody->setDynamic(false);
	blockPhysicsBody->setGravityEnable(false);
	blockPhysicsBody->setCollisionBitmask(0x000004);
	blockPhysicsBody->setContactTestBitmask(true);
	blockPhysicsBody->setPositionOffset(Vec2::ZERO);

	blockSprite->setPhysicsBody(blockPhysicsBody);
}

// //////////
// Setters function 
// //////////

void Block::setBlockHP()
{
	// Map of block HP by type
	const std::unordered_map <EBlockType, int> blcokHPMap =
	{
		{EBlockType::DEFAULT, 1},
		{EBlockType::GREEN, 2},
		{EBlockType::PURPLE, 4}
	};

	// Set block HP
	for (const auto& hpInfo : blcokHPMap)
	{
		if (hpInfo.first == blockType)
		{
			currentHP = hpInfo.second;
			defaultHP = hpInfo.second;
		}
	}
}

void Block::setBlockTexture()
{
	// Map of block texture(color) by type
	const std::unordered_map <EBlockType, Color3B> blcokTextureMap =
	{
		{EBlockType::DEFAULT, Color3B::WHITE},
		{EBlockType::GREEN, Color3B::GREEN},
		{EBlockType::PURPLE, Color3B::MAGENTA}
	};

	// Set block texture(color)
	for (const auto& blockTextureInfo : blcokTextureMap)
	{
		if (blockTextureInfo.first == blockType)
		{
			blockSprite->setColor(blockTextureInfo.second);
		}
	}
}

void Block::setBlockType(const EBlockType blockType)
{
	// Set block type and change block HP, texture
	this->blockType = blockType;
	setBlockHP();
	setBlockTexture();
}

void Block::setBlockPosition(const Vec2 position)
{
	blockSprite->setPosition(position);
}

void Block::changeHP(int damage)
{
	currentHP -= damage;
	changeTexture();
}

void Block::changeTexture()
{
	if (currentHP <= (defaultHP / 2))
	{
		blockSprite->setTexture("image/damagedBlock.png");
	}
}
// //////////
// Getters function 
// //////////
Sprite* Block::getBlockSprite() const
{
	return blockSprite;
}

int Block::getCurrentBlockHP() const
{
	return currentHP;
}

int Block::getDefaultBlockHP() const
{
	return defaultHP;
}