#pragma once

#include <vector>
#include "Font.h"
#include "../math/AoMath.h"

namespace ao
{
	class Renderable2D;

	class Renderer2D
	{
	protected:
		Renderer2D();
	public:
		virtual ~Renderer2D() {}

		void push(const mat4& matrix);
		void pop();

		virtual void begin() {}
		virtual void submit(Renderable2D* renderable) = 0;
		virtual void drawString(const std::string& text, const vec3& position, const Font& font, unsigned int color) {}
		virtual void end() {}
		virtual void flush() = 0;
	protected:
		std::vector<mat4> m_TransformationStack;
		const mat4* m_TransformationBack;
	};
}