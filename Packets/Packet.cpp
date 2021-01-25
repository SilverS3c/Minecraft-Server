#include "Packet.h"
#include "Handshake.h"
#include "LoginRequest.h"
#include "Client.h"
#include "PlayerAbilities.h"



Packet* Parse(unsigned char* data, int len, Client* c)
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