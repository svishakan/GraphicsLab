/* To draw a wireframe cone and animate it*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>

using namespace std;

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int FPS = 30;

int iteration = 0;	//Variable to keep track of animation

void initializeDisplay();
void drawCone();
void mainLoop(int val);

int main(int argc, char **argv){

	//Initialize the GLUT Primitives for Output
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Wireframe Cone");
	glEnable(GL_DEPTH_TEST);

	initializeDisplay();

	glutDisplayFunc(drawCone);
	glutTimerFunc(1000/FPS, mainLoop, 0);
	glutMainLoop();

	return 1;
}

void initializeDisplay(){

	//To clear the display and set the matrix mode & projection
	glClearColor(0, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	//glOrtho(-2, 2, -2, 2, -2, 2);
	
	//Perspective Projection with 100 deg FoVy
	gluPerspective(100, 1, 0.01, 3);	
	
	//Camera, Centre, Up Vector
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
}

void drawCone(){
	//To draw a cone and animate it

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 0, 1);
	
	//Animate the cone based on iteration value
	glPushMatrix();
	glRotatef(iteration, 1, 0, 0);	//About X axis
	glutWireCone(0.75, 1.25, 20, 20);
	glPopMatrix();

	glFlush();
}

void mainLoop(int val){

	//Callback function for the timer function
	drawCone();
	iteration = (iteration + 5) % 100000;
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, mainLoop, 0);
	//Keep iterating the animation
}