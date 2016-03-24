#pragma once

namespace ao
{
	class Color
	{
	public:
		static unsigned int colorAlpha(unsigned int mainColor, float alpha);
	public:
		static const unsigned int RED = 0xff0000ff;
		static const unsigned int GREEN = 0xff00ff00;
		static const unsigned int BLUE = 0xffff0000;
		static const unsigned int PURPLE = 0xffff00ff;
		static const unsigned int YELLOW = 0xff00ffff;
		static const unsigned int CYAN = 0xffffff00;
	};
}