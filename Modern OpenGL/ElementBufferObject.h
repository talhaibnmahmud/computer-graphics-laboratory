#pragma once

#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

#include <vector>


class ElementBufferObject
{
public:
	GLuint ID;
public:
	ElementBufferObject(std::vector<GLuint>& indices);
	~ElementBufferObject();

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !EBO_H

