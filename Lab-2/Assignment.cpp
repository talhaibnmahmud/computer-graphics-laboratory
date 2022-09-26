#include <GL/glut.h>

#include <cmath>

#include "Assignment.h"


static constexpr auto W_WIDTH = 852;
static constexpr auto W_HEIGHT = 480;

static GLfloat Txval = 0.0f, Tyval = 0.0f, Tzval = 0.0f;
static GLfloat alpha = 0.0f, theta = 0.0f;
static GLfloat axis_x = 0.0f, axis_y = 0.0f, axis_z = 0.0f;
static bool bRotate = false, uRotate = false;

static GLfloat eyeX = 2, eyeY = 0, eyeZ = 10;
static GLfloat lookX = 2, lookY = 0, lookZ = 0;

static constexpr GLfloat cube[8][3] =
{
	{0.0, 1.0, 1.0},
	{0.0, 1.0, 0.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 0.0},
	{1.0, 0.0, 1.0},
	{1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0},
	{0.0, 0.0, 0.0}
};

static constexpr GLuint indices[2][8] =
{
	{0,1,2,3,4,5,6,7},
	{3,5,1,7,0,6,2,4}
};

static void draw_sphere(GLfloat r, GLfloat g, GLfloat b)
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

	glPushMatrix();
	glTranslatef(3.5, -5.0, 4.5);
	glutSolidSphere(0.75l, 20, 16);
	glPopMatrix();
}

static void draw_cube(GLfloat r, GLfloat g, GLfloat b)
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

	glBegin(GL_QUAD_STRIP);
	for (GLint i = 0; i < 2; i++)
	{
		glVertex3fv(&cube[indices[i][0]][0]);
		glVertex3fv(&cube[indices[i][1]][0]);
		glVertex3fv(&cube[indices[i][2]][0]);
		glVertex3fv(&cube[indices[i][3]][0]);
		glVertex3fv(&cube[indices[i][4]][0]);
		glVertex3fv(&cube[indices[i][5]][0]);
		glVertex3fv(&cube[indices[i][6]][0]);
		glVertex3fv(&cube[indices[i][7]][0]);
	}

	glEnd();
}

void draw_wall()
{
	glPushMatrix();
	glTranslatef(-5.05f, -6.0f, -2.0f);
	glScalef(0.1f, 6.0f, 7.0f);
	draw_cube(0.0f, 0.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0f, -6.0f, -2.0f);
	glScalef(10.0f, 6.0f, 0.01f);
	draw_cube(0.0f, 0.0f, 1.0f);
	glPopMatrix();
}

void draw_door()
{
	glPushMatrix();
	glTranslatef(-4.5f, -6.0f, -1.9f);
	glScalef(3.5f, 5.0f, .01f);
	draw_cube(1.0f, 0.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.35f, -5.75f, -1.85f);
	glScalef(1.5f, 4.5f, .01f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.6f, -5.75f, -1.85f);
	glScalef(1.5f, 4.5f, 0.01f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.25f, -3.25f, -1.8f);
	glScalef(.05f, 0.75f, 0.1f);
	draw_cube(1.0f, 1.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.25f, -3.25f, -1.8f);
	glScalef(.05f, 0.75f, 0.1f);
	draw_cube(1.0f, 1.0f, 1.0f);
	glPopMatrix();
}

void draw_floor()
{
	glPushMatrix();
	glTranslatef(-5.0f, -6.0f, -2.0f);
	glScalef(10.0f, 0.01f, 7.0f);
	draw_cube(0.3f, 0.3f, 0.3f);
	glPopMatrix();
}

void draw_bed()
{
	// top left leg
	glPushMatrix();
	glTranslatef(-5.0f, -6.0f, 3.25f);
	glScalef(0.5f, 3.0f, 0.25f);
	draw_cube(0.6f, 0.1f, 0.1f);
	glPopMatrix();

	// top right leg
	glPushMatrix();
	glTranslatef(-5.0f, -6.0f, 0.25f);
	glScalef(0.5f, 3.0f, 0.25f);
	draw_cube(0.6f, 0.1f, 0.1f);
	glPopMatrix();

	// bottom right leg
	glPushMatrix();
	glTranslatef(0.25f, -6.0f, 0.25f);
	glScalef(0.5f, 3.0f, 0.25f);
	draw_cube(0.6f, 0.1f, 0.1f);
	glPopMatrix();

	// bottom left leg
	glPushMatrix();
	glTranslatef(0.25f, -6.0f, 3.25f);
	glScalef(0.5f, 3.0f, 0.25f);
	draw_cube(0.6f, 0.1f, 0.1f);
	glPopMatrix();

	// head plate
	glPushMatrix();
	glTranslatef(-5.0f, -5.25f, 0.25f);
	glScalef(0.5f, 1.75f, 3.0f);
	draw_cube(0.6f, 0.1f, 0.1f);
	glPopMatrix();

	// feet plate
	glPushMatrix();
	glTranslatef(0.25f, -5.25f, 0.25f);
	glScalef(0.5f, 1.75f, 3.0f);
	draw_cube(0.6f, 0.1f, 0.1f);
	glPopMatrix();

	// bed
	glPushMatrix();
	glTranslatef(-5.0f, -5.25f, 0.25f);
	glScalef(5.5f, 1.0f, 3.0f);
	draw_cube(0.6f, 0.1f, 0.1f);
	glPopMatrix();

	// matress
	glPushMatrix();
	glTranslatef(-5.0f, -4.25f, 0.25f);
	glScalef(5.5f, 0.5f, 3.0f);
	draw_cube(1.0f, 1.0f, 1.0f);
	glPopMatrix();

	// blanket
	glPushMatrix();
	glTranslatef(-3.0f, -4.20f, 0.26f);
	glScalef(3.5f, 0.51f, 3.01f);
	draw_cube(0.1f, 1.0f, 0.1f);
	glPopMatrix();

	// pillow
	glPushMatrix();
	glTranslatef(-4.5f, -3.75f, 0.75f);
	glScalef(1.25f, 0.25f, 2.0f);
	draw_cube(0.6f, 0.6f, 0.6f);
	glPopMatrix();
}

void draw_table()
{
	// top left leg
	glPushMatrix();
	glTranslatef(3.5f, -6.0f, 3.25f);
	glScalef(0.15f, 2.5f, 0.15f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	// top right leg
	glPushMatrix();
	glTranslatef(3.5f, -6.0, 0.75f);
	glScalef(0.15f, 2.5f, 0.15f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	// bottom left leg
	glPushMatrix();
	glTranslatef(4.75f, -6.0f, 3.25f);
	glScalef(0.15f, 2.5f, 0.15f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	// bottom right leg
	glPushMatrix();
	glTranslatef(4.75f, -6.0f, 0.75f);
	glScalef(0.15f, 2.5f, 0.15f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	// table top
	glPushMatrix();
	glTranslatef(3.375f, -3.65f, 0.65f);
	glScalef(1.75f, 0.15f, 3.0f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();
}

void draw_chair()
{
	// top left leg
	glPushMatrix();
	glTranslatef(2.25f, -6.0f, 3.0f);
	glScalef(0.15f, 3.0f, 0.15f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	// top right leg
	glPushMatrix();
	glTranslatef(2.25f, -6.0f, 1.75f);
	glScalef(0.15f, 3.0f, 0.15f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	// bottom left leg
	glPushMatrix();
	glTranslatef(3.75f, -6.0f, 3.0f);
	glScalef(0.15f, 1.5f, 0.15f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	// bottom right leg
	glPushMatrix();
	glTranslatef(3.75f, -6.0f, 1.75f);
	glScalef(0.15f, 1.5f, 0.15f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	// chair base
	glPushMatrix();
	glTranslatef(2.25f, -4.5f, 1.7f);
	glScalef(1.75f, 0.1f, 1.5f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();

	// chair back
	glPushMatrix();
	glTranslatef(2.25f, -3.75f, 1.7f);
	glScalef(0.1f, 0.70f, 1.5f);
	draw_cube(0.2f, 0.1f, 0.1f);
	glPopMatrix();
}

void draw_laptop()
{
	// laptop base
	glPushMatrix();
	glTranslatef(3.75f, -3.5f, 1.7f);
	glScalef(1.0f, 0.01f, 1.0f);
	draw_cube(0.0f, 0.0f, 0.0f);
	glPopMatrix();

	// laptop front
	glPushMatrix();
	glTranslatef(4.75f, -3.5f, 1.7f);
	glScalef(0.01f, 1.0f, 1.0f);
	draw_cube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
	// laptop display
	glPushMatrix();
	glTranslatef(4.74f, -3.45f, 1.75f);
	glScalef(0.01f, 0.9f, 0.9f);
	draw_cube(1.0f, 1.0f, 1.0f);
	glPopMatrix();
}

void draw_scene()
{
	draw_wall();
	draw_door();
	draw_floor();
	draw_bed();
	draw_table();
	draw_chair();
	draw_laptop();

	// draw the sphere
	draw_sphere(0.0, 1.0, 1.0);
}

void display_func()
{
	// Set the background color to mid gray
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the matrix mode to Projection
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Load the frustum
	glFrustum(-6, 6, -6, 6, 5, 200);

	// Set the matrix mode to Model View
	glMatrixMode(GL_MODELVIEW);
	// Load the identity matrix
	glLoadIdentity();
	// Set the camera
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);

	// Set the rotation
	glRotatef(alpha, axis_x, axis_y, axis_z);
	glRotatef(theta, axis_x, axis_y, axis_z);

	// Set the viewport 
	glViewport(0, 0, W_WIDTH, W_HEIGHT);

	// draw the scene
	draw_scene();

	// Flush the buffer
	glFlush();
	// Swap buffers
	glutSwapBuffers();
}

void keyboard_func(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'R':	// rotate about y-axis
		bRotate = !bRotate;
		axis_y = -1.0;
		break;
	case 'r':
		bRotate = !bRotate;
		axis_y = 1.0;
		break;
	case 'T':	// rotate about x-axis
		bRotate = !bRotate;
		axis_x = -1.0;
		break;
	case 't':
		bRotate = !bRotate;
		axis_x = 1.0;
		break;
	case 'Y':	// rotate about z-axis
		bRotate = !bRotate;
		axis_z = -1.0;
		break;
	case 'y':
		bRotate = !bRotate;
		axis_z = 1.0;
		break;

	case '+':   //zoom in
		eyeZ++;
		lookZ++;
		break;
	case '-':   //zoom out
		eyeZ--;
		lookZ--;
		break;
	case ']':   // slide up
		eyeY++;
		lookY++;
		break;
	case '[':   // slide down
		eyeY--;
		lookY--;
		break;
	case 'x':   // slide right
		eyeX++;
		lookX++;
		break;
	case 'z':   // slide left
		eyeX--;
		lookX--;
		break;

		// case 'a' for Roll left
	case 'a':
		lookX--;
		break;
		// case 'd' for Roll right
	case 'd':
		lookX++;
		break;
		// case 'w' for Pitch up
	case 'w':
		lookY++;
		break;
		// case 's' for Pitch down
	case 's':
		lookY--;
		break;
		// case 'q' for Yaw left
	case 'q':
		lookZ--;
		break;
		// case 'e' for Yaw right
	case 'e':
		lookZ++;
		break;

	case 27:	// Escape key
		exit(EXIT_SUCCESS);

	default:
		break;
	}
}

void idle_func()
{
	if (bRotate == true)
	{
		theta += 0.1f;
		if (theta > 360.0f)
			theta -= 360.0f * floor(theta / 360.0f);
	}
	if (uRotate == true)
	{
		alpha += 0.1f;
		if (alpha > 360.0f)
			alpha -= 360.0f * floor(alpha / 360.0f);
	}

	glutPostRedisplay();
}
