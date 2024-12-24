#pragma once
#include "cocos2d.h"
#include "BaseScene.h"

class GameOverScene : public BaseScene
{
public:
	CREATE_FUNC(GameOverScene);
	virtual bool init() override;

private:
	void establishBackground();
	void createButtonBackToMenu();

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	int level;
	int score;
};