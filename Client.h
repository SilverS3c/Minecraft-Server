#ifndef CLIENT_H
#define CLIENT_H
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<thread>
#include "Entity/Player.h"


class Client
{
    int sockfd = 0;
    struct sockaddr_in client_addr;
    std::u16string username;
    std::string uuid;
    

    public:
        static const int BUFF_SIZE = 2048;
    unsigned char buff[BUFF_SIZE];
    

    public:
        time_t last_keepalive = 0;
        Player player;
        std::thread cthread;
        int readBytes();
        int writeBytes(char* buf, int len);
        Client(int sock, struct sockaddr_in client_addr);
        Client() {}
        int getSockfd() { return sockfd; }
        void loop();
        std::u16string getUsername() {return username;}
        void setUsername(std::u16string usr) {username = usr; }


};
#endif