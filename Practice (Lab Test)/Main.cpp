#include <GL/glut.h>

#include <array>
#include <iostream>

static constexpr auto WINDOW_WIDTH = 1280;
static constexpr auto WINDOW_HEIGHT = 720;
static constexpr auto WINDOW_TITLE = "Lab Test";


// Control Functions
static void display();
static void reshape(int width, int height);
static void keyboard(unsigned char key, int x, int y);
static void keyboardup(unsigned char key, int x, int y);
static void special(int key, int x, int y);
static void specialup(int key, int x, int y);
static void idle();

// Key States
static std::array<bool, 256> keyStates = { false };

// Camera Variables
static GLfloat cameraX = 0.0f;
static GLfloat cameraY = 0.0f;
static GLfloat cameraZ = 50.0f;

static GLfloat lookX = 0.0f;
static GLfloat lookY = 0.0f;
static GLfloat lookZ = 0.0f;

static GLfloat upX = 0.0f;
static GLfloat upY = 1.0f;
static GLfloat upZ = 0.0f;

// Rotation around the axes
static GLfloat angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;
static GLfloat axisX = 0.0f, axisY = 0.0f, axisZ = 0.0f;
static bool rotateX = false, rotateY = false, rotateZ = false;


static void cylinder(GLfloat r=1, GLfloat g=1, GLfloat b=1) {
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glPushMatrix();
	glColor3f(r, g, b);
	glRotatef(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 1, 2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	gluDisk(gluNewQuadric(), 0, 1, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -2, 0);
	glRotatef(90, 1, 0, 0);
	gluDisk(gluNewQuadric(), 0, 1, 100, 100);
	glPopMatrix();
	glPopMatrix();
}

void A() {
	/*glPushMatrix();
	glTranslatef(0, 4, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(2, 2, 100, 100);
	glPopMatrix();*/
	
	glPushMatrix();
	glTranslatef(-2.35, 0, 0);
	glRotatef(-30, 0, 0, 1);
	glScalef(1, 5.4, 1);
	cylinder();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.35, 0, 0);
	glRotatef(30, 0, 0, 1);
	glScalef(.95, 5.4, .95);
	cylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -.5, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(.9, 2, .9);
	cylinder();
	glPopMatrix();
}

void B() {
	glPushMatrix();
	glTranslatef(1, 0, 0);
	
	glPushMatrix();
	glTranslatef(-3, 0, 0);
	glScalef(1, 5, 1);
	cylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 3, 0);
	glRotatef(-120, 0, 0, 1);
	glScalef(.8, 2.5, .8);
	cylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 1, 0);
	glRotatef(-60, 0, 0, 1);
	glScalef(.8, 2.5, .8);
	cylinder();
	glPopMatrix();
	
	/*glPushMatrix();
	glTranslatef(.5, 2, 0);
	glColor3f(1, 0, 1);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(1.5, 1.5, 10, 10);
	glPopMatrix();*/

	glPushMatrix();
	glTranslatef(0, -4, 0);
	
	glPushMatrix();
	glTranslatef(-1, 3, 0);
	glRotatef(-120, 0, 0, 1);
	glScalef(.9, 2.5, .9);
	cylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 1, 0);
	glRotatef(-60, 0, 0, 1);
	glScalef(.9, 2.5, .9);
	cylinder();
	glPopMatrix();
	
	/*glPushMatrix();
	glTranslatef(.5, 2, 0);
	glColor3f(1, 0, 1);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(1.5, 1.5, 10, 10);
	glPopMatrix();*/

	glPopMatrix();
	glPopMatrix();
}


void I() {
	glPushMatrix();
	glScalef(1, 5, 1);
	cylinder();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(1, 3, 1);
	cylinder();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, -5, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(1, 3, 1);
	cylinder();
	glPopMatrix();
}


void L() {
	glPushMatrix();
	glScalef(1, 5, 1);
	cylinder();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3, -5, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(1, 4, 1);
	cylinder();
	glPopMatrix();
}

void N() {
	glPushMatrix();
	glTranslatef(-3, 0, 0);
	glScalef(1, 5, 1);
	cylinder();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3, 0, 0);
	glScalef(1, 5, 1);
	cylinder();
	glPopMatrix();
	
	glRotatef(38, 0, 0, 1);
	glScalef(.9, 5.3, .9);
	cylinder();
	glPopMatrix();
}

//static void placement()
//{
//	if (Scene::keyStates['A'])
//	{
//		Scene::x -= 0.5f;
//#ifdef _DEBUG
//		std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
//#endif // _DEBUG
//	}
//	if (Scene::keyStates['D'])
//	{
//		Scene::x += 0.5f;
//#ifdef _DEBUG
//		std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
//#endif // _DEBUG
//	}
//	if (Scene::keyStates['W'])
//	{
//		Scene::z -= 0.5f;
//#ifdef _DEBUG
//		std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
//#endif // _DEBUG
//	}
//	if (Scene::keyStates['S'])
//	{
//		Scene::z += 0.5f;
//#ifdef _DEBUG
//		std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
//#endif // _DEBUG
//	}
//	if (Scene::keyStates['Q'])
//	{
//		Scene::y -= 0.5f;
//#ifdef _DEBUG
//		std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
//#endif // _DEBUG
//	}
//	if (Scene::keyStates['E'])
//	{
//		Scene::y += 0.5f;
//#ifdef _DEBUG
//		std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
//#endif // _DEBUG
//	}
//}

static void panning()
{
	if (keyStates[GLUT_KEY_LEFT])
	{
		cameraX -= 0.5f;
		lookX -= 0.5f;
	}
	if (keyStates[GLUT_KEY_RIGHT])
	{
		cameraX += 0.5f;
		lookX += 0.5f;
	}
	if (keyStates[GLUT_KEY_UP])
	{
		cameraY += 0.5f;
		lookY += 0.5f;
	}
	if (keyStates[GLUT_KEY_DOWN])
	{
		cameraY -= 0.5f;
		lookY -= 0.5f;
	}

	// Forward and Backward Movement
	if (keyStates[GLUT_KEY_PAGE_UP])
	{
		cameraZ -= 0.5f;
		lookZ -= 0.5f;
	}
	if (keyStates[GLUT_KEY_PAGE_DOWN])
	{
		cameraZ += 0.5f;
		lookZ += 0.5f;
	}
}


static void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glFrustum(-10, 10, -10, 10, 5, 2000);

	// Set up the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(
		cameraX, cameraY, cameraZ,
		lookX, lookY, lookZ,
		upX, upY, upZ
	);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	// Setting the rotation of the scene
	glRotatef(angleX, axisX, axisY, axisZ);
	glRotatef(angleY, axisX, axisY, axisZ);
	glRotatef(angleZ, axisX, axisY, axisZ);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(5, 10, 1);
	N();
	glPopMatrix();

	panning();

	glutSwapBuffers();
	glutPostRedisplay();
}

static void reshape(int width, int height)
{
	
}

static void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// Scene Rotation (Positive Direction)
	case 'x':
		rotateX = !rotateX;
		axisX = 1.0f;
		break;
	case 'y':
		rotateY = !rotateY;
		axisY = 1.0f;
		break;
	case 'z':
		rotateZ = !rotateZ;
		axisZ = 1.0f;
		break;
		// Scene Rotation (Negative Direction)
	case 'X':
		rotateX = !rotateX;
		axisX = -1.0f;
		break;
	case 'Y':
		rotateY = !rotateY;
		axisY = -1.0f;
		break;
	case 'Z':
		rotateZ = !rotateZ;
		axisZ = -1.0f;
		break;
		
		// Placement testing
	case 'A':
		keyStates['A'] = true;
		break;
	case 'D':
		keyStates['D'] = true;
		break;
	case 'W':
		keyStates['W'] = true;
		break;
	case 'S':
		keyStates['S'] = true;
		break;
	case 'Q':
		keyStates['Q'] = true;
		break;
	case 'E':
		keyStates['E'] = true;
		break;
		
	case 27:
		exit(EXIT_SUCCESS);
	default:
		break;
	}
	
}

static void keyboardup(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'A':
		keyStates['A'] = false;
		break;
	case 'D':
		keyStates['D'] = false;
		break;
	case 'W':
		keyStates['W'] = false;
		break;
	case 'S':
		keyStates['S'] = false;
		break;
	case 'Q':
		keyStates['Q'] = false;
		break;
	case 'E':
		keyStates['E'] = false;
		break;
	default:
		break;
	}
}

void special(int key, int x, int y)
{
	// Panning the camera
	switch (key)
	{
	case GLUT_KEY_LEFT:
		keyStates[GLUT_KEY_LEFT] = true;
		break;
	case GLUT_KEY_RIGHT:
		keyStates[GLUT_KEY_RIGHT] = true;
		break;
	case GLUT_KEY_UP:
		keyStates[GLUT_KEY_UP] = true;
		break;
	case GLUT_KEY_DOWN:
		keyStates[GLUT_KEY_DOWN] = true;
		break;

		// Zooming the camera
	case GLUT_KEY_PAGE_UP:
		keyStates[GLUT_KEY_PAGE_UP] = true;
		break;
	case GLUT_KEY_PAGE_DOWN:
		keyStates[GLUT_KEY_PAGE_DOWN] = true;
		break;
	default:
		break;
	}
}

void specialup(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		keyStates[GLUT_KEY_LEFT] = false;
		break;
	case GLUT_KEY_RIGHT:
		keyStates[GLUT_KEY_RIGHT] = false;
		break;
	case GLUT_KEY_UP:
		keyStates[GLUT_KEY_UP] = false;
		break;
	case GLUT_KEY_DOWN:
		keyStates[GLUT_KEY_DOWN] = false;
		break;
		// Forward and Backward Movement
	case GLUT_KEY_PAGE_UP:
		keyStates[GLUT_KEY_PAGE_UP] = false;
		break;
	case GLUT_KEY_PAGE_DOWN:
		keyStates[GLUT_KEY_PAGE_DOWN] = false;
		break;
	default:
		break;
	}
}

static void idle()
{
	if (rotateX)
	{
		angleX += 1.0f;
		if (angleX >= 360.0f)
			angleX = 0.0f;
	}
	if (rotateY)
	{
		if (angleY >= 360.0f)
			angleY = 0.0f;
		angleY += 1.0f;
	}
	if (rotateZ)
	{
		if (angleZ >= 360.0f)
			angleZ = 0.0f;
		angleZ += 1.0f;
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	// Initialize GLUT
	glutInit(&argc, argv);
	// Set Display Mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window position and size
	int8_t screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int8_t screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition((screenWidth - WINDOW_WIDTH) / 2, (screenHeight - WINDOW_HEIGHT) / 2);
	// Create the window with the title
	glutCreateWindow(WINDOW_TITLE);
	
	// Print OpenGL properties
	std::cout << "OpenGL Vendor:   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;
	
	// Enable functionalities
	// Shade Model
	glShadeModel(GL_SMOOTH);
	// Depth Test & Depth Function
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	// Blend & Blend Function
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Normalize, Lighting, Texture
	glEnable(GL_NORMALIZE);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_2D);

	// Load Textures
	
	// Set the callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialup);
	glutIdleFunc(idle);
	
	// Start the main loop
	glutMainLoop();
}
