#include<thread>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<iostream>
#include "Server.h"


void error(char* str)
{
    perror(str);
    exit(1);
}

Server::Server(int port)
{
    this->portno = port;
    
}

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
    
}