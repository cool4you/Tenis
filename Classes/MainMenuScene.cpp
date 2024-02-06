#include "MainMenuScene.h"
#include "GameScene.h"
#include "LeaderboardScene.h"
#include "InfoScene.h"
#include "Definition.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

bool MainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Загрузка фона
    auto background = Sprite::create("background.jpg"); // укажите путь к вашей фоновой картине
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    // Установка масштаба (scale) фона
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    this->addChild(background, -1); // -1, чтобы фон был отрисован перед всеми другими элементами

    auto gameTitle = Label::createWithTTF("Simple Tenis", "fonts/Marker Felt.ttf", 48); 
    gameTitle->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - gameTitle->getContentSize().height));
    gameTitle->setPositionY(gameTitle->getPositionY() - 50);
    this->addChild(gameTitle);

    // 1. Кнопка "Старт игры"
    auto startGameButton = MenuItemLabel::create(Label::createWithTTF("Start Game", "fonts/Marker Felt.ttf", 24),
        [](Ref* sender) {
            Director::getInstance()->replaceScene(TransitionFade::create(1.0, GameScene::createScene()));
        });

    // 2. Кнопка "Лидерборд"
    auto leaderboardButton = MenuItemLabel::create(Label::createWithTTF("Leaderboard", "fonts/Marker Felt.ttf", 24),
        [](Ref* sender) {
            Director::getInstance()->replaceScene(TransitionFade::create(1.0, LeaderboardScene::createScene()));
        });

    // 3. Кнопка "Туториал"
    auto infoButton = MenuItemLabel::create(Label::createWithTTF("Tutorial", "fonts/Marker Felt.ttf", 24),
        [](Ref* sender) {
            Director::getInstance()->replaceScene(TransitionFade::create(1.0, InfoScene::createScene()));
        });

    // 4. Кнопка "Выход из игры"

    auto exitButton = MenuItemLabel::create(Label::createWithTTF("Quit game", "fonts/Marker Felt.ttf", 24),
        [](Ref* sender) {
            Director::getInstance()->end();
        });
    // Размещение кнопок на экране
    Menu* menu = Menu::create(startGameButton, leaderboardButton, infoButton, exitButton, nullptr);
    menu->alignItemsVerticallyWithPadding(20);
    this->addChild(menu);

    return true;
}


