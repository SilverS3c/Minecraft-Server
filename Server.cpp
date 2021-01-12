#include<thread>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<iostream>
#ifndef SERVER_H
#include "Server.h"
#endif


void error(char* str)
{
    perror(str);
    exit(1);
}


bool Server::entity_lock = false;

Server::Server(int port)
{
    this->portno = port;
    
}
Entity* Server::entities = new Entity[Server::MAX_ENTITIES];
long Server::timeLastChecked = std::time(0);
int Server::run()
{
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char a[] = "Cannot create socket";
    if (sockfd < 0) error(a);

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portno);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    char err[] = "Can't bind address!";
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) error(err);
    listen(sockfd, 5);

    clilen = sizeof(client_addr);
    std::cout << "Listening..." << std::endl;
    while (true)
    {
        newsocket = accept(sockfd, (struct sockaddr *)&client_addr, (socklen_t *)&clilen);
        if (newsocket < 0) continue;
        std::cout << "Connected\n";
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (clients[i].getSockfd() == 0)
            {
                clients[i] = Client(newsocket, client_addr);
                clients[i].cthread = std::thread(&Client::loop, &clients[i]);
                std::cout << "Thread Started\n";
                break;
            }
        }
    }
    

    return 0;
}

void Server::addEntity(Entity e)
{
    while (Server::entity_lock);
    Server::entity_lock = true;
    for (int i=0; i<Server::MAX_ENTITIES; i++)
    {
        if (Server::entities[i].getEntityID() == -1)
        {
            Server::entities[i] = e;
            break;
        }
    }
    Server::entity_lock = false;
}

Entity Server::getEntity(int id)
{
    while (Server::entity_lock);
    Server::entity_lock = true;
    for (int i = 0; i < Server::MAX_ENTITIES; i++)
    {
        if (Server::entities[i].getEntityID() == id)
        {
            Server::entity_lock = false;
            return Server::entities[i];
        }
    }
    Server::entity_lock = false;
    return Entity(-1);
}

long Server::getTime()
{
    long diff = std::time(0)-Server::timeLastChecked;
    return (diff*20)%24000;
}