/* 
	3D Apple
	Run: g++ SineTransform.cpp -o ./a.out -lGL -lGLU -lglut && ./a.out
*/


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 800;
const int FPS = 60;

int iteration = 0;

void initializeDisplay();
void drawApple();
void mainLoop(int val);
void keyboardKeys(unsigned char key, int x, int y);

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3D Apple");

	glEnable(GL_DEPTH_TEST);	//3D

	initializeDisplay();

	glutKeyboardFunc(keyboardKeys);
	glutDisplayFunc(drawApple);
	glutTimerFunc(1000/FPS, mainLoop, 0);
	glutMainLoop();

	return 1;
}

void initializeDisplay(){
	glClearColor(1, 1, 1, 1);	//Clear display
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(100, 1, 0.01, 3);	//100deg FoVy, 1 AR, 0.01 Near, 3 Far


	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);	//Camera, Centre, Up Vector
}

void drawApple(){
	//Draw and rotate an apple

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//Total figure
	glPushMatrix();
	glTranslatef(0, 1, 0);			//Shift entire object back towards centre
	glRotatef(iteration, 0, 1, 0);	//Rotate about X-axis, 
									//based on iteration value

	//Apple
	glPushMatrix();
	glTranslatef(0, -1, 0);			//Draw the apple below the stick & leaf
	glColor3d(1, 0, 0);				//Red
	glutSolidSphere(0.75, 20, 20);	//Radius, Slices, Stacks
	glPopMatrix();

	//Stem
	glPushMatrix();

	glColor3d(0, 0, 0);				//Yellow
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3d(0, -0.5, 0);
	glVertex3d(0, 0, 0);
	glPopMatrix();

	//Leaf
	glPushMatrix();
	glColor3d(0, 1, 0);					//Green
	glutSolidCone(0.15, 0.75, 20, 20);	//Radius, Height, Slices, Stacks
	glPopMatrix();

	glPopMatrix();

	glFlush();
}

void mainLoop(int val){
	drawApple();
	//iteration = (iteration + 5) % 100000;	//Auto-rotate
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, mainLoop, 0);
}

void keyboardKeys(unsigned char key, int x, int y){
	//Callback for keyboard

	key = tolower(key);

	if(key == ' '){
		iteration += 5;
	}
}