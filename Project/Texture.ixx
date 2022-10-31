#include "BMPLoader.h"

export module Texture;


export namespace Texture {
	// Texture types
	enum Type
	{
		Diffuse,
		Normal,
		Specular,
		Emissive,
		Height,
		Opacity,
		Displacement,
		Lightmap,
		Reflection,
		Unknown
	};

	void LoadTexture(std::string& filename, unsigned int& ID)
	{
		glBindTexture(GL_TEXTURE_2D, ID);

		glPixelStorei(GL_UNPACK_ALIGNMENT, ID);

		BMPLoader bmp(filename);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.m_Width, bmp.m_Height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.m_Data);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bmp.m_Width, bmp.m_Height, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.m_Data);
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
