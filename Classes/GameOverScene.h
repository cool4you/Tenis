#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;

    CREATE_FUNC(GameOverScene);
private:
    void GameOverScene::backMainMenu(cocos2d::Ref* sender);
    
};

#endif // __GAME_OVER_SCENE_H__
