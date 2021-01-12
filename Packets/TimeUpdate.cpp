#ifndef TIMEUPDATE_H
#include "TimeUpdate.h"
#endif

char* TimeUpdate::build()
{
    this->len = 9;
    char* resp = new char[this->len];
    resp[0] = OPCode;
    *(long*)(resp+1) = htobe64(this->time);
    return resp;
}

void TimeUpdate::Send(Client* c)
{
    char* r = this->build();
    c->writeBytes(r, this->len);
}