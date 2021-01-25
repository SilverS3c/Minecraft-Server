#ifndef BLOCK_H
#define BLOCK_H
#include "Location.h"

class Block
{
    public:
        char id=0, data=0;
        Location GetLocation();
        Block(char id, char data) {this->id = id; this->data = data; }
        Block(char id) {this->id = id; }
        Block() {}
};
#endif