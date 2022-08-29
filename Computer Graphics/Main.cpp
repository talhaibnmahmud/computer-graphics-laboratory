#include <iostream>
#include <GLFW/glfw3.h>


int main(int argc, char **argv)
{
	GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
		
		// Draw a triangle
        glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(-0.5, -0.5);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(0.5, -0.5);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(0.0, 0.5);
		glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
	
	std::cin.get();
}
