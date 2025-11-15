#ifndef CHUNKS_H
#define CHUNKS_H
#include <GL/glu.h>
#include <GL/glut.h>

typedef struct Block
{
    GLfloat x;
    GLfloat y;
    GLfloat z;

} Block;

typedef struct Chunk
{
    Block blocks[2*2*5];
} Chunk;

typedef struct PlayerChunks
{
    Chunk chunks[16];
} PlayerChunks;

extern PlayerChunks world;
extern int ChunkWidthX;
extern int ChunkLengthZ;
extern int ChunkHeightY;
extern float BlockWidthX;
extern float BlockLengthY;
extern float BlockHeightZ;

void createChunk(Chunk *chunk, int xAdd, int zAdd);
void initWorld(PlayerChunks *world);

#endif