#include "InfoScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* InfoScene::createScene()
{
	return InfoScene::create();
}

bool InfoScene::init()
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

	cocos2d::Label* titleSprite = Label::createWithSystemFont("Info", "Felt", 72.f);
	titleSprite->setTextColor(Color4B::GRAY);
	titleSprite->enableShadow(Color4B::BLACK);
	titleSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - titleSprite->getContentSize().height));
	this->addChild(titleSprite);

	cocos2d::Label* recordButton = Label::createWithSystemFont("Main Menu", "Felt", 32);
	recordButton->setTextColor(Color4B::GRAY);
	recordButton->enableShadow(Color4B::BLACK);
	cocos2d::ui::Button* button = cocos2d::ui::Button::create();
	button->setTitleLabel(recordButton);
	button->setPosition(Vec2(100, 50));
	button->addClickEventListener(CC_CALLBACK_1(InfoScene::backMainMenu, this));
	this->addChild(button);

	


	return true;
}

void InfoScene::backMainMenu(cocos2d::Ref* sender)
{
	Director::getInstance()->popScene();
}
