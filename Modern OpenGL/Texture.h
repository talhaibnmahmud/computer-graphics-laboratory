#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.h"


class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint unit;
public:
	Texture(const char* image, const char* textureType, GLuint textureSlot);
	~Texture();
	
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // !TEXTURE_H
