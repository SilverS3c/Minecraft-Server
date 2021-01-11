#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include "Client.h"
#include "Entity/Entity.h"



class Server
{
    int sockfd, newsocket, portno, clilen, n;
    char buff[256];
    struct sockaddr_in server_addr, client_addr;
    static const int MAX_PLAYERS = 32;
    static const int MAX_ENTITIES = 128;
    Client* clients = new Client[MAX_PLAYERS];
    Entity* entities = new Entity[MAX_ENTITIES];
    bool entity_lock = false;
    public:
        Server(int port);
        int run();
        Entity* getEntities() { if (!entity_lock) return entities; else return 0;}
        void addEntity(Entity e);
        Entity getEntity(int id);
        void removeEntity(int id);
        void removeEntity(Entity e);
};