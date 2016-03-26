#include "Input.h"
#include <SDL/SDL.h>

namespace ao
{
	std::map<int, int> Input::m_KeyMap;
	std::map<KeyCode, int> Input::m_KeyCodes;

	void Input::pressKey(int key)
	{
		auto it = m_KeyMap.find(key);

		if (it == m_KeyMap.end())
		{
			m_KeyMap[key] = 1;
		}
		else
		{
			if (m_KeyMap[key] != 2)
				m_KeyMap[key] = 1;
		}
	}

	void Input::releaseKey(int key)
	{
		m_KeyMap[key] = 0;
	}

	void Input::update()
	{
		for (auto& it : m_KeyMap)
		{
			if (it.second == 1)
				it.second = 2;
		}
	}

	bool Input::isKeyJustPressed(int key)
	{
		auto it = m_KeyMap.find(key);

		if (it != m_KeyMap.end())
		{
			return m_KeyMap[key] == 1;
		}
		else
		{
			return false;
		}
	}

	bool Input::isKeyDown(int key)
	{
		auto it = m_KeyMap.find(key);

		if (it != m_KeyMap.end())
		{
			return m_KeyMap[key] >= 1;
		}
		else
		{
			return false;
		}
	}

	bool Input::isKeyJustPressed(KeyCode keyCode)
	{
		return isKeyJustPressed(m_KeyCodes[keyCode]);
	}

	bool Input::isKeyDown(KeyCode keyCode)
	{
		return isKeyDown(m_KeyCodes[keyCode]);
	}

	void Input::init()
	{
		m_KeyCodes[KeyCode::KEY_A] = SDLK_a;
		m_KeyCodes[KeyCode::KEY_B] = SDLK_b;
		m_KeyCodes[KeyCode::KEY_C] = SDLK_c;
		m_KeyCodes[KeyCode::KEY_D] = SDLK_d;
		m_KeyCodes[KeyCode::KEY_E] = SDLK_e;
		m_KeyCodes[KeyCode::KEY_F] = SDLK_f;
		m_KeyCodes[KeyCode::KEY_G] = SDLK_g;
		m_KeyCodes[KeyCode::KEY_H] = SDLK_h;
		m_KeyCodes[KeyCode::KEY_I] = SDLK_i;
		m_KeyCodes[KeyCode::KEY_J] = SDLK_j;
		m_KeyCodes[KeyCode::KEY_K] = SDLK_k;
		m_KeyCodes[KeyCode::KEY_L] = SDLK_l;
		m_KeyCodes[KeyCode::KEY_M] = SDLK_m;
		m_KeyCodes[KeyCode::KEY_N] = SDLK_n;
		m_KeyCodes[KeyCode::KEY_O] = SDLK_o;
		m_KeyCodes[KeyCode::KEY_P] = SDLK_p;
		m_KeyCodes[KeyCode::KEY_Q] = SDLK_q;
		m_KeyCodes[KeyCode::KEY_R] = SDLK_r;
		m_KeyCodes[KeyCode::KEY_S] = SDLK_s;
		m_KeyCodes[KeyCode::KEY_T] = SDLK_t;
		m_KeyCodes[KeyCode::KEY_U] = SDLK_u;
		m_KeyCodes[KeyCode::KEY_V] = SDLK_v;
		m_KeyCodes[KeyCode::KEY_W] = SDLK_w;
		m_KeyCodes[KeyCode::KEY_X] = SDLK_x;
		m_KeyCodes[KeyCode::KEY_Y] = SDLK_y;
		m_KeyCodes[KeyCode::KEY_Z] = SDLK_z;
		m_KeyCodes[KeyCode::KEY_0] = SDLK_0;
		m_KeyCodes[KeyCode::KEY_1] = SDLK_1;
		m_KeyCodes[KeyCode::KEY_2] = SDLK_2;
		m_KeyCodes[KeyCode::KEY_3] = SDLK_3;
		m_KeyCodes[KeyCode::KEY_4] = SDLK_4;
		m_KeyCodes[KeyCode::KEY_5] = SDLK_5;
		m_KeyCodes[KeyCode::KEY_6] = SDLK_6;
		m_KeyCodes[KeyCode::KEY_7] = SDLK_7;
		m_KeyCodes[KeyCode::KEY_8] = SDLK_8;
		m_KeyCodes[KeyCode::KEY_9] = SDLK_9;
		m_KeyCodes[KeyCode::KEY_SPACE] = SDLK_SPACE;
		m_KeyCodes[KeyCode::KEY_LEFT] = SDLK_LEFT;
		m_KeyCodes[KeyCode::KEY_RIGHT] = SDLK_RIGHT;
		m_KeyCodes[KeyCode::KEY_DOWN] = SDLK_DOWN;
		m_KeyCodes[KeyCode::KEY_UP] = SDLK_UP;
		m_KeyCodes[KeyCode::MOUSE_LEFT] = 1;
		m_KeyCodes[KeyCode::MOUSE_MIDDLE] = 2;
		m_KeyCodes[KeyCode::MOUSE_RIGHT] = 3;
	}
}