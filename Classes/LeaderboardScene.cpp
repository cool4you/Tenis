#include "LeaderboardScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* LeaderboardScene::createScene()
{
	return LeaderboardScene::create();
}

bool LeaderboardScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cocos2d::Sprite* backgroundSprite = Sprite::create("test2.jpg");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
	backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);	
	this->addChild(backgroundSprite);

	cocos2d::Label* recordButton = Label::createWithSystemFont("Main Menu", "Felt", 32);
	recordButton->setTextColor(Color4B::GRAY);
	recordButton->enableShadow(Color4B::BLACK);

	cocos2d::ui::Button* button = cocos2d::ui::Button::create();
	button->setTitleLabel(recordButton);
	button->setPosition(Vec2(100,50));
	button->addClickEventListener(CC_CALLBACK_1(LeaderboardScene::backMainMenu, this));
	this->addChild(button);

	return true;
}

void LeaderboardScene::backMainMenu(cocos2d::Ref* sender)
{
	//Director::getInstance()->popToSceneStackLevel(2);
	Director::getInstance()->popScene();
}