#ifndef CLIENT_H
#include "Client.h"
#endif
#include<string.h>
#include<unistd.h>
#include<iostream>
#include "Packets/Packet.h"
#include "Packets/Handshake.h"



Client::Client(int socket, struct sockaddr_in client_addr)
{
   
    sockfd = socket;
    memcpy(&(this->client_addr), &client_addr, sizeof(client_addr));
}

int Client::readBytes()
{
    bzero(buff, BUFF_SIZE);
    int n = read(sockfd, buff, BUFF_SIZE);
    if (n<0)
    {
        perror("Error reading from socket.");
        //termiante connection
    }
    return n;
}

int Client::writeBytes(char* buf, int len)
{
    int n = write(sockfd, buf, len);
    if (n<0)
    {
        perror("Error sending from socket.");
        //termiante connection
    }
    return n;
}

void Client::loop()
{
    while (true)
    {
        //wait for input
        int n = readBytes();
        //process
        Packet* packet = Parse(buff, n, this);
        if (!packet) continue;
        //response
        packet->Response(this);
    }
}