//To perform 2D Transformations on objects and to render the final output along with the original object
//Shearing

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int X_MIN = -400;
const int X_MAX = 400;
const int Y_MIN = -400;
const int Y_MAX = 400;

enum Axes {xAxis, yAxis};

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

    void setCoords(GLint xCoord, GLint yCoord){
        x = xCoord;
        y = yCoord;
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

    Point getShearAboutXAxis(double shearParam, double yRefLine = 0){
        double shearMatrix[3][3] = {{1, shearParam, -shearParam * yRefLine},
                                    {0, 1, 0},
                                    {0, 0, 1}};

        double values[3];

        for(int i = 0; i < 3; i++){
            values[i] = shearMatrix[i][0] * getHomogenousX() +
                        shearMatrix[i][1] * getHomogenousY() +
                        shearMatrix[i][2] * getH();
        }

        return Point(values[0]/h, values[1]/h, values[2]);
    }

    Point getShearAboutYAxis(double shearParam, double xRefLine = 0){
        double shearMatrix[3][3] = {{1, 0, -shearParam * xRefLine},
                                    {shearParam, 1, 0},
                                    {0, 0, 1}};

        double values[3];

        for(int i = 0; i < 3; i++){
            values[i] = shearMatrix[i][0] * getHomogenousX() +
                        shearMatrix[i][1] * getHomogenousY() +
                        shearMatrix[i][2] * getH();
        }

        return Point(values[0]/h, values[1]/h, values[2]);
    }
};

class PolygonShape{
private:
    int numVertices;
    Point *points;

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

    void setPoint(int i, GLint x, GLint y){
        points[i].setCoords(x, y);
    }
};

void initializeDisplay();
void plotTransformation();
void drawAxes();
void drawPolygon(PolygonShape polygon);
void shearPolygon(PolygonShape polygon, Axes axis, double shearParam, double refLine);

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("2D Transformations - Shearing");

    initializeDisplay();
    glutDisplayFunc(plotTransformation);
    glutMainLoop();

    return 1;
}

void initializeDisplay(){
    //Initialize the display parameters

    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(X_MIN, X_MAX, Y_MIN, Y_MAX);
    glClear(GL_COLOR_BUFFER_BIT);   //Clear the display window
}

void plotTransformation(){
    drawAxes();

    //Set coordinates for a polygon
    PolygonShape polygon(4);
    polygon.setPoint(0, 0, 0);
    polygon.setPoint(1, 0, 50);
    polygon.setPoint(2, 100, 50);
    polygon.setPoint(3, 100, 0);


    drawPolygon(polygon);

    //shear the polygon
    shearPolygon(polygon, yAxis, 2, -50);

    glFlush();
}

void drawAxes(){
    //To draw the X and Y axes

    glColor3d(0, 0, 0); //Black color

    glBegin(GL_LINES);

    //X-axis
    glVertex2d(X_MIN, 0);
    glVertex2d(X_MAX, 0);

    //Y-axis
    glVertex2d(0, Y_MIN);
    glVertex2d(0, Y_MAX);

    glEnd();
}

void drawPolygon(PolygonShape polygon){
    //To draw a given polygon

    glColor3d(1, 0, 0); //Red color

    glBegin(GL_POLYGON);

    for(int i = 0; i < polygon.getVertexCount(); i++){
        Point p = polygon.getPoint(i);
        glVertex2d(p.getX(), p.getY());
    }

    glEnd();
}

void shearPolygon(PolygonShape polygon, Axes axis, double shearParam, double refLine = 0){
    //To shear a polygon about axis and shear parameter

    //Plot the given line
    glColor3f(1, 0, 1);

    glBegin(GL_LINES);

    switch(axis){
        case xAxis:
            glVertex2d(X_MIN, 0);
            glVertex2d(X_MAX, 0);
            break;
        case yAxis:
            glVertex2d(0, Y_MIN);
            glVertex2d(0, Y_MAX);
            break;
        default:
            return;
    }

    glEnd();

    glEnable(GL_BLEND);     //enable blending (translucent colors)
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //set the blend function for translucency

    glColor4f(0, 0, 1, 0.6); //Blue Color, with alpha (transparency) factor as 0.6

    glBegin(GL_POLYGON);

    for(int i = 0; i < polygon.getVertexCount(); i++){
        Point p = polygon.getPoint(i);
        Point pDash;

        switch(axis){
            case xAxis:
                pDash = p.getShearAboutXAxis(shearParam, refLine);
                break;
            case yAxis:
                pDash = p.getShearAboutYAxis(shearParam, refLine);
                break;
            default:
                return;
        }

        glVertex2d(pDash.getX(), pDash.getY()); //Plot the normal coordinates
    }

    glEnd();

    glDisable(GL_BLEND);     //disable blending (translucent colors)
    glDepthMask(GL_TRUE);
}


