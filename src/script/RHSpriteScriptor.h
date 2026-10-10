#ifndef RHSPRITESCRIPTOR_H
#define RHSPRITESCRIPTOR_H

#include "RHSaveGame.h"
#include "Decomp.h"
#include <vector>

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &point);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    float m_x; // +0x00
    float m_y; // +0x04
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float x, float y);
    SBGeoVector2D(const SBGeoVector2D &other);
    ~SBGeoVector2D() {}
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

// SIZE 0x10
class RHUnkSpriteUshortVector
{
public:
    unsigned FUN_0044e830() const;
    unsigned short *FUN_005bdfa0(unsigned short *first, unsigned short *last);
    undefined m_0[4]; // 0x00
    unsigned short *m_first; // 0x04
    unsigned short *m_last; // 0x08
    unsigned short *m_end; // 0x0c
};

// SIZE 0x64
struct RHUnkSpriteRow
{
    RHUnkSpriteRow();
    undefined2 m_00; // 0x00
    float m_04; // 0x04
    SBGeoPoint2D m_position; // 0x08
    undefined2 m_10; // 0x10
    std::vector<int> m_resources; // 0x14
    std::vector<unsigned short> m_frames; // 0x24
    std::vector<unsigned short> m_rates; // 0x34
    std::vector<SBGeoVector2D> m_positions; // 0x44
    std::vector<unsigned short> m_flags; // 0x54
};

// SIZE 0x18
struct RHUnkSpriteScriptInfo
{
    RHUnkSpriteScriptInfo() {}
    RHUnkSpriteScriptInfo(const RHUnkSpriteScriptInfo &other)
        : m_rows(other.m_rows), m_indices(other.m_indices), m_position(other.m_position), m_size(other.m_size) {}
    ~RHUnkSpriteScriptInfo();
    std::vector<RHUnkSpriteRow> *m_rows; // +0x00
    std::vector<unsigned short> *m_indices; // +0x04
    SBGeoVector2D m_position; // +0x08
    SBGeoVector2D m_size; // +0x10; sizeof = 0x18
};

// SIZE 0x34
struct RHUnkSpriteCacheNode
{
    undefined m_0[0x0c]; // 0x00
    std::string m_key; // 0x0c
    RHUnkSpriteScriptInfo m_value; // +0x1c
};

// SIZE 0x04
struct RHUnkSpriteCacheIterator
{
    RHUnkSpriteCacheNode *m_node; // 0x00
    bool operator==(const RHUnkSpriteCacheIterator &other) const { return m_node == other.m_node; }
};

// SIZE 0x28
struct RHUnkSpriteCacheValue
{
    RHUnkSpriteCacheValue(const std::string &key, const RHUnkSpriteScriptInfo &info);
    std::string m_key; // +0x00
    RHUnkSpriteScriptInfo m_info; // +0x10; sizeof = 0x28
};

// SIZE 0x08
struct RHUnkSpriteCacheInsertResult
{
    RHUnkSpriteCacheInsertResult() {}
    RHUnkSpriteCacheInsertResult(const std::pair<RHUnkSpriteCacheIterator, bool> &other)
        : m_first(other.first), m_second(other.second) {}
    RHUnkSpriteCacheInsertResult(const RHUnkSpriteCacheIterator &first, const bool &second)
        : m_first(first), m_second(second) {}
    RHUnkSpriteCacheIterator m_first; // 0x00
    undefined m_second; // 0x04
};

// SIZE 0x10
class RHUnkSpriteCache
{
public:
    RHUnkSpriteCacheIterator FUN_005c0800(const std::string &key);
    RHUnkSpriteCacheInsertResult FUN_005c0690(const RHUnkSpriteCacheValue &value);
    std::pair<RHUnkSpriteCacheIterator, bool> FUN_005c09c0(const RHUnkSpriteCacheValue &value);
    RHUnkSpriteCacheNode *FUN_005c15a0(const std::string &key);
    RHUnkSpriteCacheIterator end() const { RHUnkSpriteCacheIterator it; it.m_node = m_head; return it; }
    RHUnkSpriteScriptInfo &operator[](const std::string &key)
    {
        return FUN_005c0690(RHUnkSpriteCacheValue(key, RHUnkSpriteScriptInfo())).m_first.m_node->m_value;
    }
    undefined m_0[4]; // 0x00
    RHUnkSpriteCacheNode *m_head; // +0x04
    undefined4 m_08; // 0x08
    unsigned m_count; // 0x0c
};

#pragma pack(push, 1)
// SIZE 0x2e
struct RHUnkSpriteFileHeader
{
    char m_name[0x20]; // +0x00
    unsigned short m_rows; // +0x20
    unsigned short m_x; // +0x22
    unsigned short m_y; // +0x24
    int m_26; // +0x26
    int m_size; // +0x2a; sizeof = 0x2e
};
#pragma pack(pop)

class RHUnkSpriteBank
{
public:
    bool FUN_00506b10(SBFile *file);
    undefined m_0[0xb4]; // 0x00
    undefined4 m_b4; // 0xb4
};

#pragma pack(push, 1)
// SIZE 0x0e
struct RHUnkSpriteRowHeader
{
    unsigned short m_count; // 0x00
    unsigned short m_kind; // 0x02
    int m_x; // 0x04
    int m_y; // 0x08
    unsigned short m_index; // 0x0c
};

// SIZE 0x0e
struct RHUnkSpriteFrameHeader
{
    int m_resource; // 0x00
    unsigned short m_frames; // 0x04
    short m_rate; // 0x06
    short m_x; // 0x08
    short m_y; // 0x0a
    unsigned short m_flags; // 0x0c
};
#pragma pack(pop)

class RHEngine;
extern RHEngine *g_pEngine;
extern RHUnkSpriteBank *g_unk0x006c0b1c;
extern std::string g_unk0x006c0620;
extern std::string g_unk0x006c0630;
std::string FUN_004e4b40(const std::string &first, const std::string &second);
std::string FUN_004e4c70(const std::string &first, const char *second);

// SIZE 0x14
class RHSpriteScriptor
{
public:
    enum RHframeKind { FRAME_0, FRAME_1, FRAME_2, FRAME_3 };
    RHUnkSpriteScriptInfo LoadSpriteScript(RHframeKind kind, const std::string &name, const std::string &profile);
    bool FUN_005c0490(SBFile &file, const char *profile);
    void FUN_005bfef0(SBFile &file, unsigned short count, std::vector<RHUnkSpriteRow> &rows, std::vector<unsigned short> &indices);
    void Emit(const std::string &name, const std::string &profile);
    undefined m_0[4]; // +0x00
    RHUnkSpriteCache m_cache; // +0x04, head at +0x08
};

#endif
