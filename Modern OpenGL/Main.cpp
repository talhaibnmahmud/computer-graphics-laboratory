#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
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
		-0.5f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.75f,	0.3f,	0.02f,		// left
		 0.5f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.75f,	0.3f,	0.02f,		// right
		 0.0f,	 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	1.00f,	0.6f,	0.32f,		// top
		-0.25f,	 0.5f * float(sqrt(3)) / 6,		0.0f,	0.95f,	0.4f,	0.15f,		// inner left
		 0.25f,  0.5f * float(sqrt(3)) / 6,		0.0f,	0.95f,	0.4f,	0.15f,		// inner right
		 0.0f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.75f,	0.3f,	0.02f,		// inner bottom
	};

	GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1,
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
	
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	
	GLuint uniScale = glGetUniformLocation(shader.ID, "scale");

	glClearColor(0.075f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.075f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();
		
		glUniform1f(uniScale, 0.5f);
		
		vao.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
}