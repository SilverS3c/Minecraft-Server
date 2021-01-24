#include "Chunk.h"


class Region
{
    public:
        int x=0, z=0;
        bool isLoaded = false;
        Location location;
        Chunk* chunks = new Chunk[32*32];
        Block* GetBlock(int x, int y, int z);
        Chunk* GetChunk(int x, int z);
        void SetChunk(int x, int z, Chunk chunk);
        void SetBlock(Location loc, Block block) {return SetBlock(loc.x, loc.y, loc.z, block); }
        void SetBlock(int x, int y, int z, Block block);
        void Load();
        void unLoad();
};