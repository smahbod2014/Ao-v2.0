#include "Shader.h"
#include <iostream>
#include <vector>
#include <cassert>

namespace ao
{
	GLuint Shader::currentlyBoundID = 0;

	Shader::Shader(const char* vert, const char* frag, bool isFromFile /* = true*/)
	{
		/*
		TODO: Add Emscripten macro guards here and append "_gles" to filename
		so it doens't have to be done in the Game files
		*/

		if (isFromFile)
		{
			char* vv = read(vert);
			char* vf = read(frag);

			//Setup the shader
			setup(vv, vf);

			//Delete the file data arrays we allocted
			delete[] vv;
			delete[] vf;
		}
		else
		{
			setup(vert, frag);
		}
	}

	Shader::~Shader()
	{
		//delete shader program?
	}

	void Shader::bind()
	{
		if (m_ProgramID != currentlyBoundID)
		{
			glUseProgram(m_ProgramID);
			currentlyBoundID = m_ProgramID;
		}
	}

	void Shader::unbind()
	{
		if (currentlyBoundID != 0)
		{
			glUseProgram(0);
			currentlyBoundID = 0;
		}
	}

	char* Shader::read(const char *filename)
	{
		char* shaderFile = 0;

		//Open the file
		FILE* fp = fopen(filename, "rb");
		if (!fp)
		{
			std::cerr << "File doesn't exist [" << filename << "]" << std::endl;
			system("pause");
			std::exit(1);
		}

		//Obtain the file size
		fseek(fp, 0, SEEK_END);
		long size = ftell(fp);
		rewind(fp);

		//Alloc memory - will be deleted while setting the shader up
		shaderFile = new char[size + 1];

		//Copy the file to the shaderFile
		fread(shaderFile, sizeof(char), size, fp);
		shaderFile[size] = '\0'; //Eliminate the garbage at EOF
		fclose(fp);

		return shaderFile;
	}

	void Shader::setup(const char* vs, const char* fs)
	{
		m_ProgramID = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex, 1, &vs, NULL);
		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Failed to compile vertex shader!" << std::endl;
			printf("%s\n", &error[0]);
			glDeleteShader(vertex);
			assert(false);
		}

		glShaderSource(fragment, 1, &fs, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compile fragment shader!" << std::endl;
			printf("%s\n", &error[0]);
			glDeleteShader(fragment);
			assert(false);
		}

		glAttachShader(m_ProgramID, vertex);
		glAttachShader(m_ProgramID, fragment);

		glLinkProgram(m_ProgramID);
		glValidateProgram(m_ProgramID);

		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetProgramInfoLog(m_ProgramID, length, &length, &error[0]);
			std::cout << "Failed to link shaders!" << std::endl;
			printf("%s\n", &error[0]);
			assert(false);
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	GLint Shader::lookup(const std::string& uniformName)
	{
		auto it = m_UniformCache.find(uniformName);
		if (it == m_UniformCache.end())
		{
			//insert into cache
			m_UniformCache[uniformName] = glGetUniformLocation(m_ProgramID, uniformName.c_str());

			//std::cout << "Caching (" << m_UniformCache[uniformName] << "): " << uniformName << std::endl;
		}

		return m_UniformCache[uniformName];
	}

	void Shader::setUniform1(const std::string& uniformName, float value)
	{
		glUniform1f(lookup(uniformName), value);
	}

	void Shader::setUniform1(const std::string& uniformName, int value)
	{
		glUniform1i(lookup(uniformName), value);
	}

	void Shader::setUniform1(const std::string& uniformName, unsigned int value)
	{
		glUniform1i(lookup(uniformName), (int)value);
	}

	void Shader::setUniform2(const std::string& uniformName, const vec2& values)
	{
		glUniform2f(lookup(uniformName), values.x, values.y);
	}

	void Shader::setUniform3(const std::string& uniformName, const vec3& values)
	{
		glUniform3f(lookup(uniformName), values.x, values.y, values.z);
	}

	void Shader::setUniformMatrix4(const std::string& uniformName, const mat4& values)
	{
		glUniformMatrix4fv(lookup(uniformName), 1, GL_FALSE, &values.elements[0]);
	}
}