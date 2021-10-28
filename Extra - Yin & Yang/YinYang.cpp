/* To draw Yin and Yang image using OpenGL */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <cstring>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

bool flag = false;

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
            x += 1;
        }

        void decY(){
            y -= 1;
        }
};

void initializeDisplay();
void drawYinYang();
void midPointCircle(GLfloat xc, GLfloat yc, GLfloat radius, bool left);
void setPixel(GLfloat x, GLfloat y);
void plotCirclePoints(GLfloat xc, GLfloat yc, Point pt);
void plotLeftSemiCircle(GLfloat xc, GLfloat yc, Point pt);
void plotRightSemiCircle(GLfloat xc, GLfloat yc, Point pt);

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Yin and Yang");

    initializeDisplay();
    
    glutDisplayFunc(drawYinYang);
    glutMainLoop();

    return 1;
}

void initializeDisplay(){
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

void drawYinYang(){
    glPointSize(3);

    //To prevent redraw --- NOTE: need to find why redraw occurs.
    if(flag) return;
    else flag = !flag;

    //Idea: Draw concentric circles, to simulate filling the circle

    //Left Outer Circle
    glColor3d(1, 1, 1);
    for(GLfloat i=0;i<=300;i+=0.1) 
        midPointCircle(400, 400, i, true);

    //Right Outer Circle
    glColor3d(0, 0, 0);
    for(GLfloat i=0;i<=300;i+=0.1) 
        midPointCircle(400, 400, i, false);

    //Right Inner Boundary
    glColor3d(1, 1, 1);
    for(GLfloat i=0;i<=150;i+=0.1) 
    midPointCircle(400, 250, i, false);

    //Left Inner Boundary
    glColor3d(0, 0, 0);
    for(GLfloat i=0;i<=150;i+=0.1) 
    midPointCircle(400, 550, i, true);

    //Upper Inner Circle
    glColor3d(1, 1, 1);
    for(GLfloat i=0;i<=50;i+=0.1) 
        midPointCircle(400, 550, i, false);
    for(GLfloat i=0;i<=50;i+=0.1)
        midPointCircle(400, 550, i, true);

    //Lower Inner Circle
    glColor3d(0, 0, 0);
    for(GLfloat i=0;i<=50;i+=0.1) 
        midPointCircle(400, 250, i, false);
    for(GLfloat i=0;i<=50;i+=0.1)
        midPointCircle(400, 250, i, true);
}

void midPointCircle(GLfloat xc, GLfloat yc, GLfloat radius, bool left){
    Point pt;

    GLfloat p = 1 - radius;

    pt.setCoords(0, radius);

    if(left){
        plotLeftSemiCircle(xc, yc, pt);
    } else{
        plotRightSemiCircle(xc, yc, pt);
    }

    while(pt.getX() < pt.getY()){
        pt.incX();

        if(p < 0){
            p += 2 * pt.getX() + 1;
        } else{
            pt.decY();
            p += 2 * (pt.getX() - pt.getY()) + 1;
        }

        if(left){
            plotLeftSemiCircle(xc, yc, pt);
        } else{
            plotRightSemiCircle(xc, yc, pt);
        }

    }

    glFlush();
}

void setPixel(GLfloat x, GLfloat y){
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plotCirclePoints(GLfloat xc, GLfloat yc, Point pt){
    plotLeftSemiCircle(xc, yc, pt);
    plotRightSemiCircle(xc, yc, pt);
}

void plotLeftSemiCircle(GLfloat xc, GLfloat yc, Point pt){
    setPixel(xc - pt.getX(), yc + pt.getY());
    setPixel(xc - pt.getY(), yc + pt.getX());
    setPixel(xc - pt.getX(), yc - pt.getY());
    setPixel(xc - pt.getY(), yc - pt.getX());
}

void plotRightSemiCircle(GLfloat xc, GLfloat yc, Point pt){
    setPixel(xc + pt.getX(), yc + pt.getY());
    setPixel(xc + pt.getY(), yc + pt.getX());
    setPixel(xc + pt.getX(), yc - pt.getY());
    setPixel(xc + pt.getY(), yc - pt.getX());
}
