#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

GLfloat T = 0;
GLfloat CameraX = 0;
GLfloat CameraY = 0;
GLfloat CameraZ = 3;
GLfloat PlayerDirX = 0;
GLfloat PlayerDirY = 0;
GLfloat PlayerDirZ = -1;
double PLAYER_SPEED = 0.001;

int lastMouseX = 0;
int lastMouseY = 0;
int mouseInteractionStarted = 0;

int pressedKeys[256] = {0};

void spinObject() {
    T =  T + 0.00025;
    if (T > 360)
        T = 0;
    glutPostRedisplay();
}

void handleKeyDown(unsigned char key, int x, int y) {
    pressedKeys[key] = 1;
    
}
void handleKeyUp(unsigned char key, int x, int y) {
    pressedKeys[key] = 0;
}

void initGraphics() {
    glClearColor(0,0,0,1);
    glColor3f(1,0,0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 20); // z always > 0
    glMatrixMode(GL_MODELVIEW);
}

void face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[], GLfloat transformation[3]) {
    glPushMatrix();
    glTranslatef(transformation[0], transformation[1], transformation[2]); // move it up

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
    if (pressedKeys['w']) {
        CameraX += PlayerDirX * PLAYER_SPEED;
        CameraZ += PlayerDirZ * PLAYER_SPEED;
    }
    if (pressedKeys['s']) {
        CameraX -= PlayerDirX * PLAYER_SPEED;
        CameraZ -= PlayerDirZ * PLAYER_SPEED;
    }     
    if (pressedKeys['a']) {
        CameraX -= -PlayerDirZ * PLAYER_SPEED;
        CameraZ -= PlayerDirX * PLAYER_SPEED;
    }
    if (pressedKeys['d']) {
        CameraX += -PlayerDirZ * PLAYER_SPEED;
        CameraZ += PlayerDirX * PLAYER_SPEED;
    }


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
    
    // glRotatef(T,0,0,0);
    GLfloat translation[3] = {1.0f, 1.0f, 0.0f};
    cube(Vertices, translation);

    translation[0] = -1.0f;
    translation[1] = -1.0f;
    translation[2] =  0.0f;
    cube(Vertices, translation);


    // switch the content of color and depth buffers 
    glutSwapBuffers();
}

void handleMouse(int button, int state, int x, int y) {
    // button: GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, etc.
    // state: GLUT_DOWN or GLUT_UP
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;

        mouseInteractionStarted = 1;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mouseInteractionStarted = 0;
    }
}

void handleMovingMouse(int x, int y) {
    if (!mouseInteractionStarted) { return; }

    int dx = x - lastMouseX;
    int dy = y - lastMouseY;

    PlayerDirX += dx * 0.01;
    PlayerDirY += -dy * 0.01;

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(1000, 400);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // rgb model, double buffer -> (color, depth)
    glutCreateWindow("Minecraft");
    glutSetCursor(GLUT_CURSOR_NONE);

    initGraphics();

    glutDisplayFunc(drawGraphics);
    glutKeyboardFunc(handleKeyDown);
    glutKeyboardUpFunc(handleKeyUp);
    glutIdleFunc(spinObject);
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMovingMouse);
    glutMainLoop();

    return 0;
}