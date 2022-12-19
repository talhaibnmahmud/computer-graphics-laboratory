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
	void Draw(Shader& shader, Camera& camera);
};

#endif // !MESH_H
