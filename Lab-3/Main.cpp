#include <GL/freeglut.h>

#include <iostream>

#include "BMPLoader.h"


constexpr auto WINDOW_WIDTH = 700;
constexpr auto WINDOW_HEIGHT = 700;

float Txval = 0, Tyval = 0, Tzval = 0;
float alpha = 0.0, theta = 0.0, axis_x = 0.0, axis_y = 0.0;
bool bRotate = false, uRotate = false;

unsigned int ID1, ID2;

static GLfloat v_box[8][3] =
{
	{-2.0, 0.0, 0.0},
	{2.0, 0.0, 0.0},
	{-2.0, 0.0, 2.0},
	{2.0, 0.0, 2.0},

	{-2.0, 2.0, 0.0},
	{2.0, 2.0, 0.0},
	{-2.0, 2.0, 2.0},
	{2.0, 2.0, 2.0}
};

static GLuint quadIndices[6][4] =
{
	{0,2,3,1},
	{0,2,6,4},
	{2,3,7,6},
	{1,3,7,5},
	{1,5,4,0},
	{6,7,5,4}
};

static void getNormal3p
(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
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

void LoadTexture(const char* const filename, unsigned int& const ID)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	BMPLoader bmp(filename);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.m_Width, bmp.m_Height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.m_Data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bmp.m_Width, bmp.m_Height, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.m_Data);
}

void drawBox()
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 60 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glBegin(GL_QUADS);
	for (GLint i = 0; i < 6; i++)
	{
		getNormal3p(v_box[quadIndices[i][0]][0], v_box[quadIndices[i][0]][1], v_box[quadIndices[i][0]][2],
			v_box[quadIndices[i][1]][0], v_box[quadIndices[i][1]][1], v_box[quadIndices[i][1]][2],
			v_box[quadIndices[i][2]][0], v_box[quadIndices[i][2]][1], v_box[quadIndices[i][2]][2]);

		glVertex3fv(&v_box[quadIndices[i][0]][0]); glTexCoord2f(1, 0);
		glVertex3fv(&v_box[quadIndices[i][1]][0]); glTexCoord2f(0, 0);
		glVertex3fv(&v_box[quadIndices[i][2]][0]); glTexCoord2f(0, 1);
		glVertex3fv(&v_box[quadIndices[i][3]][0]); glTexCoord2f(1, 1);

	}
	glEnd();
}


//void light()
//{
//	GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
//	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat light_position[] = { 0.0, 10.0, 50.0, 1.0 };
//
//	glEnable(GL_LIGHT0);
//
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
//	//GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
//	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
//	//glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);
//}

void display(void)
{
	glClearColor(0.08f, 0.16f, 0.16f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5, 5, -5, 5, 4, 50);
	//gluPerspective(60,1,5,100);
	//glOrtho(-5,5,-5,5, 4, 50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 2, 10, 0, 0, 0, 0, 1, 0);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPushMatrix();
	glTranslatef(0, 0, Tzval);
	glRotatef(alpha, axis_x, axis_y, 0.0);
	glRotatef(theta, axis_x, axis_y, 0.0);
	drawBox();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void myKeyboardFunc(const unsigned char const key, const int const x, const int const y)
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
	default: break;
	}
}


void animate()
{
	if (bRotate == true)
	{
		theta += 0.2;
		if (theta > 360.0)
			theta -= 360.0 * floor(theta / 360.0);
	}

	if (uRotate == true)
	{
		alpha += 0.2;
		if (alpha > 360.0)
			alpha -= 360.0 * floor(alpha / 360.0);
	}
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Lab-3: Textures");

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

	glEnable(GL_TEXTURE_2D);

	LoadTexture("spre.bmp", ID1);
	LoadTexture("wood.bmp", ID2);
	//light();

	std::cout << "OpenGL Vendor:   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;

	glutPassiveMotionFunc(NULL);
	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(NULL);
	glutDisplayFunc(display);
	glutIdleFunc(animate);

	glutMainLoop();

	std::cin.get();
}