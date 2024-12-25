#include "Board.h"

USING_NS_CC;

Board::Board()
{
}

Board::~Board()
{
}

void Board::init(const EBoardType boardType, const int boardLength)
{
	this->boardType = boardType;
	this->boardLength = boardLength;

	createBoard();
}

// //////////
// Create function
// //////////

void Board::createBoardCell()
{
	// Map for board texture name
	const std::unordered_map<EBoardType, std::string> boardTypeMap
	{
		{EBoardType::DEFAULT, "image/boardStock.png"},
		{EBoardType::STICKYBOARD, "image/boardSticky.png"}
	};

	// Map for board physic material
	const std::unordered_map<EBoardType, PhysicsMaterial> boardMaterialMap
	{
		{EBoardType::DEFAULT, PhysicsMaterial(0.f, 1.f, 0.f)},
		{EBoardType::STICKYBOARD, PhysicsMaterial(0.f, 0.f, 0.f)}
	};

	// Set texture name and physic material
	for (const std::pair<EBoardType,std::string>&boardName : boardTypeMap)
	{
		if (boardType == boardName.first)
		{
			textureName = boardName.second;
		}
	}

	for (const auto& boardMaterial : boardMaterialMap)
	{
		if (boardType == boardMaterial.first)
		{
			textureMaterial = boardMaterial.second;
		}
	}

	for (int i = 0; i < boardLength; ++i)
	{
		boardSprite = Sprite::create(textureName);
		boardSprite->setPosition(Vec2(boardSprite->getContentSize().width * i, 0.f));
		boardSprite->setAnchorPoint(Vec2(0.f, 0.f));
		boardNode->addChild(boardSprite);
	}
}

void Board::createBoard()
{
	if (!boardNode)
	{
		boardNode = Node::create();

		createBoardCell();

		boardNode->setContentSize(cocos2d::Size(boardSprite->getContentSize().width * boardLength, boardSprite->getContentSize().height));
		boardNode->setAnchorPoint(Vec2(0.5f, 0.5f));

		createBoardPhysicBody();
	}
}

void Board::createBoardPhysicBody()
{
	if (boardPhysicsBody)
	{
		boardPhysicsBody->removeFromWorld();
	}

	boardPhysicsBody = PhysicsBody::createBox(boardNode->getContentSize(), PhysicsMaterial(textureMaterial));
	boardPhysicsBody->setDynamic(false);
	boardPhysicsBody->setCollisionBitmask(0x000003);
	boardPhysicsBody->setContactTestBitmask(true);
	boardPhysicsBody->setVelocity(Vec2::ZERO);
	boardPhysicsBody->setVelocityLimit(speed_limit);

	boardNode->setPhysicsBody(boardPhysicsBody);
}

// //////////
// Setters function 
// //////////

void Board::setBoardPosition(const Vec2 position)
{
	boardNode->setPosition(position);
}

void Board::setBoardVelocity(const Vec2 boardVelocity)
{
	if (boardNode->getPhysicsBody())
	{
		boardPhysicsBody->setVelocity(Vec2(boardVelocity.x, boardVelocity.y * 0));
	}
}

void Board::setBoardType(const EBoardType boardType)
{
	this->boardType = boardType;

	boardNode->removeAllChildren();
	createBoardCell();
	boardPhysicsBody->getShape(0)->setMaterial(textureMaterial);
}

void Board::changeBoardSize(const int modSize)
{
	if (boardLength + modSize >= 1 && boardLength + modSize < boardLengthMax)
	{
		boardNode->removeAllChildren();

		boardLength += modSize;
		createBoardCell();
		boardNode->setContentSize(cocos2d::Size(boardSprite->getContentSize().width * boardLength, boardSprite->getContentSize().height));

		Director::getInstance()->getScheduler()->schedule([=](float dt)
			{
				createBoardPhysicBody();
			}, this, 0.f, 0, 0.f, false, "changePBodyKey");
	}
}

void Board::changeBoardType()
{
	if (this->boardType == EBoardType::DEFAULT)
	{
		this->boardType = EBoardType::STICKYBOARD;
	}
	else
	{
		this->boardType = EBoardType::DEFAULT;
	}
	setBoardType(boardType);
}

// //////////
//  Getters function
// //////////

Node* Board::getBoardNode() const
{
	return boardNode;
}

Vec2 Board::getBoardPosition() const
{
	return boardNode->getPosition();
}

EBoardType Board::getBoardType() const
{
	return boardType;
}