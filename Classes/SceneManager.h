#pragma once

enum class ESceneType
{
	None,
	SplashScene,
	MainMenuScene,
	GameScene,
	GameOverScene,
	LeaderboardScene,
	TutorialScene
};

class SceneManager
{
public:
	static void runScene(const ESceneType sceneType);
	static void deferredRunScene(const ESceneType sceneType, const float delay, void* target);
};