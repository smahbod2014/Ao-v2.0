#pragma once

#include "Renderable2D.h"
#include <string>

namespace ao
{
	class Font;
	class Label : public Renderable2D
	{
	public:
		Label(const std::string& text, float x, float y, unsigned int color);
		Label(const std::string& text, float x, float y, Font* font, unsigned int color);
		Label(const std::string& text, float x, float y, const std::string& alias, unsigned int color);
		Label(const std::string& text, float x, float y, const std::string& alias, const vec4& color);
		virtual ~Label();

		virtual void submit(Renderer2D* renderer) override;

		vec2 getBounds();
	private:
		std::string m_Text;
		Font* m_Font;
	};
}