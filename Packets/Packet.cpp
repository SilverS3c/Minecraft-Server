#ifndef PACKET_H
#include "Packet.h"
#endif
#include "Handshake.h"
#include "LoginRequest.h"
#ifndef CLIENT_H
#include "Client.h"
#endif
#ifndef PLAYERABILITIES_H
#include "PlayerAbilities.h"
#endif



Packet* Parse(char* data, int len, Client* c)
{
    switch (data[0])
    {
    case 0x02:
    {
        Handshake* h = new Handshake(data+1, len-1, c);
        return h;
    }
    case 0x01:
    {
        LoginRequest* l = new LoginRequest(data+1, len-1, c);
        return l;
    }
    case 0xca:
    {
        PlayerAbilities* p = new PlayerAbilities(data+1, len-1, c);
        return p;
    }
    default:
        break;
    }
    return 0;
}