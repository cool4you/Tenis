#include "GameOverScene.h"
#include "SceneManager.h"
#include "ui/CocosGUI.h"
#include "SaveManager.h"

USING_NS_CC;

namespace
{
	const std::string FONT = "fonts/Marker Felt.ttf";
	const int FONT_SIZE = 14;
	const int FONT_TITLE_SIZE = 24;
}

bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	establishBackground();
	createButtonBackToMenu();

	auto results =  SaveManager::loadResultFromFile();
	
	cocos2d::Label* recordLabel = Label::createWithTTF("Level : " + std::to_string(results.back().first) + "   " + "Score : " + std::to_string(results.back().second), FONT, FONT_SIZE);
	recordLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(recordLabel);

	return true;
}

void GameOverScene::establishBackground()
{
	Sprite* background = Sprite::create("image/background.jpg");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	this->addChild(background, -1);

	Label* sceneTitle = Label::createWithTTF("Game Over", FONT, FONT_TITLE_SIZE);
	sceneTitle->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - sceneTitle->getContentSize().height));
	this->addChild(sceneTitle);
}

void GameOverScene::createButtonBackToMenu()
{
	cocos2d::Label* backToMenuButton = Label::createWithTTF("Main Menu", FONT, FONT_SIZE);

	cocos2d::ui::Button* button = cocos2d::ui::Button::create();
	button->setTitleLabel(backToMenuButton);
	button->setAnchorPoint(Vec2(0.f, 0.f));
	button->setPosition(Vec2(origin.x + backToMenuButton->getContentSize().height, origin.y + backToMenuButton->getContentSize().height));
	button->addClickEventListener([](Ref* sender) {
		SceneManager::runScene(ESceneType::MainMenuScene);
		});
	this->addChild(button);
}