int readVarInt(char* buff);
int writeVarInt(int value, char* buf);
unsigned short getShortRevEndian(unsigned short* data);
void processUnicodes(char16_t* dst, char* data, int len);
int strlen16(char16_t* str);