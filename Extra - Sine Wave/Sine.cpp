/* To draw a sine wave and animate it using OpenGL */

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;

const int FPS = 10;

const int X = 25;
const int Y = 4;

int offset = 0;

void initializeDisplay();
void mainLoop(int val);
void drawSineWave();
void drawAxis();

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Sine Wave");

    initializeDisplay();

    glutDisplayFunc(drawSineWave);
    glutTimerFunc(1000/FPS, mainLoop, 0);
    glutMainLoop();

    return 0;
}

void initializeDisplay(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glLineWidth(5);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-X, X, -Y, Y);
}

void mainLoop(int val){
    drawSineWave();
    offset++;
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, mainLoop, 0);
}

void drawSineWave(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawAxis();
    
    glColor3d(1, 0, 0);
    glBegin(GL_POINTS);

    for(double i = -X; i <= X; i += 0.01){
        glVertex2f(i, sin(i + offset));
    }

    glEnd();
    glFlush();
}

void drawAxis(){
    glColor3d(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2d(-X, 0);
    glVertex2d(X, 0);
    glEnd();
}