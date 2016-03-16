#version 330 core

const int MAX_TEXTURES = 32;

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