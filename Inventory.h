#ifndef INVENTORY_H
#define INVENTORY_H
#include "Packets/Slot.h"

class Inventory
{
    public:
        static const int SlotCount = 45;
        Slot* slots = new Slot[SlotCount];
        
};

#endif