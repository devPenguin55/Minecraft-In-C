#include <GL/glu.h>
#include <GL/glut.h>
#include "chunks.h"

PlayerChunks world;
int ChunkWidthX = 2;
int ChunkLengthZ = 2;
int ChunkHeightY = 5;

float BlockWidthX  = 1;
float BlockHeightZ = 1;
float BlockLengthY = 1;

void createChunk(Chunk *chunk, int xAdd, int zAdd) {
    for (int x = 0; x < ChunkWidthX; x++)
    {
        for (int z = 0; z < ChunkLengthZ; z++)
        {
            for (int y = 0; y < ChunkHeightY; y++)
            {
                Block *curBlock = &(chunk->blocks[x + ChunkWidthX*z + (ChunkWidthX*ChunkLengthZ)*y]);

                curBlock->x = BlockWidthX*x + xAdd;
                curBlock->z = BlockHeightZ*z + zAdd;
                curBlock->y = BlockLengthY*(-y);
            }
        }
    }
}

void initWorld(PlayerChunks *world) {
    int x = 0;
    int z = 0;
    for (int i = 0; i<16; i++) {
        x = i % 4;
        z = (int)(i / 4);
        createChunk(&(world->chunks[i]), x*ChunkWidthX, z*ChunkLengthZ);
    }
}