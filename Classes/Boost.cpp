#include "Boost.h"

USING_NS_CC;

Boost::Boost()
{

}
Boost::~Boost()
{
}

namespace
{
	//	Map for boost type and image path
	const std::unordered_map <EBoostType, std::string> boostMap =
	{
		{EBoostType::BALL_DOWNGRADE, "image/boost_ball_downgrade.png"},
		{EBoostType::BOARD_MINUS, "image/boost_board_minus.png"},
		{EBoostType::BALL_UPGRADE, "image/boost_ball_upgrade.png"},
		{EBoostType::BOARD_PLUS, "image/boost_board_plus.png"},
		{EBoostType::HP_FREEZ, "image/boost_hp_freez.png"},
		{EBoostType::HP_PLUS, "image/boost_hp_plus.png"},
		{EBoostType::BOARD_CHANGE_TYPE, "image/boost_board_change_type.png"}
	};
}

void Boost::init(const Vec2 position, const EBoostType boostType)
{	
	this->boostType = boostType;
	createBoost();
	setPosition(position);
}

// //////////
// Create functions
// //////////

void Boost::createBoost()
{
	if (boostType != EBoostType::None)
	{
		boostSprite = Sprite::create(boostMap.at(boostType));
		boostSprite->setAnchorPoint(Vec2(0.f, 0.f));
		createBoostPhysicsBody();
	}
}

void Boost::createBoostPhysicsBody()
{
	PhysicsBody* boostPhysicsBody = PhysicsBody::createBox(boostSprite->getContentSize(), PhysicsMaterial(0.f, 1.f, 0.f));
	boostPhysicsBody->setDynamic(true);
	boostPhysicsBody->setGravityEnable(false);
	boostPhysicsBody->setCollisionBitmask(0x000000);
	boostPhysicsBody->setContactTestBitmask(true);
	boostPhysicsBody->setVelocity(Vec2(0.f, -100.f));
	boostSprite->setPhysicsBody(boostPhysicsBody);
}

void Boost::boostClear()
{
	boostSprite = nullptr;
	boostType = EBoostType::None;
}

// //////////
// Setters functions
// //////////

void Boost::setPosition(const Vec2 position)
{
	if (boostSprite)
	{
		boostSprite->setPosition(position);
	}
}

// //////////
// Getters functions
// //////////

Sprite* Boost::getBoostSprite() const
{
	return boostSprite;
}

EBoostType Boost::getBoostType() const
{
	return boostType;
}