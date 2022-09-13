#include <GL/glut.h>

#include <iostream>

#include "Assignment.h"


constexpr auto WINDOW_WIDTH = 852;
constexpr auto WINDOW_HEIGHT = 480;


static GLfloat p_vertices[5][3] = {
	{0.0f, 0.0f, 0.0f},				//point index 0
	{0.0f, 0.0f, 2.0f},				//point index 1
	{2.0f, 0.0f, 2.0f},				//point index 2					{2.0f, 0.0f, 0.0f},  //point index 3
	{1.0f, 4.0f, 1.0f}				//point index 4
};

static GLubyte p_indices[4][3] = {
	{4, 1, 2},						// indices for drawing the triangle plane 1
	{4, 2, 3},						// indices for drawing the triangle plane 2
	{4, 3, 0},						// indices for drawing the triangle plane 3
	{4, 0, 1}						// indices for drawing the triangle plane 4
};

static GLubyte quad_indices[1][4] = {
	{0, 3, 2, 1}					// indeces for drawing the quad plane
};

static GLfloat color_values[5][3] = {
	{0.0f, 0.0f, 1.0f},				//color for point index 0
	{0.5f, 0.0f, 1.0f},				//color for point index 1
	{0.0f, 1.0f, 0.0f},				//color for point index 2
	{0.0f, 1.0f, 1.0f},				//color for point index 3
	{0.8f, 0.0f, 0.0f}				//color for point index 4
};

static void getNormal3p
(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3) {
	GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

	Ux = x2 - x1;
	Uy = y2 - y1;
	Uz = z2 - z1;

	Vx = x3 - x1;
	Vy = y3 - y1;
	Vz = z3 - z1;

	Nx = Uy * Vz - Uz * Vy;
	Ny = Uz * Vx - Ux * Vz;
	Nz = Ux * Vy - Uy * Vx;

	glNormal3f(Nx, Ny, Nz);
}

void pyramid()
{
	glBegin(GL_TRIANGLES);
	for (GLint i = 0; i < 4; i++) {
		getNormal3p(
			p_vertices[p_indices[i][0]][0], p_vertices[p_indices[i][0]][1], p_vertices[p_indices[i][0]][2],
			p_vertices[p_indices[i][1]][0], p_vertices[p_indices[i][1]][1], p_vertices[p_indices[i][1]][2],
			p_vertices[p_indices[i][2]][0], p_vertices[p_indices[i][2]][1], p_vertices[p_indices[i][2]][2]
		);

		glVertex3fv(&p_vertices[p_indices[i][0]][0]);
		glVertex3fv(&p_vertices[p_indices[i][1]][0]);
		glVertex3fv(&p_vertices[p_indices[i][2]][0]);
	}
	glEnd();

	glBegin(GL_QUADS);
	for (GLint i = 0; i < 1; i++) {
		getNormal3p(
			p_vertices[quad_indices[i][0]][0], p_vertices[quad_indices[i][0]][1], p_vertices[quad_indices[i][0]][2],
			p_vertices[quad_indices[i][1]][0], p_vertices[quad_indices[i][1]][1], p_vertices[quad_indices[i][1]][2],
			p_vertices[quad_indices[i][2]][0], p_vertices[quad_indices[i][2]][1], p_vertices[quad_indices[i][2]][2]
		);

		glVertex3fv(&p_vertices[quad_indices[i][0]][0]);
		glVertex3fv(&p_vertices[quad_indices[i][1]][0]);
		glVertex3fv(&p_vertices[quad_indices[i][2]][0]);
		glVertex3fv(&p_vertices[quad_indices[i][3]][0]);
	}
	glEnd();
}

void ownTranslatef(GLfloat dx, GLfloat dy, GLfloat dz) {
	GLfloat m[16];

	m[0] = 1;	m[4] = 0;  	 m[8] = 0;   	m[12] = dx;
	m[1] = 0; 	m[5] = 1; 	 m[9] = 0;   	m[13] = dy;
	m[2] = 0; 	m[6] = 0;	 m[10] = 1; 	m[14] = dz;
	m[3] = 0; 	m[7] = 0; 	 m[11] = 0; 	m[15] = 1;

	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(m);
}


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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Lab-1: Assignment");
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	std::cout << "OpenGL Vendor:   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;

	glutKeyboardFunc(keyboard_func);
	glutDisplayFunc(display_func);
	glutIdleFunc(idle_func);
	
	glutMainLoop();
	
	std::cin.get();
}
