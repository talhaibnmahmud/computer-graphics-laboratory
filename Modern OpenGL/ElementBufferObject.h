#pragma once

#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
class ElementBufferObject
{
public:
	GLuint ID;
public:
	ElementBufferObject(GLuint* indices, GLsizeiptr size);
	~ElementBufferObject();

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !EBO_H

