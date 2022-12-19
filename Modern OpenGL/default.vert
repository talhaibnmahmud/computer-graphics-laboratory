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

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
	currentPosition = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0));
	
	Normal = aNormal;
	
	outColor = aColor;
	outTexCoord = mat2(0.0f, -1.0f, 1.0f, 0.0f) * aTexCoord;
	
	gl_Position = cameraMatrix * vec4(currentPosition, 1.0f);
}
