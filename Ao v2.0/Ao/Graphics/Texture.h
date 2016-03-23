#pragma once

#include <GL/glew.h>

namespace ao
{
	struct Texture
	{
		Texture(GLuint texID, unsigned long texWidth, unsigned long texHeight) : id(texID), width(texWidth), height(texHeight) {}
		~Texture()
		{
			if (id)
				glDeleteTextures(1, &id);
		}
		GLuint id = 0;
		unsigned long width, height;
	};
}