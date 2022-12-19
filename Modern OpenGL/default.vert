#version 460 core

// Position/Coordinates
layout (location = 0) in vec3 aPos;

// Color
layout (location = 1) in vec3 aColor;

// Texture Coordinates
layout (location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 outTexCoord;

uniform mat4 cameraMatrix;

void main()
{
	gl_Position = cameraMatrix * vec4(aPos, 1.0f);
	outColor = aColor;
	outTexCoord = aTexCoord;
}