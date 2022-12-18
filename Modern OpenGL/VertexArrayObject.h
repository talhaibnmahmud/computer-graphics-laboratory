#pragma once

#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include "VertexBufferObject.h"

class VertexArrayObject
{
public:
	GLuint ID;
public:
	VertexArrayObject();
	~VertexArrayObject();

	void LinkAttrib(VertexBufferObject& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // !VAO_H
