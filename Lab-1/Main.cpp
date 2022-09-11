#include <GL/glut.h>

#include <iostream>


constexpr auto WINDOW_WIDTH = 852;
constexpr auto WINDOW_HEIGHT = 480;


static void triangle()
{
	glBegin(GL_TRIANGLES);
	
	glColor3f(1.0f, 0.0f, 0.0f);	// Red
	glVertex2f(0.0f, 1.5f);			// Top
	glColor3f(0.0f, 1.0f, 0.0f);	// Green
	glVertex2f(-1.5f, -1.5f);		// Bottom Left
	glColor3f(0.0f, 0.0f, 1.0f);	// Blue
	glVertex2f(1.5f, -1.5f);		// Bottom Right
	
	glEnd();
}

static void display()
{
	glClearColor(0.35f, 0.45f, 0.45f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-3, 3, -3, 3);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	triangle();
	
	glFlush();
	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Lab-1");
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	std::cout << "OpenGL Vendor:   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;

	glutDisplayFunc(display);
	
	glutMainLoop();
	
	std::cin.get();
}
