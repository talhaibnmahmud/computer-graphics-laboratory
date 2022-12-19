#include "Texture.h"


Texture::Texture(const char* image, const char* textureType, GLuint textureSlot)
{
	type = textureType;
	
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	unit = textureSlot;
	glBindTexture(GL_TEXTURE_2D, ID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(image, &width, &height, &nrChannels, 0);
	
	// Check what type of color channels the texture has and load it accordingly
	if (nrChannels == 4)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			data
		);
	else if (nrChannels == 3)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			data
		);
	else if (nrChannels == 1)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			data
		);
	else
		throw std::invalid_argument("Automatic Texture type recognition failed");
	
	// Generates MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	shader.Activate();
	glUniform1i(glGetUniformLocation(shader.ID, uniform), unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
