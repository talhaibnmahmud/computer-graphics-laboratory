#version 460 core

// Position/Coordinates
layout (location = 0) in vec3 aPos;

// Color
layout (location = 1) in vec3 aColor;

// Texture Coordinates
layout (location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 outTexCoord;

// Scale Control
uniform float scale;

void main()
{
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	outColor = aColor;
	outTexCoord = aTexCoord;
}