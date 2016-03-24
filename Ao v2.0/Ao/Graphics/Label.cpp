#include "Label.h"
#include "../Managers/FontManager.h"
#include "Renderer2D.h"

namespace ao
{
	Label::Label(const std::string& text, float x, float y, unsigned int color)
		: Renderable2D(vec3(x, y, 0), vec2(0, 0), color)
	{
		m_Text = text;
		m_Font = FontManager::get("magnetob");
		vec2& bounds = getBounds();
		m_Origin = vec3(bounds.x / 2, bounds.y / 2, 0);
	}

	Label::Label(const std::string& text, float x, float y, Font* font, unsigned int color)
		: Renderable2D(vec3(x, y, 0), vec2(0, 0), color)
	{
		m_Text = text;
		m_Font = font;
		vec2& bounds = getBounds();
		m_Origin = vec3(bounds.x / 2, bounds.y / 2, 0);
	}

	Label::Label(const std::string& text, float x, float y, const std::string& alias, unsigned int color)
		: Renderable2D(vec3(x, y, 0), vec2(0, 0), color)
	{
		m_Text = text;
		m_Font = FontManager::get(alias);
		vec2& bounds = getBounds();
		m_Origin = vec3(bounds.x / 2, bounds.y / 2, 0);
	}

	Label::Label(const std::string& text, float x, float y, const std::string& alias, const vec4& color)
		: Renderable2D(vec3(x, y, 0.0f), vec2(0.0f, 0.0f), color)
	{
		m_Text = text;
		m_Font = FontManager::get(alias);
		vec2& bounds = getBounds();
		m_Origin = vec3(bounds.x / 2, bounds.y / 2, 0);
	}

	Label::~Label()
	{
		
	}

	void Label::submit(Renderer2D* renderer)
	{
		renderer->push(m_Transformation);
		renderer->drawString(m_Text, vec3(m_Position.x, m_Position.y, 0), *m_Font, m_Color);
		renderer->pop();
	}

	vec2 Label::getBounds()
	{
		return m_Font->getBounds(m_Text);
	}
}