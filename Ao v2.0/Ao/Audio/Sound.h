#pragma once

#include <string>
#include <SDL/SDL_mixer.h>

namespace ao
{
	class Sound
	{
	public:
		Sound(const std::string& filepath, float volume = 1.0f);
		~Sound();

		void play();
		//TODO: implement these!
		void stop();
		void pause() {}
		void resume() {}
	private:
		Mix_Chunk* m_Sound = nullptr;
	};
}