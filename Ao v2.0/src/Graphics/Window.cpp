#include "Window.h"
#include "../Managers/Input.h"

namespace ao
{
	float Window::s_Width;
	float Window::s_Height;

	Window::Window(const char* title, int width, int height)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		Uint32 flags = SDL_WINDOW_OPENGL;
		m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		SDL_GLContext glContext = SDL_GL_CreateContext(m_Window);

		if (glewInit() != GLEW_OK)
			std::cout << "ERROR: Couldn't initialize glew!" << std::endl;

		std::cout << "Ao - OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		glClearColor(0, 0, 0, 1);
		glViewport(0, 0, width, height);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		SDL_GL_SetSwapInterval(1);

		s_Width = width;
		s_Height = height;
	}

	Window::~Window()
	{
		if (m_Window)
			SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	void Window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::pollInput()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				m_ShouldClose = true;
				break;
			case SDL_KEYDOWN:
				Input::pressKey(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				Input::releaseKey(event.key.keysym.sym);
				break;
			}
		}
	}

	void Window::updateInput()
	{
		Input::update();
	}

	void Window::swapBuffer()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL error: " << error << std::endl;

		SDL_GL_SwapWindow(m_Window);
	}
}