#ifndef PACKET_H
#include "Packet.h"
#endif
#ifndef PLAYERABILITIES_H
#define PLAYERABILITIES_H
#endif

class PlayerAbilities: public Packet
{
    bool invlunerability, isFlying, canFly, InstantDestroy;
    public:
        int len=0;
        PlayerAbilities(char* data, int len, Client* c);
        PlayerAbilities(bool invuln, bool isFly, bool canFly, bool InstantDistroy): Packet(0xca) {this->invlunerability=invuln; this->isFlying=isFly; this->canFly=canFly; this->InstantDestroy=InstantDistroy;}
        char* build() override;
        void Response(Client* c) override;
        void Send(Client* c);
};