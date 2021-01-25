#include "PlayerAbilities.h"

char* PlayerAbilities::build()
{
    this->len = 5;
    char* tmp = new char[this->len];
    tmp[0] = OPCode;
    tmp[1] = invlunerability;
    tmp[2] = isFlying;
    tmp[3] = canFly;
    tmp[4] = InstantDestroy;
    return tmp;
}

PlayerAbilities::PlayerAbilities(unsigned char* data, int len, Client* c): Packet(0xca)
{

}

void PlayerAbilities::Response(Client* c)
{
    /*char* t = this->build();
    c->writeBytes(t, this->len); */
}

void PlayerAbilities::Send(Client* c)
{
    char* t = this->build();
    c->writeBytes(t, this->len);
}