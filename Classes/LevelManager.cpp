#include "LevelManager.h"
//#include "GameplayCore.h"
#include <iostream>
#include <algorithm>

USING_NS_CC;

namespace
{
	const int BLOCKS_FIELD_WEIGHT_MAX = 13;
	const int BLOCKS_FIELD_HEIGHT_MAX = 10;
	int maxBoostPerLevel;
}

void LevelManager::createLevel(const int level, Scene* scene)
{
	if (scene)
	{
		this->scene = scene;
	}
	this->level = level;
	maxBoostPerLevel = 3;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	spawnBall();
	spawnBoard();
	spawnBlocks(level);	

	if (_boost.getBoostSprite())
	{
		removeBoost(_boost.getBoostSprite());
	}
}

void LevelManager::applyBoostEffect(EBoostType boostType,int& life,int maxLife,bool& isLifeFreez)
{
	switch (boostType)
	{
	case EBoostType::None:
		break;
	case EBoostType::BALL_DOWNGRADE: _ball.changeBallType(-1);
		break;
	case EBoostType::BOARD_MINUS: _board.changeBoardSize(-1);
		break;
	case EBoostType::BALL_UPGRADE: _ball.changeBallType(1);
		break;
	case EBoostType::BOARD_PLUS: _board.changeBoardSize(1);
		break;
	case EBoostType::HP_FREEZ: 
		if (isLifeFreez) 
		{ 
			isLifeFreez = !isLifeFreez; 
		}				 
		else 
		{ 
			isLifeFreez = !isLifeFreez; 
		}
		break;
	case EBoostType::HP_PLUS: ++life; if (life >= maxLife) { life = maxLife; }
		break;
	case EBoostType::BOARD_CHANGE_TYPE: _board.changeBoardType();
		break;
	default:
		break;
	}
}

//////////
// Remove functions
//////////

void LevelManager::removeBlock(Node* block, bool& isLevelComplete)
{
	Size fieldNodeContentSize = blocksFieldNode->getContentSize();
	float offsetX = blocksFieldNode->getPosition().x - (fieldNodeContentSize.width * blocksFieldNode->getAnchorPoint().x);
	float offsetY = blocksFieldNode->getPosition().y - (fieldNodeContentSize.height * blocksFieldNode->getAnchorPoint().y);
	Vec2 position = block->getPosition() + Vec2(offsetX, offsetY);

	blocksFieldNode->removeChild(block, true);
	if (blocksFieldNode->getChildrenCount() == 0)
	{
		isLevelComplete = true;
	}

	int level = this->level;
	Director::getInstance()->getScheduler()->schedule([=](float dt)
		{
			spawnBoost(level, position);
		}, this, 0.f, 0, 0.f, false, "changePosKey");
}

void LevelManager::removeBoost(Node* boost)
{
	if (_boost.getBoostSprite() == boost)
	{
		auto boostType = _boost.getBoostType();
		scene->removeChild(boost, true);
		_boost.boostClear();
	}
}

//////////
// Spawn obj functions
//////////

void LevelManager::spawnBlocks(const int level)
{
	if (blocksFieldNode)
	{
		blocksFieldNode->removeAllChildrenWithCleanup(true);
		scene->removeChild(blocksFieldNode, true);
		blocksFieldNode = nullptr;
	}
	blocksFieldNode = Node::create();
	
	// clear blocks before creation of new blocks for current level
	_blocks.clear();

	const float PER_LEVEL_COEF = 0.1f;
	const int PURPLE_BLOCK_INITIAL_LVL = 11;

	// blocks count constants
	const size_t MIN_BLOCKS = 10;
	const size_t MAX_BLOCKS = 130;
	const size_t BLOCKS_PER_LEVEL_COEF = 10;

	// block-related chances
	const float WHITE_BLOCK_CHANCE = std::clamp((1.f - (level - 1) * PER_LEVEL_COEF), 0.f, 1.f);
	const float PURPLE_BLOCK_CHANCE = std::clamp((level - PURPLE_BLOCK_INITIAL_LVL) * PER_LEVEL_COEF, 0.f, 1.f);
	const float GREEN_BLOCK_CHANCE = std::clamp((1.f - WHITE_BLOCK_CHANCE - PURPLE_BLOCK_CHANCE), 0.f, 1.f);

	// calculate random block indexes
	const size_t BLOCKS_COUNT = std::clamp(level * BLOCKS_PER_LEVEL_COEF, MIN_BLOCKS, MAX_BLOCKS);
	std::set<size_t> indexes = {};

	while (indexes.size() < BLOCKS_COUNT)
	{
		indexes.insert(rand() % MAX_BLOCKS);
	}

	for (const size_t index : indexes)
	{
		// calculate random type of block
		const float RAND_PERCENT = (rand() % 100) * 0.01f;
		EBlockType block_type = EBlockType::DEFAULT;

		if (RAND_PERCENT < PURPLE_BLOCK_CHANCE)
		{
			block_type = EBlockType::PURPLE;
		}
		else if (RAND_PERCENT < (PURPLE_BLOCK_CHANCE + GREEN_BLOCK_CHANCE))
		{
			block_type = EBlockType::GREEN;
		}

		// create block
		_block = std::make_shared<Block>();
		_block->init(block_type);
		_blocks.push_back(_block);

		Vec2 position = Vec2(_block->getBlockSprite()->getContentSize().width * (index % BLOCKS_FIELD_WEIGHT_MAX), _block->getBlockSprite()->getContentSize().height * (index / BLOCKS_FIELD_WEIGHT_MAX));
		_block->setBlockPosition(position);
		blocksFieldNode->addChild(_block->getBlockSprite(), 1, _blocks.size() - 1);
	}

	Size contentSize = Size(_block->getBlockSprite()->getContentSize().width * BLOCKS_FIELD_WEIGHT_MAX, _block->getBlockSprite()->getContentSize().height * BLOCKS_FIELD_HEIGHT_MAX);

	blocksFieldNode->setContentSize(contentSize);
	blocksFieldNode->setAnchorPoint(Vec2(0.5f, 1.f));
	blocksFieldNode->setPosition(Vec2(150.f, 520.f));
	scene->addChild(blocksFieldNode);
}

void LevelManager::spawnBall()
{
	if (!_ball.getballSprite())
	{
		_ball.init(EBallType::DEFAULT);
		scene->addChild(_ball.getballSprite());
	}
	_ball.setBallPosition(Vec2(visibleSize.width / 2, _ball.getBallContentSize().height * 3 + 1));
	
	if (_board.getBoardNode())
	{
		if (_board.getBoardNode()->getPhysicsBody())
		{
			_ball.setBallVelocity(_board.getBoardNode()->getPhysicsBody()->getVelocity());
		}
	}
}

void LevelManager::spawnBoard()
{
	if (!_board.getBoardNode())
	{
		_board.init(EBoardType::DEFAULT, 5);
		scene->addChild(_board.getBoardNode());
	}
	_board.setBoardPosition(Vec2(visibleSize.width / 2, _ball.getBallContentSize().height * 2));
}

void LevelManager::spawnBoost(const int level,const Vec2 position)
{
	if (level != this->level)
	{
		return;
	}

	if (_boost.getBoostSprite())
	{
		return;
	}

	const float PER_LEVEL_COEF = 0.05f;
	const float BOOST_POSITIVE = std::clamp(1.f - level * PER_LEVEL_COEF, 0.2f, 0.8f);
	const float BOOST_NEGATIVE = std::clamp(1.f - BOOST_POSITIVE, 0.2f, 0.8f);
	const float RAND_BOOST_CHANCE = (rand() % 100 + 1) * 0.01f;
	const float BOOST_CHANCE = 0.25f * maxBoostPerLevel;

	if (RAND_BOOST_CHANCE > BOOST_CHANCE)
	{
		return;
	}

	const std::vector<EBoostType> PositiveBoosts = { EBoostType::BALL_UPGRADE, EBoostType::BOARD_PLUS, EBoostType::HP_FREEZ, EBoostType::HP_PLUS, EBoostType::BOARD_CHANGE_TYPE };
	const std::vector<EBoostType> NegativeBoosts = { EBoostType::BALL_DOWNGRADE, EBoostType::BOARD_MINUS,EBoostType::BOARD_CHANGE_TYPE };

	const float RAND_BOOST_TYPE_EFFECT = (rand() % 100 + 1) * 0.01f;
	const bool IS_NEGATIVE_BOOST = RAND_BOOST_TYPE_EFFECT < BOOST_NEGATIVE;

	EBoostType boostType = EBoostType::None;

	if (IS_NEGATIVE_BOOST && !NegativeBoosts.empty())
	{
		boostType = NegativeBoosts[rand() % NegativeBoosts.size()];
	}
	else if (!PositiveBoosts.empty())
	{
		boostType = PositiveBoosts[rand() % PositiveBoosts.size()];
	}

	if (boostType != EBoostType::None)
	{
		--maxBoostPerLevel;
		_boost.init(position, boostType);
		scene->addChild(_boost.getBoostSprite());
	}
}

//////////
//Getters functions
//////////

Board LevelManager::getBoard() const
{
	return _board;
}

Ball LevelManager::getBall() const
{
	return _ball;
}

Boost LevelManager::getBoost() const
{
	return _boost;
}

std::shared_ptr<Block> LevelManager::getBlock(Node* blockNode) const
{

	for (std::shared_ptr<Block> block : _blocks)
	{
		if (block && block->getBlockSprite() == blockNode)
		{
			return block;
		}
	}

	return nullptr;
}