#include "ChunkAllocation.h"

char* ChunkAllocation::build()
{
    char* res = new char[this->len];
    res[0] = OPCode;
    *(int*)(res+1) = htobe32(x);
    *(int*)(res+5) = htobe32(z);
    res[9] = mode;
    return res;
}

void ChunkAllocation::Send(Client* c)
{
    char* r = build();
    c->writeBytes(r,this->len);
}