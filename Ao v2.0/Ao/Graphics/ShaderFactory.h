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
		static Shader* DefaultShapeShader();
	private:
		static const char *s_DefaultShaderVert;
		static const char *s_DefaultShaderFrag;
		static const char *s_DefaultShapeShaderVert;
		static const char *s_DefaultShapeShaderFrag;
	};
}