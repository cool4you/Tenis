#include "Ball.h"

USING_NS_CC;

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::init(const EBallType ballType)
{
	this->ballType = ballType;

	createBall();
}

// //////////
// Create function
// //////////

void Ball::createBall()
{
	// Create ball sprite
	if (!ballSprite)
	{
		ballSprite = Sprite::create("image/defaultBall.png");
		createBallPhysicsBoydy();
		setBallType(ballType);
	}
}

void Ball::createBallPhysicsBoydy()
{
	// Create ball physicsbody
	if (ballPhysicsBody)
	{
		ballPhysicsBody->removeFromWorld();
	}

	float radius = ballSprite->getContentSize().width / 2.0f;
	ballPhysicsBody = PhysicsBody::createCircle(radius, PhysicsMaterial(0.f, 1.f, 0.f));
	ballPhysicsBody->setDynamic(true);
	ballPhysicsBody->setGravityEnable(false);
	ballPhysicsBody->setCollisionBitmask(0x000002);
	ballPhysicsBody->setContactTestBitmask(true);
	ballPhysicsBody->setVelocityLimit(speed_limit);
	ballPhysicsBody->setAngularVelocity(speed_limit);

	ballSprite->setPhysicsBody(ballPhysicsBody);
}

// //////////
// Setters function 
// //////////

void Ball::setBallPosition(const Vec2 position)
{
	// Set ball position
	if (ballSprite)
	{
		ballSprite->setPosition(position);
	}
}

void Ball::setBallVelocity(const Vec2 ballVelocity)
{
	// Set ball velocity
	if (ballPhysicsBody)
	{
		ballPhysicsBody->setVelocity(ballVelocity);
	}
}

void Ball::setBallDamage()
{
	// Map of ball damage
	const std::unordered_map <EBallType, int> ballDamageMap =
	{
		{EBallType::DEFAULT, 1},
		{EBallType::GREEN, 2},
		{EBallType::PURPLE, 4}
	};

	// Set ball damage
	for (const auto& damageInfo : ballDamageMap)
	{
		if (damageInfo.first == ballType)
		{
			damage = damageInfo.second;
		}
	}
}

void Ball::setBallTexture()
{
	// Map of ball texture(color)
	const std::unordered_map <EBallType, Color3B> ballTextureMap =
	{
		{EBallType::DEFAULT, Color3B::WHITE},
		{EBallType::GREEN, Color3B::GREEN},
		{EBallType::PURPLE, Color3B::MAGENTA}
	};

	// Set ball texture
	for (const auto& ballTextureInfo : ballTextureMap)
	{
		if (ballTextureInfo.first == ballType)
		{
			ballSprite->setColor(ballTextureInfo.second);
		}
	}
}

void Ball::setBallType(const EBallType ballType)
{
	// Set ball type
	this->ballType = ballType;
	setBallDamage();
	setBallTexture();
}

void Ball::changeBallType(const int changeGrade)
{
	// Change ball type
	std::vector<EBallType> ballTypes = { EBallType::DEFAULT,EBallType::GREEN,EBallType::PURPLE };
	int it = 0;
	for (EBallType ballType : ballTypes)
	{
		if (this->ballType == ballType)
		{
			if ((it + changeGrade) >= 0 && (it + changeGrade) < int(ballTypes.size()))
			{
				this->ballType = ballTypes.at(it + changeGrade);
				setBallType(this->ballType); 
				break;
			}
		}
		++it;
	}
}

// //////////
//  Getters function
// //////////

Sprite* Ball::getballSprite() const
{
	return ballSprite;
}

Size Ball::getBallContentSize() const
{
	return ballSprite->getContentSize();
}

Vec2 Ball::getBallPosition() const
{
	return ballSprite->getPosition();
}

int Ball::getBallDamage() const
{
	return damage;
}

EBallType Ball::getBallType() const
{
	return ballType;
}