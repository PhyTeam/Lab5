// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include "supportClass.h"
#include "Mesh.h"
#include "PLYReader.h"

using namespace std;

#define PI		3.1415926

float matrix[16];
float axis[3];
float angle = 0.0;
// Previous mouse cursor position
int previousX = 0;
int previousY = 0;
// Says if the mouse left button is currently pressed
bool isLeftButtonPressed = false;

float zoomScale = 0.95f;

int		screenWidth = 600;
int		screenHeight = 600;
bool	bWireFrame = false;
Mesh*	object3d;
float cameraX = 0, cameraY = 0, cameraZ = 1000;
bool b4View = false;
void initLight();
void initLight2();
void drawAll();

void drawAxis()
{
	glPushMatrix();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-4, 0, 0);//x
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);//y
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -4);//z
	glVertex3f(0, 0, 4);
	glEnd();

	glPopMatrix();
}


void myKeyboard(unsigned char key, int x, int y)
{
	float	fAngle = 2;
	GLboolean isOn = false;
	switch (key)
	{
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	case 'l':
	case 'L':
		break;
	case 'x':
	case 'X':
		break;
	case 'w':
	case 'W':
		bWireFrame = !bWireFrame;
		break;
	case 'D': 
	case 'd':
		glGetBooleanv(GL_LIGHT1, &isOn);
		if (isOn)
			glDisable(GL_LIGHT1);
		else
			glEnable(GL_LIGHT1);

		break;
	case 'v':
	case 'V':
		b4View = !b4View;
		break;
	case '-': 
	case '_':
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glScalef(1.f / zoomScale, 1.f / zoomScale, 1.f / zoomScale);
		glMultMatrixf(matrix);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)matrix);
		glPopMatrix();
		break;
		break;
	case '+': 
	case '=':
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glScalef(zoomScale, zoomScale, zoomScale);
		glMultMatrixf(matrix);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)matrix);
		glPopMatrix();
		break;
	
	}
	printf("PRESSED %d\n", key);
	glutPostRedisplay();
}

void keyboardSpecialDown(int k, int x, int y) {
	switch (k) {
	case 100:
		break;
	case 102:
		break;
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	default:
		break;
	}
	glutPostRedisplay();
	//printf("PRESSED %d\n", k);
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			isLeftButtonPressed = true;
			previousX = x;
			previousY = y;
			angle = 0.0;
		}
		else if (state == GLUT_UP) {
			isLeftButtonPressed = false;
		}
		break;
	case 3:
	case 4:
		if (state == GLUT_DOWN) {
		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
		glLoadIdentity();
			glScalef(zoomScale, zoomScale, zoomScale);
			glMultMatrixf(matrix);
			glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)matrix);
			glPopMatrix();
		}
		break;
	}

	glutPostRedisplay();
	}

void mouseMotion(int x, int y)
{
	if (isLeftButtonPressed) {
		// Project previous coords on to the sphere.
		float x1 = (2 * previousX - screenWidth) / (float)screenWidth;
		float y1 = (screenHeight - 2 * previousY) / (float)screenHeight;
		float z1 = 1 - x1*x1 - y1*y1;

		// Be careful not to take the square root of a negative number.
		if (z1 < 0) z1 = 0; else z1 = sqrt(z1);

		// Project current coords on to the sphere.
		float x2 = (2 * x - screenWidth) / (float)screenWidth;
		float y2 = (screenHeight - 2 * y) / (float)screenHeight;
		float z2 = 1 - x2*x2 - y2*y2;

		if (z2 < 0) z2 = 0; else z2 = sqrt(z2);

		// Take the cross product to find the axis of rotation.
		axis[0] = y1*z2 - y2*z1;
		axis[1] = z1*x2 - z2*x1;
		axis[2] = x1*y2 - x2*y1;

		// Angle is computed from the magnitude of the cross product.
		float norm = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
		angle = asin(fmin(1.0f, norm)) * 180 / 3.14159;

		// Normalize the axis.
		axis[0] /= norm;
		axis[1] /= norm;
		axis[2] /= norm;

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRotatef(angle * 1.5f, axis[0], axis[1], axis[2]);
		glMultMatrixf(matrix);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)matrix);
		glPopMatrix();

		previousX = x;
		previousY = y;
		glutPostRedisplay();
	}
	}
void myDisplay() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0f, (float)(screenWidth) / screenHeight, 1.0f, 10000.0f);
	gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth, screenHeight);

	glMultMatrixf(matrix);
	drawAll();
	//glutSolidTeapot(200.0);
	glFlush();
	glutSwapBuffers();
}

void drawAll() {
	drawAxis();
	//Base
	GLfloat	Diffuse[] = { 0.5f, 0.5f, 0.1f };
	GLfloat	Specular[] = { 0.5f, 0.5f, 0.5f };
	GLfloat	Ambient[] = { 1.0f, 0.0f, 1.0f };
	//glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	//glScaled(0.05, 0.05, 0.05);
	glTranslatef(object3d->origin[0], object3d->origin[1], object3d->origin[2]);
	object3d->DrawWireframe();
}

void myInit()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i == j) matrix[i * 4 + j] = 1.0; else matrix[i * 4 + j] = 0.0;

	// Load Mesh
	object3d = readFile();
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	initLight();
	initLight2();
}

void initLight() {
	GLfloat	lightDiffuse[] = { 0.5f, 0.5f, 0.5f };
	GLfloat	lightSpecular[] = { 1.0f, 1.0f, 1.0f };
	GLfloat	lightAmbient[] = { 0.2f, 0.2f, 0.2f, .7f };
	GLfloat 	light_position1[] = { 60.0f, 60.0f, 60.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void initLight2() {
	GLfloat	lightDiffuse[] = { 0.5f, 0.5f, 0.5f };
	GLfloat	lightSpecular[] = { 1.0f, 1.0f, 1.0f };
	GLfloat	lightAmbient[] = { 1.0f, 0.2f, 0.1f, 1.0f };
	GLfloat 	light_position1[] = { -6.0f, -6.0f, 6.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab3-2015-2016"); // open the screen window

	myInit();

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(keyboardSpecialDown);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
