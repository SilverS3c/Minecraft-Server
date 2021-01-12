#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#ifndef CLIENT_H
#include "Client.h"
#endif
#ifndef ENTITY_H
#include "Entity/Entity.h"
#endif
#ifndef SERVER_H
#define SERVER_H
#endif



class Server
{
    int sockfd, newsocket, portno, clilen, n;
    char buff[256];
    struct sockaddr_in server_addr, client_addr;
    
    Client* clients = new Client[MAX_PLAYERS];
    
    
    public:
        static bool entity_lock;
        static const int MAX_PLAYERS = 32;
        static const int MAX_ENTITIES = 128;
        static Entity* entities;
        Server(int port);
        int run();
        static Entity* getEntities() {return Server::entities;}
        static void addEntity(Entity e);
        static Entity getEntity(int id);
        static void removeEntity(int id);
        static void removeEntity(Entity e);
};