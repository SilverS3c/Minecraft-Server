#ifndef CONFIG_H
#define CONFIG_H
#include <string>


class Config
{
    public:
        static std::u16string LevelType;
        static const int ServerMode = 0;
        static const char Difficulty = 2;
        static const unsigned char MaxPlayers = 32;
        static const int SpawnX = 1000, SpawnY = 50, SpawnZ = 1000;
        static std::string WorldName;
};
#endif