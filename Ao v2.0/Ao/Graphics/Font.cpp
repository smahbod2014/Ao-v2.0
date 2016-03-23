#include "Font.h"
#include "FontFactory.h"
#include "Window.h"
#include "../Math/AoMath.h"

namespace ao
{
	Font::Font(const std::string& filepath, float size)
	{
		m_Atlas = ftgl::texture_atlas_new(512, 512, 1);
		m_Font = ftgl::texture_font_new_from_file(m_Atlas, size, filepath.c_str());
		if (!m_Font)
			std::cout << "Failed to load font" << std::endl;
		m_Size = size;
		m_Scale = vec2(1.0f, 1.0f);
	}

	Font::Font(const char* source, float size, size_t bytes)
	{
		m_Atlas = ftgl::texture_atlas_new(512, 512, 1);
		m_Font = ftgl::texture_font_new_from_memory(m_Atlas, size, source, bytes);
		if (!m_Font)
			std::cout << "Failed to load font" << std::endl;
		m_Size = size;
		m_Scale = vec2(1.0f, 1.0f);
		/*std::cout << "Font id: " << m_Atlas->id << std::endl;
		const char A = 'A', B = 'B', C = 'C';
#if 1
		if (ftgl::texture_font_get_glyph(m_Font, A))
			std::cout << "Has A" << std::endl;
		if (ftgl::texture_font_get_glyph(m_Font, B))
			std::cout << "Has B" << std::endl;
		if (ftgl::texture_font_get_glyph(m_Font, C))
			std::cout << "Has C" << std::endl;
#else
		for (int i = 0; i < 3; i++)
		{
			const char c = 'A' + i;
			std::cout << c << std::endl;
			if (!ftgl::texture_font_get_glyph(m_Font, &c))
				std::cout << "something went wrong" << std::endl;
		}
#endif

		std::cout << m_Font->glyphs->size << std::endl;*/

	}

	Font::~Font()
	{
		if (m_Font)
			texture_font_delete(m_Font);
		if (m_Atlas)
			texture_atlas_delete(m_Atlas);
	}

	void Font::setScale(float x, float y)
	{
		m_Scale.x = x;
		m_Scale.y = y;
	}
}