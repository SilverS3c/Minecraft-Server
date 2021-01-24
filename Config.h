#include <string>


class Config
{
    public:
        static std::u16string LevelType;
        static const int ServerMode = 0;
        static const char Difficulty = 2;
        static const unsigned char MaxPlayers = 32;
        static const int SpawnX = 0, SpawnY = 50, SpawnZ = 0;
        static std::string WorldName;
};