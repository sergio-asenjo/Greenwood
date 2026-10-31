#include "SBNullstr.h"
#include "RHSpriteScriptor.h"
#include "RHCampaignCommandLine.h"
#include "RHSoundCacheCore.h"
#include "RHTreeDec.h"
#include <string.h>
#include <stdlib.h>

extern RHTreeDecNode34 *g_unk0x006c10e0;

struct RHTreeInc005c11c0
{
    RHTreeDecNode34 *m_node;
    void FUN_005c11c0();
};

static inline RHTreeDecNode34 *RHSpriteTreeMinimum(RHTreeDecNode34 *node)
{
    RHUnk00641782Lock lock;
    while (node->m_00 != g_unk0x006c10e0)
        node = node->m_00;
    return node;
}

struct RHSpriteInsertNode
{
    RHSpriteInsertNode *m_00;
    RHSpriteInsertNode *m_04;
    RHSpriteInsertNode *m_08;
    RHUnkSpriteCacheValue m_0c;
    int m_34;
};

struct RHSpriteInsertIterator
{
    RHSpriteInsertNode *m_node;
    RHSpriteInsertIterator operator++(int)
    {
        RHSpriteInsertIterator previous = *this;
        ((RHTreeInc005c11c0 *)this)->FUN_005c11c0();
        return previous;
    }
};


class RHSpriteInsertTree
{
public:
    RHSpriteInsertIterator FUN_005c1290(RHSpriteInsertNode *, RHSpriteInsertNode *, const RHUnkSpriteCacheValue &);
    static RHSpriteInsertNode *&Left(RHSpriteInsertNode *node) { return node->m_00; }
    inline void RotateLeft(RHSpriteInsertNode *node)
    {
        RHUnk00641782Lock lock;
        RHSpriteInsertNode *right = node->m_08;
        node->m_08 = right->m_00;
        if (right->m_00 != (RHSpriteInsertNode *)g_unk0x006c10e0) right->m_00->m_04 = node;
        right->m_04 = node->m_04;
        if (node == m_head->m_04) m_head->m_04 = right;
        else if (node == node->m_04->m_00) node->m_04->m_00 = right;
        else node->m_04->m_08 = right;
        right->m_00 = node;
        node->m_04 = right;
    }
    inline void RotateRight(RHSpriteInsertNode *node)
    {
        RHUnk00641782Lock lock;
        RHSpriteInsertNode *left = node->m_00;
        node->m_00 = left->m_08;
        if (left->m_08 != (RHSpriteInsertNode *)g_unk0x006c10e0) left->m_08->m_04 = node;
        left->m_04 = node->m_04;
        if (node == m_head->m_04) m_head->m_04 = left;
        else if (node == node->m_04->m_08) node->m_04->m_08 = left;
        else node->m_04->m_00 = left;
        left->m_08 = node;
        node->m_04 = left;
    }
    void FUN_005bf080();
    RHSpriteInsertIterator FUN_005c06c0(RHSpriteInsertIterator, RHSpriteInsertIterator);
    RHSpriteInsertIterator FUN_005c0b50(RHSpriteInsertIterator);
    void FUN_005c10d0(RHSpriteInsertNode *);
    static RHSpriteInsertNode *&Parent(RHSpriteInsertNode *node) { return node->m_04; }
    static RHSpriteInsertNode *&Right(RHSpriteInsertNode *node) { return node->m_08; }
    static int &Color(RHSpriteInsertNode *node) { return node->m_34; }
    RHSpriteInsertNode *&Root() { return m_head->m_04; }
    RHSpriteInsertNode *&Leftmost() { return m_head->m_00; }
    RHSpriteInsertNode *&Rightmost() { return m_head->m_08; }
    RHSpriteInsertIterator Begin()
    {
        RHSpriteInsertIterator result;
        result.m_node = Leftmost();
        return result;
    }
    unsigned m_00;
    RHSpriteInsertNode *m_head;
    unsigned m_08;
    unsigned m_count;
};

static inline RHSpriteInsertNode *RHSpriteInsertMinimum(RHSpriteInsertNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_00 != (RHSpriteInsertNode *)g_unk0x006c10e0)
        node = node->m_00;
    return node;
}

static inline RHSpriteInsertNode *RHSpriteInsertMaximum(RHSpriteInsertNode *node)
{
    RHUnk00641782Lock lock;
    while (node->m_08 != (RHSpriteInsertNode *)g_unk0x006c10e0)
        node = node->m_08;
    return node;
}

static inline void RHSpriteDestroyValue(RHUnkSpriteCacheValue &value)
{
    value.m_info.m_size.~SBGeoVector2D();
    value.m_info.m_position.~SBGeoVector2D();
    value.m_key.~basic_string();
}

class RHProfileFile : public SBFile
{
public:
    int FUN_005f5370(int offset, int origin);
};

class RHSpritePointVectorEmission : public std::vector<SBGeoPoint2D>
{
public:
    static void Emit()
    {
        void (std::vector<SBGeoPoint2D>::*volatile destroy)(SBGeoPoint2D *, SBGeoPoint2D *) = &RHSpritePointVectorEmission::_Destroy;
        void (std::vector<SBGeoPoint2D>::*volatile insert)(SBGeoPoint2D *, unsigned int, const SBGeoPoint2D &) = &RHSpritePointVectorEmission::insert;
        SBGeoPoint2D *(std::vector<SBGeoPoint2D>::*volatile insertOne)(SBGeoPoint2D *, const SBGeoPoint2D &) = &RHSpritePointVectorEmission::insert;
        SBGeoPoint2D *(std::vector<SBGeoPoint2D>::*volatile copy)(const SBGeoPoint2D *, const SBGeoPoint2D *, SBGeoPoint2D *) = &RHSpritePointVectorEmission::_Ucopy;
        void (std::vector<SBGeoPoint2D>::*volatile fill)(SBGeoPoint2D *, unsigned int, const SBGeoPoint2D &) = &RHSpritePointVectorEmission::_Ufill;
    }
};

class RHSpriteGeometryVectorEmission : public std::vector<SBGeoVector2D>
{
public:
    static void Emit()
    {
        RHSpritePointVectorEmission::Emit();
        void (std::vector<SBGeoVector2D>::*volatile clear)() = &RHSpriteGeometryVectorEmission::clear;
        SBGeoVector2D *(std::vector<SBGeoVector2D>::*volatile insertOne)(SBGeoVector2D *, const SBGeoVector2D &) = &RHSpriteGeometryVectorEmission::insert;
        void (std::vector<SBGeoVector2D>::*volatile destroy)(SBGeoVector2D *, SBGeoVector2D *) = &RHSpriteGeometryVectorEmission::_Destroy;
        void (std::vector<SBGeoVector2D>::*volatile fill)(SBGeoVector2D *, unsigned int, const SBGeoVector2D &) = &RHSpriteGeometryVectorEmission::_Ufill;
        void (__cdecl *volatile pointFill)(SBGeoPoint2D *, SBGeoPoint2D *, const SBGeoPoint2D &) = &std::fill;
        SBGeoPoint2D *(__cdecl *volatile pointCopyBackward)(SBGeoPoint2D *, SBGeoPoint2D *, SBGeoPoint2D *) = &std::copy_backward;
        void (__cdecl *volatile vectorFill)(SBGeoVector2D *, SBGeoVector2D *, const SBGeoVector2D &) = &std::fill;
        SBGeoVector2D *(__cdecl *volatile vectorCopyBackward)(SBGeoVector2D *, SBGeoVector2D *, SBGeoVector2D *) = &std::copy_backward;
    }
};

class RHSpriteRowVectorEmission : public std::vector<RHUnkSpriteRow>
{
public:
    static void Emit()
    {
        RHSpriteGeometryVectorEmission::Emit();
        void (std::vector<RHUnkSpriteRow>::*volatile destroy)(RHUnkSpriteRow *, RHUnkSpriteRow *) = &RHSpriteRowVectorEmission::_Destroy;
    }
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

// LIBRARY: GAME 0x0044e830
// ?size@?$vector@GV?$allocator@G@std@@@std@@QBEIXZ

// TEMPLATE: GAME 0x00461f10
// ?_Construct@std@@YAXPAVSBGeoPoint2D@@ABV2@@Z

// TEMPLATE: GAME 0x004afd70
// ?insert@?$vector@VSBGeoVector2D@@V?$allocator@VSBGeoVector2D@@@std@@@std@@QAEPAVSBGeoVector2D@@PAV3@ABV3@@Z

// TEMPLATE: GAME 0x004afbc0
// ?insert@?$vector@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@QAEPAVSBGeoPoint2D@@PAV3@ABV3@@Z

// TEMPLATE: GAME 0x004aff00
// ?_Destroy@?$vector@VSBGeoVector2D@@V?$allocator@VSBGeoVector2D@@@std@@@std@@IAEXPAVSBGeoVector2D@@0@Z

// TEMPLATE: GAME 0x004aff30
// ?insert@?$vector@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@QAEXPAVSBGeoPoint2D@@IABV3@@Z

// TEMPLATE: GAME 0x004b01b0
// ?insert@?$vector@VSBGeoVector2D@@V?$allocator@VSBGeoVector2D@@@std@@@std@@QAEXPAVSBGeoVector2D@@IABV3@@Z

// TEMPLATE: GAME 0x004b0430
// ?_Destroy@?$vector@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@IAEXPAVSBGeoPoint2D@@0@Z

// TEMPLATE: GAME 0x004b0460
// ?_Ucopy@?$vector@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@IAEPAVSBGeoPoint2D@@PBV3@0PAV3@@Z

// TEMPLATE: GAME 0x004b04a0
// ?_Ufill@?$vector@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@IAEXPAVSBGeoPoint2D@@IABV3@@Z

// TEMPLATE: GAME 0x004b04d0
// ?_Ucopy@?$vector@VSBGeoVector2D@@V?$allocator@VSBGeoVector2D@@@std@@@std@@IAEPAVSBGeoVector2D@@PBV3@0PAV3@@Z

// TEMPLATE: GAME 0x004b0510
// ?_Ufill@?$vector@VSBGeoVector2D@@V?$allocator@VSBGeoVector2D@@@std@@@std@@IAEXPAVSBGeoVector2D@@IABV3@@Z

// TEMPLATE: GAME 0x004b0540
// ?fill@std@@YAXPAVSBGeoPoint2D@@0ABV2@@Z

// TEMPLATE: GAME 0x004b0570
// ?copy_backward@std@@YAPAVSBGeoPoint2D@@PAV2@00@Z

// TEMPLATE: GAME 0x004b05b0
// ?fill@std@@YAXPAVSBGeoVector2D@@0ABV2@@Z

// TEMPLATE: GAME 0x004b05e0
// ?copy_backward@std@@YAPAVSBGeoVector2D@@PAV2@00@Z

// TEMPLATE: GAME 0x004b0620
// ?_Construct@std@@YAXPAVSBGeoVector2D@@ABV2@@Z

// TEMPLATE: GAME 0x004b06a0
// ?clear@?$vector@VSBGeoVector2D@@V?$allocator@VSBGeoVector2D@@@std@@@std@@QAEXXZ

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

// TEMPLATE: GAME 0x005bdf70
// ?size@?$vector@URHUnkSpriteRow@@V?$allocator@URHUnkSpriteRow@@@std@@@std@@QBEIXZ

// LIBRARY: GAME 0x005bdfa0
// ?erase@?$vector@GV?$allocator@G@std@@@std@@QAEPAGPAG0@Z

// TEMPLATE: GAME 0x005bdfe0
// ?insert@?$vector@URHUnkSpriteRow@@V?$allocator@URHUnkSpriteRow@@@std@@@std@@QAEXPAURHUnkSpriteRow@@IABU3@@Z

// TEMPLATE: GAME 0x005be330
// ?erase@?$vector@URHUnkSpriteRow@@V?$allocator@URHUnkSpriteRow@@@std@@@std@@QAEPAURHUnkSpriteRow@@PAU3@0@Z

// TEMPLATE: GAME 0x005be400
// ?_Destroy@?$vector@URHUnkSpriteRow@@V?$allocator@URHUnkSpriteRow@@@std@@@std@@IAEXPAURHUnkSpriteRow@@0@Z

// TEMPLATE: GAME 0x005be430
// ?_Construct@std@@YAXPAURHUnkSpriteRow@@ABU2@@Z

// TEMPLATE: GAME 0x005be880
// ??4?$vector@VSBGeoVector2D@@V?$allocator@VSBGeoVector2D@@@std@@@std@@QAEAAV01@ABV01@@Z

// LIBRARY: GAME 0x005bea70
// ??0?$vector@GV?$allocator@G@std@@@std@@QAE@ABV01@@Z

// LIBRARY: GAME 0x005bead0
// ??4?$vector@GV?$allocator@G@std@@@std@@QAEAAV01@ABV01@@Z

// LIBRARY: GAME 0x005bec50
// ?capacity@?$vector@GV?$allocator@G@std@@@std@@QBEIXZ

// LIBRARY: GAME 0x005bec70 FOLDED
// ?copy@std@@YAPAGPBG0PAG@Z

// LIBRARY: GAME 0x005bec70 FOLDED
// ?copy@std@@YAPAGPAG00@Z

// GLOBAL: GAME 0x006c10dc
unsigned g_unk0x006c10dc;

// FUNCTION: GAME 0x005bf080
void RHSpriteInsertTree::FUN_005bf080()
{
    RHSpriteInsertIterator first = Begin();
    RHSpriteInsertIterator last;
    last.m_node = m_head;
    FUN_005c06c0(first, last);
    operator delete(m_head);
    m_head = 0;
    m_count = 0;
    {
        RHUnk00641782Lock lock;
        if (--g_unk0x006c10dc == 0) {
            operator delete(g_unk0x006c10e0);
            g_unk0x006c10e0 = 0;
        }
    }
}

// GLOBAL: GAME 0x006c10d8
RHSpriteScriptor *g_unk0x006c10d8;

// FUNCTION: GAME 0x005bf0f0
RHSpriteScriptor *RHSpriteScriptor::GetInstance()
{
    if (!g_unk0x006c10d8)
        g_unk0x006c10d8 = new RHSpriteScriptor;
    return g_unk0x006c10d8;
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
                path = FUN_004e4b40(FUN_004e4b40((directory + "\\Day\\"), name), std::string(".rhs"));
                if (!FUN_005f6400(path))
                {
                    path = FUN_004e4b40(FUN_004e4b40((directory + "\\"), name), std::string(".rhs"));
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

// Parked: the original inlines the info destructor here; its out-of-line definition stays a separate call.
// STUB: GAME 0x005c0600
RHUnkSpriteCacheValue::~RHUnkSpriteCacheValue()
{
}

// FUNCTION: GAME 0x005c0690
RHUnkSpriteCacheInsertResult RHUnkSpriteCache::FUN_005c0690(const RHUnkSpriteCacheValue &value)
{
    std::pair<RHUnkSpriteCacheIterator, bool> answer;
    answer = FUN_005c09c0(value);
    RHUnkSpriteCacheInsertResult result(answer.first, answer.second);
    return result;
}

// FUNCTION: GAME 0x005c06c0
RHSpriteInsertIterator RHSpriteInsertTree::FUN_005c06c0(RHSpriteInsertIterator first, RHSpriteInsertIterator last)
{
    if (m_count != 0 && first.m_node == m_head->m_00 && last.m_node == m_head) {
        RHUnk00641782Lock lock;
        RHSpriteInsertNode *node = Root();
        {
            RHUnk00641782Lock inner;
            for (RHSpriteInsertNode *next = node; next != (RHSpriteInsertNode *)g_unk0x006c10e0; node = next) {
                FUN_005c10d0(next->m_08);
                next = next->m_00;
                node->m_0c.~RHUnkSpriteCacheValue();
                operator delete(node);
            }
        }
        Root() = (RHSpriteInsertNode *)g_unk0x006c10e0;
        m_count = 0;
        Leftmost() = m_head;
        Rightmost() = m_head;
        return Begin();
    }
    while (first.m_node != last.m_node)
        FUN_005c0b50(first++);
    return first;
}

// FUNCTION: GAME 0x005c0800
RHUnkSpriteCacheIterator RHUnkSpriteCache::FUN_005c0800(const std::string &key)
{
    RHUnkSpriteCacheIterator result;
    result.m_node = FUN_005c15a0(key);
    return result == end() || key < result.m_node->m_key ? end() : result;
}

// FUNCTION: GAME 0x005c0890
RHUnkSpriteCacheValue::RHUnkSpriteCacheValue(const std::string &key, const RHUnkSpriteScriptInfo &info)
    : m_key(key), m_info(info)
{
}

// Parked: the original inlines the value and info destructors with their unwind states.
// STUB: GAME 0x005c0b50
RHSpriteInsertIterator RHSpriteInsertTree::FUN_005c0b50(RHSpriteInsertIterator position)
{
    RHSpriteInsertNode *x;
    RHSpriteInsertNode *y = (position++).m_node;
    RHSpriteInsertNode *z = y;
    RHUnk00641782Lock lock;
    if (Left(y) == (RHSpriteInsertNode *)g_unk0x006c10e0)
        x = Right(y);
    else if (Right(y) == (RHSpriteInsertNode *)g_unk0x006c10e0)
        x = Left(y);
    else
    {
        y = RHSpriteInsertMinimum(Right(y));
        x = Right(y);
    }
    {
        if (y != z)
        {
            Parent(Left(z)) = y;
            Left(y) = Left(z);
            if (y == Right(z))
                Parent(x) = y;
            else
            {
                Parent(x) = Parent(y);
                Left(Parent(y)) = x;
                Right(y) = Right(z);
                Parent(Right(z)) = y;
            }
            if (Root() == z)
                Root() = y;
            else if (Left(Parent(z)) == z)
                Left(Parent(z)) = y;
            else
                Right(Parent(z)) = y;
            Parent(y) = Parent(z);
            std::swap(Color(y), Color(z));
            y = z;
        }
        else
        {
            Parent(x) = Parent(y);
            if (Root() == z)
                Root() = x;
            else if (Left(Parent(z)) == z)
                Left(Parent(z)) = x;
            else
                Right(Parent(z)) = x;
            if (Leftmost() == z)
            {
                if (Right(z) == (RHSpriteInsertNode *)g_unk0x006c10e0)
                    Leftmost() = Parent(z);
                else
                {
                    Leftmost() = RHSpriteInsertMinimum(x);
                }
            }
            if (Rightmost() == z)
            {
                if (Left(z) == (RHSpriteInsertNode *)g_unk0x006c10e0)
                    Rightmost() = Parent(z);
                else
                {
                    Rightmost() = RHSpriteInsertMaximum(x);
                }
            }
        }
        if (Color(y) == 1)
        {
            while (x != Root() && Color(x) == 1)
            {
                if (x == Left(Parent(x)))
                {
                    RHSpriteInsertNode *w = Right(Parent(x));
                    if (Color(w) == 0)
                    {
                        Color(w) = 1;
                        Color(Parent(x)) = 0;
                        RotateLeft(Parent(x));
                        w = Right(Parent(x));
                    }
                    if (Color(Left(w)) == 1 && Color(Right(w)) == 1)
                    {
                        Color(w) = 0;
                        x = Parent(x);
                    }
                    else
                    {
                        if (Color(Right(w)) == 1)
                        {
                            Color(Left(w)) = 1;
                            Color(w) = 0;
                            RotateRight(w);
                            w = Right(Parent(x));
                        }
                        Color(w) = Color(Parent(x));
                        Color(Parent(x)) = 1;
                        Color(Right(w)) = 1;
                        RotateLeft(Parent(x));
                        break;
                    }
                }
                else
                {
                    RHSpriteInsertNode *w = Left(Parent(x));
                    if (Color(w) == 0)
                    {
                        Color(w) = 1;
                        Color(Parent(x)) = 0;
                        RotateRight(Parent(x));
                        w = Left(Parent(x));
                    }
                    if (Color(Right(w)) == 1 && Color(Left(w)) == 1)
                    {
                        Color(w) = 0;
                        x = Parent(x);
                    }
                    else
                    {
                        if (Color(Left(w)) == 1)
                        {
                            Color(Right(w)) = 1;
                            Color(w) = 0;
                            RotateLeft(w);
                            w = Left(Parent(x));
                        }
                        Color(w) = Color(Parent(x));
                        Color(Parent(x)) = 1;
                        Color(Left(w)) = 1;
                        RotateRight(Parent(x));
                        break;
                    }
                }
            }
            Color(x) = 1;
        }
    }
    RHSpriteDestroyValue(y->m_0c);
    operator delete(y);
    --m_count;
    return position;
}

// Parked: the original inlines the value and info destructors with their unwind states.
// STUB: GAME 0x005c10d0
void RHSpriteInsertTree::FUN_005c10d0(RHSpriteInsertNode *node)
{
    RHUnk00641782Lock lock;
    for (RHSpriteInsertNode *next = node; next != (RHSpriteInsertNode *)g_unk0x006c10e0; node = next) {
        FUN_005c10d0(next->m_08);
        next = next->m_00;
        RHSpriteDestroyValue(node->m_0c);
        operator delete(node);
    }
}

// FUNCTION: GAME 0x005c11c0
void RHTreeInc005c11c0::FUN_005c11c0()
{
    RHUnk00641782Lock lock;
    if (m_node->m_08 != g_unk0x006c10e0)
        m_node = RHSpriteTreeMinimum(m_node->m_08);
    else {
        RHTreeDecNode34 *parent;
        while (m_node == (parent = m_node->m_04)->m_08)
            m_node = parent;
        if (m_node->m_08 != parent)
            m_node = parent;
    }
}

void EmitRHSpriteTreeInc(RHTreeInc005c11c0 &iterator)
{
    iterator.FUN_005c11c0();
}

void EmitRHSpriteInsertTreeCleanup(RHSpriteInsertTree &tree)
{
    tree.FUN_005bf080();
}

// FUNCTION: GAME 0x005c1290
RHSpriteInsertIterator RHSpriteInsertTree::FUN_005c1290(RHSpriteInsertNode *node, RHSpriteInsertNode *parent, const RHUnkSpriteCacheValue &value)
{
    RHUnk00641782Lock lock;
    RHSpriteInsertNode *inserted = (RHSpriteInsertNode *)operator new(sizeof(RHSpriteInsertNode));
    inserted->m_04 = parent;
    inserted->m_34 = 0;
    inserted->m_00 = (RHSpriteInsertNode *)g_unk0x006c10e0;
    inserted->m_08 = (RHSpriteInsertNode *)g_unk0x006c10e0;
    void (*construct)(RHUnkSpriteCacheValue *, const RHUnkSpriteCacheValue &) = std::_Construct;
    construct(&inserted->m_0c, value);
    ++m_count;
    if (parent == m_head || node != (RHSpriteInsertNode *)g_unk0x006c10e0 ||
        ((RHCampaignCommandLine *)&value.m_key)->FUN_0045a010(*(const RHProfileText *)&parent->m_0c.m_key) < 0) {
        parent->m_00 = inserted;
        if (parent == m_head) {
            m_head->m_04 = inserted;
            m_head->m_08 = inserted;
        } else if (parent == m_head->m_00) m_head->m_00 = inserted;
    } else {
        parent->m_08 = inserted;
        if (parent == m_head->m_08) m_head->m_08 = inserted;
    }
    for (node = inserted; node != m_head->m_04 && node->m_04->m_34 == 0;) {
        if (node->m_04 == Left(node->m_04->m_04)) {
            parent = node->m_04->m_04->m_08;
            if (parent->m_34 == 0) {
                node->m_04->m_34 = 1;
                parent->m_34 = 1;
                node->m_04->m_04->m_34 = 0;
                node = node->m_04->m_04;
            } else {
                if (node == node->m_04->m_08) {
                    node = node->m_04;
                    RotateLeft(node);
                }
                node->m_04->m_34 = 1;
                node->m_04->m_04->m_34 = 0;
                RotateRight(node->m_04->m_04);
            }
        } else {
            parent = node->m_04->m_04->m_00;
            if (parent->m_34 == 0) {
                node->m_04->m_34 = 1;
                parent->m_34 = 1;
                node->m_04->m_04->m_34 = 0;
                node = node->m_04->m_04;
            } else {
                if (node == node->m_04->m_00) {
                    node = node->m_04;
                    RotateRight(node);
                }
                node->m_04->m_34 = 1;
                node->m_04->m_04->m_34 = 0;
                RotateLeft(node->m_04->m_04);
            }
        }
    }
    m_head->m_04->m_34 = 1;
    RHSpriteInsertIterator result;
    result.m_node = inserted;
    return result;
}

void EmitRHSpriteInsertTree(RHSpriteInsertTree &tree, const RHUnkSpriteCacheValue &value)
{
    tree.FUN_005c1290(0, 0, value);
}

// FUNCTION: GAME 0x005c15a0
RHUnkSpriteCacheNode *RHUnkSpriteCache::FUN_005c15a0(const std::string &key)
{
    RHUnk00641782Lock lock;
    RHUnkSpriteCacheNode *node = m_head->m_parent;
    RHUnkSpriteCacheNode *candidate = m_head;
    while (node != (RHUnkSpriteCacheNode *)g_unk0x006c10e0) {
        if (node->m_key.compare(key) < 0)
            node = node->m_right;
        else {
            candidate = node;
            node = node->m_left;
        }
    }
    return candidate;
}

// TEMPLATE: GAME 0x005c19c0
// ?_Construct@std@@YAXPAURHUnkSpriteCacheValue@@ABU2@@Z

void RHSpriteScriptor::Emit(const std::string &name, const std::string &profile)
{
    RHSpriteRowVectorEmission::Emit();
    unsigned short *(__cdecl *volatile copy)(unsigned short *, unsigned short *, unsigned short *) = std::copy;
    LoadSpriteScript(FRAME_2, name, profile);
    typedef std::vector<unsigned short> Vector;
    Vector *vector = (Vector *)this;
    unsigned (Vector::*size)() const = &Vector::size;
    (vector->*size)();
    unsigned short *(Vector::*erase)(unsigned short *, unsigned short *) = &Vector::erase;
    (vector->*erase)(vector->begin(), vector->end());
}
