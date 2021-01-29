#include "Slot.h"
#include "../Functions.h"
#include <string.h>

Slot::Slot(bool Present, int itemID, char ItemCount, char nbt)
{
    this->Present = Present;
    writeVarInt(itemID, this->itemID);
    this->ItemCount = ItemCount;
    this->nbt = nbt;
}

char* Slot::build()
{
    
    this->len = 1+ (readVarInt(this->itemID)==0)?0:strlen(this->itemID) + (ItemCount==0)?0:1 + (nbt==0)?0:1;
    char* res = new char[this->len];
    char* init = res;
    *(res++) = this->Present;
    if (Present)
    {
        int i = 0;
        while(res != 0)
        {
            *(res++) = itemID[i++];
        }
        *(res++) = this->ItemCount;
        *res = nbt;
    }
    return init;

}