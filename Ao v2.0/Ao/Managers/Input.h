#pragma once

#include <map>

namespace ao
{
	enum KeyCode { KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I,
		KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
		KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_SPACE, KEY_LEFT, KEY_RIGHT, KEY_UP,
		KEY_DOWN, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9 };
	class Input
	{
		friend class Window;
	public:
		static bool isKeyJustPressed(int key);
		static bool isKeyDown(int key);
		static bool isKeyJustPressed(KeyCode keyCode);
		static bool isKeyDown(KeyCode keyCode);
		static void init();
	private:
		static void pressKey(int key);
		static void releaseKey(int key);
		static void update();

		static std::map<int, int> m_KeyMap;
		static std::map<KeyCode, int> m_KeyCodes;
	};

}

#define AO_KEY_A ao::KeyCode::KEY_A
#define AO_KEY_B ao::KeyCode::KEY_B
#define AO_KEY_C ao::KeyCode::KEY_C
#define AO_KEY_D ao::KeyCode::KEY_D
#define AO_KEY_E ao::KeyCode::KEY_E
#define AO_KEY_F ao::KeyCode::KEY_F
#define AO_KEY_G ao::KeyCode::KEY_G
#define AO_KEY_H ao::KeyCode::KEY_H
#define AO_KEY_I ao::KeyCode::KEY_I
#define AO_KEY_J ao::KeyCode::KEY_J
#define AO_KEY_K ao::KeyCode::KEY_K
#define AO_KEY_L ao::KeyCode::KEY_L
#define AO_KEY_M ao::KeyCode::KEY_M
#define AO_KEY_N ao::KeyCode::KEY_N
#define AO_KEY_O ao::KeyCode::KEY_O
#define AO_KEY_P ao::KeyCode::KEY_P
#define AO_KEY_Q ao::KeyCode::KEY_Q
#define AO_KEY_R ao::KeyCode::KEY_R
#define AO_KEY_S ao::KeyCode::KEY_S
#define AO_KEY_T ao::KeyCode::KEY_T
#define AO_KEY_U ao::KeyCode::KEY_U
#define AO_KEY_V ao::KeyCode::KEY_V
#define AO_KEY_W ao::KeyCode::KEY_W
#define AO_KEY_X ao::KeyCode::KEY_X
#define AO_KEY_Y ao::KeyCode::KEY_Y
#define AO_KEY_Z ao::KeyCode::KEY_Z
#define AO_KEY_0 ao::KeyCode::KEY_0
#define AO_KEY_1 ao::KeyCode::KEY_1
#define AO_KEY_2 ao::KeyCode::KEY_2
#define AO_KEY_3 ao::KeyCode::KEY_3
#define AO_KEY_4 ao::KeyCode::KEY_4
#define AO_KEY_5 ao::KeyCode::KEY_5
#define AO_KEY_6 ao::KeyCode::KEY_6
#define AO_KEY_7 ao::KeyCode::KEY_7
#define AO_KEY_8 ao::KeyCode::KEY_8
#define AO_KEY_9 ao::KeyCode::KEY_9
#define AO_KEY_SPACE ao::KeyCode::KEY_SPACE
#define AO_KEY_LEFT ao::KeyCode::KEY_LEFT
#define AO_KEY_RIGHT ao::KeyCode::KEY_RIGHT
#define AO_KEY_DOWN ao::KeyCode::KEY_DOWN
#define AO_KEY_UP ao::KeyCode::KEY_UP

//add more keys as necessary