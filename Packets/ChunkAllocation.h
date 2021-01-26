#ifndef CHUNKALLOCATION_H
#define CHUNKALLOCATION_H

#include "Packet.h"

class ChunkAllocation: public Packet
{
    public:
        int len=10;
        int x=0,z=0;
        bool mode=1;
        ChunkAllocation(int x, int z, bool mode): Packet(0x32) {this->x = x; this->z=z; this->mode = mode; }
        char* build() override;
        void Send(Client* c);
};
#endif