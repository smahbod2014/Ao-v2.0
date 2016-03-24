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

		initializeGlyphs();
	}

	Font::Font(const char* source, float size, size_t bytes)
	{
		m_Atlas = ftgl::texture_atlas_new(512, 512, 1);
		m_Font = ftgl::texture_font_new_from_memory(m_Atlas, size, source, bytes);
		if (!m_Font)
			std::cout << "Failed to load font" << std::endl;
		m_Size = size;
		m_Scale = vec2(1.0f, 1.0f);
		
		initializeGlyphs();

		//std::cout << m_Font->glyphs->size << std::endl;

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

	void Font::initializeGlyphs()
	{
		for (int i = 32; i <= 126; i++)
		{
			char c = (char)i;
			ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(m_Font, c);
			if (glyph)
			{
				m_GlyphBounds[c] = glyph;
			}
			else
				std::cout << "No glyph exists for " << c << std::endl;
		}
	}

	vec2 Font::getBounds(const std::string& text)
	{
		vec2 textBounds;
		for (size_t i = 0; i < text.length(); i++)
		{
			ftgl::texture_glyph_t* glyph = m_GlyphBounds[text[i]];
			textBounds.x += glyph->width;
			textBounds.y = fmaxf(textBounds.y, glyph->height);
			if (i > 0)
				textBounds.x -= ftgl::texture_glyph_get_kerning(glyph, text[i - 1]);
		}
		return textBounds;
	}
}