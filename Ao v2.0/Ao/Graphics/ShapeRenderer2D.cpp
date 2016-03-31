#include "ShapeRenderer2D.h"
#include "ShaderFactory.h"
#include "Shader.h"
#include "../Math/MathUtils.h"
#include "Window.h"

namespace ao
{
	ShapeRenderer2D::ShapeRenderer2D() : ShapeRenderer2D(ShaderFactory::DefaultShapeShader())
	{

	}

	ShapeRenderer2D::ShapeRenderer2D(Shader* shader)
	{
		m_Shader = shader;
		setProjectionMatrix(mat4::orthographic(0, Window::getWidth(), 0, Window::getHeight(), -1, 1));
		init();
	}

	ShapeRenderer2D::~ShapeRenderer2D()
	{
		if (m_Vao) glDeleteVertexArrays(1, &m_Vao);
		if (m_Vbo) glDeleteBuffers(1, &m_Vbo);
		if (m_Ibo) glDeleteBuffers(1, &m_Ibo);
		if (m_Shader) delete m_Shader;
	}

	void ShapeRenderer2D::init()
	{
		glGenVertexArrays(1, &m_Vao);
		glBindVertexArray(m_Vao);

		glGenBuffers(1, &m_Vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, 100000, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(VERTEX_INDEX);
		glEnableVertexAttribArray(COLOR_INDEX);

		glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertexData), (const GLvoid*)offsetof(ShapeVertexData, position));
		glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ShapeVertexData), (const GLvoid*)offsetof(ShapeVertexData, color));

		glDisableVertexAttribArray(VERTEX_INDEX);
		glDisableVertexAttribArray(COLOR_INDEX);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &m_Ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 100000, NULL, GL_DYNAMIC_DRAW);

		glBindVertexArray(0);
	}

	//TODO: Check if we've already begun rendering, and if so, we need to flush and restart
	void ShapeRenderer2D::setProjectionMatrix(const mat4& matrix)
	{
		m_Shader->bind();
		m_Shader->setUniformMatrix4("projMatrix", matrix);
		m_Shader->unbind();
	}

	void ShapeRenderer2D::begin(ShapeType shapeType)
	{
		m_ShapeType = shapeType;
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		m_Buffer = (ShapeVertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		m_BufferIndices = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		m_Shader->bind();
	}

	void ShapeRenderer2D::drawCircle(float x, float y, float radius, unsigned int color)
	{
		//temporary
		const int SEGMENTS = 20;

		if (m_ShapeType == ShapeType::Line)
		{
			for (int i = 0; i < SEGMENTS; i++)
			{
				float theta = i * (2 * PI / SEGMENTS);
				float xPos = x + cosf(theta) * radius;
				float yPos = y + sinf(theta) * radius;

				m_Buffer->position = /**m_TransformationBack * */ vec3(xPos, yPos, 0);
				m_Buffer->color = color;
				m_Buffer++;

				*(m_BufferIndices++) = m_IndexOffset + i;
				if (i < SEGMENTS - 1)
				{
					*(m_BufferIndices++) = m_IndexOffset + i + 1;
				}
				else
				{
					*(m_BufferIndices++) = m_IndexOffset;
				}
			}

			m_IndexOffset += SEGMENTS;
			m_IndexCount += SEGMENTS * 2;
		}
		else if (m_ShapeType == ShapeType::Filled)
		{
			m_Buffer->position = vec3(x, y, 0);
			m_Buffer->color = color;
			m_Buffer++;

			for (int i = 0; i < SEGMENTS; i++)
			{
				float theta = i * (2 * PI / SEGMENTS);
				float xPos = x + cosf(theta) * radius;
				float yPos = y + sinf(theta) * radius;

				m_Buffer->position = vec3(xPos, yPos, 0);
				m_Buffer->color = color;
				m_Buffer++;

				*(m_BufferIndices++) = m_IndexOffset;
				*(m_BufferIndices++) = m_IndexOffset + i + 1;
				if (i < SEGMENTS - 1)
				{
					*(m_BufferIndices++) = m_IndexOffset + i + 2;
				}
				else
				{
					*(m_BufferIndices++) = m_IndexOffset + 1;
				}
			}

			m_IndexOffset += SEGMENTS + 1;
			m_IndexCount += SEGMENTS * 3;
		}
	}

	void ShapeRenderer2D::drawLine(float x0, float y0, float x1, float y1, unsigned int color)
	{
		if (m_ShapeType == ShapeType::Line)
		{
			m_Buffer->position = vec3(x0, y0, 0);
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->position = vec3(x1, y1, 0);
			m_Buffer->color = color;
			m_Buffer++;

			*(m_BufferIndices++) = m_IndexOffset;
			*(m_BufferIndices++) = m_IndexOffset + 1;

			m_IndexOffset += 2;
			m_IndexCount += 2;
		}
	}

	void ShapeRenderer2D::drawLine(const vec2& v0, const vec2& v1, unsigned int color)
	{
		drawLine(v0.x, v0.y, v1.x, v1.y, color);
	}

	void ShapeRenderer2D::drawRect(float x, float y, float width, float height, unsigned int color)
	{
		m_Buffer->position = vec3(x, y, 0);
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = vec3(x + width, y, 0);
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = vec3(x + width, y + height, 0);
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = vec3(x, y + height, 0);
		m_Buffer->color = color;
		m_Buffer++;

		if (m_ShapeType == ShapeType::Line)
		{
			*(m_BufferIndices++) = m_IndexOffset;
			*(m_BufferIndices++) = m_IndexOffset + 1;
			*(m_BufferIndices++) = m_IndexOffset + 1;
			*(m_BufferIndices++) = m_IndexOffset + 2;
			*(m_BufferIndices++) = m_IndexOffset + 2;
			*(m_BufferIndices++) = m_IndexOffset + 3;
			*(m_BufferIndices++) = m_IndexOffset + 3;
			*(m_BufferIndices++) = m_IndexOffset;

			m_IndexOffset += 4;
			m_IndexCount += 8;
		}
		else if (m_ShapeType == ShapeType::Filled)
		{
			*(m_BufferIndices++) = m_IndexOffset;
			*(m_BufferIndices++) = m_IndexOffset + 1;
			*(m_BufferIndices++) = m_IndexOffset + 2;
			*(m_BufferIndices++) = m_IndexOffset + 2;
			*(m_BufferIndices++) = m_IndexOffset + 3;
			*(m_BufferIndices++) = m_IndexOffset;

			m_IndexOffset += 4;
			m_IndexCount += 6;
		}
	}

	void ShapeRenderer2D::drawPolygon(const std::vector<vec2>& vertices, unsigned int color)
	{
		if (m_ShapeType == ShapeType::Line)
			for (int i = 0; i < vertices.size(); i++)
				drawLine(vertices[i], vertices[(i + 1) % vertices.size()], color);
	}

	void ShapeRenderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		flush();
	}

	void ShapeRenderer2D::flush()
	{
		glBindVertexArray(m_Vao);

		glEnableVertexAttribArray(VERTEX_INDEX);
		glEnableVertexAttribArray(COLOR_INDEX);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);

		if (m_ShapeType == ShapeType::Line)
		{
			glDrawElements(GL_LINES, m_IndexCount, GL_UNSIGNED_INT, NULL);
		}
		else if (m_ShapeType == ShapeType::Filled)
		{
			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);
		}

		glDisableVertexAttribArray(VERTEX_INDEX);
		glDisableVertexAttribArray(COLOR_INDEX);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		m_Shader->unbind();
		m_IndexCount = 0;
		m_IndexOffset = 0;
	}
}