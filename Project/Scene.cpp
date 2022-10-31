#include "Scene.h"

import Settings;

#include <GL/freeglut.h>

#include <array>
#include <iostream>
#include <string>


namespace Scene {
	// Global Variables
	
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

	// Lights Controls
	static bool light0 = true, light1 = false, light2 = false, light3 = true;
	static bool ambient = true, diffuse = true, specular = true;

	// Placements testing
	GLfloat x = 0.0f, y = 0.0f, z = 0.0f;

	static void GetNormal3f(
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

	static GLfloat quad_vertices[8][3] =
	{
		{-1.0, -1.0, -1.0},
		{ 1.0, -1.0, -1.0},
		{-1.0, -1.0,  1.0},
		{ 1.0, -1.0,  1.0},

		{-1.0,  1.0, -1.0},
		{ 1.0,  1.0, -1.0},
		{-1.0,  1.0,  1.0},
		{ 1.0,  1.0,  1.0}
	};

	static GLuint quad_indices[6][4] =
	{
		{0,2,3,1},
		{0,2,6,4},
		{2,3,7,6},
		{1,3,7,5},
		{1,5,4,0},
		{6,7,5,4}
	};

	// Draw Cube
	static void Cube(float R = 255, float G = 255, float B = 255, float alpha = 1)
	{
		float r = R / 255, g = G / 255, b = B / 255;

		GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat mat_ambient[] = { r, g, b, 1.0 };
		GLfloat mat_diffuse[] = { r, g, b, 1.0 };
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 60 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		/*if (em)
		{
			glMaterialfv(GL_FRONT, GL_EMISSION, matEm);
		}
		else
		{
			glMaterialfv(GL_FRONT, GL_EMISSION, noMat);
		}*/



		glBegin(GL_QUADS);
		for (GLint i = 0; i < 6; i++)
		{
			GetNormal3f(
				quad_vertices[quad_indices[i][0]][0], quad_vertices[quad_indices[i][0]][1], quad_vertices[quad_indices[i][0]][2],
				quad_vertices[quad_indices[i][1]][0], quad_vertices[quad_indices[i][1]][1], quad_vertices[quad_indices[i][1]][2],
				quad_vertices[quad_indices[i][2]][0], quad_vertices[quad_indices[i][2]][1], quad_vertices[quad_indices[i][2]][2]
			);

			glVertex3fv(&quad_vertices[quad_indices[i][0]][0]); glTexCoord2f(0, 0);
			glVertex3fv(&quad_vertices[quad_indices[i][1]][0]); glTexCoord2f(0, 1);
			glVertex3fv(&quad_vertices[quad_indices[i][2]][0]); glTexCoord2f(1, 1);
			glVertex3fv(&quad_vertices[quad_indices[i][3]][0]); glTexCoord2f(1, 0);
		}
		glEnd();
	}

	// Drawing Earth
	static void DrawEarth()
	{
		glPushMatrix();
		glScalef(1000, 1, 1000);
		Cube(139, 69, 19);  //165, 42, 42
		glPopMatrix();
	}

	static void Grass()
	{
		glPushMatrix();
		glScalef(250, 5, 250);
		Cube(0, 255, 0);
		glPopMatrix();
	}

	static void Pond()
	{
		glPushMatrix();
		glTranslatef(-355, 0, 0);
		glScalef(200, 5, 252);
		Cube(255, 255, 255);
		glPopMatrix();
	}

	static void Base()
	{
		// 1st Base
		glPushMatrix();
		glTranslatef(-100, 7, -141.5);
		glScalef(100, 5, 150);
		Cube(128, 0, 0);
		glPopMatrix();

		// 2nd Base
		glPushMatrix();
		glTranslatef(-98, 17, -141.5);
		glScalef(96, 5, 142);
		Cube(40, 40, 40);
		glPopMatrix();

		// 3rd Base
		glPushMatrix();
		glTranslatef(-96, 27, -141.5);
		glScalef(90, 5, 132);
		Cube(128, 10, 10);
		glPopMatrix();
	}

	static void Floors()
	{
		glPushMatrix();
		glTranslatef(16.5, 6.5, -165);
		Grass();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(325, 7.5, -667.5);
		Pond();
		glPopMatrix();

		glPushMatrix();											// Main Base 
		glTranslatef(90, 10, 0);
		glScalef(1, 1, 1.25);
		Base();
		glPopMatrix();
	}

	static void Road()
	{
		//glBindTexture(GL_TEXTURE_2D, ID[floor4]);
		glPushMatrix();
		glTranslatef(100, 5.5, -50);
		glScalef(75, 1, 35);
		Cube(165, 42, 42);
		glPopMatrix();

		//glBindTexture(GL_TEXTURE_2D, ID[white]);

		glPushMatrix();
		glTranslatef(100, 8, -50);
		glScalef(75, 1, 3);
		Cube(255, 255, 255);
		glPopMatrix();

		//glPushMatrix();
		//glTranslatef(180, -60, -150);
		//glScalef(1.5, 1.5, 1.5);
		//Tree();   //sohid minar tree
		//glPopMatrix();

		//glPushMatrix();
		//glTranslatef(180, -60, 130);
		//glScalef(1.5, 1.5, 1.5);
		//Tree();   //sohid minar tree2
		//glPopMatrix();
	}

	static void MinarBase()
	{
		//glBindTexture(GL_TEXTURE_2D, ID[white]);

		glPushMatrix();							//minar Right
		glTranslatef(-70, 35, -15);
		glScalef(3, 60, 3);
		Cube(255, 255, 255);
		glPopMatrix();

		glPushMatrix();							//minar Left
		glTranslatef(-70, 35, 15);
		glScalef(3, 60, 3);
		Cube(255, 255, 255);
		glPopMatrix();

		glPushMatrix();							//minar upper base
		glTranslatef(-70, 95, 0);
		glScalef(3, 2, 18);
		Cube(255, 255, 255);
		glPopMatrix();

		//glBindTexture(GL_TEXTURE_2D, ID[black]);
		glPushMatrix();							// Minar Middle Column (Right)
		glTranslatef(-68, 35, -2);
		glScalef(0.8, 59, 0.8);
		Cube(255, 255, 255);
		glPopMatrix();

		//glBindTexture(GL_TEXTURE_2D, ID[black]);
		glPushMatrix();							// Minar Middle Column (Left)
		glTranslatef(-68, 35, 6);
		glScalef(0.8, 59, 0.8);
		Cube(255, 255, 255);
		glPopMatrix();
	}

	static void MinarMid()
	{
		glPushMatrix();  //side_mid_base1
		glRotatef(25, 0, 1, 0);
		glTranslatef(0, 0, 12);
		glScalef(1, .9, .9);
		MinarBase();
		glPopMatrix();

		glPushMatrix();  //side_mid_base2
		glRotatef(-25, 0, 1, 0);
		glTranslatef(0, 0, -12);
		glScalef(1, .9, .9);
		MinarBase();
		glPopMatrix();
	}

	static void MinarSmall()
	{
		glPushMatrix(); //small_minar_base1
		glRotatef(-25, 0, 1, 0);
		glTranslatef(0, 0, -47);
		glScalef(1, .8, .8);
		MinarBase();
		glPopMatrix();

		glPushMatrix(); //small_minar_base2
		glRotatef(25, 0, 1, 0);
		glTranslatef(0, 0, 48);
		glScalef(1, .8, .8);
		MinarBase();
		glPopMatrix();
	}

	static void MinarUpperBase()
	{
		//glBindTexture(GL_TEXTURE_2D, ID[white]);

		glPushMatrix();  //minar base1
		glTranslatef(-70, 35, -15);
		glScalef(3, 30, 3);
		Cube(255, 255, 255);
		glPopMatrix();

		glPushMatrix();//minar base2
		glTranslatef(-70, 35, 15);
		glScalef(3, 30, 3);
		Cube(255, 255, 255);
		glPopMatrix();

		glPushMatrix();										//minar upper base
		glTranslatef(-70, 65, 0);
		glScalef(3, 2, 18);
		Cube(255, 255, 255);
		glPopMatrix();

		//  glBindTexture(GL_TEXTURE_2D, ID[black]);
		glPushMatrix();//minar thin_base1
		glTranslatef(-68, 35, -2);
		glScalef(0.8, 29, 0.8);
		Cube(255, 255, 255);
		glPopMatrix();

		//glBindTexture(GL_TEXTURE_2D, ID[black]);
		glPushMatrix();//minar thin_base1
		glTranslatef(-68, 35, 6);
		glScalef(0.8, 29, 0.8);
		Cube(255, 255, 255);
		glPopMatrix();

	}

	static void MinarUpper()
	{
		glPushMatrix();
		glRotatef(-45, 0, 0, 1);
		glTranslatef(-50, 10, 0);
		MinarUpperBase();
		glPopMatrix();
	}

	static void Minar()
	{
		glPushMatrix();
		glScalef(1, 1, 1.5);
		MinarBase();
		glPopMatrix();

		glPushMatrix();
		glScalef(1, 1, 1.5);
		MinarUpper();
		glPopMatrix();


		glPushMatrix();
		glScalef(1, 1, 1.5);
		MinarMid();
		glPopMatrix();

		glPushMatrix();
		glScalef(1, 1, 1.5);
		MinarSmall();
		glPopMatrix();

		//glEnable(GL_COLOR_MATERIAL);
		////glBindTexture(GL_TEXTURE_2D, ID[red]);
		//glPushMatrix();
		//glColor3f(1, 0, 0);
		//glTranslatef(-130, 90, 0);
		//glRotatef(85, 0, 0, 1);
		//glScalef(95, 5, 95);               //curve-------------------------
		//curve();
		//glPopMatrix();
		//glColor3f(1, 1, 1);
	}

	static void ShahidMinar()
	{
		glPushMatrix();
		Floors();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(7.5, 67.5, -178);
		Minar();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(65.5, 7.5, -130);
		Road();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(351.5, 1, 750);
		glRotatef(90, 0, 1, 0);
		glScalef(10, 1, 1);
		Road();
		glPopMatrix();

		/*glPushMatrix();
		glTranslatef(-10, 0, 0);
		FlowerStage();
		glPopMatrix();*/
	}

	static void Scene()
	{
		glPushMatrix();
		DrawEarth();
		glPopMatrix();

		glPushMatrix();
		ShahidMinar();
		glPopMatrix();
	}

	static void Light()
	{
		//Light
		glEnable(GL_LIGHTING);

		GLfloat noLight[] = { 0, 0, 0, 1 };
		GLfloat lightAmb[] = { 0.5, 0.5, 0.5, 1 };
		GLfloat lightDif[] = { 1, 1, 1, 1 };
		GLfloat lightSpec[] = { 1, 1, 1, 1 };
		GLfloat light1Pos[] = { 0, -500, 0, 1 };
		GLfloat light4Pos[] = { 0,500,0, 1 };

		// GLfloat light1Pos[] = {90, 90, 90, 1};
		//  GLfloat light4Pos[] = {90, 90, -90, 1};
		GLfloat light2Pos[] = { 683, 300, -350, 1 }; //spot light
		GLfloat light3Pos[] = { -380, 400, -50, 1 }; //spot light  GLfloat light2Pos[] = {15, 40, -45, 1}; //spot light
		// GLfloat light3Pos[] = {15, 40, 45, 1

		glEnable(GL_LIGHT0);  //1
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
		glLightfv(GL_LIGHT0, GL_POSITION, light1Pos);


		glEnable(GL_LIGHT1); //2 spot light
		glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDif);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec);
		glLightfv(GL_LIGHT1, GL_POSITION, light2Pos);

		glEnable(GL_LIGHT2); //3 spot light
		glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmb);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDif);
		glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpec);
		glLightfv(GL_LIGHT2, GL_POSITION, light3Pos);

		glEnable(GL_LIGHT3); //4
		glLightfv(GL_LIGHT3, GL_AMBIENT, lightAmb);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, lightDif);
		glLightfv(GL_LIGHT3, GL_SPECULAR, lightSpec);
		glLightfv(GL_LIGHT3, GL_POSITION, light4Pos);

		//GLfloat spotDirection[] = {0, -18, 20, 1};

		//2    {90, 36, -120, 1};
		//3    {125, 36, 180, 1};

		GLfloat spotDirection[] = { 0, -1, 0, 1 };   //2
		GLfloat spotCutOff[] = { 60 };

		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection);
		glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutOff);

		GLfloat spotDirection2[] = { 0, -1, 0, 1 }; //3
		GLfloat spotCutOff2[] = { 60 };

		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection2);
		glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutOff2);


		if (light0)
		{
			glEnable(GL_LIGHT0);
		}
		else
		{
			glDisable(GL_LIGHT0);
		}

		if (light1)
		{
			glEnable(GL_LIGHT1);
		}
		else
		{
			glDisable(GL_LIGHT1);
		}

		if (light2)
		{
			glEnable(GL_LIGHT2);
		}
		else
		{
			glDisable(GL_LIGHT2);
		}
		if (light3)
		{
			glEnable(GL_LIGHT3);
		}
		else
		{
			glDisable(GL_LIGHT3);
		}


		if (ambient)
		{
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
			glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
			glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmb);
			glLightfv(GL_LIGHT3, GL_AMBIENT, lightAmb);

		}
		else
		{
			glLightfv(GL_LIGHT0, GL_AMBIENT, noLight);
			glLightfv(GL_LIGHT1, GL_AMBIENT, noLight);
			glLightfv(GL_LIGHT2, GL_AMBIENT, noLight);
			glLightfv(GL_LIGHT3, GL_AMBIENT, noLight);
		}

		if (diffuse)
		{
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDif);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDif);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, lightDif);
		}
		else
		{
			glLightfv(GL_LIGHT0, GL_DIFFUSE, noLight);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, noLight);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, noLight);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, noLight);
		}

		if (specular)
		{
			glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
			glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec);
			glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpec);
			glLightfv(GL_LIGHT3, GL_SPECULAR, lightSpec);
		}
		else
		{
			glLightfv(GL_LIGHT0, GL_SPECULAR, noLight);
			glLightfv(GL_LIGHT1, GL_SPECULAR, noLight);
			glLightfv(GL_LIGHT2, GL_SPECULAR, noLight);
			glLightfv(GL_LIGHT3, GL_SPECULAR, noLight);
		}

	}

	static void Draw()
	{
		// Draw the scene
		glPushMatrix();
		glScaled(0.1, 0.1, 0.1);
		glRotated(-90, 0, 1, 0);
		glTranslatef(0, 0, -100);
		Scene();
		glPopMatrix();
	}

	static void Keyboard()
	{
		if (Scene::keyStates['A'])
		{
			Scene::x -= 0.5f;
			std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
		}
		if (Scene::keyStates['D'])
		{
			Scene::x += 0.5f;
			std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
		}
		if (Scene::keyStates['W'])
		{
			Scene::z -= 0.5f;
			std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
		}
		if (Scene::keyStates['S'])
		{
			Scene::z += 0.5f;
			std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
		}
		if (Scene::keyStates['Q'])
		{
			Scene::y -= 0.5f;
			std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
		}
		if (Scene::keyStates['E'])
		{
			Scene::y += 0.5f;
			std::cout << "Translation: " << Scene::x << ", " << Scene::y << ", " << Scene::z << std::endl;
		}
	}

	static void Special()
	{
		if (keyStates[GLUT_KEY_LEFT])
		{
			Scene::cameraX -= 0.5f;
			Scene::lookX -= 0.5f;
		}
		if (keyStates[GLUT_KEY_RIGHT])
		{
			Scene::cameraX += 0.5f;
			Scene::lookX += 0.5f;
		}
		if (keyStates[GLUT_KEY_UP])
		{
			Scene::cameraY += 0.5f;
			Scene::lookY += 0.5f;
		}
		if (keyStates[GLUT_KEY_DOWN])
		{
			Scene::cameraY -= 0.5f;
			Scene::lookY -= 0.5f;
		}

		// Forward and Backward Movement
		if (keyStates[GLUT_KEY_PAGE_UP])
		{
			Scene::cameraZ -= 0.5f;
			Scene::lookZ -= 0.5f;
		}
		if (keyStates[GLUT_KEY_PAGE_DOWN])
		{
			Scene::cameraZ += 0.5f;
			Scene::lookZ += 0.5f;
		}
	}
}

void Control::display()
{
	// Count the FPS
	static int frame = 0;
	static int time = 0;
	static int timebase = 0;
	char s[30]{};
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		std::string fps = "FPS: " + std::to_string(frame * 1000.0 / (time - timebase));
		std::string title = Settings::WINDOW_TITLE + std::string(" - ") + fps;
		glutSetWindowTitle(title.c_str());
		//sprintf(s, "FPS:%4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	// Set up background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up the projection matrix
	gluOrtho2D(0, Settings::WINDOW_WIDTH, 0, Settings::WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10, 10, -10, 10, 5, 2000);

	// Set up the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		Scene::cameraX, Scene::cameraY, Scene::cameraZ,
		Scene::lookX, Scene::lookY, Scene::lookZ,
		Scene::upX, Scene::upY, Scene::upZ
	);

	glViewport(0, 0, Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);

	// Setting the rotation of the scene
	glRotatef(Scene::angleX, Scene::axisX, Scene::axisY, Scene::axisZ);
	glRotatef(Scene::angleY, Scene::axisX, Scene::axisY, Scene::axisZ);
	glRotatef(Scene::angleZ, Scene::axisX, Scene::axisY, Scene::axisZ);

	// Lighting
	Scene::Light();

	// Draw the scene
	Scene::Draw();

	// Keyboard input
	Scene::Keyboard();
	Scene::Special();

	// Swap the buffers
	glutSwapBuffers();

	// Redraw the scene
	glutPostRedisplay();
}

void Control::reshape(int width, int height) {}

void Control::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// Scene Rotation (Positive Direction)
	case 'x':
		Scene::rotateX = !Scene::rotateX;
		Scene::axisX = 1.0f;
		break;
	case 'y':
		Scene::rotateY = !Scene::rotateY;
		Scene::axisY = 1.0f;
		break;
	case 'z':
		Scene::rotateZ = !Scene::rotateZ;
		Scene::axisZ = 1.0f;
		break;
		// Scene Rotation (Negative Direction)
	case 'X':
		Scene::rotateX = !Scene::rotateX;
		Scene::axisX = -1.0f;
		break;
	case 'Y':
		Scene::rotateY = !Scene::rotateY;
		Scene::axisY = -1.0f;
		break;
	case 'Z':
		Scene::rotateZ = !Scene::rotateZ;
		Scene::axisZ = -1.0f;
		break;

		// Light Control
	case '0':
		Scene::light0 = !Scene::light0;
		break;
	case '1':
		Scene::light1 = !Scene::light1;
		break;
	case '2':
		Scene::light2 = !Scene::light2;
		break;
	case '3':
		Scene::light3 = !Scene::light3;
		break;

		// Placement testing
	case 'A':
		Scene::keyStates['A'] = true;
		break;
	case 'D':
		Scene::keyStates['D'] = true;
		break;
	case 'W':
		Scene::keyStates['W'] = true;
		break;
	case 'S':
		Scene::keyStates['S'] = true;
		break;
	case 'Q':
		Scene::keyStates['Q'] = true;
		break;
	case 'E':
		Scene::keyStates['E'] = true;
		break;

		// Exit the program

	case 27:
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}

void Control::keyboardup(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'A':
		Scene::keyStates['A'] = false;
		break;
	case 'D':
		Scene::keyStates['D'] = false;
		break;
	case 'W':
		Scene::keyStates['W'] = false;
		break;
	case 'S':
		Scene::keyStates['S'] = false;
		break;
	case 'Q':
		Scene::keyStates['Q'] = false;
		break;
	case 'E':
		Scene::keyStates['E'] = false;
		break;
	default:
		break;
	}
}

void Control::special(int key, int x, int y)
{
	//std::cout << "Special Key Down Function called for " << key << std::endl;

	// Panning the camera
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Scene::keyStates[GLUT_KEY_LEFT] = true;
		break;
	case GLUT_KEY_RIGHT:
		Scene::keyStates[GLUT_KEY_RIGHT] = true;
		break;
	case GLUT_KEY_UP:
		Scene::keyStates[GLUT_KEY_UP] = true;
		break;
	case GLUT_KEY_DOWN:
		Scene::keyStates[GLUT_KEY_DOWN] = true;
		break;

		// Zooming the camera
	case GLUT_KEY_PAGE_UP:
		Scene::keyStates[GLUT_KEY_PAGE_UP] = true;
		break;
	case GLUT_KEY_PAGE_DOWN:
		Scene::keyStates[GLUT_KEY_PAGE_DOWN] = true;
		break;
	default:
		break;
	}
}

void Control::specialup(int key, int x, int y)
{
	//std::cout << "Special Key Up Function called for " << key << std::endl;

	switch (key)
	{
	case GLUT_KEY_LEFT:
		Scene::keyStates[GLUT_KEY_LEFT] = false;
		break;
	case GLUT_KEY_RIGHT:
		Scene::keyStates[GLUT_KEY_RIGHT] = false;
		break;
	case GLUT_KEY_UP:
		Scene::keyStates[GLUT_KEY_UP] = false;
		break;
	case GLUT_KEY_DOWN:
		Scene::keyStates[GLUT_KEY_DOWN] = false;
		break;
		// Forward and Backward Movement
	case GLUT_KEY_PAGE_UP:
		Scene::keyStates[GLUT_KEY_PAGE_UP] = false;
		break;
	case GLUT_KEY_PAGE_DOWN:
		Scene::keyStates[GLUT_KEY_PAGE_DOWN] = false;
		break;
	default:
		break;
	}
}

void Control::mouse(int button, int state, int x, int y) {}

void Control::motion(int x, int y) {}

void Control::idle()
{
	if (Scene::rotateX)
	{
		Scene::angleX += 1.0f;
		if (Scene::angleX >= 360.0f)
			Scene::angleX = 0.0f;
	}
	if (Scene::rotateY)
	{
		if (Scene::angleY >= 360.0f)
			Scene::angleY = 0.0f;
		Scene::angleY += 1.0f;
	}
	if (Scene::rotateZ)
	{
		if (Scene::angleZ >= 360.0f)
			Scene::angleZ = 0.0f;
		Scene::angleZ += 1.0f;
	}

	// Redraw the scene
	glutPostRedisplay();
}
