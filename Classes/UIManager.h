#pragma once
#include "cocos2d.h"


class UIManager
{
public:
	void createInfoPanel(int level, int life, int maxLife, bool isLifeFreez, cocos2d::Scene* scene);
	void updateScore(int gameScore);
	void redrawLifePanel(int life, int maxLife, bool isLifeFreez);
	void updateLevelInfo(int level);

private:
	void establishGameField();
	void establishInfoPanel();

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Scene* scene = nullptr;
 	cocos2d::Label* scoreLabel = nullptr;
	cocos2d::Label* levelInfo = nullptr;
	cocos2d::Node* lifeNode = nullptr;
	cocos2d::Sprite* lifeSprite = nullptr;
};