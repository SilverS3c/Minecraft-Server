#ifndef CHUNKDATA_H
#define CHUNKDATA_H

#include "Packet.h"
#include "World/World.h"
#include "../World/Chunk.h"

class ChunkData: public Packet
{
    public:
        int x=0,z=0;
        bool GroundUpContinuous=false;
        unsigned short PrimaryBitmap=0, AddBitmap=0;
        int CompressedSize;
        int len=0;
        Chunk* chunk;
        ChunkData(int x, int z, World* world);
        char* build() override;
        void Send(Client* c);
        bool isGroundUpContinuous();
        unsigned short calcPrimaryBitmap();
};

#endif