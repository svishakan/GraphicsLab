/* To draw an object with circles and lines - Stick man */

#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>

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

void drawStickman();
void initializeDisplay();
void setPixel(GLint xCoord, GLint yCoord);
void drawCircle(GLint xc, GLint yc, GLint radius);
void drawLine(GLint x1, GLint y1, GLint x2, GLint y2);
void circlePlotPoints(GLint xc, GLint yc, screenPoint circlePoint);


int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Stickman using Circles & Lines");

    initializeDisplay();
    glutDisplayFunc(drawStickman);
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

void drawCircle(GLint xc, GLint yc, GLint radius){
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

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2){
    //Bresenham's Line Drawing Algorithm Implementation

    GLint dx, dy, x, y, p, inc_x1, inc_y1, inc_p1, inc_p2;
    GLint x_sign, y_sign;

    dx = x2 - x1;
    dy = y2 - y1;

    //note the sign for directionality
    x_sign = dx/abs(dx);
    y_sign = dy/abs(dy);

    //increment is by 1, and in the direction of +/-
    inc_x1 = 1 * x_sign;
    inc_y1 = 1 * y_sign;

    //change the differences to absolute values (crucial step)
    dx = abs(dx);
    dy = abs(dy);

    //initial coordinates
    x = x1;
    y = y1;

    glBegin(GL_POINTS);

    if(abs(dx) > abs(dy)){
        //X difference > Y difference
        glVertex2i(x, y);

        p = (2 * dy) - dx;
        inc_p1 = 2 * (dy - dx);
        inc_p2 = 2 * dy;

        //plot for dx number of points
        for(GLint i = 0; i < dx; i++){
            if(p >= 0){
                y += inc_y1;
                p += inc_p1;
            }
            else{
                p += inc_p2;
            }

            x += inc_x1;

            glVertex2i(x, y);
        }
    }
    else{
        //X difference <= Y difference
        glVertex2i(x, y);

        p = (2 * dx) - dy;
        inc_p1 = 2 * (dx - dy);
        inc_p2 = 2 * dx;

        //plot for dy number of points
        for(GLint i = 0; i < dy; i++){
            if(p >= 0){
                x += inc_x1;
                p += inc_p1;
            }
            else{
                p += inc_p2;
            }

            y += inc_y1;

            glVertex2i(x, y);
        }
    }

    glEnd();
    glFlush();
}


void drawStickman(){
    //Draw a stick man using the drawLine() and drawCircle() algorithms

    //Face
    drawCircle(400, 650, 100);

    //Eyes
    drawCircle(350, 680, 20);
    drawCircle(450, 680, 20);

    //Nose
    drawLine(400, 650, 400, 630);
    drawLine(400, 630, 420, 630);

    //Mouth
    drawLine(370, 580, 430, 580);

    //Body
    drawLine(400, 550, 400, 250);

    //Arms
    drawLine(400, 500, 300, 340);
    drawLine(400, 500, 500, 340);

    //Legs
    drawLine(400, 250, 300, 150);
    drawLine(400, 250, 500, 150);
}
