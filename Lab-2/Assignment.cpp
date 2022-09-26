#include <GL/glut.h>

#include <cmath>

#include "Assignment.h"


static constexpr auto W_WIDTH = 852;
static constexpr auto W_HEIGHT = 480;

static GLfloat Txval = 0.0f, Tyval = 0.0f, Tzval = 0.0f;
static GLfloat alpha = 0.0f, theta = 0.0f;
static GLfloat axis_x = 0.0f, axis_y = 0.0f, axis_z = 0.0f;
static bool bRotate = false, uRotate = false;

// Fan controls
static GLfloat theta_circle = 0.0f, theta_fan_rotate = 0.0f;
static bool fan_rotate = false;

// Light controls
static bool amb_light = true, dif_light = true, spec_light = true;
static bool light0 = false, light1 = false, light2 = false;

// Camera Controls
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
	GLfloat mat_shininess[] = { 90 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glPushMatrix();
	glTranslatef(3.5, -5.25, 4.5);
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
	GLfloat r = 0.0f, g = 0.4, b = 0.6;
	glPushMatrix();
	glTranslatef(-5.05f, -6.0f, -2.0f);
	glScalef(0.1f, 6.0f, 7.0f);
	draw_cube(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0f, -6.0f, -2.0f);
	glScalef(10.0f, 6.0f, 0.01f);
	draw_cube(r, g, b);
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
	GLfloat r = 0.5, g = 0.5, b = 0.5;

	glPushMatrix();
	glTranslatef(-5.0f, -6.0f, -2.0f);
	glScalef(10.0f, 0.01f, 7.0f);
	draw_cube(r, g, b);
	glPopMatrix();

	// Draw the roof
	glPushMatrix();
	glTranslatef(-5.0f, 0.0f, -2.0f);
	glScalef(10.0f, 0.01f, 7.0f);
	draw_cube(r, g, b);
	glPopMatrix();
}

void draw_bed()
{
	GLfloat r = 0.5137f, g = 0.4118f, b = 0.3255f;
	// top left leg
	glPushMatrix();
	glTranslatef(-5.0f, -6.0f, 3.25f);
	glScalef(0.5f, 3.0f, 0.25f);
	draw_cube(r, g, b);
	glPopMatrix();

	// top right leg
	glPushMatrix();
	glTranslatef(-5.0f, -6.0f, 0.25f);
	glScalef(0.5f, 3.0f, 0.25f);
	draw_cube(r, g, b);
	glPopMatrix();

	// bottom right leg
	glPushMatrix();
	glTranslatef(0.25f, -6.0f, 0.25f);
	glScalef(0.5f, 3.0f, 0.25f);
	draw_cube(r, g, b);
	glPopMatrix();

	// bottom left leg
	glPushMatrix();
	glTranslatef(0.25f, -6.0f, 3.25f);
	glScalef(0.5f, 3.0f, 0.25f);
	draw_cube(r, g, b);
	glPopMatrix();

	// head plate
	glPushMatrix();
	glTranslatef(-5.0f, -5.25f, 0.25f);
	glScalef(0.5f, 1.75f, 3.0f);
	draw_cube(r, g, b);
	glPopMatrix();

	// feet plate
	glPushMatrix();
	glTranslatef(0.25f, -5.25f, 0.25f);
	glScalef(0.5f, 1.75f, 3.0f);
	draw_cube(r, g, b);
	glPopMatrix();

	// bed
	glPushMatrix();
	glTranslatef(-5.0f, -5.25f, 0.25f);
	glScalef(5.5f, 1.0f, 3.0f);
	draw_cube(r, g, b);
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
	draw_cube(0.46f, 0.86f, 0.46f);
	glPopMatrix();

	// pillow
	glPushMatrix();
	glTranslatef(-4.5f, -3.75f, 0.75f);
	glScalef(1.25f, 0.25f, 2.0f);
	draw_cube(0.55f, 0.35f, 0.15f);
	glPopMatrix();
}

void draw_table()
{
	GLfloat r = 0.625f, g = 0.25f, b = 0.0f;
	// top left leg
	glPushMatrix();
	glTranslatef(3.5f, -6.0f, 3.25f);
	glScalef(0.15f, 2.5f, 0.15f);
	draw_cube(r, g, b);
	glPopMatrix();

	// top right leg
	glPushMatrix();
	glTranslatef(3.5f, -6.0, 0.75f);
	glScalef(0.15f, 2.5f, 0.15f);
	draw_cube(r, g, b);
	glPopMatrix();

	// bottom left leg
	glPushMatrix();
	glTranslatef(4.75f, -6.0f, 3.25f);
	glScalef(0.15f, 2.5f, 0.15f);
	draw_cube(r, g, b);
	glPopMatrix();

	// bottom right leg
	glPushMatrix();
	glTranslatef(4.75f, -6.0f, 0.75f);
	glScalef(0.15f, 2.5f, 0.15f);
	draw_cube(r, g, b);
	glPopMatrix();

	// table top
	glPushMatrix();
	glTranslatef(3.375f, -3.65f, 0.65f);
	glScalef(1.75f, 0.15f, 3.0f);
	draw_cube(r, g, b);
	glPopMatrix();
}

void draw_chair()
{
	GLfloat r = 0.9f, g = 0.65f, b = 0.4f;
	// top left leg
	glPushMatrix();
	glTranslatef(2.25f, -6.0f, 3.0f);
	glScalef(0.15f, 3.0f, 0.15f);
	draw_cube(r, g, b);
	glPopMatrix();

	// top right leg
	glPushMatrix();
	glTranslatef(2.25f, -6.0f, 1.75f);
	glScalef(0.15f, 3.0f, 0.15f);
	draw_cube(r, g, b);
	glPopMatrix();

	// bottom left leg
	glPushMatrix();
	glTranslatef(3.75f, -6.0f, 3.0f);
	glScalef(0.15f, 1.5f, 0.15f);
	draw_cube(r, g, b);
	glPopMatrix();

	// bottom right leg
	glPushMatrix();
	glTranslatef(3.75f, -6.0f, 1.75f);
	glScalef(0.15f, 1.5f, 0.15f);
	draw_cube(r, g, b);
	glPopMatrix();

	// chair base
	glPushMatrix();
	glTranslatef(2.25f, -4.5f, 1.7f);
	glScalef(1.75f, 0.1f, 1.5f);
	draw_cube(r, g, b);
	glPopMatrix();

	// chair back
	glPushMatrix();
	glTranslatef(2.25f, -3.75f, 1.7f);
	glScalef(0.1f, 0.70f, 1.5f);
	draw_cube(r, g, b);
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

void draw_fan()
{
	GLfloat r = 1.0f, g = 1.0f, b = 1.0f;

	// fan base
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glScalef(0.2, 1.0, 0.2);
	draw_cube(r, g, b);
	glPopMatrix();

	r = 0.7f, g = 0.4f, b = 0.4f;

	// fan blades
	glPushMatrix();
	glRotatef(theta_fan_rotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, -1.0f, 0.0f);
	glScalef(0.4f, 0.4f, 0.4f);

	/*for (int i = 0; i < 180; i++) {
		glPushMatrix();
		glScalef(2.0, 0.5, 1.0);
		glRotatef(theta_circle += 2.0, 0.0, 1.0, 0.0);

		draw_cube(r, g, b);
		glPopMatrix();
	}*/

	GLfloat scale_x = 4.5f, scale_y = 0.3f, scale_z = 1.75f;

	glPushMatrix();
	glScalef(scale_x, scale_y, scale_z);
	draw_cube(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
	glScalef(scale_x, scale_y, scale_z);
	draw_cube(r, g, b);
	glPopMatrix();

	glPushMatrix();
	glRotatef(240.0f, 0.0f, 1.0f, 0.0f);
	glScalef(scale_x, scale_y, scale_z);
	draw_cube(r, g, b);
	glPopMatrix();

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
	draw_sphere(0.415f, 0.051f, 0.675f);

	// draw the fan
	draw_fan();
}

static void light(
	GLfloat x, GLfloat y, GLfloat z,
	GLenum light,
	bool toggle,
	bool spot)
{
	GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
	GLfloat light_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat light_position[] = { x, y, z, 1.0 };

	glEnable(light);

	if (toggle) {

		if (amb_light) glLightfv(light, GL_AMBIENT, light_ambient);
		else glLightfv(light, GL_AMBIENT, no_light);

		if (dif_light) glLightfv(light, GL_DIFFUSE, light_diffuse);
		else glLightfv(light, GL_DIFFUSE, no_light);

		if (spec_light) glLightfv(light, GL_SPECULAR, light_specular);
		else glLightfv(light, GL_SPECULAR, no_light);

		glLightfv(light, GL_POSITION, light_position);
	}
	else {
		glLightfv(light, GL_AMBIENT, no_light);
		glLightfv(light, GL_DIFFUSE, no_light);
		glLightfv(light, GL_SPECULAR, no_light);
		glLightfv(light, GL_POSITION, no_light);
	}

	if (spot) {
		GLfloat spot_direction[] = { -1.0, 0.0, 0.0 };
		glLightfv(light, GL_SPOT_DIRECTION, spot_direction);
		glLightf(light, GL_SPOT_CUTOFF, 55);
	}
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
	glFrustum(-6, 6, -6, 6, 6, 100);

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

	// Lights
	light(-22, -10, -20, GL_LIGHT0, light0, false);
	light(4.5, -11, -50.0, GL_LIGHT1, light1, false);
	light(26, -22, -28, GL_LIGHT2, light2, true);

	// Flush the buffer
	glFlush();
	// Swap buffers
	glutSwapBuffers();
}

void keyboard_func(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'Y':	// rotate about y-axis
		bRotate = !bRotate;
		axis_y = -1.0;
		break;
	case 'y':
		bRotate = !bRotate;
		axis_y = 1.0;
		break;
	case 'X':	// rotate about x-axis
		bRotate = !bRotate;
		axis_x = -1.0;
		break;
	case 'x':
		bRotate = !bRotate;
		axis_x = 1.0;
		break;
	case 'Z':	// rotate about z-axis
		bRotate = !bRotate;
		axis_z = -1.0;
		break;
	case 'z':
		bRotate = !bRotate;
		axis_z = 1.0;
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

		// Fan rotation
	case 'f':
		fan_rotate = !fan_rotate;
		break;

		// Light Controls
	case '0':
		light0 = !light0;
		break;
	case '1':
		light1 = !light1;
		break;
	case '2':
		light2 = !light2;
		break;

	case 27:	// Escape key
		exit(EXIT_SUCCESS);

	default:
		break;
	}
}

void special_func(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		eyeY--;
		lookY--;
		break;
	case GLUT_KEY_DOWN:
		eyeY++;
		lookY++;
		break;
	case GLUT_KEY_LEFT:
		eyeX++;
		lookX++;
		break;
	case GLUT_KEY_RIGHT:
		eyeX--;
		lookX--;
		break;
	case GLUT_KEY_PAGE_UP:
		eyeZ--;
		lookZ--;
		break;
	case GLUT_KEY_PAGE_DOWN:
		eyeZ++;
		lookZ++;
		break;
	default:
		break;
	}
}

void idle_func()
{
	if (bRotate)
	{
		theta += 0.5f;
		if (theta >= 360.0f) theta = 0.0f;
	}
	if (uRotate)
	{
		alpha += 0.5f;
		if (alpha >= 360.0f) alpha = 0.0f;
	}

	if (fan_rotate)
	{
		theta_fan_rotate += 5.0f;
		if (theta_fan_rotate > 360.0f) theta_fan_rotate = 0.0f;
	}

	glutPostRedisplay();
}
