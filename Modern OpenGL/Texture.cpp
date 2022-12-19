#include "Texture.h"


Texture::Texture(const char* image, GLenum textureType, GLenum textureSlot, GLenum format, GLenum pixelType)
{
	type = textureType;
	
	glGenTextures(1, &ID);
	glActiveTexture(textureSlot);
	glBindTexture(type, ID);
	
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(image, &width, &height, &nrChannels, 0);
	
	if (data)
	{
		glTexImage2D(type, 0, format, width, height, 0, format, pixelType, data);
		glGenerateMipmap(type);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	
	stbi_image_free(data);
	glBindTexture(type, 0);
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
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
