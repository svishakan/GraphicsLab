/*
	Draw a sine wave using 2D transformations
	Run: g++ SineTransform.cpp -o ./a.out -lGL -lGLU -lglut && ./a.out
*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cstring>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

class Point{
private:
    GLfloat x, y;

public:
    Point(){
        x = y = 0;
    }

    Point(GLfloat X, GLfloat Y){
        x = X;
        y = Y;
    }

    void setCoords(GLfloat X, GLfloat Y){
        x = X;
        y = Y;
    }

    GLfloat getX(){
        return x;
    }

    GLfloat getY(){
        return y;
    }

    void incX(){
        x++;
    }

    void decY(){
        y--;
    }
};

void initializeDisplay();
void drawContents();
void drawSineWave();
void plotAxis();
void drawSemiCircle(GLfloat xc, GLfloat yc, Point pt);
Point reflectAboutOrigin(GLfloat x, GLfloat y);
void setPixel(GLfloat x, GLfloat y);

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sine Wave Using Transforms");

	initializeDisplay();

	glutDisplayFunc(drawContents);
	glutMainLoop();

	return 1;
}

void initializeDisplay(){
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);
}

void drawContents(){
	//Display contents on the screen
	plotAxis();
	drawSineWave();
}

void drawSineWave(){
	//Draw a single sine wave
	float xc = -100;
	float yc = 0;
	float radius = 100;

	Point pt = Point(0, radius);

	float p = 1 - radius;

	while(pt.getX() < pt.getY()){
		drawSemiCircle(xc, yc, pt);

		pt.incX();

		if(p < 0){
			p += 2 * pt.getX() + 1;
		} else {
			pt.decY();
			p += 2 * (pt.getX() - pt.getY()) + 1;
		}
	}

	glFlush();
}

void plotAxis(){
    //Draw Axis
    glColor3d(1, 0, 0);
    glLineWidth(5);
    
    glBegin(GL_LINES);
    glVertex2d(0, -WINDOW_HEIGHT/2);
    glVertex2d(0, WINDOW_HEIGHT/2);

    glVertex2d(-WINDOW_WIDTH/2, 0);
    glVertex2d(WINDOW_WIDTH/2, 0);

    glEnd();
}

void setPixel(GLfloat x, GLfloat y){
	//Draw a point
	glPointSize(5);
	glColor3d(0, 0, 1);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void drawSemiCircle(GLfloat xc, GLfloat yc, Point pt){
	//Upper semicircle
	setPixel(xc + pt.getX(), yc + pt.getY());
	setPixel(xc + pt.getY(), yc + pt.getX());
	setPixel(xc - pt.getX(), yc + pt.getY());
	setPixel(xc - pt.getY(), yc + pt.getX());

	//Lower Semicircle - Transformation
	Point a = reflectAboutOrigin(xc + pt.getX(), yc + pt.getY());
	Point b = reflectAboutOrigin(xc + pt.getY(), yc + pt.getX());
	Point c = reflectAboutOrigin(xc - pt.getX(), yc + pt.getY());
	Point d = reflectAboutOrigin(xc - pt.getY(), yc + pt.getX());

	//Lower semicircle
	setPixel(a.getX(), a.getY());
	setPixel(b.getX(), b.getY());
	setPixel(c.getX(), c.getY());
	setPixel(d.getX(), d.getY());
}

Point reflectAboutOrigin(GLfloat x, GLfloat y){
	//To get the reflected point about the origin
	double reflect_matrix[3][3] = {{-1, 0, 0},
								{0, -1, 0},
								{0, 0, 1}};

	double values[3];

	for(int i = 0; i < 3; i++){
		values[i] = reflect_matrix[i][0] * x +
					reflect_matrix[i][1] * y + 
					reflect_matrix[i][2] * 1;
	}

	Point pt = Point(values[0], values[1]);

	return pt;
}