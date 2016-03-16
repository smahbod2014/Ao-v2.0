#pragma once

#include <map>
#include <SDL/SDL.h>

namespace ao
{
	class Input
	{
		friend class Window;
	public:
		static bool isKeyJustPressed(int key);
		static bool isKeyDown(int key);
	private:
		static void pressKey(int key);
		static void releaseKey(int key);
		static void update();

		static std::map<int, int> m_KeyMap;
	};
}

#define AO_KEY_A SDL_GetScancodeFromKey(SDLK_a)
#define AO_KEY_B SDL_GetScancodeFromKey(SDLK_b)
#define AO_KEY_C SDL_GetScancodeFromKey(SDLK_c)
#define AO_KEY_D SDL_GetScancodeFromKey(SDLK_d)
#define AO_KEY_E SDL_GetScancodeFromKey(SDLK_e)
#define AO_KEY_F SDL_GetScancodeFromKey(SDLK_f)
#define AO_KEY_G SDL_GetScancodeFromKey(SDLK_g)
#define AO_KEY_H SDL_GetScancodeFromKey(SDLK_h)
#define AO_KEY_I SDL_GetScancodeFromKey(SDLK_i)
#define AO_KEY_J SDL_GetScancodeFromKey(SDLK_j)
#define AO_KEY_K SDL_GetScancodeFromKey(SDLK_k)
#define AO_KEY_L SDL_GetScancodeFromKey(SDLK_l)
#define AO_KEY_M SDL_GetScancodeFromKey(SDLK_m)
#define AO_KEY_N SDL_GetScancodeFromKey(SDLK_n)
#define AO_KEY_O SDL_GetScancodeFromKey(SDLK_o)
#define AO_KEY_P SDL_GetScancodeFromKey(SDLK_p)
#define AO_KEY_Q SDL_GetScancodeFromKey(SDLK_q)
#define AO_KEY_R SDL_GetScancodeFromKey(SDLK_r)
#define AO_KEY_S SDL_GetScancodeFromKey(SDLK_s)
#define AO_KEY_T SDL_GetScancodeFromKey(SDLK_t)
#define AO_KEY_U SDL_GetScancodeFromKey(SDLK_u)
#define AO_KEY_V SDL_GetScancodeFromKey(SDLK_v)
#define AO_KEY_W SDL_GetScancodeFromKey(SDLK_w)
#define AO_KEY_X SDL_GetScancodeFromKey(SDLK_x)
#define AO_KEY_Y SDL_GetScancodeFromKey(SDLK_y)
#define AO_KEY_Z SDL_GetScancodeFromKey(SDLK_z)
#define AO_KEY_0 SDL_GetScancodeFromKey(SDLK_0)
#define AO_KEY_1 SDL_GetScancodeFromKey(SDLK_1)
#define AO_KEY_2 SDL_GetScancodeFromKey(SDLK_2)
#define AO_KEY_3 SDL_GetScancodeFromKey(SDLK_3)
#define AO_KEY_4 SDL_GetScancodeFromKey(SDLK_4)
#define AO_KEY_5 SDL_GetScancodeFromKey(SDLK_5)
#define AO_KEY_6 SDL_GetScancodeFromKey(SDLK_6)
#define AO_KEY_7 SDL_GetScancodeFromKey(SDLK_7)
#define AO_KEY_8 SDL_GetScancodeFromKey(SDLK_8)
#define AO_KEY_9 SDL_GetScancodeFromKey(SDLK_9)
#define AO_KEY_SPACE SDL_GetScancodeFromKey(SDLK_SPACE)
#define AO_KEY_LEFT 80
#define AO_KEY_RIGHT 79
#define AO_KEY_DOWN 81
#define AO_KEY_UP 82

//add more keys as necessary