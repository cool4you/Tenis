#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include <CCEventListenerKeyboard.h>

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool init() override;
	void update(float delta);

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode);

	CREATE_FUNC(GameScene);
	
private:
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
	cocos2d::PhysicsWorld* sceneWorld;
	bool isKeyPressed;
	int move;
};

#endif // __GAME_SCENE_H__
