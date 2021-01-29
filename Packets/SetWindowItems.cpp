#include "SetWindowItems.h"
#include "string.h"

SetWindowItems::SetWindowItems(char WindowID, short count, Slot* slots): Packet(0x68)
{
    this->WindowId = WindowId;
    this->count = count;
    this->slots = slots;
}

char* SetWindowItems::build()
{
    int allslotslen = 0;
    for (int i=0; i<count; i++)
    {
        slots[i].build();
        allslotslen += slots[i].len;
    }
    this->len = 4+allslotslen;
    char* res = new char[this->len];
    res[0] = OPCode;
    res[1] = WindowId;
    *(short*)(res+2) = htobe16(count);
    for (int i=0; i<count; i++)
    {
        char* s = slots[i].build();
        memcpy(res+4+i*slots[i].len, s, slots[i].len);
    }
    return res;
}

void SetWindowItems::Send(Client* c)
{
    char* r = build();
    c->writeBytes(r, len);
}