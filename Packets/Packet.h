#ifndef PACKET_H
#define PACKET_H

#include "Client.h"

class Packet
{
    public:
        char OPCode;
        virtual char* build() = 0;
        Packet(char OPCode): OPCode{OPCode} {};
        virtual void Response(Client* c) {}
        
};

Packet* Parse(unsigned char* data, int len, Client* c);

#endif