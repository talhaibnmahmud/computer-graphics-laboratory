#include <GL/freeglut.h>

#include <iostream>

#include "Scene.h"

import Settings;
import Texture;


int main(int argc, char* argv[])
{
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	int screen_width = glutGet(GLUT_SCREEN_WIDTH);
	int screen_height = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((screen_width - Settings::WINDOW_WIDTH) / 2, (screen_height - Settings::WINDOW_HEIGHT) / 2);
	glutInitWindowSize(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
	glutCreateWindow(Settings::WINDOW_TITLE);

	std::cout << "OpenGL Vendor:   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_NORMALIZE);
	//glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	// Window Handling Functions (Callbacks)
	glutDisplayFunc(Control::display);
	glutReshapeFunc(Control::reshape);
	glutKeyboardFunc(Control::keyboard);
	glutKeyboardUpFunc(Control::keyboardup);
	glutSpecialFunc(Control::special);
	glutSpecialUpFunc(Control::specialup);
	glutMouseFunc(Control::mouse);
	glutMotionFunc(Control::motion);
	glutPassiveMotionFunc(Control::motion);
	glutIdleFunc(Control::idle);

	// Enter the GLUT event processing loop
	glutMainLoop();
}
