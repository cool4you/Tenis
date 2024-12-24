#pragma once
#include "cocos2d.h"
#include "Board.h"
#include "Block.h"
#include "Ball.h"
#include "Boost.h"

class LevelManager
{
public:
	void createLevel(const int level, cocos2d::Scene* scene);
	void applyBoostEffect(const EBoostType boostType,int& life,const int maxLife, bool& isLifeFreez);
	void removeBlock(cocos2d::Node* block, bool& isLevelComplete);
	void removeBoost(cocos2d::Node* boost);

	Board getBoard() const;
	Ball getBall() const;
	Boost getBoost() const;
	std::shared_ptr<Block> getBlock(cocos2d::Node* blockNode) const;

private:
	void spawnBlocks(const int level);
	void spawnBall();
	void spawnBoard();
	void spawnBoost(const int level,const cocos2d::Vec2 position);

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Scene* scene = nullptr;
	cocos2d::Node* blocksFieldNode = nullptr;
	std::vector<std::shared_ptr<Block>> _blocks;
	std::shared_ptr<Block> _block;
	Ball _ball;
	Board _board;
	Boost _boost;
	int level = 0;
};