#pragma once

#include <SDL/SDL_mixer.h>
#include <string>

namespace ao
{
	class Music
	{
	public:
		Music(const std::string& filepath, float volume = 1.0f);
		~Music();

		void play();
		void stop();
		void pause();
		void resume();
	private:
		Mix_Music* m_Music = nullptr;
		float m_Volume = 1.0f;
	};
}