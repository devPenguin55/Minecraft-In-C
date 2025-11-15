#ifndef RENDER_H
#define RENDER_H
#include <GL/glu.h>
#include <GL/glut.h>

extern GLfloat T;
extern GLfloat CameraX;
extern GLfloat CameraY;
extern GLfloat CameraZ;
extern GLfloat PlayerDirX;
extern GLfloat PlayerDirY;
extern GLfloat PlayerDirZ;

void initGraphics();
void reshape(int width, int height);
void spinObject();
void face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[], GLfloat transformation[3]);
void cube(GLfloat Vertices[8][3], GLfloat transformation[3]);
void drawGraphics();

#endif