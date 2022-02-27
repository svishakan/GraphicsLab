//Compilation: g++ SineWave.cpp -o a.out -lGL -lGLU -lglut && ./a.out


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int FPS = 30;

int offset = 0; //for animation

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
void mainLoop(int val);
void plotDiagram();
void plotSineWave(GLfloat xc, GLfloat yc, GLfloat radius, bool up);
void plotAxis();
void setPixel(GLfloat x, GLfloat y);
void plotTopSemiCircle(GLfloat xc, GLfloat yc, Point pt);
void plotBottomSemiCircle(GLfloat xc, GLfloat yc, Point pt);

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Sine Wave Using Circle Algorithm");
    
    initializeDisplay();

    glutDisplayFunc(plotDiagram);
    glutTimerFunc(1000/FPS, mainLoop, 0);
    glutMainLoop();

    return 1;
}

void initializeDisplay(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);
}

void mainLoop(int val){
    plotDiagram();
    offset = (offset + 1) % FPS;
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, mainLoop, 0);
}

void plotDiagram(){
    glClear(GL_COLOR_BUFFER_BIT);   //Clear the window

    plotAxis();

    glColor3d(0, 1, 0);
    glPointSize(3);

    bool up = true;

    float STEP_SIZE = WINDOW_WIDTH/8;

    for(GLfloat x = -WINDOW_WIDTH/2; x <= WINDOW_WIDTH/2; x += STEP_SIZE){
        plotSineWave(x + offset, 0, STEP_SIZE/2, up);
        up = !up;
    }

    glFlush();

}

void plotSineWave(GLfloat xc, GLfloat yc, GLfloat radius, bool up){
    Point pt;

    GLfloat p = 1 - radius;
    pt.setCoords(0, radius);

    if(up){
        plotTopSemiCircle(xc, yc, pt);
    } else{
        plotBottomSemiCircle(xc, yc, pt);
    }

    while(pt.getX() < pt.getY()){
        pt.incX();

        if(p < 0){
            p += 2 * pt.getX() + 1;
        } else{
            pt.decY();
            p += 2 * (pt.getX() - pt.getY()) + 1;
        }

        if(up){
            plotTopSemiCircle(xc, yc, pt);
        } else{
            plotBottomSemiCircle(xc, yc, pt);
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
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void plotTopSemiCircle(GLfloat xc, GLfloat yc, Point pt){
    //1st and 2nd quadrant
    setPixel(xc + pt.getX(), yc + pt.getY());
    setPixel(xc + pt.getY(), yc + pt.getX());

    setPixel(xc - pt.getX(), yc + pt.getY());
    setPixel(xc - pt.getY(), yc + pt.getX());
}

void plotBottomSemiCircle(GLfloat xc, GLfloat yc, Point pt){
    //3rd and 4th quadrant
    setPixel(xc - pt.getX(), yc - pt.getY());
    setPixel(xc - pt.getY(), yc - pt.getX());

    setPixel(xc + pt.getX(), yc - pt.getY());
    setPixel(xc + pt.getY(), yc - pt.getX());
}