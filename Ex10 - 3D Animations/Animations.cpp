 /*
Write a C++ program using Opengl to draw atleast four 3D objects. Apply lighting and texture and
render the scene. Apply transformations to create a simple 3D animation.
*/

#include <iostream>
#include <cstring>
#include <GL/glut.h>
#include <math.h>

const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 800;
const int FPS = 60;

//Global variables for handling animation
float translate_x = 0;
int frame = 0;
int direction = 1;

using namespace std;

void initializeDisplay();
void renderAnimation(int val);
void setLights();
void setMaterialParams(float aR, float aG, float aB, float dR, float dG, float dB, float sR, float sG, float sB, float shiny);

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("3D Animation");
    
    glutDisplayFunc(initializeDisplay);
    glutTimerFunc(1000/FPS, renderAnimation, 0);

    glEnable(GL_DEPTH_TEST);

    setLights();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, 1, 4, 20);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

    glutMainLoop();
}

void initializeDisplay(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glColor4f(0, 0, 0, 0.3);
    
    //Draw a car
    
    glPushMatrix();
    glTranslatef(translate_x, 0, 0);

    //Body
    glPushMatrix();
    glScalef(5, 2, 2);
    setMaterialParams(0.75, 0.2, 0.75, 1, 1, 1, 1, 1, 1, 100);
    glutSolidCube(0.5);
    glPopMatrix();

    //Wheels
    setMaterialParams(0, 0, 0, 0, 0, 0, 1, 1, 1, 1);

    //Back Left
    glPushMatrix();
    glTranslatef(-1.25, -1, 0.25);
    glutSolidTorus(0.1, 0.25, 30, 30);
    glPopMatrix();

    //Front Left
    glPushMatrix();
    glTranslatef(0.75, -1, 0.25);
    glutSolidTorus(0.1, 0.25, 30, 30);
    glPopMatrix();

    //Back Right
    glPushMatrix();
    glTranslatef(-1.25, -1, -0.7);
    glutSolidTorus(0.1, 0.25, 30, 30);
    glPopMatrix();

    //Front Right
    glPushMatrix();
    glTranslatef(0.75, -1, -0.7);
    glutSolidTorus(0.1, 0.25, 30, 30);
    glPopMatrix();

    //Headlights
    setMaterialParams(1, 1, 0.2, 1, 1, 1, 1, 1, 0.2, 300);

    //Left
    glPushMatrix();
    glTranslatef(1.25, -0.25, 0.25);
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix();

    //Right
    glPushMatrix();
    glTranslatef(1.25, -0.25, -0.25);
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix();

    //Roof Hat
    glPushMatrix();

    glRotatef(270, 1, 0, 0);
    glTranslatef(0.75, 0, 0.5); //Order important. Rotate->Translate
    //Last command acted on first in OpenGL, thus rotate about fixed point here

    setMaterialParams(0, 0.25, 1, 0, 0.5, 1, 1, 1, 1, 1);
    //setMaterialParams(0, 0.5, 1, 0, 0.5, 1, 1, 1, 1, 50);
    glutSolidCone(0.5, 0.75, 30, 30);
    
    glPopMatrix();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();  //Swap the offscreen buffer to screen
}

void renderAnimation(int val){
    //Render an animation frame by frame

    frame = (frame % FPS) + 1;

    if(frame % 5 == 0){
        translate_x += (0.04 * direction);
        glutPostRedisplay();
    }

    if(translate_x >= 1.40 || translate_x <= -3.40){
        direction *= -1;
    }

    //Call the timer function again to keep animating
    glutTimerFunc(1000/FPS, renderAnimation, 0);

}

void setMaterialParams(float aR, float aG, float aB, float dR, float dG, float dB, float sR, float sG, float sB, float shiny){
    //Set material's ambient, diffuse and specular component colors, along with
    //the shininess of the material

    float ambient[3] = {aR, aG, aB};
    float diffuse[3] = {dR, dG, dB};
    float specular[3] = {sR, sG, sB};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
}

void setLights(){
    glShadeModel(GL_SMOOTH);    //Enable smooth shading of objects

    //Set modelview matrix for the lighting
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float lightPosition[] = {0.0, 10.0, 5.0};
    float lightColor[] = {0.5, 0.5, 0.5};
    float ambientColor[] = {0.3, 0.3, 0.3};
    float spotDirection[] = {-1.0, -1.0, -1.0};

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 37.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1);
}