#include "BaseScene.h"

USING_NS_CC;

void BaseScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	if (bExitAfterTransition)
	{
		onExit();
	}
}

void BaseScene::onEnter()
{
	Scene::onEnter();
	Scene* TransitionScene = Director::getInstance()->getRunningScene();

	if (TransitionScene)
	{
		TransitionScene->setOnExitTransitionDidStartCallback([this]() {
			bExitAfterTransition = false;
			});
	}
}