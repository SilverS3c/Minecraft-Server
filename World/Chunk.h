#include "Block.h"

class Chunk
{
    public:
        bool isLoaded = false;
        Block* blocks = new Block[16*256*16];
        Location location;
        void Load();
        void unLoad();
        Block* GetBlock(Location loc) {return GetBlock(loc.x, loc.y, loc.z); }
        Block* GetBlock(int x, int y, int z);
        void SetBlock(Location loc, Block block) {return SetBlock(loc.x, loc.y, loc.z, block); }
        void SetBlock(int x, int y, int z, Block block);
};