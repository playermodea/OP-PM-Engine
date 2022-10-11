#pragma once

#include <map>

#include "FMOD/fmod.hpp"

class Sound;

class SoundManager
{
private:
	FMOD_SYSTEM *SoundSystem;
	FMOD_SOUND *CurSound;
	FMOD_CHANNEL *Channel;
	FMOD_BOOL Bool;
	float Volume;

	static SoundManager* SingleInstance;

private:
	SoundManager() {};

public:
	static SoundManager* Instance();

	void InitSound();
	void SoundEnd();
	void FindSound(const char* fileName);
	void Play();
	void Pause();
	void Resume();
	void Stop();
	void VolumeUP();
	void VolumeDown();
	void Update();

	FMOD_SYSTEM* GetSoundSystem()
	{ 
		return SoundSystem;
	}
	FMOD_CHANNEL* GetChannel()
	{ 
		return Channel;
	}
};