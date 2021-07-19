//To draw a house using OpenGL

#include <windows.h>
#include <GL/glut.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initializeDisplay();
void drawHouse();


int main(int argc, char **argv){
    glutInit(&argc, argv);                      //Initialize glut
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);  //Set display mode
    glutInitWindowPosition(100, 100);           //Set Window position
    glutInitWindowSize(800, 600);               //Set window size
    glutCreateWindow("OpenGL - House");         //Create display window with title

    initializeDisplay();                        //Initialization procedure
    glutDisplayFunc(drawHouse);                 //Send graphics to display window
    glutMainLoop();                             //Display everything and wait

    return 1;
}

void initializeDisplay(){
    glClearColor(0.5, 0.1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 600);
}

void drawHouse(){
    glClear(GL_COLOR_BUFFER_BIT);       //Clear display window

    //Ground
    glColor3f(0.5, 0.3, 0);
    glBegin(GL_POLYGON);

    glVertex2i(0, 100);
    glVertex2i(800, 100);
    glVertex2i(800, 0);
    glVertex2i(0, 0);

    glEnd();

    //Side Roof
    glColor3f(0.3, 0.5, 0.8);
    glBegin(GL_POLYGON);

    glVertex2i(200, 500);
    glVertex2i(600, 500);
    glVertex2i(700, 350);
    glVertex2i(300, 350);

    glEnd();

    //Front Roof
    glColor3f(0.1, 0.5, 0.0);
    glBegin(GL_TRIANGLES);

    glVertex2i(200, 500);
    glVertex2i(100, 350);
    glVertex2i(300, 350);

    glEnd();

    //Front Wall
    glColor3f(0.7, 0.2, 0.3);
    glBegin(GL_POLYGON);

    glVertex2i(100, 350);
    glVertex2i(300, 350);
    glVertex2i(300, 100);
    glVertex2i(100, 100);

    glEnd();

    //Side Wall
    glColor3f(0.1, 0.2, 0.3);
    glBegin(GL_POLYGON);

    glVertex2i(300, 350);
    glVertex2i(700, 350);
    glVertex2i(700, 100);
    glVertex2i(300, 100);

    glEnd();

    //Front Door
    glColor3f(0.7, 0.2, 0.9);
    glBegin(GL_POLYGON);

    glVertex2i(150, 250);
    glVertex2i(250, 250);
    glVertex2i(250, 100);
    glVertex2i(150, 100);

    glEnd();

    //Front Door Lock
    glColor3f(0.3, 0.7, 0.9);
    glPointSize(15);
    glBegin(GL_POINTS);

    glVertex2i(170, 170);

    glEnd();

    //Front Door Frame
    glColor3f(1, 1, 1);
    glLineWidth(2.5);
    glBegin(GL_LINES);

    glVertex2i(150, 250);
    glVertex2i(250, 250);

    glVertex2i(150, 100);
    glVertex2i(150, 250);

    glVertex2i(250, 100);
    glVertex2i(250, 250);


    glVertex2i(150, 100);
    glVertex2i(250, 100);


    glEnd();


    //Pathway
    glColor3f(0.3, 0.5, 0.7);
    glLineWidth(5);
    glBegin(GL_POLYGON);

    glVertex2i(150, 100);
    glVertex2i(250, 100);
    glVertex2i(210, 0);
    glVertex2i(40, 0);

    glEnd();

    //Windows

    //Window - 1
    glColor3f(0.2, 0.4, 0.3);
    glBegin(GL_POLYGON);

    glVertex2i(330, 320);
    glVertex2i(450, 320);
    glVertex2i(450, 230);
    glVertex2i(330, 230);

    glEnd();

    //Window - 2
    glColor3f(0.2, 0.4, 0.3);
    glBegin(GL_POLYGON);

    glVertex2i(530, 320);
    glVertex2i(650, 320);
    glVertex2i(650, 230);
    glVertex2i(530, 230);

    glEnd();

    //Window Borders

    //Window - 1
    glColor3f(0.1, 0.7, 0.5);
    glLineWidth(5);
    glBegin(GL_LINES);

    glVertex2i(390, 320);
    glVertex2i(390, 230);
    glVertex2i(330, 273);
    glVertex2i(450, 273);

    glEnd();

    //Window -2
    glColor3f(0.1, 0.7, 0.5);
    glLineWidth(5);
    glBegin(GL_LINES);

    glVertex2i(590, 320);
    glVertex2i(590, 230);
    glVertex2i(530, 273);
    glVertex2i(650, 273);

    glEnd();

    //Decoration
    glColor3f(0.2, 0.4, 0.2);
    glPointSize(5);
    glBegin(GL_POINTS);

    GLint x = 310;
    for(x; x <= 690; x += 10){
        glVertex2i(x, 120);
    }

    glEnd();

    //Hexagonal Sun
    glColor3f(0.8, 1, 0);
    glBegin(GL_POLYGON);

    glVertex2i(50, 500);
    glVertex2i(75, 550);
    glVertex2i(125, 550);
    glVertex2i(150, 500);
    glVertex2i(125, 450);
    glVertex2i(75, 450);

    glEnd();


    glFlush();      //Flush the output to the display
}

