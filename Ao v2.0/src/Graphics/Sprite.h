#pragma once

#include <GL/glew.h>
#include "Renderable2D.h"

namespace ao
{
	struct Texture;

	class Sprite : public Renderable2D
	{
	public:
		Sprite(const vec3& position);
		Sprite(const vec3& position, const vec2& size, const vec4& color);
		Sprite(const vec3& position, const Texture* texture);
		Sprite(const vec3& position, const vec2& size, const Texture* texture);
		Sprite(const vec3& position, const vec2& size, unsigned int color, const Texture* texture);
		virtual ~Sprite() {}
	};
}