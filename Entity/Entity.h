#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
    int EntityID = -1;
    public:
        int getEntityID() {return EntityID;}
        void setEntityID(int id) {EntityID = id;}
        Entity() {}
        Entity(int id) {EntityID = id; }
        void generateID();

};
#endif