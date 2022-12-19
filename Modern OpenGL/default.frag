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


vec4 PointLight()
{
	float distance = length(lightPosition - currentPosition);
	
	float a = 3.0f;
	float b = 0.7f;
	float intensity = 1.0f / (a * distance * distance + b * distance + 1.0f);
	
	float ambientStrength = 0.1f;
	
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - currentPosition);
	
	float diffuse = max(dot(normal, lightDir), 0.0);
	
	float specularStrength = 0.5f;
	
	vec3 viewDir = normalize(cameraPosition - currentPosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	float specular = specularStrength * specularAmount;
	
	return texture(texture0, outTexCoord) * lightColor * (diffuse * intensity + ambientStrength + specular * intensity);
}

vec4 DirectionLight()
{
	float distance = length(lightPosition - currentPosition);
	
	float ambientStrength = 0.1f;
	
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));
	
	float diffuse = max(dot(normal, lightDir), 0.0);
	
	float specularStrength = 0.5f;
	
	vec3 viewDir = normalize(cameraPosition - currentPosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	float specular = specularStrength * specularAmount;
	
	return texture(texture0, outTexCoord) * lightColor * (diffuse + ambientStrength + specular);
}

vec4 SpotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;
	
	float ambientStrength = 0.1f;
	
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - currentPosition);
	
	float diffuse = max(dot(normal, lightDir), 0.0);
	
	float specularStrength = 0.5f;
	
	vec3 viewDir = normalize(cameraPosition - currentPosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	float specular = specularStrength * specularAmount;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);
	
	return texture(texture0, outTexCoord) * lightColor * (diffuse * intensity + ambientStrength + specular * intensity);
}

void main()
{	
	FragColor = PointLight();
}
