#ifndef WORLD_H
#include "World.h"
#endif
#include <iostream>

Region* World::GetRegion(int x, int z)
{
    for (int i=0; i<regions.size(); i++)
    {
        if ((&regions[i])->x == x && (&regions[z])->z == z) return &regions[i];
    }
    std::cout<< "\033[31m" <<"Can't find region (" << x << ", " << z << ")" << "\033[0m" << std::endl;
    return 0;
}

Chunk* World::GetChunk(int x, int z)
{
    return GetRegion(x>>9,z>>9)->GetChunk((x/16)%32, (z/16)%32);
}

Block* World::GetBlock(int x, int y, int z)
{
    return GetRegion(x>>9, z>>9)->GetBlock(x%512,y,z%512);
}

void World::SetBlock(int x, int y, int z, Block block)
{
    *GetBlock(x,y,z) = block;
}

void World::SetRegion(int x, int z, Region region)
{
    *GetRegion(x,z) = region;
}