#include "GameOverScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    return GameOverScene::create();
}

bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cocos2d::Sprite* backgroundSprite = Sprite::create("background.jpg");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
	backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);

	this->addChild(backgroundSprite);

	cocos2d::Label* recordButton = Label::createWithSystemFont("Main Menu", "Felt", 32);
	recordButton->setTextColor(Color4B::GRAY);
	recordButton->enableShadow(Color4B::BLACK);
	cocos2d::ui::Button* button = cocos2d::ui::Button::create();
	button->setTitleLabel(recordButton);
	button->setPosition(Vec2(100, 50));
	button->addClickEventListener(CC_CALLBACK_1(GameOverScene::backMainMenu, this));

	this->addChild(button);

    return true;
}

void GameOverScene::backMainMenu(cocos2d::Ref* sender)
{
	Director::getInstance()->popScene();
}