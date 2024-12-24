#pragma once
#include "cocos2d.h"
#include "GameplayCore.h"
#include "BaseScene.h"

class GameScene : public BaseScene
{
public:
	CREATE_FUNC(GameScene);
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	virtual void onExit() override;

private:
	void establishBackground();

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	GameplayCore gameStart;
};
