#include "Packet.h"
#include "../World/Chunk.h"

class ChunkData: public Packet
{
    public:
        ChunkData(Chunk* chunk);
};