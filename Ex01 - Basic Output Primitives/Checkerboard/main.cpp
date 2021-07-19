//To draw a checkerboard using OpenGL

#include <windows.h>
#include <GL/glut.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initializeDisplay();
void displayCheckerboard();
void drawSquare(GLint x, GLint y, GLint x_step, GLint y_step);

int CURRENT_COLOR = 0;      //Global variable to keep track of current checker color

int main(int argc, char **argv){
    glutInit(&argc, argv);                      //Initialize glut
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);  //Set display mode
    glutInitWindowPosition(100, 100);           //Set Window position
    glutInitWindowSize(800, 600);               //Set window size
    glutCreateWindow("OpenGL Checkerboard");    //Create display window with title

    initializeDisplay();                        //Initialization procedure
    glutDisplayFunc(displayCheckerboard);       //Send graphics to display window
    glutMainLoop();                             //Display everything and wait

    return 1;
}

void initializeDisplay(){
    //Initialize the display parameters

    glClearColor(0, 1, 1, 0);       //Display window color
    glMatrixMode(GL_PROJECTION);    //Choose projection
    gluOrtho2D(0, 800, 0, 600);     //Set transformation
}

void displayCheckerboard(){
    //Displays an 8x8 checkerboard

    glClear(GL_COLOR_BUFFER_BIT);   //Clear display window
    GLint x, y;
    GLint x_step = 100, y_step = 75;
    //For 8x8 board in an 800x600 window, x_step = 800/8 = 100, y_step = 600/8 = 75

    for(x = 0; x <= 800; x += x_step){
        for(y = 0; y <= 600; y += y_step){
            drawSquare(x, y, x_step, y_step);
        }
    }

    glFlush();  //Forces execution of OpenGL functions in finite time.
}

void drawSquare(GLint x, GLint y, GLint x_step, GLint y_step){
    //Draws a square, given a pair of coordinates and step sizes

    GLint x1, y1, x2, y2, x3, y3, x4, y4;

    //Vertex 1
    x1 = x;
    y1= y + y_step;

    //Vertex 2
    x2 = x + x_step;
    y2 = y + y_step;

    //Vertex 3
    x3 = x + x_step;
    y3 = y;

    //Vertex 4
    x4 = x;
    y4 = y;

    if(CURRENT_COLOR == 0){
        glColor3f(1, 1, 1);     //White color
        CURRENT_COLOR = 1;
    }
    else{
        glColor3f(0, 0, 0);     //Black color
        CURRENT_COLOR = 0;
    }

    glBegin(GL_POLYGON);

    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glVertex2i(x3, y3);
    glVertex2i(x4, y4);

    glEnd();
}
