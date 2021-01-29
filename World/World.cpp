#include "World.h"
#include <iostream>
#include <fstream>
#include "../Config.h"
#include "nbt.h"
#include "Generator.h"
#include <chrono>


Region* World::GetRegion(int x, int z)
{
    for (int i=0; i<regions.size(); i++)
    {
        if (((&regions[i])->x == x) && ((&regions[i])->z == z)) return &regions[i];
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

void World::AddRegion(int x, int z, Region region)
{
    regions.push_back(region);
}

void World::SetChunk(int x, int z, Chunk chunk)
{
    *GetChunk(x,z) = chunk;
}

void World::LoadRegion(int x, int z) // Needs optimization
{
    if (GetRegion(x,z))
    {
        if (GetRegion(x,z)->isLoaded)
        {
            //std::cout << "\033[33m" << "Region "<<std::to_string(x)<<" "<<std::to_string(z)<<" is already loaded!" << "\033[0m"<<std::endl;
            return;
        }
    }
    std::string filename = Config::WorldName+"/region/r."+std::to_string(x)+"."+std::to_string(z)+".mca";
    std::ifstream regionfile(filename);
    if (!regionfile.good())
    {
        regionfile.close();
        // generation
        Generator gen;
        Region newRegion;
        //std::cout << "Generating region..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (int z=0; z<32;z++)
        {
            for (int x = 0; x<32;x++)
            {
                newRegion.SetChunk(x,z,*gen.GenerateChunk());
            }

        }
        newRegion.x = x;
        newRegion.z = z;
        newRegion.isLoaded = true;
        AddRegion(x,z,newRegion);
        std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now()-start;
        //std::cout << "Ended in: " << diff.count() << " s" << std::endl;
    }
    else
    {
        regionfile.close();
        // load
        nbt nbtLoader;
        AddRegion(x,z,*nbtLoader.LoadRegionFile(filename));
    }
}