#pragma once

#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>


class VertexBufferObject
{
public:
	GLuint ID;
public:
	VertexBufferObject(GLfloat* vertices, GLsizeiptr size);
	~VertexBufferObject();

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !VBO_H
