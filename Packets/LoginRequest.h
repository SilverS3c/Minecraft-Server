#ifndef PACKET_H
#include "Packet.h"
#endif

class LoginRequest: public Packet
{

    int ProtocolVersion=0, EntityID=0, ServerMode=0, Dimension=0;
    std::u16string LevelType;
    char Difficulty=0;
    unsigned char MaxPlayers=0;
    std::u16string username;
    public:
        LoginRequest(char* data, int len, Client* c);
        LoginRequest(int EntId, std::u16string LevelType, int ServerMode, int Dimension, char Difficulty, unsigned char MaxPLayers);
        void Response(Client* c) override;
        char* build() override;
        int len = 0;
};