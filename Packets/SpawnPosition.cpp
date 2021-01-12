#ifndef SPAWNPOSITION_H
#include "SpawnPosition.h"
#endif

char* SpawnPosition::build()
{
    int l = 13;
    this->len = l;
    char* resp = new char[this->len];
    resp[0] = OPCode;
    *(int*)(resp+1) = htobe32(this->x);
    *(int*)(resp+5) = htobe32(this->y);
    *(int*)(resp+9) = htobe32(this->z);
    return resp;
}

void SpawnPosition::Send(Client* c)
{
    char* t = this->build();
    c->writeBytes(t, this->len);
}