#pragma once

#include <map>
#include <string>

namespace ao
{
	class Sound;
	class Music;

	class SoundManager
	{
	public:
		static void init();
		static void destroy();
		static void loadSound(const std::string& alias, const std::string& filepath, float volume = 1.0f);
		static void loadMusic(const std::string& alias, const std::string& filepath, float volume = 1.0f);
		static Sound* getSound(const std::string& alias);
		static Music* getMusic(const std::string& alias);
		static void clean();
	private:
		static std::map<const std::string, Sound*> m_SoundCache;
		static std::map<const std::string, Music*> m_MusicCache;
	};
}