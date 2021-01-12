#ifndef PACKET_H
#define PACKET_H
#endif
#ifndef CLIENT_H
#include "Client.h"
#endif

class Packet
{
    public:
        char OPCode;
        virtual char* build() = 0;
        Packet(char OPCode): OPCode{OPCode} {};
        virtual void Response(Client* c) {}
        
};

Packet* Parse(char* data, int len, Client* c);