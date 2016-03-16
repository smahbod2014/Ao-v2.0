#pragma once

namespace ao
{
	class Shader;

	class ShaderFactory
	{
	private:
		ShaderFactory() {}
		~ShaderFactory() {}
	public:
		static Shader* DefaultShader();
	private:
		static const char *s_DefaultShaderVert;
		static const char *s_DefaultShaderFrag;
	};
}