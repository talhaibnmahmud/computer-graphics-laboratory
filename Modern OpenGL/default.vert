#version 460 core

// Position/Coordinates
layout (location = 0) in vec3 aPos;

// Normals
layout (location = 1) in vec3 aNormal;

// Color
layout (location = 2) in vec3 aColor;

// Texture Coordinates
layout (location = 3) in vec2 aTexCoord;


out vec3 Normal;
out vec3 currentPosition;

out vec3 outColor;
out vec2 outTexCoord;

uniform mat4 cameraMatrix;
uniform mat4 model;

void main()
{
	currentPosition = vec3(model * vec4(aPos, 1.0));
	
	Normal = aNormal;
	
	outColor = aColor;
	outTexCoord = aTexCoord;
	
	gl_Position = cameraMatrix * vec4(currentPosition, 1.0f);
}
