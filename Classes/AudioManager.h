#pragma once
#include "cocos2d.h"

class AudioManager
{
public:
	static void playMusic(const std::string& musicPath, bool loop = true, float volume = 1.f);
	static void setIsSound(bool sound);
	static bool getIsSound();
	static void stopAll();
private:
};