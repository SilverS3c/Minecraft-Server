#ifndef NBT_H
#define NBT_H
#include "World.h"
#include <string>

class nbt
{
    public:
        nbt() {}
        Region* LoadRegionFile(std::string filename) { return 0; } // test
};
#endif