#pragma once

#include <GL/glew.h>
#include <vector>
#include "../Math/AoMath.h"

namespace ao
{
	class Renderer2D;

	struct VertexData
	{
		vec3 position;
		vec2 uv;
		float sampler;
		unsigned int color;
	};

	class Renderable2D
	{
	protected:
		Renderable2D();
	public:
		//TODO: Add extra constructors for 2D positions
		Renderable2D(const vec3& position, const vec2& size, unsigned int color);
		Renderable2D(const vec3& position, const vec2& size, const vec4& color);
		virtual ~Renderable2D() {}

		virtual void submit(Renderer2D* renderer);


		//TODO: Cache positions after every transformation for fast lookup
		void setOrigin(float x, float y);
		void translateLocal(float x, float y);
		void translateLocal(const vec2& amount);
		void translate(float x, float y);
		void translate(const vec2& amount);
		void rotate(const vec3& axis, float degrees);
		void rotate(float degrees);

		void setPosition(const vec2& pos);
		void setRotation(float degrees);
		void setOrigin(const vec2& pos);

		const vec2& getPosition() { return m_Position; }
		const vec2& getSize() const { return m_Size; }
		vec2 getCenter() const { return m_Position + m_Size / 2; }
		const unsigned int getColor() const { return m_Color; }
		const std::vector<vec2>& getUVs() const { return m_TexCoords; }
		const GLuint getTextureID() const { return m_TextureID; }
		const mat4& getTransformation() { return m_Transformation; }
	private:
		void setupDefaultUVs();
		void updateTransformation();
	protected:
		vec2 m_Position;
		vec2 m_Size;
		unsigned int m_Color;
		std::vector<vec2> m_TexCoords;
		GLuint m_TextureID;
		mat4 m_Transformation, m_Translation, m_Rotation, m_Scale;
		vec3 m_Origin;
	};
}