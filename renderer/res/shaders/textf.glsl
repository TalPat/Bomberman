#version 330 core

in vec2 textureCoord;

uniform vec3 textColor;
uniform sampler2D texture_diffuse1;

out vec4 FragColor;

void main()
{
	vec4 texColor = texture(texture_diffuse1, textureCoord);
	if (texColor.a < 0.3)
	{
		discard;
	}
	FragColor = vec4(textColor, 1.0);
}