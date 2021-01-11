#ifndef PACKET_H
#include "Packet.h"
#endif
#include<string>

class Handshake: public Packet
{
    char* data;
    
    public:
        int len = 0;
        std::u16string respData;
        Handshake(char* data, int len, Client* c);
        Handshake(std::u16string str, Client* c);
        void Response(Client* c);
        char* build();

};

