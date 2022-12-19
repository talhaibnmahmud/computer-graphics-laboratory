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
	GLenum type;
	GLuint unit;
public:
	Texture(const char* image, GLenum textureType, GLuint textureSlot, GLenum format, GLenum pixelType);
	~Texture();
	
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // !TEXTURE_H
