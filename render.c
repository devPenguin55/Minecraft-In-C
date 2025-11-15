#include <GL/glu.h>
#include <GL/glut.h>
#include "render.h"
#include "input.h"
#include "chunks.h"

GLfloat T = 0;

void initGraphics() {
    glClearColor(0,0,0,1);
    glColor3f(1,0,0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 20); // z always > 0
    glMatrixMode(GL_MODELVIEW);
}

void spinObject() {
    T = T + 0.00025;
    if (T > 360)
        T = 0;
    glutPostRedisplay();
}

void face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[], GLfloat transformation[3]) {
    glPushMatrix();
    glTranslatef(transformation[0], transformation[1], transformation[2]); // move it up
    glScalef(0.5f, 0.5f, 0.5f);

    glBegin(GL_POLYGON);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);
    glEnd();

    glPopMatrix();
}

void cube(GLfloat Vertices[8][3], GLfloat transformation[3]) {
    // front
    glColor3f(1,0,0);
    face(Vertices[0], Vertices[1], Vertices[2], Vertices[3], transformation);
    
    // back
    glColor3f(0,1,0);
    face(Vertices[4], Vertices[5], Vertices[6], Vertices[7], transformation);
    
    // left
    glColor3f(0,0,1);
    face(Vertices[0], Vertices[3], Vertices[7], Vertices[4], transformation);
    
    // right
    glColor3f(1,0,1);
    face(Vertices[1], Vertices[2], Vertices[6], Vertices[5], transformation);

    // top
    glColor3f(1,1,0);
    face(Vertices[0], Vertices[1], Vertices[5], Vertices[4], transformation);
    
    // bottom
    glColor3f(0,1,1);
    face(Vertices[3], Vertices[2], Vertices[6], Vertices[7], transformation);
}

void drawGraphics() {
    handleUserMovement();

    GLfloat Vertices[8][3] = {
        // front face
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 0.5},
        {0.5, -0.5, 0.5},
        {-0.5, -0.5, 0.5},
        // back face
        {-0.5, 0.5, -0.5},
        {0.5, 0.5, -0.5},
        {0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
    };


    // clear color buffer to clear background, uses preset color setup in initGraphics
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    // camera
    glLoadIdentity();
    // eye -> where the camera is located in the world space
    // center -> where the camera is looking at
    // up -> what direction is up for the camera
    // CameraX = cos(T)*15;
    // CameraZ = sin(T)*15;
    gluLookAt(
        CameraX,CameraY,CameraZ,  
        CameraX+PlayerDirX,CameraY+PlayerDirY,CameraZ+PlayerDirZ,  
        0,1,0
    );

    glPointSize(5);
    
    for (int chunkIndex = 0; chunkIndex < 16; chunkIndex++)
    {
        Chunk *curChunk = &(world.chunks[chunkIndex]);
        int minX = 727379969;
        int maxX = -727379969;
        int minZ = 727379969;
        int maxZ = -727379969;
        for (int blockIndex = 0; blockIndex < ChunkWidthX * ChunkLengthZ * ChunkHeightY; blockIndex++) {
            Block *curBlock = &(curChunk->blocks[blockIndex]);

            minX = (curBlock->x < minX) ? curBlock->x : minX;
            maxX = (curBlock->x > maxX) ? curBlock->x : maxX;
            minZ = (curBlock->z < minZ) ? curBlock->z : minZ;
            maxZ = (curBlock->z > maxZ) ? curBlock->z : maxZ;

            GLfloat translation[3] = {curBlock->x, curBlock->y, curBlock->z};
            cube(Vertices, translation);
        }


        glPushMatrix();

        glLineWidth(10.0f);  
        glBegin(GL_LINE_LOOP);
        glVertex3f(minX - BlockWidthX*0.5, 0.5f, minZ - BlockHeightZ*0.5);
        glVertex3f(maxX + BlockWidthX*0.5, 0.5f, minZ - BlockHeightZ*0.5);
        glVertex3f(maxX + BlockWidthX*0.5, 0.5f, maxZ + BlockHeightZ*0.5);
        glVertex3f(minX - BlockWidthX*0.5, 0.5f, maxZ + BlockHeightZ*0.5);
        glEnd();
        glLineWidth(1.0f);  

        glPopMatrix();

    }
    
    


    // switch the content of color and depth buffers 
    glutSwapBuffers();
}