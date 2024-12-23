#include "AudioManager.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

static bool isSound = true;

void AudioManager::playMusic(const std::string& musicPath, bool loop, float volume)
{
	AudioEngine::play2d(musicPath, loop, volume);
}

void AudioManager::setIsSound(bool sound)
{
	isSound = sound;
	if (isSound)
	{
		AudioEngine::resumeAll();
	}
	else
	{
		AudioEngine::pauseAll();
	}
}

bool AudioManager::getIsSound()
{
	return isSound;
}

void AudioManager::stopAll()
{
	AudioEngine::stopAll();
}
