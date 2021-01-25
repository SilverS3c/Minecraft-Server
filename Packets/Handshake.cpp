#include "Handshake.h"
#include "../Functions.h"
#include<string.h>
#include<iostream>

Handshake::Handshake(unsigned char* data, int len, Client* c): Packet(0x02)
{
    unsigned short strsize = getShortRevEndian((unsigned short*)data);
    data += 2;
    char16_t str[strsize];
    processUnicodes(str, data, strsize);
    std::u16string user = std::u16string(str);
    user = user.substr(0, user.find_first_of(u";"));
    c->setUsername(user);
    
}

char* Handshake::build()
{
    
    int l = 1 + respData.length()*2 + 2; //Calc total resp length
    this->len=l;
    char* resp = new char[this->len];
    resp[0] = OPCode;   // Set op code
    unsigned short rlen = respData.length();
    rlen = getShortRevEndian(&rlen);
    memcpy(resp+1, &rlen, 2);   // set str len
    char16_t tmp[respData.length()];
    processUnicodes(tmp, (unsigned char*)respData.c_str(), respData.length());
    memcpy(resp+3, tmp, respData.length()*2);   //set str
    return resp;
}

Handshake::Handshake(std::u16string str, Client* c): Packet(0x02)
{
    respData = str;
}

void Handshake::Response(Client* c)
{
    std::cout << "S->C Handshake" << std::endl;
    Handshake h(u"-", c);
    char* buf = h.build();
    c->writeBytes(buf, h.len);
}