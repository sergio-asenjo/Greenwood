#include "RHSpriteScriptor.h"

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
        if (!g_unk0x006c0b1c->FUN_00506b10(file))
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

void RHSpriteScriptor::Emit(const std::string &name, const std::string &profile)
{
    LoadSpriteScript(FRAME_2, name, profile);
}
