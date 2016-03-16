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