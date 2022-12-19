#include "Camera.h"


Camera::Camera(int width, int height, glm::vec3 position)
{
	Width = width;
	Height = height;
	Position = position;
}

Camera::~Camera()
{
}

void Camera::UpdateMatrix(float fov, float near, float far)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	
	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(fov), (float)Width / (float)Height, near, far);
	
	//glm::mat4 model = glm::mat4(1.0f);
	//glm::mat4 mvp = projection * view * model;

	//shader.Activate();
	CameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(CameraMatrix));
}

void Camera::Movement(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += Speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += Speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += -glm::normalize(glm::cross(Orientation, Up)) * Speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += glm::normalize(glm::cross(Orientation, Up)) * Speed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += Speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += Speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		Speed = 0.05f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		Speed = 0.01f;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
		if (FirstClick)
		{
			glfwSetCursorPos(window, Width / 2, Height / 2);
			FirstClick = false;
		}
		
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotationX = Sensitivity * (float)(mouseY - Height / 2) / Height;
		float rotationY = Sensitivity * (float)(mouseX - Width / 2) / Width;

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(rotationX), glm::normalize(glm::cross(Orientation, Up)));
		
		if (!(glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or !(glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))
		{
			Orientation = newOrientation;
		}
		
		Orientation = glm::rotate(Orientation, glm::radians(rotationY), Up);

		glfwSetCursorPos(window, Width / 2, Height / 2);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		FirstClick = true;
	}
}
