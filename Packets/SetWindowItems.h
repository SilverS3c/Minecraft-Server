#ifndef SETWINDOWITEMS_H
#define SETWINDOWITEMS_H

#include "Packet.h"
#include "Slot.h"

class SetWindowItems: public Packet
{
    public:
        int len = 0;
        char WindowId;
        short count;
        Slot* slots;
        SetWindowItems(char WindowId, short count, Slot* slots);
        char* build() override;
        void Send(Client* c);

};
#endif