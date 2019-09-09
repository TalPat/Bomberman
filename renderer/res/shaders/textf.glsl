#version 330 core

in vec2 textureCoord;

//uniform vec3 textColor;
vec3 textColor = vec3(1.0, 0.0, 0.0);
uniform sampler2D texture_diffuse1;

layout (location=0) out vec4 FragColor;

void main()
{
	vec4 texColor = texture(texture_diffuse1, textureCoord);
	// if (texColor.a < 0.1)
	// {
	// 	discard;
	// }
	FragColor = vec4(textColor, 1.0);
}