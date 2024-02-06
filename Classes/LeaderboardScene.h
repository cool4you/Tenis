#ifndef __LEADERBOARD_SCENE_H__
#define __LEADERBOARD_SCENE_H__

#include "cocos2d.h"

class LeaderboardScene : public cocos2d::Scene
{
public:
	static Scene* LeaderboardScene::createScene();
	
	bool init() override;

	CREATE_FUNC(LeaderboardScene);

private:
	void backMainMenu(cocos2d::Ref* sender);

};

#endif // __LEADERBORD_SCENE_H__
