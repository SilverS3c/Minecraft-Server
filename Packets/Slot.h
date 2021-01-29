#ifndef SLOT_H
#define SLOT_H

class Slot
{
    public:
        int len = 0;
        bool Present = false;
        char itemID[4] = {};
        char ItemCount = 0;
        char nbt = 0;
        Slot(bool Present, int itemID, char ItemCount, char nbt);
        Slot() {}
        char* build();
        


};

#endif