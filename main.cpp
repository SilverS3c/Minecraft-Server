#include "Server.h"


int main(int argc, char* argv[])
{
    Server* server = new Server(25565);
    server->run();

    return 0;
}