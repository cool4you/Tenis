#pragma once
#include "cocos2d.h"
#include "BaseScene.h"

class LeaderboardScene : public BaseScene
{
public:
	CREATE_FUNC(LeaderboardScene);
	virtual bool init() override;

private:
	void establishBackground();
	void createButtonBackToMenu();

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	int level;
	int score;
};