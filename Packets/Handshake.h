#ifndef HANDSHAKE_H
#define HANDSHAKE_H
#include "Packet.h"
#include<string>

class Handshake: public Packet
{
    char* data;
    
    public:
        int len = 0;
        std::u16string respData;
        Handshake(unsigned char* data, int len, Client* c);
        Handshake(std::u16string str, Client* c);
        void Response(Client* c) override;
        char* build() override;

};

#endif