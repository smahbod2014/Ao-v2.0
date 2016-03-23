#include "SoundManager.h"
#include "../Audio/Sound.h"
#include "../Audio/Music.h"
#include <SDL/SDL_mixer.h>
#include <iostream>

namespace ao
{
	std::map<const std::string, Sound*> SoundManager::m_SoundCache;
	std::map<const std::string, Music*> SoundManager::m_MusicCache;

	void SoundManager::init()
	{
		if (Mix_Init(MIX_INIT_OGG) == -1)
		{
			std::cout << "[SoundManager]: " << std::string(Mix_GetError()) << std::endl;
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY*2, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		{
			std::cout << "[SoundManager]: " << std::string(Mix_GetError()) << std::endl;
		}
	}

	void SoundManager::destroy()
	{
		Mix_Quit();
	}

	void SoundManager::loadSound(const std::string& alias, const std::string& filepath, float volume /* = 1.0f */)
	{
		if (m_SoundCache.find(alias) != m_SoundCache.end())
			return;

		m_SoundCache[alias] = new Sound(filepath, volume);
	}

	void SoundManager::loadMusic(const std::string& alias, const std::string& filepath, float volume /* = 1.0f */)
	{
		if (m_MusicCache.find(alias) != m_MusicCache.end())
			return;

		m_MusicCache[alias] = new Music(filepath, volume);
	}

	Sound* SoundManager::getSound(const std::string& alias)
	{
		if (m_SoundCache.find(alias) == m_SoundCache.end())
			return nullptr;

		return m_SoundCache[alias];
	}

	Music* SoundManager::getMusic(const std::string& alias)
	{
		if (m_MusicCache.find(alias) == m_MusicCache.end())
			return nullptr;

		return m_MusicCache[alias];
	}

	void SoundManager::clean()
	{
		for (auto& it : m_SoundCache)
			delete it.second;

		for (auto& it : m_MusicCache)
			delete it.second;

		m_SoundCache.clear();
		m_MusicCache.clear();
	}
}