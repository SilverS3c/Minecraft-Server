#include "ChunkData.h"
#include "Material.h"
#include <zlib.h>
#include <string.h>

ChunkData::ChunkData(int x, int z, World* world): Packet(0x33)
{
    this->x = x;
    this->z = z;
    chunk = world->GetChunk(x,z);
}

char* ChunkData::build()
{

    this->GroundUpContinuous = isGroundUpContinuous();
    this->PrimaryBitmap = calcPrimaryBitmap();
    this->AddBitmap = 0;
    int blockLength = 0;

    for (int i=0; i<16; i++)
    {
        if (PrimaryBitmap & (1 << i))
        {
            blockLength += 16*16*16;
        }
    }
    char* BlockTypeArray = new char[blockLength];
    char* BlockMetadataArray = new char[blockLength/2];
    char* BlockLightArray = new char[blockLength/2];
    char* SkyLightArray = new char[blockLength/2];
    char* BiomeArray = new char[256];
    
    //Fill block type array
    for (int i=0; i<16; i++)
    {
        if (!(PrimaryBitmap & (1 << i))) continue;
        for (int y = 0; y<16; y++)
        {
            for (int z=0; z<16; z++)
            {
                for (int x = 0; x < 16; x++)
                {
                    BlockTypeArray[(z*16+x)+(y+(i*16))*256] = chunk->GetBlock(x,y+i*16,z)->id;
                }
            }
        }
    }
    // Fill block metadata array
    int k=0;
    for (int i=0; i<sizeof(chunk->blocks); i++)
    {
        if (!(PrimaryBitmap & (1 << i)))
        {
            i += 4096;
            continue;
        }
        if (k % 2 == 0)
        {
            BlockMetadataArray[k] |= (chunk->blocks->data<<4) & 0xf0;
        }
        else
        {
            BlockMetadataArray[k] |= (chunk->blocks->data) & 0x0f;
        }
        k++;

    }
    // Fill block light array
    // This is for testing porpuses only, adding actual flood fill algorithm later
    for (int i=0; i<blockLength/2; i++)
    {
        BlockLightArray[i] = 0;
    }

    // Fill sky light array
    for (int i=0; i<blockLength/2; i++)
    {
        SkyLightArray[i] = 255;
    }

    // Implement biomes later
    if (this->GroundUpContinuous)
    {
        for (int i=0; i<256; i++)
        {
            BiomeArray[i] = 1;
        }
    }

    int bufferlen = 0;
    if (this->GroundUpContinuous)
        bufferlen = blockLength/2*5+256;
    else
        bufferlen = blockLength/2*5;

    unsigned char* buffer = new unsigned char[bufferlen];
    memcpy(buffer, BlockTypeArray, blockLength);
    memcpy(buffer+blockLength, BlockMetadataArray, blockLength/2);
    memcpy(buffer+(blockLength/2)*3, BlockLightArray, blockLength/2);
    memcpy(buffer+(blockLength/2)*4, SkyLightArray, blockLength/2);
    if (this->GroundUpContinuous) memcpy(buffer+(blockLength/2)*5, BiomeArray, 256);

    // zlib deflate

    unsigned char* tmp = new unsigned char[(int)(bufferlen*1.3)];

    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    defstream.avail_in = (uInt)bufferlen;
    defstream.next_in = buffer;
    defstream.avail_out = (uInt)(bufferlen*1.3);
    defstream.next_out = tmp;

    deflateInit(&defstream, Z_DEFAULT_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

    this->CompressedSize = defstream.total_out;


    this->len = 22+this->CompressedSize;
    char* res = new char[this->len];
    *res = OPCode;
    *(int*)(res+1) = htobe32(this->x);
    *(int*)(res+5) = htobe32(this->z);
    *(res+9) = this->GroundUpContinuous;
    *(unsigned short*)(res+10) = htobe16(this->PrimaryBitmap);
    *(unsigned short*)(res+12) = htobe16(this->AddBitmap);
    *(int*)(res+14) = htobe32(this->CompressedSize);
    *(int*)(res+18) = 0;
    memcpy(res+22, tmp, this->CompressedSize); // may need to change to BE?
    return res;
}

bool ChunkData::isGroundUpContinuous()
{
    for (int y=0;y<256;y++)
    {
        bool onlyAir = true;
        for (int z=0;z<16;z++)
        {
            for (int x=0;x<16;x++)
            {
                if (chunk->GetBlock(x,y,z)->id != Material::AIR) onlyAir = false;
            }
        }
        if (onlyAir) return true;
    }
    return false;
}

unsigned short ChunkData::calcPrimaryBitmap()
{
    unsigned short bitmask = 0;
    for (int i=0; i<16; i++)
    {
        bool onlyAir = true;
        for (int y=0;y<16;y++)
        {
            
            for (int z=0;z<16;z++)
            {
                for (int x=0;x<16;x++)
                {
                    if (!onlyAir) break;
                    if (chunk->GetBlock(x,y+i*16,z)->id != Material::AIR) onlyAir = false;
                }
                if (!onlyAir) break;
            }
            if (!onlyAir) bitmask |= (unsigned short)1 << i;
        }
    }
    return bitmask;
}

void ChunkData::Send(Client* c)
{
    char* r = build();
    c->writeBytes(r, this->len);
}