#pragma once
#include "cocos2d.h"
#include "BaseScene.h"

class SplashScene : public BaseScene
{
public:
	CREATE_FUNC(SplashScene);
	virtual bool init() override;

private:
	void establishBackground();
	const float delaySwapScene = 2.0f;
};


