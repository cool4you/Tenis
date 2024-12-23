#include "UIManager.h"
#include "GameplayCore.h"

USING_NS_CC;

namespace
{
	const std::string FONT = "fonts/Marker Felt.ttf";
	const int FONT_SIZE = 18;
}

void UIManager::createInfoPanel(int level,int life,int maxLife,bool isLifeFreez,cocos2d::Scene* scene)
{
	this->scene = scene;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	establishGameField();
	establishInfoPanel();
	redrawLifePanel(life, maxLife,isLifeFreez);
	updateLevelInfo(level);
}

void UIManager::updateScore(int gameScore)
{
	if (scoreLabel)
	{
		std::string scoreText = "Score: " + std::to_string(gameScore);
		scoreLabel->setString(scoreText);
	}
}

void UIManager::updateLevelInfo(int level)
{
	if (levelInfo)
	{
		std::string scoreText = "Level " + std::to_string(level);
		levelInfo->setString(scoreText);
	}
}

void UIManager::establishGameField()
{
	auto physicsBody = PhysicsBody::createEdgeBox(Size(visibleSize.width, (visibleSize.height * 5.5) / 6), PhysicsMaterial(0.f, 1.f, 0.f));
	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(0x000001);
	physicsBody->setContactTestBitmask(true);

	auto backgroundField = Sprite::create("image/backgroundField.jpg");
	backgroundField->setAnchorPoint(Vec2(0.5f, 1.f));
	backgroundField->setContentSize(Size(visibleSize.width, (visibleSize.height * 5.5) / 6));
	backgroundField->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - (visibleSize.height * 0.5) / 6));
	backgroundField->addComponent(physicsBody);

	scene->addChild(backgroundField, -1);
}

void UIManager::establishInfoPanel()
{
	scoreLabel = Label::createWithTTF("Score: 0", FONT, FONT_SIZE);
	scoreLabel->setAnchorPoint(Vec2(0.f, 1.f));
	scoreLabel->setPosition(Vec2(origin.x + scoreLabel->getContentSize().height / 2, visibleSize.height - scoreLabel->getContentSize().height / 2));
	scene->addChild(scoreLabel, 1);

	levelInfo = Label::createWithTTF("Level 0", FONT, FONT_SIZE);
	levelInfo->setAnchorPoint(Vec2(0.5f, 1.f));
	levelInfo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - levelInfo->getContentSize().height / 2));
	scene->addChild(levelInfo, 1);
}

void UIManager::redrawLifePanel(int life, int maxLife, bool isLifeFreez)
{
	if (life < 0) return;

	if (lifeNode)
	{
		lifeNode->removeAllChildrenWithCleanup(true);
	}

	lifeNode = Node::create();

	std::string loseSpritePath = isLifeFreez ? "image/hp_lose_freezed.png" : "image/hp_lose.png";
	std::string normalSpritePath = isLifeFreez ? "image/hp_freezed.png" : "image/hp.png";

	for (int i = 0; i < maxLife; i++)
	{
		std::string spritePath = (i < (maxLife - life)) ? loseSpritePath : normalSpritePath;

		lifeSprite = Sprite::create(spritePath);
		lifeSprite->setPosition(Vec2(lifeSprite->getContentSize().width * i, 0.f));
		lifeNode->addChild(lifeSprite);
	}

	lifeNode->setContentSize(Size(lifeSprite->getContentSize().width * maxLife,
								  lifeSprite->getContentSize().height));
	lifeNode->setAnchorPoint(Vec2(0.5f, 0.5f));
	lifeNode->setPosition(Vec2(visibleSize.width - lifeNode->getContentSize().width / 2,
							   visibleSize.height - lifeSprite->getContentSize().height / 2));

	scene->addChild(lifeNode, 1);
}