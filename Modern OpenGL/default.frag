#version 460 core

out vec4 FragColor;

in vec3 outColor;
in vec2 outTexCoord;

in vec3 Normal;
in vec3 currentPosition;

uniform sampler2D texture0;

uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
	float ambientStrength = 0.1f;
	
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - currentPosition);
	
	float diffuse = max(dot(normal, lightDir), 0.0);
	
	float specularStrength = 0.5f;
	
	vec3 viewDir = normalize(cameraPosition - currentPosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	float specular = specularStrength * specularAmount;
	
	FragColor = texture(texture0, outTexCoord) * lightColor * (diffuse + ambientStrength + specular);
}