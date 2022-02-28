/*OpenGL Template*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int FPS = 10;

int motion = 0;

void initializeDisplay();
void setLights();
void myKeyboardFunc(unsigned char key, int x, int y);
void mainLoop(int val);
void miscFunctions();

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Template")

	glEnable(GL_DEPTH);	//If necessary

	initializeDisplay();

	glutKeyboardFunc(myKeyboardFunc);
	glutTimerFunc(1000/FPS, mainLoop, 0);

	glutMainLoop();

	return 1;
}

void initializeDisplay(){
	glEnable(GL_BLEND);	//If required
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	setLights();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	//Very Important, Must in 3D.

	glOrtho2D(-WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);

	//3D - Orthographic
	glOrtho(-X, X, -Y, Y, -Z, Z); //keep it usually within +/- 10

	//3D - Perspective
	gluPerspective(100, 1, 0.01, 10);	//FoVy, AR, Near, Far

	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0)	//Camera, Centre, Up Vector
	//Adjust camera if not able to view correctly.

	//Use if only ABSOLUTELY NECESSARY
	//glMatrixMode(GL_MODELVIEW);

}

void setLights(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);	//To apply glColor3d() to objects without glMaterialfv()
	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glShadeModel(GL_SMOOTH);

	float lightPos[] = {0.0, 10.0, 0.0};
	float lightCol[] = {0.7, 0.7, 0.7, 1};

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightCol);
	//Also GL_DIFFUSE, GL_SPECULAR
}

void mainLoop(int val){
	//doSomething();
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, mainLoop, 0);
}

void myKeyboardFunc(unsigned char key, int x, int y){
	char x = tolower(key);

	switch(x){
		case ' ':
			//doSomethingDifferent();
			break;
	}

	glutPostRedisplay();
}

void miscFunctions(){
	glColor3d(1, 1, 1);	//RGB
	glColor4f(0.5, 0.5, 0.5, 0.5);	//RGBA

	glBegin(GL_LINES);	//GL_POLYGON, GL_LINE_LOOP, GL_POINTS, GL_QUADS, GL_TRIANGLES
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	//3D drawings
	glPushMatrix();
	glRotatef(degrees, x, y, z);
	glTranslatef(x, y, z);
	glScalef(x, y, z);
	glutSolidTeapot(size);
	glutWireTeapot(size);
	glutSolidCube(size);
	glutWireCube(size);
	glutSolidCone(base, height, slices, stacks);
	glutSolidSphere(radius, slices, stacks);
	glutSolidTorus(inradius, outradius, sides, rings);
	glPopMatrix();

	//Matrix copies
	memcpy(source, dest, size(source));
}