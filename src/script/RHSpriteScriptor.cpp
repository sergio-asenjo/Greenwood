#include "RHSpriteScriptor.h"
#include <string.h>
#include <stdlib.h>

class RHProfileFile : public SBFile
{
public:
    int FUN_005f5370(int offset, int origin);
};

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(RHUnkSpriteUshortVector, 0x10)
DECOMP_SIZE_ASSERT(RHUnkSpriteRow, 0x64)
DECOMP_SIZE_ASSERT(RHUnkSpriteScriptInfo, 0x18)
DECOMP_SIZE_ASSERT(RHUnkSpriteCacheNode, 0x34)
DECOMP_SIZE_ASSERT(RHUnkSpriteCacheIterator, 0x04)
DECOMP_SIZE_ASSERT(RHUnkSpriteCacheValue, 0x28)
DECOMP_SIZE_ASSERT(RHUnkSpriteCacheInsertResult, 0x08)
DECOMP_SIZE_ASSERT(RHUnkSpriteCache, 0x10)
DECOMP_SIZE_ASSERT(RHUnkSpriteFileHeader, 0x2e)
DECOMP_SIZE_ASSERT(RHSpriteScriptor, 0x14)
DECOMP_SIZE_ASSERT(RHUnkSpriteRowHeader, 0x0e)
DECOMP_SIZE_ASSERT(RHUnkSpriteFrameHeader, 0x0e)

// FUNCTION: GAME 0x0044e830
unsigned RHUnkSpriteUshortVector::FUN_0044e830() const
{
    return m_first == 0 ? 0 : m_last - m_first;
}

// FUNCTION: GAME 0x00506b10
bool RHUnkSpriteBank::FUN_00506b10(SBFile *file)
{
    file->Access(&file, 4);
    return (undefined4)file == m_b4;
}

// FUNCTION: GAME 0x005bd000
RHUnkSpriteScriptInfo::~RHUnkSpriteScriptInfo()
{
}

// FUNCTION: GAME 0x005bdfa0
unsigned short *RHUnkSpriteUshortVector::FUN_005bdfa0(unsigned short *first, unsigned short *last)
{
    return ((std::vector<unsigned short> *)this)->erase(first, last);
}

// Parked: 58.91%; frame 0x228 versus 0x230 and cache/EH temporary coloring.
// STUB: GAME 0x005bf160
RHUnkSpriteScriptInfo RHSpriteScriptor::LoadSpriteScript(RHframeKind kind, const std::string &name, const std::string &profile)
{
    std::string path;
    std::string directory;
    std::string ambiance;
    RHUnk005f4fc0 file;
    std::string key;
    SBGeoVector2D position;
    SBGeoVector2D size;
    key = FUN_004e4b40(name, profile);
    RHUnkSpriteCacheIterator ending = m_cache.end();
    if (m_cache.FUN_005c0800(key).m_node == ending.m_node)
    {
        switch (kind)
        {
        case FRAME_0:
        case FRAME_1:
        case FRAME_3:
            directory = g_unk0x006c0620;
            path = FUN_004e4b40(FUN_004e4b40(FUN_004e4b40(directory, std::string("\\")), name),
                              // STRING: GAME 0x006b8a34
                              std::string(".rhs"));
            if (file.FUN_005f5090(path, 1) != 0)
                SBAssert(1,
                         // STRING: GAME 0x006b8a4c
                         "P:\\Robin Hood\\RHSpriteScriptor.cpp", 111,
                         // STRING: GAME 0x006b8b84
                         "Unable to read RHS file %s in directory %s, file error", name.c_str(), directory.c_str());
            break;
        case FRAME_2:
            directory = g_unk0x006c0630;
            switch (*(unsigned *)((char *)g_pEngine + 0x4ad0))
            {
            case 1:
                ambiance = "\\Day\\";
                break;
            case 2:
                ambiance = "\\Fog\\";
                break;
            case 4:
                ambiance = "\\Night\\";
                break;
            case 8:
                ambiance = "\\Attack\\";
                break;
            case 16:
                ambiance = "\\Custom1\\";
                break;
            case 32:
                ambiance = "\\Custom2\\";
                break;
            case 64:
                ambiance = "\\Custom3\\";
                break;
            case 128:
                ambiance = "\\Custom4\\";
                break;
            }
            path = FUN_004e4b40(FUN_004e4b40(FUN_004e4b40(directory, ambiance), name), std::string(".rhs"));
            if (!FUN_005f6400(path))
            {
                path = FUN_004e4b40(FUN_004e4b40(FUN_004e4c70(directory, "\\Day\\"), name), std::string(".rhs"));
                if (!FUN_005f6400(path))
                {
                    path = FUN_004e4b40(FUN_004e4b40(FUN_004e4c70(directory, "\\"), name), std::string(".rhs"));
                    if (!FUN_005f6400(path))
                        SBAssert(1, "P:\\Robin Hood\\RHSpriteScriptor.cpp", 171,
                                 // STRING: GAME 0x006b8b2c
                                 "STRENG VERBOTEN : Unable to find RHS file %s in directory %s (ambiance %s), file error",
                                 name.c_str(), directory.c_str(), ambiance.c_str());
                }
            }
            if (file.FUN_005f5090(path, 1) != 0)
                SBAssert(1, "P:\\Robin Hood\\RHSpriteScriptor.cpp", 179,
                         // STRING: GAME 0x006b8adc
                         "VERBOTEN : Unable to read RHS file %s in directory %s (ambiance %s), file error",
                         name.c_str(), directory.c_str(), ambiance.c_str());
            break;
        }
        if (!g_unk0x006c0b1c->FUN_00506b10(&file))
            SBAssert(1, "P:\\Robin Hood\\RHSpriteScriptor.cpp", 190,
                     // STRING: GAME 0x006b8aa4
                     "RHS file %s\\%s was not generated with the current bank", directory.c_str(), name.c_str());
        if (!FUN_005c0490(file, profile.c_str()))
            SBAssert(1, "P:\\Robin Hood\\RHSpriteScriptor.cpp", 197,
                     // STRING: GAME 0x006b8a70
                     "Unable to read profile named %s from the rhs file", profile.c_str());
        RHUnkSpriteFileHeader header;
        file.Access(&header, 0x2e);
        std::vector<unsigned short> *indices = new std::vector<unsigned short>;
        std::vector<RHUnkSpriteRow> *rows = new std::vector<RHUnkSpriteRow>;
        indices->resize(0x11b);
        for (unsigned i = 0; i < 0x11b; ++i)
            (*indices)[i] = 0xffff;
        FUN_005bfef0(file, header.m_rows, *rows, *indices);
        file.FUN_005f5290();
        position = SBGeoVector2D((float)header.m_x, (float)header.m_y);
        size = SBGeoVector2D((float)header.m_26, (float)header.m_size);
        RHUnkSpriteScriptInfo &entry = m_cache[key];
        entry.m_rows = rows;
        entry.m_indices = indices;
        entry.m_position = position;
        entry.m_size = size;
    }
    return m_cache[key];
}

// Parked: 76.05%; container/EH layout and helper emission differ.
// STUB: GAME 0x005bfef0
void RHSpriteScriptor::FUN_005bfef0(SBFile &file, unsigned short count, std::vector<RHUnkSpriteRow> &rows, std::vector<unsigned short> &indices)
{
    rows.clear();
    rows.resize(count);
    unsigned total = 0;
    unsigned short rateTotal;
    unsigned short frameTotal;
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnkSpriteRowHeader header;
        file.Access(&header, 0x0e);
        if (indices[header.m_index] == 0xffff)
            indices[header.m_index] = i;
        rows[i].m_00 = header.m_kind;
        unsigned short frameCount = header.m_count;
        rows[i].m_position = SBGeoPoint2D((float)header.m_x, (float)header.m_y);
        rows[i].m_frames.resize(frameCount);
        rows[i].m_rates.resize(frameCount);
        rows[i].m_resources.resize(frameCount);
        rows[i].m_positions.resize(frameCount);
        rows[i].m_flags.resize(frameCount);
        total += frameCount;
        rows[i].m_04 = 0;
        unsigned j = 0;
        while (frameCount != 0)
        {
            RHUnkSpriteFrameHeader frame;
            file.Access(&frame, 0x0e);
            rows[i].m_resources[j] = frame.m_resource;
            rows[i].m_frames[j] = frame.m_frames;
            rows[i].m_rates[j] = (unsigned short)abs(frame.m_rate);
            rows[i].m_positions[j] = SBGeoVector2D((float)frame.m_x, (float)frame.m_y);
            rows[i].m_flags[j] = frame.m_flags;
            rows[i].m_04 += (unsigned short)frame.m_rate;
            frameTotal += frame.m_frames < 1 ? 1 : frame.m_frames;
            rateTotal += (unsigned short)frame.m_rate;
            ++j;
            --frameCount;
        }
        rows[i].m_04 /= (unsigned short)frameTotal;
        rows[i].m_10 = (unsigned short)rateTotal;
    }
}

// FUNCTION: GAME 0x005c0490
bool RHSpriteScriptor::FUN_005c0490(SBFile &file, const char *profile)
{
    unsigned short count;
    RHUnkSpriteFileHeader header;
    unsigned short index = 0;
    file.Access(&count, 2);
    file.Access(&header, 0x2e);
    while (strcmp(header.m_name, profile) != 0 && index < count - 1)
    {
        for (unsigned short row = header.m_rows; row > 0; --row)
        {
            RHUnkSpriteRowHeader rowHeader;
            file.Access(&rowHeader, 0x0e);
            for (unsigned short frame = rowHeader.m_count; frame > 0; --frame)
                ((RHProfileFile &)file).FUN_005f5370(0x0e, 1);
        }
        file.Access(&header, 0x2e);
        ++index;
    }
    if (strcmp(header.m_name, profile) == 0)
    {
        ((RHProfileFile &)file).FUN_005f5370(-0x2e, 1);
        return true;
    }
    return false;
}

// Parked: 93.33%; pair conversion reads a byte instead of a dword.
// STUB: GAME 0x005c0690
RHUnkSpriteCacheInsertResult RHUnkSpriteCache::FUN_005c0690(const RHUnkSpriteCacheValue &value)
{
    RHUnkSpriteCacheInsertResult result(FUN_005c09c0(value));
    return result;
}

// Parked: 98.31%; STL null-string storage is not the pooled empty literal.
// STUB: GAME 0x005c0800
RHUnkSpriteCacheIterator RHUnkSpriteCache::FUN_005c0800(const std::string &key)
{
    RHUnkSpriteCacheIterator result;
    result.m_node = FUN_005c15a0(key);
    return result == end() || key < result.m_node->m_key ? end() : result;
}

// Parked: 97.27%; STL null-string storage is not the pooled empty literal.
// STUB: GAME 0x005c0890
RHUnkSpriteCacheValue::RHUnkSpriteCacheValue(const std::string &key, const RHUnkSpriteScriptInfo &info)
    : m_key(key), m_info(info)
{
}

void RHSpriteScriptor::Emit(const std::string &name, const std::string &profile)
{
    LoadSpriteScript(FRAME_2, name, profile);
    RHUnkSpriteUshortVector *vector = (RHUnkSpriteUshortVector *)this;
    vector->FUN_0044e830();
    vector->FUN_005bdfa0(vector->m_first, vector->m_last);
}
