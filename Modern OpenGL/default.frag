#version 460 core

out vec4 FragColor;

in vec3 outColor;
in vec2 outTexCoord;

in vec3 Normal;
in vec3 currentPosition;

uniform sampler2D texture0;

uniform vec4 lightColor;
uniform vec3 lightPosition;

void main()
{
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - currentPosition);
	
	float diffuse = max(dot(normal, lightDir), 0.0);
	
	FragColor = texture(texture0, outTexCoord) * lightColor * diffuse;
}