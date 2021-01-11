#ifndef PACKET_H
#include "Packet.h"
#endif
#include "Handshake.h"
#include "LoginRequest.h"
#ifndef CLIENT_H
#include "Client.h"
#endif



Packet Parse(char* data, int len, Client* c)
{
    switch (data[0])
    {
    case 0x02:
        return Handshake(data+1, len-1, c);
    case 0x01:
        return LoginRequest(data+1, len-1, c);
    default:
        break;
    }
    return Packet(0x0);
}