/*
Create a window with any 2D object and a different sized viewport. Apply window to viewport
transformation on the object. Display both window and viewport. 
*/

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>     //for cin, cout
#include <cstring>      //for memcpy

using namespace std;

const int HEIGHT = 870;
const int WIDTH = 1010;
const int WINDOW_XMIN = -500;
const int WINDOW_XMAX = 0;
const int WINDOW_YMIN = -400;
const int WINDOW_YMAX = 400;
const int VIEWPORT_XMIN = 100;
const int VIEWPORT_XMAX = 500;
const int VIEWPORT_YMIN = -300;
const int VIEWPORT_YMAX = 300;

class Point{
private:
    GLdouble x, y, h;    

public:
    Point(){
        x = y = 0;
        h = 1;
    }

    Point(GLint xCoord, GLint yCoord){
        x = xCoord;
        y = yCoord;
        h = 1;
    }

    Point(GLint xCoord, GLint yCoord, GLint H){
        x = xCoord;
        y = yCoord;
        h = H;
    }

    void setCoords(GLdouble xCoord, GLdouble yCoord){
        x = xCoord;
        y = yCoord;
    }

    void setHomogeneousCoords(GLdouble xCoord, GLdouble yCoord, GLdouble H){
        x = xCoord;
        y = yCoord;
        h = H;
    }

    GLdouble getX() const{
        return x;
    }

    GLdouble getY() const{
        return y;
    }

    GLdouble getH() const{
        return h;
    }

    GLdouble getHomogenousX() const{
        return x * h;

    }

    GLdouble getHomogenousY() const{
        return y * h;
    }
};

class PolygonShape{
private:
    int numVertices;
    Point *points;
    double transformMatrix[3][3];

public:
    PolygonShape(){
        numVertices = 0;
    }

    PolygonShape(int noVertices){
        numVertices = noVertices;
        points = new Point[numVertices];
    }

    int getVertexCount() const{
        return numVertices;
    }

    Point getPoint(int i){
        return points[i];
    }

    void setVertices(int noVertices){
        numVertices = noVertices;
        points = new Point[numVertices];
    }

    void setPoint(int i, GLdouble x, GLdouble y, GLdouble h = 1){
        points[i].setHomogeneousCoords(x, y, h);
    }
    
    void setTransformMatrix(){
        //Perform Window->Viewport Transformation using Translation and Scaling

        double xShift = VIEWPORT_XMIN - WINDOW_XMIN;
        double yShift = VIEWPORT_YMIN - WINDOW_YMIN;
        
        double translateMatrix[3][3] = {    {1, 0, xShift},
                                            {0, 1, yShift},
                                            {0, 0, 1}};                               

        double xScale = (double) (VIEWPORT_XMAX - VIEWPORT_XMIN) / (WINDOW_XMAX - WINDOW_XMIN);
        double yScale = (double) (VIEWPORT_YMAX - VIEWPORT_YMIN) / (WINDOW_YMAX - WINDOW_YMIN);

        Point pivot(VIEWPORT_XMIN, VIEWPORT_YMIN);

        double scaleMatrix[3][3] = {    {xScale, 0, pivot.getHomogenousX() * (1 - xScale)},
                                        {0, yScale, pivot.getHomogenousY() * (1 - yScale)},
                                        {0, 0, 1}};

        double product = 0;

        //Composite Transformation = Scaling * Translation
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                product = 0;

                for(int k = 0; k < 3; k++){
                    product += scaleMatrix[i][k] * translateMatrix[k][j]; 
                }

                transformMatrix[i][j] = product; 
            }
        }
    }

    PolygonShape getViewportPolygon(){

        PolygonShape polyDash(numVertices);
        double values[3];

        for(int i = 0; i < numVertices; i++){
            Point p = getPoint(i);
            
            //[3 x 3] x [3 x 1] = [3 x 1] matrix
            for(int j = 0; j < 3; j++){
                values[j] = transformMatrix[j][0] * p.getHomogenousX() +
                            transformMatrix[j][1] * p.getHomogenousY() + 
                            transformMatrix[j][2] * p.getH();
            }

            polyDash.setPoint(i, values[0]/p.getH(), values[1]/p.getH(), values[2]);
        }

        return polyDash;
    }
};


void initializeDisplay();
void plotComponents();
void plotBoundaries();
void plotPolygon(PolygonShape polygon, bool transformed = false);

PolygonShape polygon;

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Window To Viewport Transformation");

    polygon.setVertices(3);
    polygon.setPoint(0, -300, -300);
    polygon.setPoint(1, -100, -300);
    polygon.setPoint(2, -100, 300);
    //polygon.setPoint(3, -300, 300);

    initializeDisplay();
    glutDisplayFunc(plotComponents);

    glutMainLoop();

    return 1;
}

void initializeDisplay(){
    //Initialize the display parameters

    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);
    glClear(GL_COLOR_BUFFER_BIT);
}

void plotComponents(){
    //Plot the window, viewport and transformations

    plotBoundaries();
    plotPolygon(polygon);
    polygon.setTransformMatrix();
    PolygonShape polygonDash = polygon.getViewportPolygon();
    plotPolygon(polygonDash, true);
}

void plotBoundaries(){
    //Plot the window and viewport boundaries

    glLineWidth(3);

    //Title of window area
    glColor3d(0, 0, 1); //Blue color
    unsigned char windowString[] = "Window Area";
    glutBitmapLength(GLUT_BITMAP_HELVETICA_18, windowString);
    glRasterPos2d(-320, 410);

    for(int i = 0; i < strlen((const char *)windowString); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, windowString[i]);
    }

    //Plot the window area
    glBegin(GL_LINE_LOOP);
    glVertex2f(WINDOW_XMIN, WINDOW_YMIN);
    glVertex2f(WINDOW_XMAX, WINDOW_YMIN);
    glVertex2f(WINDOW_XMAX, WINDOW_YMAX);
    glVertex2f(WINDOW_XMIN, WINDOW_YMAX);
    glEnd();

    //Title of viewport area
    glColor3d(1, 0, 0); //Red color
    unsigned char viewportString[] = "Viewport Area";
    glutBitmapLength(GLUT_BITMAP_HELVETICA_18, viewportString);
    glRasterPos2d(240, 310);

    for(int i = 0; i < strlen((const char *)viewportString); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, viewportString[i]);
    }

    //Plot the viewport area
    glBegin(GL_LINE_LOOP);
    glVertex2f(VIEWPORT_XMIN, VIEWPORT_YMIN);
    glVertex2f(VIEWPORT_XMAX, VIEWPORT_YMIN);
    glVertex2f(VIEWPORT_XMAX, VIEWPORT_YMAX);
    glVertex2f(VIEWPORT_XMIN, VIEWPORT_YMAX);
    glEnd();

    glFlush();
}

void plotPolygon(PolygonShape polygon, bool transformed){
    //To draw a given polygon

    if(!transformed){
        glColor3d(0, 0, 1); //Blue color
    } else{
        glColor3d(1, 0, 0); //Red Color
    }

    glBegin(GL_POLYGON);

    for(int i = 0; i < polygon.getVertexCount(); i++){
        Point p = polygon.getPoint(i);
        glVertex2f(p.getX(), p.getY());
    }

    glEnd();
}

