#ifndef LOCATION_H
#define LOCATION_H

#include "Config.h"

class Location
{
    public:
        int x,y,z;
        Location() {}
        Location(int x, int y, int z) {this->x = x; this->y = y; this->z = z;}
        Location(int x, int z) {this->x = x; this->y = 0; this->z = z;}

};

class Locationd
{
    public:
        double x=Config::SpawnX,y=Config::SpawnY,z=Config::SpawnZ;
        Locationd() {}
        Locationd(double x, double y, double z) {this->x = x; this->y = y; this->z = z;}
        Locationd(double x, double z) {this->x = x; this->y = 0; this->z = z;}
};
#endif