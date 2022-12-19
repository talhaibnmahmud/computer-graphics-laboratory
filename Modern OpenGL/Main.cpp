#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

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
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("test.png", &width, &height, &nrChannels, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture wrapping for flat borders
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint uniTexture = glGetUniformLocation(shader.ID, "texture0");
	shader.Activate();
	glUniform1i(uniTexture, 0);

	glClearColor(0.075f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.075f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();
		
		glUniform1f(uniScale, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		vao.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	glDeleteTextures(1, &texture);
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
}