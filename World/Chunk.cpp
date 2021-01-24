#include "Chunk.h"

Block* Chunk::GetBlock(int x, int y, int z)
{
    return &blocks[(z*16+x)+(y*256)];
}

void Chunk::SetBlock(int x, int y, int z, Block block)
{
    *GetBlock(x,y,z) = block;
}

void Chunk::Load()
{
    isLoaded = true;
}

void Chunk::unLoad()
{
    isLoaded = false;
}