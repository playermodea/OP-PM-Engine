#include <iostream>

#include "Sound.h"
#include "SoundManager.h"
#include "ResourceManager.h"

Sound::Sound(const char* path, bool loop)
{
	LoadSound(path, loop);
}

Sound::~Sound()
{
	FMOD_Sound_Release(CurSound);

	delete CurSound;
}

void Sound::LoadSound(const char* path, bool loop)
{
	FileName = path;

	if (ResourceManager::Instance()->CheckSoundData(path))
	{
		std::cout << "Sound data already exists : " << path << std::endl;
		delete this;

		return;
	}

	if (loop)
	{
		FMOD_System_CreateSound(SoundManager::Instance()->GetSoundSystem(), path, FMOD_LOOP_NORMAL, 0, &CurSound);
	}
	else
	{
		FMOD_System_CreateSound(SoundManager::Instance()->GetSoundSystem(), path, FMOD_DEFAULT, 0, &CurSound);
	}

	ResourceManager::Instance()->InsertSoundData(path, this);
}
