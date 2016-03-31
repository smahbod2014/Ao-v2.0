#pragma once

#include <GL/glew.h>
#include <vector>
#include "../Math/AoMath.h"

namespace ao
{
	struct ShapeVertexData
	{
		vec3 position;
		unsigned int color;
	};

	enum ShapeType { Line, Filled };
	class Shader;
	class ShapeRenderer2D
	{
	public:
		ShapeRenderer2D();
		ShapeRenderer2D(Shader* shader);
		~ShapeRenderer2D();

		void setProjectionMatrix(const mat4& matrix);
		void begin(ShapeType shapeType);
		void drawCircle(float x, float y, float radius, unsigned int color);
		void drawLine(float x0, float y0, float x1, float y1, unsigned int color);
		void drawLine(const vec2& v0, const vec2& v1, unsigned int color);
		void drawRect(float x, float y, float width, float height, unsigned int color);
		void drawPolygon(const std::vector<vec2>& vertices, unsigned int color);
		void end();
		void flush();
	private:
		void init();
	private:
		Shader* m_Shader;
		ShapeType m_ShapeType;
		ShapeVertexData* m_Buffer;
		unsigned int* m_BufferIndices;
		GLuint m_Vao;
		GLuint m_Vbo;
		GLuint m_Ibo;
		GLuint m_IndexOffset;
		GLsizei m_IndexCount;
		//std::vector<mat4> m_TransformationStack;
		//const mat4* m_TransformationBack;

		const int VERTEX_INDEX = 0;
		const int COLOR_INDEX = 1;
	};
}