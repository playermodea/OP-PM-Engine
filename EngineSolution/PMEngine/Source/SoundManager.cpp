#include <iostream>

#include "SoundManager.h"
#include "ResourceManager.h"

SoundManager* SoundManager::SingleInstance = 0;

SoundManager* SoundManager::Instance()
{
	if (SingleInstance == 0)
	{
		SingleInstance = new SoundManager();
	}

	return SingleInstance;
}

void SoundManager::InitSound()
{
	FMOD_System_Create(&SoundSystem, FMOD_VERSION);
	FMOD_System_Init(SoundSystem, 32, FMOD_INIT_NORMAL, nullptr);

	Channel = nullptr;
	Volume = 0.5f;
}

void SoundManager::SoundEnd()
{
	FMOD_System_Close(SoundSystem);
	FMOD_System_Release(SoundSystem);
}

void SoundManager::FindSound(const char* fileName)
{
	if (ResourceManager::Instance()->CheckSoundData(fileName))
	{
		CurSound = ResourceManager::Instance()->CheckSoundData(fileName)->GetSound();
	}
	else
	{
		std::cout << "No sound found" << std::endl;
	}
}

void SoundManager::Play()
{
	FMOD_System_PlaySound(SoundSystem, CurSound, nullptr, false, &Channel);
}

void SoundManager::Pause()
{
	FMOD_Channel_SetPaused(Channel, true);
}

void SoundManager::Resume()
{
	FMOD_Channel_SetPaused(Channel, false);
}

void SoundManager::Stop()
{
	FMOD_Channel_Stop(Channel);
}

void SoundManager::VolumeUP()
{
	if (Volume < 1.0f) {
		Volume += 0.1f;
	}

	FMOD_Channel_SetVolume(Channel, Volume);
}

void SoundManager::VolumeDown()
{
	if (Volume > 0.0f) {
		Volume -= 0.1f;
	}

	FMOD_Channel_SetVolume(Channel, Volume);
}


void SoundManager::Update()
{
	FMOD_Channel_IsPlaying(Channel, &Bool);

	if (Bool) {
		FMOD_System_Update(SoundSystem);
	}
}
