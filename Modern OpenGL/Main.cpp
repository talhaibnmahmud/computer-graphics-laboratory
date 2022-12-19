#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <iostream>

#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "ElementBufferObject.h"


int main(int argc, char* argv[])
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f,	-0.5f,	0.0f,		1.0f,	0.0f,	0.0f,		0.0f, 0.0f,		// lower left
		-0.5f,	 0.5f,	0.0f,		0.0f,	1.0f,	0.0f,		0.0f, 1.0f,		// upper left
		 0.5f,	 0.5f,	0.0f,		0.0f,	0.0f,	1.0f,		1.0f, 1.0f,		// top right
		 0.5f,	-0.5f,	0.0f,		1.0f,	1.0f,	1.0f,		1.0f, 0.0f,		// lower right
	};

	GLuint indices[] = {
		0, 2, 1,		// first triangle
		0, 3, 2,		// second triangle
	};

	GLFWwindow* window = glfwCreateWindow(800, 600, "Modern OpenGL", nullptr, nullptr);

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

	glViewport(0, 0, 800, 600);

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
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.075f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();
		
		glUniform1f(uniScale, 0.5f);
		texture.Bind();
		
		vao.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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