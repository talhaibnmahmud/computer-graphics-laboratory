#version 460 core

out vec4 FragColor;

in vec3 outColor;
in vec2 outTexCoord;

uniform sampler2D texture0;

void main()
{
	FragColor = texture(texture0, outTexCoord);
}