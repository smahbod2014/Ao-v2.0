#include "Renderable2D.h"
#include "Renderer2D.h"
#include "../Math/AoMath.h"
#include <iostream>

namespace ao
{
	Renderable2D::Renderable2D()
	{
		m_TextureID = 0;
		setupDefaultUVs();
	}

	Renderable2D::Renderable2D(const vec3& position, const vec2& size, unsigned int color)
	{
		translate(vec2(position.x, position.y));
		m_Size = size;
		m_Origin = vec3(size.x / 2, size.y / 2, 0);
		m_Color = color;
		m_TextureID = 0;
		setupDefaultUVs();
	}

	Renderable2D::Renderable2D(const vec3& position, const vec2& size, const vec4& color)
	{
		translate(vec2(position.x, position.y));
		m_Size = size;
		m_Origin = vec3(size.x / 2, size.y / 2, 0);
		m_TextureID = 0;
		setupDefaultUVs();

		std::cout << "Origin is " << m_Origin.x << ", " << m_Origin.y << std::endl;
		std::cout << "Position is " << m_Position.x << ", " << m_Position.y << std::endl;

		int r = (int)(color.x * 255);
		int g = (int)(color.y * 255);
		int b = (int)(color.z * 255);
		int a = (int)(color.w * 255);

		m_Color = a << 24 | b << 16 | g << 8 | r;
	}

	void Renderable2D::submit(Renderer2D* renderer)
	{
		renderer->push(m_Transformation);
		renderer->submit(this);
		renderer->pop();
	}

	void Renderable2D::setupDefaultUVs()
	{
		m_TexCoords.emplace_back(0.0f, 1.0f);
		m_TexCoords.emplace_back(1.0f, 1.0f);
		m_TexCoords.emplace_back(1.0f, 0.0f);
		m_TexCoords.emplace_back(0.0f, 0.0f);
	}

	void Renderable2D::setOrigin(float x, float y)
	{
		m_Origin.x = x;
		m_Origin.y = y;
	}

	void Renderable2D::translate(float x, float y)
	{
		m_Translation = m_Translation * mat4::translation(x, y, 0);
		m_Position.x += x;
		m_Position.y += y;
		updateTransformation();
	}

	void Renderable2D::translate(const vec2& amount)
	{
		translate(amount.x, amount.y);
	}

	void Renderable2D::translateLocal(float x, float y)
	{
		//translateLocal(x, y, 0);
	}

	void Renderable2D::translateLocal(const vec2& amount)
	{
		//translateLocal(amount.x, amount.y, 0);
	}

	void Renderable2D::rotate(const vec3& axis, float degrees)
	{
		m_Rotation = m_Rotation * mat4::translation(m_Origin)
			* mat4::rotation(axis, degrees) * mat4::translation(-m_Origin);
		updateTransformation();
	}

	void Renderable2D::updateTransformation()
	{
		m_Transformation = m_Translation * m_Rotation * m_Scale;
	}

	void Renderable2D::rotate(float degrees)
	{
		rotate(vec3(0, 0, 1), degrees);
	}

	void Renderable2D::setPosition(const vec2& pos)
	{
		translate(pos - m_Position);
	}

	void Renderable2D::setRotation(float degrees)
	{
		m_Rotation = mat4::rotation(vec3(0, 0, 1), degrees);
		updateTransformation();
	}

	void Renderable2D::setOrigin(const vec2& pos)
	{
		m_Origin.x = pos.x;
		m_Origin.y = pos.y;
	}
}