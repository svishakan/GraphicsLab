/* To draw a circle using the midpoint circle drawing algorithm with OpenGL */

#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>

GLint x, y, radius; //Variables for circle

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

class screenPoint{
    /* Class for a coordinate point */

private:
    GLint x, y;

public:
    screenPoint(){
        //Default constructor, initialize to (0, 0)
        x = y = 0;
    }

    screenPoint(GLint xCoord, GLint yCoord){
        //Constructor with preset points
        x = xCoord;
        y = yCoord;
    }

    void setCoords(GLint xCoord, GLint yCoord){
        //Function to set coordinates
        x = xCoord;
        y = yCoord;
    }

    GLint getX() const{
        //Return x coordinate
        return x;
    }

    GLint getY() const{
        //Return y coordinate
        return y;
    }

    void incX(){
        //Increment x coordinate
        x++;
    }

    void decY(){
        //Decrement y coordinate
        y--;
    }

    void printCoords(){
        //Print current coordinates
        printf("\nX: %d\tY: %d", x, y);
    }
};

void initializeDisplay();
void drawCircle();
void setPixel(GLint xCoord, GLint yCoord);
void circleMidPoint(GLint xc, GLint yc, GLint radius);
void circlePlotPoints(GLint xc, GLint yc, screenPoint circlePoint);


int main(int argc, char **argv){

    printf("\n\t\tEnter the center coordinates of the circle\n");

    printf("\nEnter the X coordinate: ");
    scanf("%d", &x);

    printf("\nEnter the Y coordinate: ");
    scanf("%d", &y);

    printf("\nEnter the radius of the circle: ");
    scanf("%d", &radius);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Mid-Point Circle Drawing Algorithm");

    initializeDisplay();
    glutDisplayFunc(drawCircle);
    glutMainLoop();

    return 1;
}

void initializeDisplay(){
    //Initialize the display parameters

    glClearColor(0, 1, 1, 0);       //Display window color
    glMatrixMode(GL_PROJECTION);    //Choose projection
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);     //Set transformation
}

void setPixel(GLint xCoord, GLint yCoord){
    //Draw a pixel at the given point

    glBegin(GL_POINTS);
    glVertex2i(xCoord, yCoord);
    glEnd();
}

void circleMidPoint(GLint xc, GLint yc, GLint radius){
    //Implementation of the midpoint circle drawing algorithm

    screenPoint circlePoint;

    GLint p = 1 - radius;   //Initial value for midpoint parameter

    circlePoint.setCoords(0, radius);   //Set coordinates at top of circle

    circlePlotPoints(xc, yc, circlePoint);  //Plot initial point
    //circlePoint.printCoords();

    //Calculate the next points while X < Y
    while(circlePoint.getX() < circlePoint.getY()){
        circlePoint.incX();

        if(p < 0){
            p += 2 * circlePoint.getX() + 1;
        }

        else{
            circlePoint.decY();
            p += 2 * (circlePoint.getX() - circlePoint.getY()) + 1;
        }

        //circlePoint.printCoords();
        circlePlotPoints(xc, yc, circlePoint);
    }

    glFlush();  //Flush the completed circle output to display
}

void circlePlotPoints(GLint xc, GLint yc, screenPoint circlePoint){
    //Plot points for all 8 octants of the circle

    setPixel(xc + circlePoint.getX(), yc + circlePoint.getY());
    setPixel(xc - circlePoint.getX(), yc + circlePoint.getY());
    setPixel(xc + circlePoint.getX(), yc - circlePoint.getY());
    setPixel(xc - circlePoint.getX(), yc - circlePoint.getY());
    setPixel(xc + circlePoint.getY(), yc + circlePoint.getX());
    setPixel(xc - circlePoint.getY(), yc + circlePoint.getX());
    setPixel(xc + circlePoint.getY(), yc - circlePoint.getX());
    setPixel(xc - circlePoint.getY(), yc - circlePoint.getX());
}

void drawCircle(){
    //Driver function to call the circle drawing function

    circleMidPoint(x, y, radius);
}

