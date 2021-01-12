#ifndef PACKET_H
#include "Packet.h"
#endif
#ifndef SPAWNPOSITION_H
#define SPAWNPOSITION_H
#endif

class SpawnPosition: public  Packet
{
    public:
        int len = 0;
        int x=0,y=0,z=0;
        SpawnPosition(int x, int y, int z): Packet(0x06) {this->x=x; this->y = y; this->z = z;}
        void Send(Client* c);
        char* build() override;
};
