#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

out vec2 textureCoord;
out vec4 positionW; // Position in world space.
out vec4 normalW; // Surface normal in world space.

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	positionW = model * vec4(aPos, 1); 
	normalW = model * vec4(aNormal, 0);
	textureCoord = aTexture;
}