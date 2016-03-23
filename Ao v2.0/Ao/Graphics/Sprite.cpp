#include "Sprite.h"
#include "Texture.h"
#include "../Math/AoMath.h"

namespace ao
{
	Sprite::Sprite(const vec3& position)
		: Renderable2D(position, vec2(1.0f, 1.0f), 0xffffffff)
	{

	}

	Sprite::Sprite(const vec3& position, const vec2& size, const vec4& color)
		: Renderable2D(position, size, color)
	{

	}

	Sprite::Sprite(const vec3& position, const Texture* texture)
		: Renderable2D(position, vec2(/*doesn't matter*/), 0xffffffff)
	{
		m_TextureID = texture->id;
		m_Size.x = texture->width;
		m_Size.y = texture->height;
	}

	Sprite::Sprite(const vec3& position, const vec2& size, const Texture* texture)
		: Renderable2D(position, size, 0xffffffff)
	{
		m_TextureID = texture->id;
	}

	Sprite::Sprite(const vec3& position, const vec2& size, unsigned int color, const Texture* texture)
		: Renderable2D(position, size, color)
	{
		m_TextureID = texture->id;
	}
}