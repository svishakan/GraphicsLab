//To perform 2D Transformations on objects and to render the final output along with the original object
//Scaling

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

    Point getScaledPoint(double ScaleX, double ScaleY, Point fixed){
        double xFixedValue = fixed.getX() * (1 - ScaleX);
        double yFixedValue = fixed.getY() * (1 - ScaleY);

        double scalingMatrix[3][3] = {  {ScaleX, 0, xFixedValue},
                                        {0, ScaleY, yFixedValue},
                                        {0, 0, 1}};

        double values[3];

        for(int i = 0; i < 3; i++){
            values[i] = scalingMatrix[i][0] * getHomogenousX() +
                        scalingMatrix[i][1] * getHomogenousY() +
                        scalingMatrix[i][2] * getH();
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
void scalePolygon(PolygonShape polygon, double scaleX, double scaleY, Point fixed);

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("2D Transformations - Scaling");

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
    polygon.setPoint(0, 20, 100);
    polygon.setPoint(1, 50, 200);
    polygon.setPoint(2, 70, 100);
    polygon.setPoint(3, 50, 0);


    drawPolygon(polygon);

    //Set fixed point
    Point fixed(200, 200, 1);

    scalePolygon(polygon, 2, 1.5, fixed);

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

void scalePolygon(PolygonShape polygon, double scaleX, double scaleY, Point fixed = Point(0, 0, 1)){
    //To translate a given polygon using the scale factors and fixed point

    //Plot the fixed point
    glColor3d(1, 0, 1); //Purple Color
    glPointSize(5);

    glBegin(GL_POINTS);
    glVertex2d(fixed.getX(), fixed.getY());
    glEnd();

    glColor3d(0, 0, 1); //Blue Color

    glBegin(GL_POLYGON);

    for(int i = 0; i < polygon.getVertexCount(); i++){
        Point p = polygon.getPoint(i);
        Point pDash = p.getScaledPoint(scaleX, scaleY, fixed);
        glVertex2d(pDash.getX(), pDash.getY()); //Plot the normal coordinates
    }

    glEnd();
}


