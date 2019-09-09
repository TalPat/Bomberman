#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;

out vec2 textureCoord;

// uniform vec3 textScale;
// uniform vec3 textTranslate;

void main()
{
	//gl_Position = vec4(textTranslate, 1.0) * vec4(textScale, 1.0) * vec4(aPos, 1.0);
	gl_Position = vec4(aPos, 1.0);
	textureCoord = aTexture;
}