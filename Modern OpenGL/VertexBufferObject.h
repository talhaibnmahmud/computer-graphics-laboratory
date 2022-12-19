#pragma once

#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <vector>


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texCoords;
};

class VertexBufferObject
{
public:
	GLuint ID;
public:
	VertexBufferObject(std::vector<Vertex>& vertices);
	~VertexBufferObject();

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !VBO_H
