#ifndef WORLD_H
#include "World.h"
#endif
#include <iostream>
#include <fstream>
#include "../Config.h"
#include "nbt.h"
#include "Generator.h"
#include <ctime>

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

void World::SetChunk(int x, int z, Chunk chunk)
{
    *GetChunk(x,z) = chunk;
}

void World::LoadRegion(int x, int z) // Needs optimization
{
    if (GetRegion(x,z)->isLoaded)
    {
        std::cout << "\033[33m" << "Region "<<std::to_string(x)<<" "<<std::to_string(z)<<" is already loaded!" << "\033[0m"<<std::endl;
        return;
    }
    std::string filename = Config::WorldName+"/region/r."+std::to_string(x)+"."+std::to_string(z)+".mca";
    std::ifstream regionfile(filename);
    if (!regionfile.good())
    {
        regionfile.close();
        // generation
        Generator gen;
        Region newRegion;
        std::cout << "Generating region..." << std::endl;
        std::time_t start = std::time(0);
        for (int z=0; z<32;z++)
        {
            for (int x = 0; x<32;x++)
            {
                newRegion.SetChunk(x,z,*gen.GenerateChunk());
            }

        }
        SetRegion(x,z,newRegion);
        std::cout << "Ended in: " << std::to_string(std::time(0)-start) << std::endl;
    }
    else
    {
        regionfile.close();
        // load
        nbt nbtLoader;
        SetRegion(x,z,*nbtLoader.LoadRegionFile(filename));
    }
}