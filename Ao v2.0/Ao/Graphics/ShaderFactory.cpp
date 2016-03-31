#include "ShaderFactory.h"
#include "Shader.h"
#include "BatchRenderer2D.h"

namespace ao
{
	const char* ShaderFactory::s_DefaultShaderVert = R"(
#version 330 core

layout (location = 0) in vec3 inWorldPosition;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in float inSampler;
layout (location = 3) in vec4 inColor;

uniform mat4 projMatrix;
//uniform mat4 viewMatrix; //coming soon!

out vec2 outTexCoord;
out vec4 outColor;
out float outSampler;
 
void main()
{
	//todo: add view matrix
	gl_Position = projMatrix * vec4(inWorldPosition, 1.0);
	
	outTexCoord = inTexCoord;
	outColor = inColor;
	outSampler = inSampler;
}
)";

	const char* ShaderFactory::s_DefaultShaderFrag = R"(
#version 330 core

const int MAX_TEXTURES = 8;

in vec2 outTexCoord;
in vec4 outColor;
in float outSampler;

uniform float t;
uniform sampler2D textures[MAX_TEXTURES];

out vec4 finalColor;

void main()
{
	vec4 textureColor = outColor;
	
	if (outSampler > 0.0)
	{
		//this vertex is using a texture
		int samplerIndex = int(outSampler - 0.5);
		textureColor = outColor * texture(textures[samplerIndex], outTexCoord);
	}
	
	finalColor = textureColor;
}
)";

	const char* ShaderFactory::s_DefaultShapeShaderVert = R"(
#version 330 core

layout (location = 0) in vec3 inWorldPosition;
layout (location = 1) in vec4 inColor;

uniform mat4 projMatrix;
//uniform mat4 viewMatrix; //coming soon!

out vec4 outColor;
 
void main()
{
	//todo: add view matrix
	gl_Position = projMatrix * vec4(inWorldPosition, 1.0);
	
	outColor = inColor;
}
)";

	const char* ShaderFactory::s_DefaultShapeShaderFrag = R"(
#version 330 core

in vec4 outColor;

out vec4 finalColor;

void main()
{
	finalColor = outColor;
}
)";

	Shader* ShaderFactory::DefaultShader()
	{
		return new Shader(s_DefaultShaderVert, s_DefaultShaderFrag, false);
	}

	Shader* ShaderFactory::DefaultShapeShader()
	{
		return new Shader(s_DefaultShapeShaderVert, s_DefaultShapeShaderFrag, false);
	}
}