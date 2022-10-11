#pragma once

#include <string>

#include "FMOD/fmod.h"

class Sound
{
private:
	std::string FileName;

	FMOD_SOUND *CurSound;

public:
	Sound(const char* path, bool loop = false);
	~Sound();

	void LoadSound(const char* path, bool loop = false);

	std::string GetFileName()
	{ 
		return FileName;
	}
	FMOD_SOUND* GetSound()
	{ 
		return CurSound;
	}
};