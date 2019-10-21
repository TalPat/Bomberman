#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;

out vec2 textureCoord;

uniform mat4 scaleMat;
uniform mat4 posMat;

void main()
{
	gl_Position = posMat * scaleMat * vec4(aPos, 1.0);
	textureCoord = aTexture;
}