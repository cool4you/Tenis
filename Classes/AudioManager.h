#pragma once
#include "cocos2d.h"

enum class ESoundType
{
	MenuMusic,
	GameMusic,
	BallHitSound,
	BallObsSound
};

class AudioManager
{
public:
	static void playMusic(const ESoundType soundType, bool loop = true);
	static void setIsMuted(bool muted);
	static bool getIsMuted();
	static void stopAll();
};