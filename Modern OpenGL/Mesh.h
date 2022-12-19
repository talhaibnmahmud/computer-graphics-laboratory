#pragma once

#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include "Camera.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"


class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	VertexArrayObject VAO;

public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
	void Draw(
		Shader& shader, Camera& camera, 
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
};

#endif // !MESH_H
