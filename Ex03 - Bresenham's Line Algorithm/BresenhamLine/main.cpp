//To implement the Bresenham Line Drawing Algorithm

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
