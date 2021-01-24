#ifndef WORLD_H
#include "World.h"
#endif
#include <string>

class nbt
{
    public:
        Region* LoadRegionFile(std::string filename);
};