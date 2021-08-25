//To perform 2D Transformations on objects and to render the final output along with the original object
//Translation

#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int X_MIN = -400;
const int X_MAX = 400;
const int Y_MIN = -400;
const int Y_MAX = 400;

class Point{
private:
    GLint x, y, h;

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

    GLint getX() const{
        return x;
    }

    GLint getY() const{
        return y;
    }

    GLint getH() const{
        return h;
    }

    GLint getHomogenousX() const{
        return x * h;

    }
    GLint getHomogenousY() const{
        return y * h;
    }

    Point getTranslatedPoint(Point translationVector){
        int translationMatrix[3][3] = { {1, 0, translationVector.getHomogenousX()},
                                        {0, 1, translationVector.getHomogenousY()},
                                        {0, 0, 1}};

        int values[3];

        for(int i = 0; i < 3; i++){
            values[i] = translationMatrix[i][0] * getHomogenousX() +
                        translationMatrix[i][1] * getHomogenousY() +
                        translationMatrix[i][2] * getH();
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
void translatePolygon(PolygonShape polygon, Point translationVector);

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("2D Transformations - Translation");

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
    PolygonShape polygon(3);
    polygon.setPoint(0, 20, 50);
    polygon.setPoint(1, 40, 90);
    polygon.setPoint(2, 60, 50);


    drawPolygon(polygon);

    //Set translation vector coordinates
    Point translationVector(100, 100, 1);

    translatePolygon(polygon, translationVector);

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

void translatePolygon(PolygonShape polygon, Point translationVector){
    //To translate a given polygon using the translation vector

    glColor3d(0, 0, 1); //Blue color

    glBegin(GL_POLYGON);

    for(int i = 0; i < polygon.getVertexCount(); i++){
        Point p = polygon.getPoint(i);
        Point pDash = p.getTranslatedPoint(translationVector);
        glVertex2d(pDash.getX(), pDash.getY()); //Plot the normal coordinates
    }

    glEnd();
}


