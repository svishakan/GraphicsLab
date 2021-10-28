/* To draw and reflect an apple using OpenGL */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <math.h>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int X_MIN = -400;
const int X_MAX = 400;
const int Y_MIN = -400;
const int Y_MAX = 400;

class Point{
    private:
        float x, y, h;
    
    public:
        Point(){
            x = y = 0;
            h = 1;
        }
        
        Point(float X, float Y){
            x = X;
            y = Y;
            h = 1;
        }

        void setCoords(float X, float Y){
            x = X;
            y = Y;
            h = 1;
        }

        float getX(){
            return x;
        }

        float getY(){
            return y;
        }

        float getH(){
            return h;
        }

        void incX(){
            x++;
        }
        
        void decY(){
            y--;
        }

        Point reflectPointAboutOrigin(){
            float reflectionMatrix[3][3] = {    {0, -1, 0},
                                                {-1, 0, 0},
                                                {0, 0, 1}};

            float values[3];

            for(int i = 0; i < 3; i++){
                values[i] = reflectionMatrix[i][0] * x +
                            reflectionMatrix[i][1] * y +
                            reflectionMatrix[i][2] * h;    
            }

            return Point(values[0], values[1]);
        }
};

void initializeDisplay();
void renderContents();
void drawAxis();
void drawApple();
void drawReflectedApple();
void midPointCircle(int xc, int yc, int radius);
void plotPoints(int xc, int yc, Point pt);
void setPixel(float x, float y);

Point appleCentre;
Point appleStickBottom, appleStickTop;
Point biteCentre;

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Apple");

    appleCentre.setCoords(150, 150);
    appleStickBottom.setCoords(150, 225);
    appleStickTop.setCoords(150, 275);
    biteCentre.setCoords(220, 200);

    initializeDisplay();

    glutDisplayFunc(renderContents);
    glutMainLoop();

    return 1;
}

void initializeDisplay(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(X_MIN, X_MAX, Y_MIN, Y_MAX);

    glPointSize(3);
    glLineWidth(5);
}

void renderContents(){
    drawAxis();
    drawApple();
    drawReflectedApple();
}

void drawAxis(){
    glColor3d(0, 0, 1);

    glBegin(GL_LINES);
    glVertex2d(X_MIN, 0);
    glVertex2d(X_MAX, 0);

    glVertex2d(0, Y_MIN);
    glVertex2d(0, Y_MAX);

    glEnd();
    glFlush();
}

void drawApple(){
    glColor3d(1, 0, 0);

    for(float i = 0; i < 75; i += 0.1)
        midPointCircle(appleCentre.getX(), appleCentre.getY(), i);

    glColor3d(1, 1, 1);

    for(float i = 0; i < 50; i += 0.1)
        midPointCircle(biteCentre.getX(), biteCentre.getY(), i);

    glColor3d(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(appleStickBottom.getX(), appleStickBottom.getY());
    glVertex2f(appleStickTop.getX(), appleStickTop.getY());
    glEnd();
}

void drawReflectedApple(){
    Point appleCentreDash = appleCentre.reflectPointAboutOrigin();
    Point appleStickBottomDash = appleStickBottom.reflectPointAboutOrigin();
    Point appleStickTopDash = appleStickTop.reflectPointAboutOrigin();
    Point biteCentreDash = biteCentre.reflectPointAboutOrigin();

    glColor3d(1, 0, 0);

    for(float i = 0; i < 75; i += 0.1)
        midPointCircle(appleCentreDash.getX(), appleCentreDash.getY(), i);

    glColor3d(1, 1, 1);

    for(float i = 0; i < 50; i += 0.1)
        midPointCircle(biteCentreDash.getX(), biteCentreDash.getY(), i);
    
    glColor3d(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(appleStickBottomDash.getX(), appleStickBottomDash.getY());
    glVertex2f(appleStickTopDash.getX(), appleStickTopDash.getY());
    glEnd();
}

void midPointCircle(int xc, int yc, int radius){
    Point pt(0, radius);
    int p = 1 - radius;

    plotPoints(xc, yc, pt);

    while(pt.getX() < pt.getY()){
        pt.incX();

        if(p <= 0){
            p += 2 * pt.getX() + 1;
        } else{
            p += 2 * (pt.getX() - pt.getY()) + 1;
            pt.decY();
        }

        plotPoints(xc, yc, pt);
    }

    glFlush();
}

void plotPoints(int xc, int yc, Point pt){
    setPixel(xc + pt.getX(), yc + pt.getY());
    setPixel(xc + pt.getX(), yc - pt.getY());
    setPixel(xc - pt.getX(), yc - pt.getY());
    setPixel(xc - pt.getX(), yc + pt.getY());
    setPixel(xc + pt.getY(), yc + pt.getX());
    setPixel(xc + pt.getY(), yc - pt.getX());
    setPixel(xc - pt.getY(), yc - pt.getX());
    setPixel(xc - pt.getY(), yc + pt.getX());
}

void setPixel(float x, float y){
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}