#pragma once
#include "cocos2d.h"

class BaseScene : public cocos2d::Scene
{
public:
	// Avoid crash on game exit while transitioning between scenes 
	void onEnterTransitionDidFinish() override;
	void onEnter() override;

private:
	bool bExitAfterTransition = true;
};