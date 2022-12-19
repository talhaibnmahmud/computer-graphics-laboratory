#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <json/json.hpp>

#include "Mesh.h"


class Model
{
private:
	const char* file;
	std::vector<unsigned char> data;
	nlohmann::json JSON;

	// Prevents textures from being loaded twice
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	// Meshes
	std::vector<Mesh> meshes;

	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;
	
private:
	std::vector<unsigned char> getData();
	std::vector<float> getFloats(nlohmann::json accessor);
	std::vector<unsigned int> getIndices(nlohmann::json accessor);
	std::vector<Texture> getTextures();

	std::vector<Vertex> assembleVertices(
		std::vector<glm::vec3> positions, 
		std::vector<glm::vec3> normals, 
		std::vector<glm::vec2> texCoords
	);

	void loadMeshes(unsigned int meshIndex);

	// Traverses a node recursively, so it essentially traverses all connected nodes
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	std::vector<glm::vec2> groupVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupVec4(std::vector<float> floatVec);
public:
	Model(const char* file);

	void Draw(Shader& shader, Camera& camera);
};

#endif // !MODEL_H