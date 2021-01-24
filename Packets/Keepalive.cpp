#include "Keepalive.h"
#include <cstdlib>

char* Keepalive::build()
{
    char* resp = new char[this->len];
    resp[0] = OPCode;
    *(int*)(resp+1) = htobe32(rand());
    return resp;
}

void Keepalive::Send(Client* c)
{
    char* r = build();
    c->writeBytes(r, this->len);
}