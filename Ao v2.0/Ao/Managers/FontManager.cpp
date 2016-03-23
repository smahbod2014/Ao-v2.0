#include "FontManager.h"
#include "../Graphics/Font.h"
#include <iostream>

namespace ao
{
	std::map<const std::string, Font*> FontManager::m_Cache;

	void FontManager::load(const std::string& alias, const std::string& filepath, float size)
	{
		add(alias, new Font(filepath, size));
	}

	void FontManager::add(const std::string& alias, Font* font)
	{
		auto it = m_Cache.find(alias);
		if (it != m_Cache.end())
			return;

		m_Cache[alias] = font;
	}

	Font* FontManager::get(const std::string& alias)
	{
		auto it = m_Cache.find(alias);
		if (it == m_Cache.end())
			return nullptr;

		return m_Cache[alias];
	}

	void FontManager::clean()
	{
		for (auto& it : m_Cache)
			delete it.second;

		m_Cache.clear();
	}

	void FontManager::initDefaultFonts()
	{
		int offset = 0;
		int chunks1[] = { 30016, 30000, 5268 };
		char buff1[65284] = {};

		int chunks2[] = { 30016, 30000, 30000, 30000, 30000, 30000, 30000, 30000,
			30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000,
			30000, 30000, 30000, 30000, 30000, 30000, 30000, 23836 };
		char buff2[773852] = {};

		for (int i = 0; i < 3; i++)
		{
			memcpy(buff1 + offset, Font::s_DefaultFont1[i], chunks1[i]);
			offset += chunks1[i];
		}

		offset = 0;
		for (int i = 0; i < 26; i++)
		{
			memcpy(buff2 + offset, Font::s_DefaultFont2[i], chunks2[i]);
			offset += chunks2[i];
		}

		m_Cache["magnetob"] = new Font(buff1, 35.0f, 65284);
		//m_Cache["arial"] = new Font(buff2, 35.0f, 773852);

		std::cout << "Instantiated default fonts" << std::endl;
	}
}