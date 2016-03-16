#include "Music.h"
#include <iostream>

namespace ao
{
	Music::Music(const std::string& filepath, float volume /* = 1.0f */)
	{
		m_Music = Mix_LoadMUS(filepath.c_str());

		if (!m_Music)
		{
			std::cout << "[Music]: " << std::string(Mix_GetError()) << std::endl;
		}

		m_Volume = volume;
	}

	Music::~Music()
	{
		if (m_Music)
			Mix_FreeMusic(m_Music);
	}

	void Music::play()
	{
		if (Mix_PlayMusic(m_Music, -1) == -1)
		{
			std::cout << "[Music]: " << std::string(Mix_GetError()) << std::endl;
		}

		Mix_VolumeMusic((int)(m_Volume * MIX_MAX_VOLUME));
	}

	void Music::stop()
	{
		Mix_HaltMusic();
	}

	void Music::pause()
	{
		Mix_PauseMusic();
	}

	void Music::resume()
	{
		Mix_ResumeMusic();
	}
}