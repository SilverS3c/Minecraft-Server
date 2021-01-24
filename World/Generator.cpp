#include "Generator.h"
#include "Material.h"

Chunk* Generator::GenerateChunk()
{
    Chunk* chunk = new Chunk();
    int Height = 30;
    for (int y=0; y<Height; y++)
    {
        for (int z=0; z<16; z++)
        {
            for (int x=0; x<16; x++)
            {
                if (y==0) chunk->SetBlock(x,y,z,Block(Material::BEDROCK)); continue;
                if (y<Height/2) chunk->SetBlock(x,y,z,Block(Material::STONE)); continue;
                if (y<Height) chunk->SetBlock(x,y,z,Block(Material::DIRT)); continue;
                chunk->SetBlock(x,y,z,Block(Material::GRASS));
            }
        }
    }
    return chunk;
}