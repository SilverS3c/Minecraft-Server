#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../World/Location.h"
#include "../Inventory.h"

class Player: public Entity
{
    public:
        Player() {}
        double stance = 1;
        Locationd locationd;
        float yaw=0, pitch=0;
        bool onGround = false;
        Inventory inventory;

};

#endif