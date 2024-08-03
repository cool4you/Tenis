#pragma once

#include "cocos2d.h"
#include "GameSceneManager.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool init() override;

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode);
	void update(float delta) override;

	CREATE_FUNC(GameScene);
	
private:
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
	cocos2d::PhysicsWorld* sceneWorld;
	bool isKeyPressed = false;
	GameSceneManager Start;
};
