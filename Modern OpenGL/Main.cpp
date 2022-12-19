#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include <iostream>

#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "ElementBufferObject.h"


constexpr auto width = 800;
constexpr auto height = 800;



int main(int argc, char* argv[])
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f,	 0.0f,	 0.5f,		0.85f,	0.70f,	0.45f,		0.0f, 0.0f,		// lower left
		-0.5f,	 0.0f,	-0.5f,		0.85f,	0.70f,	0.45f,		5.0f, 0.0f,		// upper left
		 0.5f,	 0.0f,	-0.5f,		0.85f,	0.70f,	0.45f,		0.0f, 0.0f,		// top right
		 0.5f,	 0.0f,	 0.5f,		0.85f,	0.70f,	0.45f,		5.0f, 0.0f,		// lower right
		 0.0f,	 0.8f,	 0.0f,		0.95f,	0.85f,	0.75f,		2.5f, 5.0f,		// lower right
	};

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4,
	};

	GLFWwindow* window = glfwCreateWindow(width, height, "Modern OpenGL", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	gladLoadGL();

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;

	glViewport(0, 0, width, height);

	Shader shader("default.vert", "default.frag");
	
	VertexArrayObject vao;
	vao.Bind();

	VertexBufferObject vbo(vertices, sizeof(vertices));
	ElementBufferObject ebo(indices, sizeof(indices));
	
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	
	GLuint uniScale = glGetUniformLocation(shader.ID, "scale");

	// Texture
	Texture texture("test.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	texture.texUnit(shader, "texture0", 0);

	glClearColor(0.075f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(window);

	float rotation = 0.0f;
	double previousTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.075f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Activate();

		double currentTime = glfwGetTime();
		if (currentTime - previousTime >= 1 / 60)
		{
			rotation += 0.05f;
			previousTime = currentTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		int uniModel = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
		int uniView = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		int uniProj = glGetUniformLocation(shader.ID, "projection");
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
		
		glUniform1f(uniScale, 0.5f);
		texture.Bind();
		
		vao.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	texture.Delete();
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
}