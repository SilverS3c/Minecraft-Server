#include "LoginRequest.h"
#include<endian.h>
#include<iostream>
#include<string.h>

#include<string>
#include<locale>
#include<codecvt>

#include "Functions.h"

#ifndef SERVER_H
#include "Server.h"
#endif
#ifndef ENTITY_H
#include "Entity/Entity.h"
#endif
#include "Config.h"
#ifndef SPAWNPOSITION_H
#include "SpawnPosition.h"
#endif
#ifndef PLAYERABILITIES_H
#include "PlayerAbilities.h"
#endif
#ifndef TIMEUPDATE_H
#include "TimeUpdate.h"
#endif

LoginRequest::LoginRequest(char* data, int len, Client* c): Packet(0x01)
{
    ProtocolVersion = be32toh(*(int*)data);
    data += 4;
    std::cout << "Protocol version: " << ProtocolVersion << std::endl;
    short namelen = be16toh(*(short*)data);
    data += 2;
    char16_t tmp[namelen+1];
    tmp[namelen] = 0;
    processUnicodes(tmp, data, namelen);
    username = std::u16string(tmp);
    
    std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>,wchar_t> conv;
    std::wstring test = conv.from_bytes(
        reinterpret_cast<const char*>(&username[0]),
        reinterpret_cast<const char*>(&username[0]+username.size()));
    std::wcout << "username: " << test << std::endl;
    

}

LoginRequest::LoginRequest(int EntId, std::u16string LevelType, int ServerMode, int Dimension, char Difficulty, unsigned char MaxPLayers): Packet(0x01)
{
    EntityID = EntId;
    this->LevelType = LevelType;
    this->ServerMode = ServerMode;
    this->Dimension = Dimension;
    this->Difficulty = Difficulty;
    this->MaxPlayers = MaxPLayers;


}

char* LoginRequest::build()
{
    int tmp_len = LevelType.length()*2;
    int l = 20 + tmp_len;
    this->len=l;
    char* resp = new char[this->len];
    resp[0] = OPCode;
    *(int*)(resp+1) = htobe32(EntityID);

    *(short*)(resp+5) = (short)0;

    *(short*)(resp+7) = htobe16((short)tmp_len/2);

    
    processUnicodes((char16_t*)(resp+9), (char*)LevelType.c_str(), LevelType.length());

    
    *(int*)(resp+9+tmp_len) = htobe32(ServerMode);
    *(int*)(resp+13+tmp_len) = htobe32(Dimension);
    *(resp+17+tmp_len) = Difficulty;
    *(resp+18+tmp_len) = (char)0;
    *(resp+19+tmp_len) = MaxPlayers;
    return resp;

}

void LoginRequest::Response(Client* c)
{
    std::cout << "S->C LoginRequest" << std::endl;
    Entity e = Entity();
    e.generateID();
    Server::addEntity(e);
    LoginRequest req(e.getEntityID(), Config::LevelType, Config::ServerMode, 0, Config::Difficulty, Config::MaxPlayers);
    char* t = req.build();
    c->writeBytes(t, req.len);

    //Send spawn position
    SpawnPosition s(Config::SpawnX, Config::SpawnY, Config::SpawnZ);
    s.Send(c);

    PlayerAbilities abilities(false, false, false, false);
    abilities.Send(c);

    TimeUpdate timeupdate(Server::getTime());
    timeupdate.Send(c);

}