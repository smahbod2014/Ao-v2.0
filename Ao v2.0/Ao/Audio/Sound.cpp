#include "Sound.h"
#include <SDL/SDL_mixer.h>
#include <iostream>

namespace ao
{
	Mix_Chunk* m_Sound = nullptr;

	Sound::Sound(const std::string& filepath, float volume /* = 1.0f */)
	{
		m_Sound = Mix_LoadWAV(filepath.c_str());

		if (!m_Sound)
		{
			std::cout << "[Sound]: Failed to load " << filepath << std::endl;
			std::cout << "[Sound]: " << std::string(Mix_GetError()) << std::endl;
		}

		if (m_Sound)
		{
			Mix_VolumeChunk(m_Sound, (int)(volume * MIX_MAX_VOLUME));
		}
	}

	Sound::~Sound()
	{
		if (m_Sound)
			Mix_FreeChunk(m_Sound);
	}

	void Sound::play()
	{
		if (!m_Sound)
			return;

		if (Mix_PlayChannel(-1, m_Sound, 0) == -1)
		{
			std::cout << "[Sound]: Failed to play sound." << std::endl;
			std::cout << "[Sound]: " << std::string(Mix_GetError()) << std::endl;
		}
	}

	void Sound::stop()
	{

	}
}