#pragma once

#include <iostream>
#include <SDL/SDL.h>

namespace ao
{
	class Window
	{
	public:
		Window(const char* title, int width, int height);
		~Window();
		void clear();
		void pollInput();
		void updateInput();
		void swapBuffer();
		bool shouldClose() const { return m_ShouldClose; }

		static float getWidth() { return s_Width; }
		static float getHeight() { return s_Height; }

	private:
		static float s_Width, s_Height;
		SDL_Window* m_Window;
		bool m_ShouldClose = false;
	};
}