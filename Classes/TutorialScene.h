#pragma once
#include "BaseScene.h"

class TutorialScene : public BaseScene
{
public:
	CREATE_FUNC(TutorialScene);
	virtual bool init() override;

private:
	void establishBackground();
	void createButtonBackToMenu();

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};