#ifndef __INFO_SCENE_H__
#define __INFO_SCENE_H__

#include "cocos2d.h"

class InfoScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool init() override;

	CREATE_FUNC(InfoScene);

private:
	void backMainMenu(cocos2d::Ref* sender);

};

#endif // __INFO_SCENE_H__
