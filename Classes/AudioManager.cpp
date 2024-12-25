#include "AudioManager.h"
#include "audio/include/AudioEngine.h"


USING_NS_CC;

static bool isMuted = false;
static int audioID = AudioEngine::INVALID_AUDIO_ID;

void AudioManager::playMusic(const ESoundType soundType, bool loop)
{
	const std::unordered_map<ESoundType, std::string> musicMap =
	{  
		{ESoundType::MenuMusic, "audio/menu_music.mp3"},
		{ESoundType::GameMusic, "audio/game_music.mp3"},
	};
	
	const std::unordered_map<ESoundType, std::string> soundMap =
	{
		{ESoundType::BallHitSound, "audio/ball_hit.mp3"},
		{ESoundType::BallObsSound, "audio/ball_obs.mp3"},
	};

	if (musicMap.count(soundType))
	{
		audioID = AudioEngine::play2d(musicMap.at(soundType), loop);
		setIsMuted(isMuted);
	}
	else if(soundMap.count(soundType) && !isMuted)
	{
		AudioEngine::play2d(soundMap.at(soundType), loop);
	}
}

void AudioManager::setIsMuted(bool muted)
{
	if (audioID != AudioEngine::INVALID_AUDIO_ID)
	{
		isMuted = muted;
		AudioEngine::setVolume(audioID, isMuted ? 0.f : 0.5f);
	}
}

bool AudioManager::getIsMuted()
{
	return isMuted;
}

void AudioManager::stopAll()
{
	AudioEngine::stopAll();
	audioID = AudioEngine::INVALID_AUDIO_ID;
}
