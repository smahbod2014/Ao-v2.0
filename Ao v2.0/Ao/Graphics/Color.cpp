#include "Color.h"

namespace ao
{
	unsigned int Color::colorAlpha(unsigned int color, float alpha)
	{
		color &= 0x00ffffff;
		unsigned int alphaValue = (int)(alpha * 0xff);
		color |= alphaValue << 24;
		return color;
	}
}