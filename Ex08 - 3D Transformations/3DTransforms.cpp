/*
3D Transformations - Translation, Rotation, Scaling, Reflection and Shearing
*/

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>     //for cin, cout
#include <cstring>      //for memcpy

using namespace std;

enum Axes {xAxis = 0, yAxis = 1, zAxis = 2};
enum Planes {xyPlane = 0, yzPlane = 1, zxPlane = 2};

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;
const int FPS = 60;

class Face{     //wrapper class for a face of a 3D object
    private:
        GLfloat r = 1, g = 1, b = 1, a = 1; //black
        GLfloat vertices[4][4];     // V * (x, y, z, h)
        int vertexCount = 4;        // V
    
    public:
        Face(){
            r = g = b = a = 1;  //black
            vertexCount = 4;
        }

        Face(GLfloat R, GLfloat G, GLfloat B, GLfloat A){
            //Set colors
            Face();
            r = R;
            g = G;
            b = B;
            a = A;
        }
        
        void setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A){
            //Set colors
            r = R;
            g = G;
            b = B;
            a = A;
        }

        void setIthVertex(int i, GLfloat x, GLfloat y, GLfloat z, GLfloat h = 1){
            //Set the ith vertex coordinates
            vertices[i][0] = x;
            vertices[i][1] = y;
            vertices[i][2] = z;
            vertices[i][3] = h;
        }

        void drawFace(){
            glColor4f(r, g, b, a);

            glBegin(GL_POLYGON);
            
            for(int i = 0; i < vertexCount; i++){
                glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
            }

            glEnd();            
        }

        Face transform(double transformationMatrix[4][4]){
            Face fDash(r, g, b, a - 0.5);
            double values[4];

            // [V x 4] x [4 x 1] = [V x 1] matrix
            for(int i = 0; i < vertexCount; i++){
                for(int j = 0; j < 4; j++){
                    values[j] = transformationMatrix[j][0] * vertices[i][0] +
                                transformationMatrix[j][1] * vertices[i][1] +
                                transformationMatrix[j][2] * vertices[i][2] +
                                transformationMatrix[j][3] * vertices[i][3];
                }

                fDash.setIthVertex(i, values[0], values[1], values[2], values[3]);
                //cout << "\nVertex" << values[0] << " " << values[1] << " " << values[2] << " " << values[3];
            
            }

            return fDash;
        }
};

class Object3D{     //wrapper class for a 3D object with multiple faces
    private:
        Face *faces;
        int numFaces;
    
    public:
        Object3D(){
            numFaces = 0;
        }

        Object3D(int noFaces){
            numFaces = noFaces;
            faces = new Face[numFaces];
        }

        void setIthFace(int i, Face face){
            faces[i] = face;
        }

        void drawObject3D(){
            for(int i = 0; i < numFaces; i++){
                faces[i].drawFace();
            }
        }

        Object3D translateObject3D(GLfloat tx, GLfloat ty, GLfloat tz){
            //To translate the 3D object wrt. a translation vector

            double translationMatrix[4][4] = {  {1, 0, 0, tx},
                                                {0, 1, 0, ty},
                                                {0, 0, 1, tz},
                                                {0, 0, 0, 1}};
            
            Object3D transformedObject(numFaces);

            for(int i = 0; i < numFaces; i++){
                Face fDash = faces[i].transform(translationMatrix);
                transformedObject.setIthFace(i, fDash);
            }

            return transformedObject;
        }

        Object3D scaleObject3D(GLfloat sx, GLfloat sy, GLfloat sz){
            //To scale the 3D object wrt. the given scaling factors

            double scalingMatrix[4][4] = {  {sx, 0, 0, 0},
                                            {0, sy, 0, 0},
                                            {0, 0, sz, 0},
                                            {0, 0, 0, 1}};
            
            Object3D transformedObject(numFaces);

            for(int i = 0; i < numFaces; i++){
                Face fDash = faces[i].transform(scalingMatrix);
                transformedObject.setIthFace(i, fDash);
            }

            return transformedObject;
        }

        Object3D rotateObject3D(int axis, double rotationAngle){
            //To rotate the 3D object about an axis and an angle

            double rotationAngleInRadians = rotationAngle * 3.14159 / 180;
            double cosAngle = cos(rotationAngleInRadians);
            double sinAngle = sin(rotationAngleInRadians);
            double rotationMatrix[4][4];

            switch(axis){
                case xAxis:{
                    double temp[4][4] = {   {1, 0, 0, 0},
                                            {0, cosAngle, -sinAngle, 0},
                                            {0, sinAngle, cosAngle, 0},
                                            {0, 0, 0, 1}};

                    memcpy(rotationMatrix, temp, sizeof(temp));
                    break;
                }

                case yAxis:{
                    double temp[4][4] = {   {cosAngle, 0, sinAngle, 0},
                                            {0, 1, 0, 0},
                                            {-sinAngle, 0, cosAngle, 0},
                                            {0, 0, 0, 1}};

                    memcpy(rotationMatrix, temp, sizeof(temp));
                    break;
                }

                case zAxis:{
                    double temp[4][4] = {   {cosAngle, -sinAngle, 0, 0},
                                            {sinAngle, cosAngle, 0, 0},
                                            {0, 0, 1, 0},
                                            {0, 0, 0, 1}};

                    memcpy(rotationMatrix, temp, sizeof(temp));
                    break;
                }                
            }

            Object3D transformedObject(numFaces);

            for(int i = 0; i < numFaces; i++){
                Face fDash = faces[i].transform(rotationMatrix);
                transformedObject.setIthFace(i, fDash);
            }

            return transformedObject;            
        }

        Object3D shearObject3D(int axis, double shx = 0, double shy = 0, double shz = 0){
            //To shear the 3D object wrt. an axis and the given shear parameters

            double shearingMatrix[4][4];
            
            switch(axis){
                case xAxis:{
                    double temp[4][4] = {   {1, 0, 0, 0},
                                            {shy, 1, 0, 0},
                                            {shz, 0, 1, 0},
                                            {0, 0, 0, 1}};

                    memcpy(shearingMatrix, temp, sizeof(temp));
                    break;
                }

                case yAxis:{
                    double temp[4][4] = {   {1, shx, 0, 0},
                                            {0, 1, 0, 0},
                                            {0, shz, 1, 0},
                                            {0, 0, 0, 1}};

                    memcpy(shearingMatrix, temp, sizeof(temp));
                    break;
                }

                case zAxis:{
                    double temp[4][4] = {   {1, 0, shx, 0},
                                            {0, 1, shy, 0},
                                            {0, 0, 1, 0},
                                            {0, 0, 0, 1}};

                    memcpy(shearingMatrix, temp, sizeof(temp));
                    break;
                }                
            }

            Object3D transformedObject(numFaces);

            for(int i = 0; i < numFaces; i++){
                Face fDash = faces[i].transform(shearingMatrix);
                transformedObject.setIthFace(i, fDash);
            }

            return transformedObject;
        }

        Object3D reflectObject3D(int plane){
            //To reflect the 3D Object about a given plane

            double reflectionMatrix[4][4];

            switch(plane){
                case xyPlane:{
                    double temp[4][4] = {   {1, 0, 0, 0},
                                            {0, 1, 0, 0},
                                            {0, 0, -1, 0},
                                            {0, 0, 0, 1}};

                    memcpy(reflectionMatrix, temp, sizeof(temp));
                    break;
                }

                case yzPlane:{
                    double temp[4][4] = {   {-1, 0, 0, 0},
                                            {0, 1, 0, 0},
                                            {0, 0, 1, 0},
                                            {0, 0, 0, 1}};

                    memcpy(reflectionMatrix, temp, sizeof(temp));
                    break;
                }

                case zxPlane:{
                    double temp[4][4] = {   {1, 0, 0, 0},
                                            {0, -1, 0, 0},
                                            {0, 0, 1, 0},
                                            {0, 0, 0, 1}};

                    memcpy(reflectionMatrix, temp, sizeof(temp));
                    break;
                }                
            }

            Object3D transformedObject(numFaces);

            for(int i = 0; i < numFaces; i++){
                Face fDash = faces[i].transform(reflectionMatrix);
                transformedObject.setIthFace(i, fDash);
            }

            return transformedObject;
        }
};

void dummyFunction();
void mainLoop(int val);
void initializeDisplay();
void initializeBaseCube();
void plotBase3DObject();
void plotTransformation();

Object3D cube;

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("3D Transformations - Examples");

    initializeBaseCube();
    initializeDisplay();

    glutDisplayFunc(dummyFunction);
    glutTimerFunc(1000/FPS, mainLoop, 0);
    glutMainLoop();

    return 1;
}

void mainLoop(int val){
    //Render the display using the timer function
    plotTransformation();
}

void dummyFunction(){
    //Placeholder function
}

void initializeDisplay(){
    glClearColor(1, 1, 1, 1);
    glOrtho(-800, 800, -800, 800, -800, 800);   //Orthographic projection
    glEnable(GL_DEPTH_TEST);    //Enable depth

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //Rotate the entire display so that different sides of the 3D object can be seen
    glRotatef(50, 1, 0, 0);
    glRotatef(50, 0, 1, 0);
    glRotatef(50, 0, 0, 1);

    glEnable(GL_BLEND);     //enable blending (translucent colors)
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //set the blend function for translucency
}

void initializeBaseCube(){
    //Set the coordinates for the base cube

    cube = Object3D(6);

    Face front, back, left, right, bottom, top;

    front = Face(1, 0, 0, 0.75);   //Red
    front.setIthVertex(0, -100, 100, 100);
    front.setIthVertex(1, 100, 100, 100);
    front.setIthVertex(2, 100, -100, 100);
    front.setIthVertex(3, -100, -100, 100);

    back = Face(0, 1, 0, 0.75);    //Green
    back.setIthVertex(0, -100, 100, -100);
    back.setIthVertex(1, 100, 100, -100);
    back.setIthVertex(2, 100, -100, -100);
    back.setIthVertex(3, -100, -100, -100);

    left = Face(0, 0, 1, 0.75);    //Blue
    left.setIthVertex(0, -100, 100, -100);
    left.setIthVertex(1, -100, 100, 100);
    left.setIthVertex(2, -100, -100, 100);
    left.setIthVertex(3, -100, -100, -100);
    
    right = Face(1, 1, 0, 0.75);   //Yellow   
    right.setIthVertex(0, 100, 100, -100);
    right.setIthVertex(1, 100, 100, 100);
    right.setIthVertex(2, 100, -100, 100);
    right.setIthVertex(3, 100, -100, -100);

    bottom = Face(0, 1, 1, 0.75);  //Cyan
    bottom.setIthVertex(0, -100, -100, -100);
    bottom.setIthVertex(1, 100, -100, -100);
    bottom.setIthVertex(2, 100, -100, 100);
    bottom.setIthVertex(3, -100, -100, 100);
    
    top = Face(1, 0, 1, 0.75);     //Magenta
    top.setIthVertex(0, -100, 100, -100);
    top.setIthVertex(1, 100, 100, -100);
    top.setIthVertex(2, 100, 100, 100);
    top.setIthVertex(3, -100, 100, 100);

    cube.setIthFace(0, front);
    cube.setIthFace(1, back);
    cube.setIthFace(2, left);
    cube.setIthFace(3, right);
    cube.setIthFace(4, bottom);
    cube.setIthFace(5, top);
}

void plotBase3DObject(){
    //Plot the base 3D object without any transformations

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //Clear window
    cube.drawObject3D();
    glFlush();
}

void plotTransformation(){
    //Plot the transformation

    plotBase3DObject();
    glFlush();

    int transform = 0;
    Object3D cubeDash;

    while(true){
        //Await user input

        cout << "\nChoose Transformation: " << endl;
        cout << "\t1 for Translation" << endl;
        cout << "\t2 for Rotation" << endl;
        cout << "\t3 for Scaling" << endl;
        cout << "\t4 for Reflection" << endl;
        cout << "\t5 for Shearing" << endl;
        cout << "\t0 to Exit" << endl;
        cout << "\tYour Option -> ";
        cin >> transform;
        
        switch(transform){
            case 0:{
                exit(0);
            }

            case 1:{
                float tx, ty, tz;
                cout << endl << "-----TRANSLATION-----" << endl;
                cout << "\nEnter Translation Vector Coordinates: " << endl;
                cout << "\nEnter X: "; cin >> tx;
                cout << "\nEnter Y: "; cin >> ty;
                cout << "\nEnter Z: "; cin >> tz;
                
                cubeDash = cube.translateObject3D(tx, ty, tz);
                cout << endl << "------TRANSLATION DONE-----" << endl;

                break;
            }

            case 2:{
                double angle; int axis;
                cout << endl << "-----ROTATION-----" << endl;
                cout << "\nEnter Rotation Axis: " << endl;
                cout << "\t0 for X-Axis" << endl;
                cout << "\t1 for Y-Axis" << endl;
                cout << "\t2 for Z-Axis" << endl;
                cout << "\tYour Option -> ";
                cin >> axis;

                cout << "\nEnter Rotation Angle: "; cin >> angle;
                
                cubeDash = cube.rotateObject3D(axis, angle);
                cout << endl << "-----ROTATION DONE-----" << endl;
                break;
            }

            case 3:{
                float sx, sy, sz;

                cout << endl << "-----SCALING-----" << endl;
                cout << "\nEnter Scale Factors: " << endl;
                cout << "\nEnter X Factor: "; cin >> sx;
                cout << "\nEnter Y Factor: "; cin >> sy;
                cout << "\nEnter Z Factor: "; cin >> sz;
                
                cubeDash = cube.scaleObject3D(sx, sy, sz);
                cout << endl << "------SCALING DONE-----" << endl;

                break;
            }

            case 4:{
                int plane;
                cout << endl << "-----REFLECTION-----" << endl;
                cout << "\nEnter Reflection Plane: " << endl;
                cout << "\t0 for XY-Plane" << endl;
                cout << "\t1 for YZ-Plane" << endl;
                cout << "\t2 for ZX-Plane" << endl;
                cout << "\tYour Option -> ";
                cin >> plane;
                
                cubeDash = cube.reflectObject3D(plane);
                cout << endl << "-----REFLECTION DONE-----" << endl;
                break;
            }

            case 5:{
                double shx = 0, shy = 0, shz = 0; int axis;
                
                cout << endl << "-----SHEARING-----" << endl;
                cout << "\nEnter Shear Axis: " << endl;
                cout << "\t0 for X-Axis" << endl;
                cout << "\t1 for Y-Axis" << endl;
                cout << "\t2 for Z-Axis" << endl;
                cout << "\tYour Option -> ";
                cin >> axis;

                cout << "\nEnter Shear Factors: " << endl;

                switch(axis){
                    case xAxis:{
                        cout << "\n Enter Y Factor: "; cin >> shy;
                        cout << "\n Enter Z Factor: "; cin >> shz;
                        break;
                    }

                    case yAxis:{
                        cout << "\n Enter X Factor: "; cin >> shx;
                        cout << "\n Enter Z Factor: "; cin >> shz;
                        break;
                    }

                    case zAxis:{
                        cout << "\n Enter X Factor: "; cin >> shx;
                        cout << "\n Enter Y Factor: "; cin >> shy;
                        break;
                    }
                }
                
                cubeDash = cube.shearObject3D(axis, shx, shy, shz);
                cout << endl << "-----SHEARING DONE-----" << endl;
                break;
            }
        }

        plotBase3DObject();
        cubeDash.drawObject3D();
        glFlush();
    }
}



