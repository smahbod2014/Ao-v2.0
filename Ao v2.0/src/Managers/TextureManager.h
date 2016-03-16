#pragma once

#include <string>
#include <map>
#include <GL/glew.h>
#include "../Graphics/Texture.h"

namespace ao
{
	class TextureManager
	{
	public:
		static void load(const std::string& alias, const std::string& path);
		static const Texture* get(const std::string& alias);
		static void clean();
	private:
		static std::map<const std::string, const Texture*> m_Cache;
	};
}