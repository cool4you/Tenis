#include "Ball.h"

USING_NS_CC;

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::initialize(cocos2d::Scene* scene, EBallUpgrade ballGrade)
{
	ballSprite = Sprite::create("defaultBall.png");
	ballSprite->setPosition(Vec2(150.f, 50.f));
	setTextureBall(ballGrade);
	createPhysicBody();
	scene->addChild(ballSprite);
}

void Ball::setTextureBall(EBallUpgrade ballGrade)
{
	std::string textureName = "";
	switch (ballGrade)
	{
	case EBallUpgrade::DEFAULT:
		ballSprite->setColor(Color3B::WHITE);
		setDamage(1);
		break;
	case EBallUpgrade::RED:
		ballSprite->setColor(Color3B::RED);
		setDamage(2);
		break;
	case EBallUpgrade::YELLOW:
		ballSprite->setColor(Color3B::YELLOW);
		setDamage(4);
		break;
	case EBallUpgrade::GREEN:
		ballSprite->setColor(Color3B::GREEN);
		setDamage(6);
		break;
	case EBallUpgrade::BLUE:
		ballSprite->setColor(Color3B::BLUE);
		setDamage(8);
		break;
	case EBallUpgrade::PURPLE:
		ballSprite->setColor(Color3B::MAGENTA);
		setDamage(10);
		break;
	default:
		break;
	}
}

void Ball::createPhysicBody()
{
	if (ballPhysicsBody != nullptr)
	{
		ballPhysicsBody->removeFromWorld();
	}

	float radius = ballSprite->getContentSize().width / 2.0f;
	ballPhysicsBody = PhysicsBody::createCircle(radius, PhysicsMaterial(0.f,1.f,0.f));
	ballPhysicsBody->setDynamic(true);
	ballPhysicsBody->setCollisionBitmask(0x000003);
	ballPhysicsBody->setContactTestBitmask(true);
	ballPhysicsBody->setVelocity(Vec2(0.f, 0.f));
	ballSprite->setPhysicsBody(ballPhysicsBody);
}

void Ball::setDamage(int newDamage)
{
	damage = newDamage;
}

void Ball::setVelocity(int speed)
{
	ballPhysicsBody->setVelocity(ballDefaultVelocity*speed);
}

int Ball::getDamage()
{
	return damage;
}


