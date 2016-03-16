#pragma once

#include <string>
#include "Audio/Sound.h"
#include "Audio/Music.h"
#include "Managers/AoManagers.h"
#include "Graphics/Window.h"

namespace ao
{
	class Ao
	{
	public:
		Ao(const char* title, int width, int height)
		{
			m_Window = new Window(title, width, height);
		}

		void start()
		{
			srand((unsigned int)time(NULL));
			FontManager::initDefaultFonts();
			SoundManager::init();
			init();
			run();
		}
	protected:
		virtual ~Ao()
		{
			FontManager::clean();
			TextureManager::clean();
			SoundManager::clean();
			SoundManager::destroy();

			if (m_Window) delete m_Window;
			if (m_Timer) delete m_Timer;
		}

		virtual void init() = 0;
		//virtual void tick() {}
		virtual void input(float dt) {}
		virtual void update(float dt) {}
		virtual void render() = 0;
		virtual void finish() {}

	private:
#if 1
		void run()
		{
			m_Timer = new Timer();
			float previousTime = m_Timer->elapsed();

			while (!m_Window->shouldClose())
			{
				m_Window->pollInput();
				m_Window->clear();
				float now = m_Timer->elapsed();
				float dt = now - previousTime;
				previousTime = now;
				input(dt);
				update(dt);
				render();
				m_Window->updateInput();
				m_Window->swapBuffer();
			}
			finish();
		}
#else
		void run()
		{
			m_Timer = new Timer();
			float previousTime = m_Timer->elapsed();
			uint32_t currentTime = SDL_GetTicks();
			uint32_t prevTime = currentTime;
			uint32_t frameRate = 1000 / 60;

			while (!m_Window->shouldClose())
			{
				m_Window->pollInput();

				currentTime = SDL_GetTicks();
				if (currentTime - prevTime > frameRate)
				{
					prevTime = currentTime;
					m_Window->clear();
					float now = m_Timer->elapsed();
					float dt = now - previousTime;
					previousTime = now;
					input(dt);
					update(dt);
					render();
					m_Window->updateInput();
					m_Window->swapBuffer();
				}
			}
			finish();
		}
#endif

	private:
		Window* m_Window;
		Timer* m_Timer;
	};
}