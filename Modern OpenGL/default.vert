#version 460 core

// Position/Coordinates
layout (location = 0) in vec3 aPos;

// Color
layout (location = 1) in vec3 aColor;

// Texture Coordinates
layout (location = 2) in vec2 aTexCoord;

// Normals
layout (location = 3) in vec3 aNormal;

out vec3 outColor;
out vec2 outTexCoord;

out vec3 Normal;
out vec3 currentPosition;

uniform mat4 cameraMatrix;
uniform mat4 model;

void main()
{
	currentPosition = vec3(model * vec4(aPos, 1.0));
	
	gl_Position = cameraMatrix * vec4(currentPosition, 1.0f);
	outColor = aColor;
	outTexCoord = aTexCoord;
	Normal = aNormal;
}
