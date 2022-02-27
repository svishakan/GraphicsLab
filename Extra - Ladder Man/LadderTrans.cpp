//LadderTrans
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int ITERATION = 0, FPS = 1, STEP = 1;

void myInit() {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-500, 500, -500, 500, -500, 500);
    gluOrtho2D(-1000, 1000, -1000, 1000);

    //glEnable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void plotAll(int x, int y, int xc, int yc) {
    glVertex2d(x + xc, y + yc);
    glVertex2d(x + xc, -y + yc);
    glVertex2d(-x + xc, y + yc);
    glVertex2d(-x + xc, -y + yc);

    glVertex2d(y + xc, x + yc);
    glVertex2d(y + xc, -x + yc);
    glVertex2d(-y + xc, x + yc);
    glVertex2d(-y + xc, -x + yc);
}

void midpointcircle(int xc, int yc, int r) {
    int x = r, y = 0, pk = 1 - r;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    plotAll(x, y, xc, yc);

    while (x > y) {
        y++;

        if (pk < 0) {
            pk += (2 * y) + 1;
        }
        else {
            x--;
            pk += (2 * y) - (2 * x) + 1;
        }
        plotAll(x, y, xc, yc);
    }
    glEnd();
    glFlush();
}

void bresenham(int x0, int y0, int x1, int y1)
{
    int x, y, dy, dx, pk;
    dx = x1 - x0;
    dy = y1 - y0;

    x = x0;
    y = y0;

    if (dy < dx)
    {
        pk = (2 * dy) - dx; //p0

        glBegin(GL_POINTS);
        for (x = x0; x < x1; x++)
        {
            if (pk > 0)
            {
                glVertex2d(x, ++y);
                pk = pk + (2 * dy) - (2 * dx);
            }
            else
            {
                glVertex2d(x, y);
                pk = pk + (2 * dy);
            }
        }
        glEnd();
    }
    else
    {
        pk = (2 * dx) - dy;

        glBegin(GL_POINTS);
        for (y = y0; y < y1; y++)
        {
            if (pk > 0)
            {
                glVertex2d(++x, y);
                pk = pk + (2 * dx) - (2 * dy);
            }
            else
            {
                glVertex2d(x, y + 1);
                pk = pk + (2 * dx);
            }
        }
        glEnd();
    }
    glFlush();
}

void drawPerson() {
    int move = ITERATION * 100;
    midpointcircle(40, 150+move, 50);
    bresenham(40, -50+move, 40, 100+move);
    bresenham(-20, -50+move, 100, -50+move);
    bresenham(-20, -100+move, -20, -50+move);
    bresenham(100, -100+move, 100, -50+move);
}


void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPerson();

    bresenham(-100, -200, -100, 500); //left ladder line
    bresenham(200, -200, 200, 500); //right ladder line
    //rails in between
    bresenham(-100, -100, 200, -100);
    bresenham(-100, 0, 200, 0);
    bresenham(-100, 100, 200, 100);
    bresenham(-100, 200, 200, 200);
    bresenham(-100, 300, 200, 300);
    bresenham(-100, 400, 200, 400);

    glFlush();



}


void updatemove() {
    ITERATION += STEP;
    if (ITERATION > 4) STEP = -1;
    if (ITERATION <= 0) STEP = 1;
    myInit();
}


void Timer(int i) {
    updatemove();
    glutPostRedisplay();
    myDisplay();

    glutTimerFunc(1000 / FPS, Timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Stick Man");
    glutDisplayFunc(myDisplay);
    glutTimerFunc(1000 / FPS, Timer, 0);
    myInit();
    glutMainLoop();
    return 1;
}
