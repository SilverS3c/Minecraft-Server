#include "LoginRequest.h"
#include<endian.h>
#include<iostream>
#include<string.h>

#include<string>
#include<locale>
#include<codecvt>

#include "Functions.h"

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

}

char* LoginRequest::build()
{

}

void LoginRequest::Response(Client* c)
{

}