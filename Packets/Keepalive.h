#include "Packet.h"

class Keepalive: public Packet
{
    public:
        int len = 5;
        Keepalive(): Packet(0x00) {}
        char* build() override;
        void Send(Client* c);
};