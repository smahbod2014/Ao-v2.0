#pragma once

#include <map>
#include <GL/glew.h>
#include <string>
#include "../Math/AoMath.h"

namespace ao
{
	class Shader
	{
	public:
		Shader(const char* vert, const char* frag, bool isFromFile = true);
		~Shader();

		void bind();
		void unbind();

		void setUniform1(const std::string& uniformName, float value);
		void setUniform1(const std::string& uniformName, int value);
		void setUniform1(const std::string& uniformName, unsigned int value);
		void setUniform2(const std::string& uniformName, const vec2& values);
		void setUniform3(const std::string& uniformName, const vec3& values);
		void setUniformMatrix4(const std::string& uniformName, const mat4& matrix);
	private:
		static GLuint currentlyBoundID;

		char* read(const char* filename);
		//TODO: clean up setup!
		void setup(const char* vs, const char* fs);
		GLint lookup(const std::string& uniformName);

		std::map<const std::string, GLint> m_UniformCache;
		GLuint m_ProgramID;
	};
}