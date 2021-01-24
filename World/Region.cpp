#include "Region.h"

Block* Region::GetBlock(int x, int y, int z)
{
    return GetChunk(x>>4, z>>4)->GetBlock(x%16,y,z%16);
}

Chunk* Region::GetChunk(int x, int z)
{
    return &chunks[(z*32+x)];
}

void Region::SetBlock(int x, int y, int z, Block block)
{
    *GetBlock(x,y,z) = block;
}