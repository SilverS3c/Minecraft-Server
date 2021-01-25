#ifndef FUNCTION_H
#define FUNCTION_H
int readVarInt(char* buff);
int writeVarInt(int value, char* buf);
unsigned short getShortRevEndian(unsigned short* data);
void processUnicodes(char16_t* dst, unsigned char* data, int len);
int strlen16(char16_t* str);
#endif