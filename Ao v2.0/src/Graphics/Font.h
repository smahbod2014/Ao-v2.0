#pragma once

#include <string>
#include "../External/freetype-gl-old/freetype-gl.h"
#include "../Math/AoMath.h"

namespace ao
{
	class Font
	{
		friend class FontManager;
	public:
		Font(const std::string& filepath, float size);
		Font(const char* source, float size, size_t bytes);
		~Font();

		void setScale(float x, float y);

		ftgl::texture_font_t* getFont() const { return m_Font; }
		const GLuint getID() const { return m_Atlas->id; }
		const float getSize() const { return m_Size; }
		const vec2& getScale() const { return m_Scale; }

	private:
		ftgl::texture_atlas_t* m_Atlas;
		ftgl::texture_font_t* m_Font;
		float m_Size;
		vec2 m_Scale;
		static const char* s_DefaultFont1[3];
		static const char* s_DefaultFont2[26];
	};
}