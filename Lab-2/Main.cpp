#include <GL/freeglut_std.h>

#include <iostream>

#include "Assignment.h"


constexpr auto WINDOW_WIDTH = 700;
constexpr auto WINDOW_HEIGHT = 700;


static GLdouble Txval = 0, Tyval = 0, Tzval = 0;
// static double windowHeight = 700, windowWidth = 700;
static GLfloat alpha = 0.0, theta = 0.0, axis_x = 0.0, axis_y = 0.0;
static bool bRotate = false, uRotate = false;


static GLfloat v_pyramid[5][3] =
{
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 2.0f},
	{2.0f, 0.0f, 2.0f},
	{2.0f, 0.0f, 0.0f},
	{1.0f, 4.0f, 1.0f}
};

static GLuint p_Indices[4][3] =
{
	{4, 1, 2},
	{4, 2, 3},
	{4, 3, 0},
	{4, 0, 1}
};

static GLuint quadIndices[1][4] = { {0, 3, 2, 1} };

static GLfloat colors[5][3] =
{
	{0.0f, 0.0f, 1.0f},
	{0.5f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 1.0f},
	{0.8f, 0.0f, 0.0f}
};

static void getNormal3p(
	GLfloat x1, GLfloat y1, GLfloat z1,
	GLfloat x2, GLfloat y2, GLfloat z2,
	GLfloat x3, GLfloat y3, GLfloat z3)
{
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

void drawpyramid(GLfloat r, GLfloat g, GLfloat b)
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { r, g, b, 1.0 };
	GLfloat mat_diffuse[] = { r, g, b, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 60 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	/*glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	for (GLint i = 0; i < 4; i++)
	{
		glColor3f(colors[i][0], colors[i][1], colors[i][2]);
		getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
			v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
			v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);

		glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
		glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
		glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
	}
	glEnd();

	glBegin(GL_QUADS);
	for (GLint i = 0; i < 1; i++)
	{
		glColor3f(colors[4][0], colors[4][1], colors[4][2]);
		getNormal3p(v_pyramid[quadIndices[i][0]][0], v_pyramid[quadIndices[i][0]][1], v_pyramid[quadIndices[i][0]][2],
			v_pyramid[quadIndices[i][1]][0], v_pyramid[quadIndices[i][1]][1], v_pyramid[quadIndices[i][1]][2],
			v_pyramid[quadIndices[i][2]][0], v_pyramid[quadIndices[i][2]][1], v_pyramid[quadIndices[i][2]][2]);

		glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
		glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
		glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
		glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
	}
	glEnd();*/

	glutSolidSphere(2.0, 20, 16);
}

static void light()
{
	//GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light0_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_position[] = { 0.0, 50.0, 0.0, 1.0 };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);


	GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);

	GLfloat light1_ambient[] = { 0.3, 0.3, 0.0, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat light1_position[] = { 10.0, 0.0, 0.0, 1.0 };

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	GLfloat light2_ambient[] = { 0.0, 0.0, 0.3, 1.0 };
	GLfloat light2_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat light2_specular[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat light2_position[] = { 0.0, 0.0, -50.0, 1.0 };

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-5, 5, -5, 5, 4, 50);
	 gluPerspective(60, 1, 5, 100);
	// glOrtho(-5,5,-5,5, 4, 50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 1, 10, 2, 0, 0, 0, 1, 0);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPushMatrix();
	glTranslatef(1.5, 0, 0);
	glRotatef(alpha, axis_x, axis_y, 0.0);
	glRotatef(theta, axis_x, axis_y, 0.0);
	drawpyramid(1.0f, 0.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.5, 0, 0);
	glRotatef(alpha, axis_x, axis_y, 0.0);
	glRotatef(theta, axis_x, axis_y, 0.0);
	drawpyramid(0.0f, 1.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.5, 0, 0);
	glRotatef(alpha, axis_x, axis_y, 0.0);
	glRotatef(theta, axis_x, axis_y, 0.0);
	drawpyramid(.5f, 0.5f, .5f);
	glPopMatrix();

	//glPushMatrix();
	////glTranslatef(0,0,Tzval);
	//ownTranslatef(10,0,0);
	//glRotatef( alpha,axis_x, axis_y, 0.0 );
	//glRotatef( theta, axis_x, axis_y, 0.0 );
	//drawpyramid();
	//glPopMatrix();

	glFlush();
	glutSwapBuffers();
}
static void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
	case 'S':
		bRotate = !bRotate;
		uRotate = false;
		axis_x = 0.0;
		axis_y = 1.0;
		break;

	case 'r':
	case 'R':
		uRotate = !uRotate;
		bRotate = false;
		axis_x = 1.0;
		axis_y = 0.0;
		break;
	case '+':
		Tzval += 0.2;
		break;

	case '-':
		Tzval -= 0.2;
		break;

	case 27:	// Escape key
		exit(EXIT_SUCCESS);
	}
}

static void animate()
{
	if (bRotate == true)
	{
		theta += 0.8;
		if (theta > 360.0)
			theta -= 360.0 * floor(theta / 360.0);
	}

	if (uRotate == true)
	{
		alpha += 0.8;
		if (alpha > 360.0)
			alpha -= 360.0 * floor(alpha / 360.0);
	}
	glutPostRedisplay();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Lab-2: Lighting & Material Properties");

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

	glEnable(GL_LIGHTING);

	//light();

	std::cout << "OpenGL Vendor:   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;

	glutKeyboardFunc(keyboard_func);
	glutDisplayFunc(display_func);
	glutIdleFunc(idle_func);
	glutSpecialFunc(special_func);

	glutMainLoop();

	std::cin.get();
}
