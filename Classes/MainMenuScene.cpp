#include "MainMenuScene.h"
#include "SceneManager.h"
#include "ui/CocosGUI.h"
#include "AudioManager.h"

USING_NS_CC;

namespace
{
	const std::string FONT = "fonts/Marker Felt.ttf";
	const int FONT_SIZE = 16;
	const int FONT_TITLE_SIZE = 24;
	const int ALIGN_SIZE = 12;
}

bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	establishBackground();
	createMenuButtons();

	AudioManager::playMusic(ESoundType::MenuMusic, true);

	return true;
}

void MainMenuScene::establishBackground()
{
	const Size visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("image/background.jpg");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	background->setScaleX(visibleSize.width / background->getContentSize().width);
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	this->addChild(background, -1);

	Label* gameTitle = Label::createWithTTF("Simple Tenis", FONT, FONT_TITLE_SIZE);
	gameTitle->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - gameTitle->getContentSize().height));
	this->addChild(gameTitle);

}

void MainMenuScene::createMenuButtons()
{
	const std::unordered_map <ESceneType, std::string> buttonsMap =
	{
		{ESceneType::GameScene,"Start Game" },
		{ESceneType::LeaderboardScene,"Leaderboard" },
		{ESceneType::TutorialScene,"Tutorial" },
		{ESceneType::None,"Quit game" }
	};

	Vector<MenuItem*> menuButtonItems = {};

	auto subsribeToMenuButton = [](const ESceneType sceneType, const std::string& buttonTitle) -> MenuItemLabel*
		{
			MenuItemLabel* menuItem = MenuItemLabel::create(Label::createWithTTF(buttonTitle, FONT, FONT_SIZE),
				[=](Ref* sender)
				{
					sceneType == ESceneType::None ? Director::getInstance()->end() : SceneManager::runScene(sceneType);
				});

			return menuItem;
		};

	for (const auto& buttonInfo : buttonsMap)
	{
		menuButtonItems.pushBack(subsribeToMenuButton(buttonInfo.first, buttonInfo.second));
	}

	Menu* menu = Menu::createWithArray(menuButtonItems);
	menu->alignItemsVerticallyWithPadding(ALIGN_SIZE);
	this->addChild(menu);

	const Size visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cocos2d::ui::Button* button = cocos2d::ui::Button::create("image/sound_on.png", "image/sound_off.png");
	button->setAnchorPoint(Vec2(0.f, 0.f));
	button->setPosition(Vec2(origin.x + button->getContentSize().width / 2, origin.y + button->getContentSize().height / 2));
	button->loadTextureNormal(AudioManager::getIsMuted() ? "image/sound_off.png" : "image/sound_on.png");

	button->addClickEventListener([button](Ref* sender) {
		bool isSoundEnabled = !AudioManager::getIsMuted();
		AudioManager::setIsMuted(isSoundEnabled);
		button->loadTextureNormal(isSoundEnabled ? "image/sound_off.png" : "image/sound_on.png");
		});

	this->addChild(button);
}