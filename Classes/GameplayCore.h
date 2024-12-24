#pragma once
#include "cocos2d.h"
#include "LevelManager.h"
#include "UIManager.h"
#include "base/CCEventListener.h"

enum class EMoveDirection
{
	MOVE_LEFT,
	MOVE_RIGHT
};

class GameplayCore
{
public:
	void startGame(cocos2d::Scene* scene);
	void removeEventListeners();
private:
	void SetupEventListeners();
	bool onContactBegin(const cocos2d::PhysicsContact& contact);
	void onContactSeparate(const cocos2d::PhysicsContact& contact);
	bool onContactPreSolve(const cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPreSolve& preSolve);
	bool onContactPostSolve(const cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& postSolve);
	void keyPressed(const cocos2d::EventKeyboard::KeyCode keyCode);
	void keyReleased(const cocos2d::EventKeyboard::KeyCode keyCode);

	cocos2d::Scene* scene = nullptr;
	bool isBallMove = false;
	bool isBoostSpawn = false;
	bool isGameFinish = false;
	bool isLevelComplete = false;
	bool isLeftBounded = false;
	bool isRightBounded = false;
	int gameLevel = 1;
	int gameScore = 0;
	int life = 3;
	const int maxLife = 3;
	bool isLifeFreez = false;
	const cocos2d::Vec2 boardSpeed = cocos2d::Vec2(150.f, 0.f);
	const cocos2d::Vec2 ballSpeed = cocos2d::Vec2(0.f, 150.f);

	LevelManager levelManager;
	UIManager uiManager;

	std::vector<cocos2d::EventListener*> listeners;
};
