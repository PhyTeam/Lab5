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
bool	selectedMode = false;
float	fovy = 45.0f, near_ = 1.0f, far_ = 10000.0f;
float	xselect = 0, yselect = 0;
float	cur_trans_x = 0, cur_trans_y = 0, cur_trans_z = 0;
Mesh*	object3d;
float cameraX = 0, cameraY = 0, cameraZ = 1000;
bool b4View = false;
bool bhit = false;
void initLight();
void initLight2();
void drawAll();
void init();

void drawAxis()
{
	glPushMatrix();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-400, 0, 0);//x
	glVertex3f(400, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);//y
	glVertex3f(0, 400, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -400);//z
	glVertex3f(0, 0, 400);
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
	case 's'|'S':
		selectedMode = !selectedMode;
		break;
	
	}
	//printf("PRESSED %d\n", key);
	init();
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
	init();
	glutPostRedisplay();
	//printf("PRESSED %d\n", k);
}
void processHits(GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	GLuint names, *ptr;
	GLfloat maxz1 = 10, maxz2 = -1, z1, z2;
	GLint name = -1;
	//printf("hits = %d\n", hits);
	ptr = (GLuint *)buffer;
	/*for (i = 0; i < hits; i++) {  // for each hit  
		names = *ptr;
		printf(" number of names for hit = %d\n", names); ptr++;
		printf("  z1 is %g;", (float)*ptr / 0x7fffffff); z1 = (float)*ptr / 0x7fffffff; ptr++;
		printf(" z2 is %g\n", (float)*ptr / 0x7fffffff); z2 = (float)*ptr / 0x7fffffff; ptr++;
		if (z1 < maxz1) {
			maxz1 = z1;
			name = *ptr;
		}
		printf("   the name is ");
		for (j = 0; j < names; j++) {  // for each name 
			printf("%d ", *ptr); ptr++;
		}
		printf("\n");
	}*/

	if (hits > 0) {
		bhit = true;
		//printf("Selected");
		
	}

}
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			isLeftButtonPressed = true;
			previousX = x;
			previousY = y;
			cur_trans_x = object3d->slideX;
			cur_trans_y = object3d->slideY;
			cur_trans_z = object3d->slideZ;
			angle = 0.0;

			// selected mode
			xselect = x; yselect = y;
			GLuint selectBuf[512];
			GLint hits;
			GLint viewport[4];
			if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
				return;
			glGetIntegerv(GL_VIEWPORT, viewport);

			glSelectBuffer(512, selectBuf);
			(void)glRenderMode(GL_SELECT);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			glInitNames();
			glPushName(0);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			/*  create 5x5 pixel picking region near cursor location */
			gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y),
				5.0, 5.0, viewport);
			//glMatrixMode(GL_MODELVIEW);
			
			gluPerspective(45.0f, (float)(screenWidth) / screenHeight, 1.0f, 10000.0f);
			gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glMultMatrixf(matrix);

			drawAll();
			glPopMatrix();
			//glFlush();

			hits = glRenderMode(GL_RENDER);
			processHits(hits, selectBuf);
		}
		else if (state == GLUT_UP) {
			isLeftButtonPressed = false;
			bhit = false;
			//selectedMode = false;
			//glutPostRedisplay();
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
		//glutPostRedisplay();
		break;
	}

	
	}
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)(screenWidth) / screenHeight, 1.0f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
}
void mouseMotion(int x, int y)
{
	if (isLeftButtonPressed) {
		if (!selectedMode) {
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
			init();
			glutPostRedisplay();
		}
		else if (bhit) {// selected mode -> translate
			float xdiff = previousX - x;
			float ydiff = previousY - y;
			previousX = x;
			previousY = y;
			//cameraX = camera_dis*cos(camera_angle);
			//cameraY = camera_height;
			//cameraZ = camera_dis*sin(camera_angle);
			GLint upx = 0, upy = 0, upz = 0, leftx = 0, lefty = 0, leftz = 0;
			Vector3 OE(cameraX, cameraY, cameraZ);
			Vector3 up(0.0, 1.0, 0.0);
			Vector3 left = OE.cross(up);
			left.normalize();
			Vector3 wup = left.cross(OE);
			wup.normalize();
			float fovy1 = 45.0/180.0*PI;	// near
			// reset translate vector
			//object3d->slideX = cur_trans_x + 2 * xdiff*tan(fovy1 / 2) / screenHeight*sqrt(OE.dot(OE)) *left.x + 2 * ydiff*tan(fovy1 / 2) / screenHeight*sqrt(OE.dot(OE))*wup.x;
			//object3d->slideY = cur_trans_y + 2 * xdiff*tan(fovy1 / 2) / screenHeight*sqrt(OE.dot(OE)) *left.x + 2 * ydiff*tan(fovy1 / 2) / screenHeight*sqrt(OE.dot(OE))*wup.y;
			//object3d->slideZ = cur_trans_z + 2 * xdiff*tan(fovy1 / 2) / screenHeight*sqrt(OE.dot(OE)) *left.x + 2 * ydiff*tan(fovy1 / 2) / screenHeight*sqrt(OE.dot(OE))*wup.z;
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			//glRotatef(angle * 1.5f, axis[0], axis[1], axis[2]);
			glTranslatef(xdiff*left.x*1.3 + ydiff*wup.x*1.3, xdiff*left.y*1.3 + ydiff*wup.y*1.3, xdiff*left.z*1.3 + ydiff*wup.z*1.3);
			glMultMatrixf(matrix);
			glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)matrix);
			glPopMatrix();

			init();
			glutPostRedisplay();
		}
	}
}

void myDisplay() {
	/*if (isLeftButtonPressed) {
		xselect = x; yselect = y;
		GLuint selectBuf[BUFSIZE];
		GLint hits;
		GLint viewport[4];
		if (state == GLUT_UP) {	// end picking
			bselect = false;
		}
		if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
			return;
		glGetIntegerv(GL_VIEWPORT, viewport);

		glSelectBuffer(BUFSIZE, selectBuf);
		(void)glRenderMode(GL_SELECT);

		glInitNames();
		glPushName(0);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		// create 5x5 pixel picking region near cursor location *
		gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y),
			5.0, 5.0, viewport);
		gluPerspective(80, 1, 1, 100);
		gluLookAt(camera_X, camera_Y, camera_Z, 0, 1, 0, 0, 1, 0);

		drawAll();
		glPopMatrix();
		//glFlush();

		hits = glRenderMode(GL_RENDER);
		processHits(hits, selectBuf);

		return;
	} */
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	//gluPerspective(45.0f, (float)(screenWidth) / screenHeight, 1.0f, 10000.0f);
	gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(30.0, 1, 0.5, 0);
	drawAxis();
	glMultMatrixf(matrix);

	
	drawAll();
	//glPopMatrix();
	//glutSolidTeapot(200.0);
	glFlush();
	glutSwapBuffers();
}

void drawAll() {
	//drawAxis();
	//Base
	GLfloat	Diffuse[] = { 0.5f, 0.5f, 0.1f };
	GLfloat	Specular[] = { 0.5f, 0.5f, 0.5f };
	GLfloat	Ambient[] = { 1.0f, 0.0f, 1.0f };
	//glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	//glScaled(0.05, 0.05, 0.05);
	//glTranslatef(object3d->slideX, object3d->slideY, object3d->slideZ);
	glTranslatef(object3d->origin[0], object3d->origin[1], object3d->origin[2]);
	glLoadName(1);
	object3d->Draw2();
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
	glEnable(GL_CULL_FACE);

	initLight();
	initLight2();
	init();
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

	//glutReshapeFunc(reshape);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(keyboardSpecialDown);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
