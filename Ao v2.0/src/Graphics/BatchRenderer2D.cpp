#include "BatchRenderer2D.h"
#include "Shader.h"
#include "ShaderFactory.h"
#include "../Math/AoMath.h"
#include "Window.h"
#include "Sprite.h"
#include "Group.h"

namespace ao
{
	BatchRenderer2D::BatchRenderer2D() : BatchRenderer2D(ShaderFactory::DefaultShader())
	{

	}

	BatchRenderer2D::BatchRenderer2D(Shader* shader)
	{
		m_IndexCount = 0;
		m_Shader = shader;
		setProjectionMatrix(mat4::orthographic(0, Window::getWidth(), 0, Window::getHeight(), -1, 1));
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		if (m_Vao) glDeleteVertexArrays(1, &m_Vao);
		if (m_Vbo) glDeleteBuffers(1, &m_Vbo);
		if (m_Ibo) glDeleteBuffers(1, &m_Ibo);
		if (m_Shader) delete m_Shader;
	}

	void BatchRenderer2D::init()
	{
		glGenVertexArrays(1, &m_Vao);
		glBindVertexArray(m_Vao);

		glGenBuffers(1, &m_Vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(VERTEX_INDEX);
		glEnableVertexAttribArray(UV_INDEX);
		glEnableVertexAttribArray(SAMPLER_INDEX);
		glEnableVertexAttribArray(COLOR_INDEX);

		glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)offsetof(VertexData, position));
		glVertexAttribPointer(UV_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)offsetof(VertexData, uv));
		glVertexAttribPointer(SAMPLER_INDEX, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)offsetof(VertexData, sampler));
		glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), (const GLvoid*)offsetof(VertexData, color));

		glDisableVertexAttribArray(VERTEX_INDEX);
		glDisableVertexAttribArray(UV_INDEX);
		glDisableVertexAttribArray(SAMPLER_INDEX);
		glDisableVertexAttribArray(COLOR_INDEX);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &m_Ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);

		GLuint* indices = new GLuint[INDICES_SIZE]; //fixme

		int offset = 0;
		for (int i = 0; i < INDICES_SIZE; i += 6)
		{
			indices[i] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset;

			offset += 4;
		}

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * INDICES_SIZE, indices, GL_STATIC_DRAW);

		glBindVertexArray(0);

		delete[] indices;

		m_Shader->bind();
		for (int i = 0; i < MAX_TEXTURES; i++)
			m_Shader->setUniform1("textures[" + std::to_string(i) + "]", i);
		m_Shader->unbind();
	}

	//TODO: Check if we've already begun rendering, and if so, we need to flush and restart
	void BatchRenderer2D::setProjectionMatrix(const mat4& matrix)
	{
		m_Shader->bind();
		m_Shader->setUniformMatrix4("projMatrix", matrix);
		m_Shader->unbind();
	}

	float BatchRenderer2D::findSamplerIndex(const GLuint textureID)
	{
		float samplerIndex = 0.0f;
		if (textureID > 0)
		{
			bool found = false;
			for (size_t i = 0; i < m_Textures.size(); i++)
			{
				if (m_Textures[i] == textureID)
				{
					found = true;
					samplerIndex = (float)(i + 1);
					break;
				}
			}

			if (!found)
			{
				if (m_Textures.size() >= MAX_TEXTURES)
				{
					end();
					begin();
				}

				m_Textures.push_back(textureID);
				samplerIndex = (float)m_Textures.size();
			}
		}

		return samplerIndex;
	}

	void BatchRenderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		m_Shader->bind();
	}

	/*void BatchRenderer2D::submit(Renderable2D* renderable)
	{
		std::cout << "NOOOOO" << std::endl;
		vec3 position; // renderable->getPosition3();
		const vec2& size = renderable->getSize();
		const unsigned int color = renderable->getColor();
		const std::vector<vec2>& uvs = renderable->getUVs();
		const GLuint textureID = renderable->getTextureID();

		float samplerIndex = findSamplerIndex(textureID);

		m_Buffer->position = *m_TransformationBack * position;
		m_Buffer->uv = uvs[0];
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * vec3(position.x + size.x, position.y, position.z);
		m_Buffer->uv = uvs[1];
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->uv = uvs[2];
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * vec3(position.x, position.y + size.y, position.z);
		m_Buffer->uv = uvs[3];
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}*/

	void BatchRenderer2D::submit(Renderable2D* renderable)
	{
		const vec2& size = renderable->getSize();
		const unsigned int color = renderable->getColor();
		const std::vector<vec2>& uvs = renderable->getUVs();
		const GLuint textureID = renderable->getTextureID();

		float samplerIndex = findSamplerIndex(textureID);

		m_Buffer->position = *m_TransformationBack * vec3(0, 0, 0);
		m_Buffer->uv = uvs[0];
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * vec3(size.x, 0, 0);
		m_Buffer->uv = uvs[1];
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * vec3(size.x, size.y, 0);
		m_Buffer->uv = uvs[2];
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * vec3(0, size.y, 0);
		m_Buffer->uv = uvs[3];
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void BatchRenderer2D::drawString(const std::string& text, const vec3& position,
									 const Font& font, unsigned int color)
	{
		float samplerIndex = findSamplerIndex(font.getID());
		float x = position.x;
		const vec2& scale = font.getScale();
		
		for (size_t i = 0; i < text.length(); i++)
		{
			const char& c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(font.getFont(), &c);
			if (glyph)
			{
				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph, &c);
				}
			}
		}
		/*
		float samplerIndex =

		float x = position.x;
		const vec2& scale = font.getScale();

		for (size_t i = 0; i < text.length(); i++)
		{
		const char& c = text[i];
		ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(font.getFont(), c);
		if (glyph)
		{
		if (i > 0)
		{
		float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
		x += kerning / scale.x;
		}

		float x0 = x + glyph->offset_x / scale.x;
		float y0 = position.y + glyph->offset_y / scale.y;
		float x1 = x0 + glyph->width / scale.x;
		float y1 = y0 - glyph->height / scale.y;

		float u0 = glyph->s0;
		float v0 = glyph->t0;
		float u1 = glyph->s1;
		float v1 = glyph->t1;

		m_Buffer->position = *m_TransformationBack * vec3(x0, y0, 0.0f);
		m_Buffer->uv = vec2(u0, v0);
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * vec3(x0, y1, 0.0f);
		m_Buffer->uv = vec2(u0, v1);
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * vec3(x1, y1, 0.0f);
		m_Buffer->uv = vec2(u1, v1);
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * vec3(x1, y0, 0.0f);
		m_Buffer->uv = vec2(u1, v0);
		m_Buffer->sampler = samplerIndex;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;

		x += glyph->advance_x / scale.x;
		}
		}
		*/


	}

	void BatchRenderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		flush();
	}

	void BatchRenderer2D::flush()
	{
		glBindVertexArray(m_Vao);

		glEnableVertexAttribArray(VERTEX_INDEX);
		glEnableVertexAttribArray(UV_INDEX);
		glEnableVertexAttribArray(SAMPLER_INDEX);
		glEnableVertexAttribArray(COLOR_INDEX);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);

		for (size_t i = 0; i < m_Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_Textures[i]);
		}

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		glDisableVertexAttribArray(VERTEX_INDEX);
		glDisableVertexAttribArray(UV_INDEX);
		glDisableVertexAttribArray(SAMPLER_INDEX);
		glDisableVertexAttribArray(COLOR_INDEX);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		m_Shader->unbind();
		m_IndexCount = 0;
		m_Textures.clear();
	}
}