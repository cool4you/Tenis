#include "UIManager.h"
#include "GameplayCore.h"

USING_NS_CC;

namespace
{
	const std::string FONT = "fonts/Marker Felt.ttf";
	const int FONT_SIZE = 18;
}

// Create InfoPanel with score, level and life

void UIManager::createInfoPanel(const int level,const int life,const int maxLife,const bool isLifeFreez,Scene* scene)
{
	if (scene)
	{
		this->scene = scene;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	establishGameField();
	establishInfoPanel();
	redrawLifePanel(life, maxLife,isLifeFreez);
	updateLevelInfo(level);
}

// Update score and level
void UIManager::updateScore(const int gameScore)
{
	if (scoreLabel)
	{
		std::string scoreText = "Score: " + std::to_string(gameScore);
		scoreLabel->setString(scoreText);
	}
}

// Update level
void UIManager::updateLevelInfo(const int level)
{
	if (levelInfo)
	{
		std::string scoreText = "Level " + std::to_string(level);
		levelInfo->setString(scoreText);
	}
}

void UIManager::establishGameField()
{
	PhysicsBody* physicsBody = PhysicsBody::createEdgeBox(Size(visibleSize.width, (visibleSize.height * 5.5f) / 6.f), PhysicsMaterial(0.f, 1.f, 0.f));
	physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(0x000001);
	physicsBody->setContactTestBitmask(true);

	Sprite* backgroundField = Sprite::create("image/backgroundField.jpg");
	backgroundField->setAnchorPoint(Vec2(0.5f, 1.f));
	backgroundField->setContentSize(Size(visibleSize.width, (visibleSize.height * 5.5f) / 6.f));
	backgroundField->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - (visibleSize.height * 0.5f) / 6.f));
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

// Redraw life panel
void UIManager::redrawLifePanel(const int life,const int maxLife,const bool isLifeFreez)
{
	if (life < 0) return;

	if (lifeNode)
	{
		lifeNode->removeAllChildrenWithCleanup(true);
	}

	lifeNode = Node::create();

	// Create a sprite based on a variable "isLifeFreez"
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