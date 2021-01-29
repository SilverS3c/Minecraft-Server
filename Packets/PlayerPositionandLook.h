#ifndef PLAYERPOSITIONANDLOOK_H
#define PLAYERPOSITIONANDLOOK_H

#include "Packet.h"

class PlayerPositionandLook: public Packet
{
    public:
        int len = 42;
        double x,y,stance,z;
        float yaw, pitch;
        bool onGround;
        PlayerPositionandLook(unsigned char* data, int len, Client* c);
        PlayerPositionandLook(double x, double stance, double y, double z, float yaw, float pitch, bool onGround);
        PlayerPositionandLook():Packet(0x0d) {}
        char* build() override;
        void Send(Client* c);
        void copyToPlayer(Player* p);
        void copyFromPlayer(Player* p);
        void Response(Client* c) override;
};

#endif