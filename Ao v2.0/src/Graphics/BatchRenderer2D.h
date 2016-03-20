#pragma once

#include <GL/glew.h>
#include <vector>
//#include <freetype-gl/freetype-gl.h>
#include "../freetype-gl-old/freetype-gl.h"

#include "Renderer2D.h"
#include "Renderable2D.h"

#define MAX_SPRITES 60000
#define MAX_TEXTURES 8
#define BUFFER_SIZE sizeof(VertexData) * 4 * MAX_SPRITES
#define INDICES_SIZE MAX_SPRITES * 6

#define VERTEX_INDEX 0
#define UV_INDEX 1
#define SAMPLER_INDEX 2
#define COLOR_INDEX 3

namespace ao
{
	class vec3;
	class Shader;
	class Sprite;
	class Group;

	class BatchRenderer2D : public Renderer2D
	{
	public:
		BatchRenderer2D();
		BatchRenderer2D(Shader* shader);
		virtual ~BatchRenderer2D();

		virtual void begin() override;
		virtual void submit(Renderable2D* renderable) override;
		virtual void drawString(const std::string& text, const vec3& position, const Font& font, unsigned int color) override;
		virtual void end() override;
		virtual void flush() override;

		void setProjectionMatrix(const mat4& matrix);
	private:
		void init();
		float findSamplerIndex(const GLuint textureID);

		GLuint m_Vao;
		GLuint m_Vbo;
		GLuint m_Ibo;
		GLsizei m_IndexCount;
		VertexData* m_Buffer = nullptr;
		std::vector<GLuint> m_Textures;
		Shader* m_Shader;
		mat4 m_ProjectionMatrix;
	};
}