//Try out later

//Global variable for checker texture
const int checkerWidth = 64;
const int checkerHeight = 64;
GLubyte checkerImage[checkerHeight][checkerWidth][4];
GLuint texName;

void makeCheckerTexture(){
    int i, j, c;
    
    for(i = 0; i < checkerHeight; i++){
        for(j = 0; j < checkerWidth; j++){
            c = ((((i & 0x8) == 0) ^ (( j & 0x8)) == 0)) * 255;
            checkerImage[i][j][0] = (GLubyte) c;
            checkerImage[i][j][1] = (GLubyte) c;
            checkerImage[i][j][2] = (GLubyte) c;
            checkerImage[i][j][3] = (GLubyte) 255;
        }
    }
}

void drawTexture(){
    glEnable(GL_TEXTURE_2D);

    makeCheckerTexture();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //figure out how this works
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkerWidth, checkerHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texName);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(5, -1, 0);
    glTexCoord2f(0, 1); glVertex3f(5, 1, 0);
    glTexCoord2f(1, 1); glVertex3f(4, 1, 0);
    glTexCoord2f(1, 0); glVertex3f(4, -1, 0);
    
    glDisable(GL_TEXTURE_2D);
    glEnd();

    glFlush();
}