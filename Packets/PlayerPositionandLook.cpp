#include "PlayerPositionandLook.h"
#include "Keepalive.h"
#include <time.h>
#include "Server.h"
#include "iostream"
#include "../Functions.h"
#include "ChunkAllocation.h"
#include "ChunkData.h"

PlayerPositionandLook::PlayerPositionandLook(unsigned char* data, int len, Client* c): Packet(0x0d)
{
    this->x = betohDouble((double*)data);
    this->y = betohDouble((double*)(data+8));
    this->stance = betohDouble((double*)(data+16));
    this->z = betohDouble((double*)(data+24));
    this->yaw = ReverseFloat(*(float*)(data+32));
    this->pitch = ReverseFloat(*(float*)(data+36));
    this->onGround = (data+40);

}

PlayerPositionandLook::PlayerPositionandLook(double x, double stance, double y, double z, float yaw, float pitch, bool onGround): Packet(0x0d)
{
    this->x = x;
    this->stance = stance;
    this->y = y;
    this->z = z;
    this->yaw = yaw;
    this->pitch = pitch;
    this->onGround = onGround;
}

char* PlayerPositionandLook::build()
{
    char* res = new char[this->len];
    res[0] = OPCode;
    *(double*)(res+1) = htobeDouble(&this->x);
    *(double*)(res+9) = htobeDouble(&this->stance);
    *(double*)(res+17) = htobeDouble(&this->y);
    *(double*)(res+25) = htobeDouble(&this->z);
    *(float*)(res+33) = ReverseFloat(this->yaw);
    *(float*)(res+37) = ReverseFloat(this->pitch);
    *(res+41) = this->onGround;

    return res;
}

void PlayerPositionandLook::Send(Client* c)
{
    char* r = build();
    c->writeBytes(r, this->len);
    std::cout << "Sent: x=" << x << " y=" << y << " z=" << z << std::endl;
}

void PlayerPositionandLook::copyToPlayer(Player* p)
{
    p->locationd.x = this->x;
    p->locationd.y = this->y;
    p->locationd.z = this->z;
    p->yaw = this->yaw;
    p->pitch = this->pitch;
    p->stance = this->stance;
    p->onGround = this->onGround;
}

void PlayerPositionandLook::copyFromPlayer(Player* p)
{
    this->x = p->locationd.x;
    this->y = p->locationd.y;
    this->z = p->locationd.z;
    this->yaw = p->yaw;
    this->pitch = p->pitch;
    this->stance = p->stance;
    this->onGround = p->onGround;
}

void PlayerPositionandLook::Response(Client* c)
{
    
    copyToPlayer(&(c->player));
    std::cout << "Received: x=" << c->player.locationd.x << " y=" << c->player.locationd.y << " z=" << c->player.locationd.z << std::endl;
    if (c->last_keepalive+1 < time(0))
    {
        Keepalive keepalive;
        keepalive.Send(c);
        c->last_keepalive = time(0);
    }
    /*Server::overworld->LoadRegion((int)(c->player.locationd.x)/512, (int)(c->player.locationd.z)/512);
    ChunkAllocation alloc(x/16,z/16,true);
    alloc.Send(c);
    ChunkData data(x,z, Server::overworld);
    data.Send(c);*/
}