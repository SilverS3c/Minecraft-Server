#include "Functions.h"
#include <arpa/inet.h>
#include<string.h>

int readVarInt(char* buff)
{
    int numRead = 0;
    int result = 0;
    char read = 0;
    do
    {
        read = buff[numRead];
        int value = (read & 0b01111111);
        result |= (value << (numRead*7));
        numRead++;
        if (numRead > 5)
        {
            //too big
        }
    } while ((buff[numRead] & 0b10000000) != 0);
    return result;
}

int writeVarInt(int value, char* buf)
{
    int n = 0;
    do
    {
        char temp = (value & 0b01111111);
        value >>= 7;
        if (value != 0)
        {
            temp |= 0b10000000;
        }
        buf[n] = temp;
        n++;
    } while (value != 0);
    return n;
}

unsigned short getShortRevEndian(unsigned short* data)
{
    return ntohs(*(unsigned short *)(data));
}

void processUnicodes(char16_t* dst, char* data, int len)
{
    memcpy(dst, data, len*2);
    for (int i=0; i<len; i++)
    {
        dst[i] = ntohs(dst[i]);
    }

}

int strlen16(char16_t* str)
{
    int counter = 0;
    if (!str) return -1;
    char16_t* tmp = str;
    while (tmp)
    {
        counter++;
        tmp++;
    }
    return counter;
}