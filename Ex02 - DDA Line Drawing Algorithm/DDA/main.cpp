//To implement the DDA Line Drawing Algorithm
// DDA: Digital Differential Algorithm

#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>

GLfloat x1, y1, x2, y2;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initializeDisplay();
void drawLine();
GLint round(GLfloat num);

int main(int argc, char **argv){


    printf("\nEnter the value of X1: ");
    scanf("%f", &x1);

    printf("\nEnter the value of Y1: ");
    scanf("%f", &y1);

    printf("\nEnter the value of X2: ");
    scanf("%f", &x2);

    printf("\nEnter the value of Y2: ");
    scanf("%f", &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("DDA Line Drawing Algorithm");

    initializeDisplay();
    glutDisplayFunc(drawLine);
    glutMainLoop();

    return 1;
}

void initializeDisplay(){
    //Initialize the display parameters

    glClearColor(0, 1, 1, 0);       //Display window color
    glMatrixMode(GL_PROJECTION);    //Choose projection
    gluOrtho2D(0, 800, 0, 600);     //Set transformation
}

void drawLine(){
    GLfloat dx, dy, k, x_inc, y_inc, x, y, slope_max;

    dx = x2 - x1;
    dy = y2 - y1;

    if(abs(dx) > abs(dy)){
        // |slope| < 0
        slope_max = abs(dx);
    } else {
        // |slope| >= 0
        slope_max = abs(dy);
    }

    // if dx/dy >= slope_max, then x_inc/y_inc will be >= 1
    // respectively, and the other will be < 1.
    // increments will be calculated on this basis
    // according to the DDA Algorithm
    x_inc = dx/slope_max;
    y_inc = dy/slope_max;

    //Initial point
    x = x1;
    y = y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    //Plot for all points from 1 to slope_max
    for(k = 1; k <= slope_max; k++){
        x += x_inc;
        y += y_inc;

        glVertex2i(x, y);
    }

    glEnd();
    glFlush();
}
