//Ball Bounce

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int FPS = 10;

int motion = 0;		//For animation
int direction = 1;	//For direction

void initializeDisplay();
void bounceBall();
void mainLoop(int val);
void keyboardKeys(unsigned int val, int x, int y);
void setLights();

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutCreateWindow("Ball Bounce");

	initializeDisplay();

	glutDisplayFunc(bounceBall);
	glutTimerFunc(1000/FPS, mainLoop, 0);
	glutMainLoop();
	
	return 1;
}

void initializeDisplay(){
	glClearColor(1, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	setLights();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	//VERY IMPORTANT TO INCLUDE THIS
	//gluPerspective(100, 1, 0.01, 10);
	
	glOrtho(-5, 5, -5, 5, -5, 5);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	//Camera: (0,0,1) works for ortho, but for perspective, (0, 0, 5) is essential
}

void mainLoop(int val){
	motion += 1 * direction;

	if(motion > 4 || motion < -2){
		direction *= -1;	
	}

	bounceBall();
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, mainLoop, 0);
}

void bounceBall(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	//Base
	glPushMatrix();
	glColor3d(0, 1, 0);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex3d(-5, -4, 0);
	glVertex3d(5, -4, 0);
	glEnd();
	glPopMatrix();

	//Ball
	glPushMatrix();
	glColor3d(0, 0, 1);
	//glRotatef(45, 0, 0, 1);
	glTranslatef(0, motion, 0);
	//glutSolidCube(1);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	glPopMatrix();
	

	glFlush();
	glutSwapBuffers();
}

void setLights(){
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	
	glShadeModel(GL_SMOOTH);

	float lightPos[] = {10, 15, 5};
	float lightCol[] = {0.7, 0.7, 0.7, 1};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightCol);
}