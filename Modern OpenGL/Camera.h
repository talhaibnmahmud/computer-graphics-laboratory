#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	glm::mat4 CameraMatrix = glm::mat4(1.0f);

	int Width, Height;
	
	bool FirstClick = true;
	float Speed = 0.01f;
	float Sensitivity = 100.0f;
	
public:
	Camera(int width, int height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
	~Camera();

	void Matrix(Shader& shader, const char* uniform);
	void UpdateMatrix(float fov, float near, float far);
	void Movement(GLFWwindow* window);
};

#endif // !CAMERA_H
