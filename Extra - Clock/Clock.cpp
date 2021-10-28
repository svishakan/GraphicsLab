/* To draw an animate a clock using OpenGL */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

const int X = 300;
const int Y = 300;

const int FPS = 10;
int iteration = 0;

class Point{
    private:
        double x, y, h;

    public:
        Point(){
            x = y = 0;
            h = 1;
        }
        
        Point(double X, double Y){
            x = X;
            y = Y;
            h = 1;
        }

        void setCoords(double X, double Y){
            x = X;
            y = Y;
            h = 1;
        }

        double getX(){
            return x;
        }

        double getY(){
            return y;
        }

        double getH(){
            return h;
        }

        void incX(){
            x++;
        }
        
        void decY(){
            y--;
        }

        Point rotate(double angle){
            double angleRadians = angle * 3.14 / 180;
            double cosAngle = cos(angleRadians);
            double sinAngle = sin(angleRadians);

            double rotationMatrix[3][3] = { {cosAngle, -sinAngle, 0},
                                            {sinAngle, cosAngle, 0},
                                            {0, 0, 1}};
            
            double values[3];

            for(int i = 0; i < 3; i++){
                values[i] = rotationMatrix[i][0] * x +
                            rotationMatrix[i][1] * y +
                            rotationMatrix[i][2] * h;
            }

            return Point(values[0], values[1]); 
        }
};


void initializeDisplay();
void midPointCircle(int xc, int yc, int radius);
void plotCirclePoints(int xc, int yc, Point pt);
void setPixel(double x, double y);
void renderClock();
void mainLoop(int val);
void bresenhamLine(Point a, Point b);

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Clock");

    initializeDisplay();

    glutDisplayFunc(renderClock);
    glutTimerFunc(1000/FPS, mainLoop, 0);
    glutMainLoop();

    return 1;
}

void initializeDisplay(){
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-X, X, -Y, Y);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void renderClock(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(1, 1, 0);
    glPointSize(10);

    midPointCircle(0, 0, 150);

    Point hourBottom(0, 0);
    Point hourTop(0, 70);
    Point minuteBottom(0, 0);
    Point minuteTop(0, 140);

    glColor4f(0, 1, 0, 1);
    glPointSize(3);

    Point hourTopDash = hourTop.rotate(-0.12 * 0.12 * iteration);
    Point minuteTopDash = minuteTop.rotate(-0.12 * iteration);

    bresenhamLine(hourBottom, hourTopDash);
    bresenhamLine(minuteBottom, minuteTopDash);
    
    glFlush();
}

void mainLoop(int val){
    renderClock();
    iteration++;
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, mainLoop, 0);
}

void midPointCircle(int xc, int yc, int radius){
    Point pt(0, radius);
    int p = 1 - radius;

    plotCirclePoints(xc, yc, pt);

    while(pt.getX() < pt.getY()){
        pt.incX();

        if(p <= 0){
            p += 2 * pt.getX() + 1;
        } else{
            p += 2 * (pt.getX() - pt.getY()) + 1;
            pt.decY();
        }

        plotCirclePoints(xc, yc, pt);
    }

    glFlush();
}

void plotCirclePoints(int xc, int yc, Point pt){
    setPixel(xc + pt.getX(), yc + pt.getY());
    setPixel(xc + pt.getX(), yc - pt.getY());
    setPixel(xc - pt.getX(), yc - pt.getY());
    setPixel(xc - pt.getX(), yc + pt.getY());
    setPixel(xc + pt.getY(), yc + pt.getX());
    setPixel(xc + pt.getY(), yc - pt.getX());
    setPixel(xc - pt.getY(), yc - pt.getX());
    setPixel(xc - pt.getY(), yc + pt.getX());
}

void setPixel(double x, double y){
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void bresenhamLine(Point a, Point b){
    GLdouble dx, dy, x, y, p, inc_x, inc_y, inc_p1, inc_p2;
    GLdouble x_sign, y_sign;

    dx = b.getX() - a.getX();
    dy = b.getY() - a.getY();

    x_sign = dx/abs(dx);
    y_sign = dy/abs(dy);

    inc_x = 1 * x_sign;
    inc_y = 1 * y_sign;

    dx = abs(dx);
    dy = abs(dy);

    x = a.getX();
    y = a.getY();

    glBegin(GL_POINTS);

    if(abs(dx) > abs(dy)){
        glVertex2f(x, y);

        p = (2 * dy) - dx;
        inc_p1 = 2 * (dy - dx);
        inc_p2 = 2 * dy;

        for(int i = 0; i < dx; i++){
            if(p >= 0){
                y += inc_y;
                p += inc_p1;
            } else{
                p += inc_p2;
            }

            x += inc_x;

            glVertex2f(x, y);
        }
    } else{
        glVertex2f(x, y);

        p = (2 * dx) - dy;
        inc_p1 = 2 * (dx - dy);
        inc_p2 = 2 * dx;

        for(int i = 0; i < dy; i++){
            if(p >= 0){
                x += inc_x;
                p += inc_p1;
            } else{
                p += inc_p2;
            }

            y += inc_y;

            glVertex2f(x, y);
        }
    }

    glEnd();
    glFlush();
}