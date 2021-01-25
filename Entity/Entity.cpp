#include "Entity/Entity.h"
#include <cstdlib>
#include "../Server.h"

void Entity::generateID()
{
    int id;
    do{
        id = rand();
    }while(Server::getEntity(id).getEntityID() != -1);
    setEntityID(id);
    
}