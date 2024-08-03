#include "Ball.h"
#include "Definition.h"

USING_NS_CC;

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::initialize(cocos2d::Scene* scene, EBallUpgrade ballGrade)
{
	gameScene = scene;
	createBall();
	setTextureBall(ballGrade);
	
}

void Ball::setTextureBall(EBallUpgrade ballGrade)
{
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

void Ball::createBall()
{
	ballSprite = Sprite::create("defaultBall.png");
	ballSprite->setAnchorPoint(Vec2(0.5f, 0.f));
	Size visibleSize = Director::getInstance()->getVisibleSize();
	ballDefaultPosition = Vec2(visibleSize.width / 2, ballSprite->getContentSize().height * 2);

	ballSprite->setPosition(ballDefaultPosition);

	createPhysicBody();

	gameScene->addChild(ballSprite);
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
	ballPhysicsBody->setCollisionBitmask(BALL_COLLISION_BITMASK);
	ballPhysicsBody->setContactTestBitmask(true);
	ballPhysicsBody->setVelocity(Vec2::ZERO);
	ballPhysicsBody->setVelocityLimit(speed);
	ballSprite->setPhysicsBody(ballPhysicsBody);
}

void Ball::setDamage(int newDamage)
{
	damage = newDamage;
}

void Ball::setVelocity(int multFactor,bool levelStarted)
{
	if (!levelStarted)
	{
		ballPhysicsBody->setVelocityLimit(speed * multFactor);
		ballPhysicsBody->setVelocity(ballDefaultMove * multFactor);
	}
	else
	{
		ballPhysicsBody->setVelocityLimit(speed * multFactor);
		ballPhysicsBody->setVelocity(ballDefaultVelocity * multFactor);
	}
	
}

int Ball::getDamage() const
{
	return damage;
}

cocos2d::Sprite* Ball::getBallSprite() const
{
	return ballSprite;
}

void Ball::setBallPosition(Vec2 position)
{
	if (ballSprite != nullptr)
	{
		gameScene->removeChild(ballSprite);
	}
	createBall();
	ballSprite->setPosition(position);
	
}
