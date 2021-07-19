//Basic output primitives using OpenGL
//Shapes: Points, Lines, Line Strips, Line Loops, Triangles, Quads, Quad Strips and Polygons

//Documentation: https://docs.microsoft.com/en-us/windows/win32/opengl/gl-functions

#include <windows.h>
#include <GL/glut.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initializeDisplay();
void displayShapes();

void displayPoints();
void displayLines();
void displayLineStrips();
void displayLineLoops();
void displayTriangles();
void displayQuads();
void displayQuadStrips();
void displayPolygons();

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Basic Shapes");
    glutDisplayFunc(displayShapes);
    initializeDisplay();
    glutMainLoop();

    return 1;
}

void initializeDisplay(){
    glClearColor(1.0, 1.0, 1.0, 0.0);   //The glClearColor function specifies clear values for the color buffers.
    glColor3f(255.0f, 0.0f, 127.0f);    //Sets the current color.
    glPointSize(5);                    //The glPointSize function specifies the diameter of rasterized points.
    glMatrixMode(GL_PROJECTION);        //The glMatrixMode function specifies which matrix is the current matrix.
    glLoadIdentity();                   //The glLoadIdentity function replaces the current matrix with the identity matrix.
    gluOrtho2D(0.0, 800.0, 0.0, 600.0); //The gluOrtho2D function defines a 2-D orthographic projection matrix.
}

void displayShapes(){
    glClear(GL_COLOR_BUFFER_BIT);

    displayPoints();
    displayLines();
    displayLineStrips();
    displayLineLoops();
    displayTriangles();
    displayQuads();
    displayQuadStrips();
    displayPolygons();

    glFlush();
}

void displayPoints(){
    //Treats each vertex as a single point.
    //Vertex n defines point n. N points are drawn.

    glBegin(GL_POINTS);

    glVertex2d(10, 10);
    glVertex2d(15, 15);
    glVertex2d(20, 20);
    glVertex2d(25, 25);
    glVertex2d(30, 30);

    glEnd();
}

void displayLines(){
    //Treats each pair of vertices as an independent line segment.
    //Vertices 2n - 1 and 2n define line n. N/2 lines are drawn.

    glBegin(GL_LINES);

    glVertex2d(0, 0);
    glVertex2d(800, 600);

    glEnd();
}

void displayLineStrips(){
    //Draws a connected group of line segments from the first vertex to the last.
    // Vertices n and n+1 define line n. N - 1 lines are drawn.

    glBegin(GL_LINE_STRIP);

    glVertex2d(100, 100);
    glVertex2d(200, 200);

    glVertex2d(200, 500);
    glVertex2d(500, 600);

    glEnd();
}

void displayLineLoops(){
    //Draws a connected group of line segments from the first vertex to the last,
    //then back to the first. Vertices n and n + 1 define line n.
    //The last line, however, is defined by vertices N and 1. N lines are drawn.

    glBegin(GL_LINE_LOOP);

    glVertex2d(650, 250);
    glVertex2d(750, 250);
    glVertex2d(750, 350);
    glVertex2d(650, 350);

    glEnd();
}

void displayTriangles(){
    //Treats each triplet of vertices as an independent triangle.
    //Vertices 3n - 2, 3n - 1, and 3n define triangle n. N/3 triangles are drawn.

    glBegin(GL_TRIANGLES);

    glVertex2d(170, 170);
    glVertex2d(170, 220);
    glVertex2d(150, 200);

    glEnd();
}

void displayQuads(){
    //Treats each group of four vertices as an independent quadrilateral.
    //Vertices 4n - 3, 4n - 2, 4n - 1, and 4n define quadrilateral n. N/4 quadrilaterals are drawn.

    glBegin(GL_QUADS);

    glVertex2d(400, 400);
    glVertex2d(450, 400);
    glVertex2d(450, 500);
    glVertex2d(400, 500);

    glEnd();
}

void displayQuadStrips(){
    //Draws a connected group of quadrilaterals.
    //One quadrilateral is defined for each pair of vertices presented after the first pair.
    //Vertices 2n - 1, 2n, 2n + 2, and 2n + 1 define quadrilateral n. N/2 - 1 quadrilaterals are drawn.
    //Note that the order in which vertices are used to construct a quadrilateral
    //from strip data is different from that used with independent data.

    glBegin(GL_QUAD_STRIP);

    glVertex2d(320, 320);
    glVertex2d(360, 320);

    glVertex2d(320, 360);
    glVertex2d(360, 360);

    glVertex2d(360, 390);
    glVertex2d(390, 390);

    glEnd();

}

void displayPolygons(){
    //Draws a single, convex polygon.
    //Vertices 1 through N define this polygon.

    glBegin(GL_POLYGON);

    glVertex2d(510, 0);
    glVertex2d(500, 20);
    glVertex2d(500, 40);
    glVertex2d(510, 60);
    glVertex2d(520, 40);
    glVertex2d(520, 20);

    glEnd();
}

