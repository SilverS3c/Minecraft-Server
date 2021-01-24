
class Location
{
    public:
        int x,y,z;
        Location();
        Location(int x, int y, int z) {this->x = x; this->y = y; this->z = z;}
        Location(int x, int z) {this->x = x; this->y = 0; this->z = z;}

};