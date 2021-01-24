#ifndef WORLD_H
#define WORLD_H
#endif
#include "Region.h"
#include <vector>

class World
{
    public:
        std::vector<Region> regions = std::vector<Region>();
        Block* GetBlock(Location loc) {return GetBlock(loc.x, loc.y, loc.z); }
        Block* GetBlock(int x, int y, int z);
        Region* GetRegion(Location loc) {return GetRegion(loc.x, loc.z); }
        Region* GetRegion(int x, int z);
        Chunk* GetChunk(Location loc) {return GetChunk(loc.x, loc.z); }
        Chunk* GetChunk(int x, int z);
        void SetBlock(Location loc, Block block) {return SetBlock(loc.x, loc.y, loc.z, block); }
        void SetBlock(int x, int y, int z, Block block);
        void SetRegion(Location loc, Region region) {SetRegion(loc.x, loc.z, region); }
        void SetRegion(int x, int z, Region region);
        void SetChunk(Location loc, Chunk chunk) {SetChunk(loc.x, loc.z, chunk); }
        void SetChunk(int x, int z, Chunk chunk);
    
};