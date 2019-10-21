#version 330 core

in vec4 positionW; // Position in world space.
in vec4 normalW; // Surface normal in world space.
in vec2 textureCoord;

// uniform vec4 LightPosW = vec4(10.0f, 5.0f, 10.0f, 1.0f); // Light's position in world space.
uniform vec4 LightPosW;
uniform vec4 LightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f); // Light's diffuse and specular contribution.

uniform vec4 Ambient = vec4(0.5f, 0.5f, 0.5f, 1.0f); // Global ambient contribution.

uniform sampler2D texture_diffuse1;

layout (location=0) out vec4 FragColor;

void main()
{
  vec4 texColor = texture(texture_diffuse1, textureCoord);
	if(texColor.a < 0.1)
		discard;
	// Compute the diffuse term.
	vec4 N = normalize(normalW);
	vec4 L = normalize(LightPosW - positionW);
	float NdotL = max(dot(N, L), 0);
	vec4 Diffuse =  NdotL * LightColour;

	FragColor = (Ambient + Diffuse) * texColor;
}